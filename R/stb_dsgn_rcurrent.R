## -----------------------------------------------------------------------------
##
##  DESCRIPTION:
##      This file contains R functions for simulating recurrent events
##      All functions start with "stb_rc_"
##
##  DATE:
##      FEBRUARY, 2023
## -----------------------------------------------------------------------------

#' Describe the design
#'
#' @export
#'
rcurrent_describe <- function(x, ...) {
    cat("Type:\n")
    cat("    Study with recurrent events \n\n")
    cat("Design Parameters:\n")
    cat("    sample_size:    total sample size (default 100)\n")
    cat("    ratio_by_arm:   randomization proportion for each arm \n")
    cat("                    (default c(0.5, 0.5))\n")
    cat("    hr_by_arm:      hazard rate, i.e. annualized event rate, for each arm\n")
    cat("                    (default c(0.7, 0.3))\n")
    cat("    k_by_arm:       dispersion for each arm, smaller the bigger variance\n")
    cat("                    (default c(1, 1))\n")
    cat("    alpha:          alpha level (default 0.025)\n")
    cat("    power:          power level (default 0.95)\n")
    cat("    max_n_event:    Maximum number of events for each patient (default 10)\n")
    cat("    par_enroll:     list of enrollment parameters \n")
    cat("    n_stage1:       no. of patients for stage 1 (default 100) \n")
    cat("    fix_fu:         fixed FU days (default 12 * 7) \n")
    cat("    rcur_weight:    Information weight in recurrent events (default 0.2) \n")
    cat("    ssr_zone:       range of total size that will trigger sample size  \n")
    cat("                    adaptation (default c(1.2, 2))\n")

}


#' Default design parameter for single arm
#'
#'
internal_rcurrent_dpara <- function() {
    list(sample_size       = 100,
         ratio_by_arm      = c(0.5, 0.5),
         hr_by_arm         = c(1.3, 1),
         k_by_arm          = c(1, 1),
         par_enroll        = list(type = "by_duration", pt_dur_mth = 16),
         max_n_event       = 10,
         alpha             = 0.025,
         power             = 0.9,
         n_stage1          = 100,
         fix_fu            = 12 * 7,
         rcur_weight       = 0.2,
         ssr_zone          = c(1.2, 2),
         method_samplesize = "EAST")
}

#' Generate data
#'
#'
#'
rcurrent_gen_data <- function(lst_design, seed = NULL, ...) {

    if (!is.null(seed))
        old_seed <- set.seed(seed)

    ## n by arm
    n_by_arm <- tl_draw_arm_size(sample_size  = lst_design$sample_size,
                                 ratio_by_arm = lst_design$ratio_by_arm)

    ## enrollment
    dat_enroll <- do.call(stb_tl_simu_enroll_arms,
                          list(n_by_arm   = c(n_by_arm),
                               par_enroll = lst_design$par_enroll))

    ## outcome
    ## annual to day hr
    hr_by_arm   <- lst_design$hr_by_arm / 365.25
    k_by_arm    <- lst_design$k_by_arm
    max_n_event <- lst_design$max_n_event
    rst         <- NULL
    for (i in seq_len(length(n_by_arm))) {
        cur_events <- stb_tl_rc_simu_events(n_by_arm[i],
                                            hr_by_arm[i],
                                            k_by_arm[i],
                                            n_event = max_n_event)

        cur_events$arm <- i - 1
        rst            <- rbind(rst, cur_events)
    }

    ## merget data
    rst <- dat_enroll %>%
        left_join(rst, by = c("arm", "sid" = "id")) %>%
        mutate(day_start = day_enroll + start,
               day_end   = day_enroll + end,
               sid       = sid + arm * lst_design$sample_size)


    ## reset
    if (!is.null(seed))
        set.seed(old_seed)

    ## return
    rst
}


#' Generate analysis data set
#'
#' Generate analysis dataset for minimum fu days
#'
rcurrent_day_eos_1 <- function(data_full,
                               min_fu_days   = 12 * 7,
                               pt_proportion = 1) {
    dat <- data_full %>%
        select(arm, sid, day_enroll) %>%
        distinct() %>%
        arrange(day_enroll)

    day_eos <- dat[ceiling(nrow(dat) * pt_proportion), "day_enroll"]
    day_eos <- day_eos + min_fu_days

    data_full %>%
        mutate(day_eos = day_eos)
}

