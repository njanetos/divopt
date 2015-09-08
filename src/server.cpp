#include "server_http.hpp"
#include "client_http.hpp"

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

#include "picojson.h"

using namespace std;
using namespace picojson;
using namespace divopt;

typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;
typedef SimpleWeb::Client<SimpleWeb::HTTP> HttpClient;

int main() {
    //HTTP-server at port 8080 using 4 threads
    HttpServer server(8080, 4);

    server.resource["^/quote$"]["POST"]=[](HttpServer::Response& response, shared_ptr<HttpServer::Request> request) {
        try {

            response << "HTTP/1.1 200 OK\r\nContent-Length: " << "\r\n\r\n";

            value v;
            string err = parse(v, request->content);
            const value::object& obj = v.get<object>();

            int dim;

            dim = obj.find("dim")->second.get<double>();

            vector<value> raw_values = obj.find("raw")->second.get<vector<value>>();

            vector<double> raw_data(raw_values.size());
            for (size_t i = 0; i < raw_values.size(); ++i) {
                raw_data[i] = raw_values[i].get<double>();
            }

            vector<value> low_val = obj.find("low")->second.get<vector<value>>();
            vector<value> hig_val = obj.find("high")->second.get<vector<value>>();

            arma::Mat<double> inequalities(dim, 2);
            for (size_t i = 0; i < low_val.size(); ++i) {
                if (low_val[i].is<string>()) {
                    inequalities(i, 0) = -1*std::numeric_limits<double>::infinity();
                } else {
                    inequalities(i, 0) = low_val[i].get<double>();
                }

                if (hig_val[i].is<string>()) {
                    inequalities(i, 1) = std::numeric_limits<double>::infinity();
                } else {
                    inequalities(i, 1) = hig_val[i].get<double>();
                }
            }

            c_rand_var_norm rand_var_norm(dim);

            rand_var_norm.dat_to_dist(&raw_data[0]);
            rand_var_norm.unpack();

            string ret_val = to_string(100*rand_var_norm.cdf(inequalities));

            response << "HTTP/1.1 200 OK\r\nContent-Length: " << strlen(ret_val.c_str()) << "\r\n\r\n" << ret_val;


        }
        catch(exception& e) {
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
        }
    };

    thread server_thread([&server](){
        //Start server
        server.start();
    });

    server_thread.join();

    return 0;
}
