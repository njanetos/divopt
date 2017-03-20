# tiresias

[![wercker status](https://app.wercker.com/status/03dc26b453adc7a34931c734b82e96e7/s/master "wercker status")](https://app.wercker.com/project/byKey/03dc26b453adc7a34931c734b82e96e7)

Tiresais is a betting market engine which prices Arrow-Debreu securities over continuous random variables. It consists of a library of optimization routines specialized for the task, as well as a server which provides an API for implementing those routines.

## Installation

```
make
make install
```

## Usage

See `libtiresias.h`, for exposed functions and documentation. The library accepts market prices encoded as a JSON file. See `c_tests.cpp` for examples of how to encode market prices in JSON format.
