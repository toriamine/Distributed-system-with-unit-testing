#pragma once

#include "Cluster.h"
#include <stdexcept>
#include <iostream>

struct VectorParams {
    size_t size;       // Общий размер вектора
    size_t nodeOffset; // Смещение для узла в распределенной системе
    size_t deviceOffset; // Смещение для устройства в рамках узла
    size_t blockSize;  // Размер блока (число элементов в данном блоке), для разделений вычислений по узлам
};

template <typename T>
class VectorHCS {
public:
    VectorHCS(const VectorParams& vparams, Cluster* cluster)
        : _size(vparams.size), _blockSize(vparams.blockSize),
        _nodeOffset(vparams.nodeOffset), _deviceOffset(vparams.deviceOffset),
        _cluster(cluster) {
        if (_size == 0) {
            throw std::invalid_argument("Vector size must be greater than zero");
        }
        if (_blockSize == 0) {
            throw std::invalid_argument("Block size must be greater than zero");
        }
        if (_size % _blockSize != 0) {
            throw std::invalid_argument("Vector size must be a multiple of block size");
        }

        _numNodes = _cluster->GetNodeCount();
        _numBlocks = _size / _blockSize;

        if (_numBlocks > _numNodes) {
            throw std::invalid_argument("Number of blocks exceeds number of nodes");
        }

        // Распределяем блоки по узлам и устройствам
        size_t currentNode = _nodeOffset;
        size_t currentDevice = _deviceOffset;
        for (size_t i = 0; i < _numBlocks; ++i) {
            if (currentNode >= _numNodes) {
                throw std::runtime_error("Not enough nodes to distribute blocks");
            }
            const ClusterNode* node = _cluster->GetNode(currentNode);
            if (!node) {
                throw std::runtime_error("Invalid node in cluster");
            }

            // Выбираем устройство внутри узла
            size_t deviceIndex = currentDevice % node->GetGpuSpecs().size();
            if (deviceIndex >= node->GetGpuSpecs().size()) {
                throw std::runtime_error("Not enough devices in node");
            }

            _blocks.push_back({ node, deviceIndex, new std::vector<T>(_blockSize) });
            ++currentDevice;
            if (currentDevice >= node->GetGpuSpecs().size()) {
                currentDevice = 0;
                ++currentNode;
            }

            // Отладочное сообщение
            std::cout << "Block " << i << ": Node " << currentNode << ", Device " << deviceIndex << std::endl;
        }
    }

    ~VectorHCS() {
        for (auto& block : _blocks) {
            delete block.data;
        }
    }

    T& operator[](size_t index) {
        size_t blockIndex = index / _blockSize;
        size_t localIndex = index % _blockSize;

        if (blockIndex >= _blocks.size()) {
            throw std::out_of_range("Index out of range");
        }

        return (*_blocks[blockIndex].data)[localIndex];
    }

    const T& operator[](size_t index) const {
        size_t blockIndex = index / _blockSize;
        size_t localIndex = index % _blockSize;

        if (blockIndex >= _blocks.size()) {
            throw std::out_of_range("Index out of range");
        }

        return (*_blocks[blockIndex].data)[localIndex];
    }

    VectorHCS operator+(const VectorHCS& other) const {
        if (_size != other._size || _blockSize != other._blockSize) {
            throw std::invalid_argument("Vectors must have the same size and block size");
        }

        VectorHCS result(*this);
        for (size_t i = 0; i < _numBlocks; ++i) {
            for (size_t j = 0; j < _blockSize; ++j) {
                (*result._blocks[i].data)[j] += (*other._blocks[i].data)[j];
            }
        }
        return result;
    }

    VectorHCS operator-(const VectorHCS& other) const {
        if (_size != other._size || _blockSize != other._blockSize) {
            throw std::invalid_argument("Vectors must have the same size and block size");
        }

        VectorHCS result(*this);
        for (size_t i = 0; i < _numBlocks; ++i) {
            for (size_t j = 0; j < _blockSize; ++j) {
                (*result._blocks[i].data)[j] -= (*other._blocks[i].data)[j];
            }
        }
        return result;
    }

    T operator*(const VectorHCS& other) const {
        if (_size != other._size || _blockSize != other._blockSize) {
            throw std::invalid_argument("Vectors must have the same size and block size");
        }

        T result = 0;
        for (size_t i = 0; i < _numBlocks; ++i) {
            for (size_t j = 0; j < _blockSize; ++j) {
                result += (*_blocks[i].data)[j] * (*other._blocks[i].data)[j];
            }
        }
        return result;
    }

    void ScaleVector(T scalar) {
        for (size_t i = 0; i < _numBlocks; ++i) {
            for (size_t j = 0; j < _blockSize; ++j) {
                (*_blocks[i].data)[j] *= scalar;
            }
        }
    }

    T DotProduct(const VectorHCS& other) const {
        if (_size != other._size || _blockSize != other._blockSize) {
            throw std::invalid_argument("Vectors must have the same size and block size");
        }

        T result = 0;
        for (size_t i = 0; i < _numBlocks; ++i) {
            for (size_t j = 0; j < _blockSize; ++j) {
                result += (*_blocks[i].data)[j] * (*other._blocks[i].data)[j];
            }
        }
        return result;
    }

private:
    struct Block {
        const ClusterNode* node;
        size_t deviceIndex;
        std::vector<T>* data;
    };

    size_t _size;
    size_t _blockSize;
    size_t _nodeOffset;
    size_t _deviceOffset;
    size_t _numNodes;
    size_t _numBlocks;
    Cluster* _cluster;
    std::vector<Block> _blocks;
};

// Явная инстанциация для типов
// Явная инстанциация для стандартных числовых типов

template class VectorHCS<int>;                       // int: 32-битное целое число (в большинстве сред).
template class VectorHCS<unsigned int>;              // unsigned int: Беззнаковое 32-битное целое число.
template class VectorHCS<short>;                     // short: Обычно 16-битное целое число.
template class VectorHCS<unsigned short>;            // unsigned short: Беззнаковое 16-битное целое число.
template class VectorHCS<long>;                       // long: Обычно 32-битное целое, но в некоторых средах это 64-битное целое (например, на 64-разрядных системах).
template class VectorHCS<unsigned long>;              // unsigned long: Беззнаковое представление long.
template class VectorHCS<long long>;                 // long long: Гарантирует минимум 64 бита.
template class VectorHCS<unsigned long long>;        // unsigned long long: Беззнаковое представление long long.
template class VectorHCS<float>;                      // float: Обычно 32-битное представление числа с плавающей точкой.
template class VectorHCS<double>;                     // double: Обычно 64-битное представление числа с плавающей точкой.
template class VectorHCS<long double>;                // long double: Обычно расширенное представление числа с плавающей точкой, минимум 80 бит.
