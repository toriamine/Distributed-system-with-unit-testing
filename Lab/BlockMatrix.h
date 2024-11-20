#pragma once // Защита от многократного подключения файла

#include "Matrix.h"
#include "DenseMatrix.h"
#include "DiagonalMatrix.h"
#include <vector>
#include <stdexcept>
#include <iostream>

// Шаблонный класс блочной матрицы
template<typename T, template <typename> class MatrixType>
class BlockMatrix : public Matrix<T> {
private:
    std::vector<std::vector<MatrixType<T>*>> blocks; // Указатели на блоки
    size_t numBlocksRows; // Количество блоков по строкам
    size_t numBlocksCols; // Количество блоков по столбцам
    size_t blockRows;     // Количество строк в каждом блоке
    size_t blockCols;     // Количество столбцов в каждом блоке

public:
    // Конструктор
    BlockMatrix(size_t blockRows, size_t blockCols, size_t rows, size_t cols);

    // Деструктор
    ~BlockMatrix();

    // Установить блок
    void setBlock(size_t row, size_t col, MatrixType<T>* block);

    // Оператор доступа к элементам
    T& operator()(size_t i, size_t j); // Переопределение для доступа к элементам
    const T& operator()(size_t i, size_t j) const; // Переопределение для доступа к элементам

    size_t rows() const override; // Переопределение для количества строк
    size_t cols() const override; // Переопределение для количества столбцов

    void Print() const override; // Печать всей блочной матрицы

    MatrixType<T>& block(size_t row, size_t col) {
        if (!blocks[row][col]) {
            blocks[row][col] = new MatrixType<T>(blockRows, blockCols); // Инициализируем блок, если он не установлен
        }
        return *blocks[row][col];
    }

    // Операторы сложения, вычитания и умножения
    BlockMatrix<T, MatrixType> operator+(const BlockMatrix<T, MatrixType>& other) const;
    BlockMatrix<T, MatrixType> operator-(const BlockMatrix<T, MatrixType>& other) const;
    BlockMatrix<T, MatrixType> operator*(const BlockMatrix<T, MatrixType>& other) const;

    // Метод для вычисления произведения Кронекера
    //BlockMatrix<T, MatrixType> kroneckerProduct(const BlockMatrix<T, MatrixType>& other) const;
};