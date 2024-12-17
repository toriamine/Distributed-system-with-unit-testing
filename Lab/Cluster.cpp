#include "Cluster.h"

// ����� ��� ���������� ���� � �������
void Cluster::AddNode(const ClusterNode& node) {
    _nodes.push_back(node); // ��������� ���� � ������ �����
    _nodeMap[node.GetNodeId()] = &_nodes.back(); // ��������� ������������ �������������� ���� � ������ ���������� ������������ ����
}

// ����� ��� ��������� ���������� ����� � ��������
std::size_t Cluster::GetNodeCount() const {
    return _nodes.size(); // ���������� ������ ������� �����
}

// ����� ��� ��������� ���� �� ��� ��������������
const ClusterNode* Cluster::GetNode(const std::string& nodeId) const {
    auto it = _nodeMap.find(nodeId); // ����� ���� � ���-������� �� ��������������
    if (it != _nodeMap.end()) { // ���� ���� ������
        return it->second; // ���������� ��������� �� ����
    }
    return nullptr; // ���� ���� �� ������, ���������� nullptr
}

// ����� ��� ��������� ���� �� ��� ��������������
const ClusterNode* Cluster::GetNode(size_t index) const {
    if (index < _nodes.size()) { // ������ �� ������ �������� �� ������� ���������� �����
        return &_nodes[index]; //������� ����
    }
    return nullptr; // ���� ������ ������� �� ������� ���������� �����, ���������� nullptr
}

/*
std::unordered_map � ��� ��������� �� ����������� ���������� C++, ������� ������ ������ � ���� ��� "����-��������". 
�� ����������� ��� ���-�������, ��� ��������� ������ �������� ������ � ��������� �� �����.
�������� ������ <unordered_map>:
"one": 1
- it->first ��������� �� ���� (� ������ ������ "one").
- it->second ��������� �� ��������, ��������� � ���� ������ (� ������ ������ 1).
*/