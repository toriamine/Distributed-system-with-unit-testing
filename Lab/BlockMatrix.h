#pragma once

#include <iostream>
#include <vector>
#include <exception>
#include "DenseMatrix.h"
#include "DiagonalMatrix.h"

// ��������� ����� ��� ������� ������, ������� ����� ��������� ��� �������
template <typename T, template <typename> class MatrixType = Matrix>
class BlockMatrix : public Matrix<T> {
private:
    size_t m, n; // ���������� ������ �� ������� � ��������
    std::vector<std::vector<MatrixType<T>*>> blocks; // ������ ���������� �� ����� ������

public:
    // ����������� ��� �������� ������ ������
    BlockMatrix(size_t rows, size_t cols, size_t blockRows, size_t blockCols)
        : m(rows), n(cols) {
        // ������������� ������
        blocks.resize(m);
        for (size_t i = 0; i < m; ++i) {
            blocks[i].resize(n);
            for (size_t j = 0; j < n; ++j) {
                blocks[i][j] = new MatrixType<T>(blockRows, blockCols);
            }
        }
    }

    // ���������� ��� ������������ ������
    ~BlockMatrix() {
        // ����������� ������, ���������� ��� �����
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                delete blocks[i][j]; // ������� ������ ����
            }
        }
    }

    // �������� ������� � ����� ������ �� ��������
    MatrixType<T>& operator()(size_t i, size_t j) {
        return *blocks[i][j]; // ���������� ������ �� ����
    }

    const MatrixType<T>& operator()(size_t i, size_t j) const {
        return *blocks[i][j]; // ���������� ����������� ������ ��� ������������� �������
    }

    // �������� ������������
    BlockMatrix& operator=(const BlockMatrix& other) {
        if (this != &other) { // �������� �� ����������������
            // ����������� ������ ������� ������
            for (size_t i = 0; i < m; ++i) {
                for (size_t j = 0; j < n; ++j) {
                    delete blocks[i][j]; // ������� ������ ����
                }
            }

            // ��������� ����� �������� � �������� ������
            m = other.m;
            n = other.n;
            blocks.resize(m);
            for (size_t i = 0; i < m; ++i) {
                blocks[i].resize(n);
                for (size_t j = 0; j < n; ++j) {
                    blocks[i][j] = new MatrixType<T>(other(i, j).rows(), other(i, j).cols());
                }
            }

            // �������� ������������ �����
            for (size_t i = 0; i < m; ++i) {
                for (size_t j = 0; j < n; ++j) {
                    (*this)(i, j) = other(i, j); // �������� ���������� ������� �����
                }
            }
        }
        return *this; // ���������� ������ �� ������� ������
    }

    // ����� ��� ��������� ���������� ������ �� �������
    size_t rows() const override {
        return m; // ���������� ���������� ������ �� �������
    }

    // ����� ��� ��������� ���������� ������ �� ��������
    size_t cols() const override {
        return n; // ���������� ���������� ������ �� ��������
    }

    // �������� �������� ������
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

    // �������� ��������� ������
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

    // �������� ��������� ������
    Matrix<T>* operator*(const Matrix<T>& other) const override {
        // ���������, �������� �� 'other' ������� ��������
        const BlockMatrix<T, MatrixType>* otherBlock = dynamic_cast<const BlockMatrix<T, MatrixType>*>(&other);

        // ���� 'other' ������� �������, ���������� ������� ���������
        if (otherBlock) {
            return MultiplyWithBlock(*otherBlock);
        }

        // ���������, �������� �� 'other' ������� ��������
        const DenseMatrix<T>* otherDense = dynamic_cast<const DenseMatrix<T>*>(&other);
        if (otherDense) {
            return MultiplyWithDense(*otherDense);
        }

        // ���������, �������� �� 'other' ������������ ��������
        const DiagonalMatrix<T>* otherDiagonal = dynamic_cast<const DiagonalMatrix<T>*>(&other);
        if (otherDiagonal) {
            return MultiplyWithDiagonal(*otherDiagonal);
        }

        // ���� ��� �� ��������������, ����������� ����������
        throw std::runtime_error("Unsupported matrix type for multiplication");
    }
    // ����� ��� ���������� ������������ ���������
    BlockMatrix<T, MatrixType> KroneckerProduct(const BlockMatrix<T, MatrixType>& other) const {
        size_t newM = m * other.m; // ����� ���������� �����
        size_t newN = n * other.n; // ����� ���������� ��������
        size_t blockRows = (*this)(0, 0).rows(); // ���������� ����� � ������
        size_t blockCols = other(0, 0).cols(); // ���������� �������� � ������

        BlockMatrix<T, MatrixType> result(newM, newN, blockRows, blockCols); // �������������� �������

        // �������� �� ���� ������ ������������ � ������ ������� �������
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                const MatrixType<T>& aBlock = (*this)(i, j); // ������� ���� �� ������� �������
                const MatrixType<T>& bBlock = other(i, j); // ������� ���� �� ������ �������

                // ��������� ����� a �� ������ ������ ����� b
                for (size_t k = 0; k < other.m; ++k) {
                    for (size_t l = 0; l < other.n; ++l) {
                        const MatrixType<T>& bBlock = other(k, l);
                        for (size_t bi = 0; bi < blockRows; ++bi) {
                            for (size_t bj = 0; bj < blockCols; ++bj) {
                                T value = aBlock(bi, bj) * bBlock(bi, bj);
                                size_t resultRow = i * other.m + k;
                                size_t resultCol = j * other.n + l;

                                result(resultRow, resultCol)(bi, bj) = value; // ������ ����������
                            }
                        }
                    }
                }
            }
        }
        return result; // ���������� �������������� ������� �������
    }

    // �������� ������ � �����
    friend std::ostream& operator<<(std::ostream& os, const BlockMatrix<T, MatrixType>& matrix) {
        for (size_t i = 0; i < matrix.rows(); ++i) {
            for (size_t j = 0; j < matrix.cols(); ++j) {
                os << matrix(i, j) << " "; // ������� �������� ������
            }
            os << std::endl; // ������� �� ����� ������
        }
        return os; // ���������� �����
    }

