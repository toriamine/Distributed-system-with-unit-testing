#pragma once

// Абстрактный класс для матриц

template <typename T>
class Matrix {
public:
    virtual size_t rows() const = 0;

    virtual size_t cols() const = 0;

    // У всех матриц есть оператор доступа
   
    // Первый оператор доступа используется для изменения
    virtual T& operator()(size_t i, size_t j) = 0;

    // Второй оператор доступа используется для чтения
    virtual const T& operator()(size_t i, size_t j) const = 0;

    virtual void Print() const = 0;

    virtual ~Matrix() {}; // Виртуальный деструктор
};