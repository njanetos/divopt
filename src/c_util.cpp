#include "c_util.h"

using namespace divopt;

std::vector<c_inequality> divopt::c_util::reduce(const std::vector<c_inequality> *ineq1,
                                                 const std::vector<c_inequality> *ineq2) {

    // Results stored in res
    std::vector<c_inequality> res;

    // Combine the two vectors
    res = *ineq1;
    res.insert(res.end(), ineq2->begin(), ineq2->end());

    // Check for zero probability events
    for (size_t i = 0; i < res.size(); ++i) {
        for (size_t j = i+1; j < res.size(); ++j) {
            // If it's a zero probability event, return an empty vector
            if (c_util::null_event(&res[i], &res[j])) {
                res.empty();
                return res;
            }
        }
    }

    // Combine redundant vectors
    for (std::vector<c_inequality>::iterator i = res.end() - 1; i >= res.begin(); --i) {
        for (std::vector<c_inequality>::iterator j = i + 1; j < res.end(); ++j) {
            // If it's redundant, eliminate the redundant one
            int red = c_util::is_nested(&*i, &*j);
            if (red != -1) {
                (red == 0) ? res.erase(i) : res.erase(j);
            }
        }
    }

    return res;

}

std::vector<c_inequality> divopt::c_util::reduce(c_constraint constraint,
                                                 size_t dim1,
                                                 size_t dim2) {

    return reduce(&(*constraint.get_inequalities())[dim1],
                  &(*constraint.get_inequalities())[dim2]);

}

bool divopt::c_util::null_event(const c_inequality *ineq1,
                                const c_inequality *ineq2) {

    // If they're not the same dimension, then they can't be a null event
    if (ineq1->get_dim() != ineq2->get_dim()) return false;

    // If they point in the same direction, then they can't be a null event
    if (ineq1->get_binary_relation() == ineq2->get_binary_relation()) return false;

    // Check the two other cases

    // x1 > v1, x1 < v2, v2 < v1
    if (ineq1->get_binary_relation() == divopt::e_binary_relation::GEQ &&
        ineq2->get_val() < ineq1->get_val()) return false;

    // x1 < v1, x1 > v2, v2 > v1
    if (ineq1->get_binary_relation() == divopt::e_binary_relation::LEQ &&
        ineq2->get_val() > ineq1->get_val()) return false;

    return true;

}

int divopt::c_util::is_nested(const c_inequality *ineq1,
                              const c_inequality *ineq2) {

    // Not a null event, so there are only three cases
    int res = -1;
    if (ineq1->get_binary_relation() == ineq2->get_binary_relation()) {
        if (ineq1->get_binary_relation() == divopt::e_binary_relation::GEQ) {
            (ineq1->get_val() > ineq2->get_val()) ? res = 0 : res = 1;
        } else {
            (ineq1->get_val() > ineq2->get_val()) ? res = 1 : res = 0;
        }
    }
    return res;

}

const double divopt::c_util::PI =         3.1415926535897932384626;
const double divopt::c_util::SQRT_TWO =   1.4142135623730950488016;
const double divopt::c_util::WEIGHTS[] ={ 0.0199532420590459132077,
                                          0.3936193231522411598285,
                                          0.9453087204829418812260,
                                          0.3936193231522411598285,
                                          0.0199532420590459132077};
const double divopt::c_util::ABS[] = {   -2.0201828704560856329290,
                                         -0.9585724646138185071128,
                                          0.0000000000000000000000,
                                          0.9585724646138185071128,
                                          2.020182870456085632929};
const size_t divopt::c_util::QUADRATURE_DIM = 5;
const double divopt::c_util::WEIGHT_FLOOR = 0.000001;
