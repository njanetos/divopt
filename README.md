# tiresias

[![wercker status](https://app.wercker.com/status/03dc26b453adc7a34931c734b82e96e7/s/master "wercker status")](https://app.wercker.com/project/byKey/03dc26b453adc7a34931c734b82e96e7)

Tiresais is a betting market engine which prices Arrow-Debreu securities over continuous random variables. It consists of a library of optimization routines specialized for the task, as well as a server which provides an API for implementing those routines.

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

# Library

See the [documentation folder](http://njanetos.github.io/tiresias/html/) for documentation of the source code.

# API

The server listens for POST requests with JSON-formatted content. The JSON content encodes and returns the current parameterization of market prices.

## Quoting prices

The server listens at `/quote` for information about quoting prices. Here is the typical format of the content which would be sent.

```JSON5
{
  "dim": 3,
  "raw": [1, 1.3, 1.2, 1, 0, 1, 0, 0.2, 1],
  "low": ["-INF", "-INF", 0],
  "high": [1.3, 1.4, 1]
}
```

This request encodes both the trader's requested prediction, as well as current market prices. The first two values, `dim` and `raw`, are the parameterization of the market in its current state.
 - `dim: 3` means that there are three dimensions to the state space.
 - `raw` encodes the market's current prediction (price). This is represented by a multivariate normal over three dimension. The first three values of `raw` are the mean of the normal distribution, the last six values are the upper triangular Cholesky factorization of the covariance matrix of the normal distribution, in column major form. In this case, they represent
```
1
0 1
0 0.2 1
```

The second two values, `high` and `low`, are the bounds on a trader's predicted event. `low` is the lower bound, `high` is the upper bound. Here, the trader is requesting a quote on the current price of the event that the first dimension will be less than `1.3` and the second dimension will be less than `1.4` and the third dimension will be between `0` and `1`. The values `-INF` and `INF` represent negative infinity and positive infinity, respectively.

The server returns a JSON-formatted string with the market's current estimate that this event will occur, i.e., the current expected value of the asset traded on this event. In this case, the server should return a value of `11.04`, representing an 11.04% chance that the predicted event will occur.

## Buying / selling

The server listens at `/update` for requests to buy or sell, i.e., predictions. Typical content here would now look like
```JSON5
{
  "dim": 3,
  "raw": [1, 1.3, 1.2, 1, 0, 1, 0, 0.2, 1],
  "low": ["-INF", "-INF", 0],
  "high": [1.3, 1.4, 1],
  "prob": 0.4
}
```
This trader is saying he believes there to be a 40% chance of the event occurring. The server will return the updated market estimate, as well as the price quoted, formatted in the same way. In this case, the market should return
