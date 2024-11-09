#pragma once

#include "DenseMatrix.h"     
#include "DiagonalMatrix.h"  
#include "BlockMatrix.h"     

//����������� �����


// ����� ��������� ��� ������� ������
template <typename T>
DenseMatrix<T> operator+(const DenseMatrix<T>& a, const DenseMatrix<T>& b) {
    // ���������� ��������� �������� ��� ������� ������
    return a + b; // ���� � DenseMatrix ���� ������������� ���������, ��� ���������� �����
}

template <typename T>
DenseMatrix<T> operator-(const DenseMatrix<T>& a, const DenseMatrix<T>& b) {
    // ���������� ��������� ��������� ��� ������� ������
    return a - b; // �������� ����������
}

template <typename T>
DenseMatrix<T> operator*(const DenseMatrix<T>& a, const DenseMatrix<T>& b) {
    // ���������� ��������� ��������� ��� ������� ������
    return a * b; // �������� ����������
}

// ���������� ���������� ��� ������������ ������
template <typename T>
DiagonalMatrix<T> operator+(const DiagonalMatrix<T>& a, const DiagonalMatrix<T>& b) {
    // ���������� ��������� �������� ��� ������������ ������
    return a + b; // ��������, �������������� ������� ��������������� ������� � DiagonalMatrix
}

template <typename T>
DiagonalMatrix<T> operator-(const DiagonalMatrix<T>& a, const DiagonalMatrix<T>& b) {
    // ���������� ��������� ��������� ��� ������������ ������
    return a - b; // ����������
}

template <typename T>
DiagonalMatrix<T> operator*(const DiagonalMatrix<T>& a, const DiagonalMatrix<T>& b) {
    // ���������� ��������� ��������� ��� ������������ ������
    return a * b; // ����������
}

// ���������� ���������� ��� ������� ������
template <typename T>
BlockMatrix<T> operator+(const BlockMatrix<T>& a, const BlockMatrix<T>& b) {
    // ���������� ��������� �������� ��� ������� ������
    return a + b; // ����������
}

template <typename T>
BlockMatrix<T> operator-(const BlockMatrix<T>& a, const BlockMatrix<T>& b) {
    // ���������� ��������� ��������� ��� ������� ������
    return a - b; // ����������
}

template <typename T>
BlockMatrix<T> operator*(const BlockMatrix<T>& a, const BlockMatrix<T>& b) {
    // ���������� ��������� ��������� ��� ������� ������
    return a * b; // ����������
}

// ����� ������� ��� ������ � ���������

template <typename T>
T FrobeniusNorm(const DenseMatrix<T>& matrix) {
    // ���������� ������� ���������� ����� ����������
    T sum = 0; // ���������� ��� ���������� ����� ��������� ���������
    for (size_t i = 0; i < matrix.rows(); ++i) {
        for (size_t j = 0; j < matrix.cols(); ++j) {
            sum += matrix(i, j) * matrix(i, j); // ��������� �������� ���������
        }
    }
    return std::sqrt(sum); // ���������� ���������� ������ �� �����
}

template <typename T>
DenseMatrix<T> Transpose(const DenseMatrix<T>& matrix) {
    // ���������� ������� ���������������� ������� �������
    DenseMatrix<T> result(matrix.cols(), matrix.rows()); // ������� ������� � ���������� ������������
    for (size_t i = 0; i < matrix.rows(); ++i) {
        for (size_t j = 0; j < matrix.cols(); ++j) {
            result(j, i) = matrix(i, j); // �������������
        }
    }
    return result; // ���������� �������������� �������
}

// ������������� �������� << ��� ������ ������

template <typename T>
std::ostream& operator<<(std::ostream& os, const DenseMatrix<T>& matrix) {
    for (size_t i = 0; i < matrix.rows(); ++i) {
        for (size_t j = 0; j < matrix.cols(); ++j) {

            os << matrix(i, j) << " "; // ������� �������� � ������
        }
        os << std::endl; // ��������� �� ��������� ������
    }
    return os; // ���������� �����
}

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

template <typename T>
std::ostream& operator<<(std::ostream& os, const BlockMatrix<T>& matrix) {
    for (size_t i = 0; i < matrix.rows(); ++i) {
        for (size_t j = 0; j < matrix.cols(); ++j) {
            os << matrix(i, j) << " "; // ������� �������� ������
        }
        os << std::endl; // ������� �� ����� ������
    }
    return os; // ���������� �����
}
