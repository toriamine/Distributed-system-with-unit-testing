#pragma once

#include <vector>
#include "AppParams.h"

// ����� ��� ������ � ��������� ����������
class Geometry2D
{
public:
    // �����������, ����������� ��������� ����������
    Geometry2D(const AppParams& appParams);

    // ����������
    ~Geometry2D();

    // ����� ��� ��������� ������ �� �������� (i, j)
    int GetData(size_t i, size_t j) const;

    // ����� ��� ������ ���������� � ��������� �� �����
    void Print() const;

private:
    double fragmentSizeX;    // ������ ��������� �� ��� X
    double fragmentSizeY;    // ������ ��������� �� ��� Y
    size_t fragmentCountX;   // ���������� ���������� �� ��� X
    size_t fragmentCountY;   // ���������� ���������� �� ��� Y
    std::vector<int> data;   // ������ ��� �������� ������ ���������
};