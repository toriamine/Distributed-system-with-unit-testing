#include <boost/test/unit_test.hpp>
#include "../Lab/Cluster.cpp"
#include "../Lab/ClusterNode.cpp"
#include "../Lab/DeviceSpecs.cpp"

BOOST_AUTO_TEST_SUITE(FullSystemTests)

// �������� ������ ��� �������� ���� �������
BOOST_AUTO_TEST_CASE(FullSystemTest) {
    // ������������ ������ DeviceSpecs
    // ��������� �������� ���������� GpuSpec � ��� ������
    GpuSpec gpu(8.0, 1.5, 200, 500, 2048, "GDDR6", 36, "DirectX 12");
    BOOST_CHECK_EQUAL(gpu.GetMemory(), 8.0);                  // ���������, ��� ����� ������ �������������
    BOOST_CHECK_EQUAL(gpu.GetClockSpeed(), 1.5);              // ���������, ��� �������� ������� �������������
    BOOST_CHECK_EQUAL(gpu.GetPower(), 200);                   // ���������, ��� ������������ �������� �������������
    BOOST_CHECK_EQUAL(gpu.GetCudaCores(), 2048);              // ��������� ���������� CUDA ����
    BOOST_CHECK_EQUAL(gpu.GetMemoryType(), "GDDR6");          // ��������� ��� ������
    BOOST_CHECK_EQUAL(gpu.GetRayTracingCores(), 36);          // ��������� ���������� ���� ����������� �����
    BOOST_CHECK_EQUAL(gpu.GetApiSupport(), "DirectX 12");     // ��������� ��������� API

    // ��������� �������� ���������� CpuSpec � ��� ������
    CpuSpec cpu(4, 2.8, 150.0, 300.0, 8, 12.0, true, "x86");
    BOOST_CHECK_EQUAL(cpu.GetCoreCount(), 4);                  // ��������� ���������� ����
    BOOST_CHECK_EQUAL(cpu.GetClockSpeed(), 2.8);               // ��������� �������� �������
    BOOST_CHECK_EQUAL(cpu.GetPower(), 150.0);                  // ��������� ������������ ��������
    BOOST_CHECK_EQUAL(cpu.GetThreadCount(), 8);                // ��������� ���������� �������
    BOOST_CHECK_EQUAL(cpu.GetCacheSize(), 12.0);              // ��������� ������ ���-������
    BOOST_CHECK(cpu.HasIntegratedGraphics());                   // ��������� ������� ���������� �������
    BOOST_CHECK_EQUAL(cpu.GetArchitecture(), "x86");           // ��������� �����������

    // ��������� �������� ���������� RamSpec � ��� ������
    RamSpec ram(16.0, 3200, 16.0, "DDR4", 1.2, "DIMM", true);
    BOOST_CHECK_EQUAL(ram.GetSize(), 16.0);                    // ��������� ������ ����������� ������
    BOOST_CHECK_EQUAL(ram.GetMhz(), 3200);                     // ��������� �������
    BOOST_CHECK_EQUAL(ram.GetLatency(), 16.0);                 // ��������� ��������
    BOOST_CHECK_EQUAL(ram.GetMemoryType(), "DDR4");            // ��������� ��� ������
    BOOST_CHECK_EQUAL(ram.GetVoltage(), 1.2);                  // ��������� ������� ����������
    BOOST_CHECK(ram.HasECC());                                  // ��������� ��������� ECC

    // ������������ ������ ClusterNode
    // ������� ���� �������� � ��������� �����������
    ClusterNode node("node1", ram, cpu, gpu, {
        {"gpu1", GpuSpec(4.0, 1.2, 150.0, 300.0, 1024, "GDDR5", 20, "DirectX 11")} // �������������� ����������� �����
        }, {
            {"lan1", LanSpec(10, 50, "Ethernet", "802.11ac", 5.0)} // ������� �������
        }, {
            {"ssd1", SSDSpec(500, 550, 500, "2.5\"", "SATA", 1000, 800, 300)} // SSD
        }, {
            {"hdd1", HDDSpec(1000, 160, 150, 7200, 64, "3.5\"", 8.0)} // HDD
        });

        // ��������� ��������� ������ �� ����
        BOOST_CHECK_EQUAL(node.GetRamSpec().GetSize(), 16.0);                 // �������� ������� RAM � ����

    BOOST_CHECK_EQUAL(node.GetCpuSpec().GetCoreCount(), 4);               // �������� ���������� ���� CPU
    BOOST_CHECK_EQUAL(node.GetGpuSpec().GetMemory(), 8.0);                // �������� ������ �������� GPU
    BOOST_CHECK_EQUAL(node.GetGpuSpecs().at("gpu1").GetMemory(), 4.0);    // �������� ������ �������������� GPU
    BOOST_CHECK_EQUAL(node.GetLanSpecs().at("lan1").GetPower(), 10);       // �������� �������� �������� ��������
    BOOST_CHECK_EQUAL(node.GetSSDSpecs().at("ssd1").GetSize(), 500);       // �������� ������� SSD
    BOOST_CHECK_EQUAL(node.GetHDDSpecs().at("hdd1").GetSize(), 1000);      // �������� ������� HDD

    // ������������ ������ Cluster
    Cluster cluster; // ������� �������
    cluster.AddNode(node); // ��������� ���� � �������
    BOOST_CHECK_EQUAL(cluster.GetNodeCount(), 1); // ��������, ��� � �������� ���� ����

    // �������� ��������� ���� �� ��������������
    const ClusterNode* retrievedNode = cluster.GetNode("node1");
    BOOST_REQUIRE(retrievedNode != nullptr); // ��������, ��� ���� ������� ������
    BOOST_CHECK_EQUAL(retrievedNode->GetNodeId(), "node1"); // �������� �������������� ����
}

BOOST_AUTO_TEST_SUITE_END()

/*
� ���� ����� �� ��������������� ���������:
1. ���������������� ������ DeviceSpecs (�������� Get-������� ��� ��������� ����� ���������).
2. ���������������� ������ ClusterNode (�������� �������� ���� � ��������� ���������� � ���).
3. ���������������� ������ Cluster (�������� ���������� ���� � ��������� ���� �� ��������������).
*/
