#include "server_http.hpp"
#include "client_http.hpp"

#include "common.h"

#include "utils.h"

using namespace std;
using namespace divopt;

typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;
typedef SimpleWeb::Client<SimpleWeb::HTTP> HttpClient;

int main() {
    //HTTP-server at port 8080 using 4 threads
    HttpServer server(8080, 4);

    server.resource["^/quote$"]["POST"]=[](HttpServer::Response& response, shared_ptr<HttpServer::Request> request) {
        try {
            stringstream ss;
            ss << request->content.rdbuf();;
            string ret_val = to_string(utils::quote_current_price(ss.str()));

            response << "HTTP/1.1 200 OK\r\nContent-Length: " << ret_val.size() << "\r\n\r\n" << ret_val;

        }
        catch(exception& e) {
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
        }
    };

    server.resource["^/update$"]["POST"]=[](HttpServer::Response& response, shared_ptr<HttpServer::Request> request) {
        try {
            stringstream ss;
            ss << request->content.rdbuf();;
            string ret_val = utils::update_json(ss.str());

            response << "HTTP/1.1 200 OK\r\nContent-Length: " << ret_val.size() << "\r\n\r\n" << ret_val;

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
