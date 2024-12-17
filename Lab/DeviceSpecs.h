#pragma once

#include <string>

// ����� GpuSpec ������ ������������ ����������� �����
class GpuSpec {
public:

    // ����������� �� ���������
    GpuSpec()
        : _memory(0), _clockSpeed(0), _power(0), _bandwidth(0),
        _cudaCores(0), _rayTracingCores(0) {}

    // ����������� � �����������
    GpuSpec(double memory, double clockSpeed, double power, double bandwidth,
        int cudaCores, const std::string& memoryType, int rayTracingCores,
        const std::string& apiSupport)
        : _memory(memory), _clockSpeed(clockSpeed), _power(power),
        _bandwidth(bandwidth), _cudaCores(cudaCores),
        _memoryType(memoryType), _rayTracingCores(rayTracingCores),
        _apiSupport(apiSupport) {}

    // �������
    double GetMemory() const { return _memory; }
    double GetClockSpeed() const { return _clockSpeed; }
    double GetPower() const { return _power; }
    double GetBandwidth() const { return _bandwidth; }
    int GetCudaCores() const { return _cudaCores; }
    std::string GetMemoryType() const { return _memoryType; }
    int GetRayTracingCores() const { return _rayTracingCores; }
    std::string GetApiSupport() const { return _apiSupport; }

private:
    double _memory;           // ����� ������ � ��
    double _clockSpeed;       // �������� ������� � ���
    double _power;            // ������������ �������� � ��
    double _bandwidth;        // ���������� ����������� � ��/�
    int _cudaCores;           // ���������� CUDA ����
    std::string _memoryType;  // ��� ������ (��������, GDDR5, GDDR6)
    int _rayTracingCores;     // ���������� ���� ��� ����������� �����
    std::string _apiSupport;  // �������������� API (��������, DirectX, OpenGL)
};

// ����� CpuSpec ������ ������������ ����������
class CpuSpec {
public:
    // ����������� �� ���������
    CpuSpec()
        : _coreCount(0), _clockSpeed(0.0), _power(0.0),
        _thermalDesignPower(0.0), _threadCount(0),
        _cacheSize(0.0), _hasIntegratedGraphics(false),
        _architecture("") {}

    // ����������� � �����������
    CpuSpec(int coreCount, double clockSpeed, double power, double thermalDesignPower,
        int threadCount, double cacheSize, bool hasIntegratedGraphics,
        const std::string& architecture)
        : _coreCount(coreCount), _clockSpeed(clockSpeed), _power(power),
        _thermalDesignPower(thermalDesignPower), _threadCount(threadCount),
        _cacheSize(cacheSize), _hasIntegratedGraphics(hasIntegratedGraphics),
        _architecture(architecture) {}

    // �������
    int GetCoreCount() const { return _coreCount; }               // �������� ���������� ���� ����������
    double GetClockSpeed() const { return _clockSpeed; }           // �������� �������� ������� � ���
    double GetPower() const { return _power; }                     // �������� ������������ �������� � ��
    double GetThermalDesignPower() const { return _thermalDesignPower; } // �������� ������������� � ��
    int GetThreadCount() const { return _threadCount; }            // �������� ���������� �������
    double GetCacheSize() const { return _cacheSize; }            // �������� ������ ���-������
    bool HasIntegratedGraphics() const { return _hasIntegratedGraphics; } // ������� ���������� �������
    std::string GetArchitecture() const { return _architecture; }  // �������� ����������� (��������, x86, ARM)

private:
    int _coreCount;                 // ���������� ���� ����������
    double _clockSpeed;             // �������� ������� � ���
    double _power;                  // ������������ �������� � ��
    double _thermalDesignPower;     // �������� �������� � ��
    int _threadCount;               // ���������� �������
    double _cacheSize;              // ������ ���-������ (L1, L2, L3)
    bool _hasIntegratedGraphics;    // ������� ���������� �������
    std::string _architecture;      // ����������� (��������, x86, ARM)
};

// ����� RamSpec ������ ������������ ����������� ������
class RamSpec {
public:
    // ����������� �� ���������
    RamSpec()
        : _size(0.0), _mhz(0.0), _latency(0.0),
        _memoryType(""), _voltage(0.0),
        _formFactor(""), _hasECC(false) {}

    // ����������� � �����������
    RamSpec(double size, double mhz, double latency, const std::string& memoryType,
        double voltage, const std::string& formFactor, bool hasECC)
        : _size(size), _mhz(mhz), _latency(latency),
        _memoryType(memoryType), _voltage(voltage),
        _formFactor(formFactor), _hasECC(hasECC) {}

    // �������
    double GetSize() const { return _size; }                      // �������� ������ ������ � ��
    double GetMhz() const { return _mhz; }                        // �������� ������� ������ � ���
    double GetLatency() const { return _latency; }                // �������� �������� � ������������
    std::string GetMemoryType() const { return _memoryType; }     // �������� ��� ������ (DDR4, DDR5 � �.�.)
    double GetVoltage() const { return _voltage; }                // �������� ������� ���������� � �������
    std::string GetFormFactor() const { return _formFactor; }     // �������� ����-������ (DIMM, SO-DIMM)
    bool HasECC() const { return _hasECC; }                       // ��������� ��������� ECC

private:
    double _size;          // ������ ������ � ��
    double _mhz;           // ������� � ���
    double _latency;       // �������� � ������������
    std::string _memoryType; // ��� ������ (DDR4, DDR5 � �.�.)
    double _voltage;      // ������� ���������� � �������
    std::string _formFactor; // ����-������ (DIMM, SO-DIMM)
    bool _hasECC;         // ��������� ECC
};

