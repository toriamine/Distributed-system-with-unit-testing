#pragma once

//����������� �����

template <typename T>
class Matrix {
public:
    virtual size_t rows() const = 0;
    virtual size_t cols() const = 0;

    virtual Matrix<T>* operator+(const Matrix<T>& other) const = 0;//����� ������� unique_ptr
    virtual Matrix<T>* operator-(const Matrix<T>& other) const = 0;
    virtual Matrix<T>* operator*(const Matrix<T>& other) const = 0;

    virtual ~Matrix() {}; // ����������� ����������
};








