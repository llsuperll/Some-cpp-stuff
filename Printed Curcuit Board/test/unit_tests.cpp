#include <iostream>
#include <sstream>
#include "../include/simple_class.hpp"
#include "../include/logger.hpp"

using std::istringstream;

void test_empty_constructor(MyLogger::Logger& log) {
    try {
        ContactLib::Contact t;
        ContactLib::Contact q;
        string msg = "Пустой конструктор: тест пройден";
        log.write_log(msg);
    } catch (const std::exception& e) {
        string err_msg = string("Ошибка: ") + e.what();
        log.write_log(err_msg);
    }
}

void test_first_constructor(MyLogger::Logger& log) {
    try {
        string type1("in");
        ContactLib::Contact t1(type1, 10, 300);
        string type2("out");
        ContactLib::Contact t(type2, 10, 300);
        string type3("fasfsaf");
        try {
            ContactLib::Contact t(type3, 10, 300);
        } catch (const std::invalid_argument& a) {
            string msg = "Первый конструктор: тесты пройдены";
            log.write_log(msg);
        }
    } catch (const std::exception& e) {
        string err_msg = string("Ошибка: ") + e.what();
        log.write_log(err_msg);
    }
}

void test_first_constructor_empty(MyLogger::Logger& log) {
    try {
        string type("IN");
        ContactLib::Contact t(type, 10, 300);
    } catch (const std::invalid_argument& a) {
            string msg = "Первый конструктор: тесты пройдены";
            log.write_log(msg);
    }
}


void test_second_constructor(MyLogger::Logger& log) {
    string t("in");
    string t2("out");
    ContactLib::Contact link(t, 10, 10);
    ContactLib::Contact link2(t2, 20, 20);

    try {
        ContactLib::Contact t(50, 50, link);
    } catch (const std::exception& e) {
        string err_msg = string("Ошибка тест 1: ") + e.what();
        log.write_log(err_msg);
    }

    try {
        ContactLib::Contact t2(50, 50, link2);
    } catch (const std::exception& e) {
        string err_msg = string("Ошибка тест 2: ") + e.what();
        log.write_log(err_msg);
    }

    try {
        ContactLib::Contact t3(50, 50, link2);
    } catch (const std::invalid_argument& a) {
        string msg = "Второй конструктор: тесты пройдены";
        log.write_log(msg);
    } catch (const std::exception& e) {
        string err_msg = string("Ошибка тест 3: ") + e.what();
        log.write_log(err_msg);
    }

}

void test_getters(MyLogger::Logger& log) {
    try {
        string type("in");
        ContactLib::Contact t(type, 10, 10);
        t.get_contact_type();
        t.get_x_coordinate();
        t.get_y_coordinate();
        string msg = "Геттеры: тесты пройдены";
        log.write_log(msg);
    } catch (const std::exception& e) {
        string err_msg = string("Ошибка: ") + e.what();
        log.write_log(err_msg);
    }
}

void test_setters(MyLogger::Logger& log) {
    try {
        string type("in");
        string type2("out");
        string type3("fsqiekewr");
        ContactLib::Contact t(type, 10, 10);
        t.set_x_coordinate(200);
        t.set_y_coordinate(300);
        t.set_contact_type(type2);
        try {
            t.set_contact_type(type3);
        } catch (const std::invalid_argument& a) {
            string msg = "Сеттеры: тесты пройдены";
            log.write_log(msg);
        }
    } catch (const std::exception& e) {
        string err_msg = string("Ошибка: ") + e.what();
        log.write_log(err_msg);
    }
}

void test_setters_bad(MyLogger::Logger& log) {
    string type("in");
    ContactLib::Contact t(type, 10, 10);
    try {
        string tr("safas");
        t.set_contact_type(tr);
    } catch (const std::exception& e) {
        string msg = "Сеттеры (bad): тесты пройдены";
        log.write_log(msg);
    }
}

void test_console_output(MyLogger::Logger& log) {
    try {
        string type("in");
        string type2("out");
        ContactLib::Contact t(type, 10, 10);
        ContactLib::Contact t2(type2, 20, 20);
        
        std::cout << t;
        t >> t2;
        std::cout << t;
        string msg = "Вывод в консоль (перегрузка): тесты пройдены";
        log.write_log(msg);
    } catch (const std::exception& e) {
        string err_msg = string("Ошибка: ") + e.what();
        log.write_log(err_msg);
    }
}

