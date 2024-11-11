#pragma once

#include <iostream>
#include <vector>
#include <exception>
#include "DenseMatrix.h"
#include "DiagonalMatrix.h"

// Шаблонный класс для блочных матриц, который будет принимать тип матрицы
template <typename T, template <typename> class MatrixType = Matrix>
class BlockMatrix : public Matrix<T> {
private:
    size_t m, n; // Количество блоков по строкам и столбцам
    std::vector<std::vector<MatrixType<T>*>> blocks; // Вектор указателей на блоки матриц

public:
    // Конструктор для создания блоков матриц
    BlockMatrix(size_t rows, size_t cols, size_t blockRows, size_t blockCols)
        : m(rows), n(cols) {
        // Инициализация блоков
        blocks.resize(m);
        for (size_t i = 0; i < m; ++i) {
            blocks[i].resize(n);
            for (size_t j = 0; j < n; ++j) {
                blocks[i][j] = new MatrixType<T>(blockRows, blockCols);
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
    MatrixType<T>& operator()(size_t i, size_t j) {
        return *blocks[i][j]; // Возвращает ссылку на блок
    }

    const MatrixType<T>& operator()(size_t i, size_t j) const {
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
                    blocks[i][j] = new MatrixType<T>(other(i, j).rows(), other(i, j).cols());
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

    // Метод для получения количества блоков по строкам
    size_t rows() const override {
        return m; // Возвращает количество блоков по строкам
    }

    // Метод для получения количества блоков по столбцам
    size_t cols() const override {
        return n; // Возвращает количество блоков по столбцам
    }

    // Оператор сложения блоков
    Matrix<T>* operator+(const Matrix<T>& other) const override {
        const BlockMatrix<T, MatrixType>* otherBlock = dynamic_cast<const BlockMatrix<T, MatrixType>*>(&other);
        if (otherBlock) {
            return AddWithBlock(*otherBlock);
        }

        const DenseMatrix<T>* otherDense = dynamic_cast<const DenseMatrix<T>*>(&other);
        if (otherDense) {
            return AddWithDense(*otherDense);
        }

        const DiagonalMatrix<T>* otherDiagonal = dynamic_cast<const DiagonalMatrix<T>*>(&other);
        if (otherDiagonal) {
            return AddWithDiagonal(*otherDiagonal);
        }

        throw std::runtime_error("Unsupported matrix type for addition");
    }

    // Оператор вычитания блоков
    Matrix<T>* operator-(const Matrix<T>& other) const override {
        const BlockMatrix<T, MatrixType>* otherBlock = dynamic_cast<const BlockMatrix<T, MatrixType>*>(&other);
        if (otherBlock) {
            return SubtractWithBlock(*otherBlock);
        }

        const DenseMatrix<T>* otherDense = dynamic_cast<const DenseMatrix<T>*>(&other);
        if (otherDense) {
            return SubtractWithDense(*otherDense);
        }

        const DiagonalMatrix<T>* otherDiagonal = dynamic_cast<const DiagonalMatrix<T>*>(&other);
        if (otherDiagonal) {
            return SubtractWithDiagonal(*otherDiagonal);
        }

        throw std::runtime_error("Unsupported matrix type for subtraction");
    }

    // Оператор умножения блоков
    Matrix<T>* operator*(const Matrix<T>& other) const override {
        // Проверяем, является ли 'other' блочной матрицей
        const BlockMatrix<T, MatrixType>* otherBlock = dynamic_cast<const BlockMatrix<T, MatrixType>*>(&other);

        // Если 'other' блочная матрица, продолжаем обычное умножение
        if (otherBlock) {
            return MultiplyWithBlock(*otherBlock);
        }

        // Проверяем, является ли 'other' плотной матрицей
        const DenseMatrix<T>* otherDense = dynamic_cast<const DenseMatrix<T>*>(&other);
        if (otherDense) {
            return MultiplyWithDense(*otherDense);
        }

        // Проверяем, является ли 'other' диагональной матрицей
        const DiagonalMatrix<T>* otherDiagonal = dynamic_cast<const DiagonalMatrix<T>*>(&other);
        if (otherDiagonal) {
            return MultiplyWithDiagonal(*otherDiagonal);
        }

        // Если тип не поддерживается, выбрасываем исключение
        throw std::runtime_error("Unsupported matrix type for multiplication");
    }
    // Метод для вычисления произведения Кронекера
    BlockMatrix<T, MatrixType> KroneckerProduct(const BlockMatrix<T, MatrixType>& other) const {
        size_t newM = m * other.m; // Новое количество строк
        size_t newN = n * other.n; // Новое количество столбцов
        size_t blockRows = (*this)(0, 0).rows(); // Количество строк в блоках
        size_t blockCols = other(0, 0).cols(); // Количество столбцов в блоках

        BlockMatrix<T, MatrixType> result(newM, newN, blockRows, blockCols); // Результирующая матрица

        // Итерация по всем блокам оригинальной и другой блочной матрицы
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                const MatrixType<T>& aBlock = (*this)(i, j); // Текущий блок из текущей матрицы
                const MatrixType<T>& bBlock = other(i, j); // Текущий блок из другой матрицы

                // Умножение блока a на каждую ячейку блока b
                for (size_t k = 0; k < other.m; ++k) {
                    for (size_t l = 0; l < other.n; ++l) {
                        const MatrixType<T>& bBlock = other(k, l);
                        for (size_t bi = 0; bi < blockRows; ++bi) {
                            for (size_t bj = 0; bj < blockCols; ++bj) {
                                T value = aBlock(bi, bj) * bBlock(bi, bj);
                                size_t resultRow = i * other.m + k;
                                size_t resultCol = j * other.n + l;

                                result(resultRow, resultCol)(bi, bj) = value; // Запись результата
                            }
                        }
                    }
                }
            }
        }
        return result; // Возвращает результирующую блочную матрицу
    }

    // Оператор вывода в поток
    friend std::ostream& operator<<(std::ostream& os, const BlockMatrix<T, MatrixType>& matrix) {
        for (size_t i = 0; i < matrix.rows(); ++i) {
            for (size_t j = 0; j < matrix.cols(); ++j) {
                os << matrix(i, j) << " "; // Выводим элементы блоков
            }
            os << std::endl; // Переход на новую строку
        }
        return os; // Возвращаем поток
    }

private:
    // Специальный метод для умножения на другую блочную матрицу
    Matrix<T>* MultiplyWithBlock(const BlockMatrix<T, MatrixType>& otherBlock) const {
        if (n != otherBlock.m) {
            throw std::runtime_error("Matrices have incompatible dimensions for multiplication");
        }

        BlockMatrix<T, MatrixType>* result = new BlockMatrix<T, MatrixType>(m, otherBlock.n, (*this)(0, 0).rows(), otherBlock.operator()(0, 0).cols());

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < otherBlock.n; ++j) {
                MatrixType<T> temp((*this)(0, 0).rows(), otherBlock.operator()(0, 0).cols());
                for (size_t k = 0; k < n; ++k) {
                    const MatrixType<T>& aBlock = (*this)(i, k);
                    const MatrixType<T>& bBlock = (*otherBlock)(k, j);

                    temp = temp + aBlock * bBlock; // Умножаем и складываем
                }
                (*result)(i, j) = temp; // Присвоение результата
            }
        }

        return result; // Возвращает указатель на результирующую матрицу
    }

