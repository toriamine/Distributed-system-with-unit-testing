#pragma once

#include <vector>
#include <unordered_map>
#include "ClusterNode.h"

// ����� ��� ������������� ��������, ������� �������� ���� (ClusterNode)
class Cluster {
public:
    // ����� ��� ���������� ���� � �������
    void AddNode(const ClusterNode& node);

    // ����� ��� ��������� ���������� ����� � ��������
    std::size_t GetNodeCount() const;

    // ����� ��� ��������� ���� �� ��� ��������������
    const ClusterNode* GetNode(const std::string& nodeId) const;

    const ClusterNode* GetNode(size_t index) const {
        if (index < nodes_.size()) {
            return &nodes_[index];
        }
        return nullptr;
    }

private:
    std::vector<ClusterNode> nodes_;  // ������, �������� ���� ��������
    std::unordered_map<std::string, ClusterNode*> nodeMap_; // ������������ ��������������� ����� � ���������� �� ���
};