#' Generate analysis data set
#'
#' Generate analysis dataset for fixed fu days
#'
rcurrent_day_eos_2 <- function(data_full, fu_days = 12 * 7, pt_proportion = 1) {
    dat <- data_full %>%
        select(arm, sid, day_enroll) %>%
        distinct() %>%
        mutate(day_eos = day_enroll + fu_days) %>%
        arrange(day_enroll)

    n_pt <- ceiling(nrow(dat) * pt_proportion)
    dat  <- dat[1 : n_pt, ]

    dat %>%
        left_join(data_full %>%
                  select(-day_enroll),
                  by = c("arm", "sid"))
}

#' Generate analysis data set
#'
#' Generate final analysis dataset for 1) stage 1 patients with fixed fu, 2)
#' stage 2 patients with fixed fu, 3) target number of events
#'
#'
rcurrent_day_eos_adapt_1 <- function(data_full, n_stage1, fix_fu = 12 * 7) {

    dat <- data_full %>%
        select(arm, sid, date_enroll) %>%
        distinct() %>%
        arrange(date_enroll)

    date_eos_1 <- dat[n_stage1, "date_enroll"] + 1
    rst        <- data_full %>%
        mutate(date_eos_1 = date_eos_1,
               date_eos_2 = date_enroll + fix_fu,
               date_eos   = if_else(date_eos_1 < date_eos_2,
                                    date_eos_1,
                                    date_eos_2),
               day_eos    = as.numeric(date_eos - date_bos)) %>%
        rcurrent_censor()

    rst
}


#' Generate analysis data set
#'
#' Generate final analysis dataset for 1) stage 1 patients with fixed fu, 2)
#' stage 2 patients with fixed fu, 3) target number of events
#'
#'
rcurrent_day_eos_adapt_2 <- function(data_full,
                                     n_stage1,
                                     n_stage2       = 0,
                                     target_event   = 0,
                                     rcur_weight    = 0.2,
                                     fix_fu         = 12 * 7) {

    dat <- data_full %>%
        select(arm, sid, date_enroll) %>%
        distinct() %>%
        arrange(date_enroll)

    ## stage 1 patients
    dat_stage1 <- dat %>%
        slice(1:n_stage1) %>%
        select(-date_enroll) %>%
        left_join(data_full,
                  by = c("arm" = "arm", "sid" = "sid"))

    ## last stage 1 patient FU finished
    date_eos_1 <- max(dat_stage1$date_enroll) + fix_fu + 1

    if (0 == n_stage2) {
        dat_stage2  <- NULL
        date_eos_12 <- date_eos_1
        reason_eos  <- 0 # no re-estimation
    } else {
        dat_stage2 <- dat %>%
            slice(n_stage1 + (1:n_stage2)) %>%
            select(-date_enroll) %>%
            left_join(data_full,
                      by = c("arm" = "arm",
                             "sid" = "sid"))

        ## target event observed
        dat_target_temp <- dat %>%
            slice(1:(n_stage1 + n_stage2)) %>%
            select(-date_enroll) %>%
            left_join(data_full,
                      by = c("arm" = "arm",
                             "sid" = "sid")) %>%
            mutate(day_eos = day_enroll + fix_fu) %>%
            filter(day_end <= day_eos) %>%
            arrange(day_end) %>%
            mutate(nevent   = case_when(inx == 1 ~ 1,
                                        inx >  1 ~ rcur_weight),
                   cumevent = cumsum(nevent))

        dat_target_filter <- dat_target_temp %>%
            filter(cumevent >= target_event)

        if (0 == nrow(dat_target_filter)) {
            dat_target <- dat_target_temp %>%
                slice_tail(n = 1) %>%
                mutate(date_eos = date_bos + day_end + 1)

            date_eos_2  <- dat_target[1, "date_eos"]
            date_eos_12 <- date_eos_2
            reason_eos  <- 1 # both stages finish fu
        } else {
            dat_target <- dat_target_filter %>%
                slice(1) %>%
                mutate(date_eos = date_bos + day_end + 1)

            date_eos_2 <- dat_target[1, "date_eos"]

            ## make sure stage 1 patients have FU
            date_eos_12 <- max(date_eos_1, date_eos_2)
            reason_eos <- if_else(date_eos_12 == date_eos_1,
                                  2, # stage 1 finishes FU
                                  3) # target no. are reached
        }
    }

    rst <- rbind(dat_stage1, dat_stage2) %>%
        mutate(date_eos_1 = date_eos_12,
               date_eos_2 = date_enroll + fix_fu,
               date_eos   = if_else(date_eos_1 < date_eos_2,
                                    date_eos_1,
                                    date_eos_2),
               day_eos    = as.numeric(date_eos - date_bos)) %>%
        rcurrent_censor()

    ## return
    list(data       = rst,
         reason_eos = reason_eos)
}


