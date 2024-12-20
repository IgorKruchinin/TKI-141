    #include "Matrix.h"
    #include <memory>
    #include <cmath>
    #include <sstream>
    #include "Generator.h"

    /**
     * @brief Конструктор по умолчанию.
     * Инициализирует пустую матрицу.
     */
    miit::algebra::Matrix::Matrix() {}

    /**
     * @brief Конструктор с параметрами.
     * Инициализирует матрицу с заданным количеством строк и столбцов.
     * @param rows Количество строк.
     * @param cols Количество столбцов.
     */
    miit::algebra::Matrix::Matrix(size_t rows, size_t cols)
        : data(rows, std::vector<int>(cols, 0)) {}

    /**
     * @brief Конструктор копирования.
     * Создает копию матрицы.
     * @param other Копируемая матрица.
     */
    miit::algebra::Matrix::Matrix(const Matrix& other)
        : data(other.data) {}

    /**
     * @brief Оператор присваивания (копирование).
     * @param other Копируемая матрица.
     * @return Ссылка на текущий объект.
     */
    miit::algebra::Matrix& miit::algebra::Matrix::operator=(const miit::algebra::Matrix& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    /**
     * @brief Конструктор перемещения.
     * @param other Перемещаемая матрица.
     */
    miit::algebra::Matrix::Matrix(Matrix&& other) noexcept
        : data(std::move(other.data)) {
    }

    /**
     * @brief Оператор присваивания (перемещение).
     * @param other Перемещаемая матрица.
     * @return Ссылка на текущий объект.
     */
    miit::algebra::Matrix& miit::algebra::Matrix::operator=(miit::algebra::Matrix&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
        }
        return *this;
    }

     /**
     * @brief Доступ по индексу константный (получаем отдельную строку таблицы).
     * @param index index.
     * @return Строка таблицы в формате std::vector.
     */
   const std::vector<int>& miit::algebra::Matrix::operator[](size_t index) const {
    return data[index];
   }
   /**
     * @brief Доступ по индексу (получаем отдельную строку таблицы).
     * @param index index.
     * @return Строка таблицы в формате std::vector.
     */
    std::vector<int>& miit::algebra::Matrix::operator[](size_t index) {
      return data[index];
    }

    /**
     * @brief Получить количество строк в матрице.
     * @return Количество строк.
     */
    size_t miit::algebra::Matrix::countRows() const { return data.size(); }

    /**
     * @brief Получить количество столбцов в матрице.
     * @return Количество столбцов.
     */
    size_t miit::algebra::Matrix::countCols() const { 
      if (data.size() == 0) return 0;
      return data[0].size();
    }
         /**
     * @brief Получить максимальный элемент в матрице.
     * @return максимальный элемент в матрице.
     */
    int miit::algebra::Matrix::findMax() {
        int maximum = (*this)[0][0];
        for (size_t i = 0; i < countRows(); ++i) {
           for (size_t j = 0; j < countRows(); ++j) {
                if (std::abs((*this)[i][j]) > maximum) {
                        maximum = (*this)[i][j];
                }
            }
        }
        return maximum;
    }
         /**
     * @brief Получить индекс колонки с максимальным элементом в матрице.
     * @return индекс колонки с максимальным элементом в матрице.
     */
    size_t miit::algebra::Matrix::findMaxColumn() {
        int maximum = (*this)[0][0];
        size_t maxJIdx = 0;
        for (size_t i = 0; i < countRows(); ++i) {
          for (size_t j = 0; j < countCols(); ++j) {
                if (std::abs((*this)[i][j]) > maximum) {
                        maxJIdx = j;
                        maximum = (*this)[i][j];
                }
            }
        }
        return maxJIdx;
}

void miit::algebra::Matrix::fill(std::shared_ptr<Generator> generator) {
	for (size_t i = 0; i < countRows(); ++i) {
		for (size_t j = 0; j < countCols(); ++j) {
			(*this)[i][j] = generator->generate();
		}
	}
}
std::string miit::algebra::Matrix::toString() const {
    std::ostringstream oss;
    for (size_t i = 0; i < countRows(); ++i) {
        for (size_t j = 0; j < countCols(); ++j) {
            oss << (*this)[i][j];  // Доступ к элементам через оператор []
            if (j != countCols() - 1)
                oss << " ";  // Разделитель между элементами
        }
        if (i != countRows() - 1)
            oss << "\n";  // Перевод строки после каждой строки матрицы
    }
    return oss.str();
}

