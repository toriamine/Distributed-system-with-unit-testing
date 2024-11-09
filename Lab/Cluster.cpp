#include "Cluster.h"

// Метод для добавления узла в кластер
void Cluster::AddNode(const ClusterNode& node) {
    nodes_.push_back(node); // Добавляем узел в вектор узлов
    nodeMap_[node.GetNodeId()] = &nodes_.back(); // Сохраняем соответствие идентификатора узла и адреса последнего добавленного узла
}

// Метод для получения количества узлов в кластере
std::size_t Cluster::GetNodeCount() const {
    return nodes_.size(); // Возвращаем размер вектора узлов
}

// Метод для получения узла по его идентификатору
const ClusterNode* Cluster::GetNode(const std::string& nodeId) const {
    auto it = nodeMap_.find(nodeId); // Поиск узла в хэш-таблице по идентификатору
    if (it != nodeMap_.end()) { // Если узел найден
        return it->second; // Возвращаем указатель на узел
    }
    return nullptr; // Если узел не найден, возвращаем nullptr
}

/*
std::unordered_map — это контейнер из стандартной библиотеки C++, который хранит данные в виде пар "ключ-значение". 
Он организован как хэш-таблица, что позволяет быстро получать доступ к элементам по ключу.
Тонкости класса <unordered_map>:
"one": 1
- it->first ссылается на ключ (в данном случае "one").
- it->second ссылается на значение, связанное с этим ключом (в данном случае 1).
*/