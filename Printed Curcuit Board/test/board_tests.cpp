#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "../include/board.hpp"
#include <sstream>
using BoardLib::PCBoard;
using ContactLib::Contact;

Contact* init_board(size_t size) {
    Contact* cs = new Contact[size];
    string t("in");
    for (int i = 0; i < size; i++) {
        Contact c(t, 10 + i, 5 + i);
        cs[i] = c;
    }
    return cs;
}

TEST_CASE("Конструкторы") {
    SECTION("Пустой конструктор") {
        PCBoard b;
        REQUIRE(b.get_size() == 0);
        REQUIRE(b.get_capacity() == N);
        REQUIRE(b.get_contacts() != nullptr);
    }

    SECTION("Конструктор с 1 контактом") {
        Contact c;
        PCBoard b(c);
        REQUIRE(b.get_size() == 1);
        REQUIRE(b.get_capacity() == N);
        REQUIRE((b.get_contacts()[0] <=> c) == std::partial_ordering::equivalent);
    }

    SECTION("Конструтор из массива") {
        size_t size = 5;
        Contact* cs = init_board(size);
        PCBoard b(cs, size);
        REQUIRE(b.get_contacts() != nullptr);
        REQUIRE(b.get_size() == size);
        REQUIRE(b.get_capacity() == size + N);
        delete[] cs;
    }

    SECTION("Конструктор из массива с повторками") {
        size_t size = 3;
        Contact* cs = init_board(size);
        cs[1].set_x_coordinate(10);
        cs[1].set_y_coordinate(5);
        PCBoard b(cs, size);
        REQUIRE(b.get_size() == 2);
        delete[] cs;
    }

    SECTION("Копирующий конструктор") {
        size_t size = 5;
        Contact* cs = init_board(size);
        PCBoard b(cs, size);
        PCBoard b2(b);
        REQUIRE((b2.get_contacts()[2] <=> b.get_contacts()[2]) == std::partial_ordering::equivalent);
        REQUIRE((b2.get_size() == b.get_size()));
        REQUIRE((b2.get_capacity() == b.get_capacity()));
        delete[] cs;
    }

    SECTION("Перемещающий конструктор") {
        size_t size = 5;
        Contact* cs = init_board(size);
        PCBoard b(cs, size);
        PCBoard b2(std::move(b));
        REQUIRE(b2.get_size() == size);
        REQUIRE(b2.get_capacity() == size + N);
        REQUIRE(b.get_size() == 0);
        REQUIRE(b.get_capacity() == 0);
        REQUIRE(b.get_contacts() == nullptr);
        REQUIRE(b2.get_contacts() != nullptr);
        delete[] cs;
    }
}

TEST_CASE("Создание связей") {
    size_t size = 4;
    Contact* cs = init_board(size);
    PCBoard b(cs, size);
    string t("out");
    Contact c(t, 10, 100);
    b += c;
    SECTION("Корректное создание") {
        b.create_connection(0, 4);
        REQUIRE(b.get_contacts()[0].get_linked_contact() == &(b.get_contacts()[4]));
    }
    SECTION("Некорректное создание") {
        REQUIRE_THROWS_AS(b.create_connection(1, 2), std::invalid_argument);
        REQUIRE_THROWS_AS(b.create_connection(55, 3), std::invalid_argument);
        REQUIRE_THROWS_AS(b.create_connection(3, 55), std::invalid_argument);
    }
    delete[] cs;
}

TEST_CASE("Удаление связей") {
    size_t size = 4;
    Contact* cs = init_board(size);
    PCBoard b(cs, size);
    string t("out");
    Contact c(t, 10, 100);
    b += c;
    b.create_connection(0, 4);
    SECTION("Корректное удаление") {
        b.delete_connection(0);
        REQUIRE(b.get_contacts()[0].get_linked_contact() == nullptr);
        REQUIRE(b.get_contacts()[4].get_linked_contact() == nullptr);
    }
    SECTION("Некорректное удаление") {
        REQUIRE_THROWS_AS(b.delete_connection(2), std::invalid_argument);
        REQUIRE_THROWS_AS(b.delete_connection(55), std::invalid_argument);
    }
    delete[] cs;
}

TEST_CASE("Удаление контакта") {
    size_t size = 4;
    Contact* cs = init_board(size);
    PCBoard b(cs, size);
    string t("out");
    Contact c(t, 10, 100);
    b += c;
    b.create_connection(0, 4);
    SECTION("Корректное удаление") {
        b.delete_contact(0);
        REQUIRE(b.get_size() == 4);
        REQUIRE(b.get_contacts()[3].get_linked_contact() == nullptr);
    }
    SECTION("Некорректное удаление") {
        REQUIRE_THROWS_AS(b.delete_contact(55), std::invalid_argument);
    }
    delete[] cs;
}

