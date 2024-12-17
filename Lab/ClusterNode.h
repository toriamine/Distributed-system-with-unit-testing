#pragma once

#include <string>
#include <unordered_map>
#include "DeviceSpecs.h"

// Класс ClusterNode представляет собой узел в кластере,
// который хранит информацию о процессоре, оперативной памяти, 
// графических картах и различных подключаемых устройствах.
class ClusterNode {
public:
    // Конструктор класса, который инициализирует узел с заданными параметрами.
    // Параметры описывают характеристики узла, такие как его идентификатор,
    // спецификации RAM, CPU, GPU и карты подключенного оборудования (LAN, SSD, HDD).
    ClusterNode(std::string nodeId, const RamSpec& ramSpec, const CpuSpec& cpuSpec,
        const GpuSpec& gpuSpec,
        const std::unordered_map<std::string, GpuSpec>& gpuSpecs,
        const std::unordered_map<std::string, LanSpec>& lanSpecs,
        const std::unordered_map<std::string, SSDSpec>& ssdSpecs,
        const std::unordered_map<std::string, HDDSpec>& hddSpecs);

    //Методы

    // Получает уникальный идентификатор узла
    const std::string& GetNodeId() const { return _nodeId; }

    // Получает конкретные спецификации оперативной памяти
    const RamSpec& GetRamSpec() const { return _ramSpec; }

    // Получает конкретные спецификации процессора
    const CpuSpec& GetCpuSpec() const { return _cpuSpec; }

    // Получает спецификации первичной графической карты
    const GpuSpec& GetGpuSpec() const { return _gpuSpec; }

    // Возвращает карту всех доступных графических карт узла
    const std::unordered_map<std::string, GpuSpec>& GetGpuSpecs() const { return _gpuSpecs; }

    // Возвращает карту всех доступных сетевых адаптеров, подключенных к узлу
    const std::unordered_map<std::string, LanSpec>& GetLanSpecs() const { return _lanSpecs; }

    // Возвращает карту всех доступных SSD, подключенных к узлу
    const std::unordered_map<std::string, SSDSpec>& GetSSDSpecs() const { return _ssdSpecs; }

    // Возвращает карту всех доступных HDD, подключенных к узлу
    const std::unordered_map<std::string, HDDSpec>& GetHDDSpecs() const { return _hddSpecs; }

    // Метод для добавления дополнительной графической карты в узел
    void AddGpu(const std::string& id, const GpuSpec& gpuSpec);

    // Метод для обновления спецификаций процессора узла
    void AddCpu(const CpuSpec& cpuSpec);

    // Метод для обновления спецификаций оперативной памяти узла
    void AddRam(const RamSpec& ramSpec);

    // Метод для добавления сетевого адаптера к узлу
    void AddLan(const std::string& id, const LanSpec& lanSpec);

    // Метод для добавления SSD к узлу
    void AddSSD(const std::string& id, const SSDSpec& ssdSpec);

    // Метод для добавления HDD к узлу
    void AddHDD(const std::string& id, const HDDSpec& hddSpec);

private:
    std::string _nodeId;  // Уникальный идентификатор узла в кластере
    RamSpec _ramSpec;     // Спецификации оперативной памяти
    CpuSpec _cpuSpec;     // Спецификации процессора
    GpuSpec _gpuSpec;     // Спецификации основной графической карты

    std::unordered_map<std::string, GpuSpec> _gpuSpecs; // Карта дополнительных графических карт
    std::unordered_map<std::string, LanSpec> _lanSpecs; // Карта сетевых адаптеров
    std::unordered_map<std::string, SSDSpec> _ssdSpecs; // Карта SSD
    std::unordered_map<std::string, HDDSpec> _hddSpecs; // Карта HDD
};