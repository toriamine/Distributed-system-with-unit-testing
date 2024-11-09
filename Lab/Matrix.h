#pragma once

#include "DenseMatrix.h"     
#include "DiagonalMatrix.h"  
#include "BlockMatrix.h"     

//Абстрактный класс


// Общие операторы для плотных матриц
template <typename T>
DenseMatrix<T> operator+(const DenseMatrix<T>& a, const DenseMatrix<T>& b) {
    // Перегрузка оператора сложения для плотных матриц
    return a + b; // Если у DenseMatrix есть перегруженные операторы, они вызываются здесь
}

template <typename T>
DenseMatrix<T> operator-(const DenseMatrix<T>& a, const DenseMatrix<T>& b) {
    // Перегрузка оператора вычитания для плотных матриц
    return a - b; // Механизм аналогичен
}

template <typename T>
DenseMatrix<T> operator*(const DenseMatrix<T>& a, const DenseMatrix<T>& b) {
    // Перегрузка оператора умножения для плотных матриц
    return a * b; // Механизм аналогичен
}

// Перегрузка операторов для диагональных матриц
template <typename T>
DiagonalMatrix<T> operator+(const DiagonalMatrix<T>& a, const DiagonalMatrix<T>& b) {
    // Перегрузка оператора сложения для диагональных матриц
    return a + b; // Операция, предполагающая наличие соответствующих методов в DiagonalMatrix
}

template <typename T>
DiagonalMatrix<T> operator-(const DiagonalMatrix<T>& a, const DiagonalMatrix<T>& b) {
    // Перегрузка оператора вычитания для диагональных матриц
    return a - b; // Аналогично
}

template <typename T>
DiagonalMatrix<T> operator*(const DiagonalMatrix<T>& a, const DiagonalMatrix<T>& b) {
    // Перегрузка оператора умножения для диагональных матриц
    return a * b; // Аналогично
}

// Перегрузка операторов для блочных матриц
template <typename T>
BlockMatrix<T> operator+(const BlockMatrix<T>& a, const BlockMatrix<T>& b) {
    // Перегрузка оператора сложения для блочных матриц
    return a + b; // Аналогично
}

template <typename T>
BlockMatrix<T> operator-(const BlockMatrix<T>& a, const BlockMatrix<T>& b) {
    // Перегрузка оператора вычитания для блочных матриц
    return a - b; // Аналогично
}

template <typename T>
BlockMatrix<T> operator*(const BlockMatrix<T>& a, const BlockMatrix<T>& b) {
    // Перегрузка оператора умножения для блочных матриц
    return a * b; // Аналогично
}

// Общие функции для работы с матрицами

template <typename T>
T FrobeniusNorm(const DenseMatrix<T>& matrix) {
    // Реализация функции вычисления нормы Фробениуса
    T sum = 0; // Переменная для накопления суммы квадратов элементов
    for (size_t i = 0; i < matrix.rows(); ++i) {
        for (size_t j = 0; j < matrix.cols(); ++j) {
            sum += matrix(i, j) * matrix(i, j); // Суммируем квадраты элементов
        }
    }
    return std::sqrt(sum); // Возвращаем квадратный корень из суммы
}

template <typename T>
DenseMatrix<T> Transpose(const DenseMatrix<T>& matrix) {
    // Реализация функции транспонирования плотной матрицы
    DenseMatrix<T> result(matrix.cols(), matrix.rows()); // Создаем матрицу с измененной размерностью
    for (size_t i = 0; i < matrix.rows(); ++i) {
        for (size_t j = 0; j < matrix.cols(); ++j) {
            result(j, i) = matrix(i, j); // Транспонируем
        }
    }
    return result; // Возвращаем результирующую матрицу
}

// Перегруженный оператор << для вывода матриц

template <typename T>
std::ostream& operator<<(std::ostream& os, const DenseMatrix<T>& matrix) {
    for (size_t i = 0; i < matrix.rows(); ++i) {
        for (size_t j = 0; j < matrix.cols(); ++j) {

            os << matrix(i, j) << " "; // Выводим элементы в строку
        }
        os << std::endl; // Переходим на следующую строку
    }
    return os; // Возвращаем поток
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const DiagonalMatrix<T>& matrix) {
    for (size_t i = 0; i < matrix.rows(); ++i) {
        for (size_t j = 0; j < matrix.cols(); ++j) {
            if (i == j) {
                os << matrix(i, j) << " "; // Выводим только диагональные элементы
            }
            else {
                os << "0 "; // Остальные элементы равны нулю
            }
        }
        os << std::endl; // Переход на новую строку
    }
    return os; // Возвращаем поток
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const BlockMatrix<T>& matrix) {
    for (size_t i = 0; i < matrix.rows(); ++i) {
        for (size_t j = 0; j < matrix.cols(); ++j) {
            os << matrix(i, j) << " "; // Выводим элементы блоков
        }
        os << std::endl; // Переход на новую строку
    }
    return os; // Возвращаем поток
}
