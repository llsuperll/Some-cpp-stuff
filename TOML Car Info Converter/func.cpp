#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include "func.hpp"
#include <iterator>


string to_toml(Car& car, string& name) {
    string res = "[" + name + "]\n" + 
                 "brand = \"" + car.brand + "\"\n" + 
                 "owner = \"" + car.owner + "\"\n" + 
                 "mileage = " + to_string(car.mileage) + "\n";
    return res;
}

String_with_Size to_toml(Car& car, String_with_Size name) {
    char* res = to_toml(car, string(name.first, name.second).c_str());
    return {res, strlen(res)};
}

char* to_toml(Car& car, const char* name) {
    string nam(name);
    string str = to_toml(car, nam);
    char* res = new char[str.length() + 1];
    for (int i = 0; i < str.length(); i++) {
        res[i] = str[i];
    }
    res[str.length()] = '\0';
    return res;
}

Car to_struct(const string& toml) {
    int index = 1;
    int endline = toml.find('\n', index);
    if (toml[1] != '[' || toml[endline - 1] != ']') {
        std::cout << 111 << std::endl;
        throw invalid_argument("Введённая строка не соответствует формату toml");
    }
    
    index = endline + 1;
    if (std::ranges::find(toml, '"') == toml.end() || std::ranges::find(toml, '=') == toml.end()) {
        std::cout << 2222 << std::endl;
        throw invalid_argument("Введённая строка не соответствует формату toml");
    }
    
    std::vector<string> fields;
    while (index < toml.length()) {
        int end_line = toml.find('\n', index);
        int eq_pos = std::find(toml.begin() + index, toml.begin() + end_line, '=') - toml.begin();
        
        int field_start = eq_pos + 1;
        while (toml[field_start] == ' ' || toml[field_start] == '"') field_start++;
        int q_pos = std::find(toml.begin() + field_start, toml.begin() + end_line, '"') - toml.begin();
        
        if (q_pos == end_line) {
            q_pos = std::find(toml.begin() + field_start, toml.begin() + end_line, ' ') - toml.begin();
        }
        
        string value = toml.substr(field_start, q_pos - field_start);
        fields.push_back(value);
        index = end_line + 1;
    }
    std::cout << fields.size() << std::endl;
    if (fields.size() < 3) {
        throw invalid_argument("Введённая строка не соответствует формату toml");
    }

    float mileage = stod(fields[2]);
    Car res{fields[0], fields[1], mileage};
    return res;
}


Car to_struct(const char* toml) {
    string str(toml);
    Car res = to_struct(str);
    return res;
}

Car to_struct(String_with_Size toml) {
    string str(toml.first, toml.second);
    Car res = to_struct(str);
    return res;
}
