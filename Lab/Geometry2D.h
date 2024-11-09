#pragma once

#include <vector>
#include "AppParams.h"

// Класс для работы с двумерной геометрией
class Geometry2D
{
public:
    // Конструктор, принимающий параметры приложения
    Geometry2D(const AppParams& appParams);

    // Деструктор
    ~Geometry2D();

    // Метод для получения данных по индексам (i, j)
    int GetData(size_t i, size_t j) const;

    // Метод для вывода информации о геометрии на экран
    void Print() const;

private:
    double fragmentSizeX;    // Размер фрагмента по оси X
    double fragmentSizeY;    // Размер фрагмента по оси Y
    size_t fragmentCountX;   // Количество фрагментов по оси X
    size_t fragmentCountY;   // Количество фрагментов по оси Y
    std::vector<int> data;   // Вектор для хранения данных геометрии
};