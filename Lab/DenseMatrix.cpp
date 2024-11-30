#include "DenseMatrix.h"

// ���������� ������������
template <typename T>
DenseMatrix<T>::DenseMatrix(size_t rows, size_t cols) : rows_(rows), cols_(cols), data(rows, std::vector<T>(cols, T(0))) {}

template <typename T>
DenseMatrix<T>::DenseMatrix(std::initializer_list<std::initializer_list<T>> list) {
    rows_ = list.size();
    cols_ = (list.size() > 0) ? list.begin()->size() : 0;
    data.resize(rows_);
    size_t i = 0;
    for (auto& row : list) {
        data[i++] = row;
    }

    /*��� ������ for (const auto& value : list) {
            diagonalElements.push_back(value);
        }
        //�� Vector
    */
}

// ����������� �����������
template <typename T>
DenseMatrix<T>::DenseMatrix(const DenseMatrix<T>& other) : rows_(other.rows_), cols_(other.cols_), data(other.data) {}

// �������� ������������
template <typename T>
DenseMatrix<T>& DenseMatrix<T>::operator=(const DenseMatrix<T>& other) {
    if (this != &other) {
        rows_ = other.rows_;
        cols_ = other.cols_;
        data = other.data;
    }
    return *this;
}

// ����������
template <typename T>
DenseMatrix<T>::~DenseMatrix() {}; // ����� ������ ������������ default

// �������� ������� � �������� (��������������)
template <typename T>
T& DenseMatrix<T>::operator()(size_t i, size_t j) {
    if (i >= rows_ || j >= cols_) {
        throw std::out_of_range("Index out of range");
    }
    return data[i][j];
}

// �������� ������� � �������� (�����������)
template <typename T>
const T& DenseMatrix<T>::operator()(size_t i, size_t j) const {
    if (i >= rows_ || j >= cols_) {
        throw std::out_of_range("Index out of range");
    }
    return data[i][j];
}

// ����� ��������� ���������� �����
template <typename T>
size_t DenseMatrix<T>::rows() const {
    return rows_;
}

// ����� ��������� ���������� ��������
template <typename T>
size_t DenseMatrix<T>::cols() const {
    return cols_;
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

    DenseMatrix<T> result(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            result(i, j) = (*this)(i, j) + other(i, j);
        }
    }
    return result;
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

    DenseMatrix<T> result(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            result(i, j) = (*this)(i, j) - other(i, j);
        }
    }
    return result;
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

    DenseMatrix<T> result(rows_, other.cols_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < other.cols_; ++j) {
            result(i, j) = T(0); // ������������� �����
            for (size_t k = 0; k < cols_; ++k) {
                result(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }
    return result;
}

// ����� ��� ������ �������
template <typename T>
void DenseMatrix<T>::Print() const {
    std::cout << "Dense Matrix:\n";
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            std::cout << (*this)(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

// ����� ������������ ��� �����
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
