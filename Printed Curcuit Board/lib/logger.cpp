#include "logger.hpp"
using std::runtime_error;
using std::endl;

namespace MyLogger {

Logger::Logger() {
    logs.open("logs.txt");
    if (!logs.is_open()) {
        throw runtime_error("Ошибка открытия файла логов");
    }
    logs << "Гигачад тесты класса контакт:\n";
}

Logger::~Logger() {
    if (logs.is_open()) {
        logs.close();
    }
}

void Logger::write_log(string& msg) {
    logs << msg << endl;
}

}