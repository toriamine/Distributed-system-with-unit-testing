#include "DiagonalMatrix.h"

// Реализация операторов
   // Доступ к элементам матрицы
template <typename T>
T& DiagonalMatrix<T>::operator()(size_t i, size_t j) {
    if (i >= rows() || j >= cols()) {
        throw std::out_of_range("Index out of range");
    }
    return data[i][j];
}

template <typename T>
const T& DiagonalMatrix<T>::operator()(size_t i, size_t j) const {
    if (i >= rows() || j >= cols()) {
        throw std::out_of_range("Index out of range");
    }
    return data[i][j];
}

template <typename T>
DiagonalMatrix<T> DiagonalMatrix<T>::operator+(const DiagonalMatrix<T>& other) const {
    // Проверка на несовместимые размеры
    if (rows() != other.rows()) {
        throw std::invalid_argument("Количество строк в матрицах не совпадает."); // Количество строк не совпадает
    }
    if (cols() != other.cols()) {
        throw std::invalid_argument("Количество столбцов в матрицах не совпадает."); // Количество столбцов не совпадает
    }

    DiagonalMatrix<T> result(rows());
    for (size_t i = 0; i < rows(); ++i) {
        result(i, i) = diagonalElements[i] + other.diagonalElements[i];
    }
    return result;
}

template <typename T>
DiagonalMatrix<T> DiagonalMatrix<T>::operator-(const DiagonalMatrix<T>& other) const {
    // Проверка на несовместимые размеры
    if (rows() != other.rows()) {
        throw std::invalid_argument("Количество строк в матрицах не совпадает."); // Количество строк не совпадает
    }
    if (cols() != other.cols()) {
        throw std::invalid_argument("Количество столбцов в матрицах не совпадает."); // Количество столбцов не совпадает
    }

    DiagonalMatrix<T> result(rows());
    for (size_t i = 0; i < rows(); ++i) {
        result(i, i) = diagonalElements[i] - other.diagonalElements[i];
    }
    return result;
}

template <typename T>
DiagonalMatrix<T> DiagonalMatrix<T>::operator*(const DiagonalMatrix<T>& other) const {

    // Проверка на несовместимые размеры (число столбцов первой должно совпадать с числом строк второй)
    if (cols() != other.rows()) {
        throw std::invalid_argument("Количество столбцов первой матрицы должно совпадать с количеством строк второй матрицы."); // Проверка совместимости для умножения
    }

    DiagonalMatrix<T> result(rows());
    for (size_t i = 0; i < rows(); ++i) {
        result(i, i) = diagonalElements[i] * other.diagonalElements[i];
    }
    return result;
}


// Явная инстанциация для типов
// Явная инстанциация для стандартных числовых типов

template class DiagonalMatrix<int>;                       // int: 32-битное целое число (в большинстве сред).
template class DiagonalMatrix<unsigned int>;              // unsigned int: Беззнаковое 32-битное целое число.
template class DiagonalMatrix<short>;                     // short: Обычно 16-битное целое число.
template class DiagonalMatrix<unsigned short>;            // unsigned short: Беззнаковое 16-битное целое число.
template class DiagonalMatrix<long>;                       // long: Обычно 32-битное целое, но в некоторых средах это 64-битное целое (например, на 64-разрядных системах).
template class DiagonalMatrix<unsigned long>;              // unsigned long: Беззнаковое представление long.
template class DiagonalMatrix<long long>;                 // long long: Гарантирует минимум 64 бита.
template class DiagonalMatrix<unsigned long long>;        // unsigned long long: Беззнаковое представление long long.
template class DiagonalMatrix<float>;                      // float: Обычно 32-битное представление числа с плавающей точкой.
template class DiagonalMatrix<double>;                     // double: Обычно 64-битное представление числа с плавающей точкой.
template class DiagonalMatrix<long double>;                // long double: Обычно расширенное представление числа с плавающей точкой, минимум 80 бит.

