#include "utils.h"

#include "c_rand_var_norm.h"

using namespace picojson;

real divopt::utils::quote_current_price(std::string json_string) {

    c_rand_var_norm rand_var_norm = json_to_rand_var_norm(json_string);
    arma::Mat<real> inequalities = json_to_inequalities(json_string);

    return 100*rand_var_norm.cdf(inequalities);

}

real divopt::utils::quote_current_price(c_rand_var_norm& current, arma::Mat<real>& inequalities) {
    return current.cdf(inequalities);
}

real divopt::utils::quote_cost(real current_price, real delta_x) {
    return log(1-current_price) - log(exp(1-delta_x)/(exp(delta_x) - exp(1-delta_x)));
}

real divopt::utils::quote_cost(c_rand_var_norm &current, arma::Mat<real>& inequalities, real delta_x) {
    return quote_cost(quote_current_price(current, inequalities), delta_x);
}

real divopt::utils::shares_outstanding(c_rand_var_norm& current, arma::Mat<real>& inequalities) {
    return shares_outstanding(current, quote_current_price(current, inequalities));
}

real divopt::utils::shares_outstanding(c_rand_var_norm& current, real price) {
    return 1/(1 + log((1-price)/price));
}

divopt::c_rand_var_norm divopt::utils::update(c_rand_var_norm& rand_var_norm, arma::Mat<real>& inequalities, real prob) {


    nlopt::opt opt(nlopt::LD_SLSQP, rand_var_norm.get_dim_prob());

    // Set the constraints and objective data
    obj_data obj;
    obj.current = &rand_var_norm;
    con_data con;
    con.current = &rand_var_norm;
    con.inequalities = inequalities;
    con.p = prob;

    // Upper / Lower bounds

    opt.set_lower_bounds(rand_var_norm.get_lower_bounds());
    opt.set_upper_bounds(rand_var_norm.get_upper_bounds());
    opt.set_min_objective(obj_norm, &obj);

    std::vector<double> tol(2);
    tol[0] = 0.01;
    tol[1] = 0.01;
    opt.add_equality_constraint(con_norm, &con, 0.0001);

    opt.set_maxeval(100);
    opt.set_xtol_rel(0.0001);

    std::vector<double> x = rand_var_norm.raw_data;

    double minf;
    opt.optimize(x, minf);

    c_rand_var_norm update(rand_var_norm.get_dim());
    update.dat_to_dist(&x[0]);
    update.unpack();

    return update;

}

divopt::c_rand_var_norm divopt::utils::update(std::string json_string) {
    c_rand_var_norm rand_var_norm = json_to_rand_var_norm(json_string);
    arma::Mat<real> inequalities = json_to_inequalities(json_string);
    return update(rand_var_norm, inequalities, get_double_json(json_string, "prob"));
}

std::string divopt::utils::update_json(std::string json_string) {
    c_rand_var_norm upd = update(json_string);
    return rand_var_norm_to_json(upd);
}

divopt::c_rand_var_norm divopt::utils::json_to_rand_var_norm(std::string json_string) {

    value v;
    std::string err = parse(v, json_string);

    if (!err.empty()) {
        throw std::invalid_argument(err);
    }

    if (!v.is<object>()) {
        throw std::invalid_argument("Malformed JSON.");
    }
    const value::object& obj = v.get<object>();

    if (!obj.find("dim")->second.is<double>()) {
        throw std::invalid_argument("Malformed JSON: Dimension.");
    }
    int dim = obj.find("dim")->second.get<double>();

    if (!obj.find("raw")->second.is<std::vector<value>>()) {
        throw std::invalid_argument("Malformed JSON: Raw values vector.");
    }
    std::vector<value> raw_values = obj.find("raw")->second.get<std::vector<value>>();

    std::vector<double> raw_data(raw_values.size());
    for (size_t i = 0; i < raw_values.size(); ++i) {
        if (!raw_values[i].is<double>()) {
            throw std::invalid_argument("Malformed JSON: Raw values.");
        }
        raw_data[i] = raw_values[i].get<double>();
    }

    c_rand_var_norm rand_var_norm(dim);

    rand_var_norm.dat_to_dist(&raw_data[0]);
    rand_var_norm.unpack();

    return rand_var_norm;

}

