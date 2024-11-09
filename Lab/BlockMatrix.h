#pragma once

#include <iostream>
#include <vector>
#include <exception>
#include "DenseMatrix.h"

template <typename T = double>
class BlockMatrix {
private:
    size_t m, n; // Количество строк и столбцов блоков
    std::vector<std::vector<DenseMatrix<T>*>> blocks; // Вектор векторов указателей на блоки матриц

public:
    // Конструктор для создания блоков матриц
    BlockMatrix(size_t rows, size_t cols, size_t blockRows, size_t blockCols)
        : m(rows), n(cols) {
        // Инициализация блоков
        blocks.resize(m);
        for (size_t i = 0; i < m; ++i) {
            blocks[i].resize(n);
            for (size_t j = 0; j < n; ++j) {
                blocks[i][j] = new DenseMatrix<T>(blockRows, blockCols);
            }
        }
    }

    // Деструктор для освобождения памяти
    ~BlockMatrix() {
        // Освобождаем память, выделенную под блоки
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                delete blocks[i][j]; // Удаляем каждый блок
            }
        }
    }

    // Оператор доступа к блоку матриц по индексам
    DenseMatrix<T>& operator()(size_t i, size_t j) {
        return *blocks[i][j]; // Возвращает ссылку на блок
    }

    const DenseMatrix<T>& operator()(size_t i, size_t j) const {
        return *blocks[i][j]; // Возвращает константную ссылку для неизменяемого доступа
    }

    // Оператор присваивания
    BlockMatrix& operator=(const BlockMatrix& other) {
        if (this != &other) { // Проверка на самоприсваивание
            // Освобождаем память текущих блоков
            for (size_t i = 0; i < m; ++i) {
                for (size_t j = 0; j < n; ++j) {
                    delete blocks[i][j]; // Удаляем каждый блок
                }
            }

            // Установка новых размеров и создание блоков
            m = other.m;
            n = other.n;
            blocks.resize(m);
            for (size_t i = 0; i < m; ++i) {
                blocks[i].resize(n);
                for (size_t j = 0; j < n; ++j) {
                    blocks[i][j] = new DenseMatrix<T>(other(i, j).rows(), other(i, j).cols());
                }
            }

            // Копируем существующие блоки
            for (size_t i = 0; i < m; ++i) {
                for (size_t j = 0; j < n; ++j) {
                    (*this)(i, j) = other(i, j); // Копируем содержимое каждого блока
                }
            }
        }
        return *this; // Возвращаем ссылку на текущий объект
    }

    // Метод для получения количества строк
    size_t rows() const {
        return m; // Возвращает количество блоков по строкам
    }

    // Метод для получения количества столбцов
    size_t cols() const {
        return n; // Возвращает количество блоков по столбцам
    }

    // Оператор сложения блоков
    BlockMatrix operator+(const BlockMatrix& other) const {
        if (m != other.m || n != other.n) {
            throw std::runtime_error("Matrices have incompatible dimensions");
        }

        BlockMatrix result(m, n, (*this)(0, 0).rows(), (*this)(0, 0).cols());
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                result(i, j) = (*this)(i, j) + other(i, j); // Сложение блоков
            }
        }
        return result; // Возвращает результирующую блочную матрицу
    }

    // Оператор вычитания блоков
    BlockMatrix operator-(const BlockMatrix& other) const {

        if (m != other.m || n != other.n) {
            throw std::runtime_error("Matrices have incompatible dimensions");
        }

        BlockMatrix result(m, n, (*this)(0, 0).rows(), (*this)(0, 0).cols());
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                result(i, j) = (*this)(i, j) - other(i, j); // Вычитание блоков
            }
        }
        return result; // Возвращает результирующую блочную матрицу
    }

    // Оператор умножения блоков
    BlockMatrix operator*(const BlockMatrix& other) const {
        if (n != other.m) {
            throw std::runtime_error("Matrices have incompatible dimensions");
        }

        BlockMatrix result(m, other.n, (*this)(0, 0).rows(), (*this)(0, 0).cols());
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < other.n; ++j) {
                for (size_t k = 0; k < n; ++k) {
                    result(i, j) = result(i, j) + (*this)(i, k) * other(k, j); // Умножение матриц
                }
            }
        }
        return result; // Возвращает результирующую блочную матрицу
    }

    // Метод для вычисления произведения Кронекера
    BlockMatrix<T> KroneckerProduct(const BlockMatrix<T>& other) const;
};

// Реализация метода Кронекера
template <typename T>
BlockMatrix<T> BlockMatrix<T>::KroneckerProduct(const BlockMatrix<T>& other) const {
    size_t newM = m * other.m; // Новое количество строк
    size_t newN = n * other.n; // Новое количество столбцов
    size_t blockRows = (*this)(0, 0).rows(); // Количество строк в блоках
    size_t blockCols = other(0, 0).cols(); // Количество столбцов в блоках

    BlockMatrix<T> result(newM, newN, blockRows, blockCols); // Результирующая матрица

    // Итерация по всем блокам оригинальной и другой блочной матрицы
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            const DenseMatrix<T>& aBlock = (*this)(i, j); // Текущий блок из текущей матрицы
            const DenseMatrix<T>& bBlock = other(i, j); // Текущий блок из другой матрицы

            // Умножение блока a на каждую ячейку блока b
            for (size_t k = 0; k < other.m; ++k) {
                for (size_t l = 0; l < other.n; ++l) {
                    const DenseMatrix<T>& bBlock = other(k, l);
                    for (size_t bi = 0; bi < blockRows; ++bi) {
                        for (size_t bj = 0; bj < blockCols; ++bj) {
                            T value = aBlock(bi, bj) * bBlock(bi, bj);
                            size_t resultRow = i * other.m + k;
                            size_t resultCol = j * other.n + l;

                            std::cout << "Setting result[" << resultRow << "][" << resultCol
                                << "][" << bi << "][" << bj << "] = "
                                << value << " (from " << aBlock(bi, bj) << " * "
                                << bBlock(bi, bj) << ")\n";

                            result(resultRow, resultCol)(bi, bj) = value; // Запись результата
                        }
                    }
                }
            }
        }
    }

    return result; // Возвращает результирующую блочную матрицу
}
