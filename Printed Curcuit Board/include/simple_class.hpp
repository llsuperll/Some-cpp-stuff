#ifndef SIMPLE_CLASS_HPP
#define SIMPLE_CLASS_HPP

#include <string>
#include <iostream>
using std::string;
using std::istream;
using std::ostream;

namespace ContactLib {

enum class ContactType {
    IN = 0,
    OUT = 1,
};

/**
 * @class Contact
 * @brief Класс для представления контакта на печатной плате
 * 
 * Этот класс хранит информацию о контакте: его тип, координаты и указатель на соединенный контакт.
 * Класс предоставляет методы для работы с контактами.
 */
class Contact {
    private:
        ContactType contact_type;
        int x;
        int y;
        Contact* linked_contact;
        
        /**
        * @brief Определяет обратный тип контакта
        * 
        * Если тип контакта in, возвращает out, и наоборот
        */
        ContactType define_type(const Contact& link_contact);
        /**
        * @brief Конвертирует тип из строки в IN(0)/OUT(1)
        * 
        * Если тип контакта 'in', возвращает IN(0), если 'out' - OUT(1)
        */
        ContactType convert_type(string& type);
        /**
        * @brief Конвертирует тип из enum в строковое представление
        * 
        * Если тип контакта IN(0) возвращает 'IN', если OUT(1) - 'OUT'
        */
        static string to_string(ContactType type);
    
    public:
        /**
        * @brief Конструктор по умолчанию
        * 
        * Устанавливает тип OUT, x = 0, y = 0, соединенный контакт nullptr
        */
        Contact();
        /**
        * @brief Конструктор контакта с заданным типом
        * @param type строка тип контакта in, out
        * @param x Координата х
        * @param y Координата y
        * @throw std::invalid_argument Если тип не in, out
        */
        Contact(string& type, int x_coordinate, int y_coordinate);
        /**
        * @brief Конструктор контакта с заданным соединенным контактом
        * @param linked Соединенный контакт
        * @param x Координата х
        * @param y Координата y
        * @throw std::invalid_argument Если linked уже соединен с другим контактом
        */
        Contact(int x_coordinate, int y_coordinate, Contact& linked);
        /**
        * @brief Поиск расстояния контакта от начала платы (0, 0)
        * @param x Координата х
        * @param y Координата y
        * @return возвращает расстояние контакта от (0,0)
        */
        static double find_distance(int x, int y);
        /**
        * @brief Подсчет задержки сигнала между соединенными контактами
        * @param contact Соединенный контакт
        * @throw std::invalid_argument Если контакты не соединены
        * @return возвращает время задержки сигнала
        */
        double count_latency(Contact& contact);
        /**
        * @brief Соединение двух контактов
        * @param link_contact Контакт выбранный для соединения с текущим
        * @param x Координата х
        * @param y Координата y
        * @throw std::invalid_argument Если link_contact или текущий контакт уже соединен с другим контактом
        */
        void operator>>(Contact& link_contact);
        /**
        * @brief Разрыв связи между контактами
        * @param link_contact Контакт выбранный для разрыва связи
        * @throw std::invalid_argument Если контакты не соединены
        */
        void operator<<(Contact* link_contact);
        /**
        * @brief Сравнение двух контактов по удаленности от начала платы
        * @param contact Другой контакт
        * @return результат сравнения
        */
        std::partial_ordering operator<=>(Contact& contact);
        /**
        * @brief Получить координату х
        * @return x coord
        */
        int get_x_coordinate();
        /**
        * @brief Получить координату y
        * @return y coord
        */
        int get_y_coordinate();
        /**
        * @brief Получить тип контакта
        * @return тип контакта
        */
        ContactType get_contact_type();
        /**
        * @brief Получить соединенный контакт
        * @return текущий соединенный контакт
        */
        Contact* get_linked_contact();
        /**
        * @brief Установить координату х
        * @param x_coordinate Новая координата х
        * 
        * Устанавливает новую координату х
        */
        void set_x_coordinate(int x_coordinate);
        /**
        * @brief Установить координату y
        * @param x_coordinate Новая координата y
        * 
        * Устанавливает новую координату y
        */
        void set_y_coordinate(int y_coordinate);
        /**
        * @brief Установить тип контакта
        * @param x_coordinate Новый тип контакта
        * 
        * Устанавливает новый тип контакта
        */
        void set_contact_type(string& type);
        /**
        * @brief Ввод контакта из потока
        * @param in Входной поток
        * @param contact ссылка на контакт для ввода
        * 
        * @return Ссылка на входной поток
        * 
        * Формат ввода тип\nx_coord\ny_coord
        */
        friend istream& operator>>(istream& in, Contact& contact);
        /**
        * @brief Вывод контакта в поток
        * @param os Выходной поток
        * @param contact ссылка на контакт для вывода
        * @return Ссылка на выходной поток
        * 
        * Формат вывода Контакт(x, y) + если есть соединенный, его координаты
        */
        friend ostream& operator<<(ostream& os, Contact& contact);
};

}

#endif
