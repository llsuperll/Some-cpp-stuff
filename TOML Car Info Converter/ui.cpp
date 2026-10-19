#include <iostream>
#include <string>
#include "func.hpp"
#include <limits>
using std::string;
using std::invalid_argument;
using std::runtime_error;
using std::ostream;
using std::getline;
using std::cout;
using std::endl;
using std::cin;
using std::numeric_limits;
using std::streamsize;

void print_info() {
    cout << "================= TOML ПЕРЕГОНЯТЕЛЬ228: ===================\n"
         << "Преобразование из строки в структуру:\n"
         << "  1 - из std::string\n"
         << "  2 - из char* c нуль-терминатором\n"
         << "  3 - из char* с размером\n"
         << "Преобразование из структуры в строку:\n"
         << "  4 - в std::string\n"
         << "  5 - в char* с нуль-терминатором\n"
         << "  6 - в char* с размером\n" 
         << "  7 - Выйти из программы\n"
         << "===========================================================" << endl;
}

void check_eof() {
    if (cin.eof()) {
        throw runtime_error("EOF");
    }
}

Car input_car() {
    string owner, brand;
    float mileage;
    cout << "Введите бренд: ";
    cin >> brand;
    check_eof();
    cout << "Введите владельца: ";
    cin >> owner;
    check_eof();
    cout << "Введите пробег: ";
    while (!(cin >> mileage)) {
        cout << "Введите пробег: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    check_eof();
    return Car(brand, owner, mileage);
}

string input_toml() {
    string buf, res;
    for (int i = 0; i < 5; i++) {
        getline(cin, buf);
        check_eof();
        res += buf + "\n";
    }
    return res;
}   

void dialog_menu() {
    int choice;
    string str;
    print_info();
    cout << "Сделайте выбор (1-7): ";
    cin >> choice;
    if (cin.eof()) {
        throw runtime_error("EOF");
    } 
    switch (choice) {
    case 1: {
        str = input_toml();
        Car car = to_struct(str);
        cout << car << endl;
        break;
    }
    case 2: {
        str = input_toml();
        const char* toml = str.c_str();
        Car car = to_struct(toml);
        cout << car << endl;
        break;
    }
    case 3: {
        str = input_toml();
        const char* cstr = str.c_str();
        String_with_Size toml(cstr, str.length());
        Car car = to_struct(toml);
        cout << car << endl;
        break;
    }
    case 4: {
        cout << "Введите название записи:";
        cin >> str;
        check_eof();
        Car example = input_car();
        string res = to_toml(example, str);
        cout << res << endl;
        break;
    }
    case 5: {
        cout << "Введите название записи:";
        cin >> str;
        check_eof();
        Car example = input_car();
        const char* name = str.c_str();
        char* res = to_toml(example, name);
        cout << res << endl;
        delete[] res;
        break;
    }
    case 6: {
        cout << "Введите название записи:";
        cin >> str;
        check_eof();
        Car example = input_car();
        const char* name = str.c_str();
        String_with_Size nam(name, str.length());
        String_with_Size res = to_toml(example, nam);
        cout << string (res.first, res.second) << endl;
        delete[] res.first;
        break;
    }
    case 7:
        throw(runtime_error("EOF"));
    default:
        cout << "Неизвестная команда" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }
}