void test_console_input(MyLogger::Logger& log) {
    try {
        ContactLib::Contact t;
        ContactLib::Contact t2;
        istringstream input("in\n100\n200\n");
        input >> t;
        try {
            istringstream input2("out\n100\n200\n");
            input2 >> t2;
        } catch (const std::invalid_argument& a) {
            string msg = "Ввод из консоли (перегрузка): тесты пройдены";
            log.write_log(msg);
        }
    } catch (const std::exception& e) {
        string err_msg = string("Ошибка: ") + e.what();
        log.write_log(err_msg);
    }
}

void test_console_input_bad(MyLogger::Logger& log) {
    try {
        ContactLib::Contact t;
        ContactLib::Contact t2;
        istringstream input("sad\nfsafsa\nsaasf\n");
        input >> t;
    } catch (const std::exception& e) {
        string msg = "Ввод из консоли (плохой): тесты пройдены";
        log.write_log(msg);
    }
}

void test_contact_connection(MyLogger::Logger& log) {
    string t("in");
    string t2("out");
    ContactLib::Contact link(t, 10, 10);
    ContactLib::Contact link2(t2, 20, 20);
    ContactLib::Contact link3(t, 20, 20);
    try {
        link >> link2;
    } catch (const std::exception& e) {
        string err_msg = string("Ошибка: ") + e.what();
        log.write_log(err_msg);
    }
    
    try {
        link >> link2;
    } catch (const std::invalid_argument& a) {
    } catch (const std::exception& e) {
        string err_msg = string("Ошибка: ") + e.what();
        log.write_log(err_msg);
    }

    try {
        link >> link3;
    } catch (const std::invalid_argument& a) {
    } catch (const std::exception& e) {
        string err_msg = string("Ошибка: ") + e.what();
        log.write_log(err_msg);
    }

    try {
        link3 >> link2;
    } catch (const std::invalid_argument& a) {
        string msg = "Соединение контактов (перегрузка): тесты пройдены";
        log.write_log(msg);
    } catch (const std::exception& e) {
        string err_msg = string("Ошибка: ") + e.what();
        log.write_log(err_msg);
    }
    
    try {
        string r("out");
        link3.set_contact_type(r);
        link >> link3;
    } catch (const std::invalid_argument& a) {
    } catch (const std::exception& e) {
        string err_msg = string("Ошибка: ") + e.what();
        log.write_log(err_msg);
    }
}

void test_count_latency(MyLogger::Logger& log) {
    string t("in");
    string t2("out");
    ContactLib::Contact link(t, 10, 10);
    ContactLib::Contact link2(t2, 20, 20);

    try {
        link.count_latency(link2);
    } catch (const std::invalid_argument& a) {
        try {
            link >> link2;
            link.count_latency(link2);
            string msg = "Подсчет задержки: тесты пройдены";
            log.write_log(msg);
        } catch (std::exception& e) {
            string err_msg = string("Ошибка: ") + e.what();
            log.write_log(err_msg);
        }
    } catch (std::exception& e) {
            string err_msg = string("Ошибка: ") + e.what();
            log.write_log(err_msg);
    }
}

void test_compare_contacts(MyLogger::Logger& log) {
    string t("in");
    string t2("out");
    ContactLib::Contact link(t, 10, 10);
    ContactLib::Contact link2(t2, 20, 20);

    auto cmp = link <=> link2;
    link2.set_x_coordinate(10);
    link2.set_y_coordinate(10);
    cmp = link2 <=> link;

    link.set_x_coordinate(30);
    cmp = link <=> link2;
    link.set_x_coordinate(10);
    link.set_y_coordinate(30);
    cmp = link <=> link2;
    link.set_x_coordinate(15);
    cmp = link <=> link2;
    if (cmp == std::strong_ordering::greater) {
        string msg = "Сравнение контактов <=> : тесты пройдены";
        log.write_log(msg);
    } else {
        string err_msg = string("Ошибка тест сравнение контактов");
        log.write_log(err_msg);
    }
}

int main() {
    MyLogger::Logger logger;
    test_empty_constructor(logger);
    test_first_constructor(logger);
    test_second_constructor(logger);
    test_getters(logger);
    test_setters(logger);
    test_setters_bad(logger);
    test_console_output(logger);
    test_console_input(logger);
    test_contact_connection(logger);
    test_count_latency(logger);
    test_compare_contacts(logger);
    test_console_input_bad(logger);
    return 0;
}
