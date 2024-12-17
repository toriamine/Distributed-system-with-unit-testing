#pragma once

#include <string>

// Класс GpuSpec хранит спецификации графической карты
class GpuSpec {
public:

    // Конструктор по умолчанию
    GpuSpec()
        : _memory(0), _clockSpeed(0), _power(0), _bandwidth(0),
        _cudaCores(0), _rayTracingCores(0) {}

    // Конструктор с параметрами
    GpuSpec(double memory, double clockSpeed, double power, double bandwidth,
        int cudaCores, const std::string& memoryType, int rayTracingCores,
        const std::string& apiSupport)
        : _memory(memory), _clockSpeed(clockSpeed), _power(power),
        _bandwidth(bandwidth), _cudaCores(cudaCores),
        _memoryType(memoryType), _rayTracingCores(rayTracingCores),
        _apiSupport(apiSupport) {}

    // Геттеры
    double GetMemory() const { return _memory; }
    double GetClockSpeed() const { return _clockSpeed; }
    double GetPower() const { return _power; }
    double GetBandwidth() const { return _bandwidth; }
    int GetCudaCores() const { return _cudaCores; }
    std::string GetMemoryType() const { return _memoryType; }
    int GetRayTracingCores() const { return _rayTracingCores; }
    std::string GetApiSupport() const { return _apiSupport; }

private:
    double _memory;           // Объем памяти в ГБ
    double _clockSpeed;       // Тактовая частота в ГГц
    double _power;            // Потребляемая мощность в Вт
    double _bandwidth;        // Пропускная способность в ГБ/с
    int _cudaCores;           // Количество CUDA ядер
    std::string _memoryType;  // Тип памяти (например, GDDR5, GDDR6)
    int _rayTracingCores;     // Количество ядер для трассировки лучей
    std::string _apiSupport;  // Поддерживаемые API (например, DirectX, OpenGL)
};

// Класс CpuSpec хранит спецификации процессора
class CpuSpec {
public:
    // Конструктор по умолчанию
    CpuSpec()
        : _coreCount(0), _clockSpeed(0.0), _power(0.0),
        _thermalDesignPower(0.0), _threadCount(0),
        _cacheSize(0.0), _hasIntegratedGraphics(false),
        _architecture("") {}

    // Конструктор с параметрами
    CpuSpec(int coreCount, double clockSpeed, double power, double thermalDesignPower,
        int threadCount, double cacheSize, bool hasIntegratedGraphics,
        const std::string& architecture)
        : _coreCount(coreCount), _clockSpeed(clockSpeed), _power(power),
        _thermalDesignPower(thermalDesignPower), _threadCount(threadCount),
        _cacheSize(cacheSize), _hasIntegratedGraphics(hasIntegratedGraphics),
        _architecture(architecture) {}

    // Геттеры
    int GetCoreCount() const { return _coreCount; }               // Получить количество ядер процессора
    double GetClockSpeed() const { return _clockSpeed; }           // Получить тактовую частоту в ГГц
    double GetPower() const { return _power; }                     // Получить потребляемую мощность в Вт
    double GetThermalDesignPower() const { return _thermalDesignPower; } // Получить теплопередачу в Вт
    int GetThreadCount() const { return _threadCount; }            // Получить количество потоков
    double GetCacheSize() const { return _cacheSize; }            // Получить размер кэш-памяти
    bool HasIntegratedGraphics() const { return _hasIntegratedGraphics; } // Наличие встроенной графики
    std::string GetArchitecture() const { return _architecture; }  // Получить архитектуру (например, x86, ARM)

private:
    int _coreCount;                 // Количество ядер процессора
    double _clockSpeed;             // Тактовая частота в ГГц
    double _power;                  // Потребляемая мощность в Вт
    double _thermalDesignPower;     // Тепловая мощность в Вт
    int _threadCount;               // Количество потоков
    double _cacheSize;              // Размер кэш-памяти (L1, L2, L3)
    bool _hasIntegratedGraphics;    // Наличие встроенной графики
    std::string _architecture;      // Архитектура (например, x86, ARM)
};

