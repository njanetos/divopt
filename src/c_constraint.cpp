#include "c_constraint.h"

using namespace divopt;

divopt::c_constraint::c_constraint() {
    std::vector<arma::mat> inequalities;
    prob = 0.5;
}

divopt::c_constraint::c_constraint(float prob) {

    this->prob = prob;

}

void divopt::c_constraint::add_inequality(arma::mat inequalities) {

    this->inequalities.push_back(inequalities);

}

bool divopt::c_constraint::is_satisfied(c_rand_var *rand_var) {

    bool test_is_satisfied = false;

    for (size_t i = 0; i < inequalities.size(); ++i) {
        test_is_satisfied = (test_is_satisfied || rand_var->cdf(&inequalities[i]));
    }

    return test_is_satisfied;

}

float divopt::c_constraint::eval_prob(c_rand_var *rand_var) {

    return 0.5;

}

void divopt::c_constraint::set_prob(float prob) {

    this->prob = prob;

}

std::vector<arma::mat> * divopt::c_constraint::get_inequalities() {

    return &inequalities;

}

float divopt::c_constraint::get_prob() {

    return prob;

}
