# tiresias

[![Build Status](https://travis-ci.org/njanetos/tiresias.svg?branch=master)](https://travis-ci.org/njanetos/tiresias)
[![Coverage Status](https://coveralls.io/repos/njanetos/tiresias/badge.svg?branch=master&service=github)](https://coveralls.io/github/njanetos/tiresias?branch=master)

Tiresais is a betting market engine which prices Arrow-Debreu securities over continuous random variables. It consists of a library of optimization routines specialized for the task, as well as a server which provides a RESTful API for implementing those routines.

# Installation

To build and run the server, use
```Shell
make server
./tiresias_server
```
The server listens on port 8080. The API is described below.

To build and run the suite of tests,
```Shell
make test
./tiresisas_tests
```

# API

The server listens for POST requests with JSON-formatted content. The JSON content encodes and returns the current parameterization of market prices.

## Quoting prices

The server listens at `/quote` for information about quoting prices. Here is the typical format of the content which would be sent.

```JSON5
{
  dim: 3,
  raw: [1, 1.3, 1.2, 1, 0, 1, 0, 0.2, 1},
  low: ["-INF", "-INF", 0],
  high: [1.3, 1.4, 1]
}
```

The first two values, `dim` and `raw`, are the parameterization of the market in its current state. `dim: 3` means that there are three dimensions. The first three values of `raw` are the current mean values, and the remaining values form the upper triangular Cholesky factorization of the covariance matrix. In this case, they represent
```
1
0 1 
0 0.2 1
```

`high` and `low` are the bounds on a trader's predicted event. `low` is the lower bound, `high` is the upper bound. Here, the trader is requesting a quote on the current price of the event that the first dimension will be less than `1.3` and the second dimension will be less than `1.4` and the third dimension will be between `0` and `1`. 

The server returns a JSON-formatted string with the market's current estimate that this event will occur, i.e., the current expected value of the asset traded on this event.

## Buying / selling

The server listens at `/update` for requests to buy or sell, i.e., predictions. Typical content here would now look like 
```JSON5
{
  dim: 3,
  raw: [1, 1.3, 1.2, 1, 0, 1, 0, 0.2, 1},
  low: ["-INF", "-INF", 0],
  high: [1.3, 1.4, 1],
  prob: 0.4
}
```
This trader is saying he believes there to be a 40% chance of the event occuring. The server will return the updated market estimate / price, formatted in the same way. 