// Класс RamSpec хранит спецификации оперативной памяти
class RamSpec {
public:
    // Конструктор по умолчанию
    RamSpec()
        : _size(0.0), _mhz(0.0), _latency(0.0),
        _memoryType(""), _voltage(0.0),
        _formFactor(""), _hasECC(false) {}

    // Конструктор с параметрами
    RamSpec(double size, double mhz, double latency, const std::string& memoryType,
        double voltage, const std::string& formFactor, bool hasECC)
        : _size(size), _mhz(mhz), _latency(latency),
        _memoryType(memoryType), _voltage(voltage),
        _formFactor(formFactor), _hasECC(hasECC) {}

    // Геттеры
    double GetSize() const { return _size; }                      // Получить размер памяти в ГБ
    double GetMhz() const { return _mhz; }                        // Получить частоту памяти в МГц
    double GetLatency() const { return _latency; }                // Получить задержку в наносекундах
    std::string GetMemoryType() const { return _memoryType; }     // Получить тип памяти (DDR4, DDR5 и т.д.)
    double GetVoltage() const { return _voltage; }                // Получить рабочее напряжение в Вольтах
    std::string GetFormFactor() const { return _formFactor; }     // Получить форм-фактор (DIMM, SO-DIMM)
    bool HasECC() const { return _hasECC; }                       // Проверить поддержку ECC

private:
    double _size;          // Размер памяти в ГБ
    double _mhz;           // Частота в МГц
    double _latency;       // Задержка в наносекундах
    std::string _memoryType; // Тип памяти (DDR4, DDR5 и т.д.)
    double _voltage;      // Рабочее напряжение в Вольтах
    std::string _formFactor; // Форм-фактор (DIMM, SO-DIMM)
    bool _hasECC;         // Поддержка ECC
};

// Класс LanSpec хранит спецификации сетевого адаптера
class LanSpec {
public:
    // Конструктор по умолчанию
    LanSpec()
        : _power(0.0), _bandwidth(0.0), _interfaceType(""),
        _protocolStandard(""), _latency(0.0) {}

    // Конструктор с параметрами
    LanSpec(double power, double bandwidth, const std::string& interfaceType,
        const std::string& protocolStandard, double latency)
        : _power(power), _bandwidth(bandwidth),
        _interfaceType(interfaceType),
        _protocolStandard(protocolStandard), _latency(latency) {}

    // Геттеры
    double GetPower() const { return _power; }                      // Получить потребляемую мощность в Вт
    double GetBandwidth() const { return _bandwidth; }              // Получить пропускную способность в Гбит/с
    std::string GetInterfaceType() const { return _interfaceType; } // Получить тип интерфейса (Ethernet, Wi-Fi)
    std::string GetProtocolStandard() const { return _protocolStandard; } // Получить поддерживаемые протоколы
    double GetLatency() const { return _latency; }                  // Получить задержку передачи данных

private:
    double _power;                     // Потребляемая мощность в Вт
    double _bandwidth;                 // Пропускная способность в Гбит/с
    std::string _interfaceType;        // Тип интерфейса (Ethernet, Wi-Fi)
    std::string _protocolStandard;     // Поддерживаемые стандарты (например, 802.11n/ac/ax)
    double _latency;                   // Задержка передачи данных
};

// Класс SSDSpec хранит спецификации SSD (твердотельных накопителей)
class SSDSpec {
public:
    // Конструктор по умолчанию
    SSDSpec()
        : _size(0.0), _readSpeed(0.0), _writeSpeed(0.0),
        _formFactor(""), _interfaceType(""),
        _randomReadSpeed(0.0), _randomWriteSpeed(0.0),
        _endurance(0.0) {}

