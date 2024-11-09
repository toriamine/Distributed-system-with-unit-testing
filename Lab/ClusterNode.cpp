#include "ClusterNode.h"

// ����������� ������ ClusterNode �������������� ���� ��������
// � ���������� ����������� ������������ ���������, ������ ���
// ������������� ����, ������������ ����������� ������, ����������,
// ����������� ���� � ������ ���������.
ClusterNode::ClusterNode(std::string nodeId, const RamSpec& ramSpec,
    const CpuSpec& cpuSpec, const GpuSpec& gpuSpec,
    const std::unordered_map<std::string, GpuSpec>& gpuSpecs,
    const std::unordered_map<std::string, LanSpec>& lanSpecs,
    const std::unordered_map<std::string, SSDSpec>& ssdSpecs,
    const std::unordered_map<std::string, HDDSpec>& hddSpecs)
    : nodeId_(std::move(nodeId)),  // ���������� ������������� ���� ��� ��������� �����������
    ramSpec_(ramSpec),            // �������������� ������������ ����������� ������
    cpuSpec_(cpuSpec),            // �������������� ������������ ����������
    gpuSpec_(gpuSpec),            // �������������� ������������ ����������� �����
    gpuSpecs_(gpuSpecs),          // �������������� ����� �������������� ����������� ����
    lanSpecs_(lanSpecs),          // �������������� ����� ������� ���������
    ssdSpecs_(ssdSpecs),          // �������������� ����� SSD
    hddSpecs_(hddSpecs) {         // �������������� ����� HDD
}

// ����� ��� ���������� �������������� ����������� �����
// � ���� ��������. ���� ����������� ����� � ����� �� ���������������
// ��� ����������, ��� ����� ���������.
void ClusterNode::AddGpu(const std::string& id, const GpuSpec& gpuSpec) {
    gpuSpecs_[id] = gpuSpec; // ���������� ��� ���������� ����������� ����� �� ��������������
}

// ����� ��� ���������� ������������ ���������� � ���� ��������.
void ClusterNode::AddCpu(const CpuSpec& cpuSpec) {
    cpuSpec_ = cpuSpec; // ������ ������� ������������ ���������� �� �����
}

// ����� ��� ���������� ������������ ����������� ������ � ���� ��������.
void ClusterNode::AddRam(const RamSpec& ramSpec) {
    ramSpec_ = ramSpec; // ������ ������� ������������ ����������� ������ �� �����
}

// ����� ��� ���������� �������� �������� � ����. 
// ���� ������� � ����� ��������������� ��� ����������, �� ����� ��������.
void ClusterNode::AddLan(const std::string& id, const LanSpec& lanSpec) {
    lanSpecs_[id] = lanSpec; // ���������� ��� ���������� �������� �������� �� ��������������
}

// ����� ��� ���������� SSD � ����. 
// ���� SSD � ����� ��������������� ��� ����������, �� ����� ��������.
void ClusterNode::AddSSD(const std::string& id, const SSDSpec& ssdSpec) {
    ssdSpecs_[id] = ssdSpec; // ���������� ��� ���������� SSD �� ��������������
}

// ����� ��� ���������� HDD � ����. 
// ���� HDD � ����� ��������������� ��� ����������, �� ����� ��������.
void ClusterNode::AddHDD(const std::string& id, const HDDSpec& hddSpec) {
    hddSpecs_[id] = hddSpec; // ���������� ��� ���������� HDD �� ��������������
}
