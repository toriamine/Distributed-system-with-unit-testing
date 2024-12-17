#include <iostream>
#include "Matrix.h"
#include "BlockMatrix.h"
#include "DiagonalMatrix.h"
#include "DenseMatrix.h"
#include "VectorHCS.h"
#include "Cluster.h"
#include "ClusterNode.h"
#include "DeviceSpecs.h"
#include "Geometry2D.h"
#include "AppParams.h"

int main(int argc, char* argv[]) {

    setlocale(LC_ALL, "ru");

    AppParams appParams;

    if (!appParams.ParseCommandLine(argc, argv))
        return 1;
    try {
        std::cout << "\n������������ ������ �������.\n";

        std::cout << "\n��������� ��������� �������:\n";
        Geometry2D geometry2D(appParams);
        geometry2D.Print();

        std::cout << "\n��������, ���� ��������� � ���������� �� ����� (����):\n";

        // �������������� ����������, ��������� �� � ����, � ����� ���� � �������
        // �������� ������� ����� �� ������ ���� � ������� ��� ������������

        RamSpec ramSpecTest(32.0, 3200.0, 16.0, "DDR4", 1.2, "DIMM", true);
        CpuSpec cpuSpecTest(8, 3.6, 95.0, 300.0, 16, 12.0, true, "x86");
        GpuSpec gpuSpecTest(8.0, 1800.0, 250.0, 500.0, 2048, "GDDR6", 36, "DirectX 12");

        std::unordered_map<std::string, GpuSpec> gpuSpecsTest = {
            {"GPU1", GpuSpec(4.0, 1600.0, 180.0, 300.0, 1024, "GDDR5", 20, "DirectX 11")},
            {"GPU2", GpuSpec(6.0, 1700.0, 220.0, 400.0, 1280, "GDDR5", 26, "DirectX 12")},
        };

        LanSpec lanSpecTest(20.0, 100.0, "Ethernet", "802.11ac", 5.0);
        SSDSpec ssdSpecTest(500.0, 550.0, 500.0, "2.5\"", "SATA", 1000.0, 800.0, 300.0);
        HDDSpec hddSpecTest(1000.0, 160.0, 150.0, 7200, 64.0, "3.5\"", 8.0);

        // ������� ���� ��������
        ClusterNode nodeTest1("Node1", ramSpecTest, cpuSpecTest, gpuSpecTest, gpuSpecsTest, { {"LAN1", lanSpecTest} }, { {"SSD1", ssdSpecTest} }, { {"HDD1", hddSpecTest} });
      
        // ������� ������� � ��������� ����
        Cluster clusterTest;
        clusterTest.AddNode(nodeTest1);

        // ������ ������� ����� �������� �������
        std::cout << "����� � ��������: " << clusterTest.GetNodeCount() << std::endl;

        const ClusterNode* node = clusterTest.GetNode("Node1");

        if (node) {
            std::cout << "Node ID: " << node->GetNodeId() << std::endl;
            std::cout << "RAM: " << node->GetRamSpec().GetSize() << " GB, "
                << node->GetRamSpec().GetMhz() << " MHz, "
                << node->GetRamSpec().GetLatency() << " ns, "
                << node->GetRamSpec().GetMemoryType() << ", "
                << node->GetRamSpec().GetVoltage() << " V"
                << (node->GetRamSpec().HasECC() ? ", ECC support" : ", No ECC support") << std::endl;

            std::cout << "CPU: " << node->GetCpuSpec().GetCoreCount() << " cores, "
                << node->GetCpuSpec().GetClockSpeed() << " GHz, "
                << node->GetCpuSpec().GetPower() << " W, "
                << node->GetCpuSpec().GetThermalDesignPower() << " TDP, "
                << node->GetCpuSpec().GetThreadCount() << " threads, "
                << node->GetCpuSpec().GetCacheSize() << " MB cache, "
                << (node->GetCpuSpec().HasIntegratedGraphics() ? "Integrated graphics" : "No integrated graphics")
                << ", " << node->GetCpuSpec().GetArchitecture() << std::endl;

            std::cout << "Main GPU: " << node->GetGpuSpec().GetMemory() << " GB, "
                << node->GetGpuSpec().GetClockSpeed() << " MHz, "
                << node->GetGpuSpec().GetPower() << " W, "
                << node->GetGpuSpec().GetBandwidth() << " GB/s, "
                << node->GetGpuSpec().GetCudaCores() << " CUDA cores, "
                << node->GetGpuSpec().GetMemoryType() << ", "
                << node->GetGpuSpec().GetRayTracingCores() << " Ray Tracing cores, "
                << "Supports " << node->GetGpuSpec().GetApiSupport() << std::endl;

            std::cout << "Additional GPUs:" << std::endl;
            for (const auto& pair : node->GetGpuSpecs()) {
                const std::string& id = pair.first;
                const GpuSpec& spec = pair.second;
                std::cout << "  " << id << ": " << spec.GetMemory() << " GB, "
                          << spec.GetClockSpeed() << " MHz, " << spec.GetPower() << " W, "
                          << spec.GetBandwidth() << " GB/s, "
                          << spec.GetCudaCores() << " CUDA cores, "
                          << spec.GetMemoryType() << ", "
                          << spec.GetRayTracingCores() << " Ray Tracing cores, "
                          << "Supports " << spec.GetApiSupport() << std::endl;
            }

            std::cout << "LAN: " << node->GetLanSpecs().at("LAN1").GetPower() << " W, " 
                      << node->GetLanSpecs().at("LAN1").GetBandwidth() << " Gbps, "
                      << node->GetLanSpecs().at("LAN1").GetInterfaceType() << ", "
                      << node->GetLanSpecs().at("LAN1").GetProtocolStandard() << ", "
                      << node->GetLanSpecs().at("LAN1").GetLatency() << " ms" << std::endl;

            std::cout << "SSD: " << node->GetSSDSpecs().at("SSD1").GetSize() << " GB, "
                      << node->GetSSDSpecs().at("SSD1").GetReadSpeed() << " MB/s, "
                      << node->GetSSDSpecs().at("SSD1").GetWriteSpeed() << " MB/s, "
                      << node->GetSSDSpecs().at("SSD1").GetFormFactor() << ", "
                      << node->GetSSDSpecs().at("SSD1").GetInterfaceType() << ", "
                      << node->GetSSDSpecs().at("SSD1").GetRandomReadSpeed() << " MB/s, "
                      << node->GetSSDSpecs().at("SSD1").GetRandomWriteSpeed() << " MB/s, "
                      << node->GetSSDSpecs().at("SSD1").GetEndurance() << " TBW" << std::endl;

            std::cout << "HDD: " << node->GetHDDSpecs().at("HDD1").GetSize() << " GB, "
                      << node->GetHDDSpecs().at("HDD1").GetReadSpeed() << " MB/s, "
                      << node->GetHDDSpecs().at("HDD1").GetWriteSpeed() << " MB/s, "
                      << node->GetHDDSpecs().at("HDD1").GetRpm() << " RPM, "
                      << node->GetHDDSpecs().at("HDD1").GetBufferSize() << " MB, "
                      << node->GetHDDSpecs().at("HDD1").GetFormFactor() << ", "
                      << node->GetHDDSpecs().at("HDD1").GetAverageSeekTime() << " ms" << std::endl;
        }
        else {
            std::cout << "���� �� ������" << std::endl;
        }

        std::cout << "\n������� ������� DenseMatrix � �� ����������:\n";

        // ������� ����������� ������� 2x2
        DenseMatrix<int> denseA(2, 2);
        denseA(0, 0) = 1; denseA(0, 1) = 2;
        denseA(1, 0) = 3; denseA(1, 1) = 4;

        DenseMatrix<int> denseB(2, 2);
        denseB(0, 0) = 5; denseB(0, 1) = 6;
        denseB(1, 0) = 7; denseB(1, 1) = 8;

        std::cout << "Dense Matrix A:\n";
        denseA.Print();
        std::cout << "\nDense Matrix B:\n";
        denseB.Print();

        // �������� � �������� ���������
        DenseMatrix<int> denseC = DenseMatrix<int>(denseA + denseB);
        std::cout << "\nA + B:\n";
        denseC.Print();

        DenseMatrix<int> denseD = DenseMatrix<int>(denseA - denseB);
        std::cout << "\nA - B:\n";
        denseD.Print();

        DenseMatrix<int> denseE = DenseMatrix<int>(denseA * denseB);
        std::cout << "\nA * B:\n";
        denseE.Print();

        std::cout << "\n������������ ������� DiagonalMatrix � �� ����������:\n";

        // ������� ������������ �������
        DiagonalMatrix<int> diagA(3);
        diagA(0, 0) = 1; diagA(1, 1) = 3; diagA(2, 2) = 6;

        DiagonalMatrix<int> diagB(3);
        diagB(0, 0) = 2; diagB(1, 1) = 4; diagB(2, 2) = 10;

        std::cout << "\nDiagonal Matrix A:\n";
        diagA.Print();
        std::cout << "\nDiagonal Matrix B:\n";
        diagB.Print();

        // �������� � ������������� ���������
        DiagonalMatrix<int> diagC = DiagonalMatrix<int>(diagA + diagB);
        std::cout << "\nA + B:\n";
        diagC.Print();

        DiagonalMatrix<int> diagD = DiagonalMatrix<int>(diagA - diagB);
        std::cout << "\nA - B:\n";
        diagD.Print();

        DiagonalMatrix<int> diagE = DiagonalMatrix<int>(diagA * diagB);
        std::cout << "\nA * B:\n";
        diagE.Print();

        std::cout << "\n������� �������, ��������� �� DenseMatrix:\n" << std::endl;

        // ������� ������� ������� �� 2x2 ������, ������ ���� 2x2 ��������
        // ����� ������ ����� ������������������ ���� (new DenseMatrix<int>(2, 2)) ��� �����������, 
        // � � ����� ��� ����� ������ � ���������� �������� �����

        BlockMatrix<int, DenseMatrix> blockMatrixA(2, 2, 2, 2);
        blockMatrixA.CreateBlock(0, 0, new DenseMatrix<int>(2, 2));
        blockMatrixA(0, 0) = 16; blockMatrixA(0, 1) = 3;
        blockMatrixA(1, 0) = 1; blockMatrixA(1, 1) = 8;

        blockMatrixA.CreateBlock(0, 1, new DenseMatrix<int>(2, 2));
        blockMatrixA(0, 2) = 25; blockMatrixA(0, 3) = 5;
        blockMatrixA(1, 2) = 17; blockMatrixA(1, 3) = 3;

        blockMatrixA.CreateBlock(1, 0, new DenseMatrix<int>(2, 2));
        blockMatrixA(2, 0) = 12; blockMatrixA(2, 1) = 18;
        blockMatrixA(3, 0) = 10; blockMatrixA(3, 1) = 7;

        blockMatrixA.CreateBlock(1, 1, new DenseMatrix<int>(2, 2));
        blockMatrixA(2, 2) = 13; blockMatrixA(2, 3) = 28;
        blockMatrixA(3, 2) = 1; blockMatrixA(3, 3) = 5;

        blockMatrixA(2, 2) = 11; blockMatrixA(2, 3) = 2;
        blockMatrixA(3, 2) = 17; blockMatrixA(3, 3) = 3;

        std::cout << "Block Matrix A:\n";
        blockMatrixA.Print();

        BlockMatrix<int, DenseMatrix> blockMatrixB(2, 2, 2, 2);
        blockMatrixB.CreateBlock(0, 0, new DenseMatrix<int>(2, 2));
        blockMatrixB(0, 0) = 17; blockMatrixB(0, 1) = 1;
        blockMatrixB(1, 0) = 12; blockMatrixB(1, 1) = 4;

        blockMatrixB.CreateBlock(0, 1, new DenseMatrix<int>(2, 2));
        blockMatrixB(0, 2) = 3; blockMatrixB(0, 3) = 6;
        blockMatrixB(1, 2) = 5; blockMatrixB(1, 3) = 8;

        blockMatrixB.CreateBlock(1, 0, new DenseMatrix<int>(2, 2));
        blockMatrixB(2, 0) = 18; blockMatrixB(2, 1) = 9;
        blockMatrixB(3, 0) = 8; blockMatrixB(3, 1) = 2;

        blockMatrixB.CreateBlock(1, 1, new DenseMatrix<int>(2, 2));
        blockMatrixB(2, 2) = 14; blockMatrixB(2, 3) = 5;
        blockMatrixB(3, 2) = 12; blockMatrixB(3, 3) = 15;

        std::cout << "\nBlock Matrix B:\n";
        blockMatrixB.Print();

        // ��������
        BlockMatrix<int, DenseMatrix> blockMatrixC = blockMatrixA + blockMatrixB;
        std::cout << "\nA + B:\n";
        blockMatrixC.Print();

        BlockMatrix<int, DenseMatrix> blockMatrixD = blockMatrixA - blockMatrixB;
        std::cout << "\nA - B:\n";
        blockMatrixD.Print();

        // ����� ������ kroneckerProduct
        BlockMatrix<int, DenseMatrix> kroneckerResult = blockMatrixA.kroneckerProduct(blockMatrixB);
        std::cout << "\nKronecker Product of A and B:\n";
        kroneckerResult.Print();

        std::cout << "\n������� �������, ��������� �� DiagonalMatrix:\n" << std::endl;

        BlockMatrix<int, DiagonalMatrix> blockMatrixA1(2, 2, 2, 2);
        blockMatrixA1.CreateBlock(0, 0, new DiagonalMatrix<int>({ 1, 4 }));
        blockMatrixA1.CreateBlock(0, 1, new DiagonalMatrix<int>({ 5, 8 }));
        blockMatrixA1.CreateBlock(1, 0, new DiagonalMatrix<int>({ 9, 12 }));
        blockMatrixA1.CreateBlock(1, 1, new DiagonalMatrix<int>({ 13, 16 }));

        std::cout << "Block Diagonal Matrix A:\n";
        blockMatrixA1.Print();

        BlockMatrix<int, DiagonalMatrix> blockMatrixB1(2, 2, 2, 2);
        blockMatrixB1.CreateBlock(0, 0, new DiagonalMatrix<int>({ 1, 1 }));
        blockMatrixB1.CreateBlock(0, 1, new DiagonalMatrix<int>({ 2, 2 }));
        blockMatrixB1.CreateBlock(1, 0, new DiagonalMatrix<int>({ 3, 3 }));
        blockMatrixB1.CreateBlock(1, 1, new DiagonalMatrix<int>({ 4, 4 }));

        std::cout << "\nBlock Diagonal Matrix B:\n";
        blockMatrixB1.Print();

        // ��������
        BlockMatrix<int, DiagonalMatrix> blockMatrixC1 = blockMatrixA1 + blockMatrixB1;
        std::cout << "\nA + B:\n";
        blockMatrixC1.Print();

        BlockMatrix<int, DiagonalMatrix> blockMatrixD1 = blockMatrixA1 - blockMatrixB1;
        std::cout << "\nA - B:\n";
        blockMatrixD1.Print();

        // ����� ������ kroneckerProduct
        BlockMatrix<int, DiagonalMatrix> kroneckerResult1 = blockMatrixA1.kroneckerProduct(blockMatrixB1);
        std::cout << "\nKronecker Product of A and B:\n";
        kroneckerResult1.Print();

        //������ � �������������� ��������

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

        // ������� ���� ��������
        ClusterNode node1("Node1", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN1", lanSpec} }, { {"SSD1", ssdSpec} }, { {"HDD1", hddSpec} });
        ClusterNode node2("Node2", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN2", lanSpec} }, { {"SSD2", ssdSpec} }, { {"HDD2", hddSpec} });
        ClusterNode node3("Node3", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN3", lanSpec} }, { {"SSD3", ssdSpec} }, { {"HDD3", hddSpec} });
        ClusterNode node4("Node4", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN4", lanSpec} }, { {"SSD4", ssdSpec} }, { {"HDD4", hddSpec} });

        // ������� ������� � ��������� ����
        Cluster cluster;
        cluster.AddNode(node1);
        cluster.AddNode(node2);
        cluster.AddNode(node3);
        cluster.AddNode(node4);

        // ������ ���������� ����� � ��������
        std::cout << "���������� �����: " << cluster.GetNodeCount() << std::endl;

        //������ �������: ������������ ���������� ��� �������� ��� ���� � ����������
        std::cout << "\n���������� VectorHCS ��� �������� ��� ���� � ���������:\n\n";

        // ������� ��������� �������
        VectorParams vparams = {16, 0, 0, 4}; // ������ �������� 16, ����� �� 4 ��������, �������� ���� 0, �������� ���������� 0

        // ������� �������������� ������
        VectorHCS<double> vec1(vparams, &cluster);

        // ��������� ������ �������
        for (size_t i = 0; i < vparams.size; ++i) {
            vec1[i] = static_cast<double>(i);
        }

        // ������� ������ �������
        vec1.Print("vec1");

        // ������� ������ ������ ��� ��������
        VectorHCS<double> vec2(vparams, &cluster);
        for (size_t i = 0; i < vparams.size; ++i) {
            vec2[i] = static_cast<double>(i) * 2.0;
        }

        // ������� ������ �������
        vec2.Print("vec2");

        // �������� ��������
        std::cout << "\n��������� �������� vec1 � vec2:\n";
        VectorHCS<double> vecSum = vec1 + vec2;
        vecSum.Print("vecSum");

        // ��������� ��������
        std::cout << "\n��������� ��������� vec1 � vec2:\n";
        VectorHCS<double> vecDiff = vec1 - vec2;
        vecDiff.Print("vecDiff");

        // ��������� ��������
        std::cout << "\n��������� ��������� vec1 � vec2:\n";
        VectorHCS<double> vecProd = vec1 * vec2;
        vecProd.Print("vecProd");

        // ��������� ������� �� ������
        vec1.ScaleVector(2.0);
        std::cout << "��������� ������� �� ������:" << std::endl;
        vec1.Print("vec1 ����� ��������� �� 2.0");

        // ��������� ������������ ���� ��������
        double dotProductScal = vec1.DotProduct(vec2);
        std::cout << "��������� ������������ ��������: " << dotProductScal << std::endl;

        //������ �������: ������������ ���������� �� ��������� ��� ���� � ���������
        std::cout << "\n���������� VectorHCS co ��������� ��� ���� � ����������:\n\n";

        // ������� ��������� �������
        VectorParams vparams1 = { 16, 1, 1, 4 }; // ������ �������� 16, ����� �� 4 ��������, �������� ���� 1, �������� ���������� 1

        // ������� �������������� ������
        VectorHCS<double> vec_offset1(vparams1, &cluster);

        // ��������� ������ �������
        for (size_t i = 0; i < vparams1.size; ++i) {
            vec_offset1[i] = static_cast<double>(i);
        }

        // ������� ������ �������
        vec_offset1.Print("vec_offset1");

        // ������� ������ ������ ��� ��������
        VectorHCS<double> vec_offset2(vparams1, &cluster);
        for (size_t i = 0; i < vparams1.size; ++i) {
            vec_offset2[i] = static_cast<double>(i) * 2.0;
        }
        
        // ������� ������ �������
        vec_offset2.Print("vec_offset2");

        // �������� ��������
        std::cout << "\n��������� �������� vec_offset1 � vec_offset2:\n";
        VectorHCS<double> vecSumOffset = vec_offset1 + vec_offset2;
        vecSumOffset.Print("vecSumOffset");

        // ��������� ��������
        std::cout << "\n��������� ��������� vec_offset1 � vec_offset2:\n";
        VectorHCS<double> vecDiffOffset = vec_offset1 - vec_offset2;
        vecDiffOffset.Print("vecDiffOffset");

        // ��������� ��������
        std::cout << "\n��������� ��������� vec_offset1 � vec_offset2:\n";
        VectorHCS<double> vecProdOffset = vec_offset1 * vec_offset2;
        vecProdOffset.Print("vecProdOffset");

        // ��������� ������� �� ������
        vec_offset1.ScaleVector(2.0);
        std::cout << "��������� ������� �� ������:" << std::endl;
        vec_offset1.Print("vec_offset1 ����� ��������� �� 2.0");

        // ��������� ������������ ���� ��������
        double dotProductScalOffset = vec_offset1.DotProduct(vec_offset2);
        std::cout << "��������� ������������ ��������: " << dotProductScalOffset << std::endl;

        std::cout << "\n��������� �� ������ � �������� ������� ���������!\n";

        std::cout << "\n�������� ����������� �������� ��������:\n";

        return 0;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

}