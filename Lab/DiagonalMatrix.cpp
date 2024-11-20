#include "DiagonalMatrix.h"

// ���������� ����������
template <typename T>
T& DiagonalMatrix<T>::operator()(size_t i, size_t j) {
    if (i >= rows() || j >= cols()) {
        throw std::out_of_range("Index out of range");
    }
    if (i == j) {
        return diagonalElements[i]; // ���������� ������ �� ������������ �������
    }
    else {
        throw std::out_of_range("Accessing non-diagonal element"); // ���������� ��� ������� � ����������� ���������
    }
}

template <typename T>
const T& DiagonalMatrix<T>::operator()(size_t i, size_t j) const {
    if (i >= rows() || j >= cols()) {
        throw std::out_of_range("Index out of range");
    }
    if (i == j) {
        return diagonalElements[i]; // ���������� ������ �� ������������ �������
    }
    else {
        throw std::out_of_range("Accessing non-diagonal element"); // ���������� ��� ������� � ����������� ���������
    }
}

template <typename T>
DiagonalMatrix<T> DiagonalMatrix<T>::operator+(const DiagonalMatrix<T>& other) const {
    if (rows() != other.rows() || cols() != other.cols()) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition.");
    }

    DiagonalMatrix<T> result(rows());
    for (size_t i = 0; i < rows(); ++i) {
        result(i, i) = diagonalElements[i] + other.diagonalElements[i];
    }
    return result;
}

template <typename T>
DiagonalMatrix<T> DiagonalMatrix<T>::operator-(const DiagonalMatrix<T>& other) const {
    if (rows() != other.rows() || cols() != other.cols()) {
        throw std::invalid_argument("Matrices must have the same dimensions for subtraction.");
    }

    DiagonalMatrix<T> result(rows());
    for (size_t i = 0; i < rows(); ++i) {
        result(i, i) = diagonalElements[i] - other.diagonalElements[i];
    }
    return result;
}

template <typename T>
DiagonalMatrix<T> DiagonalMatrix<T>::operator*(const DiagonalMatrix<T>& other) const {

    if (cols() != other.rows()) { // ��������� �������� ������ ���� cols ������� == rows �������
        throw std::invalid_argument("Number of columns in the first matrix must match number of rows in the second.");
    }

    DiagonalMatrix<T> result(rows());
    for (size_t i = 0; i < rows(); ++i) {
        result(i, i) = diagonalElements[i] * other.diagonalElements[i];
    }
    return result;
}


// ����� ������������ ��� �����
// ����� ������������ ��� ����������� �������� �����

template class DiagonalMatrix<int>;                       // int: 32-������ ����� ����� (� ����������� ����).
template class DiagonalMatrix<unsigned int>;              // unsigned int: ����������� 32-������ ����� �����.
template class DiagonalMatrix<short>;                     // short: ������ 16-������ ����� �����.
template class DiagonalMatrix<unsigned short>;            // unsigned short: ����������� 16-������ ����� �����.
template class DiagonalMatrix<long>;                       // long: ������ 32-������ �����, �� � ��������� ������ ��� 64-������ ����� (��������, �� 64-��������� ��������).
template class DiagonalMatrix<unsigned long>;              // unsigned long: ����������� ������������� long.
template class DiagonalMatrix<long long>;                 // long long: ����������� ������� 64 ����.
template class DiagonalMatrix<unsigned long long>;        // unsigned long long: ����������� ������������� long long.
template class DiagonalMatrix<float>;                      // float: ������ 32-������ ������������� ����� � ��������� ������.
template class DiagonalMatrix<double>;                     // double: ������ 64-������ ������������� ����� � ��������� ������.
template class DiagonalMatrix<long double>;                // long double: ������ ����������� ������������� ����� � ��������� ������, ������� 80 ���.

