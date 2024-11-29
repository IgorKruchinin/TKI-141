#pragma once
#include "node.h"
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>
/**
 * @brief Односвзяный список
**/
template <typename T>
class List {
    Node<T> *head = nullptr;
    size_t size = 0;
     /**
     * @brief получение указателя на узел списка по индексу
     * @params значение индекса
     * @returns указатель на узел списка по данному индексу
    **/
    Node<T> *toIndex(size_t index)  {
        checkIndex(index);
        size_t current_index = 0;
        Node<T> *current = head;
        while (current_index < index) {
            current = current->next;
            ++current_index;
        }
        return current;
    }
    /**
     * @brief проверка индекса на корректность
     * @params значение проверяемого индекса
    **/
    void checkIndex(size_t index) const {
        if (index > size - 1) throw std::out_of_range("Invalid index!\n");
    }
    /**
     * @brief получение указателя на узел списка по индексу (константный метод)
     * @params значение индекса
     * @returns указатель на узел списка по данному индексу
    **/
    const Node<T> *toIndex(size_t index) const {
        checkIndex(index);
        if (head == nullptr) return nullptr;
        size_t current_index = 0;
        Node<T> *current = head;
        while (current_index < index) {
            current = current->next;
            ++current_index;
        }
        return current;
    }
public:
    /**
     * @brief конструктор без параметров
    **/
    List()  {
        this->head = nullptr;
        this->size = 0;
    }
    /**
     * @brief конструктор
     * @params initializer_list от T
    **/
    List(std::initializer_list<T> lst) {
        if (lst.begin() != lst.end()) {
            for (const auto &elem: lst) {
                this->append(elem);
            }
        }
    }
    /**
     * @brief конструктор копирования
     * @params константная ссылка на другой объект этого класса
    **/
    List(const List<T> &other) {
        if (this != &other) {
            for (size_t i = 0; i < other.size; ++i) {
                this->append(other[i]);
            }
        }
    }
    /**
     * @brief конструктор перемещения
     * @params двойная ссылка на другой объект этого класса
    **/
    List(List<T> &&other) noexcept  {
    if (this != &other) {
        std::swap(this->head, other.head);
        std::swap(this->size, other.size);
        }
    }
    /**
     * @brief копирующий оператор присваивания
     * @params константная ссылка на другой объект этого класса
    **/
    List& operator=(const List<T> &other) {
        if (this != &other) {
            List tmp = List(other);
            *this = std::move(tmp);
        }
        return *this;
    }
    /**
     * @brief оператор присваивания
     * @params двойная ссылка на другой объект этого класса
    **/
    List& operator=(List &&other) noexcept {
        if (this != &other) {
            this->head = other.head;
            other.head = nullptr;
        }
        return *this;
    }
    /**
     * @brief оператор доступа по индексу
     * @params значение индекса
     * @returns ссылка на значение элемента по данному индексу
    **/
    T &operator[](size_t index) {
        checkIndex(index);
        Node<T> *current = toIndex(index);
        return current->value;
    }
    /**
     * @brief константный оператор доступа по индексу
     * @params значение индекса
     * @returns  значение элемента по данному индексу
    **/
    const T operator[](size_t index) const {
        checkIndex(index);
        const Node<T> *current = toIndex(index);
        return current->value;
    }
    /**
     * @brief удаление по данному индексу
     * @params значение индекса
    **/
    void remove(size_t index) {
        checkIndex(index);
        Node<T> *current = toIndex(index - 1);
        Node<T> *tmp = current->next->next;
        delete current->next;
        current->next = tmp;
        size--;
    }
    /**
     * @brief добавление в конец списка
     * @params значение добавляемого элемента
    **/
    void append(T elem)  {
        Node<T> *current = nullptr;
        if (head != nullptr) {
            current = toIndex(size - 1);
            current->next = new Node<T>(elem, nullptr);
        } else {
            head = new Node<T>(elem, nullptr);
        }
        size++;
    }
    /**
     * @brief вставка данного значения элемента по данному индексу
     * @params значение индекса, значение добавляемого элемента
    **/
    void insert(size_t index, T elem) {
        checkIndex(index);
        Node<T> *current = toIndex(index - 1);
        Node<T> *tmp = current->next;
        current->next = new Node<T>(elem, tmp);
        size++;
    }
    /**
     * @brief получение размера списка
     * @params размер списка
    **/
    size_t getSize()  {
        return size;
    }
        /**
     * @brief деструктор
    **/
    ~List()  {
        if (head != nullptr) {
            size_t current_index = 0;
            Node<T> *current = head;
            while (current_index < size - 1) {
                Node<T> *to_delete = current;
                current = current->next;
                delete to_delete;
                ++current_index;
            }
        }
    }
};
