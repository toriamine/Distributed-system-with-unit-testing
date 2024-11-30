#pragma once

#include "Cluster.h"
#include <stdexcept> // для std::out_of_range
#include <iostream>

struct VectorParams {
    size_t size;       // Общий размер вектора
    size_t nodeOffset; // Смещение для узла в распределенной системе
    size_t deviceOffset; // Смещение для устройства в рамках узла
    size_t blockSize;  // Размер блока (число элементов в данном блоке)
};

// Шаблонный класс для векторов в распределенной системе
template <typename T>
class VectorHCS {
private:
    size_t _size;       // Общий размер вектора
    size_t _nodeOffset; // Смещение для узла
    size_t _deviceOffset; // Смещение для устройства
    size_t _blockSize;  // Размер блока
    Cluster* _cluster;   // Указатель на кластер
    T* _data;           // Указатель на массив данных
public:
    // Конструктор класса
    VectorHCS(const VectorParams& vparams, Cluster* cluster)// принимает структуру вектора и кластер, в котором мы его размещаем
        : _size(vparams.size), // Инициализация размера вектора
        _nodeOffset(vparams.nodeOffset), // Установка смещения узла
        _deviceOffset(vparams.deviceOffset), // Установка смещения устройства
        _blockSize(vparams.blockSize), // Установка размера блока
        _cluster(cluster), // Инициализация указателя на кластер
        _data(new T[vparams.blockSize]()) { // Выделяем память под массив данных, инициализируем нулями
        // Заполнение массива нулями. Если нежелательно, уберите "()" после new.
    }

    // Деструктор
    ~VectorHCS() {
        delete[] _data; // Освобождение памяти, выделенной под массив данных
    }

    // Оператор доступа по индексу (модифицируемый)
    T& operator[](size_t index) {
        // Локальный индекс с учетом смещений
        size_t localIndex = index - _nodeOffset * _blockSize - _deviceOffset;
        // Проверка выхода за границы блока
        if (localIndex >= _blockSize) {
            throw std::out_of_range("Index out of range"); // Выбрасываем исключение, если индекс вне диапазона
        }
        return _data[localIndex]; // Возвращаем элемент по локальному индексу
    }

    // Оператор доступа по индексу (константный, недоступный для изменения)
    const T& operator[](size_t index) const {
        size_t localIndex = index - _nodeOffset * _blockSize - _deviceOffset; // Локальный индекс
        if (localIndex >= _blockSize) {
            throw std::out_of_range("Index out of range"); // Проверка выхода за границы
        }
        return _data[localIndex]; // Возвращаем элемент по локальному индексу
    }

    // Метод скалярного умножения вектора
    void ScaleVector(T scalar) {
        // Умножаем каждый элемент вектора на скаляр
        for (size_t i = 0; i < _blockSize; ++i) {
            _data[i] *= scalar; // Умножение элемента на скаляр
        }
    }

    // Метод для нахождения скалярного произведения двух векторов
    T DotProduct(const VectorHCS<T>& other) const {
        T result = 0; // Инициализация результата

        // Итерация по минимальному размеру двух векторов
        size_t count = std::min(_blockSize, other._blockSize);

        for (size_t i = 0; i < count; ++i) {
            size_t indexThis = i; // Индекс текущего вектора
            // Индекс для другого вектора с учетом смещений
            size_t indexOther = i + _nodeOffset * _blockSize + _deviceOffset;

            // Вывод индексов для отладки
            std::cout << "Index in this: " << indexThis
                << ", index in other: " << indexOther << std::endl;

            // Проверка правильности индекса в текущем векторе
            if (indexThis >= _blockSize) {

                throw std::out_of_range("Index in this out of range");
            }

            // Проверка правильности индекса в другом векторе
            if (indexOther >= other._blockSize) {
                throw std::out_of_range("Index in other out of range");
            }

            // Скалярное произведение
            result += _data[indexThis] * other[indexOther];
        }

        return result; // Возвращаем результат скалярного произведения
    }


};