    // Специальный метод для умножения на плотную матрицу
    Matrix<T>* MultiplyWithDense(const DenseMatrix<T>& otherDense) const {
        if (n != otherDense.rows()) {
            throw std::runtime_error("Matrices have incompatible dimensions for multiplication");
        }

        BlockMatrix<T, MatrixType>* result = new BlockMatrix<T, MatrixType>(m, otherDense.cols(), (*this)(0, 0).rows(), otherDense.cols());

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < otherDense.cols(); ++j) {
                MatrixType<T> temp((*this)(0, 0).rows(), otherDense.cols());
                for (size_t k = 0; k < n; ++k) {
                    const MatrixType<T>& aBlock = (*this)(i, k); // Блок из первой матрицы
                    const T& bElement = otherDense(k, j); // Элемент из плотной матрицы

                    temp = temp + aBlock * bElement; // Умножаем и складываем
                }
                (*result)(i, j) = temp; // Присвоение результата
            }
        }
        return result; // Возвращает указатель на результирующую матрицу
    }

    // Специальный метод для умножения на диагональную матрицу
    Matrix<T>* MultiplyWithDiagonal(const DiagonalMatrix<T>& otherDiagonal) const {
        if (n != otherDiagonal.rows()) {
            throw std::runtime_error("Matrices have incompatible dimensions for multiplication");
        }

        BlockMatrix<T, MatrixType>* result = new BlockMatrix<T, MatrixType>(m, otherDiagonal.cols(), (*this)(0, 0).rows(), otherDiagonal.cols());

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < otherDiagonal.cols(); ++j) {
                MatrixType<T> temp((*this)(0, 0).rows(), 1); // Результат будет столбцом
                for (size_t k = 0; k < n; ++k) {
                    const MatrixType<T>& aBlock = (*this)(i, k); // Блок из первой матрицы
                    const T& dElement = otherDiagonal(k, k); // Диагональный элемент

                    temp = temp + aBlock * dElement; // Умножаем и складываем
                }
                (*result)(i, j) = temp; // Присвоение результата
            }
        }

        return result; // Возвращает указатель на результирующую матрицу
    }

    // Специальный метод для вычитания с другой блочной матрицей
    Matrix<T>* SubtractWithBlock(const BlockMatrix<T, MatrixType>& otherBlock) const {
        if (m != otherBlock.m || n != otherBlock.n) {
            throw std::runtime_error("Matrices have incompatible dimensions for subtraction");
        }

        BlockMatrix<T, MatrixType>* result = new BlockMatrix<T, MatrixType>(m, n, (*this)(0, 0).rows(), (*this)(0, 0).cols());

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                (*result)(i, j) = (*this)(i, j) - (*otherBlock)(i, j); // Вычитание блоков
            }
        }

        return result; // Возвращает указатель на результирующую блочную матрицу
    }

    // Специальный метод для вычитания с плотной матрицей
    Matrix<T>* SubtractWithDense(const DenseMatrix<T>& otherDense) const {
        if (m != otherDense.rows() || n != otherDense.cols()) {
            throw std::runtime_error("Matrices have incompatible dimensions for subtraction");
        }

        BlockMatrix<T, MatrixType>* result = new BlockMatrix<T, MatrixType>(m, n, (*this)(0, 0).rows(), (*this)(0, 0).cols());

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                (*result)(i, j) = (*this)(i, j) - otherDense(i, j); // Используем оператор вычитания
            }
        }

        return result; // Возвращает указатель на результирующую матрицу
    }

    // Специальный метод для вычитания с диагональной матрицей
    Matrix<T>* SubtractWithDiagonal(const DiagonalMatrix<T>& otherDiagonal) const {
        if (m != otherDiagonal.rows() || n != otherDiagonal.cols()) {
            throw std::runtime_error("Matrices have incompatible dimensions for subtraction");
        }

        BlockMatrix<T, MatrixType>* result = new BlockMatrix<T, MatrixType>(m, n, (*this)(0, 0).rows(), (*this)(0, 0).cols());

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (i == j) { // Мы вычитаем только диагональные элементы
                    (*result)(i, j) = (*this)(i, j) - otherDiagonal(i, i); // Вычитаем диагональный элемент
                }
                else {
                    (*result)(i, j) = (*this)(i, j); // Остальные элементы остаются без изменений
                }
            }
        }

        return result; // Возвращает указатель на результирующую матрицу
    }

    // Специальный метод для сложения с другой блочной матрицей
    Matrix<T>* AddWithBlock(const BlockMatrix<T, MatrixType>& otherBlock) const {
        // Проверка совместимости размеров
        if (m != otherBlock.rows() || n != otherBlock.cols()) {
            throw std::runtime_error("Matrices have incompatible dimensions for addition");
        }

        BlockMatrix<T, MatrixType>* result = new BlockMatrix<T, MatrixType>(m, n, (*this)(0, 0).rows(), (*this)(0, 0).cols());

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                const MatrixType<T>& aBlock = (*this)(i, j);
                const MatrixType<T>& bBlock = (*otherBlock)(i, j);
                (*result)(i, j) = aBlock + bBlock; // Теперь мы используем ссылки
            }
        }

        return result; // Возвращает указатель на результирующую блочную матрицу
    }

    // Специальный метод для сложения с плотной матрицей
    Matrix<T>* AddWithDense(const DenseMatrix<T>& otherDense) const {
        // Проверка совместимости размеров
        if (m != otherDense.rows() || n != otherDense.cols()) {
            throw std::runtime_error("Matrices have incompatible dimensions for addition");
        }

        BlockMatrix<T, MatrixType>* result = new BlockMatrix<T, MatrixType>(m, n, (*this)(0, 0).rows(), (*this)(0, 0).cols());

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                const MatrixType<T>& aBlock = (*this)(i, j);
                const T& bElement = otherDense(i, j);
                (*result)(i, j) = aBlock + bElement; // Используйте ссылку для элемента другого типа
            }
        }

        return result; // Возвращает указатель на результирующую матрицу
    }

    // Специальный метод для сложения с диагональной матрицей
    Matrix<T>* AddWithDiagonal(const DiagonalMatrix<T>& otherDiagonal) const {
        // Проверка совместимости размеров
        if (m != otherDiagonal.rows() || n != otherDiagonal.cols()) {
            throw std::runtime_error("Matrices have incompatible dimensions for addition");
        }

        // Создаем результирующую блочную матрицу
        BlockMatrix<T, MatrixType>* result = new BlockMatrix<T, MatrixType>(m, n, (*this)(0, 0).rows(), (*this)(0, 0).cols());

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                const MatrixType<T>& aBlock = (*this)(i, j); // Получаем блок текущей матрицы

                if (i == j) { // Сложение происходит только для диагональных элементов
                    const T& dElement = otherDiagonal(i, i); // Берем соответствующий диагональный элемент
                    (*result)(i, j) = aBlock + dElement; // Сложение с диагональным элементом
                }
                else {
                    // Если это не диагональный элемент, просто копируем
                    (*result)(i, j) = aBlock;
                }
            }
        }

        return result; // Возвращает указатель на полученную матрицу
    }


};