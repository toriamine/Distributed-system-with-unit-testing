#pragma once

#include <iostream>
#include <vector>
#include <exception>
#include <initializer_list>

template <typename T = double>
class DenseMatrix {
private:
    size_t m, n; // m - ���������� �����, n - ���������� �������
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
    DenseMatrix operator+(const DenseMatrix& other) const {
        // �������� ������������� ��������
        if (m != other.m || n != other.n) {
            throw std::runtime_error("Matrices have incompatible dimensions for addition");
        }

        DenseMatrix result(m, n); // �������������� �������
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                result(i, j) = (*this)(i, j) + other(i, j); // �������� ��������������� ���������
            }
        }
        return result; // ������� ����������
    }

    // �������� ���������
    DenseMatrix operator-(const DenseMatrix& other) const {
        // �������� ������������� ��������
        if (m != other.m || n != other.n) {
            throw std::runtime_error("Matrices have incompatible dimensions for subtraction");
        }

        DenseMatrix result(m, n); // �������������� �������
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                result(i, j) = (*this)(i, j) - other(i, j); // ��������� ��������������� ���������
            }
        }

        return result; // ������� ����������
    }

    // �������� ���������
    DenseMatrix operator*(const DenseMatrix& other) const {
        // �������� ������������� �������� ��� ���������
        if (n != other.m) {
            throw std::runtime_error("Matrices have incompatible dimensions for multiplication");
        }

        DenseMatrix result(m, other.n); // �������������� �������
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < other.n; ++j) {
                result(i, j) = 0; // ������������� � ����
                for (size_t k = 0; k < n; ++k) {
                    result(i, j) += (*this)(i, k) * other(k, j); // ��������� � ���������� ����������
                }
            }
        }
        return result; // ������� ����������
    }

    // ����� ��� ����������� ������������
    /*DenseMatrix KroneckerProduct(const DenseMatrix& other) const {
        // �������������� ������� ����� �������� (m * m') x (n * n')
        DenseMatrix result(m * other.m, n * other.n);

        // �������� �� ��������� ������� �������
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                T a_ij = (*this)(i, j); // ������� �������
                // ��������� �������� �������� �� ��� ������� other
                for (size_t k = 0; k < other.m; ++k) {
                    for (size_t l = 0; l < other.n; ++l) {
                        result(i * other.m + k, j * other.n + l) = a_ij * other(k, l);
                    }
                }
            }
        }
        return result; // ������� �������������� �������
    }*/
};


/*���� ����� ������������ "�������" �������, ������� ������ �������� � ���� ����������� �������. �� ������������� ������� ���:

- �������� ������� �������� ��������.
- ������������� ������� � ������� ������� �������������.
- ����������� �������� � ������� ������������ �����������.
- �������� ������� � ��������� ����� �������� ().
- �������� ��������, ��������� � ��������� � ��������� ������������� ������������.*/