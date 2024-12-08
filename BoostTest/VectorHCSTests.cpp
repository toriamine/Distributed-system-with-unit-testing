#include <boost/test/unit_test.hpp>
#include "../Lab/VectorHCS.h"
#include "../Lab/Cluster.h"
#include "../Lab/ClusterNode.h"

// ������ ��������� ������ ��� VectorHCS
BOOST_AUTO_TEST_SUITE(VectorHCSTests)

// ������������ �������� � ������� � ��������� �������
BOOST_AUTO_TEST_CASE(CreateAndAccessVector) {
    Cluster cluster; // ������� ������� ��� ���������� ������

    // ��������� �������
    VectorParams vparams;
    vparams.size = 10; // ����� ������ �������
    vparams.nodeOffset = 0; // �������� ��� ����
    vparams.deviceOffset = 0; // �������� ��� ����������
    vparams.blockSize = 5; // ������ ����� (���������� ���������, �������������� ������� �����)

    // ������� ������ � ������ VectorHCS
    VectorHCS<double> vector(vparams, &cluster);

    // ��������� ������ � ������ ��������� �������
    for (size_t i = 0; i < vparams.blockSize; ++i) {
        vector[i] = static_cast<double>(i); // ��������� ������ ���������� �� 0 �� 4
    }

    // ���������, ��� �������� ������� ���������
    for (size_t i = 0; i < vparams.blockSize; ++i) {
        BOOST_CHECK_CLOSE(vector[i], static_cast<double>(i), 1e-6); // ��������� � ��������� �������� �� ������
    }
}

// ������������ ��������������� �������
BOOST_AUTO_TEST_CASE(ScaleVector) {
    Cluster cluster; // ������� �������

    // ������� � ����������� ����
    ClusterNode node1("node1",
        RamSpec(16.0, 3200, 16.0, "DDR4", 1.2, "DIMM", true),
        CpuSpec(4, 2.8, 150.0, 300.0, 8, 12.0, true, "x86"),
        GpuSpec(8.0, 1.5, 200, 500, 2048, "GDDR6", 36, "DirectX 12"),
        {}, {}, {}, {});

        node1.AddGpu("gpu1", GpuSpec(8.0, 1.5, 200, 500, 2048, "GDDR6", 36, "DirectX 12"));
        node1.AddCpu(CpuSpec(4, 2.8, 150.0, 300.0, 8, 12.0, true, "x86"));
        node1.AddRam(RamSpec(16.0, 3200, 16.0, "DDR4", 1.2, "DIMM", true));
        cluster.AddNode(node1); // ��������� ���� � �������

    // ��������� �������
    VectorParams vparams;
    vparams.size = 10; // ����� ������
    vparams.nodeOffset = 0; // ��������
    vparams.deviceOffset = 0; // �������� ��� ����������
    vparams.blockSize = 5; // ������ �����

    // ������� ������
    VectorHCS<double> vector(vparams, &cluster);

    // ��������� ������ ��������� �������
    for (size_t i = 0; i < vparams.blockSize; ++i) {
        vector[i] = static_cast<double>(i); // ��������� ������ ���������� �� 0 �� 4
    }

    // ������������ ������
    vector.ScaleVector(2.0); // �������� ������ ������� �� 2

    // ���������, ��� ������ ��� ������� �������������
    for (size_t i = 0; i < vparams.blockSize; ++i) {
        BOOST_CHECK_CLOSE(vector[i], static_cast<double>(i) * 2.0, 1e-6); // ���������, ��� �������� ����������
    }
}