private:
    // ����������� ����� ��� ��������� �� ������ ������� �������
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

                    temp = temp + aBlock * bBlock; // �������� � ����������
                }
                (*result)(i, j) = temp; // ���������� ����������
            }
        }

        return result; // ���������� ��������� �� �������������� �������
    }

    // ����������� ����� ��� ��������� �� ������� �������
    Matrix<T>* MultiplyWithDense(const DenseMatrix<T>& otherDense) const {
        if (n != otherDense.rows()) {
            throw std::runtime_error("Matrices have incompatible dimensions for multiplication");
        }

        BlockMatrix<T, MatrixType>* result = new BlockMatrix<T, MatrixType>(m, otherDense.cols(), (*this)(0, 0).rows(), otherDense.cols());

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < otherDense.cols(); ++j) {
                MatrixType<T> temp((*this)(0, 0).rows(), otherDense.cols());
                for (size_t k = 0; k < n; ++k) {
                    const MatrixType<T>& aBlock = (*this)(i, k); // ���� �� ������ �������
                    const T& bElement = otherDense(k, j); // ������� �� ������� �������

                    temp = temp + aBlock * bElement; // �������� � ����������
                }
                (*result)(i, j) = temp; // ���������� ����������
            }
        }
        return result; // ���������� ��������� �� �������������� �������
    }

    // ����������� ����� ��� ��������� �� ������������ �������
    Matrix<T>* MultiplyWithDiagonal(const DiagonalMatrix<T>& otherDiagonal) const {
        if (n != otherDiagonal.rows()) {
            throw std::runtime_error("Matrices have incompatible dimensions for multiplication");
        }

        BlockMatrix<T, MatrixType>* result = new BlockMatrix<T, MatrixType>(m, otherDiagonal.cols(), (*this)(0, 0).rows(), otherDiagonal.cols());

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < otherDiagonal.cols(); ++j) {
                MatrixType<T> temp((*this)(0, 0).rows(), 1); // ��������� ����� ��������
                for (size_t k = 0; k < n; ++k) {
                    const MatrixType<T>& aBlock = (*this)(i, k); // ���� �� ������ �������
                    const T& dElement = otherDiagonal(k, k); // ������������ �������

                    temp = temp + aBlock * dElement; // �������� � ����������
                }
                (*result)(i, j) = temp; // ���������� ����������
            }
        }

        return result; // ���������� ��������� �� �������������� �������
    }

    // ����������� ����� ��� ��������� � ������ ������� ��������
    Matrix<T>* SubtractWithBlock(const BlockMatrix<T, MatrixType>& otherBlock) const {
        if (m != otherBlock.m || n != otherBlock.n) {
            throw std::runtime_error("Matrices have incompatible dimensions for subtraction");
        }

        BlockMatrix<T, MatrixType>* result = new BlockMatrix<T, MatrixType>(m, n, (*this)(0, 0).rows(), (*this)(0, 0).cols());

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                (*result)(i, j) = (*this)(i, j) - (*otherBlock)(i, j); // ��������� ������
            }
        }

        return result; // ���������� ��������� �� �������������� ������� �������
    }

    // ����������� ����� ��� ��������� � ������� ��������
    Matrix<T>* SubtractWithDense(const DenseMatrix<T>& otherDense) const {
        if (m != otherDense.rows() || n != otherDense.cols()) {
            throw std::runtime_error("Matrices have incompatible dimensions for subtraction");
        }

        BlockMatrix<T, MatrixType>* result = new BlockMatrix<T, MatrixType>(m, n, (*this)(0, 0).rows(), (*this)(0, 0).cols());

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                (*result)(i, j) = (*this)(i, j) - otherDense(i, j); // ���������� �������� ���������
            }
        }

        return result; // ���������� ��������� �� �������������� �������
    }

    // ����������� ����� ��� ��������� � ������������ ��������
    Matrix<T>* SubtractWithDiagonal(const DiagonalMatrix<T>& otherDiagonal) const {
        if (m != otherDiagonal.rows() || n != otherDiagonal.cols()) {
            throw std::runtime_error("Matrices have incompatible dimensions for subtraction");
        }

        BlockMatrix<T, MatrixType>* result = new BlockMatrix<T, MatrixType>(m, n, (*this)(0, 0).rows(), (*this)(0, 0).cols());

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (i == j) { // �� �������� ������ ������������ ��������
                    (*result)(i, j) = (*this)(i, j) - otherDiagonal(i, i); // �������� ������������ �������
                }
                else {
                    (*result)(i, j) = (*this)(i, j); // ��������� �������� �������� ��� ���������
                }
            }
        }

        return result; // ���������� ��������� �� �������������� �������
    }

    // ����������� ����� ��� �������� � ������ ������� ��������
    Matrix<T>* AddWithBlock(const BlockMatrix<T, MatrixType>& otherBlock) const {
        // �������� ������������� ��������
        if (m != otherBlock.rows() || n != otherBlock.cols()) {
            throw std::runtime_error("Matrices have incompatible dimensions for addition");
        }

        BlockMatrix<T, MatrixType>* result = new BlockMatrix<T, MatrixType>(m, n, (*this)(0, 0).rows(), (*this)(0, 0).cols());

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                const MatrixType<T>& aBlock = (*this)(i, j);
                const MatrixType<T>& bBlock = (*otherBlock)(i, j);
                (*result)(i, j) = aBlock + bBlock; // ������ �� ���������� ������
            }
        }

        return result; // ���������� ��������� �� �������������� ������� �������
    }

    // ����������� ����� ��� �������� � ������� ��������
    Matrix<T>* AddWithDense(const DenseMatrix<T>& otherDense) const {
        // �������� ������������� ��������
        if (m != otherDense.rows() || n != otherDense.cols()) {
            throw std::runtime_error("Matrices have incompatible dimensions for addition");
        }

        BlockMatrix<T, MatrixType>* result = new BlockMatrix<T, MatrixType>(m, n, (*this)(0, 0).rows(), (*this)(0, 0).cols());

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                const MatrixType<T>& aBlock = (*this)(i, j);
                const T& bElement = otherDense(i, j);
                (*result)(i, j) = aBlock + bElement; // ����������� ������ ��� �������� ������� ����
            }
        }

        return result; // ���������� ��������� �� �������������� �������
    }

    // ����������� ����� ��� �������� � ������������ ��������
    Matrix<T>* AddWithDiagonal(const DiagonalMatrix<T>& otherDiagonal) const {
        // �������� ������������� ��������
        if (m != otherDiagonal.rows() || n != otherDiagonal.cols()) {
            throw std::runtime_error("Matrices have incompatible dimensions for addition");
        }

        // ������� �������������� ������� �������
        BlockMatrix<T, MatrixType>* result = new BlockMatrix<T, MatrixType>(m, n, (*this)(0, 0).rows(), (*this)(0, 0).cols());

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                const MatrixType<T>& aBlock = (*this)(i, j); // �������� ���� ������� �������

                if (i == j) { // �������� ���������� ������ ��� ������������ ���������
                    const T& dElement = otherDiagonal(i, i); // ����� ��������������� ������������ �������
                    (*result)(i, j) = aBlock + dElement; // �������� � ������������ ���������
                }
                else {
                    // ���� ��� �� ������������ �������, ������ ��������
                    (*result)(i, j) = aBlock;
                }
            }
        }

        return result; // ���������� ��������� �� ���������� �������
    }


};