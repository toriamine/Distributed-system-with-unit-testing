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
    std::vector<std::vector<T>> data;// Полная матрица с нулями на не-диагональных местах
public:
    // Конструктор, который принимает список значений для диагонали
    DiagonalMatrix(std::initializer_list<T> list)
        : diagonalElements(list), data(list.size(), std::vector<T>(list.size(), T(0))) {
        size_t index = 0;
        for (auto& val : list) {
            data[index][index] = val;  // Заполните диагональные элементы
            ++index;
        }
    }

    // Конструктор, который принимает размер и нулевую инициализацию
    DiagonalMatrix(size_t size)
        : diagonalElements(size, T(0)), data(size, std::vector<T>(size, T(0))) {
        for (size_t i = 0; i < size; ++i) {
            data[i][i] = T(0);  // Все элементы по умолчанию нули
        }
    }


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
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    ~DiagonalMatrix() = default; // Деструктор
};