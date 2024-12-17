#include "VectorHCS.h"

// �����������
template <typename T>
VectorHCS<T>::VectorHCS(const VectorParams& vparams, Cluster* cluster)
    : _size(vparams.size), _blockSize(vparams.blockSize),
    _nodeOffset(vparams.nodeOffset), _deviceOffset(vparams.deviceOffset),
    _cluster(cluster) {

    if (_size == 0) {
        throw std::invalid_argument("������ ������� ������ ���� ������ ����");
    }
    if (_blockSize == 0) {
        throw std::invalid_argument("������ ����� ������ ���� ������ ����");
    }
    if (_size % _blockSize != 0) {
        throw std::invalid_argument("������ ������� ������ ���� ������ ������� �����");
    }

    _numNodes = _cluster->GetNodeCount();
    _numBlocks = _size / _blockSize;

    if (_numBlocks > _numNodes) {
        throw std::invalid_argument("���������� ������ ��������� ���������� �����");
    }

    // ������������ ����� �� ����� � �����������
    size_t currentNode = _nodeOffset;
    size_t currentDevice = _deviceOffset;

    for (size_t i = 0; i < _numBlocks; ++i) {

        if (currentNode >= _numNodes) {
            throw std::runtime_error("������������ ����� ��� ������������� ������");
        }

        const ClusterNode* node = _cluster->GetNode(currentNode);

        if (!node) {
            throw std::runtime_error("������������ ���� � ��������");
        }

        // �������� ���������� ������ ����
        size_t deviceIndex = currentDevice % node->GetGpuSpecs().size();

        if (deviceIndex >= node->GetGpuSpecs().size()) {
            throw std::runtime_error("������������ ��������� � ����");
        }

        _blocks.push_back({ node, deviceIndex, new std::vector<T>(_blockSize) });
        ++currentDevice;
        if (currentDevice >= node->GetGpuSpecs().size()) {
            currentDevice = 0;
            ++currentNode;
        }

        // ���������� ���������
        std::cout << "���� " << i << ": ���� " << currentNode << ", ���������� " << deviceIndex << std::endl;
    }
}

// ����������
template <typename T>
VectorHCS<T>::~VectorHCS() {

    // �������� ����� ������ �������� ��� �������� ������������ ������ ��������������� ������� � ����
    auto start = std::chrono::high_resolution_clock::now();

    // �������� ������ ������� �����
    for (Block& block : _blocks) {
        delete block.data; // ����������� ����������� ���������� ������ ��� ������ �����
        // �� ������� block.node, ��� ��� �� ����������� ��������� � ����� ������ ��� ����������� ��������
    }

    // �������� ����� ��������� ��������
    auto end = std::chrono::high_resolution_clock::now();

    // ��������� ������� �� �������
    std::chrono::duration<double> duration = end - start;

    // ������� ����� �������� ��� ������� � �������� ������������������
    std::cout << "�������� ������ ������� � ����������� ��������� �� " << duration.count() << " ������" << std::endl;
}

// ����������� �����������
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

// �������� ����������� ������������
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

    // ����������� ������� ������
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

// ����������� �����������
template <typename T>
VectorHCS<T>::VectorHCS(VectorHCS&& other) noexcept
    : _size(other._size), _blockSize(other._blockSize),
    _nodeOffset(other._nodeOffset), _deviceOffset(other._deviceOffset),
    _cluster(other._cluster),
    _numNodes(other._numNodes), _numBlocks(other._numBlocks),
    _blocks(std::move(other._blocks)) {

    // �������� ��������� � ������������ �������
    for (Block& block : other._blocks) {
        block.data = nullptr;
    }
}

// �������� ������������� ������������
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

    // ����������� ������� ������
    for (Block& block : _blocks) {
        delete block.data;
    }
    _blocks.clear();

    _blocks = std::move(other._blocks);

    // �������� ��������� � ������������ �������
    for (Block& block : other._blocks) {
        block.data = nullptr;
    }

    return *this;
}

// ������ ��� ���������
template <typename T>
T& VectorHCS<T>::operator[](size_t index) {
    if ((index / _blockSize) >= _blocks.size()) {
        throw std::out_of_range("������ ��� ���������");
    }

    return (*_blocks[index / _blockSize].data)[index % _blockSize];
}

