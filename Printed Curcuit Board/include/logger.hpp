#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>
using std::string;

namespace MyLogger {

class Logger {
    private:
        std::ofstream logs;
    public:
        Logger();
        ~Logger();
        void write_log(string& msg);
};

}
#endif