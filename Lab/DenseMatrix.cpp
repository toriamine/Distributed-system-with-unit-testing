#include "DenseMatrix.h"

template <typename T>
DenseMatrix<T>::DenseMatrix(size_t rows, size_t cols) : _rows(rows), _cols(cols), data(rows, std::vector<T>(cols, T(0))) {}

template <typename T>
DenseMatrix<T>::DenseMatrix(std::initializer_list<std::initializer_list<T>> list) {

    // ���������� ���������� ����� ��� ������ ����������������� ������
    _rows = list.size();

    // ���������� ���������� �������� ��� ������ ������ ������ (���� ������ �� ����)
    _cols = (list.size() > 0) ? list.begin()->size() : 0;

    // �������� ������ ������� data �� ���������� �����
    data.resize(_rows);

    // �������� ��� ������� �� ������ ������ ����������������� ������
    typename std::initializer_list<std::initializer_list<T>>::iterator row_it = list.begin();

    // ������ ��� ������� �� ������� data
    size_t i = 0;

    // �������� �� ������ ������ ����������������� ������
    while (row_it != list.end()) {
        // ����������� ������� ������ �� ����������������� ������ ��������������� ������ � data
        data[i++] = *row_it;
        // ��������� � ��������� ������
        ++row_it;
    }
}

// ����������� �����������
template <typename T>
DenseMatrix<T>::DenseMatrix(const DenseMatrix<T>& other) : _rows(other._rows), _cols(other._cols), data(other.data) {}

// �������� ������������
template <typename T>
DenseMatrix<T>& DenseMatrix<T>::operator=(const DenseMatrix<T>& other) {
    if (this != &other) {
        _rows = other._rows;
        _cols = other._cols;
        data = other.data;
    }
    return *this;
}

// ����������
template <typename T>
DenseMatrix<T>::~DenseMatrix() {};


template <typename T>
T& DenseMatrix<T>::operator()(size_t i, size_t j) {
    if (i >= _rows || j >= _cols) {
        throw std::out_of_range("������ ��� ���������.");
    }
    return data[i][j];
}

template <typename T>
const T& DenseMatrix<T>::operator()(size_t i, size_t j) const {
    if (i >= _rows || j >= _cols) {
        throw std::out_of_range("������ ��� ���������.");
    }
    return data[i][j];
}

// ����� ��� ��������� ���������� �����
template <typename T>
size_t DenseMatrix<T>::rows() const {
    return _rows;
}

// ����� ��� ��������� ���������� ��������
template <typename T>
size_t DenseMatrix<T>::cols() const {
    return _cols;
}

// �������� ��������
template <typename T>
DenseMatrix<T> DenseMatrix<T>::operator+(const DenseMatrix<T>& other) const {

    // �������� �� ������������� �������
    if (rows() != other.rows()) {
        throw std::invalid_argument("���������� ����� � �������� �� ���������."); // ���������� ����� �� ���������
    }
    if (cols() != other.cols()) {
        throw std::invalid_argument("���������� �������� � �������� �� ���������."); // ���������� �������� �� ���������
    }

    DenseMatrix<T> res(_rows, _cols);

    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j) {
            res(i, j) = (*this)(i, j) + other(i, j);
        }
    }
    return res;

}

// �������� ���������
template <typename T>
DenseMatrix<T> DenseMatrix<T>::operator-(const DenseMatrix<T>& other) const {

    // �������� �� ������������� �������
    if (rows() != other.rows()) {
        throw std::invalid_argument("���������� ����� � �������� �� ���������."); // ���������� ����� �� ���������
    }
    if (cols() != other.cols()) {
        throw std::invalid_argument("���������� �������� � �������� �� ���������."); // ���������� �������� �� ���������
    }

    DenseMatrix<T> res(_rows, _cols);

    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j) {
            res(i, j) = (*this)(i, j) - other(i, j);
        }
    }
    return res;

}

// �������� ���������
template <typename T>
DenseMatrix<T> DenseMatrix<T>::operator*(const DenseMatrix<T>& other) const {

    // �������� �� ������������� �������
    if (rows() != other.rows()) {
        throw std::invalid_argument("���������� ����� � �������� �� ���������."); // ���������� ����� �� ���������
    }
    if (cols() != other.cols()) {
        throw std::invalid_argument("���������� �������� � �������� �� ���������."); // ���������� �������� �� ���������
    }

    DenseMatrix<T> res(_rows, other._cols);

    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < other._cols; ++j) {
            res(i, j) = T(0); // ������������� �����
            for (size_t k = 0; k < _cols; ++k) {
                res(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }
    return res;

}

// ����� ��� ������ �������
template <typename T>
void DenseMatrix<T>::Print() const {

    std::cout << "Dense Matrix:\n";

    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j) {
            std::cout << (*this)(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

// ����� ������������ ��� ����������� �������� �����
template class DenseMatrix<int>;                       // int: 32-������ ����� ����� (� ����������� ����).
template class DenseMatrix<unsigned int>;              // unsigned int: ����������� 32-������ ����� �����.
template class DenseMatrix<short>;                     // short: ������ 16-������ ����� �����.
template class DenseMatrix<unsigned short>;            // unsigned short: ����������� 16-������ ����� �����.
template class DenseMatrix<long>;                       // long: ������ 32-������ �����, �� � ��������� ������ ��� 64-������ ����� (��������, �� 64-��������� ��������).
template class DenseMatrix<unsigned long>;              // unsigned long: ����������� ������������� long.
template class DenseMatrix<long long>;                 // long long: ����������� ������� 64 ����.
template class DenseMatrix<unsigned long long>;        // unsigned long long: ����������� ������������� long long.
template class DenseMatrix<float>;                      // float: ������ 32-������ ������������� ����� � ��������� ������.
template class DenseMatrix<double>;                     // double: ������ 64-������ ������������� ����� � ��������� ������.
template class DenseMatrix<long double>;                // long double: ������ ����������� ������������� ����� � ��������� ������, ������� 80 ���.