// ������������ ���������� ������������
BOOST_AUTO_TEST_CASE(DotProduct) {
    Cluster cluster; // ������� �������

    // ��������� ���� 1
    ClusterNode node1("node1",
        RamSpec(16.0, 3200, 16.0, "DDR4", 1.2, "DIMM", true),
        CpuSpec(4, 2.8, 150.0, 300.0, 8, 12.0, true, "x86"),
        GpuSpec(8.0, 1.5, 200, 500, 2048, "GDDR6", 36, "DirectX 12"),
        {}, {}, {}, {});

    node1.AddGpu("gpu1", GpuSpec(8.0, 1.5, 200, 500, 2048, "GDDR6", 36, "DirectX 12"));
    node1.AddCpu(CpuSpec(4, 2.8, 150.0, 300.0, 8, 12.0, true, "x86"));
    node1.AddRam(RamSpec(16.0, 3200, 16.0, "DDR4", 1.2, "DIMM", true));
    cluster.AddNode(node1); // ��������� ���� � �������

    // ��������� ���� 2
    ClusterNode node2("node2",
        RamSpec(16.0, 3200, 16.0, "DDR4", 1.2, "DIMM", true),
        CpuSpec(4, 2.8, 150.0, 300.0, 8, 12.0, true, "x86"),
        GpuSpec(8.0, 1.5, 200, 500, 2048, "GDDR6", 36, "DirectX 12"),
        {}, {}, {}, {});

    node2.AddGpu("gpu1", GpuSpec(8.0, 1.5, 200, 500, 2048, "GDDR6", 36, "DirectX 12"));
    node2.AddCpu(CpuSpec(4, 2.8, 150.0, 300.0, 8, 12.0, true, "x86"));
    node2.AddRam(RamSpec(16.0, 3200, 16.0, "DDR4", 1.2, "DIMM", true));
    cluster.AddNode(node2); // ��������� ������ ���� � �������


    // ��������� ��������
    VectorParams vparams1 = { 10, 0, 0, 5 }; // ��������� ������� �������
    VectorHCS<double> vector1(vparams1, &cluster); // ������� ������ ������
    for (size_t i = 0; i < vparams1.blockSize; ++i) {
        vector1[i] = static_cast<double>(i); // ��������� ���������� �� 0 �� 4
    }

    VectorParams vparams2 = { 10, 0, 0, 5 }; // ��������� ������� �������
    VectorHCS<double> vector2(vparams2, &cluster); // ������� ������ ������
    for (size_t i = 0; i < vparams2.blockSize; ++i) {
        vector2[i] = static_cast<double>(i + 5); // ��������� ���������� �� 5 �� 9
    }

    std::cout << "Calculating dot product..." << std::endl; // ��������� � ������ ����������

    try {
        double dotProduct = vector1.DotProduct(vector2); // ��������� ��������� ������������
        std::cout << "Dot Product: " << dotProduct << std::endl; // ������� ���������
        BOOST_CHECK_CLOSE(dotProduct, 80.0, 1e-6); // ���������, ��� ��������� ������������� ���������� ��������
    }
    catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl; // ��������� ����������
    }
}

// ������������ ���������� �������
BOOST_AUTO_TEST_CASE(MemoryManagement) {
    Cluster cluster; // ������� �������

    // �������� ���� � ��������� ������������ ��� RAM, CPU � GPU
    ClusterNode node1("node1",
        RamSpec(16.0, 3200, 16.0, "DDR4", 1.2, "DIMM", true),
        CpuSpec(4, 2.8, 150.0, 300.0, 8, 12.0, true, "x86"),
        GpuSpec(8.0, 1.5, 200, 500, 2048, "GDDR6", 36, "DirectX 12"),
        {}, {}, {}, {});

    node1.AddGpu("gpu1", GpuSpec(8.0, 1.5, 200, 500, 2048, "GDDR6", 36, "DirectX 12")); // ��������� GPU � ����
    node1.AddCpu(CpuSpec(4, 2.8, 150.0, 300.0, 8, 12.0, true, "x86")); // ��������� CPU � ����
    node1.AddRam(RamSpec(16.0, 3200, 16.0, "DDR4", 1.2, "DIMM", true)); // ��������� RAM � ����
    cluster.AddNode(node1); // ��������� ���� � �������

    // ��������� ��� �������
    VectorParams vparams;
    vparams.size = 1000000; // ����� ������ �������
    vparams.nodeOffset = 0; // �������� ��� ����
    vparams.deviceOffset = 0; // �������� ��� ����������
    vparams.blockSize = 100000; // ������ �����

    // ������� ������ � �������� ������ �����������
    VectorHCS<double>* vector = new VectorHCS<double>(vparams, &cluster);

    BOOST_CHECK(vector != nullptr); // ���������, ��� ��������� �� ������ �� �������

    // ��������� ������ �������
    for (size_t i = 0; i < vparams.blockSize; ++i) {
        (*vector)[i] = static_cast<double>(i); // ��������� ������ ���������� �� 0 �� 99999
    }

    // ���������, ��� ������ ��� ������� ��������
    for (size_t i = 0; i < vparams.blockSize; ++i) {
        BOOST_CHECK_CLOSE((*vector)[i], static_cast<double>(i), 1e-6); // ���������, ��� �������� ����������
    }

    delete vector; // ����������� ������, ���������� ��� ������
}

BOOST_AUTO_TEST_SUITE_END() // ����� ��������� ������ ��� VectorHCS
