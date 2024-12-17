#pragma once

#include "Matrix.h"
#include <vector>
#include <initializer_list>
#include <stdexcept>
#include <iostream>

template <typename T>
class DenseMatrix : public Matrix<T> {
private:
    size_t _rows, _cols; // ���������� ����� � ��������
    std::vector<std::vector<T>> data;

public:
    // ����������� ��� ��������� ���������� ����� � ��������
    DenseMatrix(size_t rows, size_t cols);

    // ����������� � �������������� ���������������� �������
    DenseMatrix(std::initializer_list<std::initializer_list<T>> list);

    // ����������� �����������
    DenseMatrix(const DenseMatrix<T>& other);

    // �������� ������������
    DenseMatrix<T>& operator=(const DenseMatrix<T>& other);

    // �������� ������� � �������� ��� ���������
    T& operator()(size_t i, size_t j) override;

    // �������� ������� � �������� ��� ������
    const T& operator()(size_t i, size_t j) const override;

    // ����� ��� ��������� ���������� �����
    size_t rows() const override;

    // ����� ��� ��������� ���������� ��������
    size_t cols() const override;

    // �������� ��������
    DenseMatrix<T> operator+(const DenseMatrix<T>& other) const;

    // �������� ���������
    DenseMatrix<T> operator-(const DenseMatrix<T>& other) const;

    // �������� ���������
    DenseMatrix<T> operator*(const DenseMatrix<T>& other) const;

    // ����� ��� ������ �������
    void Print() const override;

    // ����������
    ~DenseMatrix() override; 
};

/*
���� ����� ������������ "�������" �������, ������� ������ �������� � ���� ���������� �������.
� ���� ������ ������������ �������:
1) �������� ������� �������� ��������.
2) ������������� ������� � ������� ������� �������������.
3) ����������� �������� � ������� ������������ �����������.
4) �������� ������� � ��������� ����� �������� ().
5) �������� ��������, ��������� � ��������� � ��������� ������������� ������������.
*/