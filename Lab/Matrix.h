#pragma once

//����������� �����
#include <stdexcept>

template <typename T>
class Matrix {
public:
    virtual size_t rows() const = 0;
    virtual size_t cols() const = 0;

    // �� ����� ����������� ������, ���� �� ������������� ��������� ������
    /*virtual T& operator()(size_t i, size_t j) = 0;

    virtual const T& operator()(size_t i, size_t j) const = 0;*/

   /* virtual Matrix<T>* operator+(const Matrix<T>& other) const = 0;
    virtual Matrix<T>* operator-(const Matrix<T>& other) const = 0;
    virtual Matrix<T>* operator*(const Matrix<T>& other) const = 0;*/

    virtual void Print() const = 0;

    virtual ~Matrix() {}; // ����������� ����������
};









