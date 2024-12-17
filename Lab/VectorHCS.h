#pragma once

#include "Cluster.h"
#include <stdexcept>
#include <iostream>
#include <chrono>
#include <vector>

struct VectorParams {
    size_t size;       // Общий размер вектора
    size_t nodeOffset; // Смещение для узла в распределенной системе
    size_t deviceOffset; // Смещение для устройства в рамках узла
    size_t blockSize;  // Размер блока (число элементов в данном блоке), для разделений вычислений по узлам
};

template <typename T>
class VectorHCS {
public:

    // Конструктор
    VectorHCS(const VectorParams& vparams, Cluster* cluster);

    // Деструктор
    ~VectorHCS();

    // Конструктор копирования
    VectorHCS(const VectorHCS& other);

    // Оператор копирующего присваивания
    VectorHCS& operator=(const VectorHCS& other);

    // Конструктор перемещения
    VectorHCS(VectorHCS&& other) noexcept;

    // Оператор перемещающего присваивания
    VectorHCS& operator=(VectorHCS&& other) noexcept;

    // Оператор доступа для изменения
    T& operator[](size_t index);

    // Оператор доступа для чтения
    const T& operator[](size_t index) const;

    // Оператор для сложения векторов
    VectorHCS operator+(const VectorHCS& other) const;

    // Оператор для вычитания векторов
    VectorHCS operator-(const VectorHCS& other) const;

    // Оператор для умножения векторов
    VectorHCS<T> operator*(const VectorHCS& other) const;

    // Умножение вектора на скаляр
    void ScaleVector(T scalar);

    // Скалярное произведение двух векторов
    T DotProduct(const VectorHCS& other) const;

    // Метод для вывода данных вектора
    void Print(const std::string& name) const;

private:

    /* Тут я изменила структуру класса, теперь в классе есть структура Block, содержащая указатель на узел,
    индекс утройства в узле и соответственно уже распределенные данные для этого узла.
    Фактически переменные класса остались такими же, просто изменился подход на более удобный */

    struct Block {
        const ClusterNode* node; // Указатель на узел
        size_t deviceIndex; // Индекс устройства на узле
        std::vector<T>* data; // Данные для узла
    };

    size_t _size; // Размер вектора
    size_t _blockSize; // Размер блока
    size_t _nodeOffset; // Смещение для узла
    size_t _deviceOffset; // Смещение для устройств
    size_t _numNodes; // Количество узлов
    size_t _numBlocks; // Количество блоков
    Cluster* _cluster; // Кластер, в котором будет распределение по узлам
    std::vector<Block> _blocks; // Вектор блоков с данными для каждого блока
};