TEST_CASE("Изменение положения") {
    size_t size = 4;
    Contact* cs = init_board(size);
    PCBoard b(cs, size);
    SECTION("Корректное изменение") {
        b.change_position(0, 100, 200);
        REQUIRE(((b.get_contacts()[0].get_x_coordinate() == 100) && (b.get_contacts()[0].get_y_coordinate() == 200)));
    }
    SECTION("Некорректное изменение") {
        REQUIRE_THROWS_AS(b.change_position(0, 11, 6), std::invalid_argument);
        REQUIRE_THROWS_AS(b.change_position(55, 5, 6), std::invalid_argument);
    }
    delete[] cs;
}

TEST_CASE("Сортировка") {
    size_t size = 5;
    Contact* cs = init_board(size);
    cs[0].set_x_coordinate(55);
    cs[2].set_x_coordinate(2);
    cs[3].set_x_coordinate(2);
    cs[4].set_x_coordinate(9);
    PCBoard b(cs, size);
    b.sort_contacts();
    Contact* c = b.get_contacts();
    REQUIRE(c[0].get_x_coordinate() == 2);
    REQUIRE(c[0].get_y_coordinate() == 7);
    REQUIRE(c[1].get_x_coordinate() == 2);
    REQUIRE(c[1].get_y_coordinate() == 8);
    REQUIRE(c[2].get_x_coordinate() == 11);
    REQUIRE(c[3].get_x_coordinate() == 9);
    REQUIRE(c[4].get_x_coordinate() == 55);
    delete[] cs;
}

TEST_CASE("Вывод") {
    size_t size = 4;
    Contact* cs = init_board(size);
    PCBoard b(cs, size);
    REQUIRE_NOTHROW(std::cout << b);
    delete[] cs;
}

TEST_CASE("Ввод") {
    PCBoard b;
    std::istringstream input("1\nin\n7\n8");
    SECTION("Корректный ввод") {
        input >> b;
        REQUIRE(b.get_size() == 1);
    }
    SECTION("Некорректный ввод") {
        std::istringstream in("dsfsdf\ndsfsd\nfdgfd\nfgdfg");
        PCBoard t;
        REQUIRE_THROWS_AS(in >> t, std::invalid_argument);
    }
}

TEST_CASE("дОБАВЛЕНИЕ") {
    PCBoard b;
    string t("in");
    for (int i = 0; i < 9; i++) {
        Contact c(t, 5 + i, 7 + i);
        b += c;
    }
    REQUIRE(b.get_size() == 9);
    REQUIRE(b.get_capacity() == 3 * N);
    Contact c_r(t, 5, 7);
    REQUIRE_THROWS_AS(b += c_r, std::invalid_argument);
}

TEST_CASE("Поиск дальних") {
    size_t size = 4;
    string t("out");
    Contact* cs = init_board(size);
    cs[3].set_contact_type(t);
    cs[2].set_contact_type(t);
    PCBoard b(cs, size);
    REQUIRE_THROWS_AS(b.find_most_distant(), std::invalid_argument);
    b.create_connection(0, 3);
    b.create_connection(1, 2);
    std::pair<int, int> res = b.find_most_distant();
    REQUIRE(res.first == 3);
    REQUIRE(res.second == 0);

    PCBoard b2;
    REQUIRE_THROWS_AS(b2.find_most_distant(), std::invalid_argument);
    delete[] cs;
}

TEST_CASE("Присваивание") {
    size_t size = 4;
    Contact* cs = init_board(size);
    SECTION("Перемещающее присваивание") {
        PCBoard b(cs, size);
        PCBoard b2;
        b2 = std::move(b);
        REQUIRE(b2.get_contacts() != nullptr);
        REQUIRE(b.get_contacts() == nullptr);
        REQUIRE(b2.get_capacity() == (4 + N));
        REQUIRE(b.get_capacity() == 0);
    }
    SECTION("Копирующее присваивание") {
        PCBoard b(cs, size);
        PCBoard b2;
        b2 = b;
        REQUIRE((b2.get_contacts()[2] <=> b.get_contacts()[2]) == std::partial_ordering::equivalent);
        REQUIRE(b2.get_size() == size);
        REQUIRE(b.get_size() == size);
    }
    SECTION("Копирующее в себя") {
        PCBoard b(cs, size);
        b = b;
    }
    delete[] cs;
}
