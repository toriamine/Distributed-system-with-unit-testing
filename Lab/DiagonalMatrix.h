#pragma once
#include "Matrix.h"
#include <iostream>
#include <vector>
#include <stdexcept> // Для обработки исключений

// Шаблонный класс для диагональных матриц
template <typename T>
class DiagonalMatrix : public Matrix<T> {
private:
    std::vector<T> diagonalElements; // Вектор для хранения элементов главной диагонали

public:
    DiagonalMatrix(std::initializer_list<T> list) : diagonalElements(list) {}
    DiagonalMatrix(size_t size) : diagonalElements(size, T(0)) {}

    // Доступ к элементам матрицы
    T& operator()(size_t i, size_t j);
    const T& operator()(size_t i, size_t j) const;

    size_t rows() const { return diagonalElements.size(); }
    size_t cols() const { return diagonalElements.size(); }

    // Операторы сложения, вычитания и умножения
    DiagonalMatrix<T> operator+(const DiagonalMatrix<T>& other) const;
    DiagonalMatrix<T> operator-(const DiagonalMatrix<T>& other) const;
    DiagonalMatrix<T> operator*(const DiagonalMatrix<T>& other) const;

    void Print() const {
        std::cout << "Diagonal Matrix:\n";
        for (size_t i = 0; i < rows(); ++i) {
            for (size_t j = 0; j < cols(); ++j) {
                if (i == j) {
                    std::cout << diagonalElements[i] << " ";
                }
                else {
                    std::cout << "0 ";
                }
            }
            std::cout << std::endl;
        }
    }

    ~DiagonalMatrix() = default; // Деструктор
};