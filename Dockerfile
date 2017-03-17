FROM debian:latest
MAINTAINER njanetos <nejanetos@gmail.com>
LABEL Description="Build environment for the tiresias engine"

RUN rm -rf /var/lib/apt/lists/* && \
    apt-get update && \
    apt-get install -y g++ libboost-all-dev git make libarmadillo-dev libnlopt-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/njanetos/tiresias.git && \
    cd tiresias && \
    make all && \
    ./tiresias_tests