arma::Mat<real> divopt::utils::json_to_inequalities(std::string json_string) {

    value v;
    std::string err = parse(v, json_string);

    if (!err.empty()) {
        throw std::invalid_argument(err);
    }

    if (!v.is<object>()) {
        throw std::invalid_argument("Malformed JSON.");
    }
    const value::object& obj = v.get<object>();

    if (!obj.find("dim")->second.is<double>()) {
        throw std::invalid_argument("Malformed JSON: Dimension.");
    }
    int dim = obj.find("dim")->second.get<double>();


    if (!obj.find("low")->second.is<std::vector<value>>()) {
        throw std::invalid_argument("Malformed JSON: Lower inequality.");
    }
    std::vector<value> low_val = obj.find("low")->second.get<std::vector<value>>();

    if (!obj.find("high")->second.is<std::vector<value>>()) {
        throw std::invalid_argument("Malformed JSON: Upper inequality.");
    }
    std::vector<value> hig_val = obj.find("high")->second.get<std::vector<value>>();

    arma::Mat<double> inequalities(dim, 2);
    for (size_t i = 0; i < low_val.size(); ++i) {
        if (low_val[i].is<std::string>()) {
            inequalities(i, 0) = -1*std::numeric_limits<double>::infinity();
        } else {
            inequalities(i, 0) = low_val[i].get<double>();
        }

        if (hig_val[i].is<std::string>()) {
            inequalities(i, 1) = std::numeric_limits<double>::infinity();
        } else {
            inequalities(i, 1) = hig_val[i].get<double>();
        }
    }

    return inequalities;

}

double divopt::utils::get_double_json(std::string json_string, std::string key) {

    value v;
    std::string err = parse(v, json_string);

    if (!err.empty()) {
        throw std::invalid_argument(err);
    }

    if (!v.is<object>()) {
        throw std::invalid_argument("Malformed JSON.");
    }
    const value::object& obj = v.get<object>();

    if (!obj.find(key)->second.is<double>()) {
        throw std::invalid_argument("Malformed JSON: Cannot find key.");
    }
    return obj.find(key)->second.get<double>();

}

std::string divopt::utils::rand_var_norm_to_json(c_rand_var_norm& rand_var_norm) {
    value dim((double) rand_var_norm.get_dim());

    std::vector<value> raw_data(rand_var_norm.get_dim_prob());
    for (size_t i = 0; i < rand_var_norm.get_dim_prob(); ++i) {
        raw_data[i] = value(rand_var_norm.raw_data[i]);
    }

    value raw_data_array(raw_data);

    object all;

    all.insert(std::pair<std::string, value>("dim", dim));
    all.insert(std::pair<std::string, value>("raw", raw_data_array));

    value all_value(all);

    return all_value.serialize();
}

real divopt::utils::obj_norm(unsigned n, const double *x, double *grad, void *data) {

    // Convert the pointer
    obj_data *d = (obj_data *) data;

    // Clone the current guy
    c_rand_var_norm temp(d->current->get_dim());

    temp.dat_to_dist(x);
    temp.unpack();

    // Compute gradient
    if (grad) {
        // Find the gradient
        arma::Mat<real> div_grad = temp.div_grad(*(d->current));

        // Copy in the gradient
        for (size_t i = 0; i < temp.get_dim_prob(); ++i) {
            grad[i] = div_grad(i);
        }
    }

    // Compute divergence
    real div = temp.div(*(d->current));

    return div;
}

double divopt::utils::con_norm(unsigned n, const double *x, double *grad, void *data) {

    // Convert the pointer
    con_data * d = (con_data *) data;

    c_rand_var_norm temp(d->current->get_dim());
    temp.dat_to_dist(x);
    temp.unpack();

    // Compute the gradient
    if (grad) {
        arma::Mat<real> con_grad = temp.cdf_grad(d->inequalities);

        // Copy in the gradient
        for (size_t i = 0; i < temp.get_dim_prob(); ++i) {
            grad[i] = con_grad(i);
        }
    }

    // Find the cdf
    double cdf = temp.cdf(d->inequalities) - d->p;

    return cdf;
}

const double divopt::utils::PI =         3.1415926535897932384626;
const double divopt::utils::SQRT_TWO =   1.4142135623730950488016;
const double divopt::utils::WEIGHTS[] ={ 0.0199532420590459132077,
                                         0.3936193231522411598285,
                                         0.9453087204829418812260,
                                         0.3936193231522411598285,
                                         0.0199532420590459132077};
const double divopt::utils::ABS[] = {   -2.0201828704560856329290,
                                        -0.9585724646138185071128,
                                         0.0000000000000000000000,
                                         0.9585724646138185071128,
                                         2.020182870456085632929};
const size_t divopt::utils::QUADRATURE_DIM = 5;
const double divopt::utils::WEIGHT_FLOOR = 0.000001;
