#include <boost/test/unit_test.hpp>
#include "../Lab/VectorHCS.h"

// ������ ��������� ������ ��� VectorHCS
BOOST_AUTO_TEST_SUITE(VectorHCSTests)

// ������������ �������� � ������� � ��������� �������
BOOST_AUTO_TEST_CASE(CreateAndAccessVector) {
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

    // �������� ����������
    BOOST_REQUIRE_GT(vparams.size, 0);
    BOOST_REQUIRE_GT(vparams.blockSize, 0);
    BOOST_REQUIRE_EQUAL(vparams.size % vparams.blockSize, 0);

    // ������� �������������� ������
    VectorHCS<double> vec(vparams, &cluster);

    // ��������� ������ �������
    for (size_t i = 0; i < vparams.size; ++i) {
        vec[i] = static_cast<double>(i);
    }

    // ������� ������ �������
    for (size_t i = 0; i < vparams.size; ++i) {
        std::cout << "vec[" << i << "] = " << vec[i] << std::endl;
    }

    for (size_t i = 0; i < vparams.size; ++i) {
        BOOST_CHECK_CLOSE(vec[i], static_cast<double>(i), 1e-6);
    }
}

// ������������ ��������������� �������
BOOST_AUTO_TEST_CASE(ScaleVector) {
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
    vparams.nodeOffset = 0; // ������ ����
    vparams.deviceOffset = 0;
    vparams.blockSize = 10;

    // �������� ����������
    BOOST_REQUIRE_GT(vparams.size, 0);
    BOOST_REQUIRE_GT(vparams.blockSize, 0);
    BOOST_REQUIRE_EQUAL(vparams.size % vparams.blockSize, 0);

    VectorHCS<double> vector(vparams, &cluster);

    // ��������� ������ �������
    for (size_t i = 0; i < vparams.size; ++i) {
        vector[i] = static_cast<double>(i);
    }

    // ������������ ������
    vector.ScaleVector(2.0);

    // ���������, ��� ������ ��� ������� �������������
    for (size_t i = 0; i < vparams.size; ++i) {
        BOOST_CHECK_CLOSE(vector[i], static_cast<double>(i) * 2.0, 1e-6);
    }

    // ��������� ������ ���������� ��� ������ �� ������� �������
    BOOST_CHECK_THROW(vector[20], std::out_of_range); // ������ 20 ��������� �� ��������� �������
    BOOST_CHECK_THROW(vector[29], std::out_of_range); // ������ 29 ��������� �� ��������� �������
}

// ������������ ���������� �������
// ������������ ���������� �������
BOOST_AUTO_TEST_CASE(MemoryManagement) {
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
    vparams.nodeOffset = 0; // ������ ����
    vparams.deviceOffset = 0;
    vparams.blockSize = 10;

    // ������� ������ � �������� ������ �����������
    VectorHCS<double>* vector = new VectorHCS<double>(vparams, &cluster);

    BOOST_CHECK(vector != nullptr); // ���������, ��� ��������� �� ������ �� �������

    // ��������� ������ �������
    for (size_t i = 0; i < vparams.size; ++i) {
        (*vector)[i] = static_cast<double>(i);
    }

    // ���������, ��� ������ ��� ������� ��������
    for (size_t i = 0; i < vparams.size; ++i) {
        BOOST_CHECK_CLOSE((*vector)[i], static_cast<double>(i), 1e-6);
    }

    delete vector; // ����������� ������, ���������� ��� ������
}

BOOST_AUTO_TEST_CASE(VectorHCS_TestWithOffsets)
{
    Cluster cluster;

    RamSpec ramSpec(32.0, 3200.0, 16.0, "DDR4", 1.2, "DIMM", true);
    CpuSpec cpuSpec(8, 3.6, 95.0, 300.0, 16, 12.0, true, "x86");
    GpuSpec gpuSpec(8.0, 1800.0, 250.0, 500.0, 2048, "GDDR6", 36, "DirectX 12");
    std::unordered_map<std::string, GpuSpec> gpuSpecs = {
        {"GPU1", gpuSpec}, // ��������� ���� �� ���� GPU ������������
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

    // �������� ����������
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


BOOST_AUTO_TEST_CASE(VectorHCS_TestWithoutOffsets)
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
    vparams.nodeOffset = 0; // �������� � ������� ����
    vparams.deviceOffset = 0;
    vparams.blockSize = 10;

    // �������� ����������
    BOOST_REQUIRE_GT(vparams.size, 0);
    BOOST_REQUIRE_GT(vparams.blockSize, 0);
    BOOST_REQUIRE_EQUAL(vparams.size % vparams.blockSize, 0);

    VectorHCS<double> vector(vparams, &cluster);

    // ��������� ������ ��� ���� 1 � ������ ��������
    for (size_t i = 0; i < vparams.size; ++i) {
        vector[i] = static_cast<double>(i + 1);
    }

    // ��������� ������������ �������� � ������ ��������
    BOOST_CHECK_EQUAL(vector[0], 1.0);
    BOOST_CHECK_EQUAL(vector[9], 10.0);
    BOOST_CHECK_EQUAL(vector[10], 11.0);
    BOOST_CHECK_EQUAL(vector[19], 20.0);

    BOOST_CHECK_NO_THROW(vector[0] = 1.0);
    BOOST_CHECK_NO_THROW(vector[19] = 20.0);

    // ��������� ������ ���������� ��� ������ �� ������� �������
    BOOST_CHECK_THROW(vector[20], std::out_of_range); // ������ 20 ��������� ��� ������
    BOOST_CHECK_THROW(vector[29], std::out_of_range); // ������ 29 ��������� ��� ������
}

// ������������ � nodeOffset
BOOST_AUTO_TEST_CASE(VectorHCS_TestWithNodeOffset)
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
    vparams.nodeOffset = 1; // ������ ����
    vparams.deviceOffset = 0;
    vparams.blockSize = 10;

    // �������� ����������
    BOOST_REQUIRE_GT(vparams.size, 0);
    BOOST_REQUIRE_GT(vparams.blockSize, 0);
    BOOST_REQUIRE_EQUAL(vparams.size % vparams.blockSize, 0);

    VectorHCS<double> vector(vparams, &cluster);

    // ��������� ������ ��� ���� 1 � ������ ��������
    size_t startIndex = vparams.nodeOffset * vparams.blockSize + vparams.deviceOffset;
    for (size_t i = 0; i < vparams.blockSize; ++i) {
        vector[startIndex + i] = static_cast<double>(i + 1);
    }

    // ��������� ������������ �������� � ������ ��������
    BOOST_CHECK_EQUAL(vector[10], 1.0);
    BOOST_CHECK_EQUAL(vector[19], 10.0);

    BOOST_CHECK_NO_THROW(vector[10] = 1.0);
    BOOST_CHECK_NO_THROW(vector[19] = 10.0);

    // ��������� ������ ���������� ��� ������ �� ������� �������
    //BOOST_CHECK_THROW(vector[9], std::out_of_range);  // ������ 9 ��������� ��� ������
    //BOOST_CHECK_THROW(vector[0], std::out_of_range);  // ������ 0 ��������� ��� ������
    BOOST_CHECK_THROW(vector[20], std::out_of_range); // ������ 20 ��������� �� ��������� �������
    BOOST_CHECK_THROW(vector[29], std::out_of_range); // ������ 29 ��������� �� ��������� �������
}

