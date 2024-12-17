#include "DiagonalMatrix.h"

// �����������, ������� ��������� ������ �������� ��� ���������
template<typename T>
DiagonalMatrix<T>::DiagonalMatrix(std::initializer_list<T> initializer_list)
    : data(initializer_list.size(), std::vector<T>(initializer_list.size(), T(0))) {
    size = initializer_list.size();
    size_t index = 0;

    // � ����� ���� ��������� ����������� ��� �������� - ��� ���
    for (typename std::initializer_list<T>::iterator it = initializer_list.begin(); it != initializer_list.end(); ++it) {
        data[index][index] = *it;
        ++index;
    }
}

// �����������, ������� ��������� ������ � ������� �������������
template<typename T>
DiagonalMatrix<T>::DiagonalMatrix(size_t Size)
    : data(Size, std::vector<T>(Size, T(0))) {
    size = Size;
    for (size_t i = 0; i < size; ++i) {
        data[i][i] = T(0);  // ��� �������� �� ��������� ����
    }
}

template <typename T>
T& DiagonalMatrix<T>::operator()(size_t i, size_t j) {
    if (i >= rows() || j >= cols()) {
        throw std::out_of_range("������ ��� ���������.");
    }
    return data[i][j];  
}

template <typename T>
const T& DiagonalMatrix<T>::operator()(size_t i, size_t j) const {
    if (i >= rows() || j >= cols()) {
        throw std::out_of_range("������ ��� ���������.");
    }
    return data[i][j];
}

// ����� ��� ��������� ���������� �����
template <typename T>
size_t DiagonalMatrix<T>::rows() const {
    return size;
}

// ����� ��� ��������� ���������� ��������
template <typename T>
size_t DiagonalMatrix<T>::cols() const {
    return size;
}

template <typename T>
DiagonalMatrix<T> DiagonalMatrix<T>::operator+(const DiagonalMatrix<T>& other) const {

    // �������� �� ������������� �������
    if (rows() != other.rows()) {
        throw std::invalid_argument("���������� ����� � �������� �� ���������."); // ���������� ����� �� ���������
    }
    if (cols() != other.cols()) {
        throw std::invalid_argument("���������� �������� � �������� �� ���������."); // ���������� �������� �� ���������
    }

    DiagonalMatrix<T> res(rows());

    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < rows(); ++j)
        {
            if (i == j)
            {
                res(i, j) = data[i][j] + other.data[i][j];
            }
            
        }
    }
    return res;
}

template <typename T>
DiagonalMatrix<T> DiagonalMatrix<T>::operator-(const DiagonalMatrix<T>& other) const {

    // �������� �� ������������� �������
    if (rows() != other.rows()) {
        throw std::invalid_argument("���������� ����� � �������� �� ���������."); // ���������� ����� �� ���������
    }
    if (cols() != other.cols()) {
        throw std::invalid_argument("���������� �������� � �������� �� ���������."); // ���������� �������� �� ���������
    }

    DiagonalMatrix<T> res(rows());

    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < rows(); ++j)
        {
            if (i == j)
            {
                res(i, j) = data[i][j] - other.data[i][j];
            }

        }
    }
    return res;
}

template <typename T>
DiagonalMatrix<T> DiagonalMatrix<T>::operator*(const DiagonalMatrix<T>& other) const {

    // �������� �� ������������� ������� (����� �������� ������ ������ ��������� � ������ ����� ������)
    if (cols() != other.rows()) {
        throw std::invalid_argument("���������� �������� ������ ������� ������ ��������� � ����������� ����� ������ �������.");
    }

    // �������� �� ������������� ������� (����� �������� ������ ������ ��������� � ������ ����� ������)
    if (rows() != other.cols()) {
        throw std::invalid_argument("���������� ����� ������ ������� ������ ��������� � ����������� �������� ������ �������.");
    }

    DiagonalMatrix<T> res(rows());

    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < rows(); ++j)
        {
            if (i == j)
            {
                res(i, j) = data[i][j] * other.data[i][j];
            }

        }
    }
    return res;
}

// ����� ��� ������ �������

template <typename T>
void DiagonalMatrix<T>::Print() const {

    std::cout << "Diagonal Matrix:\n";

    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < cols(); ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

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