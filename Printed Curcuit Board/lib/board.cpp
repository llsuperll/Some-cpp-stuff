#include "../include/board.hpp"
#include <exception>
using std::invalid_argument;

namespace BoardLib {

PCBoard::PCBoard() {
    size = 0;
    capacity = N;
    contacts = new Contact[capacity];
}

PCBoard::PCBoard(Contact& contact) {
    size = 0;
    capacity = N;
    contacts = new Contact[capacity];
    contacts[size++] = contact;
}

PCBoard::PCBoard(Contact* contacts_arr, size_t arr_size) {
    size = 0;
    capacity = arr_size + N;
    contacts = new Contact[capacity];
    for (int i = 0; i < arr_size; i++) {
        if (check_free_position(contacts_arr[i])) {
            contacts[size] = contacts_arr[i];
            size++;
        }
    }
}

PCBoard::PCBoard(const PCBoard& board) {
    contacts = new Contact[board.capacity];
    size = board.size;
    capacity = board.capacity;
    for (int i = 0; i < board.size; i++) {
        contacts[i] = board.contacts[i];
    }
}

PCBoard::PCBoard(PCBoard&& board) noexcept {
    contacts = board.contacts;
    size = board.size;
    capacity = board.capacity;
    board.contacts = nullptr;
    board.size = 0;
    board.capacity = 0;
}

PCBoard& PCBoard::operator=(PCBoard&& board) noexcept {
    delete[] contacts;
    contacts = board.contacts;
    size = board.size;
    capacity = board.capacity;
    board.contacts = nullptr;
    board.size = 0;
    board.capacity = 0;
    return *this;
}

PCBoard& PCBoard::operator=(const PCBoard& board) {
    if (this == &board) {
       return *this; 
    }
    Contact* new_contacts = new Contact[board.capacity];
    for (int i = 0; i < board.size; i++) {
        new_contacts[i] = board.contacts[i];
    }
    delete[] contacts;
    contacts = new_contacts;
    size = board.size;
    capacity = board.capacity;
    return *this;
}

Contact* PCBoard::get_contacts() {
    return contacts;
}

size_t PCBoard::get_size() {
    return size;
}

size_t PCBoard::get_capacity() {
    return capacity;
}

bool PCBoard::check_free_position(Contact& new_contact) {
    for (int i = 0; i < size; i++) {
        if (new_contact <=> contacts[i] == std::partial_ordering::equivalent) {
            return false;
        }
    }
    return true;
}

void PCBoard::create_connection(int first_contact, int second_contact) {
    if (first_contact < 0 || first_contact >= size) {
        throw invalid_argument("Неверный индекс первого контакта");
    } else if (second_contact < 0 || second_contact >= size) {
        throw invalid_argument("Неверный индекс второго контакта");
    }
    Contact& contact = contacts[first_contact];
    Contact& contact2 = contacts[second_contact];
    contact >> contact2;
}

void PCBoard::delete_connection(int contact_id) {
    if (contact_id < 0 || contact_id >= size) {
        throw invalid_argument("Неверный индекс");
    }
    Contact& c = contacts[contact_id];
    Contact* c2 = c.get_linked_contact();
    c << c.get_linked_contact();
}

void PCBoard::delete_contact(int contact_id) {
    if (contact_id < 0 || contact_id >= size) {
        throw invalid_argument("Неверный индекс");
    }
    delete_connection(contact_id);
    for (int i = contact_id; i < size - 1; i++) {
        contacts[i] = contacts[i + 1];
    }
    size--;
}

PCBoard::~PCBoard() {
    delete[] contacts;
    size = 0;
    capacity = 0;
}

void PCBoard::change_position(int contact_id, int new_x, int new_y) {
    if (contact_id < 0 || contact_id >= size) {
        throw invalid_argument("Неверный индекс");
    }
    string t("in");
    Contact temp(t, new_x, new_y);
    if (check_free_position(temp)) {
        contacts[contact_id].set_x_coordinate(new_x);
        contacts[contact_id].set_y_coordinate(new_y);
    } else {
        throw invalid_argument("Место уже занято другим контактом!");
    }
}

void PCBoard::sort_contacts() {
    std::sort(contacts, contacts + size, 
        [](Contact& first, Contact& second) {
            return Contact::find_distance(first.get_x_coordinate(), first.get_y_coordinate())
            < Contact::find_distance(second.get_x_coordinate(), second.get_y_coordinate());
        }
    );
}

std::pair<int, int> PCBoard::find_most_distant() {
    double max_l = -1000, l = 0;
    int f = 0, d = 0;
    for (int i = 0; i < size; i++) {
        Contact c = contacts[i];
        for (int j = 0; j < size; j++) {
            try {
                l = c.count_latency(contacts[j]);
                if (l >= max_l) {
                    f = i;
                    d = j;
                    max_l = l;
                }   
            } catch (const std::invalid_argument& a) {}
        }
    }
    if (f == 0 && d == 0) {
        throw invalid_argument("На плате нет соединенных контактов!");
    }
    return std::make_pair(f, d);
}

void PCBoard::operator+=(Contact& new_contact) {
    if (capacity == size) {
        capacity += N;
        Contact* new_contacts = new Contact[capacity];
        for (int i = 0; i < size; i++) {
            new_contacts[i] = contacts[i];
        }
        delete[] contacts;
        contacts = new_contacts;
    }
    if (check_free_position(new_contact)) {
        contacts[size++] = new_contact; 
    } else {
        throw invalid_argument("Данные координаты уже заняты другим контактом");
    }
}


std::ostream& operator<<(ostream& os, PCBoard& board) {
    os << "[";
    for (int i = 0; i < board.size; i++) {
        os << "(" << board.contacts[i].get_x_coordinate() << "," << board.contacts[i].get_y_coordinate() << "), ";
    } 
    os << "]" << std::endl;
    return os;
}

std::istream& operator>>(istream& in, PCBoard& board) {
    int n;
    in >> n;
    if (in) {
        for (int i = 0; i < n; i++) {
            Contact c;
            in >> c;
            board += c;
        }
    } else {
        throw invalid_argument("Неверный ввод");
    }
    return in;
}

}