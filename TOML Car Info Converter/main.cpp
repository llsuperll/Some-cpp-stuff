#include <iostream>
#include <string>
#include <limits>
#include "ui.hpp"
#include "func.hpp"

using std::invalid_argument;
using std::runtime_error;
using std::bad_alloc;
using std::cout;
using std::endl;
using std::cin;
using std::numeric_limits;
using std::streamsize;

int main() {
    bool flag = true;
    while (flag) {
        try {
            dialog_menu();
        } 
        catch (invalid_argument& e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        catch (runtime_error& e) {
            cout << e.what() << ". Завершение программы."<< endl;
            flag = false;
        }
        catch (bad_alloc& e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}
