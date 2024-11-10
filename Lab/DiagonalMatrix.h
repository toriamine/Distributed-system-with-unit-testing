#pragma once // ������ �� ������������� ����������� �����

#include "Matrix.h"
#include <iostream>
#include <vector>
#include <exception> // ��� ��������� ����������

// ��������� ����� ��� ������������ ������
template <typename T>
class DiagonalMatrix : public Matrix<T> {
private:
    size_t m, n; // ���������� ����� (m) � �������� (n) � �������
    std::vector<T> diagonal; // ������ ��� �������� ��������� ������� ���������

public:
    // �����������
    DiagonalMatrix(size_t rows, size_t cols);

    // �������� ������� � �������� (��������������)
    T& operator()(size_t i, size_t j) override;

    // �������� ������� � �������� (�����������)
    const T& operator()(size_t i, size_t j) const override;

    // ����� ��� ��������� ���������� �����
    size_t rows() const override;

    // ����� ��� ��������� ���������� ��������
    size_t cols() const override;

    // �������� ��������
    Matrix<T>* operator+(const Matrix<T>& other) const override;

    // �������� ���������
    Matrix<T>* operator-(const Matrix<T>& other) const override;

    // �������� ���������
    Matrix<T>* operator*(const Matrix<T>& other) const override;

    // �������� ������ � �����
    friend std::ostream& operator<<(std::ostream& os, const DiagonalMatrix<T>& matrix) {
        for (size_t i = 0; i < matrix.rows(); ++i) {
            for (size_t j = 0; j < matrix.cols(); ++j) {
                if (i == j) {
                    os << matrix(i, j) << " "; // ������� ������ ������������ ��������
                }
                else {
                    os << "0 "; // ��������� �������� ����� ����
                }
            }
            os << std::endl; // ������� �� ����� ������
        }
        return os; // ���������� �����
    }

    // ����������� ����������
    ~DiagonalMatrix() override = default;
};
