#pragma once

#include "Matrix.h"
#include <iostream>
#include <vector>
#include <stdexcept> // ��� ��������� ����������

// ��������� ����� ��� ������������ ������
template <typename T>
class DiagonalMatrix : public Matrix<T> {
private:

    std::vector<std::vector<T>> data;// ����� ���� ������ ������ ������������ ��������,�� ����������� ������� ������� �� ��������� ������ ������������ ��������, ����� ������������� ������ �������)
    
    size_t size;// � ������������ ������� ���������� ����� ����� ���������� ��������, ������� ������ ����.                        

public:
    // �����������, ������� ��������� ������ �������� ��� ���������
    DiagonalMatrix(std::initializer_list<T> initializer_list);

    // �����������, ������� ��������� ������ � ������� �������������
    DiagonalMatrix(size_t Size);

    // ������ � ��������� �������
    T& operator()(size_t i, size_t j) override;

    const T& operator()(size_t i, size_t j) const override;

    size_t rows() const;

    size_t cols() const;

    // ��������� ��������, ��������� � ���������
    DiagonalMatrix<T> operator+(const DiagonalMatrix<T>& other) const;

    DiagonalMatrix<T> operator-(const DiagonalMatrix<T>& other) const;

    DiagonalMatrix<T> operator*(const DiagonalMatrix<T>& other) const;

    void Print() const;
};