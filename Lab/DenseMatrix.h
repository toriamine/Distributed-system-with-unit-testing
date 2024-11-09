#pragma once

#include <iostream>
#include <vector>
#include <exception>
#include <initializer_list>

template <typename T = double>
class DenseMatrix {
private:
    size_t m, n; // m - количество строк, n - количество колонок
    T* data; // указатель на элементы матрицы

public:
    // Конструктор с указанием количества строк и колонок
    DenseMatrix(size_t rows, size_t cols)
        : m(rows), n(cols) {
        data = new T[m * n]; // Выделение памяти для хранения элементов
        std::fill(data, data + m * n, static_cast<T>(0)); // Инициализация нулями
    }

    // Конструктор с использованием инициализирующих списков
    DenseMatrix(std::initializer_list<std::initializer_list<T>> values)
        : m(values.size()), n(values.begin()->size()) {
        data = new T[m * n]; // Выделение памяти
        size_t i = 0;
        // Заполнение матрицы элементами из инициализирующего списка
        for (const auto& row : values) {
            size_t j = 0;
            for (const auto& value : row) {
                (*this)(i, j) = value; // Доступ через оператор
                ++j;
            }
            ++i;
        }
    }

    // Конструктор копирования
    DenseMatrix(const DenseMatrix& other)
        : m(other.m), n(other.n) {
        data = new T[m * n]; // Выделение памяти
        std::copy(other.data, other.data + m * n, data); // Копирование данных
    }

    // Оператор присваивания
    DenseMatrix& operator=(const DenseMatrix& other) {
        if (this != &other) { // Проверка на самоприсваивание
            delete[] data; // Освобождение предыдущих ресурсов
            m = other.m;
            n = other.n;
            data = new T[m * n]; // Выделение памяти
            std::copy(other.data, other.data + m * n, data); // Копирование данных
        }
        return *this;
    }

    // Деструктор для освобождения ресурсов
    ~DenseMatrix() {
        delete[] data; // Освобождение памяти, выделенной под данные
    }

    // Доступ к элементам с использованием операторов ()
    T& operator()(size_t i, size_t j) {
        return data[i * n + j]; // Расчёт индекса в одномерном массиве
    }

    const T& operator()(size_t i, size_t j) const {
        return data[i * n + j];
    }

    // Получение количества строк и колонок
    size_t rows() const { return m; }
    size_t cols() const { return n; }

    // Оператор сложения
    DenseMatrix operator+(const DenseMatrix& other) const {
        // Проверка совместимости размеров
        if (m != other.m || n != other.n) {
            throw std::runtime_error("Matrices have incompatible dimensions for addition");
        }

        DenseMatrix result(m, n); // Результирующая матрица
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                result(i, j) = (*this)(i, j) + other(i, j); // Сложение соответствующих элементов
            }
        }
        return result; // Возврат результата
    }

    // Оператор вычитания
    DenseMatrix operator-(const DenseMatrix& other) const {
        // Проверка совместимости размеров
        if (m != other.m || n != other.n) {
            throw std::runtime_error("Matrices have incompatible dimensions for subtraction");
        }

        DenseMatrix result(m, n); // Результирующая матрица
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                result(i, j) = (*this)(i, j) - other(i, j); // Вычитание соответствующих элементов
            }
        }

        return result; // Возврат результата
    }

    // Оператор умножения
    DenseMatrix operator*(const DenseMatrix& other) const {
        // Проверка совместимости размеров для умножения
        if (n != other.m) {
            throw std::runtime_error("Matrices have incompatible dimensions for multiplication");
        }

        DenseMatrix result(m, other.n); // Результирующая матрица
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < other.n; ++j) {
                result(i, j) = 0; // Инициализация с нуля
                for (size_t k = 0; k < n; ++k) {
                    result(i, j) += (*this)(i, k) * other(k, j); // Умножение и накопление результата
                }
            }
        }
        return result; // Возврат результата
    }

    // Метод для Кронекерова произведения
    /*DenseMatrix KroneckerProduct(const DenseMatrix& other) const {
        // Результирующая матрица будет размером (m * m') x (n * n')
        DenseMatrix result(m * other.m, n * other.n);

        // Итерация по элементам текущей матрицы
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                T a_ij = (*this)(i, j); // Текущий элемент
                // Умножение текущего элемента на всю матрицу other
                for (size_t k = 0; k < other.m; ++k) {
                    for (size_t l = 0; l < other.n; ++l) {
                        result(i * other.m + k, j * other.n + l) = a_ij * other(k, l);
                    }
                }
            }
        }
        return result; // Возврат результирующей матрицы
    }*/
};


/*Этот класс представляет "плотную" матрицу, которая хранит элементы в виде одномерного массива. Он предоставляет функции для:

- Создания матрицы заданных размеров.
- Инициализации матрицы с помощью списков инициализации.
- Копирования объектов с помощью конструктора копирования.
- Операций доступа к элементам через оператор ().
- Операций сложения, вычитания и умножения с проверкой совместимости размерностей.*/