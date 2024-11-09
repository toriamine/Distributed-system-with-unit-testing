#pragma once // Защита от многократного подключения файла

#include <iostream>
#include <vector>
#include <exception> // Для обработки исключений

// Шаблонный класс для диагональных матриц
template <typename T = double>
class DiagonalMatrix {
private:
    size_t m, n; // Количество строк (m) и столбцов (n) в матрице
    std::vector<T> diagonal; // Вектор для хранения элементов главной диагонали

public:
    // Конструктор
    DiagonalMatrix(size_t rows, size_t cols) : m(rows), n(cols) {
        // Инициализация вектора диагонали размером min(m, n)
        // Поскольку элементы вне главной диагонали равны 0
        diagonal.resize(std::min(m, n), 0);
    }

    // Оператор доступа к элементу (модифицируемый)
    T& operator()(size_t i, size_t j) {
        // Если i и j не равны, возвращаем 0 (элементы вне диагонали)
        if (i != j) {
            static T zero = 0; // Статическая переменная для возвращения нуля
            return zero; // Возвращаем 0
        }
        // Если i равно j, возвращаем элемент диагонали по индексу i
        return diagonal[i];
    }

    // Оператор доступа к элементу (константный, недоступный для изменения)
    const T& operator()(size_t i, size_t j) const {
        // Проверка на вне диагональные координаты
        if (i != j) {
            static T zero = 0; // Создаем статическую переменную
            return zero; // Возвращаем 0
        }
        // Возвращаем элемент диагонали
        return diagonal[i];
    }

    // Метод для получения количества строк
    size_t rows() const {
        return m; // Возвращаем количество строк
    }

    // Метод для получения количества столбцов
    size_t cols() const {
        return n; // Возвращаем количество столбцов
    }

    // Оператор сложения двух диагональных матриц
    DiagonalMatrix operator+(const DiagonalMatrix& other) const {
        // Проверка на совместимость размеров
        if (m != other.m || n != other.n) {
            throw std::runtime_error("Matrices have incompatible dimensions");
        }

        DiagonalMatrix result(m, n); // Создаем результатирующую диагональную матрицу
        // Сложение поэлементно только для главной диагонали
        for (size_t i = 0; i < std::min(m, n); ++i) {
            result.diagonal[i] = diagonal[i] + other.diagonal[i]; // Сложение соответствующих диагональных элементов
        }
        return result; // Возвращаем результат
    }

    // Оператор вычитания двух диагональных матриц
    DiagonalMatrix operator-(const DiagonalMatrix& other) const {
        // Проверка на совместимость размеров
        if (m != other.m || n != other.n) {
            throw std::runtime_error("Matrices have incompatible dimensions");
        }

        DiagonalMatrix result(m, n); // Создаем результатирующую матрицу
        // Вычитание поэлементно для главной диагонали
        for (size_t i = 0; i < std::min(m, n); ++i) {
            result.diagonal[i] = diagonal[i] - other.diagonal[i]; // Вычитание соответствующих диагональных элементов
        }
        return result; // Возвращаем результат
    }

    // Оператор умножения двух диагональных матриц
    DiagonalMatrix operator*(const DiagonalMatrix& other) const {
        // Проверка на совместимость размеров для умножения
        if (n != other.m) {
            throw std::runtime_error("Matrices have incompatible dimensions");
        }

        DiagonalMatrix result(m, other.n); // Создаем результирующую матрицу
        // Умножение поэлементно для главной диагонали

        for (size_t i = 0; i < std::min(m, n); ++i) {
            result.diagonal[i] = diagonal[i] * other.diagonal[i]; // Умножение соответствующих диагональных элементов
        }
        return result; // Возвращаем результат
    }
};
