#include "c_constraint.h"

divopt::c_constraint::c_constraint() {
    std::vector< std::vector<c_inequality> > inequalities;
    prob = 0.5;
}

divopt::c_constraint::c_constraint(float prob) {

    this->prob = prob;

}

divopt::c_constraint::~c_constraint() {
    //dtor
}

void divopt::c_constraint::add_inequality(c_inequality inequality) {

    std::vector<c_inequality> new_inequalities;
    new_inequalities.push_back(inequality);
    inequalities.push_back(new_inequalities);

}

void divopt::c_constraint::add_inequality(std::vector<c_inequality> inequalities) {

    this->inequalities.push_back(inequalities);

}

void divopt::c_constraint::add_inequality(c_inequality inequality, size_t pos) {

    inequalities[pos].push_back(inequality);

}

bool divopt::c_constraint::is_satisfied(c_rand_var *rand_var) {

    bool test_is_satisfied = false;

    for (size_t i = 0; i < inequalities.size(); ++i) {
        test_is_satisfied = (test_is_satisfied || rand_var->cdf(&inequalities[i]));
    }

    return test_is_satisfied;

}

float divopt::c_constraint::eval_prob(c_rand_var *rand_var) {



}

void divopt::c_constraint::set_prob(float prob) {

    this->prob = prob;

}

float divopt::c_constraint::get_prob() {

    return prob;

}
