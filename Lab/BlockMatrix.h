#pragma once // ������ �� ������������� ����������� �����

#include "Matrix.h"
#include "DenseMatrix.h"
#include "DiagonalMatrix.h"
#include <vector>
#include <stdexcept>
#include <iostream>

template <typename T, template<typename> class MatrixType>
class BlockMatrix : public Matrix<T> {
private:
    /*���������� �� ������������� ����� ���������������� ����� ���������� ������ �������, �� ������ ���� 
    �������� ������ ������� � ������ ������� ����� ���������� ��������� ���� ������� �������.
    */
    std::vector<std::vector<MatrixType<T>*>> blocks;//������������� ��������� �������
    size_t _RowsBlock, _ColsBlock;//������������� ���������� ����� � �������� � �����
    size_t _FullRowsBlockSize, _FullColsBlockSize;//������� ������ � ������� ������� �� ������ � ��������
public:
    BlockMatrix(size_t blockRows, size_t blockCols, size_t blockSizeRows, size_t blockSizeCols);

    ~BlockMatrix();

    void CreateBlock(size_t row, size_t col, MatrixType<T>* block);

    T& operator()(size_t i, size_t j) override;

    const T& operator()(size_t i, size_t j) const override;

    size_t rows() const override;

    size_t cols() const override;

    BlockMatrix operator+(const BlockMatrix& other) const;

    BlockMatrix operator-(const BlockMatrix& other) const;

    void Print() const override;

    BlockMatrix<T, MatrixType> kroneckerProduct(const BlockMatrix<T, MatrixType>& other) const;
};