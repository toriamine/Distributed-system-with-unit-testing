#pragma once

#include <vector>
#include <unordered_map>
#include "ClusterNode.h"

// Класс для представления кластера, который содержит узлы (ClusterNode)
class Cluster {
public:

    // Метод для добавления узла в кластер
    void AddNode(const ClusterNode& node);

    // Метод для получения количества узлов в кластере
    std::size_t GetNodeCount() const;

    // Метод для получения узла по его идентификатору
    const ClusterNode* GetNode(const std::string& nodeId) const;

    // Метод для получения узла по его индексу
    const ClusterNode* GetNode(size_t index) const;

private:
    std::vector<ClusterNode> _nodes;  // Вектор, хранящий узлы кластера
    std::unordered_map<std::string, ClusterNode*> _nodeMap; // Соответствие идентификаторов узлов и указателей на них в виде карты
};