#pragma once

#include <string>
#include <unordered_map>
#include "DeviceSpecs.h"

// ����� ClusterNode ������������ ����� ���� � ��������,
// ������� ������ ���������� � ����������, ����������� ������, 
// ����������� ������ � ��������� ������������ �����������.
class ClusterNode {
public:
    // ����������� ������, ������� �������������� ���� � ��������� �����������.
    // ��������� ��������� �������������� ����, ����� ��� ��� �������������,
    // ������������ RAM, CPU, GPU � ����� ������������� ������������ (LAN, SSD, HDD).
    ClusterNode(std::string nodeId, const RamSpec& ramSpec, const CpuSpec& cpuSpec,
        const GpuSpec& gpuSpec,
        const std::unordered_map<std::string, GpuSpec>& gpuSpecs,
        const std::unordered_map<std::string, LanSpec>& lanSpecs,
        const std::unordered_map<std::string, SSDSpec>& ssdSpecs,
        const std::unordered_map<std::string, HDDSpec>& hddSpecs);

    //������

    // �������� ���������� ������������� ����
    const std::string& GetNodeId() const { return _nodeId; }

    // �������� ���������� ������������ ����������� ������
    const RamSpec& GetRamSpec() const { return _ramSpec; }

    // �������� ���������� ������������ ����������
    const CpuSpec& GetCpuSpec() const { return _cpuSpec; }

    // �������� ������������ ��������� ����������� �����
    const GpuSpec& GetGpuSpec() const { return _gpuSpec; }

    // ���������� ����� ���� ��������� ����������� ���� ����
    const std::unordered_map<std::string, GpuSpec>& GetGpuSpecs() const { return _gpuSpecs; }

    // ���������� ����� ���� ��������� ������� ���������, ������������ � ����
    const std::unordered_map<std::string, LanSpec>& GetLanSpecs() const { return _lanSpecs; }

    // ���������� ����� ���� ��������� SSD, ������������ � ����
    const std::unordered_map<std::string, SSDSpec>& GetSSDSpecs() const { return _ssdSpecs; }

    // ���������� ����� ���� ��������� HDD, ������������ � ����
    const std::unordered_map<std::string, HDDSpec>& GetHDDSpecs() const { return _hddSpecs; }

    // ����� ��� ���������� �������������� ����������� ����� � ����
    void AddGpu(const std::string& id, const GpuSpec& gpuSpec);

    // ����� ��� ���������� ������������ ���������� ����
    void AddCpu(const CpuSpec& cpuSpec);

    // ����� ��� ���������� ������������ ����������� ������ ����
    void AddRam(const RamSpec& ramSpec);

    // ����� ��� ���������� �������� �������� � ����
    void AddLan(const std::string& id, const LanSpec& lanSpec);

    // ����� ��� ���������� SSD � ����
    void AddSSD(const std::string& id, const SSDSpec& ssdSpec);

    // ����� ��� ���������� HDD � ����
    void AddHDD(const std::string& id, const HDDSpec& hddSpec);

private:
    std::string _nodeId;  // ���������� ������������� ���� � ��������
    RamSpec _ramSpec;     // ������������ ����������� ������
    CpuSpec _cpuSpec;     // ������������ ����������
    GpuSpec _gpuSpec;     // ������������ �������� ����������� �����

    std::unordered_map<std::string, GpuSpec> _gpuSpecs; // ����� �������������� ����������� ����
    std::unordered_map<std::string, LanSpec> _lanSpecs; // ����� ������� ���������
    std::unordered_map<std::string, SSDSpec> _ssdSpecs; // ����� SSD
    std::unordered_map<std::string, HDDSpec> _hddSpecs; // ����� HDD
};