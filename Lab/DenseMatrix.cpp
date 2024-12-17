#include "DenseMatrix.h"

template <typename T>
DenseMatrix<T>::DenseMatrix(size_t rows, size_t cols) : _rows(rows), _cols(cols), data(rows, std::vector<T>(cols, T(0))) {}

template <typename T>
DenseMatrix<T>::DenseMatrix(std::initializer_list<std::initializer_list<T>> list) {

    // Определяем количество строк как размер инициализирующего списка
    _rows = list.size();

    // Определяем количество столбцов как размер первой строки (если список не пуст)
    _cols = (list.size() > 0) ? list.begin()->size() : 0;

    // Изменяем размер вектора data на количество строк
    data.resize(_rows);

    // Итератор для прохода по каждой строке инициализирующего списка
    typename std::initializer_list<std::initializer_list<T>>::iterator row_it = list.begin();

    // Индекс для прохода по вектору data
    size_t i = 0;

    // Проходим по каждой строке инициализирующего списка
    while (row_it != list.end()) {
        // Присваиваем текущую строку из инициализирующего списка соответствующей строке в data
        data[i++] = *row_it;
        // Переходим к следующей строке
        ++row_it;
    }
}

// Конструктор копирования
template <typename T>
DenseMatrix<T>::DenseMatrix(const DenseMatrix<T>& other) : _rows(other._rows), _cols(other._cols), data(other.data) {}

// Оператор присваивания
template <typename T>
DenseMatrix<T>& DenseMatrix<T>::operator=(const DenseMatrix<T>& other) {
    if (this != &other) {
        _rows = other._rows;
        _cols = other._cols;
        data = other.data;
    }
    return *this;
}

// Деструктор
template <typename T>
DenseMatrix<T>::~DenseMatrix() {};


template <typename T>
T& DenseMatrix<T>::operator()(size_t i, size_t j) {
    if (i >= _rows || j >= _cols) {
        throw std::out_of_range("Индекс вне диапазона.");
    }
    return data[i][j];
}

template <typename T>
const T& DenseMatrix<T>::operator()(size_t i, size_t j) const {
    if (i >= _rows || j >= _cols) {
        throw std::out_of_range("Индекс вне диапазона.");
    }
    return data[i][j];
}

// Метод для получения количества строк
template <typename T>
size_t DenseMatrix<T>::rows() const {
    return _rows;
}

// Метод для получения количества столбцов
template <typename T>
size_t DenseMatrix<T>::cols() const {
    return _cols;
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

    DenseMatrix<T> res(_rows, _cols);

    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j) {
            res(i, j) = (*this)(i, j) + other(i, j);
        }
    }
    return res;

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

    DenseMatrix<T> res(_rows, _cols);

    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j) {
            res(i, j) = (*this)(i, j) - other(i, j);
        }
    }
    return res;

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

    DenseMatrix<T> res(_rows, other._cols);

    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < other._cols; ++j) {
            res(i, j) = T(0); // Инициализация суммы
            for (size_t k = 0; k < _cols; ++k) {
                res(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }
    return res;

}

// Метод для вывода матрицы
template <typename T>
void DenseMatrix<T>::Print() const {

    std::cout << "Dense Matrix:\n";

    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j) {
            std::cout << (*this)(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

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