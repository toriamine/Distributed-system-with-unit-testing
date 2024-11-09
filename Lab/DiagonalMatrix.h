#pragma once // ������ �� ������������� ����������� �����

#include <iostream>
#include <vector>
#include <exception> // ��� ��������� ����������

// ��������� ����� ��� ������������ ������
template <typename T = double>
class DiagonalMatrix {
private:
    size_t m, n; // ���������� ����� (m) � �������� (n) � �������
    std::vector<T> diagonal; // ������ ��� �������� ��������� ������� ���������

public:
    // �����������
    DiagonalMatrix(size_t rows, size_t cols) : m(rows), n(cols) {
        // ������������� ������� ��������� �������� min(m, n)
        // ��������� �������� ��� ������� ��������� ����� 0
        diagonal.resize(std::min(m, n), 0);
    }

    // �������� ������� � �������� (��������������)
    T& operator()(size_t i, size_t j) {
        // ���� i � j �� �����, ���������� 0 (�������� ��� ���������)
        if (i != j) {
            static T zero = 0; // ����������� ���������� ��� ����������� ����
            return zero; // ���������� 0
        }
        // ���� i ����� j, ���������� ������� ��������� �� ������� i
        return diagonal[i];
    }

    // �������� ������� � �������� (�����������, ����������� ��� ���������)
    const T& operator()(size_t i, size_t j) const {
        // �������� �� ��� ������������ ����������
        if (i != j) {
            static T zero = 0; // ������� ����������� ����������
            return zero; // ���������� 0
        }
        // ���������� ������� ���������
        return diagonal[i];
    }

    // ����� ��� ��������� ���������� �����
    size_t rows() const {
        return m; // ���������� ���������� �����
    }

    // ����� ��� ��������� ���������� ��������
    size_t cols() const {
        return n; // ���������� ���������� ��������
    }

    // �������� �������� ���� ������������ ������
    DiagonalMatrix operator+(const DiagonalMatrix& other) const {
        // �������� �� ������������� ��������
        if (m != other.m || n != other.n) {
            throw std::runtime_error("Matrices have incompatible dimensions");
        }

        DiagonalMatrix result(m, n); // ������� ���������������� ������������ �������
        // �������� ����������� ������ ��� ������� ���������
        for (size_t i = 0; i < std::min(m, n); ++i) {
            result.diagonal[i] = diagonal[i] + other.diagonal[i]; // �������� ��������������� ������������ ���������
        }
        return result; // ���������� ���������
    }

    // �������� ��������� ���� ������������ ������
    DiagonalMatrix operator-(const DiagonalMatrix& other) const {
        // �������� �� ������������� ��������
        if (m != other.m || n != other.n) {
            throw std::runtime_error("Matrices have incompatible dimensions");
        }

        DiagonalMatrix result(m, n); // ������� ���������������� �������
        // ��������� ����������� ��� ������� ���������
        for (size_t i = 0; i < std::min(m, n); ++i) {
            result.diagonal[i] = diagonal[i] - other.diagonal[i]; // ��������� ��������������� ������������ ���������
        }
        return result; // ���������� ���������
    }

    // �������� ��������� ���� ������������ ������
    DiagonalMatrix operator*(const DiagonalMatrix& other) const {
        // �������� �� ������������� �������� ��� ���������
        if (n != other.m) {
            throw std::runtime_error("Matrices have incompatible dimensions");
        }

        DiagonalMatrix result(m, other.n); // ������� �������������� �������
        // ��������� ����������� ��� ������� ���������

        for (size_t i = 0; i < std::min(m, n); ++i) {
            result.diagonal[i] = diagonal[i] * other.diagonal[i]; // ��������� ��������������� ������������ ���������
        }
        return result; // ���������� ���������
    }
};
