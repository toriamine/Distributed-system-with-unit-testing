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

    // �������� ���������� ������������� ����.
    const std::string& GetNodeId() const { return nodeId_; }

    // �������� ���������� ������������ ����������� ������.
    const RamSpec& GetRamSpec() const { return ramSpec_; }

    // �������� ���������� ������������ ����������.
    const CpuSpec& GetCpuSpec() const { return cpuSpec_; }

    // �������� ������������ ��������� ����������� �����.
    const GpuSpec& GetGpuSpec() const { return gpuSpec_; }

    // ���������� ����� ���� ��������� ����������� ���� ����.
    const std::unordered_map<std::string, GpuSpec>& GetGpuSpecs() const { return gpuSpecs_; }

    // ���������� ����� ���� ��������� ������� ���������, ������������ � ����.
    const std::unordered_map<std::string, LanSpec>& GetLanSpecs() const { return lanSpecs_; }

    // ���������� ����� ���� ��������� SSD, ������������ � ����.
    const std::unordered_map<std::string, SSDSpec>& GetSSDSpecs() const { return ssdSpecs_; }

    // ���������� ����� ���� ��������� HDD, ������������ � ����.
    const std::unordered_map<std::string, HDDSpec>& GetHDDSpecs() const { return hddSpecs_; }

    // ����� ��� ���������� �������������� ����������� ����� � ����.
    void AddGpu(const std::string& id, const GpuSpec& gpuSpec);

    // ����� ��� ���������� ������������ ���������� ����.
    void AddCpu(const CpuSpec& cpuSpec);

    // ����� ��� ���������� ������������ ����������� ������ ����.
    void AddRam(const RamSpec& ramSpec);

    // ����� ��� ���������� �������� �������� � ����.
    void AddLan(const std::string& id, const LanSpec& lanSpec);

    // ����� ��� ���������� SSD � ����.
    void AddSSD(const std::string& id, const SSDSpec& ssdSpec);

    // ����� ��� ���������� HDD � ����.
    void AddHDD(const std::string& id, const HDDSpec& hddSpec);

private:
    std::string nodeId_;  // ���������� ������������� ���� � ��������
    RamSpec ramSpec_;     // ������������ ����������� ������
    CpuSpec cpuSpec_;     // ������������ ����������

    GpuSpec gpuSpec_;     // ������������ �������� ����������� �����
    std::unordered_map<std::string, GpuSpec> gpuSpecs_; // ����� �������������� ����������� ����
    std::unordered_map<std::string, LanSpec> lanSpecs_; // ����� ������� ���������
    std::unordered_map<std::string, SSDSpec> ssdSpecs_; // ����� SSD
    std::unordered_map<std::string, HDDSpec> hddSpecs_; // ����� HDD
};