// ������ ��� ������
template <typename T>
const T& VectorHCS<T>::operator[](size_t index) const {
    if ((index / _blockSize) >= _blocks.size()) {
        throw std::out_of_range("������ ��� ���������");
    }

    return (*_blocks[index / _blockSize].data)[index % _blockSize];
}

// �������� ��������
template <typename T>
VectorHCS<T> VectorHCS<T>::operator+(const VectorHCS& other) const {

    if (_size != other._size || _blockSize != other._blockSize) {
        throw std::invalid_argument("������� ������ ����� ���������� ����� � ������ �����");
    }

    VectorHCS res(*this);

    for (size_t i = 0; i < _numBlocks; ++i) {
        for (size_t j = 0; j < _blockSize; ++j) {
            (*res._blocks[i].data)[j] += (*other._blocks[i].data)[j];
        }
    }

    return res;

}

// �������� ���������
template <typename T>
VectorHCS<T> VectorHCS<T>::operator-(const VectorHCS& other) const {

    if (_size != other._size || _blockSize != other._blockSize) {
        throw std::invalid_argument("������� ������ ����� ���������� ����� � ������ �����");
    }

    VectorHCS res(*this);

    for (size_t i = 0; i < _numBlocks; ++i) {
        for (size_t j = 0; j < _blockSize; ++j) {
            (*res._blocks[i].data)[j] -= (*other._blocks[i].data)[j];
        }
    }

    return res;

}

// �������� ���������
template <typename T>
VectorHCS<T> VectorHCS<T>::operator*(const VectorHCS& other) const {

    if (_size != other._size || _blockSize != other._blockSize) {
        throw std::invalid_argument("������� ������ ����� ���������� ����� � ������ �����");
    }

    VectorHCS res(*this);

    for (size_t i = 0; i < _numBlocks; ++i) {
        for (size_t j = 0; j < _blockSize; ++j) {
            (*res._blocks[i].data)[j] *= (*other._blocks[i].data)[j];
        }
    }

    return res;
}

// ��������� ������� �� ������
template <typename T>
void VectorHCS<T>::ScaleVector(T scalar) {
    for (size_t i = 0; i < _numBlocks; ++i) {
        for (size_t j = 0; j < _blockSize; ++j) {
            (*_blocks[i].data)[j] *= scalar;
        }
    }
}

// ��������� ������������ ���� ��������
template <typename T>
T VectorHCS<T>::DotProduct(const VectorHCS& other) const {

    if (_size != other._size || _blockSize != other._blockSize) {
        throw std::invalid_argument("������� ������ ����� ���������� ����� � ������ �����");
    }

    T res = 0;

    for (size_t i = 0; i < _numBlocks; ++i) {
        for (size_t j = 0; j < _blockSize; ++j) {
            res += (*_blocks[i].data)[j] * (*other._blocks[i].data)[j];
        }
    }
    return res;

}

// ����� ��� ������ ������ �������
template <typename T>
void VectorHCS<T>::Print(const std::string& name) const {
    std::cout << "\n������ " << name << ":\n";
    for (size_t i = 0; i < _size; ++i) {
        std::cout << name << "[" << i << "] = " << (*this)[i] << std::endl;
    }
}

// ����� ������������ ��� ����������� �������� �����
template class VectorHCS<int>;                       // int: 32-������ ����� ����� (� ����������� ����).
template class VectorHCS<unsigned int>;              // unsigned int: ����������� 32-������ ����� �����.
template class VectorHCS<short>;                     // short: ������ 16-������ ����� �����.
template class VectorHCS<unsigned short>;            // unsigned short: ����������� 16-������ ����� �����.
template class VectorHCS<long>;                       // long: ������ 32-������ �����, �� � ��������� ������ ��� 64-������ ����� (��������, �� 64-��������� ��������).
template class VectorHCS<unsigned long>;              // unsigned long: ����������� ������������� long.
template class VectorHCS<long long>;                 // long long: ����������� ������� 64 ����.
template class VectorHCS<unsigned long long>;        // unsigned long long: ����������� ������������� long long.
template class VectorHCS<float>;                      // float: ������ 32-������ ������������� ����� � ��������� ������.
template class VectorHCS<double>;                     // double: ������ 64-������ ������������� ����� � ��������� ������.
template class VectorHCS<long double>;                // long double: ������ ����������� ������������� ����� � ��������� ������, ������� 80 ���.