#' Generate analysis data set
#'
#' Generate final analysis dataset for all patients with fixed fu
#'
#'
rcurrent_day_eos_adapt_3 <- function(data_full, n, fix_fu = 12 * 7) {

    dat <- data_full %>%
        select(arm, sid, date_enroll) %>%
        distinct() %>%
        arrange(date_enroll) %>%
        slice(1:n) %>%
        select(-date_enroll) %>%
        left_join(data_full,
                  by = c("arm" = "arm", "sid" = "sid"))

    rst <- dat %>%
        mutate(date_eos = date_enroll + fix_fu,
               day_eos  = as.numeric(date_eos - date_bos)) %>%
        rcurrent_censor()

    rst
}


#' Generate censoring data
#'
#'
rcurrent_censor <- function(data_full) {
    data_full %>%
        filter(day_start <= day_eos) %>%
        mutate(censor  = if_else(day_end <= day_eos, 0, 1),
               day_end = if_else(day_end <= day_eos, day_end, day_eos),
               time    = day_end - day_start)
}

#' Generate NB data
#'
#'
rcurrent_get_nb <- function(data_full) {
    n_arm <- max(data_full$arm)
    rst   <- NULL
    for (i in 0:n_arm) {
        cur_arm   <- data_full %>%
            filter(i == arm)

        cur_count <- cur_arm %>%
            group_by(arm, sid) %>%
            summarize(y = n() - 1)

        cur_rst <- cur_count %>%
            left_join(data_full %>%
                      select(sid, arm, lambda, day_enroll, day_eos) %>%
                      distinct(),
                      by = c("arm", "sid")) %>%
            mutate(day_onstudy = day_eos - day_enroll)

        rst <- rbind(rst, cur_rst)
    }

    rst
}

#' Calculate NB sample size based on survival analysis
#'
#' Calculate NB sample size based on logrank power and sample size calculation
#'
#' @param r0 hazard rate in control
#' @param r1 hazard rate in treatment
#' @param fu average follow up time on each pt
#' @param rcur_weight information weight on recurrent events
#'
#'
rcurrent_logrank_size <- function(r0, r1, fix_fu,
                                  power       = 0.9,
                                  rcur_weight = 0.2,
                                  k           = 1,
                                  alpha       = 0.05) {

    z_alpha <- qnorm(1 - alpha / 2)
    z_beta  <- qnorm(power)

    ## total No. of events from logrank test
    m <- ceiling(4 * (z_alpha + z_beta)^2 / (log(r1 / r0))^2)

    ## calculate sample size per group
    eys_0 <- rcur_eff_event(r0 * fix_fu, k, rcur_weight)
    eys_1 <- rcur_eff_event(r1 * fix_fu, k, rcur_weight)
    n     <- ceiling(m / (eys_0 + eys_1))

    c(n_events = m,
      n_pts    = n * 2,
      eys_0    = eys_0,
      eys_1    = eys_1)
}


