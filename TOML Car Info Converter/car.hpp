#ifndef CAR_HPP
#define CAR_HPP

#include <string>
#include <stdexcept>
#include <regex>
#include <iostream>

using std::ostream;
using std::string;
using std::invalid_argument;
using std::regex;
using std::regex_match;

inline bool check_brand(string& str) {
    regex brand_format(R"(^[a-zA-Z\- ]{1,16}$)");
    return regex_match(str, brand_format);
}

struct Car {
    string brand;
    string owner;
    float mileage;

    Car(string& car_brand, string& car_owner, float car_mileage) {
        if (!check_brand(car_brand)) {
            throw invalid_argument("Invalid car brand: " + car_brand);
        }
        brand = car_brand;
        owner = car_owner;
        mileage = car_mileage;
    }
};

inline ostream& operator<<(ostream& os, Car& car) {
    os << "Объект: " << "{" << "brand='" << car.brand << "', " << "owner='" << car.owner << "', " << "mileage="<< car.mileage << "}"; 
    return os;
}

#endif
