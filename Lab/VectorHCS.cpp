#include "VectorHCS.h"

// Конструктор
template <typename T>
VectorHCS<T>::VectorHCS(const VectorParams& vparams, Cluster* cluster)
    : _size(vparams.size), _blockSize(vparams.blockSize),
    _nodeOffset(vparams.nodeOffset), _deviceOffset(vparams.deviceOffset),
    _cluster(cluster) {

    if (_size == 0) {
        throw std::invalid_argument("Размер вектора должен быть больше нуля");
    }
    if (_blockSize == 0) {
        throw std::invalid_argument("Размер блока должен быть больше нуля");
    }
    if (_size % _blockSize != 0) {
        throw std::invalid_argument("Размер вектора должен быть кратен размеру блока");
    }

    _numNodes = _cluster->GetNodeCount();
    _numBlocks = _size / _blockSize;

    if (_numBlocks > _numNodes) {
        throw std::invalid_argument("Количество блоков превышает количество узлов");
    }

    // Распределяем блоки по узлам и устройствам
    size_t currentNode = _nodeOffset;
    size_t currentDevice = _deviceOffset;

    for (size_t i = 0; i < _numBlocks; ++i) {

        if (currentNode >= _numNodes) {
            throw std::runtime_error("Недостаточно узлов для распределения блоков");
        }

        const ClusterNode* node = _cluster->GetNode(currentNode);

        if (!node) {
            throw std::runtime_error("Недопустимый узел в кластере");
        }

        // Выбираем устройство внутри узла
        size_t deviceIndex = currentDevice % node->GetGpuSpecs().size();

        if (deviceIndex >= node->GetGpuSpecs().size()) {
            throw std::runtime_error("Недостаточно устройств в узле");
        }

        _blocks.push_back({ node, deviceIndex, new std::vector<T>(_blockSize) });
        ++currentDevice;
        if (currentDevice >= node->GetGpuSpecs().size()) {
            currentDevice = 0;
            ++currentNode;
        }

        // Отладочное сообщение
        std::cout << "Блок " << i << ": Узел " << currentNode << ", Устройство " << deviceIndex << std::endl;
    }
}

// Деструктор
template <typename T>
VectorHCS<T>::~VectorHCS() {

    // Засекаем время начала удаления для проверки корректности работы распределенного вектора в куче
    auto start = std::chrono::high_resolution_clock::now();

    // Удаление данных каждого блока
    for (Block& block : _blocks) {
        delete block.data; // Освобождаем динамически выделенную память для данных блока
        // Не удаляем block.node, так как он управляется кластером и будет удален при уничтожении кластера
    }

    // Засекаем время окончания удаления
    auto end = std::chrono::high_resolution_clock::now();

    // Вычисляем разницу во времени
    std::chrono::duration<double> duration = end - start;

    // Выводим время удаления для отладки и проверки производительности
    std::cout << "Удаление данных вектора в деструкторе завершено за " << duration.count() << " секунд" << std::endl;
}

// Конструктор копирования
template <typename T>
VectorHCS<T>::VectorHCS(const VectorHCS& other)
    : _size(other._size), _blockSize(other._blockSize),
    _nodeOffset(other._nodeOffset), _deviceOffset(other._deviceOffset),
    _cluster(other._cluster),
    _numNodes(other._numNodes), _numBlocks(other._numBlocks) {

    _blocks.reserve(_numBlocks);
    for (const Block& block : other._blocks) {
        _blocks.push_back({ block.node, block.deviceIndex, new std::vector<T>(*block.data) });
    }
}

// Оператор копирующего присваивания
template <typename T>
VectorHCS<T>& VectorHCS<T>::operator=(const VectorHCS& other) {

    if (this == &other) {
        return *this;
    }

    _size = other._size;
    _blockSize = other._blockSize;
    _nodeOffset = other._nodeOffset;
    _deviceOffset = other._deviceOffset;
    _cluster = other._cluster;
    _numNodes = other._numNodes;
    _numBlocks = other._numBlocks;

    // Освобождаем текущие данные
    for (Block& block : _blocks) {
        delete block.data;
    }
    _blocks.clear();

    _blocks.reserve(_numBlocks);
    for (const Block& block : other._blocks) {
        _blocks.push_back({ block.node, block.deviceIndex, new std::vector<T>(*block.data) });
    }

    return *this;
}

