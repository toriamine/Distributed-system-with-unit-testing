#pragma once // Защита от многократного подключения файла

#include "Matrix.h"
#include <iostream>
#include <vector>
#include <exception> // Для обработки исключений

// Шаблонный класс для диагональных матриц
template <typename T = double>
class DiagonalMatrix : public Matrix<T> {
private:
    size_t m, n; // Количество строк (m) и столбцов (n) в матрице
    std::vector<T> diagonal; // Вектор для хранения элементов главной диагонали

public:
    // Конструктор
    DiagonalMatrix(size_t rows, size_t cols) : m(rows), n(cols) {
        diagonal.resize(std::min(m, n), 0); // Инициализация вектора диагонали
    }

    // Оператор доступа к элементу (модифицируемый)
    T& operator()(size_t i, size_t j) override {
        if (i != j) {
            static T zero = 0; // Статическая переменная для возвращения нуля
            return zero; // Возвращаем 0
        }
        return diagonal[i]; // Возвращаем элемент диагонали
    }

    // Оператор доступа к элементу (константный)
    const T& operator()(size_t i, size_t j) const override {
        if (i != j) {
            static T zero = 0; // Статическая переменная для возвращения нуля
            return zero; // Возвращаем 0
        }
        return diagonal[i]; // Возвращаем элемент диагонали
    }

    // Метод для получения количества строк
    size_t rows() const override {
        return m; // Возвращаем количество строк
    }

    // Метод для получения количества столбцов
    size_t cols() const override {
        return n; // Возвращаем количество столбцов
    }

    // Оператор для Matrix
    Matrix<T>* operator+(const Matrix<T>& other) const override {
        const DiagonalMatrix<T>* otherDiagonal = dynamic_cast<const DiagonalMatrix<T>*>(&other);
        if (!otherDiagonal || m != otherDiagonal->m || n != otherDiagonal->n) {
            throw std::runtime_error("Matrices have incompatible dimensions");
        }

        DiagonalMatrix<T>* result = new DiagonalMatrix<T>(m, n); // Создаем результирующую матрицу
        for (size_t i = 0; i < std::min(m, n); ++i) {
            (*result)(i, i) = (*this)(i, i) + (*otherDiagonal)(i, i); // Сложение соответствующих диагональных элементов
        }
        return result; // Возвращаем указатель на результат
    }

    // Оператор вычитания двух диагональных матриц
    Matrix<T>* operator-(const Matrix<T>& other) const override {
        const DiagonalMatrix<T>* otherDiagonal = dynamic_cast<const DiagonalMatrix<T>*>(&other);
        if (!otherDiagonal || m != otherDiagonal->m || n != otherDiagonal->n) { // Исправлено условие с логическими операторами
            throw std::runtime_error("Matrices have incompatible dimensions for subtraction");
        }

        DiagonalMatrix<T>* result = new DiagonalMatrix<T>(m, n); // Создаем результирующую матрицу
        for (size_t i = 0; i < std::min(m, n); ++i) {
            (*result)(i, i) = (*this)(i, i) - (*otherDiagonal)(i, i); // Вычитание соответствующих диагональных элементов
        }
        return result; // Возвращаем указатель на результат
    }

    // Оператор умножения двух диагональных матриц
    Matrix<T>* operator*(const Matrix<T>& other) const override {
        const DiagonalMatrix<T>* otherDiagonal = dynamic_cast<const DiagonalMatrix<T>*>(&other);
        if (!otherDiagonal || n != otherDiagonal->m) { // Исправлено условие для совместимости
            throw std::runtime_error("Matrices have incompatible dimensions for multiplication");
        }

        DiagonalMatrix<T>* result = new DiagonalMatrix<T>(m, otherDiagonal->n); // Создаем результирующую матрицу
        for (size_t i = 0; i < std::min(m, otherDiagonal->n); ++i) {
            (*result)(i, i) = (*this)(i, i) * (*otherDiagonal)(i, i); // Умножение соответствующих диагональных элементов
        }
        return result; // Возвращаем указатель на результат
    }


    // Виртуальный деструктор
    ~DiagonalMatrix() override = default;
};

// Оператор вывода для диагональной матрицы
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
