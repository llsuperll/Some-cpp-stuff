#ifndef BOARD_HPP
#define BOARD_HPP

#include "simple_class.hpp"
#define N 4
namespace BoardLib {

using ContactLib::Contact;

/**
 * @class PCBoard
 * @brief Класс, представляющий печатную плату с контактами
 * 
 * Этот класс хранит массив контактов, его размер и вместимость.
 * Класс предоставляет методы для работы с печатной платой и контактами на ней.
 */
class PCBoard {
    private:
        Contact* contacts;
        size_t size;
        size_t capacity;
        /**
        * @brief Проверяет занято ли место на плате
        * 
        * @return true если место не занято, false в ином случае
        */
        bool check_free_position(Contact& new_contact);
    public:
        /**
        * @brief Конструктор по умолчанию
        * 
        * Инициализирует размер 0, вместимость N, выделяет память под текущую вместимость
        */
        PCBoard();
        /**
        * @brief Конструктор из входного массива контактов
        * @param contacts_arr массив контактов
        * @param size размер входного массива
        * Инициализирует размер size, вместимость size + N, копирует все контакты из массива
        */
        PCBoard(Contact* contacts_arr, size_t size);
        /**
        * @brief Конструктор из одного контакта
        * @param contact контакт
        * Инициализирует размер 1, вместимость N, добавляет контакт
        */
        PCBoard(Contact& contact);
        /**
        * @brief Перемещающий конструктор
        * @param board другая плата
        * Забирает всю начинку из переданной платы в данную
        */
        PCBoard(PCBoard&& board) noexcept;
        /**
        * @brief Копирующий конструктор
        * @param board другая плата
        * Копирует всю начинку из другой платы в данную
        */
        PCBoard(const PCBoard& board);
        
        /**
        * @brief Добавление контакта на плату
        * @param new_contact ссылка на новый контакт
        * @throw std::invalid_argument если место на плате уже занято
        * Добавляет новый контакт на плату
        */
        void operator+=(Contact& new_contact);
        /**
        * @brief Оператор копирования
        * @return Ссылка на скопированную плату
        * 
        * Копирует плату
        */
        PCBoard& operator=(const PCBoard& board);
        /**
        * @brief Оператор присваивания
        * @return Ссылка на плату с 'украденной' начинкой
        * 
        * Переносит данные с переданной платы на данную
        */
        PCBoard& operator=(PCBoard&& board) noexcept;
        
        /**
        * @brief Получить массив контактов на плате
        * @return текущее состояние массива контактов
        */
        Contact* get_contacts();
        /**
        * @brief Получить размер массива контактов
        * @return size
        */
        size_t get_size();
        /**
        * @brief Получить вместимость массива контактов
        * @return capacity
        */
        size_t get_capacity();

        /**
        * @brief Создать связь между контактами
        * @param first_contact номер первого контакта
        * @param second_contact номер второго контакта
        * @throw std::invalid_argument Если какой-либо из контактов уже соединен, либо номер за пределами массива
        * 
        * Создает связь между двумя контактами, заданными номерами.
        */
        void create_connection(int first_contact, int second_contact);
        /**
        * @brief Удалить связь между контактами
        * @param first_contact номер первого контакта
        * @param second_contact номер второго контакта
        * @throw std::invalid_argument если они не соединены, либо номер за пределами массива
        * 
        * Удаляет связь между двумя контактами, заданными номерами.
        */
        void delete_connection(int contact_id);
        /**
        * @brief Удалить контакт
        * @param contact_id номер контакта
        * @throw std::invalid_argument Если номер за пределами массива
        * 
        * Удаляет контакт с платы
        */
        void delete_contact(int contact_id);
        /**
        * @brief Сортирует массив контактов
        * 
        * Сортирует массив контактов по удаленности от начала платы (0, 0)
        */
        void sort_contacts();
        /**
        * @brief Изменить расположение контакта
        * @param contact_id номер контакта
        * @param new_x новая координата х
        * @param new_y новая координата y
        * @throw std::invalid_argument Если новые координаты уже заняты другим контактом
        * 
        * Перемещает контакт на другие координаты
        */
        void change_position(int contact_id, int new_x, int new_y);
        /**
        * @brief Найти наиболее удаленную пару соединенных контактов 
        * @throw std::invalid_argument Если нет соединенных контактов на плате
        * 
        * Находит наиболее удаленную друг от друга пару соединенных контактов
        */
        std::pair<int, int> find_most_distant();
        /**
        * @brief Деструктор
        */
        ~PCBoard();
        
        /**
        * @brief Вывод контакта в поток
        * @param os Выходной поток
        * @param board ссылка на плату для вывода
        * @return Ссылка на выходной поток
        * 
        * Формат вывода: [(x1,y1), ..., (xn, yn`)]
        */
        friend std::ostream& operator<<(ostream& os, PCBoard& board);
        /**
        * @brief Ввод контакта из потока
        * @param in Входной поток
        * @param board ссылка на плату для ввода
        * 
        * @return Ссылка на входной поток
        * 
        * Формат ввода: кол-во контактов\ввод для контакта
        */
        friend std::istream& operator>>(istream& in, PCBoard& board);
};

}

#endif
