#include "Geometry2D.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

// ����������� ������ Geometry2D
// ��������� ���� ��� ������ ������ ���������, ��������� ������ � �������������� ����������
Geometry2D::Geometry2D(const AppParams& appParams)
{
    std::ifstream file(appParams.geometryFilePath); // �������� �����
    if (!file.is_open()) // �������� ��������� �������� �����
    {
        throw std::runtime_error("Error opening file: " + appParams.geometryFilePath);
    }

    std::string format;
    file >> format; // ������ ������� �����

    // �������� ������������ �������
    if (format != "Geometry_TXT_Format")
    {
        throw std::runtime_error("File must be in Geometry_TXT_Format format");
    }

    // ������ �������� ���������� � �� ����������
    file >> fragmentSizeX >> fragmentSizeY >> fragmentCountX >> fragmentCountY;

    // �������������� ����� � ������� ��� ������
    data.resize(fragmentCountX * fragmentCountY);
    // ������ ������ �� �����
    for (size_t i = 0; i < fragmentCountX * fragmentCountY; ++i)
    {
        file >> data[i];
    }

    file.close(); // �������� �����
}

// ���������� ������ Geometry2D
Geometry2D::~Geometry2D()
{
    
}

// ����� ��� ��������� ������ �� �������� (i, j)
int Geometry2D::GetData(size_t i, size_t j) const
{
    return data[i + j * fragmentCountX]; // ������� �������� �� ������� �� ������������ �������
}

// ����� ��� ������ ���������� � ���������
void Geometry2D::Print() const
{
    std::cout << "--- Geometry2D::Print() ---" << std::endl;
    std::cout << "Fragment size X: " << fragmentSizeX << std::endl;
    std::cout << "Fragment size Y: " << fragmentSizeY << std::endl;
    std::cout << "Fragment count X: " << fragmentCountX << std::endl;
    std::cout << "Fragment count Y: " << fragmentCountY << std::endl;

    std::cout << "Data:" << std::endl;
    // ����� ������ � ��������� ����
    for (size_t i = 0; i < fragmentCountY; ++i)
    {
        for (size_t j = 0; j < fragmentCountX; ++j)
        {
            std::cout << data[j + i * fragmentCountX] << " "; // ����� ��������
        }
        std::cout << std::endl; 
    }
}
