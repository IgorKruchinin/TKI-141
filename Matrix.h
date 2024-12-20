#pragma once
#include <vector>
#include "Generator.h"
#include <memory>
#include <string>
#include <iostream>

namespace miit::algebra {
  class Matrix {
  private:
    std::vector<std::vector<int>> data;
  public:
        /**
     * @brief Конструктор по умолчанию.
     * Инициализирует пустую матрицу.
     */
    Matrix();

    /**
     * @brief Конструктор с параметрами.
     * Инициализирует матрицу с заданным количеством строк и столбцов.
     * @param rows Количество строк.
     * @param cols Количество столбцов.
     */
    Matrix(size_t rows, size_t cols);

    /**
     * @brief Конструктор копирования.
     * Создает копию матрицы.
     * @param other Копируемая матрица.
     */
    Matrix(const Matrix& other);

    /**
     * @brief Оператор присваивания (копирование).
     * @param other Копируемая матрица.
     * @return Ссылка на текущий объект.
     */
    Matrix& operator=(const Matrix& other);

    /**
     * @brief Конструктор перемещения.
     * @param other Перемещаемая матрица.
     */
    Matrix(Matrix&& other) noexcept;

    /**
     * @brief Оператор присваивания (перемещение).
     * @param other Перемещаемая матрица.
     * @return Ссылка на текущий объект.
     */
    Matrix& operator=(Matrix&& other) noexcept;
    /**
     * @brief Доступ по индексу константный (получаем отдельную строку таблицы).
     * @param index index.
     * @return Строка таблицы в формате std::vector.
     */
    const std::vector<int>& operator[](size_t index) const;
    /**
     * @brief Доступ по индексу (получаем отдельную строку таблицы).
     * @param index index.
     * @return Строка таблицы в формате std::vector.
     */
    std::vector<int>& operator[](size_t index);

    /**
     * @brief Получить количество строк в матрице.
     * @return Количество строк.
     */
    size_t countRows() const;

    /**
     * @brief Получить количество столбцов в матрице.
     * @return Количество столбцов.
     */
    size_t countCols() const;
       /**
     * @brief Получить максимальный элемент в матрице.
     * @return максимальный элемент в матрице.
     */
    int findMax();
     /**
     * @brief Получить индекс колонки с максимальным элементом в матрице.
     * @return индекс колонки с максимальным элементом в матрице.
     */
    size_t findMaxColumn();
    /**
     * @brief Заполняем матрицу при помощи generator.
     * @param generator - генератор ввода-вывода
     * @return индекс колонки с максимальным элементом в матрице.
     */
    void fill(std::shared_ptr<Generator> generator);
       /**
     * @brief Вывод в строку.
     * @return строка.
     */
    std::string toString() const;
       /**
     * @brief Вывод в ostream.
     */
friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
      os << matrix.toString();
      return os;
}
    
  };
}
