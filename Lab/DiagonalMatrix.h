#pragma once

#include "Matrix.h"
#include <iostream>
#include <vector>
#include <stdexcept> // Для обработки исключений

// Шаблонный класс для диагональных матриц
template <typename T>
class DiagonalMatrix : public Matrix<T> {
private:

    std::vector<std::vector<T>> data;// Можно было просто задать диагональные элементы,но конструктор блочной матрицы не принимает только диагональные элементы, нужна инициализация полной матрицы)
    
    size_t size;// В диагональной матрице количество строк равно количеству столбцов, поэтому размер один.                        

public:
    // Конструктор, который принимает список значений для диагонали
    DiagonalMatrix(std::initializer_list<T> initializer_list);

    // Конструктор, который принимает размер и нулевую инициализацию
    DiagonalMatrix(size_t Size);

    // Доступ к элементам матрицы
    T& operator()(size_t i, size_t j) override;

    const T& operator()(size_t i, size_t j) const override;

    size_t rows() const;

    size_t cols() const;

    // Операторы сложения, вычитания и умножения
    DiagonalMatrix<T> operator+(const DiagonalMatrix<T>& other) const;

    DiagonalMatrix<T> operator-(const DiagonalMatrix<T>& other) const;

    DiagonalMatrix<T> operator*(const DiagonalMatrix<T>& other) const;

    void Print() const;
};