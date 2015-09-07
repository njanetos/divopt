#include <iostream>
#include <armadillo>

class c_log_message {

    public:
        c_log_message(const char *header) {
            std::cout << header;
        }

        c_log_message(bool result) {
            std::cout << "[";
            if (result) {
                std::cout << "\033[1;32m";
                std::cout << "SUCCESS";
                std::cout << "\033[0m";

            } else {
                std::cout << "\033[1;31m";
                std::cout << "FAILURE";
                std::cout << "\033[0m";
            }

            std::cout << "]: ";
        }

        ~c_log_message() {
            std::cout << "\n";
        }

        c_log_message &operator<<(const arma::mat &t) {
            std::cout << std::endl;
            std::cout << t;
            return *this;
        }

        template<typename T>
        c_log_message &operator<<(const T &t) {
            std::cout << t;
            return *this;
        }

};

class c_logger {
    public:
        c_log_message error() {
            return c_log_message("\033[1;31mERROR: \033[0m");
        }

        c_log_message info() {
            return c_log_message("\033[1;34mINFO: \033[0m");
        }

        c_log_message warning() {
            return c_log_message("\033[1;35mINFO: \033[0m");
        }

        c_log_message debug() {
            return c_log_message("\033[1;32mDEBUG: \033[0m");
        }

        c_log_message test(bool result) {
            return c_log_message(result);
        }

        c_log_message breakLine() {
            return c_log_message("-----------------------------------------------------------");
        }
};

c_logger &logg();
