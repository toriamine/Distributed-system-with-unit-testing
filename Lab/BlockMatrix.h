#pragma once // ������ �� ������������� ����������� �����

#include "Matrix.h"
#include "DenseMatrix.h"
#include "DiagonalMatrix.h"
#include <vector>
#include <stdexcept>
#include <iostream>

// ��������� ����� ������� �������
template<typename T, template <typename> class MatrixType>
class BlockMatrix : public Matrix<T> {
private:
    std::vector<std::vector<MatrixType<T>*>> blocks; // ��������� �� �����
    size_t numBlocksRows; // ���������� ������ �� �������
    size_t numBlocksCols; // ���������� ������ �� ��������
    size_t blockRows;     // ���������� ����� � ������ �����
    size_t blockCols;     // ���������� �������� � ������ �����

public:
    // �����������
    BlockMatrix(size_t blockRows, size_t blockCols, size_t rows, size_t cols);

    // ����������
    ~BlockMatrix();

    // ���������� ����
    void setBlock(size_t row, size_t col, MatrixType<T>* block);

    // �������� ������� � ���������
    T& operator()(size_t i, size_t j); // ��������������� ��� ������� � ���������
    const T& operator()(size_t i, size_t j) const; // ��������������� ��� ������� � ���������

    size_t rows() const override; // ��������������� ��� ���������� �����
    size_t cols() const override; // ��������������� ��� ���������� ��������

    void Print() const override; // ������ ���� ������� �������

    MatrixType<T>& block(size_t row, size_t col) {
        if (!blocks[row][col]) {
            blocks[row][col] = new MatrixType<T>(blockRows, blockCols); // �������������� ����, ���� �� �� ����������
        }
        return *blocks[row][col];
    }

    // ��������� ��������, ��������� � ���������
    BlockMatrix<T, MatrixType> operator+(const BlockMatrix<T, MatrixType>& other) const;
    BlockMatrix<T, MatrixType> operator-(const BlockMatrix<T, MatrixType>& other) const;
    BlockMatrix<T, MatrixType> operator*(const BlockMatrix<T, MatrixType>& other) const;

    // ����� ��� ���������� ������������ ���������
    //BlockMatrix<T, MatrixType> kroneckerProduct(const BlockMatrix<T, MatrixType>& other) const;
};