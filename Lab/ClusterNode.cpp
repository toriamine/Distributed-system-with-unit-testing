#include "ClusterNode.h"

// Конструктор класса ClusterNode инициализирует узел кластера
// с указанными параметрами спецификаций устройств, такими как
// идентификатор узла, спецификации оперативной памяти, процессора,
// графических карт и других устройств.
ClusterNode::ClusterNode(std::string nodeId, const RamSpec& ramSpec,
    const CpuSpec& cpuSpec, const GpuSpec& gpuSpec,
    const std::unordered_map<std::string, GpuSpec>& gpuSpecs,
    const std::unordered_map<std::string, LanSpec>& lanSpecs,
    const std::unordered_map<std::string, SSDSpec>& ssdSpecs,
    const std::unordered_map<std::string, HDDSpec>& hddSpecs)
    : nodeId_(std::move(nodeId)),  // Перемещаем идентификатор узла для избежания копирования
    ramSpec_(ramSpec),            // Инициализируем спецификацию оперативной памяти
    cpuSpec_(cpuSpec),            // Инициализируем спецификацию процессора
    gpuSpec_(gpuSpec),            // Инициализируем спецификацию графической карты
    gpuSpecs_(gpuSpecs),          // Инициализируем карту дополнительных графических карт
    lanSpecs_(lanSpecs),          // Инициализируем карту сетевых адаптеров
    ssdSpecs_(ssdSpecs),          // Инициализируем карту SSD
    hddSpecs_(hddSpecs) {         // Инициализируем карту HDD
}

// Метод для добавления дополнительной графической карты
// в узел кластера. Если графическая карта с таким же идентификатором
// уже существует, она будет обновлена.
void ClusterNode::AddGpu(const std::string& id, const GpuSpec& gpuSpec) {
    gpuSpecs_[id] = gpuSpec; // Добавление или обновление графической карты по идентификатору
}

// Метод для обновления спецификаций процессора в узле кластера.
void ClusterNode::AddCpu(const CpuSpec& cpuSpec) {
    cpuSpec_ = cpuSpec; // Замена текущей спецификации процессора на новую
}

// Метод для обновления спецификаций оперативной памяти в узле кластера.
void ClusterNode::AddRam(const RamSpec& ramSpec) {
    ramSpec_ = ramSpec; // Замена текущей спецификации оперативной памяти на новую
}

// Метод для добавления сетевого адаптера к узлу. 
// Если адаптер с таким идентификатором уже существует, он будет обновлен.
void ClusterNode::AddLan(const std::string& id, const LanSpec& lanSpec) {
    lanSpecs_[id] = lanSpec; // Добавление или обновление сетевого адаптера по идентификатору
}

// Метод для добавления SSD к узлу. 
// Если SSD с таким идентификатором уже существует, он будет обновлен.
void ClusterNode::AddSSD(const std::string& id, const SSDSpec& ssdSpec) {
    ssdSpecs_[id] = ssdSpec; // Добавление или обновление SSD по идентификатору
}

// Метод для добавления HDD к узлу. 
// Если HDD с таким идентификатором уже существует, он будет обновлен.
void ClusterNode::AddHDD(const std::string& id, const HDDSpec& hddSpec) {
    hddSpecs_[id] = hddSpec; // Добавление или обновление HDD по идентификатору
}