// ����� LanSpec ������ ������������ �������� ��������
class LanSpec {
public:
    // ����������� �� ���������
    LanSpec()
        : _power(0.0), _bandwidth(0.0), _interfaceType(""),
        _protocolStandard(""), _latency(0.0) {}

    // ����������� � �����������
    LanSpec(double power, double bandwidth, const std::string& interfaceType,
        const std::string& protocolStandard, double latency)
        : _power(power), _bandwidth(bandwidth),
        _interfaceType(interfaceType),
        _protocolStandard(protocolStandard), _latency(latency) {}

    // �������
    double GetPower() const { return _power; }                      // �������� ������������ �������� � ��
    double GetBandwidth() const { return _bandwidth; }              // �������� ���������� ����������� � ����/�
    std::string GetInterfaceType() const { return _interfaceType; } // �������� ��� ���������� (Ethernet, Wi-Fi)
    std::string GetProtocolStandard() const { return _protocolStandard; } // �������� �������������� ���������
    double GetLatency() const { return _latency; }                  // �������� �������� �������� ������

private:
    double _power;                     // ������������ �������� � ��
    double _bandwidth;                 // ���������� ����������� � ����/�
    std::string _interfaceType;        // ��� ���������� (Ethernet, Wi-Fi)
    std::string _protocolStandard;     // �������������� ��������� (��������, 802.11n/ac/ax)
    double _latency;                   // �������� �������� ������
};

// ����� SSDSpec ������ ������������ SSD (������������� �����������)
class SSDSpec {
public:
    // ����������� �� ���������
    SSDSpec()
        : _size(0.0), _readSpeed(0.0), _writeSpeed(0.0),
        _formFactor(""), _interfaceType(""),
        _randomReadSpeed(0.0), _randomWriteSpeed(0.0),
        _endurance(0.0) {}

    // ����������� � �����������
    SSDSpec(double size, double readSpeed, double writeSpeed, const std::string& formFactor,
        const std::string& interfaceType, double randomReadSpeed, double randomWriteSpeed,
        double endurance)
        : _size(size), _readSpeed(readSpeed), _writeSpeed(writeSpeed),
        _formFactor(formFactor), _interfaceType(interfaceType),
        _randomReadSpeed(randomReadSpeed), _randomWriteSpeed(randomWriteSpeed),
        _endurance(endurance) {}

    // �������
    double GetSize() const { return _size; }                       // �������� ������ � ��
    double GetReadSpeed() const { return _readSpeed; }             // �������� �������� ������ � ��/�
    double GetWriteSpeed() const { return _writeSpeed; }           // �������� �������� ������ � ��/�
    std::string GetFormFactor() const { return _formFactor; }      // �������� ����-������ (2.5", M.2 � �.�.)
    std::string GetInterfaceType() const { return _interfaceType; } // �������� ��������� ����������� (SATA, NVMe)
    double GetRandomReadSpeed() const { return _randomReadSpeed; } // �������� �������� ���������� ������ � ��/�
    double GetRandomWriteSpeed() const { return _randomWriteSpeed; } // �������� �������� ��������� ������ � ��/�
    double GetEndurance() const { return _endurance; }             // �������� ���������� (TBW)

private:
    double _size;                   // ������ � ��
    double _readSpeed;              // �������� ������ � ��/�
    double _writeSpeed;             // �������� ������ � ��/�
    std::string _formFactor;        // ����-������ (��������, 2.5", M.2, PCIe)
    std::string _interfaceType;     // ��������� ����������� (��������, SATA, NVMe)
    double _randomReadSpeed;        // �������� ���������� ������ � ��/�
    double _randomWriteSpeed;       // �������� ��������� ������ � ��/�
    double _endurance;              // ���������� (TBW)
};

// ����� HDDSpec ������ ������������ HDD (������� ������)
class HDDSpec {
public:
    // ����������� �� ���������
    HDDSpec()
        : _size(0.0), _readSpeed(0.0), _writeSpeed(0.0),
        _rpm(0), _bufferSize(0.0),
        _formFactor(""), _averageSeekTime(0.0) {}

    // ����������� � �����������
    HDDSpec(double size, double readSpeed, double writeSpeed, int rpm,
        double bufferSize, const std::string& formFactor, double averageSeekTime)
        : _size(size), _readSpeed(readSpeed), _writeSpeed(writeSpeed),
        _rpm(rpm), _bufferSize(bufferSize),
        _formFactor(formFactor), _averageSeekTime(averageSeekTime) {}

    // �������
    double GetSize() const { return _size; }                       // �������� ������ � ��
    double GetReadSpeed() const { return _readSpeed; }             // �������� �������� ������ � ��/�
    double GetWriteSpeed() const { return _writeSpeed; }           // �������� �������� ������ � ��/�
    int GetRpm() const { return _rpm; }                             // �������� �������� �������� � �������� � ������
    double GetBufferSize() const { return _bufferSize; }           // �������� ������ ������ ����
    std::string GetFormFactor() const { return _formFactor; }      // �������� ����-������ (��������, 3.5", 2.5")
    double GetAverageSeekTime() const { return _averageSeekTime; } // �������� ������� ����� ������

private:
    double _size;              // ������ � ��
    double _readSpeed;         // �������� ������ � ��/�
    double _writeSpeed;        // �������� ������ � ��/�
    int _rpm;                  // �������� �������� ����� � �������� � ������
    double _bufferSize;        // ������ ������ ����
    std::string _formFactor;   // ����-������ (��������, 3.5", 2.5")
    double _averageSeekTime;   // ������� ����� ������
};