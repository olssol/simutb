// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppEigen.h>
#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// c_test
double c_test(double test);
RcppExport SEXP _simutb_c_test(SEXP testSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type test(testSEXP);
    rcpp_result_gen = Rcpp::wrap(c_test(test));
    return rcpp_result_gen;
END_RCPP
}

RcppExport SEXP _rcpp_module_boot_stan_fit4fix_ind_mod();
RcppExport SEXP _rcpp_module_boot_stan_fit4fix_mono_mod();
RcppExport SEXP _rcpp_module_boot_stan_fit4fix_samecv_mod();

static const R_CallMethodDef CallEntries[] = {
    {"_simutb_c_test", (DL_FUNC) &_simutb_c_test, 1},
    {"_rcpp_module_boot_stan_fit4fix_ind_mod", (DL_FUNC) &_rcpp_module_boot_stan_fit4fix_ind_mod, 0},
    {"_rcpp_module_boot_stan_fit4fix_mono_mod", (DL_FUNC) &_rcpp_module_boot_stan_fit4fix_mono_mod, 0},
    {"_rcpp_module_boot_stan_fit4fix_samecv_mod", (DL_FUNC) &_rcpp_module_boot_stan_fit4fix_samecv_mod, 0},
    {NULL, NULL, 0}
};

void my_package_init(DllInfo *dll);
RcppExport void R_init_simutb(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
    my_package_init(dll);
}
