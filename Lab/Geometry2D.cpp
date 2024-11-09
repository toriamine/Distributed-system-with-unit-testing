#include "Geometry2D.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

// Конструктор класса Geometry2D
// Открывает файл для чтения данных геометрии, проверяет формат и инициализирует переменные
Geometry2D::Geometry2D(const AppParams& appParams)
{
    std::ifstream file(appParams.geometryFilePath); // Открытие файла
    if (!file.is_open()) // Проверка успешного открытия файла
    {
        throw std::runtime_error("Error opening file: " + appParams.geometryFilePath);
    }

    std::string format;
    file >> format; // Чтение формата файла

    // Проверка соответствия формата
    if (format != "Geometry_TXT_Format")
    {
        throw std::runtime_error("File must be in Geometry_TXT_Format format");
    }

    // Чтение размеров фрагментов и их количества
    file >> fragmentSizeX >> fragmentSizeY >> fragmentCountX >> fragmentCountY;

    // Резервирование места в векторе для данных
    data.resize(fragmentCountX * fragmentCountY);
    // Чтение данных из файла
    for (size_t i = 0; i < fragmentCountX * fragmentCountY; ++i)
    {
        file >> data[i];
    }

    file.close(); // Закрытие файла
}

// Деструктор класса Geometry2D
Geometry2D::~Geometry2D()
{
    
}

// Метод для получения данных по индексам (i, j)
int Geometry2D::GetData(size_t i, size_t j) const
{
    return data[i + j * fragmentCountX]; // Возврат элемента из вектора по вычисленному индексу
}

// Метод для вывода информации о геометрии
void Geometry2D::Print() const
{
    std::cout << "--- Geometry2D::Print() ---" << std::endl;
    std::cout << "Fragment size X: " << fragmentSizeX << std::endl;
    std::cout << "Fragment size Y: " << fragmentSizeY << std::endl;
    std::cout << "Fragment count X: " << fragmentCountX << std::endl;
    std::cout << "Fragment count Y: " << fragmentCountY << std::endl;

    std::cout << "Data:" << std::endl;
    // Вывод данных в двумерном виде
    for (size_t i = 0; i < fragmentCountY; ++i)
    {
        for (size_t j = 0; j < fragmentCountX; ++j)
        {
            std::cout << data[j + i * fragmentCountX] << " "; // Вывод элемента
        }
        std::cout << std::endl; 
    }
}
