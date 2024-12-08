#pragma once

#include <iostream>
#include "Matrix.h"
#include <vector>
#include <exception>
#include <initializer_list>

// ����������� ������ DenseMatrix, ��������������� �� Matrix
template <typename T>
class DenseMatrix : public Matrix<T> {
private:
    size_t m, n; // ���������� ����� � ��������
    T* data; // ��������� �� �������� �������

public:
    // ����������� � ��������� ���������� ����� � �������
    DenseMatrix(size_t rows, size_t cols)
        : m(rows), n(cols) {
        data = new T[m * n]; // ��������� ������ ��� �������� ���������
        std::fill(data, data + m * n, static_cast<T>(0)); // ������������� ������
    }

    // ����������� � �������������� ���������������� �������
    DenseMatrix(std::initializer_list<std::initializer_list<T>> values)
        : m(values.size()), n(values.begin()->size()) {
        data = new T[m * n]; // ��������� ������
        size_t i = 0;
        // ���������� ������� ���������� �� ����������������� ������
        for (const auto& row : values) {
            size_t j = 0;
            for (const auto& value : row) {
                (*this)(i, j) = value; // ������ ����� ��������
                ++j;
            }
            ++i;
        }
    }

    // ����������� �����������
    DenseMatrix(const DenseMatrix& other)
        : m(other.m), n(other.n) {
        data = new T[m * n]; // ��������� ������
        std::copy(other.data, other.data + m * n, data); // ����������� ������
    }

    // �������� ������������
    DenseMatrix& operator=(const DenseMatrix& other) {
        if (this != &other) { // �������� �� ����������������
            delete[] data; // ������������ ���������� ��������
            m = other.m;
            n = other.n;
            data = new T[m * n]; // ��������� ������
            std::copy(other.data, other.data + m * n, data); // ����������� ������
        }
        return *this;
    }

    // ���������� ��� ������������ ��������
    ~DenseMatrix() {
        delete[] data; // ������������ ������, ���������� ��� ������
    }

    // ������ � ��������� � �������������� ���������� ()
    T& operator()(size_t i, size_t j) {
        return data[i * n + j]; // ������ ������� � ���������� �������
    }

    const T& operator()(size_t i, size_t j) const {
        return data[i * n + j];
    }

    // ��������� ���������� ����� � �������
    size_t rows() const { return m; }
    size_t cols() const { return n; }

    // �������� ��������
    Matrix<T>* operator+(const Matrix<T>& other) const override {
        const DenseMatrix<T>* otherDense = dynamic_cast<const DenseMatrix<T>*>(&other);
        if (!otherDense || m != otherDense->m || n != otherDense->n) {
            throw std::runtime_error("Matrices have incompatible dimensions for addition");
        }

        DenseMatrix<T>* result = new DenseMatrix<T>(m, n); // ������� �������������� �������
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                (*result)(i, j) = (*this)(i, j) + otherDense->operator()(i, j); // �������� ��������������� ���������
            }
        }
        return result; // ���������� ��������� �� ���������
    }


    // �������� ���������
    Matrix<T>* operator-(const Matrix<T>& other) const override {
        const DenseMatrix<T>* otherDense = dynamic_cast<const DenseMatrix<T>*>(&other);
        if (!otherDense || m != otherDense->m || n != otherDense->n) {
            throw std::runtime_error("Matrices have incompatible dimensions for subtraction");
        }

        DenseMatrix<T>* result = new DenseMatrix<T>(m, n); // ������� �������������� �������
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                (*result)(i, j) = (*this)(i, j) - otherDense->operator()(i, j); // ��������� ��������������� ���������
            }
        }
        return result; // ���������� ��������� �� ���������
    }

    // �������� ���������
    Matrix<T>* operator*(const Matrix<T>& other) const override {
        const DenseMatrix<T>* otherDense = dynamic_cast<const DenseMatrix<T>*>(&other);
        if ((!otherDense || m != otherDense->m || n != otherDense->n)) {
            throw std::runtime_error("Matrices have incompatible dimensions for multiplication");
        }

        DenseMatrix<T>* result = new DenseMatrix<T>(m, otherDense->n); // ������� �������������� �������
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < otherDense->n; ++j) {
                (*result)(i, j) = 0; // ������������� � ����
                for (size_t k = 0; k < n; ++k) {
                    (*result)(i, j) += (*this)(i, k) * otherDense->operator()(k, j); // ��������� � ���������� ����������
                }
            }
        }
        return result; // ���������� ��������� �� ���������
    }

};

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

/*���� ����� ������������ "�������" �������, ������� ������ �������� � ���� ����������� �������. �� ������������� ������� ���:

- �������� ������� �������� ��������.
- ������������� ������� � ������� ������� �������������.
- ����������� �������� � ������� ������������ �����������.
- �������� ������� � ��������� ����� �������� ().
- �������� ��������, ��������� � ��������� � ��������� ������������� ������������.*/