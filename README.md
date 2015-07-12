# divopt

[![Build Status](https://travis-ci.org/njanetos/divopt.svg?branch=master)](https://travis-ci.org/njanetos/divopt)
[![Coverage Status](https://coveralls.io/repos/njanetos/divopt/badge.svg?branch=master&service=github)](https://coveralls.io/github/njanetos/divopt?branch=master)

C++ library for finding a normal random variable which minimizes the Kullback-Leibler divergence with respect to some other, given normal random variable, and subject to the constraint that the probability of some event be some value.

## Installation

```
make
make install
```

## Usage

### Random variables and events

To create a 2-dimensional normal random variable:

```
c_rand_var_norm rand_var_norm(2);
```

divopt uses the armadillo library for all matrices. To set the mean and covariance matrix:

```
arma::Mat<double> mean(2, 1);
arma::Mat<double> cov(2, 2);

mean(0) = 0;
mean(1) = 2;

cov(0, 0) = 1;
cov(1, 0) = 0.25;
cov(0, 1) = 0.25;
cov(1, 1) = 2;

rand_var_norm.mean = mean;
rand_var_norm.cov = cov;
rand_var_norm.pack();
rand_var_norm.unpack();
```

`pack()` and `unpack()` are necessary to first read the mean and covariance matrix into the underlying data type (a vector), then to unpack that back into a mean and covariance matrix, along with other useful information such as the correlation matrix and the Cholesky factorization of the covariance matrix. You can also read in the underlying vector directly:

```
std::vector<double> raw_data;
raw_data[0] = 0;
raw_data[1] = 2;
raw_data[2] = 1;
raw_data[3] = 0.25;
raw_data[4] = 2;

rand_var_norm.dat_to_dist(&raw_data[0]);
```

This is not exactly the same thing as the first example, because the format for `raw_data` is [Mean, Cholesky factorization], meaning that the first two entries are the mean vector, and the last three entries are the lower triangular portion of the Cholesky factorization of the covariance matrix, read in column order.

Once the random variable has been instantiated, one can find the pdf, cdf, divergence, and entropy as follows. Here, `rand_var_norm2` is a second normal random variable of the same dimension as `rand_var_norm`, that has already been unpacked.

```
arma::Mat<double> location(2, 1);
location(0, 0) = -0.2;
location(1, 0) = -0.1;

// Returns the pdf at location
rand_var_norm.pdf(&location);

// Returns the cdf at location
rand_var_norm.cdf(&location);

// Returns the entropy at some location, measured against rand_var_norm 2
// This is equivalent to log(rand_var_norm.pdf(location)) - log(rand_var_norm2.pdf(location))
rand_var_norm.ent(&location, &rand_var_norm2);

// Returns the divergence against rand_var_norm2
rand_var_norm.div(&rand_var_norm2);
```

To define an event, use the `c_constraint` class. An event is something of the form 'x1 > 0.2 AND x2 < -0.1 OR x1 > 0.3'. The instantiation of this event would look like this:
```
// Define the 3 inequalities which will form this constraint
c_inequality inequality1(0, 0.2, e_binary_relation::GEQ);
c_inequality inequality2(1, -0.1, e_binary_relation::LEQ);
c_inequality inequality3(0, 0.3, e_binary_relation::GEQ);

c_constraint constraint();

constraint.add_inequality(inequality1, 0);
constraint.add_inequality(inequality2, 0);
constraint.add_inequality(inequality3, 1);
```
The first entry in `add_inequality` is the inequality to add. The second entry determines which 'slot' the inequality should fit in. There can be as many slots as you want, and they encode the following logical structure: If the first slot has inequalities E1, E2, ..., the second slot F1, F2, ... etc, then the logical interpretation is '(E1 AND E2 AND ...) OR (F1 AND F2 AND ...) OR ...'.  

A member of the `c_constraint` class can also have a probability associated with it.
```
constraint.set_prob(0.25);
```
To check whether it is indeed true that the probability that the defined event has probability 0.25 under some random variable `rand_var`,
```
constraint.is_satisfied(&rand_var);
```

### Optimization

To solve the optimization problem, use
```
rand_var2.approach(&rand_var, constraint);
```
Note that this will overwrite any data in `rand_var2`.

## Documentation

The code documentation is [here](http://njanetos.github.io/divopt/html/index.html).

A description of the math involved in the optimization problem is [here](http://njanetos.github.io/divopt/html/index.html).