//������������ �� ��������� deviceOffset
// ������������ � deviceOffset
BOOST_AUTO_TEST_CASE(VectorHCS_TestWithDeviceOffset)
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
    vparams.nodeOffset = 0; // ������ ����
    vparams.deviceOffset = 1; // ������ ����������
    vparams.blockSize = 10;

    // �������� ����������
    BOOST_REQUIRE_GT(vparams.size, 0);
    BOOST_REQUIRE_GT(vparams.blockSize, 0);
    BOOST_REQUIRE_EQUAL(vparams.size % vparams.blockSize, 0);

    VectorHCS<double> vector(vparams, &cluster);

    // ��������� ������ ��� ���� 1 � ������ ��������
    size_t startIndex = vparams.nodeOffset * vparams.blockSize + vparams.deviceOffset;
    for (size_t i = 0; i < vparams.blockSize; ++i) {
        vector[startIndex + i] = static_cast<double>(i + 1);
    }

    // ��������� ������������ �������� � ������ ��������
    BOOST_CHECK_EQUAL(vector[1], 1.0);
    BOOST_CHECK_EQUAL(vector[10], 10.0);

    BOOST_CHECK_NO_THROW(vector[1] = 1.0);
    BOOST_CHECK_NO_THROW(vector[10] = 10.0);

    // ��������� ������ ���������� ��� ������ �� ������� �������
    //BOOST_CHECK_THROW(vector[0], std::out_of_range);  // ������ 0 ��������� ��� ������
    //BOOST_CHECK_THROW(vector[11], std::out_of_range); // ������ 11 ��������� ��� ������
    BOOST_CHECK_THROW(vector[20], std::out_of_range); // ������ 20 ��������� �� ��������� �������
    BOOST_CHECK_THROW(vector[29], std::out_of_range); // ������ 29 ��������� �� ��������� �������
}

//������������ � ������ ����������
BOOST_AUTO_TEST_CASE(VectorHCS_TestWithNodeAndDeviceOffsets)
{
    Cluster cluster;

    // ������������ ��� �����
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

    cluster.AddNode(node1);
    cluster.AddNode(node2);

    // Node count and VectorParams
    std::cout << "Node count: " << cluster.GetNodeCount() << std::endl;

    VectorParams vparams;
    vparams.size = 16;
    vparams.nodeOffset = 1; // ������ ����
    vparams.deviceOffset = 0; // ������ ����������
    vparams.blockSize = 8;

    // �������� ����������
    BOOST_REQUIRE_GT(vparams.size, 0);
    BOOST_REQUIRE_GT(vparams.blockSize, 0);
    BOOST_REQUIRE_EQUAL(vparams.size % vparams.blockSize, 0);

    VectorHCS<double> vector(vparams, &cluster);

    // ���������� � �������� ������������
    size_t startIndex = vparams.nodeOffset * vparams.blockSize + vparams.deviceOffset;

    for (size_t i = 0; i < vparams.blockSize; ++i) {
        vector[startIndex + i] = static_cast<double>(i + 1);
    }

    // ��������� ������������ �������� � ������ ��������
    BOOST_CHECK_EQUAL(vector[8], 1.0);
    BOOST_CHECK_EQUAL(vector[15], 8.0);

    BOOST_CHECK_NO_THROW(vector[8] = 1.0);
    BOOST_CHECK_NO_THROW(vector[15] = 8.0);

    // ��������� ������ ���������� ��� ������ �� ������� �������
    //BOOST_CHECK_THROW(vector[7], std::out_of_range);  // ������ 7 ��������� ��� ������
    //BOOST_CHECK_THROW(vector[0], std::out_of_range);  // ������ 0 ��������� ��� ������
    //BOOST_CHECK_THROW(vector[16], std::out_of_range); // ������ 16 ��������� ��� ������
    //BOOST_CHECK_THROW(vector[23], std::out_of_range); // ������ 23 ��������� ��� ������
}


BOOST_AUTO_TEST_SUITE_END() // ����� ��������� ������ ��� VectorHCS
