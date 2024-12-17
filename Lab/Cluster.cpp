#include "Cluster.h"

// Метод для добавления узла в кластер
void Cluster::AddNode(const ClusterNode& node) {
    _nodes.push_back(node); // Добавляем узел в вектор узлов
    _nodeMap[node.GetNodeId()] = &_nodes.back(); // Сохраняем соответствие идентификатора узла и адреса последнего добавленного узла
}

// Метод для получения количества узлов в кластере
std::size_t Cluster::GetNodeCount() const {
    return _nodes.size(); // Возвращаем размер вектора узлов
}

// Метод для получения узла по его идентификатору
const ClusterNode* Cluster::GetNode(const std::string& nodeId) const {
    auto it = _nodeMap.find(nodeId); // Поиск узла в хэш-таблице по идентификатору
    if (it != _nodeMap.end()) { // Если узел найден
        return it->second; // Возвращаем указатель на узел
    }
    return nullptr; // Если узел не найден, возвращаем nullptr
}

// Метод для получения узла по его идентификатору
const ClusterNode* Cluster::GetNode(size_t index) const {
    if (index < _nodes.size()) { // Индекс не должен выходить за пределы количества узлов
        return &_nodes[index]; //Возврат узла
    }
    return nullptr; // Если индекс выходит за пределы количества узлов, возвращаем nullptr
}

/*
std::unordered_map — это контейнер из стандартной библиотеки C++, который хранит данные в виде пар "ключ-значение". 
Он организован как хэш-таблица, что позволяет быстро получать доступ к элементам по ключу.
Тонкости класса <unordered_map>:
"one": 1
- it->first ссылается на ключ (в данном случае "one").
- it->second ссылается на значение, связанное с этим ключом (в данном случае 1).
*/