#pragma once

#include "Cluster.h"
#include <stdexcept>
#include <iostream>
#include <chrono>
#include <vector>

struct VectorParams {
    size_t size;       // ����� ������ �������
    size_t nodeOffset; // �������� ��� ���� � �������������� �������
    size_t deviceOffset; // �������� ��� ���������� � ������ ����
    size_t blockSize;  // ������ ����� (����� ��������� � ������ �����), ��� ���������� ���������� �� �����
};

template <typename T>
class VectorHCS {
public:

    // �����������
    VectorHCS(const VectorParams& vparams, Cluster* cluster);

    // ����������
    ~VectorHCS();

    // ����������� �����������
    VectorHCS(const VectorHCS& other);

    // �������� ����������� ������������
    VectorHCS& operator=(const VectorHCS& other);

    // ����������� �����������
    VectorHCS(VectorHCS&& other) noexcept;

    // �������� ������������� ������������
    VectorHCS& operator=(VectorHCS&& other) noexcept;

    // �������� ������� ��� ���������
    T& operator[](size_t index);

    // �������� ������� ��� ������
    const T& operator[](size_t index) const;

    // �������� ��� �������� ��������
    VectorHCS operator+(const VectorHCS& other) const;

    // �������� ��� ��������� ��������
    VectorHCS operator-(const VectorHCS& other) const;

    // �������� ��� ��������� ��������
    VectorHCS<T> operator*(const VectorHCS& other) const;

    // ��������� ������� �� ������
    void ScaleVector(T scalar);

    // ��������� ������������ ���� ��������
    T DotProduct(const VectorHCS& other) const;

    // ����� ��� ������ ������ �������
    void Print(const std::string& name) const;

private:

    /* ��� � �������� ��������� ������, ������ � ������ ���� ��������� Block, ���������� ��������� �� ����,
    ������ ��������� � ���� � �������������� ��� �������������� ������ ��� ����� ����.
    ���������� ���������� ������ �������� ������ ��, ������ ��������� ������ �� ����� ������� */

    struct Block {
        const ClusterNode* node; // ��������� �� ����
        size_t deviceIndex; // ������ ���������� �� ����
        std::vector<T>* data; // ������ ��� ����
    };

    size_t _size; // ������ �������
    size_t _blockSize; // ������ �����
    size_t _nodeOffset; // �������� ��� ����
    size_t _deviceOffset; // �������� ��� ���������
    size_t _numNodes; // ���������� �����
    size_t _numBlocks; // ���������� ������
    Cluster* _cluster; // �������, � ������� ����� ������������� �� �����
    std::vector<Block> _blocks; // ������ ������ � ������� ��� ������� �����
};