#include "server_http.hpp"
#include "client_http.hpp"

//Added for the json-example
#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

//Added for the default_resource example
#include <fstream>
#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <armadillo>

#include "common.h"

#include "c_rand_var_norm.h"
#include "c_logger.h"

using namespace std;
//Added for the json-example:
using namespace boost::property_tree;
using namespace divopt;

typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;
typedef SimpleWeb::Client<SimpleWeb::HTTP> HttpClient;

int main() {
    //HTTP-server at port 8080 using 4 threads
    HttpServer server(8080, 4);

    //GET-example for the path /match/[number], responds with the matched string in path (number)
    //For instance a request GET /match/123 will receive: 123
    server.resource["^/match/([0-9]+)$"]["GET"]=[](HttpServer::Response& response, shared_ptr<HttpServer::Request> request) {
        logg().info() << "Request received: " << request->path_match[1];

        string number = request->path_match[1];
        response << "HTTP/1.1 200 OK\r\nContent-Length: " << number.length() << "\r\n\r\n" << number;
    };

    server.resource["^/quote/([0-9|,|.|INF|-]+)$"]["GET"]=[](HttpServer::Response& response, shared_ptr<HttpServer::Request> request) {

        logg().info() << "Request received: " << request->path_match[1];

        string val = request->path_match[1];
        istringstream ss(val);
        string token;
        vector<string> tokens;

        while(getline(ss, token, ',')) {
            tokens.push_back(token);
        }


        logg().info() << "Received " << tokens.size();
        for (size_t i = 0; i < tokens.size(); ++i) {
            logg().info() << tokens[i];
        }

        int dim = atoi(tokens[0].c_str());

        int curr = 1;

        double raw_data[dim+dim*(dim+1)/2];
        for (size_t i = 0; i < dim+dim*(dim+1)/2; ++i) {
            raw_data[i] = atof(tokens[curr+i].c_str());
        }

        curr = curr + dim+dim*(dim+1)/2;

        arma::Mat<double> inequalities(dim, 2);

        for (size_t i = 0; i < dim; ++i) {
            if (tokens[curr+i] == "INF") {
                inequalities(i, 0) = -1*std::numeric_limits<double>::infinity();
            } else {
                inequalities(i, 0) = atof(tokens[curr+i].c_str());
            }
        }

        curr = curr + dim;

        for (size_t i = 0; i < dim; ++i) {
            if (tokens[curr+i] == "INF") {
                inequalities(i, 1) = std::numeric_limits<double>::infinity();
            } else {
                inequalities(i, 1) = atof(tokens[curr+i].c_str());
            }
        }

        c_rand_var_norm rand_var_norm(dim);
        rand_var_norm.dat_to_dist(raw_data);
        rand_var_norm.unpack();

        logg().info() << rand_var_norm.mean;
        logg().info() << rand_var_norm.cov;
        logg().info() << inequalities;

        string ret_val = to_string(100*GOOrand_var_norm.cdf(inequalities));

        response << "HTTP/1.1 200 OK\r\nContent-Length: " << ret_val.length() << "\r\n\r\n" << ret_val;
    };

    thread server_thread([&server](){
        //Start server
        server.start();
    });

    server_thread.join();

    return 0;
}
