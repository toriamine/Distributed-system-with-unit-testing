#pragma once

#include "Cluster.h"
#include <stdexcept> // ��� std::out_of_range
#include <iostream>

struct VectorParams {
    size_t size;       // ����� ������ �������
    size_t nodeOffset; // �������� ��� ���� � �������������� �������
    size_t deviceOffset; // �������� ��� ���������� � ������ ����
    size_t blockSize;  // ������ ����� (����� ��������� � ������ �����)
};

// ��������� ����� ��� �������� � �������������� �������
template <typename T>
class VectorHCS {
private:
    size_t _size;       // ����� ������ �������
    size_t _nodeOffset; // �������� ��� ����
    size_t _deviceOffset; // �������� ��� ����������
    size_t _blockSize;  // ������ �����
    Cluster* _cluster;   // ��������� �� �������
    T* _data;           // ��������� �� ������ ������
public:
    // ����������� ������
    VectorHCS(const VectorParams& vparams, Cluster* cluster)// ��������� ��������� ������� � �������, � ������� �� ��� ���������
        : _size(vparams.size), // ������������� ������� �������
        _nodeOffset(vparams.nodeOffset), // ��������� �������� ����
        _deviceOffset(vparams.deviceOffset), // ��������� �������� ����������
        _blockSize(vparams.blockSize), // ��������� ������� �����
        _cluster(cluster), // ������������� ��������� �� �������
        _data(new T[vparams.blockSize]()) { // �������� ������ ��� ������ ������, �������������� ������
        // ���������� ������� ������. ���� ������������, ������� "()" ����� new.
    }

    // ����������
    ~VectorHCS() {
        delete[] _data; // ������������ ������, ���������� ��� ������ ������
    }

    // �������� ������� �� ������� (��������������)
    T& operator[](size_t index) {
        // ��������� ������ � ������ ��������
        size_t localIndex = index - _nodeOffset * _blockSize - _deviceOffset;
        // �������� ������ �� ������� �����
        if (localIndex >= _blockSize) {
            throw std::out_of_range("Index out of range"); // ����������� ����������, ���� ������ ��� ���������
        }
        return _data[localIndex]; // ���������� ������� �� ���������� �������
    }

    // �������� ������� �� ������� (�����������, ����������� ��� ���������)
    const T& operator[](size_t index) const {
        size_t localIndex = index - _nodeOffset * _blockSize - _deviceOffset; // ��������� ������
        if (localIndex >= _blockSize) {
            throw std::out_of_range("Index out of range"); // �������� ������ �� �������
        }
        return _data[localIndex]; // ���������� ������� �� ���������� �������
    }

    // ����� ���������� ��������� �������
    void ScaleVector(T scalar) {
        // �������� ������ ������� ������� �� ������
        for (size_t i = 0; i < _blockSize; ++i) {
            _data[i] *= scalar; // ��������� �������� �� ������
        }
    }

    // ����� ��� ���������� ���������� ������������ ���� ��������
    T DotProduct(const VectorHCS<T>& other) const {
        T result = 0; // ������������� ����������

        // �������� �� ������������ ������� ���� ��������
        size_t count = std::min(_blockSize, other._blockSize);

        for (size_t i = 0; i < count; ++i) {
            size_t indexThis = i; // ������ �������� �������
            // ������ ��� ������� ������� � ������ ��������
            size_t indexOther = i + _nodeOffset * _blockSize + _deviceOffset;

            // ����� �������� ��� �������
            std::cout << "Index in this: " << indexThis
                << ", index in other: " << indexOther << std::endl;

            // �������� ������������ ������� � ������� �������
            if (indexThis >= _blockSize) {

                throw std::out_of_range("Index in this out of range");
            }

            // �������� ������������ ������� � ������ �������
            if (indexOther >= other._blockSize) {
                throw std::out_of_range("Index in other out of range");
            }

            // ��������� ������������
            result += _data[indexThis] * other[indexOther];
        }

        return result; // ���������� ��������� ���������� ������������
    }


};
