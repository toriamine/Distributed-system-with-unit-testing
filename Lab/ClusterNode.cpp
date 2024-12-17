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
    : _nodeId(std::move(nodeId)),  // ���������� ������������� ���� ��� ��������� �����������
    _ramSpec(ramSpec),            // �������������� ������������ ����������� ������
    _cpuSpec(cpuSpec),            // �������������� ������������ ����������
    _gpuSpec(gpuSpec),            // �������������� ������������ ����������� �����
    _gpuSpecs(gpuSpecs),          // �������������� ����� �������������� ����������� ����
    _lanSpecs(lanSpecs),          // �������������� ����� ������� ���������
    _ssdSpecs(ssdSpecs),          // �������������� ����� SSD
    _hddSpecs(hddSpecs) {         // �������������� ����� HDD
}

// ����� ��� ���������� �������������� ����������� �����
// � ���� ��������. ���� ����������� ����� � ����� �� ���������������
// ��� ����������, ��� ����� ���������.
void ClusterNode::AddGpu(const std::string& id, const GpuSpec& gpuSpec) {
    _gpuSpecs[id] = gpuSpec; // ���������� ��� ���������� ����������� ����� �� ��������������
}

// ����� ��� ���������� ������������ ���������� � ���� ��������
void ClusterNode::AddCpu(const CpuSpec& cpuSpec) {
    _cpuSpec = cpuSpec; // ������ ������� ������������ ���������� �� �����
}

// ����� ��� ���������� ������������ ����������� ������ � ���� ��������
void ClusterNode::AddRam(const RamSpec& ramSpec) {
    _ramSpec = ramSpec; // ������ ������� ������������ ����������� ������ �� �����
}

// ����� ��� ���������� �������� �������� � ����. 
// ���� ������� � ����� ��������������� ��� ����������, �� ����� ��������.
void ClusterNode::AddLan(const std::string& id, const LanSpec& lanSpec) {
    _lanSpecs[id] = lanSpec; // ���������� ��� ���������� �������� �������� �� ��������������
}

// ����� ��� ���������� SSD � ����. 
// ���� SSD � ����� ��������������� ��� ����������, �� ����� ��������.
void ClusterNode::AddSSD(const std::string& id, const SSDSpec& ssdSpec) {
    _ssdSpecs[id] = ssdSpec; // ���������� ��� ���������� SSD �� ��������������
}

// ����� ��� ���������� HDD � ����. 
// ���� HDD � ����� ��������������� ��� ����������, �� ����� ��������.
void ClusterNode::AddHDD(const std::string& id, const HDDSpec& hddSpec) {
    _hddSpecs[id] = hddSpec; // ���������� ��� ���������� HDD �� ��������������
}