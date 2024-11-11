#pragma once

#include <iostream>
#include "Matrix.h"
#include <vector>
#include <exception>
#include <initializer_list>

// Определение класса DenseMatrix, унаследованного от Matrix
template <typename T>
class DenseMatrix : public Matrix<T> {
private:
    size_t m, n; // Количество строк и столбцов
    T* data; // Указатель на элементы матрицы

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
    Matrix<T>* operator+(const Matrix<T>& other) const override {
        const DenseMatrix<T>* otherDense = dynamic_cast<const DenseMatrix<T>*>(&other);
        if (!otherDense || m != otherDense->m || n != otherDense->n) {
            throw std::runtime_error("Matrices have incompatible dimensions for addition");
        }

        DenseMatrix<T>* result = new DenseMatrix<T>(m, n); // Создаем результирующую матрицу
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                (*result)(i, j) = (*this)(i, j) + otherDense->operator()(i, j); // Сложение соответствующих элементов
            }
        }
        return result; // Возвращаем указатель на результат
    }


    // Оператор вычитания
    Matrix<T>* operator-(const Matrix<T>& other) const override {
        const DenseMatrix<T>* otherDense = dynamic_cast<const DenseMatrix<T>*>(&other);
        if (!otherDense || m != otherDense->m || n != otherDense->n) {
            throw std::runtime_error("Matrices have incompatible dimensions for subtraction");
        }

        DenseMatrix<T>* result = new DenseMatrix<T>(m, n); // Создаем результирующую матрицу
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                (*result)(i, j) = (*this)(i, j) - otherDense->operator()(i, j); // Вычитание соответствующих элементов
            }
        }
        return result; // Возвращаем указатель на результат
    }

    // Оператор умножения
    Matrix<T>* operator*(const Matrix<T>& other) const override {
        const DenseMatrix<T>* otherDense = dynamic_cast<const DenseMatrix<T>*>(&other);
        if ((!otherDense || m != otherDense->m || n != otherDense->n)) {
            throw std::runtime_error("Matrices have incompatible dimensions for multiplication");
        }

        DenseMatrix<T>* result = new DenseMatrix<T>(m, otherDense->n); // Создаем результирующую матрицу
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < otherDense->n; ++j) {
                (*result)(i, j) = 0; // Инициализация с нуля
                for (size_t k = 0; k < n; ++k) {
                    (*result)(i, j) += (*this)(i, k) * otherDense->operator()(k, j); // Умножение и накопление результата
                }
            }
        }
        return result; // Возвращаем указатель на результат
    }

};

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

/*Этот класс представляет "плотную" матрицу, которая хранит элементы в виде одномерного массива. Он предоставляет функции для:

- Создания матрицы заданных размеров.
- Инициализации матрицы с помощью списков инициализации.
- Копирования объектов с помощью конструктора копирования.
- Операций доступа к элементам через оператор ().
- Операций сложения, вычитания и умножения с проверкой совместимости размерностей.*/