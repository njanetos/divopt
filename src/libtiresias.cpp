#include <armadillo>
#include "libtiresias.h"
#include "picojson.h"
#include "c_rand_var_norm.h"
#include "nlopt.hpp"

using namespace picojson;
using namespace std;

double tiresias::quote(string json_string) {

    c_rand_var_norm rand_var_norm = json_to_rand_var_norm(json_string);
    arma::Mat<double> inequalities = json_to_inequalities(json_string);

    return 100*rand_var_norm.cdf(inequalities);

}

double tiresias::quote(c_rand_var_norm& current, arma::Mat<double>& inequalities) {
    return current.cdf(inequalities);
}

double tiresias::quote_cost(double current_price, double delta_x) {
    return log(1-current_price) - log(exp(1-delta_x)/(exp(delta_x) - exp(1-delta_x)));
}

double tiresias::quote_cost(c_rand_var_norm &current, arma::Mat<double>& inequalities, double delta_x) {
    return quote_cost(quote(current, inequalities), delta_x);
}

double tiresias::shares_outstanding(c_rand_var_norm& current, arma::Mat<double>& inequalities) {
    return shares_outstanding(current, quote(current, inequalities));
}

double tiresias::shares_outstanding(c_rand_var_norm& current, double price) {
    return 1/(1 + log((1-price)/price));
}

c_rand_var_norm tiresias::update(c_rand_var_norm& rand_var_norm,
                                 arma::Mat<double>& inequalities,
                                 double prob,
                                 double step = 0.01) {

    // initialize nlopt object
    nlopt::opt opt(nlopt::LN_COBYLA, rand_var_norm.get_opt_dim());

    opt.set_initial_step(step);

    // set up the data structure passed to the objective function
    obj_data obj;
    obj.current = &rand_var_norm;

    // set up the data structure passed for constraints
    con_data con;
    con.current = &rand_var_norm;
    con.inequalities = inequalities;
    con.p = prob;

    // set upper / Lower bounds
    opt.set_lower_bounds(rand_var_norm.get_lower_bounds());
    opt.set_upper_bounds(rand_var_norm.get_upper_bounds());

    // set the objective function
    opt.set_min_objective(obj_norm, &obj);

    // set the constraint function
    opt.add_equality_constraint(con_norm, &con, 0.001);

    // set algorithm parameters
    opt.set_maxeval(10000000);
    opt.set_xtol_rel(0.001);

    // construct the initial vector of data
    vector<double> x;
    x.resize(rand_var_norm.get_opt_dim());
    size_t k = 0;
    for (size_t i = 0; i < rand_var_norm.get_dim_prob(); ++i) {
        if (rand_var_norm.opt_flags[i]) {
            x[k] = rand_var_norm.raw_data[i];
            ++k;
        }
    }

    // optimize
    double minf;
    opt.optimize(x, minf);

    c_rand_var_norm update(rand_var_norm.get_dim());
    update.clone(&rand_var_norm);

    k = 0;
    for (size_t i = 0; i < rand_var_norm.get_dim_prob(); ++i) {
        if (rand_var_norm.opt_flags[i]) {
            update.raw_data[i] = x[k];
            ++k;
        }
    }
    update.unpack();

    return update;

}

string tiresias::update(string json_string) {
    c_rand_var_norm rand_var_norm = json_to_rand_var_norm(json_string);
    arma::Mat<double> inequalities = json_to_inequalities(json_string);

    c_rand_var_norm upd = update(rand_var_norm, inequalities, get_double_json(json_string, "prob"));
    return rand_var_norm_to_json(upd);
}

c_rand_var_norm tiresias::json_to_rand_var_norm(string json_string) {

    value v;
    string err = parse(v, json_string);

    if (!err.empty()) {
        throw invalid_argument(err);
    }

    if (!v.is<object>()) {
        throw invalid_argument("Malformed JSON.");
    }
    const value::object& obj = v.get<object>();

    if (!obj.find("dim")->second.is<double>()) {
        throw invalid_argument("Malformed JSON: Dimension.");
    }
    int dim = obj.find("dim")->second.get<double>();

    if (!obj.find("raw")->second.is<vector<value>>()) {
        throw invalid_argument("Malformed JSON: Raw values vector.");
    }
    vector<value> raw_values = obj.find("raw")->second.get<vector<value>>();

    vector<double> raw_data(raw_values.size());
    for (size_t i = 0; i < raw_values.size(); ++i) {
        if (!raw_values[i].is<double>()) {
            throw invalid_argument("Malformed JSON: Raw values.");
        }
        raw_data[i] = raw_values[i].get<double>();
    }

    c_rand_var_norm rand_var_norm(dim);

    rand_var_norm.dat_to_dist(&raw_data[0]);
    rand_var_norm.unpack();

    return rand_var_norm;

}

