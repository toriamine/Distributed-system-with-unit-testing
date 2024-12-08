#pragma once // ������ �� ������������� ����������� �����

#include "Matrix.h"
#include <iostream>
#include <vector>
#include <exception> // ��� ��������� ����������

// ��������� ����� ��� ������������ ������
template <typename T = double>
class DiagonalMatrix : public Matrix<T> {
private:
    size_t m, n; // ���������� ����� (m) � �������� (n) � �������
    std::vector<T> diagonal; // ������ ��� �������� ��������� ������� ���������

public:
    // �����������
    DiagonalMatrix(size_t rows, size_t cols) : m(rows), n(cols) {
        diagonal.resize(std::min(m, n), 0); // ������������� ������� ���������
    }

    // �������� ������� � �������� (��������������)
    T& operator()(size_t i, size_t j) override {
        if (i != j) {
            static T zero = 0; // ����������� ���������� ��� ����������� ����
            return zero; // ���������� 0
        }
        return diagonal[i]; // ���������� ������� ���������
    }

    // �������� ������� � �������� (�����������)
    const T& operator()(size_t i, size_t j) const override {
        if (i != j) {
            static T zero = 0; // ����������� ���������� ��� ����������� ����
            return zero; // ���������� 0
        }
        return diagonal[i]; // ���������� ������� ���������
    }

    // ����� ��� ��������� ���������� �����
    size_t rows() const override {
        return m; // ���������� ���������� �����
    }

    // ����� ��� ��������� ���������� ��������
    size_t cols() const override {
        return n; // ���������� ���������� ��������
    }

    // �������� ��� Matrix
    Matrix<T>* operator+(const Matrix<T>& other) const override {
        const DiagonalMatrix<T>* otherDiagonal = dynamic_cast<const DiagonalMatrix<T>*>(&other);
        if (!otherDiagonal || m != otherDiagonal->m || n != otherDiagonal->n) {
            throw std::runtime_error("Matrices have incompatible dimensions");
        }

        DiagonalMatrix<T>* result = new DiagonalMatrix<T>(m, n); // ������� �������������� �������
        for (size_t i = 0; i < std::min(m, n); ++i) {
            (*result)(i, i) = (*this)(i, i) + (*otherDiagonal)(i, i); // �������� ��������������� ������������ ���������
        }
        return result; // ���������� ��������� �� ���������
    }

    // �������� ��������� ���� ������������ ������
    Matrix<T>* operator-(const Matrix<T>& other) const override {
        const DiagonalMatrix<T>* otherDiagonal = dynamic_cast<const DiagonalMatrix<T>*>(&other);
        if (!otherDiagonal || m != otherDiagonal->m || n != otherDiagonal->n) { // ���������� ������� � ����������� �����������
            throw std::runtime_error("Matrices have incompatible dimensions for subtraction");
        }

        DiagonalMatrix<T>* result = new DiagonalMatrix<T>(m, n); // ������� �������������� �������
        for (size_t i = 0; i < std::min(m, n); ++i) {
            (*result)(i, i) = (*this)(i, i) - (*otherDiagonal)(i, i); // ��������� ��������������� ������������ ���������
        }
        return result; // ���������� ��������� �� ���������
    }

    // �������� ��������� ���� ������������ ������
    Matrix<T>* operator*(const Matrix<T>& other) const override {
        const DiagonalMatrix<T>* otherDiagonal = dynamic_cast<const DiagonalMatrix<T>*>(&other);
        if (!otherDiagonal || n != otherDiagonal->m) { // ���������� ������� ��� �������������
            throw std::runtime_error("Matrices have incompatible dimensions for multiplication");
        }

        DiagonalMatrix<T>* result = new DiagonalMatrix<T>(m, otherDiagonal->n); // ������� �������������� �������
        for (size_t i = 0; i < std::min(m, otherDiagonal->n); ++i) {
            (*result)(i, i) = (*this)(i, i) * (*otherDiagonal)(i, i); // ��������� ��������������� ������������ ���������
        }
        return result; // ���������� ��������� �� ���������
    }


    // ����������� ����������
    ~DiagonalMatrix() override = default;
};

// �������� ������ ��� ������������ �������
template <typename T>
std::ostream& operator<<(std::ostream& os, const DiagonalMatrix<T>& matrix) {
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