// Конструктор перемещения
template <typename T>
VectorHCS<T>::VectorHCS(VectorHCS&& other) noexcept
    : _size(other._size), _blockSize(other._blockSize),
    _nodeOffset(other._nodeOffset), _deviceOffset(other._deviceOffset),
    _cluster(other._cluster),
    _numNodes(other._numNodes), _numBlocks(other._numBlocks),
    _blocks(std::move(other._blocks)) {

    // Обнуляем указатели в перемещенном объекте
    for (Block& block : other._blocks) {
        block.data = nullptr;
    }
}

// Оператор перемещающего присваивания
template <typename T>
VectorHCS<T>& VectorHCS<T>::operator=(VectorHCS&& other) noexcept {

    if (this == &other) {
        return *this;
    }

    _size = other._size;
    _blockSize = other._blockSize;
    _nodeOffset = other._nodeOffset;
    _deviceOffset = other._deviceOffset;
    _cluster = other._cluster;
    _numNodes = other._numNodes;
    _numBlocks = other._numBlocks;

    // Освобождаем текущие данные
    for (Block& block : _blocks) {
        delete block.data;
    }
    _blocks.clear();

    _blocks = std::move(other._blocks);

    // Обнуляем указатели в перемещенном объекте
    for (Block& block : other._blocks) {
        block.data = nullptr;
    }

    return *this;
}

// Доступ для изменения
template <typename T>
T& VectorHCS<T>::operator[](size_t index) {
    if ((index / _blockSize) >= _blocks.size()) {
        throw std::out_of_range("Индекс вне диапазона");
    }

    return (*_blocks[index / _blockSize].data)[index % _blockSize];
}

// Доступ для чтения
template <typename T>
const T& VectorHCS<T>::operator[](size_t index) const {
    if ((index / _blockSize) >= _blocks.size()) {
        throw std::out_of_range("Индекс вне диапазона");
    }

    return (*_blocks[index / _blockSize].data)[index % _blockSize];
}

// Оператор сложения
template <typename T>
VectorHCS<T> VectorHCS<T>::operator+(const VectorHCS& other) const {

    if (_size != other._size || _blockSize != other._blockSize) {
        throw std::invalid_argument("Векторы должны иметь одинаковую длину и размер блока");
    }

    VectorHCS res(*this);

    for (size_t i = 0; i < _numBlocks; ++i) {
        for (size_t j = 0; j < _blockSize; ++j) {
            (*res._blocks[i].data)[j] += (*other._blocks[i].data)[j];
        }
    }

    return res;

}

// Оператор вычитания
template <typename T>
VectorHCS<T> VectorHCS<T>::operator-(const VectorHCS& other) const {

    if (_size != other._size || _blockSize != other._blockSize) {
        throw std::invalid_argument("Векторы должны иметь одинаковую длину и размер блока");
    }

    VectorHCS res(*this);

    for (size_t i = 0; i < _numBlocks; ++i) {
        for (size_t j = 0; j < _blockSize; ++j) {
            (*res._blocks[i].data)[j] -= (*other._blocks[i].data)[j];
        }
    }

    return res;

}

// Оператор умножения
template <typename T>
VectorHCS<T> VectorHCS<T>::operator*(const VectorHCS& other) const {

    if (_size != other._size || _blockSize != other._blockSize) {
        throw std::invalid_argument("Векторы должны иметь одинаковую длину и размер блока");
    }

    VectorHCS res(*this);

    for (size_t i = 0; i < _numBlocks; ++i) {
        for (size_t j = 0; j < _blockSize; ++j) {
            (*res._blocks[i].data)[j] *= (*other._blocks[i].data)[j];
        }
    }

    return res;
}

// Умножение вектора на скаляр
template <typename T>
void VectorHCS<T>::ScaleVector(T scalar) {
    for (size_t i = 0; i < _numBlocks; ++i) {
        for (size_t j = 0; j < _blockSize; ++j) {
            (*_blocks[i].data)[j] *= scalar;
        }
    }
}

// Скалярное произведение двух векторов
template <typename T>
T VectorHCS<T>::DotProduct(const VectorHCS& other) const {

    if (_size != other._size || _blockSize != other._blockSize) {
        throw std::invalid_argument("Векторы должны иметь одинаковую длину и размер блока");
    }

    T res = 0;

    for (size_t i = 0; i < _numBlocks; ++i) {
        for (size_t j = 0; j < _blockSize; ++j) {
            res += (*_blocks[i].data)[j] * (*other._blocks[i].data)[j];
        }
    }
    return res;

}

// Метод для вывода данных вектора
template <typename T>
void VectorHCS<T>::Print(const std::string& name) const {
    std::cout << "\nДанные " << name << ":\n";
    for (size_t i = 0; i < _size; ++i) {
        std::cout << name << "[" << i << "] = " << (*this)[i] << std::endl;
    }
}

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