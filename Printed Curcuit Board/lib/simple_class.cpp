#include <string>
#include <iostream>
#include <exception>
#include <cmath>
#include "../include/simple_class.hpp"

using std::endl;
using std::invalid_argument;
using std::cout;
using std::sqrt;
constexpr int DATA_TRANSMISSION_SPEED = 1000000000;

namespace ContactLib {

ContactType Contact::define_type(const Contact& link_contact) {
    if (link_contact.contact_type == ContactType::IN) {
        return ContactType::OUT;
    } else {
        return ContactType::IN;
    }
}

ContactType Contact::convert_type(string& type) {
    if (type == "in") {
        return ContactType::IN;
    } else if (type == "out") {
        return ContactType::OUT;
    } else {
        throw invalid_argument("Неверный тип контакта. Используйте in/out.");
    }
}

double Contact::find_distance(int x, int y) {
    double r = sqrt(x * x + y * y);
    return r;
}

string Contact::to_string(ContactType type) {
    if (type == ContactType::IN) {
        return "IN";
    } else {
        return "OUT";
    }
}

Contact::Contact() {
    contact_type = ContactType::OUT;
    x = 0;
    y = 0;
    linked_contact = nullptr;
}

Contact::Contact(string& type, int x_coordinate, int y_coordinate) {
    if (type != "in" && type != "out") {
        throw invalid_argument("Неверный тип. Невозможно создать контакт!");
    }
    x = x_coordinate;
    y = y_coordinate;
    contact_type = convert_type(type);
    linked_contact = nullptr;
}

Contact::Contact(int x_coordinate, int y_coordinate, Contact& linked) {
    if (linked.linked_contact != nullptr) {
        throw invalid_argument("Выбранный контакт уже соединен!");
    }
    ContactType type = define_type(linked);
    x = x_coordinate;
    y = y_coordinate;
    contact_type = type;
    linked_contact = &linked;
    linked.linked_contact = this;
}

void Contact::operator>>(Contact& link_contact) {
    if (contact_type == link_contact.contact_type) {
        throw invalid_argument("Невозможно соединить контакты одинаковых типов!");
    } else if (linked_contact == &link_contact){
        throw invalid_argument("Контакты уже соединены друг с другом");
    } else if (linked_contact != nullptr) {
        throw invalid_argument("Первый контакт уже соединён с другим контактом!");
    } else if (link_contact.linked_contact != nullptr) {
        throw invalid_argument("Второй контакт уже соединён с другим контактом!");
    }
    linked_contact = &link_contact;
    link_contact.linked_contact = this;
}

void Contact::operator<<(Contact* link_contact) {
    if (link_contact == nullptr) {
        throw invalid_argument("Контакты не соединены!");
    } else if (linked_contact != link_contact) {
        throw invalid_argument("Контакты не соединены!");
    }
    link_contact -> linked_contact = nullptr;
    linked_contact = nullptr;
}

std::ostream& operator<<(ostream& os, Contact& contact) {
    os << "Контакт" << Contact::to_string(contact.contact_type) << "(" << contact.x << "," << contact.y << ")" << endl; 
    if (contact.linked_contact != nullptr) {
        os << "Соединенный контакт: (" << (*contact.linked_contact).x 
           << "," << (*contact.linked_contact).y << ")" << endl;
    }
    return os;
}

std::istream& operator>>(istream& in, Contact& contact) {
    string type;
    int x, y;
    in >> type;
    in >> x;
    in >> y;
    if (in) {
        contact.set_contact_type(type);
        contact.set_x_coordinate(x);
        contact.set_y_coordinate(y);
    } else {
        throw invalid_argument("Неверный ввод");
    }
    return in;
}

void Contact::set_x_coordinate(int x_coordinate) {
    x = x_coordinate;
}

void Contact::set_y_coordinate(int y_coordinate) {
    y = y_coordinate;
}

void Contact::set_contact_type(string& type) {
    if ((type == "in")) {
        contact_type = ContactType::IN;
    } else if (type == "out") {
        contact_type = ContactType::OUT;
    } 
    else {
        throw invalid_argument("Неверный тип контакта. Используйте in/out.");
    }
}

int Contact::get_x_coordinate() {
    return x;
}

int Contact::get_y_coordinate() {
    return y;
}

ContactType Contact::get_contact_type() {
    return contact_type;
}

Contact* Contact::get_linked_contact() {
    return linked_contact;
}

double Contact::count_latency(Contact& contact) {
    if (linked_contact != &contact) {
        throw invalid_argument("Контакты не соединены");
    }
    return find_distance(x - contact.x, y - contact.y) / DATA_TRANSMISSION_SPEED;
}

std::partial_ordering Contact::operator<=>(Contact& contact) {
    return find_distance(x, y) <=> find_distance(contact.x, contact.y);
}

}