arma::Mat<double> tiresias::json_to_inequalities(string json_string) {

    value v;
    string err = parse(v, json_string);

    if (!err.empty()) {
        throw invalid_argument(err);
    }

    if (!v.is<object>()) {
        throw invalid_argument("Malformed JSON.");
    }
    const value::object& obj = v.get<object>();

    if (!obj.find("dim")->second.is<double>()) {
        throw invalid_argument("Malformed JSON: Dimension.");
    }
    int dim = obj.find("dim")->second.get<double>();


    if (!obj.find("low")->second.is<vector<value>>()) {
        throw invalid_argument("Malformed JSON: Lower inequality.");
    }
    vector<value> low_val = obj.find("low")->second.get<vector<value>>();

    if (!obj.find("high")->second.is<vector<value>>()) {
        throw invalid_argument("Malformed JSON: Upper inequality.");
    }
    vector<value> hig_val = obj.find("high")->second.get<vector<value>>();

    arma::Mat<double> inequalities(dim, 2);
    for (size_t i = 0; i < low_val.size(); ++i) {
        inequalities(i, 0) = low_val[i].is<string>() ?
          stod(low_val[i].get<string>()) : low_val[i].get<double>();
        inequalities(i, 1) = hig_val[i].is<string>() ?
          stod(hig_val[i].get<string>()) : hig_val[i].get<double>();
    }

    return inequalities;

}

double tiresias::get_double_json(string json_string, string key) {

    value v;
    string err = parse(v, json_string);

    if (!err.empty()) {
        throw invalid_argument(err);
    }

    if (!v.is<object>()) {
        throw invalid_argument("Malformed JSON.");
    }
    const value::object& obj = v.get<object>();

    if (!obj.find(key)->second.is<double>()) {
        throw invalid_argument("Malformed JSON: Cannot find key.");
    }
    return obj.find(key)->second.get<double>();

}

string tiresias::rand_var_norm_to_json(c_rand_var_norm& rand_var_norm) {
    value dim((double) rand_var_norm.get_dim());

    vector<value> raw_data(rand_var_norm.get_dim_prob());
    for (size_t i = 0; i < rand_var_norm.get_dim_prob(); ++i) {
        raw_data[i] = value(rand_var_norm.raw_data[i]);
    }

    value raw_data_array(raw_data);

    object all;

    all.insert(pair<string, value>("dim", dim));
    all.insert(pair<string, value>("raw", raw_data_array));

    value all_value(all);

    return all_value.serialize();
}

double tiresias::obj_norm(unsigned n,
                          const double *x,
                          double *grad,
                          void *data) {

    // convert the pointer
    obj_data *d = (obj_data *) data;

    // clone the current guy
    c_rand_var_norm temp(d->current->get_dim());
    temp.clone(d->current);

    // update the current guy
    size_t k = 0;
    for (size_t i = 0; i < temp.get_dim_prob(); ++i) {
        if (temp.opt_flags[i]) {
            temp.raw_data[i] = x[k];
            ++k;
        }
    }
    temp.unpack();

    // Compute gradient
    if (grad) {
        // Find the gradient
        arma::Mat<double> div_grad = temp.div_grad(*(d->current));

        // Copy in the gradient
        for (size_t i = 0; i < temp.get_dim_prob(); ++i) {
            grad[i] = div_grad(i);
        }
    }

    // Compute divergence
    double div = temp.div(*(d->current));

    return div;
}

double tiresias::con_norm(unsigned n,
                          const double *x,
                          double *grad,
                          void *data) {

    // Convert the pointer
    con_data * d = (con_data *) data;

    // clone the current guy
    c_rand_var_norm temp(d->current->get_dim());
    temp.clone(d->current);

    // update the current guy
    size_t k = 0;
    for (size_t i = 0; i < temp.get_dim_prob(); ++i) {
        if (temp.opt_flags[i]) {
            temp.raw_data[i] = x[k];
            ++k;
        }
    }
    temp.unpack();

    // Compute the gradient
    if (grad) {
        arma::Mat<double> con_grad = temp.cdf_grad(d->inequalities);

        // Copy in the gradient
        for (size_t i = 0; i < temp.get_dim_prob(); ++i) {
            grad[i] = con_grad(i);
        }
    }

    // Find the cdf
    double cdf = temp.cdf(d->inequalities) - d->p;

    return cdf;
}
