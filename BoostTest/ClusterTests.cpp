#include <boost/test/unit_test.hpp>
#include "../Lab/Cluster.cpp"
#include "../Lab/ClusterNode.cpp"
#include "../Lab/DeviceSpecs.cpp"

BOOST_AUTO_TEST_SUITE(FullSystemTests)

// Тестовый случай для проверки всей системы
BOOST_AUTO_TEST_CASE(FullSystemTest) {
    // Тестирование класса DeviceSpecs
    // Проверяем создание экземпляра GpuSpec и его методы
    GpuSpec gpu(8.0, 1.5, 200, 500, 2048, "GDDR6", 36, "DirectX 12");
    BOOST_CHECK_EQUAL(gpu.GetMemory(), 8.0);                  // Проверяем, что объем памяти соответствует
    BOOST_CHECK_EQUAL(gpu.GetClockSpeed(), 1.5);              // Проверяем, что тактовая частота соответствует
    BOOST_CHECK_EQUAL(gpu.GetPower(), 200);                   // Проверяем, что потребляемая мощность соответствует
    BOOST_CHECK_EQUAL(gpu.GetCudaCores(), 2048);              // Проверяем количество CUDA ядер
    BOOST_CHECK_EQUAL(gpu.GetMemoryType(), "GDDR6");          // Проверяем тип памяти
    BOOST_CHECK_EQUAL(gpu.GetRayTracingCores(), 36);          // Проверяем количество ядер трассировки лучей
    BOOST_CHECK_EQUAL(gpu.GetApiSupport(), "DirectX 12");     // Проверяем поддержку API

    // Проверяем создание экземпляра CpuSpec и его методы
    CpuSpec cpu(4, 2.8, 150.0, 300.0, 8, 12.0, true, "x86");
    BOOST_CHECK_EQUAL(cpu.GetCoreCount(), 4);                  // Проверяем количество ядер
    BOOST_CHECK_EQUAL(cpu.GetClockSpeed(), 2.8);               // Проверяем тактовую частоту
    BOOST_CHECK_EQUAL(cpu.GetPower(), 150.0);                  // Проверяем потребляемую мощность
    BOOST_CHECK_EQUAL(cpu.GetThreadCount(), 8);                // Проверяем количество потоков
    BOOST_CHECK_EQUAL(cpu.GetCacheSize(), 12.0);              // Проверяем размер кэш-памяти
    BOOST_CHECK(cpu.HasIntegratedGraphics());                   // Проверяем наличие встроенной графики
    BOOST_CHECK_EQUAL(cpu.GetArchitecture(), "x86");           // Проверяем архитектуру

    // Проверяем создание экземпляра RamSpec и его методы
    RamSpec ram(16.0, 3200, 16.0, "DDR4", 1.2, "DIMM", true);
    BOOST_CHECK_EQUAL(ram.GetSize(), 16.0);                    // Проверяем размер оперативной памяти
    BOOST_CHECK_EQUAL(ram.GetMhz(), 3200);                     // Проверяем частоту
    BOOST_CHECK_EQUAL(ram.GetLatency(), 16.0);                 // Проверяем задержку
    BOOST_CHECK_EQUAL(ram.GetMemoryType(), "DDR4");            // Проверяем тип памяти
    BOOST_CHECK_EQUAL(ram.GetVoltage(), 1.2);                  // Проверяем рабочее напряжение
    BOOST_CHECK(ram.HasECC());                                  // Проверяем поддержку ECC

    // Тестирование класса ClusterNode
    // Создаем узел кластера с заданными параметрами
    ClusterNode node("node1", ram, cpu, gpu, {
        {"gpu1", GpuSpec(4.0, 1.2, 150.0, 300.0, 1024, "GDDR5", 20, "DirectX 11")} // Дополнительная графическая карта
        }, {
            {"lan1", LanSpec(10, 50, "Ethernet", "802.11ac", 5.0)} // Сетевой адаптер
        }, {
            {"ssd1", SSDSpec(500, 550, 500, "2.5\"", "SATA", 1000, 800, 300)} // SSD
        }, {
            {"hdd1", HDDSpec(1000, 160, 150, 7200, 64, "3.5\"", 8.0)} // HDD
        });

        // Проверяем получение данных из узла
        BOOST_CHECK_EQUAL(node.GetRamSpec().GetSize(), 16.0);                 // Проверка размера RAM в узле

    BOOST_CHECK_EQUAL(node.GetCpuSpec().GetCoreCount(), 4);               // Проверка количества ядер CPU
    BOOST_CHECK_EQUAL(node.GetGpuSpec().GetMemory(), 8.0);                // Проверка объема основной GPU
    BOOST_CHECK_EQUAL(node.GetGpuSpecs().at("gpu1").GetMemory(), 4.0);    // Проверка объема дополнительной GPU
    BOOST_CHECK_EQUAL(node.GetLanSpecs().at("lan1").GetPower(), 10);       // Проверка мощности сетевого адаптера
    BOOST_CHECK_EQUAL(node.GetSSDSpecs().at("ssd1").GetSize(), 500);       // Проверка размера SSD
    BOOST_CHECK_EQUAL(node.GetHDDSpecs().at("hdd1").GetSize(), 1000);      // Проверка размера HDD

    // Тестирование класса Cluster
    Cluster cluster; // Создаем кластер
    cluster.AddNode(node); // Добавляем узел в кластер
    BOOST_CHECK_EQUAL(cluster.GetNodeCount(), 1); // Проверка, что в кластере один узел

    // Проверка получения узла по идентификатору
    const ClusterNode* retrievedNode = cluster.GetNode("node1");
    BOOST_REQUIRE(retrievedNode != nullptr); // Проверка, что узел успешно найден
    BOOST_CHECK_EQUAL(retrievedNode->GetNodeId(), "node1"); // Проверка идентификатора узла
}

BOOST_AUTO_TEST_SUITE_END()

/*
В этом тесте мы последовательно проверяем:
1. Функциональность класса DeviceSpecs (проверка Get-методов для различных типов устройств).
2. Функциональность класса ClusterNode (проверка создания узла и получения информации о нем).
3. Функциональность класса Cluster (проверка добавления узла и получения узла по идентификатору).
*/
