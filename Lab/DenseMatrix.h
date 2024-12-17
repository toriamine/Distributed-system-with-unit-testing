#pragma once

#include "Matrix.h"
#include <vector>
#include <initializer_list>
#include <stdexcept>
#include <iostream>

template <typename T>
class DenseMatrix : public Matrix<T> {
private:
    size_t _rows, _cols; // Количество строк и столбцов
    std::vector<std::vector<T>> data;

public:
    // Конструктор для заданного количества строк и столбцов
    DenseMatrix(size_t rows, size_t cols);

    // Конструктор с использованием инициализирующих списков
    DenseMatrix(std::initializer_list<std::initializer_list<T>> list);

    // Конструктор копирования
    DenseMatrix(const DenseMatrix<T>& other);

    // Оператор присваивания
    DenseMatrix<T>& operator=(const DenseMatrix<T>& other);

    // Оператор доступа к элементу для изменения
    T& operator()(size_t i, size_t j) override;

    // Оператор доступа к элементу для чтения
    const T& operator()(size_t i, size_t j) const override;

    // Метод для получения количества строк
    size_t rows() const override;

    // Метод для получения количества столбцов
    size_t cols() const override;

    // Оператор сложения
    DenseMatrix<T> operator+(const DenseMatrix<T>& other) const;

    // Оператор вычитания
    DenseMatrix<T> operator-(const DenseMatrix<T>& other) const;

    // Оператор умножения
    DenseMatrix<T> operator*(const DenseMatrix<T>& other) const;

    // Метод для вывода матрицы
    void Print() const override;

    // Деструктор
    ~DenseMatrix() override; 
};

/*
Этот класс представляет "плотную" матрицу, которая хранит элементы в виде двумерного массива.
В этом классе представлены функции:
1) Создания матрицы заданных размеров.
2) Инициализации матрицы с помощью списков инициализации.
3) Копирования объектов с помощью конструктора копирования.
4) Операций доступа к элементам через оператор ().
5) Операций сложения, вычитания и умножения с проверкой совместимости размерностей.
*/