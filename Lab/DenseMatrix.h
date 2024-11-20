#pragma once // Защита от многократного подключения файла

#include "Matrix.h"
#include <vector>
#include <initializer_list>
#include <stdexcept>
#include <iostream>

template <typename T>
class DenseMatrix : public Matrix<T> {
private:
    size_t rows_, cols_; // Количество строк и столбцов
    std::vector<std::vector<T>> data; // Данные матрицы

public:
    // Конструктор для заданного количества строк и столбцов
    DenseMatrix(size_t rows, size_t cols);

    // Конструктор с использованием инициализирующих списков
    DenseMatrix(std::initializer_list<std::initializer_list<T>> list);

    // Конструктор копирования
    DenseMatrix(const DenseMatrix<T>& other);

    // Оператор присваивания
    DenseMatrix<T>& operator=(const DenseMatrix<T>& other);

    ~DenseMatrix() override; // Деструктор

    // Оператор доступа к элементу (модифицируемый)
    T& operator()(size_t i, size_t j);

    // Оператор доступа к элементу (константный)
    const T& operator()(size_t i, size_t j) const;

    // Метод получения количества строк
    size_t rows() const override;

    // Метод получения количества столбцов
    size_t cols() const override;

    // Оператор сложения
    DenseMatrix<T> operator+(const DenseMatrix<T>& other) const;

    // Оператор вычитания
    DenseMatrix<T> operator-(const DenseMatrix<T>& other) const;

    // Оператор умножения
    DenseMatrix<T> operator*(const DenseMatrix<T>& other) const;

    // Метод для вывода матрицы
    void Print() const override;
};



/*Этот класс представляет "плотную" матрицу, которая хранит элементы в виде одномерного массива. Он предоставляет функции для:

- Создания матрицы заданных размеров.
- Инициализации матрицы с помощью списков инициализации.
- Копирования объектов с помощью конструктора копирования.
- Операций доступа к элементам через оператор ().
- Операций сложения, вычитания и умножения с проверкой совместимости размерностей.*/