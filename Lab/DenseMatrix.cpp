#include "DenseMatrix.h"

// Реализация конструктора
template <typename T>
DenseMatrix<T>::DenseMatrix(size_t rows, size_t cols) : rows_(rows), cols_(cols), data(rows, std::vector<T>(cols, T(0))) {}

template <typename T>
DenseMatrix<T>::DenseMatrix(std::initializer_list<std::initializer_list<T>> list) {
    rows_ = list.size();
    cols_ = (list.size() > 0) ? list.begin()->size() : 0;
    data.resize(rows_);
    size_t i = 0;
    for (auto& row : list) {
        data[i++] = row;
    }

    /*Или просто for (const auto& value : list) {
            diagonalElements.push_back(value);
        }
        //Из Vector
    */
}

// Конструктор копирования
template <typename T>
DenseMatrix<T>::DenseMatrix(const DenseMatrix<T>& other) : rows_(other.rows_), cols_(other.cols_), data(other.data) {}

// Оператор присваивания
template <typename T>
DenseMatrix<T>& DenseMatrix<T>::operator=(const DenseMatrix<T>& other) {
    if (this != &other) {
        rows_ = other.rows_;
        cols_ = other.cols_;
        data = other.data;
    }
    return *this;
}

// Деструктор
template <typename T>
DenseMatrix<T>::~DenseMatrix() {}; // Можно просто использовать default

// Оператор доступа к элементу (модифицируемый)
template <typename T>
T& DenseMatrix<T>::operator()(size_t i, size_t j) {
    if (i >= rows_ || j >= cols_) {
        throw std::out_of_range("Index out of range");
    }
    return data[i][j];
}

// Оператор доступа к элементу (константный)
template <typename T>
const T& DenseMatrix<T>::operator()(size_t i, size_t j) const {
    if (i >= rows_ || j >= cols_) {
        throw std::out_of_range("Index out of range");
    }
    return data[i][j];
}

// Метод получения количества строк
template <typename T>
size_t DenseMatrix<T>::rows() const {
    return rows_;
}

// Метод получения количества столбцов
template <typename T>
size_t DenseMatrix<T>::cols() const {
    return cols_;
}

// Оператор сложения
template <typename T>
DenseMatrix<T> DenseMatrix<T>::operator+(const DenseMatrix<T>& other) const {
    // Проверка на несовместимые размеры
    if (rows() != other.rows()) {
        throw std::invalid_argument("Количество строк в матрицах не совпадает."); // Количество строк не совпадает
    }
    if (cols() != other.cols()) {
        throw std::invalid_argument("Количество столбцов в матрицах не совпадает."); // Количество столбцов не совпадает
    }

    DenseMatrix<T> result(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            result(i, j) = (*this)(i, j) + other(i, j);
        }
    }
    return result;
}

// Оператор вычитания
template <typename T>
DenseMatrix<T> DenseMatrix<T>::operator-(const DenseMatrix<T>& other) const {
    // Проверка на несовместимые размеры
    if (rows() != other.rows()) {
        throw std::invalid_argument("Количество строк в матрицах не совпадает."); // Количество строк не совпадает
    }
    if (cols() != other.cols()) {
        throw std::invalid_argument("Количество столбцов в матрицах не совпадает."); // Количество столбцов не совпадает
    }

    DenseMatrix<T> result(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            result(i, j) = (*this)(i, j) - other(i, j);
        }
    }
    return result;
}

// Оператор умножения
template <typename T>
DenseMatrix<T> DenseMatrix<T>::operator*(const DenseMatrix<T>& other) const {
    // Проверка на несовместимые размеры
    if (rows() != other.rows()) {
        throw std::invalid_argument("Количество строк в матрицах не совпадает."); // Количество строк не совпадает
    }
    if (cols() != other.cols()) {
        throw std::invalid_argument("Количество столбцов в матрицах не совпадает."); // Количество столбцов не совпадает
    }

    DenseMatrix<T> result(rows_, other.cols_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < other.cols_; ++j) {
            result(i, j) = T(0); // Инициализация суммы
            for (size_t k = 0; k < cols_; ++k) {
                result(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }
    return result;
}

// Метод для вывода матрицы
template <typename T>
void DenseMatrix<T>::Print() const {
    std::cout << "Dense Matrix:\n";
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            std::cout << (*this)(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

// Явная инстанциация для типов
// Явная инстанциация для стандартных числовых типов

template class DenseMatrix<int>;                       // int: 32-битное целое число (в большинстве сред).
template class DenseMatrix<unsigned int>;              // unsigned int: Беззнаковое 32-битное целое число.
template class DenseMatrix<short>;                     // short: Обычно 16-битное целое число.
template class DenseMatrix<unsigned short>;            // unsigned short: Беззнаковое 16-битное целое число.
template class DenseMatrix<long>;                       // long: Обычно 32-битное целое, но в некоторых средах это 64-битное целое (например, на 64-разрядных системах).
template class DenseMatrix<unsigned long>;              // unsigned long: Беззнаковое представление long.
template class DenseMatrix<long long>;                 // long long: Гарантирует минимум 64 бита.
template class DenseMatrix<unsigned long long>;        // unsigned long long: Беззнаковое представление long long.
template class DenseMatrix<float>;                      // float: Обычно 32-битное представление числа с плавающей точкой.
template class DenseMatrix<double>;                     // double: Обычно 64-битное представление числа с плавающей точкой.
template class DenseMatrix<long double>;                // long double: Обычно расширенное представление числа с плавающей точкой, минимум 80 бит.