#' Rcurrent adaptive design
#'
#'
#' @export
#'
rcurrent_adapt_ana_set <- function(data, lst_design) {

    ## design parameters
    hr          <- lst_design$hr_by_arm
    fix_fu      <- lst_design$fix_fu
    n_stage1    <- lst_design$n_stage1
    alpha       <- lst_design$alpha
    power       <- lst_design$power
    k           <- lst_design$k_by_arm[1]
    ssr_zone    <- lst_design$ssr_zone
    rcur_weight <- lst_design$rcur_weight
    hr          <- hr[2] / hr[1]

    ## interim when all n_stage1 pts have been enrolled
    data_interim <- rcurrent_day_eos_adapt_1(data,
                                             n_stage1 = n_stage1,
                                             fix_fu   = fix_fu)

    data_interim_nb <- rcurrent_get_nb(data_interim)

    ## sample size re_estimated
    inter_rst  <- stb_tl_rc_pooled(data_interim_nb, hr = hr)
    smp_size   <- rcurrent_logrank_size(
        r0          = inter_rst$r0,
        r1          = inter_rst$r1,
        fix_fu      = fix_fu,
        power       = power,
        rcur_weight = rcur_weight,
        k           = k,
        alpha       = alpha)

    target_event <- smp_size["n_events"]
    re_est_size  <- smp_size["n_pts"]

    ss_r <- re_est_size / n_stage1
    if (ss_r < ssr_zone[1] |
        ss_r > ssr_zone[2]) {
        n_stage2        <- 0
        reason_no_reest <- ifelse(ss_r < ssr_zone[1],
                                  1, # due to low ss
                                  2) # due to high ss
    } else {
        n_stage2        <- re_est_size - n_stage1
        reason_no_reest <- 0 # re-estimate
    }

    inter_rst <- inter_rst %>%
        mutate(n_stage2      = n_stage2,
               target_event  = target_event) %>%
        rename(inter_roverall = r_overall,
               inter_r0       = r0,
               inter_r1       = r1,
               inter_k        = k)

    ## final analysis dataset
    data_final <- rcurrent_day_eos_adapt_2(
        data,
        n_stage1       = n_stage1,
        n_stage2       = n_stage2,
        target_event   = target_event,
        rcur_weight    = rcur_weight,
        fix_fu         = fix_fu)

    data_final_nb <- rcurrent_get_nb(data_final$data)

    ## return
    list(data            = data,
         interim_rst     = inter_rst,
         data_interim    = data_interim,
         data_interim_nb = data_interim_nb,
         data_final      = data_final$data,
         data_final_nb   = data_final_nb,
         reason_eos      = data_final$reason_eos,
         reason_no_reest = reason_no_reest)
}


#' Rcurrent sample size re-estimation
#'
#' This is based on a naive NB sample size re-estimation
#'
#' @export
#'
rcurrent_ssr_ana_set <- function(data, lst_design) {

    ## design parameters
    hr          <- lst_design$hr_by_arm
    fix_fu      <- lst_design$fix_fu
    n_stage1    <- lst_design$n_stage1
    alpha       <- lst_design$alpha
    power       <- lst_design$power
    k           <- lst_design$k_by_arm[1]
    method      <- lst_design$method_samplesize
    ssr_zone    <- lst_design$ssr_zone
    hr          <- hr[2] / hr[1]

    ## interim when all n_stage1 pts have been enrolled
    data_interim <- rcurrent_day_eos_adapt_1(data,
                                             n_stage1 = n_stage1,
                                             fix_fu   = fix_fu)

    data_interim_nb <- rcurrent_get_nb(data_interim)

    ## sample size re_estimated
    inter_rst   <- stb_tl_rc_pooled(data_interim_nb, hr = hr)
    re_est_size <- stb_tl_rc_size(power  = power,
                                  mu_t   = fix_fu,
                                  r0     = inter_rst$r0,
                                  r1     = inter_rst$r1,
                                  k      = k,
                                  alpha  = alpha,
                                  method = method)

    ss_r <- re_est_size / n_stage1
    if (ss_r < ssr_zone[1] |
        ss_r > ssr_zone[2]) {
        n_stage2        <- 0
        reason_no_reest <- ifelse(ss_r < ssr_zone[1],
                                  1, # due to low ss
                                  2) # due to high ss
    } else {
        n_stage2        <- re_est_size - n_stage1
        reason_no_reest <- 0 # re-estimate
    }

    inter_rst <- inter_rst %>%
        mutate(n_stage2       = n_stage2,
               target_event   = NA) %>%
        rename(inter_roverall = r_overall,
               inter_r0       = r0,
               inter_r1       = r1,
               inter_k        = k)

    ## final analysis dataset
    data_final <- rcurrent_day_eos_adapt_3(data,
                                           n_stage1 + n_stage2,
                                           fix_fu = fix_fu)

    data_final_nb <- rcurrent_get_nb(data_final)

    ## return
    list(data            = data,
         interim_rst     = inter_rst,
         data_interim    = data_interim,
         data_interim_nb = data_interim_nb,
         data_final      = data_final,
         data_final_nb   = data_final_nb,
         reason_eos      = NA,
         reason_no_reest = reason_no_reest)
}


