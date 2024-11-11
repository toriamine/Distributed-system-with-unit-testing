#include "DiagonalMatrix.h"

// Конструктор
template <typename T>
DiagonalMatrix<T>::DiagonalMatrix(size_t rows, size_t cols) : m(rows), n(cols) {
    diagonal.resize(std::min(m, n), 0); // Инициализация вектора диагонали
}

// Оператор доступа к элементу (модифицируемый)
template <typename T>
T& DiagonalMatrix<T>::operator()(size_t i, size_t j) {
    if (i != j) {
        static T zero = 0; // Статическая переменная для возвращения нуля
        return zero; // Возвращаем 0
    }
    return diagonal[i]; // Возвращаем элемент диагонали
}

// Оператор доступа к элементу (константный)
template <typename T>
const T& DiagonalMatrix<T>::operator()(size_t i, size_t j) const {
    if (i != j) {
        static T zero = 0; // Статическая переменная для возвращения нуля
        return zero; // Возвращаем 0
    }
    return diagonal[i]; // Возвращаем элемент диагонали
}

// Метод для получения количества строк
template <typename T>
size_t DiagonalMatrix<T>::rows() const {
    return m; // Возвращаем количество строк
}

// Метод для получения количества столбцов
template <typename T>
size_t DiagonalMatrix<T>::cols() const {
    return n; // Возвращаем количество столбцов
}

// Оператор сложения
template <typename T>
Matrix<T>* DiagonalMatrix<T>::operator+(const Matrix<T>& other) const {
    const DiagonalMatrix<T>* otherDiagonal = dynamic_cast<const DiagonalMatrix<T>*>(&other);

    // Проверяем совместимость размеров
    if (!otherDiagonal || m != otherDiagonal->m || n != otherDiagonal->n) {
        throw std::runtime_error("Matrices have incompatible dimensions for addition");
    }

    DiagonalMatrix<T>* result = new DiagonalMatrix<T>(m, n); // Создаем результирующую матрицу
    for (size_t i = 0; i < std::min(m, n); ++i) {
        (*result)(i, i) = (*this)(i, i) + (*otherDiagonal)(i, i); // Сложение соответствующих диагональных элементов
    }
    return result; // Возвращаем указатель на результат
}


// Оператор вычитания
template <typename T>
Matrix<T>* DiagonalMatrix<T>::operator-(const Matrix<T>& other) const {
    const DiagonalMatrix<T>* otherDiagonal = dynamic_cast<const DiagonalMatrix<T>*>(&other);
    if (!otherDiagonal || m != otherDiagonal->m || n != otherDiagonal->n) {
        throw std::runtime_error("Matrices have incompatible dimensions for subtraction");
    }

    DiagonalMatrix<T>* result = new DiagonalMatrix<T>(m, n); // Создаем результирующую матрицу
    for (size_t i = 0; i < std::min(m, n); ++i) {
        (*result)(i, i) = (*this)(i, i) - (*otherDiagonal)(i, i); // Вычитание соответствующих диагональных элементов
    }
    return result; // Возвращаем указатель на результат
}

// Оператор умножения
template <typename T>
Matrix<T>* DiagonalMatrix<T>::operator*(const Matrix<T>& other) const {
    const DiagonalMatrix<T>* otherDiagonal = dynamic_cast<const DiagonalMatrix<T>*>(&other);
    if (!otherDiagonal || n != otherDiagonal->m) {
        throw std::runtime_error("Matrices have incompatible dimensions for multiplication");
    }

    DiagonalMatrix<T>* result = new DiagonalMatrix<T>(m, otherDiagonal->n); // Создаем результирующую матрицу
    for (size_t i = 0; i < std::min(m, otherDiagonal->n); ++i) {
        (*result)(i, i) = (*this)(i, i) * (*otherDiagonal)(i, i); // Умножение соответствующих диагональных элементов
    }
    return result; // Возвращаем указатель на результат
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

