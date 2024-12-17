#include <boost/test/unit_test.hpp>
#include "../Lab/VectorHCS.cpp"

// Начало тестового набора для VectorHCS
BOOST_AUTO_TEST_SUITE(VectorHCSTests)

// Тестирование создания и доступа к элементам вектора
BOOST_AUTO_TEST_CASE(VectorHCSTests_CreateAndAccessVectorTest) {

    Cluster cluster;

    RamSpec ramSpec(32.0, 3200.0, 16.0, "DDR4", 1.2, "DIMM", true);
    CpuSpec cpuSpec(8, 3.6, 95.0, 300.0, 16, 12.0, true, "x86");
    GpuSpec gpuSpec(8.0, 1800.0, 250.0, 500.0, 2048, "GDDR6", 36, "DirectX 12");

    std::unordered_map<std::string, GpuSpec> gpuSpecs = {
        {"GPU1", GpuSpec(4.0, 1600.0, 180.0, 300.0, 1024, "GDDR5", 20, "DirectX 11")},
        {"GPU2", GpuSpec(6.0, 1700.0, 220.0, 400.0, 1280, "GDDR5", 26, "DirectX 12")},
    };

    LanSpec lanSpec(20.0, 100.0, "Ethernet", "802.11ac", 5.0);
    SSDSpec ssdSpec(500.0, 550.0, 500.0, "2.5\"", "SATA", 1000.0, 800.0, 300.0);
    HDDSpec hddSpec(1000.0, 160.0, 150.0, 7200, 64.0, "3.5\"", 8.0);

    ClusterNode node1("Node1", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN1", lanSpec} }, { {"SSD1", ssdSpec} }, { {"HDD1", hddSpec} });
    ClusterNode node2("Node2", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN2", lanSpec} }, { {"SSD2", ssdSpec} }, { {"HDD2", hddSpec} });

    cluster.AddNode(node1);
    cluster.AddNode(node2);

    std::cout << "Node count: " << cluster.GetNodeCount() << std::endl;

    VectorParams vparams = { 10, 0, 0, 5 };

    // Проверка параметров
    BOOST_REQUIRE_GT(vparams.size, 0);
    BOOST_REQUIRE_GT(vparams.blockSize, 0);
    BOOST_REQUIRE_EQUAL(vparams.size % vparams.blockSize, 0);

    // Создаем распределенный вектор
    VectorHCS<double> vec(vparams, &cluster);

    // Заполняем вектор данными
    for (size_t i = 0; i < vparams.size; ++i) {
        vec[i] = static_cast<double>(i);
    }

    // Выводим данные вектора
    for (size_t i = 0; i < vparams.size; ++i) {
        std::cout << "vec[" << i << "] = " << vec[i] << std::endl;
    }

    for (size_t i = 0; i < vparams.size; ++i) {
        BOOST_CHECK_CLOSE(vec[i], static_cast<double>(i), 1e-6);
    }

}

// Тестирование умножения вектора на скаляр
BOOST_AUTO_TEST_CASE(VectorHCSTests_ScaleVectorTest) {

    Cluster cluster;

    RamSpec ramSpec(32.0, 3200.0, 16.0, "DDR4", 1.2, "DIMM", true);
    CpuSpec cpuSpec(8, 3.6, 95.0, 300.0, 16, 12.0, true, "x86");
    GpuSpec gpuSpec(8.0, 1800.0, 250.0, 500.0, 2048, "GDDR6", 36, "DirectX 12");

    std::unordered_map<std::string, GpuSpec> gpuSpecs = {
        {"GPU1", GpuSpec(4.0, 1600.0, 180.0, 300.0, 1024, "GDDR5", 20, "DirectX 11")},
        {"GPU2", GpuSpec(6.0, 1700.0, 220.0, 400.0, 1280, "GDDR5", 26, "DirectX 12")},
    };

    LanSpec lanSpec(20.0, 100.0, "Ethernet", "802.11ac", 5.0);
    SSDSpec ssdSpec(500.0, 550.0, 500.0, "2.5\"", "SATA", 1000.0, 800.0, 300.0);
    HDDSpec hddSpec(1000.0, 160.0, 150.0, 7200, 64.0, "3.5\"", 8.0);

    ClusterNode node1("Node1", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN1", lanSpec} }, { {"SSD1", ssdSpec} }, { {"HDD1", hddSpec} });
    ClusterNode node2("Node2", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN2", lanSpec} }, { {"SSD2", ssdSpec} }, { {"HDD2", hddSpec} });

    cluster.AddNode(node1);
    cluster.AddNode(node2);

    std::cout << "Node count: " << cluster.GetNodeCount() << std::endl;

    VectorParams vparams;
    vparams.size = 20;
    vparams.nodeOffset = 0; // Узел: "Node1"
    vparams.deviceOffset = 0;
    vparams.blockSize = 10;

    // Проверка параметров
    BOOST_REQUIRE_GT(vparams.size, 0);
    BOOST_REQUIRE_GT(vparams.blockSize, 0);
    BOOST_REQUIRE_EQUAL(vparams.size % vparams.blockSize, 0);

    VectorHCS<double> vector(vparams, &cluster);

    // Заполняем вектор данными
    for (size_t i = 0; i < vparams.size; ++i) {
        vector[i] = static_cast<double>(i);
    }

    // Умножение вектора на скаляр
    vector.ScaleVector(2.0);

    // Проверяем, что вектор был успешно умножен на скаляр
    for (size_t i = 0; i < vparams.size; ++i) {
        BOOST_CHECK_CLOSE(vector[i], static_cast<double>(i) * 2.0, 1e-6);
    }

    // Проверяем выброс исключения при выходе за пределы вектора
    BOOST_CHECK_THROW(vector[20], std::out_of_range); // Индекс 20 находится за пределами вектора
    BOOST_CHECK_THROW(vector[29], std::out_of_range); // Индекс 29 находится за пределами вектора

}

// Тестирование управления памятью
BOOST_AUTO_TEST_CASE(VectorHCSTests_MemoryManagementTest) {

    /* Этот тест написан для управления памятью вектора, когда он создается как указатель.
    Он написан для исправления ошибки, когда динамически неправильно выделялась память под вектор 
    с типом "VectorHCS<T>*" и соответственно эта память не освобождалась. */

    Cluster cluster;

    RamSpec ramSpec(32.0, 3200.0, 16.0, "DDR4", 1.2, "DIMM", true);
    CpuSpec cpuSpec(8, 3.6, 95.0, 300.0, 16, 12.0, true, "x86");
    GpuSpec gpuSpec(8.0, 1800.0, 250.0, 500.0, 2048, "GDDR6", 36, "DirectX 12");

    std::unordered_map<std::string, GpuSpec> gpuSpecs = {
        {"GPU1", GpuSpec(4.0, 1600.0, 180.0, 300.0, 1024, "GDDR5", 20, "DirectX 11")},
        {"GPU2", GpuSpec(6.0, 1700.0, 220.0, 400.0, 1280, "GDDR5", 26, "DirectX 12")},
    };

    LanSpec lanSpec(20.0, 100.0, "Ethernet", "802.11ac", 5.0);
    SSDSpec ssdSpec(500.0, 550.0, 500.0, "2.5\"", "SATA", 1000.0, 800.0, 300.0);
    HDDSpec hddSpec(1000.0, 160.0, 150.0, 7200, 64.0, "3.5\"", 8.0);

    ClusterNode node1("Node1", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN1", lanSpec} }, { {"SSD1", ssdSpec} }, { {"HDD1", hddSpec} });
    ClusterNode node2("Node2", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN2", lanSpec} }, { {"SSD2", ssdSpec} }, { {"HDD2", hddSpec} });

    cluster.AddNode(node1);
    cluster.AddNode(node2);

    std::cout << "Node count: " << cluster.GetNodeCount() << std::endl;

    VectorParams vparams;
    vparams.size = 20;
    vparams.nodeOffset = 0; // Узел: "Node1"
    vparams.deviceOffset = 0;
    vparams.blockSize = 10;

    // Создаем вектор и выделяем память динамически
    VectorHCS<double>* vector = new VectorHCS<double>(vparams, &cluster);

    BOOST_CHECK(vector != nullptr); // Проверяем, что указатель на вектор не nullptr

    // Заполняем вектор данными
    for (size_t i = 0; i < vparams.size; ++i) {
        (*vector)[i] = static_cast<double>(i);
    }

    // Проверяем, что вектор был успешно заполнен
    for (size_t i = 0; i < vparams.size; ++i) {
        BOOST_CHECK_CLOSE((*vector)[i], static_cast<double>(i), 1e-6);
    }

    delete vector; // Освобождаем память, выделенную под вектор
}

// Скалярное произведение векторов
BOOST_AUTO_TEST_CASE(VectorHCSЕTests_DotProductTest)
{
    Cluster cluster;

    RamSpec ramSpec(32.0, 3200.0, 16.0, "DDR4", 1.2, "DIMM", true);
    CpuSpec cpuSpec(8, 3.6, 95.0, 300.0, 16, 12.0, true, "x86");
    GpuSpec gpuSpec(8.0, 1800.0, 250.0, 500.0, 2048, "GDDR6", 36, "DirectX 12");

    std::unordered_map<std::string, GpuSpec> gpuSpecs = {
        {"GPU1", GpuSpec(4.0, 1600.0, 180.0, 300.0, 1024, "GDDR5", 20, "DirectX 11")},
        {"GPU2", GpuSpec(6.0, 1700.0, 220.0, 400.0, 1280, "GDDR5", 26, "DirectX 12")},
    };

    LanSpec lanSpec(20.0, 100.0, "Ethernet", "802.11ac", 5.0);
    SSDSpec ssdSpec(500.0, 550.0, 500.0, "2.5\"", "SATA", 1000.0, 800.0, 300.0);
    HDDSpec hddSpec(1000.0, 160.0, 150.0, 7200, 64.0, "3.5\"", 8.0);

    ClusterNode node1("Node1", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN1", lanSpec} }, { {"SSD1", ssdSpec} }, { {"HDD1", hddSpec} });
    ClusterNode node2("Node2", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN2", lanSpec} }, { {"SSD2", ssdSpec} }, { {"HDD2", hddSpec} });

    cluster.AddNode(node1);
    cluster.AddNode(node2);

    std::cout << "Node count: " << cluster.GetNodeCount() << std::endl;

    VectorParams vparams;
    vparams.size = 10;
    vparams.nodeOffset = 0;
    vparams.deviceOffset = 0;
    vparams.blockSize = 5;

    // Проверка параметров
    BOOST_REQUIRE_GT(vparams.size, 0);
    BOOST_REQUIRE_GT(vparams.blockSize, 0);
    BOOST_REQUIRE_EQUAL(vparams.size % vparams.blockSize, 0);

    VectorHCS<double> vector1(vparams, &cluster);
    VectorHCS<double> vector2(vparams, &cluster);

    for (size_t i = 0; i < vparams.size; ++i) {
        vector1[i] = static_cast<double>(i);
        vector2[i] = static_cast<double>(i + 1);
    }

    // Скалярное произведение
    double dotProduct = vector1.DotProduct(vector2);
    std::cout << "Dot Product: " << dotProduct << std::endl;

    // Проверяем корректность значения скалярного произведения
    BOOST_CHECK_EQUAL(dotProduct, 330.0);

}

// Тестирование без смещения
BOOST_AUTO_TEST_CASE(VectorHCSTests_TestWithoutOffsets)
{

    Cluster cluster;

    RamSpec ramSpec(32.0, 3200.0, 16.0, "DDR4", 1.2, "DIMM", true);
    CpuSpec cpuSpec(8, 3.6, 95.0, 300.0, 16, 12.0, true, "x86");
    GpuSpec gpuSpec(8.0, 1800.0, 250.0, 500.0, 2048, "GDDR6", 36, "DirectX 12");
    std::unordered_map<std::string, GpuSpec> gpuSpecs = {
        {"GPU1", gpuSpec},
    };

    LanSpec lanSpec(20.0, 100.0, "Ethernet", "802.11ac", 5.0);
    SSDSpec ssdSpec(500.0, 550.0, 500.0, "2.5\"", "SATA", 1000.0, 800.0, 300.0);
    HDDSpec hddSpec(1000.0, 160.0, 150.0, 7200, 64.0, "3.5\"", 8.0);

    ClusterNode node1("Node1", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN1", lanSpec} }, { {"SSD1", ssdSpec} }, { {"HDD1", hddSpec} });
    ClusterNode node2("Node2", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN2", lanSpec} }, { {"SSD2", ssdSpec} }, { {"HDD2", hddSpec} });

    cluster.AddNode(node1);
    cluster.AddNode(node2);

    std::cout << "Node count: " << cluster.GetNodeCount() << std::endl;

    VectorParams vparams;
    vparams.size = 20;
    vparams.nodeOffset = 0;
    vparams.deviceOffset = 0;
    vparams.blockSize = 10;

    // Проверка параметров
    BOOST_REQUIRE_GT(vparams.size, 0);
    BOOST_REQUIRE_GT(vparams.blockSize, 0);
    BOOST_REQUIRE_EQUAL(vparams.size % vparams.blockSize, 0);

    VectorHCS<double> vector(vparams, &cluster);

    for (size_t i = 0; i < 10; ++i) {
        vector[i] = static_cast<double>(i + 1);
    }

    BOOST_CHECK_NO_THROW(vector[0] = 1.0);
    BOOST_CHECK_NO_THROW(vector[9] = 10.0);
    BOOST_CHECK_THROW(vector[-1], std::out_of_range);

    BOOST_CHECK_EQUAL(vector[0], 1.0);
    BOOST_CHECK_EQUAL(vector[9], 10.0);
}

// Тестирование с одним смещением nodeOffset
BOOST_AUTO_TEST_CASE(VectorHCSTests_TestWithNodeOffset)
{
    Cluster cluster;

    RamSpec ramSpec(32.0, 3200.0, 16.0, "DDR4", 1.2, "DIMM", true);
    CpuSpec cpuSpec(8, 3.6, 95.0, 300.0, 16, 12.0, true, "x86");
    GpuSpec gpuSpec(8.0, 1800.0, 250.0, 500.0, 2048, "GDDR6", 36, "DirectX 12");

    std::unordered_map<std::string, GpuSpec> gpuSpecs = {
        {"GPU1", GpuSpec(4.0, 1600.0, 180.0, 300.0, 1024, "GDDR5", 20, "DirectX 11")},
        {"GPU2", GpuSpec(6.0, 1700.0, 220.0, 400.0, 1280, "GDDR5", 26, "DirectX 12")},
    };

    LanSpec lanSpec(20.0, 100.0, "Ethernet", "802.11ac", 5.0);
    SSDSpec ssdSpec(500.0, 550.0, 500.0, "2.5\"", "SATA", 1000.0, 800.0, 300.0);
    HDDSpec hddSpec(1000.0, 160.0, 150.0, 7200, 64.0, "3.5\"", 8.0);

    ClusterNode node1("Node1", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN1", lanSpec} }, { {"SSD1", ssdSpec} }, { {"HDD1", hddSpec} });
    ClusterNode node2("Node2", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN2", lanSpec} }, { {"SSD2", ssdSpec} }, { {"HDD2", hddSpec} });

    cluster.AddNode(node1);
    cluster.AddNode(node2);

    std::cout << "Node count: " << cluster.GetNodeCount() << std::endl;

    VectorParams vparams;
    vparams.size = 20;
    vparams.nodeOffset = 1; // Узел "Node2"
    vparams.deviceOffset = 0;
    vparams.blockSize = 10;

    // Проверка параметров
    BOOST_REQUIRE_GT(vparams.size, 0);
    BOOST_REQUIRE_GT(vparams.blockSize, 0);
    BOOST_REQUIRE_EQUAL(vparams.size % vparams.blockSize, 0);

    VectorHCS<double> vector(vparams, &cluster);

    // Заполняем вектор для узла 1 с учетом смещений
    size_t startIndex = vparams.nodeOffset * vparams.blockSize + vparams.deviceOffset;
    for (size_t i = 0; i < vparams.blockSize; ++i) {
        vector[startIndex + i] = static_cast<double>(i + 1);
    }

    // Проверяем корректность значения с учетом смещения
    BOOST_CHECK_EQUAL(vector[10], 1.0);
    BOOST_CHECK_EQUAL(vector[19], 10.0);

    BOOST_CHECK_NO_THROW(vector[10] = 1.0);
    BOOST_CHECK_NO_THROW(vector[19] = 10.0);

    // Проверяем выброс исключения при выходе за пределы вектора
    BOOST_CHECK_THROW(vector[20], std::out_of_range); // Индекс 20 находится за пределами вектора
    BOOST_CHECK_THROW(vector[29], std::out_of_range); // Индекс 29 находится за пределами вектора
}

//Тестирование с одним смещением deviceOffset
BOOST_AUTO_TEST_CASE(VectorHCSTests_TestWithDeviceOffset)
{
    Cluster cluster;

    RamSpec ramSpec(32.0, 3200.0, 16.0, "DDR4", 1.2, "DIMM", true);
    CpuSpec cpuSpec(8, 3.6, 95.0, 300.0, 16, 12.0, true, "x86");
    GpuSpec gpuSpec(8.0, 1800.0, 250.0, 500.0, 2048, "GDDR6", 36, "DirectX 12");

    std::unordered_map<std::string, GpuSpec> gpuSpecs = {
        {"GPU1", GpuSpec(4.0, 1600.0, 180.0, 300.0, 1024, "GDDR5", 20, "DirectX 11")},
        {"GPU2", GpuSpec(6.0, 1700.0, 220.0, 400.0, 1280, "GDDR5", 26, "DirectX 12")},
    };

    LanSpec lanSpec(20.0, 100.0, "Ethernet", "802.11ac", 5.0);
    SSDSpec ssdSpec(500.0, 550.0, 500.0, "2.5\"", "SATA", 1000.0, 800.0, 300.0);
    HDDSpec hddSpec(1000.0, 160.0, 150.0, 7200, 64.0, "3.5\"", 8.0);

    ClusterNode node1("Node1", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN1", lanSpec} }, { {"SSD1", ssdSpec} }, { {"HDD1", hddSpec} });
    ClusterNode node2("Node2", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN2", lanSpec} }, { {"SSD2", ssdSpec} }, { {"HDD2", hddSpec} });

    cluster.AddNode(node1);
    cluster.AddNode(node2);

    std::cout << "Node count: " << cluster.GetNodeCount() << std::endl;

    VectorParams vparams;
    vparams.size = 20;
    vparams.nodeOffset = 0; // Узел: "Node1"
    vparams.deviceOffset = 1; // Второе устройство: "GPU2"
    vparams.blockSize = 10;

    // Проверка параметров
    BOOST_REQUIRE_GT(vparams.size, 0);
    BOOST_REQUIRE_GT(vparams.blockSize, 0);
    BOOST_REQUIRE_EQUAL(vparams.size % vparams.blockSize, 0);

    VectorHCS<double> vector(vparams, &cluster);

    size_t startIndex = vparams.nodeOffset * vparams.blockSize + vparams.deviceOffset;
    for (size_t i = 0; i < vparams.blockSize; ++i) {
        vector[startIndex + i] = static_cast<double>(i + 1);
    }

    // Проверяем корректность значений
    BOOST_CHECK_EQUAL(vector[1], 1.0);
    BOOST_CHECK_EQUAL(vector[10], 10.0);

    BOOST_CHECK_NO_THROW(vector[1] = 1.0);
    BOOST_CHECK_NO_THROW(vector[10] = 10.0);

    // Проверяем выброс исключения при выходе за пределы вектора
    BOOST_CHECK_THROW(vector[20], std::out_of_range); // Индекс 20 находится за пределами вектора
    BOOST_CHECK_THROW(vector[29], std::out_of_range); // Индекс 29 находится за пределами вектора
}

//Тестирование с обоими смещениями
BOOST_AUTO_TEST_CASE(VectorHCSTests_TestWithNodeAndDeviceOffsets)
{
    Cluster cluster;

    RamSpec ramSpec(32.0, 3200.0, 16.0, "DDR4", 1.2, "DIMM", true);
    CpuSpec cpuSpec(8, 3.6, 95.0, 300.0, 16, 12.0, true, "x86");
    GpuSpec gpuSpec1(8.0, 1800.0, 250.0, 500.0, 2048, "GDDR6", 36, "DirectX 12");
    GpuSpec gpuSpec2(8.0, 1800.0, 250.0, 500.0, 2048, "GDDR6", 36, "DirectX 12");

    std::unordered_map<std::string, GpuSpec> gpuSpecs1 = {
        {"GPU1", gpuSpec1},
        {"GPU2", gpuSpec2}
    };

    std::unordered_map<std::string, GpuSpec> gpuSpecs2 = {
        {"GPU1", gpuSpec1},
        {"GPU2", gpuSpec2}
    };

    LanSpec lanSpec(20.0, 100.0, "Ethernet", "802.11ac", 5.0);
    SSDSpec ssdSpec(500.0, 550.0, 500.0, "2.5\"", "SATA", 1000.0, 800.0, 300.0);
    HDDSpec hddSpec(1000.0, 160.0, 150.0, 7200, 64.0, "3.5\"", 8.0);

    ClusterNode node1("Node1", ramSpec, cpuSpec, gpuSpec1, gpuSpecs1, { {"LAN1", lanSpec} }, { {"SSD1", ssdSpec} }, { {"HDD1", hddSpec} });
    ClusterNode node2("Node2", ramSpec, cpuSpec, gpuSpec2, gpuSpecs2, { {"LAN2", lanSpec} }, { {"SSD2", ssdSpec} }, { {"HDD2", hddSpec} });
    ClusterNode node3("Node1", ramSpec, cpuSpec, gpuSpec1, gpuSpecs1, { {"LAN1", lanSpec} }, { {"SSD1", ssdSpec} }, { {"HDD1", hddSpec} });
    ClusterNode node4("Node2", ramSpec, cpuSpec, gpuSpec2, gpuSpecs2, { {"LAN2", lanSpec} }, { {"SSD2", ssdSpec} }, { {"HDD2", hddSpec} });

    cluster.AddNode(node1);
    cluster.AddNode(node2);
    cluster.AddNode(node3);
    cluster.AddNode(node4);

    std::cout << "Node count: " << cluster.GetNodeCount() << std::endl;

    VectorParams vparams;
    vparams.size = 16;
    vparams.nodeOffset = 1; // Второй узел (Node2)
    vparams.deviceOffset = 1; // Второе устройство (GPU2)
    vparams.blockSize = 4;

    // Проверка параметров
    BOOST_REQUIRE_GT(vparams.size, 0);
    BOOST_REQUIRE_GT(vparams.blockSize, 0);
    BOOST_REQUIRE_EQUAL(vparams.size % vparams.blockSize, 0);

    VectorHCS<double> vector(vparams, &cluster);

    // Заполнение и проверка корректности
    size_t startIndex = vparams.nodeOffset * vparams.blockSize + vparams.deviceOffset;

    for (size_t i = 0; i < vparams.blockSize; ++i) {
        vector[startIndex + i] = static_cast<double>(i + 1);
    }

    // Проверяем корректность значения с учетом смещений
    BOOST_CHECK_EQUAL(vector[9], 0);
    BOOST_CHECK_THROW(vector[16], std::out_of_range);


    BOOST_CHECK_NO_THROW(vector[9] = 1.0);
    BOOST_CHECK_NO_THROW(vector[12] = 4.0);

    // Проверяем выброс исключения при выходе за пределы вектора
    BOOST_CHECK_THROW(vector[16], std::out_of_range); // Индекс 16 находится за пределами вектора
    BOOST_CHECK_THROW(vector[17], std::out_of_range); // Индекс 17 находится за пределами вектора
}

BOOST_AUTO_TEST_SUITE_END()