#' Effective number of events
#'
#' Calculate effective number of events for recurrent events
#'
#' @export
#'
rcur_eff_event <- function(nb_mu, nb_k, weight = 0.2) {
    eys <- weight * nb_mu +
        (1 - weight) * (1 - dnbinom(0, size = nb_k, mu = nb_mu))

    eys
}

#' Effective number of events
#'
#' Calculate effective number of events for recurrent events
#'
#' @export
#'
rcur_eff_event_dta <- function(dta, weight = 0.2) {
    rst <- dta %>%
        mutate(n_event = case_when(
                   censor == 1 ~ 0,
                   censor == 0 & inx == 1 ~ 1,
                   censor == 0 & inx > 1  ~ weight)) %>%
        group_by(arm, sid) %>%
        summarize(n_event        = sum(n_event),
                  n_1st_event    = sum(censor == 0 & inx == 1),
                  n_ge_2nd_event = sum(censor == 0 & inx > 1)) %>%
        group_by(arm) %>%
        summarize(total_event        = sum(n_event),
                  total_1st_event    = sum(n_1st_event),
                  total_ge_2nd_event = sum(n_ge_2nd_event),
                  event_rate         = mean(n_event),
                  event_rate_1st     = mean(n_1st_event),
                  event_rate_ge_2nd  = mean(n_ge_2nd_event))

    c(unlist(rst$total_event),
      unlist(rst$total_1st_event),
      unlist(rst$total_ge_2nd_event),
      unlist(rst$event_rate),
      unlist(rst$event_rate_1st),
      unlist(rst$event_rate_ge_2nd))
}

#' Final analysis
#'
#' Final analysis
#'
#' @export
#'
rcurrent_adapt_ana <- function(data_ana, lst_design) {
    dat_final    <- data_ana$data_final
    dat_final_nb <- data_ana$data_final_nb
    rst          <- stb_tl_rc_reg(dat_final_nb)

    ## effective number of events
    eff_nevent   <- rcur_eff_event_dta(dat_final,
                                       weight = lst_design$rcur_weight)

    ## sample size and duration
    rst$study_n   <- length(unique(dat_final$sid))
    rst$study_dur <- max(dat_final$date_eos) - min(dat_final$date_bos)

    rst$event_ctl             <- eff_nevent[1]
    rst$event_trt             <- eff_nevent[2]
    rst$event_1st_ctl         <- eff_nevent[3]
    rst$event_1st_trt         <- eff_nevent[4]
    rst$event_ge_2nd_ctl      <- eff_nevent[5]
    rst$event_ge_2nd_trt      <- eff_nevent[6]
    rst$event_total           <- sum(eff_nevent[1:2])
    rst$event_1st_total       <- sum(eff_nevent[3:4])
    rst$event_ge_2nd_total    <- sum(eff_nevent[5:6])
    rst$event_rate_ctl        <- eff_nevent[7]
    rst$event_rate_trt        <- eff_nevent[8]
    rst$event_rate_1st_ctl    <- eff_nevent[9]
    rst$event_rate_1st_trt    <- eff_nevent[10]
    rst$event_rate_ge_2nd_ctl <- eff_nevent[11]
    rst$event_rate_ge_2nd_trt <- eff_nevent[12]
    rst$reason_eos            <- data_ana$reason_eos
    rst$reason_no_reest       <- data_ana$reason_no_reest


    ## return
    rst <- cbind(data_ana$interim_rst,
                 rst)
}
