#pragma once // Защита от многократного подключения файла

#include "Matrix.h"
#include <iostream>
#include <vector>
#include <exception> // Для обработки исключений

// Шаблонный класс для диагональных матриц
template <typename T>
class DiagonalMatrix : public Matrix<T> {
private:
    size_t m, n; // Количество строк (m) и столбцов (n) в матрице
    std::vector<T> diagonal; // Вектор для хранения элементов главной диагонали

public:
    // Конструктор
    DiagonalMatrix(size_t rows, size_t cols);

    // Оператор доступа к элементу (модифицируемый)
    T& operator()(size_t i, size_t j) override;

    // Оператор доступа к элементу (константный)
    const T& operator()(size_t i, size_t j) const override;

    // Метод для получения количества строк
    size_t rows() const override;

    // Метод для получения количества столбцов
    size_t cols() const override;

    // Оператор сложения
    Matrix<T>* operator+(const Matrix<T>& other) const override;

    // Оператор вычитания
    Matrix<T>* operator-(const Matrix<T>& other) const override;

    // Оператор умножения
    Matrix<T>* operator*(const Matrix<T>& other) const override;

    // Оператор вывода в поток
    friend std::ostream& operator<<(std::ostream& os, const DiagonalMatrix<T>& matrix) {
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

    // Виртуальный деструктор
    ~DiagonalMatrix() override = default;
};