    // Конструктор с параметрами
    SSDSpec(double size, double readSpeed, double writeSpeed, const std::string& formFactor,
        const std::string& interfaceType, double randomReadSpeed, double randomWriteSpeed,
        double endurance)
        : _size(size), _readSpeed(readSpeed), _writeSpeed(writeSpeed),
        _formFactor(formFactor), _interfaceType(interfaceType),
        _randomReadSpeed(randomReadSpeed), _randomWriteSpeed(randomWriteSpeed),
        _endurance(endurance) {}

    // Геттеры
    double GetSize() const { return _size; }                       // Получить размер в ГБ
    double GetReadSpeed() const { return _readSpeed; }             // Получить скорость чтения в МБ/с
    double GetWriteSpeed() const { return _writeSpeed; }           // Получить скорость записи в МБ/с
    std::string GetFormFactor() const { return _formFactor; }      // Получить форм-фактор (2.5", M.2 и т.д.)
    std::string GetInterfaceType() const { return _interfaceType; } // Получить интерфейс подключения (SATA, NVMe)
    double GetRandomReadSpeed() const { return _randomReadSpeed; } // Получить скорость случайного чтения в МБ/с
    double GetRandomWriteSpeed() const { return _randomWriteSpeed; } // Получить скорость случайной записи в МБ/с
    double GetEndurance() const { return _endurance; }             // Получить надежность (TBW)

private:
    double _size;                   // Размер в ГБ
    double _readSpeed;              // Скорость чтения в МБ/с
    double _writeSpeed;             // Скорость записи в МБ/с
    std::string _formFactor;        // Форм-фактор (например, 2.5", M.2, PCIe)
    std::string _interfaceType;     // Интерфейс подключения (например, SATA, NVMe)
    double _randomReadSpeed;        // Скорость случайного чтения в МБ/с
    double _randomWriteSpeed;       // Скорость случайной записи в МБ/с
    double _endurance;              // Надежность (TBW)
};

// Класс HDDSpec хранит спецификации HDD (жестких дисков)
class HDDSpec {
public:
    // Конструктор по умолчанию
    HDDSpec()
        : _size(0.0), _readSpeed(0.0), _writeSpeed(0.0),
        _rpm(0), _bufferSize(0.0),
        _formFactor(""), _averageSeekTime(0.0) {}

    // Конструктор с параметрами
    HDDSpec(double size, double readSpeed, double writeSpeed, int rpm,
        double bufferSize, const std::string& formFactor, double averageSeekTime)
        : _size(size), _readSpeed(readSpeed), _writeSpeed(writeSpeed),
        _rpm(rpm), _bufferSize(bufferSize),
        _formFactor(formFactor), _averageSeekTime(averageSeekTime) {}

    // Геттеры
    double GetSize() const { return _size; }                       // Получить размер в ГБ
    double GetReadSpeed() const { return _readSpeed; }             // Получить скорость чтения в МБ/с
    double GetWriteSpeed() const { return _writeSpeed; }           // Получить скорость записи в МБ/с
    int GetRpm() const { return _rpm; }                             // Получить скорость вращения в оборотах в минуту
    double GetBufferSize() const { return _bufferSize; }           // Получить размер буфера кэша
    std::string GetFormFactor() const { return _formFactor; }      // Получить форм-фактор (например, 3.5", 2.5")
    double GetAverageSeekTime() const { return _averageSeekTime; } // Получить среднее время поиска

private:
    double _size;              // Размер в ГБ
    double _readSpeed;         // Скорость чтения в МБ/с
    double _writeSpeed;        // Скорость записи в МБ/с
    int _rpm;                  // Скорость вращения диска в оборотах в минуту
    double _bufferSize;        // Размер буфера кэша
    std::string _formFactor;   // Форм-фактор (например, 3.5", 2.5")
    double _averageSeekTime;   // Среднее время поиска
};