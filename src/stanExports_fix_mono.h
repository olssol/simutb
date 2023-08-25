// Generated by rstantools.  Do not edit by hand.

/*
    test is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    test is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with test.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef MODELS_HPP
#define MODELS_HPP
#define STAN__SERVICES__COMMAND_HPP
#include <rstan/rstaninc.hpp>
// Code generated by Stan version 2.21.0
#include <stan/model/model_header.hpp>
namespace model_fix_mono_namespace {
using std::istream;
using std::string;
using std::stringstream;
using std::vector;
using stan::io::dump;
using stan::math::lgamma;
using stan::model::prob_grad;
using namespace stan::math;
static int current_statement_begin__;
stan::io::program_reader prog_reader__() {
    stan::io::program_reader reader;
    reader.add_event(0, 0, "start", "model_fix_mono");
    reader.add_event(56, 54, "end", "model_fix_mono");
    return reader;
}
#include <stan_meta_header.hpp>
class model_fix_mono
  : public stan::model::model_base_crtp<model_fix_mono> {
private:
        int N;
        int n_dose;
        vector_d y;
        std::vector<int> DL;
        double L_m;
        double U_m;
        double L_m_inc;
        double U_m_inc;
        double L_cv;
        double U_cv;
public:
    model_fix_mono(stan::io::var_context& context__,
        std::ostream* pstream__ = 0)
        : model_base_crtp(0) {
        ctor_body(context__, 0, pstream__);
    }
    model_fix_mono(stan::io::var_context& context__,
        unsigned int random_seed__,
        std::ostream* pstream__ = 0)
        : model_base_crtp(0) {
        ctor_body(context__, random_seed__, pstream__);
    }
    void ctor_body(stan::io::var_context& context__,
                   unsigned int random_seed__,
                   std::ostream* pstream__) {
        typedef double local_scalar_t__;
        boost::ecuyer1988 base_rng__ =
          stan::services::util::create_rng(random_seed__, 0);
        (void) base_rng__;  // suppress unused var warning
        current_statement_begin__ = -1;
        static const char* function__ = "model_fix_mono_namespace::model_fix_mono";
        (void) function__;  // dummy to suppress unused var warning
        size_t pos__;
        (void) pos__;  // dummy to suppress unused var warning
        std::vector<int> vals_i__;
        std::vector<double> vals_r__;
        local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // suppress unused var warning
        try {
            // initialize data block variables from context__
            current_statement_begin__ = 2;
            context__.validate_dims("data initialization", "N", "int", context__.to_vec());
            N = int(0);
            vals_i__ = context__.vals_i("N");
            pos__ = 0;
            N = vals_i__[pos__++];
            check_greater_or_equal(function__, "N", N, 0);
            current_statement_begin__ = 3;
            context__.validate_dims("data initialization", "n_dose", "int", context__.to_vec());
            n_dose = int(0);
            vals_i__ = context__.vals_i("n_dose");
            pos__ = 0;
            n_dose = vals_i__[pos__++];
            check_greater_or_equal(function__, "n_dose", n_dose, 0);
            current_statement_begin__ = 4;
            validate_non_negative_index("y", "N", N);
            context__.validate_dims("data initialization", "y", "vector_d", context__.to_vec(N));
            y = Eigen::Matrix<double, Eigen::Dynamic, 1>(N);
            vals_r__ = context__.vals_r("y");
            pos__ = 0;
            size_t y_j_1_max__ = N;
            for (size_t j_1__ = 0; j_1__ < y_j_1_max__; ++j_1__) {
                y(j_1__) = vals_r__[pos__++];
            }
            check_greater_or_equal(function__, "y", y, 0);
            current_statement_begin__ = 5;
            validate_non_negative_index("DL", "N", N);
            context__.validate_dims("data initialization", "DL", "int", context__.to_vec(N));
            DL = std::vector<int>(N, int(0));
            vals_i__ = context__.vals_i("DL");
            pos__ = 0;
            size_t DL_k_0_max__ = N;
            for (size_t k_0__ = 0; k_0__ < DL_k_0_max__; ++k_0__) {
                DL[k_0__] = vals_i__[pos__++];
            }
            size_t DL_i_0_max__ = N;
            for (size_t i_0__ = 0; i_0__ < DL_i_0_max__; ++i_0__) {
                check_greater_or_equal(function__, "DL[i_0__]", DL[i_0__], 0);
            }
            current_statement_begin__ = 6;
            context__.validate_dims("data initialization", "L_m", "double", context__.to_vec());
            L_m = double(0);
            vals_r__ = context__.vals_r("L_m");
            pos__ = 0;
            L_m = vals_r__[pos__++];
            check_greater_or_equal(function__, "L_m", L_m, 0);
            current_statement_begin__ = 7;
            context__.validate_dims("data initialization", "U_m", "double", context__.to_vec());
            U_m = double(0);
            vals_r__ = context__.vals_r("U_m");
            pos__ = 0;
            U_m = vals_r__[pos__++];
            check_greater_or_equal(function__, "U_m", U_m, 0);
            current_statement_begin__ = 8;
            context__.validate_dims("data initialization", "L_m_inc", "double", context__.to_vec());
            L_m_inc = double(0);
            vals_r__ = context__.vals_r("L_m_inc");
            pos__ = 0;
            L_m_inc = vals_r__[pos__++];
            check_greater_or_equal(function__, "L_m_inc", L_m_inc, 0);
            current_statement_begin__ = 9;
            context__.validate_dims("data initialization", "U_m_inc", "double", context__.to_vec());
            U_m_inc = double(0);
            vals_r__ = context__.vals_r("U_m_inc");
            pos__ = 0;
            U_m_inc = vals_r__[pos__++];
            check_greater_or_equal(function__, "U_m_inc", U_m_inc, 0);
            current_statement_begin__ = 10;
            context__.validate_dims("data initialization", "L_cv", "double", context__.to_vec());
            L_cv = double(0);
            vals_r__ = context__.vals_r("L_cv");
            pos__ = 0;
            L_cv = vals_r__[pos__++];
            check_greater_or_equal(function__, "L_cv", L_cv, 0);
            current_statement_begin__ = 11;
            context__.validate_dims("data initialization", "U_cv", "double", context__.to_vec());
            U_cv = double(0);
            vals_r__ = context__.vals_r("U_cv");
            pos__ = 0;
            U_cv = vals_r__[pos__++];
            check_greater_or_equal(function__, "U_cv", U_cv, 0);
            // initialize transformed data variables
            // execute transformed data statements
            // validate transformed data
            // validate, set parameter ranges
            num_params_r__ = 0U;
            param_ranges_i__.clear();
            current_statement_begin__ = 15;
            num_params_r__ += 1;
            current_statement_begin__ = 16;
            validate_non_negative_index("alpha", "(n_dose - 1)", (n_dose - 1));
            num_params_r__ += (n_dose - 1);
            current_statement_begin__ = 17;
            num_params_r__ += 1;
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(e, current_statement_begin__, prog_reader__());
            // Next line prevents compiler griping about no return
            throw std::runtime_error("*** IF YOU SEE THIS, PLEASE REPORT A BUG ***");
        }
    }
    ~model_fix_mono() { }
    void transform_inits(const stan::io::var_context& context__,
                         std::vector<int>& params_i__,
                         std::vector<double>& params_r__,
                         std::ostream* pstream__) const {
        typedef double local_scalar_t__;
        stan::io::writer<double> writer__(params_r__, params_i__);
        size_t pos__;
        (void) pos__; // dummy call to supress warning
        std::vector<double> vals_r__;
        std::vector<int> vals_i__;
        current_statement_begin__ = 15;
        if (!(context__.contains_r("alpha1")))
            stan::lang::rethrow_located(std::runtime_error(std::string("Variable alpha1 missing")), current_statement_begin__, prog_reader__());
        vals_r__ = context__.vals_r("alpha1");
        pos__ = 0U;
        context__.validate_dims("parameter initialization", "alpha1", "double", context__.to_vec());
        double alpha1(0);
        alpha1 = vals_r__[pos__++];
        try {
            writer__.scalar_lub_unconstrain(L_m, U_m, alpha1);
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(std::runtime_error(std::string("Error transforming variable alpha1: ") + e.what()), current_statement_begin__, prog_reader__());
        }
        current_statement_begin__ = 16;
        if (!(context__.contains_r("alpha")))
            stan::lang::rethrow_located(std::runtime_error(std::string("Variable alpha missing")), current_statement_begin__, prog_reader__());
        vals_r__ = context__.vals_r("alpha");
        pos__ = 0U;
        validate_non_negative_index("alpha", "(n_dose - 1)", (n_dose - 1));
        context__.validate_dims("parameter initialization", "alpha", "vector_d", context__.to_vec((n_dose - 1)));
        Eigen::Matrix<double, Eigen::Dynamic, 1> alpha((n_dose - 1));
        size_t alpha_j_1_max__ = (n_dose - 1);
        for (size_t j_1__ = 0; j_1__ < alpha_j_1_max__; ++j_1__) {
            alpha(j_1__) = vals_r__[pos__++];
        }
        try {
            writer__.vector_lub_unconstrain(L_m_inc, U_m_inc, alpha);
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(std::runtime_error(std::string("Error transforming variable alpha: ") + e.what()), current_statement_begin__, prog_reader__());
        }
        current_statement_begin__ = 17;
        if (!(context__.contains_r("cv")))
            stan::lang::rethrow_located(std::runtime_error(std::string("Variable cv missing")), current_statement_begin__, prog_reader__());
        vals_r__ = context__.vals_r("cv");
        pos__ = 0U;
        context__.validate_dims("parameter initialization", "cv", "double", context__.to_vec());
        double cv(0);
        cv = vals_r__[pos__++];
        try {
            writer__.scalar_lub_unconstrain(L_cv, U_cv, cv);
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(std::runtime_error(std::string("Error transforming variable cv: ") + e.what()), current_statement_begin__, prog_reader__());
        }
        params_r__ = writer__.data_r();
        params_i__ = writer__.data_i();
    }
    void transform_inits(const stan::io::var_context& context,
                         Eigen::Matrix<double, Eigen::Dynamic, 1>& params_r,
                         std::ostream* pstream__) const {
      std::vector<double> params_r_vec;
      std::vector<int> params_i_vec;
      transform_inits(context, params_i_vec, params_r_vec, pstream__);
      params_r.resize(params_r_vec.size());
      for (int i = 0; i < params_r.size(); ++i)
        params_r(i) = params_r_vec[i];
    }
    template <bool propto__, bool jacobian__, typename T__>
    T__ log_prob(std::vector<T__>& params_r__,
                 std::vector<int>& params_i__,
                 std::ostream* pstream__ = 0) const {
        typedef T__ local_scalar_t__;
        local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // dummy to suppress unused var warning
        T__ lp__(0.0);
        stan::math::accumulator<T__> lp_accum__;
        try {
            stan::io::reader<local_scalar_t__> in__(params_r__, params_i__);
            // model parameters
            current_statement_begin__ = 15;
            local_scalar_t__ alpha1;
            (void) alpha1;  // dummy to suppress unused var warning
            if (jacobian__)
                alpha1 = in__.scalar_lub_constrain(L_m, U_m, lp__);
            else
                alpha1 = in__.scalar_lub_constrain(L_m, U_m);
            current_statement_begin__ = 16;
            Eigen::Matrix<local_scalar_t__, Eigen::Dynamic, 1> alpha;
            (void) alpha;  // dummy to suppress unused var warning
            if (jacobian__)
                alpha = in__.vector_lub_constrain(L_m_inc, U_m_inc, (n_dose - 1), lp__);
            else
                alpha = in__.vector_lub_constrain(L_m_inc, U_m_inc, (n_dose - 1));
            current_statement_begin__ = 17;
            local_scalar_t__ cv;
            (void) cv;  // dummy to suppress unused var warning
            if (jacobian__)
                cv = in__.scalar_lub_constrain(L_cv, U_cv, lp__);
            else
                cv = in__.scalar_lub_constrain(L_cv, U_cv);
            // transformed parameters
            current_statement_begin__ = 21;
            validate_non_negative_index("m", "n_dose", n_dose);
            Eigen::Matrix<local_scalar_t__, Eigen::Dynamic, 1> m(n_dose);
            stan::math::initialize(m, DUMMY_VAR__);
            stan::math::fill(m, DUMMY_VAR__);
            current_statement_begin__ = 22;
            validate_non_negative_index("mu", "n_dose", n_dose);
            Eigen::Matrix<local_scalar_t__, Eigen::Dynamic, 1> mu(n_dose);
            stan::math::initialize(mu, DUMMY_VAR__);
            stan::math::fill(mu, DUMMY_VAR__);
            current_statement_begin__ = 23;
            local_scalar_t__ sigma;
            (void) sigma;  // dummy to suppress unused var warning
            stan::math::initialize(sigma, DUMMY_VAR__);
            stan::math::fill(sigma, DUMMY_VAR__);
            // transformed parameters block statements
            current_statement_begin__ = 25;
            stan::model::assign(m, 
                        stan::model::cons_list(stan::model::index_uni(1), stan::model::nil_index_list()), 
                        alpha1, 
                        "assigning variable m");
            current_statement_begin__ = 26;
            for (int j = 2; j <= n_dose; ++j) {
                current_statement_begin__ = 27;
                stan::model::assign(m, 
                            stan::model::cons_list(stan::model::index_uni(j), stan::model::nil_index_list()), 
                            (get_base1(m, (j - 1), "m", 1) + get_base1(alpha, (j - 1), "alpha", 1)), 
                            "assigning variable m");
            }
            current_statement_begin__ = 30;
            for (int j = 1; j <= n_dose; ++j) {
                current_statement_begin__ = 31;
                stan::model::assign(mu, 
                            stan::model::cons_list(stan::model::index_uni(j), stan::model::nil_index_list()), 
                            stan::math::log((get_base1(m, j, "m", 1) / stan::math::sqrt((1 + pow(cv, 2))))), 
                            "assigning variable mu");
            }
            current_statement_begin__ = 33;
            stan::math::assign(sigma, stan::math::sqrt(stan::math::log((1 + pow(cv, 2)))));
            // validate transformed parameters
            const char* function__ = "validate transformed params";
            (void) function__;  // dummy to suppress unused var warning
            current_statement_begin__ = 21;
            size_t m_j_1_max__ = n_dose;
            for (size_t j_1__ = 0; j_1__ < m_j_1_max__; ++j_1__) {
                if (stan::math::is_uninitialized(m(j_1__))) {
                    std::stringstream msg__;
                    msg__ << "Undefined transformed parameter: m" << "(" << j_1__ << ")";
                    stan::lang::rethrow_located(std::runtime_error(std::string("Error initializing variable m: ") + msg__.str()), current_statement_begin__, prog_reader__());
                }
            }
            check_greater_or_equal(function__, "m", m, L_m);
            check_less_or_equal(function__, "m", m, U_m);
            current_statement_begin__ = 22;
            size_t mu_j_1_max__ = n_dose;
            for (size_t j_1__ = 0; j_1__ < mu_j_1_max__; ++j_1__) {
                if (stan::math::is_uninitialized(mu(j_1__))) {
                    std::stringstream msg__;
                    msg__ << "Undefined transformed parameter: mu" << "(" << j_1__ << ")";
                    stan::lang::rethrow_located(std::runtime_error(std::string("Error initializing variable mu: ") + msg__.str()), current_statement_begin__, prog_reader__());
                }
            }
            current_statement_begin__ = 23;
            if (stan::math::is_uninitialized(sigma)) {
                std::stringstream msg__;
                msg__ << "Undefined transformed parameter: sigma";
                stan::lang::rethrow_located(std::runtime_error(std::string("Error initializing variable sigma: ") + msg__.str()), current_statement_begin__, prog_reader__());
            }
            check_greater_or_equal(function__, "sigma", sigma, 0);
            // model body
            current_statement_begin__ = 37;
            lp_accum__.add(uniform_log<propto__>(cv, L_cv, U_cv));
            current_statement_begin__ = 38;
            lp_accum__.add(uniform_log<propto__>(alpha1, L_m, U_m));
            current_statement_begin__ = 39;
            lp_accum__.add(uniform_log<propto__>(alpha, L_m_inc, U_m_inc));
            current_statement_begin__ = 41;
            for (int i = 1; i <= N; ++i) {
                current_statement_begin__ = 42;
                lp_accum__.add(normal_log<propto__>(stan::math::log(get_base1(y, i, "y", 1)), get_base1(mu, get_base1(DL, i, "DL", 1), "mu", 1), sigma));
            }
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(e, current_statement_begin__, prog_reader__());
            // Next line prevents compiler griping about no return
            throw std::runtime_error("*** IF YOU SEE THIS, PLEASE REPORT A BUG ***");
        }
        lp_accum__.add(lp__);
        return lp_accum__.sum();
    } // log_prob()
    template <bool propto, bool jacobian, typename T_>
    T_ log_prob(Eigen::Matrix<T_,Eigen::Dynamic,1>& params_r,
               std::ostream* pstream = 0) const {
      std::vector<T_> vec_params_r;
      vec_params_r.reserve(params_r.size());
      for (int i = 0; i < params_r.size(); ++i)
        vec_params_r.push_back(params_r(i));
      std::vector<int> vec_params_i;
      return log_prob<propto,jacobian,T_>(vec_params_r, vec_params_i, pstream);
    }
    void get_param_names(std::vector<std::string>& names__) const {
        names__.resize(0);
        names__.push_back("alpha1");
        names__.push_back("alpha");
        names__.push_back("cv");
        names__.push_back("m");
        names__.push_back("mu");
        names__.push_back("sigma");
        names__.push_back("x_tilde");
        names__.push_back("y_tilde");
    }
    void get_dims(std::vector<std::vector<size_t> >& dimss__) const {
        dimss__.resize(0);
        std::vector<size_t> dims__;
        dims__.resize(0);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dims__.push_back((n_dose - 1));
        dimss__.push_back(dims__);
        dims__.resize(0);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dims__.push_back(n_dose);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dims__.push_back(n_dose);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dims__.push_back(n_dose);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dims__.push_back(n_dose);
        dimss__.push_back(dims__);
    }
    template <typename RNG>
    void write_array(RNG& base_rng__,
                     std::vector<double>& params_r__,
                     std::vector<int>& params_i__,
                     std::vector<double>& vars__,
                     bool include_tparams__ = true,
                     bool include_gqs__ = true,
                     std::ostream* pstream__ = 0) const {
        typedef double local_scalar_t__;
        vars__.resize(0);
        stan::io::reader<local_scalar_t__> in__(params_r__, params_i__);
        static const char* function__ = "model_fix_mono_namespace::write_array";
        (void) function__;  // dummy to suppress unused var warning
        // read-transform, write parameters
        double alpha1 = in__.scalar_lub_constrain(L_m, U_m);
        vars__.push_back(alpha1);
        Eigen::Matrix<double, Eigen::Dynamic, 1> alpha = in__.vector_lub_constrain(L_m_inc, U_m_inc, (n_dose - 1));
        size_t alpha_j_1_max__ = (n_dose - 1);
        for (size_t j_1__ = 0; j_1__ < alpha_j_1_max__; ++j_1__) {
            vars__.push_back(alpha(j_1__));
        }
        double cv = in__.scalar_lub_constrain(L_cv, U_cv);
        vars__.push_back(cv);
        double lp__ = 0.0;
        (void) lp__;  // dummy to suppress unused var warning
        stan::math::accumulator<double> lp_accum__;
        local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // suppress unused var warning
        if (!include_tparams__ && !include_gqs__) return;
        try {
            // declare and define transformed parameters
            current_statement_begin__ = 21;
            validate_non_negative_index("m", "n_dose", n_dose);
            Eigen::Matrix<double, Eigen::Dynamic, 1> m(n_dose);
            stan::math::initialize(m, DUMMY_VAR__);
            stan::math::fill(m, DUMMY_VAR__);
            current_statement_begin__ = 22;
            validate_non_negative_index("mu", "n_dose", n_dose);
            Eigen::Matrix<double, Eigen::Dynamic, 1> mu(n_dose);
            stan::math::initialize(mu, DUMMY_VAR__);
            stan::math::fill(mu, DUMMY_VAR__);
            current_statement_begin__ = 23;
            double sigma;
            (void) sigma;  // dummy to suppress unused var warning
            stan::math::initialize(sigma, DUMMY_VAR__);
            stan::math::fill(sigma, DUMMY_VAR__);
            // do transformed parameters statements
            current_statement_begin__ = 25;
            stan::model::assign(m, 
                        stan::model::cons_list(stan::model::index_uni(1), stan::model::nil_index_list()), 
                        alpha1, 
                        "assigning variable m");
            current_statement_begin__ = 26;
            for (int j = 2; j <= n_dose; ++j) {
                current_statement_begin__ = 27;
                stan::model::assign(m, 
                            stan::model::cons_list(stan::model::index_uni(j), stan::model::nil_index_list()), 
                            (get_base1(m, (j - 1), "m", 1) + get_base1(alpha, (j - 1), "alpha", 1)), 
                            "assigning variable m");
            }
            current_statement_begin__ = 30;
            for (int j = 1; j <= n_dose; ++j) {
                current_statement_begin__ = 31;
                stan::model::assign(mu, 
                            stan::model::cons_list(stan::model::index_uni(j), stan::model::nil_index_list()), 
                            stan::math::log((get_base1(m, j, "m", 1) / stan::math::sqrt((1 + pow(cv, 2))))), 
                            "assigning variable mu");
            }
            current_statement_begin__ = 33;
            stan::math::assign(sigma, stan::math::sqrt(stan::math::log((1 + pow(cv, 2)))));
            if (!include_gqs__ && !include_tparams__) return;
            // validate transformed parameters
            const char* function__ = "validate transformed params";
            (void) function__;  // dummy to suppress unused var warning
            current_statement_begin__ = 21;
            check_greater_or_equal(function__, "m", m, L_m);
            check_less_or_equal(function__, "m", m, U_m);
            current_statement_begin__ = 23;
            check_greater_or_equal(function__, "sigma", sigma, 0);
            // write transformed parameters
            if (include_tparams__) {
                size_t m_j_1_max__ = n_dose;
                for (size_t j_1__ = 0; j_1__ < m_j_1_max__; ++j_1__) {
                    vars__.push_back(m(j_1__));
                }
                size_t mu_j_1_max__ = n_dose;
                for (size_t j_1__ = 0; j_1__ < mu_j_1_max__; ++j_1__) {
                    vars__.push_back(mu(j_1__));
                }
                vars__.push_back(sigma);
            }
            if (!include_gqs__) return;
            // declare and define generated quantities
            current_statement_begin__ = 47;
            validate_non_negative_index("x_tilde", "n_dose", n_dose);
            Eigen::Matrix<double, Eigen::Dynamic, 1> x_tilde(n_dose);
            stan::math::initialize(x_tilde, DUMMY_VAR__);
            stan::math::fill(x_tilde, DUMMY_VAR__);
            current_statement_begin__ = 48;
            validate_non_negative_index("y_tilde", "n_dose", n_dose);
            Eigen::Matrix<double, Eigen::Dynamic, 1> y_tilde(n_dose);
            stan::math::initialize(y_tilde, DUMMY_VAR__);
            stan::math::fill(y_tilde, DUMMY_VAR__);
            // generated quantities statements
            current_statement_begin__ = 50;
            for (int j = 1; j <= n_dose; ++j) {
                current_statement_begin__ = 51;
                stan::model::assign(x_tilde, 
                            stan::model::cons_list(stan::model::index_uni(j), stan::model::nil_index_list()), 
                            normal_rng(get_base1(mu, j, "mu", 1), sigma, base_rng__), 
                            "assigning variable x_tilde");
                current_statement_begin__ = 52;
                stan::model::assign(y_tilde, 
                            stan::model::cons_list(stan::model::index_uni(j), stan::model::nil_index_list()), 
                            stan::math::exp(get_base1(x_tilde, j, "x_tilde", 1)), 
                            "assigning variable y_tilde");
            }
            // validate, write generated quantities
            current_statement_begin__ = 47;
            size_t x_tilde_j_1_max__ = n_dose;
            for (size_t j_1__ = 0; j_1__ < x_tilde_j_1_max__; ++j_1__) {
                vars__.push_back(x_tilde(j_1__));
            }
            current_statement_begin__ = 48;
            check_greater_or_equal(function__, "y_tilde", y_tilde, 0);
            size_t y_tilde_j_1_max__ = n_dose;
            for (size_t j_1__ = 0; j_1__ < y_tilde_j_1_max__; ++j_1__) {
                vars__.push_back(y_tilde(j_1__));
            }
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(e, current_statement_begin__, prog_reader__());
            // Next line prevents compiler griping about no return
            throw std::runtime_error("*** IF YOU SEE THIS, PLEASE REPORT A BUG ***");
        }
    }
    template <typename RNG>
    void write_array(RNG& base_rng,
                     Eigen::Matrix<double,Eigen::Dynamic,1>& params_r,
                     Eigen::Matrix<double,Eigen::Dynamic,1>& vars,
                     bool include_tparams = true,
                     bool include_gqs = true,
                     std::ostream* pstream = 0) const {
      std::vector<double> params_r_vec(params_r.size());
      for (int i = 0; i < params_r.size(); ++i)
        params_r_vec[i] = params_r(i);
      std::vector<double> vars_vec;
      std::vector<int> params_i_vec;
      write_array(base_rng, params_r_vec, params_i_vec, vars_vec, include_tparams, include_gqs, pstream);
      vars.resize(vars_vec.size());
      for (int i = 0; i < vars.size(); ++i)
        vars(i) = vars_vec[i];
    }
    std::string model_name() const {
        return "model_fix_mono";
    }
    void constrained_param_names(std::vector<std::string>& param_names__,
                                 bool include_tparams__ = true,
                                 bool include_gqs__ = true) const {
        std::stringstream param_name_stream__;
        param_name_stream__.str(std::string());
        param_name_stream__ << "alpha1";
        param_names__.push_back(param_name_stream__.str());
        size_t alpha_j_1_max__ = (n_dose - 1);
        for (size_t j_1__ = 0; j_1__ < alpha_j_1_max__; ++j_1__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "alpha" << '.' << j_1__ + 1;
            param_names__.push_back(param_name_stream__.str());
        }
        param_name_stream__.str(std::string());
        param_name_stream__ << "cv";
        param_names__.push_back(param_name_stream__.str());
        if (!include_gqs__ && !include_tparams__) return;
        if (include_tparams__) {
            size_t m_j_1_max__ = n_dose;
            for (size_t j_1__ = 0; j_1__ < m_j_1_max__; ++j_1__) {
                param_name_stream__.str(std::string());
                param_name_stream__ << "m" << '.' << j_1__ + 1;
                param_names__.push_back(param_name_stream__.str());
            }
            size_t mu_j_1_max__ = n_dose;
            for (size_t j_1__ = 0; j_1__ < mu_j_1_max__; ++j_1__) {
                param_name_stream__.str(std::string());
                param_name_stream__ << "mu" << '.' << j_1__ + 1;
                param_names__.push_back(param_name_stream__.str());
            }
            param_name_stream__.str(std::string());
            param_name_stream__ << "sigma";
            param_names__.push_back(param_name_stream__.str());
        }
        if (!include_gqs__) return;
        size_t x_tilde_j_1_max__ = n_dose;
        for (size_t j_1__ = 0; j_1__ < x_tilde_j_1_max__; ++j_1__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "x_tilde" << '.' << j_1__ + 1;
            param_names__.push_back(param_name_stream__.str());
        }
        size_t y_tilde_j_1_max__ = n_dose;
        for (size_t j_1__ = 0; j_1__ < y_tilde_j_1_max__; ++j_1__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "y_tilde" << '.' << j_1__ + 1;
            param_names__.push_back(param_name_stream__.str());
        }
    }
    void unconstrained_param_names(std::vector<std::string>& param_names__,
                                   bool include_tparams__ = true,
                                   bool include_gqs__ = true) const {
        std::stringstream param_name_stream__;
        param_name_stream__.str(std::string());
        param_name_stream__ << "alpha1";
        param_names__.push_back(param_name_stream__.str());
        size_t alpha_j_1_max__ = (n_dose - 1);
        for (size_t j_1__ = 0; j_1__ < alpha_j_1_max__; ++j_1__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "alpha" << '.' << j_1__ + 1;
            param_names__.push_back(param_name_stream__.str());
        }
        param_name_stream__.str(std::string());
        param_name_stream__ << "cv";
        param_names__.push_back(param_name_stream__.str());
        if (!include_gqs__ && !include_tparams__) return;
        if (include_tparams__) {
            size_t m_j_1_max__ = n_dose;
            for (size_t j_1__ = 0; j_1__ < m_j_1_max__; ++j_1__) {
                param_name_stream__.str(std::string());
                param_name_stream__ << "m" << '.' << j_1__ + 1;
                param_names__.push_back(param_name_stream__.str());
            }
            size_t mu_j_1_max__ = n_dose;
            for (size_t j_1__ = 0; j_1__ < mu_j_1_max__; ++j_1__) {
                param_name_stream__.str(std::string());
                param_name_stream__ << "mu" << '.' << j_1__ + 1;
                param_names__.push_back(param_name_stream__.str());
            }
            param_name_stream__.str(std::string());
            param_name_stream__ << "sigma";
            param_names__.push_back(param_name_stream__.str());
        }
        if (!include_gqs__) return;
        size_t x_tilde_j_1_max__ = n_dose;
        for (size_t j_1__ = 0; j_1__ < x_tilde_j_1_max__; ++j_1__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "x_tilde" << '.' << j_1__ + 1;
            param_names__.push_back(param_name_stream__.str());
        }
        size_t y_tilde_j_1_max__ = n_dose;
        for (size_t j_1__ = 0; j_1__ < y_tilde_j_1_max__; ++j_1__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "y_tilde" << '.' << j_1__ + 1;
            param_names__.push_back(param_name_stream__.str());
        }
    }
}; // model
}  // namespace
typedef model_fix_mono_namespace::model_fix_mono stan_model;
#ifndef USING_R
stan::model::model_base& new_model(
        stan::io::var_context& data_context,
        unsigned int seed,
        std::ostream* msg_stream) {
  stan_model* m = new stan_model(data_context, seed, msg_stream);
  return *m;
}
#endif
#endif