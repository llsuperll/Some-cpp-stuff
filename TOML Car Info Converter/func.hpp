#ifndef FUNC_HPP
#define FUNC_HPP

#include "car.hpp"
using String_with_Size = std::pair<const char*, size_t>;
using std::string;
using std::to_string;
using std::regex_search;
using std::smatch;

string to_toml(Car& car, string& name);
String_with_Size to_toml(Car& car, String_with_Size name);
char* to_toml(Car& car, const char* name);
Car to_struct(const string& toml);
Car to_struct(const char* toml);
Car to_struct(String_with_Size toml);

#endif
