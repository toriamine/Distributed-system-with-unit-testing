#include "Cluster.h"

// ����� ��� ���������� ���� � �������
void Cluster::AddNode(const ClusterNode& node) {
    nodes_.push_back(node); // ��������� ���� � ������ �����
    nodeMap_[node.GetNodeId()] = &nodes_.back(); // ��������� ������������ �������������� ���� � ������ ���������� ������������ ����
}

// ����� ��� ��������� ���������� ����� � ��������
std::size_t Cluster::GetNodeCount() const {
    return nodes_.size(); // ���������� ������ ������� �����
}

// ����� ��� ��������� ���� �� ��� ��������������
const ClusterNode* Cluster::GetNode(const std::string& nodeId) const {
    auto it = nodeMap_.find(nodeId); // ����� ���� � ���-������� �� ��������������
    if (it != nodeMap_.end()) { // ���� ���� ������
        return it->second; // ���������� ��������� �� ����
    }
    return nullptr; // ���� ���� �� ������, ���������� nullptr
}

/*
std::unordered_map � ��� ��������� �� ����������� ���������� C++, ������� ������ ������ � ���� ��� "����-��������". 
�� ����������� ��� ���-�������, ��� ��������� ������ �������� ������ � ��������� �� �����.
�������� ������ <unordered_map>:
"one": 1
- it->first ��������� �� ���� (� ������ ������ "one").
- it->second ��������� �� ��������, ��������� � ���� ������ (� ������ ������ 1).
*/