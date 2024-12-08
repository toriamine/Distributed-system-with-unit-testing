#include "DiagonalMatrix.h"

// �����������
template <typename T>
DiagonalMatrix<T>::DiagonalMatrix(size_t rows, size_t cols) : m(rows), n(cols) {
    diagonal.resize(std::min(m, n), 0); // ������������� ������� ���������
}

// �������� ������� � �������� (��������������)
template <typename T>
T& DiagonalMatrix<T>::operator()(size_t i, size_t j) {
    if (i != j) {
        static T zero = 0; // ����������� ���������� ��� ����������� ����
        return zero; // ���������� 0
    }
    return diagonal[i]; // ���������� ������� ���������
}

// �������� ������� � �������� (�����������)
template <typename T>
const T& DiagonalMatrix<T>::operator()(size_t i, size_t j) const {
    if (i != j) {
        static T zero = 0; // ����������� ���������� ��� ����������� ����
        return zero; // ���������� 0
    }
    return diagonal[i]; // ���������� ������� ���������
}

// ����� ��� ��������� ���������� �����
template <typename T>
size_t DiagonalMatrix<T>::rows() const {
    return m; // ���������� ���������� �����
}

// ����� ��� ��������� ���������� ��������
template <typename T>
size_t DiagonalMatrix<T>::cols() const {
    return n; // ���������� ���������� ��������
}

// �������� ��������
template <typename T>
Matrix<T>* DiagonalMatrix<T>::operator+(const Matrix<T>& other) const {
    const DiagonalMatrix<T>* otherDiagonal = dynamic_cast<const DiagonalMatrix<T>*>(&other);

    // ��������� ������������� ��������
    if (!otherDiagonal || m != otherDiagonal->m || n != otherDiagonal->n) {
        throw std::runtime_error("Matrices have incompatible dimensions for addition");
    }

    DiagonalMatrix<T>* result = new DiagonalMatrix<T>(m, n); // ������� �������������� �������
    for (size_t i = 0; i < std::min(m, n); ++i) {
        (*result)(i, i) = (*this)(i, i) + (*otherDiagonal)(i, i); // �������� ��������������� ������������ ���������
    }
    return result; // ���������� ��������� �� ���������
}


// �������� ���������
template <typename T>
Matrix<T>* DiagonalMatrix<T>::operator-(const Matrix<T>& other) const {
    const DiagonalMatrix<T>* otherDiagonal = dynamic_cast<const DiagonalMatrix<T>*>(&other);
    if (!otherDiagonal || m != otherDiagonal->m || n != otherDiagonal->n) {
        throw std::runtime_error("Matrices have incompatible dimensions for subtraction");
    }

    DiagonalMatrix<T>* result = new DiagonalMatrix<T>(m, n); // ������� �������������� �������
    for (size_t i = 0; i < std::min(m, n); ++i) {
        (*result)(i, i) = (*this)(i, i) - (*otherDiagonal)(i, i); // ��������� ��������������� ������������ ���������
    }
    return result; // ���������� ��������� �� ���������
}

// �������� ���������
template <typename T>
Matrix<T>* DiagonalMatrix<T>::operator*(const Matrix<T>& other) const {
    const DiagonalMatrix<T>* otherDiagonal = dynamic_cast<const DiagonalMatrix<T>*>(&other);
    if (!otherDiagonal || n != otherDiagonal->m) {
        throw std::runtime_error("Matrices have incompatible dimensions for multiplication");
    }

    DiagonalMatrix<T>* result = new DiagonalMatrix<T>(m, otherDiagonal->n); // ������� �������������� �������
    for (size_t i = 0; i < std::min(m, otherDiagonal->n); ++i) {
        (*result)(i, i) = (*this)(i, i) * (*otherDiagonal)(i, i); // ��������� ��������������� ������������ ���������
    }
    return result; // ���������� ��������� �� ���������
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

