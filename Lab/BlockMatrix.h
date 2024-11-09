#pragma once

#include <iostream>
#include <vector>
#include <exception>
#include "DenseMatrix.h"

template <typename T = double>
class BlockMatrix {
private:
    size_t m, n; // ���������� ����� � �������� ������
    std::vector<std::vector<DenseMatrix<T>*>> blocks; // ������ �������� ���������� �� ����� ������

public:
    // ����������� ��� �������� ������ ������
    BlockMatrix(size_t rows, size_t cols, size_t blockRows, size_t blockCols)
        : m(rows), n(cols) {
        // ������������� ������
        blocks.resize(m);
        for (size_t i = 0; i < m; ++i) {
            blocks[i].resize(n);
            for (size_t j = 0; j < n; ++j) {
                blocks[i][j] = new DenseMatrix<T>(blockRows, blockCols);
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
    DenseMatrix<T>& operator()(size_t i, size_t j) {
        return *blocks[i][j]; // ���������� ������ �� ����
    }

    const DenseMatrix<T>& operator()(size_t i, size_t j) const {
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
                    blocks[i][j] = new DenseMatrix<T>(other(i, j).rows(), other(i, j).cols());
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

    // ����� ��� ��������� ���������� �����
    size_t rows() const {
        return m; // ���������� ���������� ������ �� �������
    }

    // ����� ��� ��������� ���������� ��������
    size_t cols() const {
        return n; // ���������� ���������� ������ �� ��������
    }

    // �������� �������� ������
    BlockMatrix operator+(const BlockMatrix& other) const {
        if (m != other.m || n != other.n) {
            throw std::runtime_error("Matrices have incompatible dimensions");
        }

        BlockMatrix result(m, n, (*this)(0, 0).rows(), (*this)(0, 0).cols());
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                result(i, j) = (*this)(i, j) + other(i, j); // �������� ������
            }
        }
        return result; // ���������� �������������� ������� �������
    }

    // �������� ��������� ������
    BlockMatrix operator-(const BlockMatrix& other) const {

        if (m != other.m || n != other.n) {
            throw std::runtime_error("Matrices have incompatible dimensions");
        }

        BlockMatrix result(m, n, (*this)(0, 0).rows(), (*this)(0, 0).cols());
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                result(i, j) = (*this)(i, j) - other(i, j); // ��������� ������
            }
        }
        return result; // ���������� �������������� ������� �������
    }

    // �������� ��������� ������
    BlockMatrix operator*(const BlockMatrix& other) const {
        if (n != other.m) {
            throw std::runtime_error("Matrices have incompatible dimensions");
        }

        BlockMatrix result(m, other.n, (*this)(0, 0).rows(), (*this)(0, 0).cols());
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < other.n; ++j) {
                for (size_t k = 0; k < n; ++k) {
                    result(i, j) = result(i, j) + (*this)(i, k) * other(k, j); // ��������� ������
                }
            }
        }
        return result; // ���������� �������������� ������� �������
    }

    // ����� ��� ���������� ������������ ���������
    BlockMatrix<T> KroneckerProduct(const BlockMatrix<T>& other) const;
};

// ���������� ������ ���������
template <typename T>
BlockMatrix<T> BlockMatrix<T>::KroneckerProduct(const BlockMatrix<T>& other) const {
    size_t newM = m * other.m; // ����� ���������� �����
    size_t newN = n * other.n; // ����� ���������� ��������
    size_t blockRows = (*this)(0, 0).rows(); // ���������� ����� � ������
    size_t blockCols = other(0, 0).cols(); // ���������� �������� � ������

    BlockMatrix<T> result(newM, newN, blockRows, blockCols); // �������������� �������

    // �������� �� ���� ������ ������������ � ������ ������� �������
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            const DenseMatrix<T>& aBlock = (*this)(i, j); // ������� ���� �� ������� �������
            const DenseMatrix<T>& bBlock = other(i, j); // ������� ���� �� ������ �������

            // ��������� ����� a �� ������ ������ ����� b
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

                            result(resultRow, resultCol)(bi, bj) = value; // ������ ����������
                        }
                    }
                }
            }
        }
    }

    return result; // ���������� �������������� ������� �������
}
