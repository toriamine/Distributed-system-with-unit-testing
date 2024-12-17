#pragma once

#include "Matrix.h"
#include <iostream>
#include <vector>
#include <stdexcept>

// Шаблонный класс для диагональных матриц
template <typename T>
class DiagonalMatrix : public Matrix<T> {
private:

    // Можно было просто задать диагональные элементы, 
    // но конструктор блочной матрицы не принимает только диагональные элементы, нужна инициализация полной матрицы.
    std::vector<std::vector<T>> data;
    
    size_t size;// В диагональной матрице количество строк равно количеству столбцов, поэтому размер один.                        

public:
    // Конструктор, который принимает список значений для диагонали
    DiagonalMatrix(std::initializer_list<T> initializer_list);

    // Конструктор, который принимает размер и нулевую инициализацию
    DiagonalMatrix(size_t Size);

    // Оператор доступа к элементу для изменения
    T& operator()(size_t i, size_t j) override;

    // Оператор доступа к элементу для чтения
    const T& operator()(size_t i, size_t j) const override;

    // Метод для получения количества строк
    size_t rows() const override;

    // Метод для получения количества столбцов
    size_t cols() const override;

    // Операторы сложения, вычитания и умножения
    DiagonalMatrix<T> operator+(const DiagonalMatrix<T>& other) const;

    DiagonalMatrix<T> operator-(const DiagonalMatrix<T>& other) const;

    DiagonalMatrix<T> operator*(const DiagonalMatrix<T>& other) const;

    // Метод для вывода матрицы
    void Print() const override;
};