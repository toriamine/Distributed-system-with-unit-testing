// main.cpp
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
        //return 1;

    try {
        //Geometry2D geometry2D(appParams);
        //geometry2D.Print();

        //Создаем спецификации устройств с новыми параметрами
        // Ваши спецификации компонентов
        //RamSpec ramSpec(32.0, 3200.0, 16.0, "DDR4", 1.2, "DIMM", true);
        //CpuSpec cpuSpec(8, 3.6, 95.0, 300.0, 16, 12.0, true, "x86");
        //GpuSpec gpuSpec(8.0, 1800.0, 250.0, 500.0, 2048, "GDDR6", 36, "DirectX 12");

        //std::unordered_map<std::string, GpuSpec> gpuSpecs = {
        //    {"GPU1", GpuSpec(4.0, 1600.0, 180.0, 300.0, 1024, "GDDR5", 20, "DirectX 11")},
        //    {"GPU2", GpuSpec(6.0, 1700.0, 220.0, 400.0, 1280, "GDDR5", 26, "DirectX 12")},
        //};

        //LanSpec lanSpec(20.0, 100.0, "Ethernet", "802.11ac", 5.0);
        //SSDSpec ssdSpec(500.0, 550.0, 500.0, "2.5\"", "SATA", 1000.0, 800.0, 300.0);
        //HDDSpec hddSpec(1000.0, 160.0, 150.0, 7200, 64.0, "3.5\"", 8.0);

        //// Создаем узлы кластера
        //ClusterNode node1("Node1", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN1", lanSpec} }, { {"SSD1", ssdSpec} }, { {"HDD1", hddSpec} });
        //ClusterNode node2("Node2", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN2", lanSpec} }, { {"SSD2", ssdSpec} }, { {"HDD2", hddSpec} });
        //ClusterNode node3("Node3", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN3", lanSpec} }, { {"SSD3", ssdSpec} }, { {"HDD3", hddSpec} });

        //// Создаем кластер и добавляем узлы
        //Cluster cluster;
        //cluster.AddNode(node1);
        //cluster.AddNode(node2);
        //cluster.AddNode(node3);

        //// Тестируем функциональность кластера и узлов
        //std::cout << "Node count: " << cluster.GetNodeCount() << std::endl;

        //const ClusterNode* node = cluster.GetNode("Node1,Node2,Node3");
        //if (node) {
 //           std::cout << "Node ID: " << node->GetNodeId() << std::endl;
 //           std::cout << "RAM: " << node->GetRamSpec().GetSize() << " GB, "
 //               << node->GetRamSpec().GetMhz() << " MHz, "
 //               << node->GetRamSpec().GetLatency() << " ns, "
 //               << node->GetRamSpec().GetMemoryType() << ", "
 //               << node->GetRamSpec().GetVoltage() << " V"
 //               << (node->GetRamSpec().HasECC() ? ", ECC support" : ", No ECC support") << std::endl;

 //           std::cout << "CPU: " << node->GetCpuSpec().GetCoreCount() << " cores, "
 //               << node->GetCpuSpec().GetClockSpeed() << " GHz, "
 //               << node->GetCpuSpec().GetPower() << " W, "
 //               << node->GetCpuSpec().GetThermalDesignPower() << " TDP, "
 //               << node->GetCpuSpec().GetThreadCount() << " threads, "
 //               << node->GetCpuSpec().GetCacheSize() << " MB cache, "
 //               << (node->GetCpuSpec().HasIntegratedGraphics() ? "Integrated graphics" : "No integrated graphics")
 //               << ", " << node->GetCpuSpec().GetArchitecture() << std::endl;

 //           std::cout << "Main GPU: " << node->GetGpuSpec().GetMemory() << " GB, "
 //               << node->GetGpuSpec().GetClockSpeed() << " MHz, "
 //               << node->GetGpuSpec().GetPower() << " W, "
 //<< node->GetGpuSpec().GetBandwidth() << " GB/s, "
 //                 << node->GetGpuSpec().GetCudaCores() << " CUDA cores, "
 //                 << node->GetGpuSpec().GetMemoryType() << ", "
 //                 << node->GetGpuSpec().GetRayTracingCores() << " Ray Tracing cores, "
 //                 << "Supports " << node->GetGpuSpec().GetApiSupport() << std::endl;

 //       std::cout << "Additional GPUs:" << std::endl;
 //       for (const auto& pair : node->GetGpuSpecs()) {
 //           const std::string& id = pair.first;
 //           const GpuSpec& spec = pair.second;
 //           std::cout << "  " << id << ": " << spec.GetMemory() << " GB, "
 //                     << spec.GetClockSpeed() << " MHz, " << spec.GetPower() << " W, "
 //                     << spec.GetBandwidth() << " GB/s, "
 //                     << spec.GetCudaCores() << " CUDA cores, "
 //                     << spec.GetMemoryType() << ", "
 //                     << spec.GetRayTracingCores() << " Ray Tracing cores, "
 //                     << "Supports " << spec.GetApiSupport() << std::endl;
 //       }

 //       std::cout << "LAN: " << node->GetLanSpecs().at("LAN1").GetPower() << " W, " 
 //                 << node->GetLanSpecs().at("LAN1").GetBandwidth() << " Gbps, "
 //                 << node->GetLanSpecs().at("LAN1").GetInterfaceType() << ", "
 //                 << node->GetLanSpecs().at("LAN1").GetProtocolStandard() << ", "
 //                 << node->GetLanSpecs().at("LAN1").GetLatency() << " ms" << std::endl;

 //       std::cout << "SSD: " << node->GetSSDSpecs().at("SSD1").GetSize() << " GB, "
 //                 << node->GetSSDSpecs().at("SSD1").GetReadSpeed() << " MB/s, "
 //                 << node->GetSSDSpecs().at("SSD1").GetWriteSpeed() << " MB/s, "
 //                 << node->GetSSDSpecs().at("SSD1").GetFormFactor() << ", "
 //                 << node->GetSSDSpecs().at("SSD1").GetInterfaceType() << ", "
 //                 << node->GetSSDSpecs().at("SSD1").GetRandomReadSpeed() << " MB/s, "
 //                 << node->GetSSDSpecs().at("SSD1").GetRandomWriteSpeed() << " MB/s, "
 //                 << node->GetSSDSpecs().at("SSD1").GetEndurance() << " TBW" << std::endl;

 //       std::cout << "HDD: " << node->GetHDDSpecs().at("HDD1").GetSize() << " GB, "
 //                 << node->GetHDDSpecs().at("HDD1").GetReadSpeed() << " MB/s, "
 //                 << node->GetHDDSpecs().at("HDD1").GetWriteSpeed() << " MB/s, "
 //                 << node->GetHDDSpecs().at("HDD1").GetRpm() << " RPM, "
 //                 << node->GetHDDSpecs().at("HDD1").GetBufferSize() << " MB, "
 //                 << node->GetHDDSpecs().at("HDD1").GetFormFactor() << ", "
 //                 << node->GetHDDSpecs().at("HDD1").GetAverageSeekTime() << " ms" << std::endl;
    //}
    //else {
    //    std::cout << "Node not found" << std::endl;
    //}

        //// Создаем заполненные матрицы 2x2
        //DenseMatrix<int> denseA(2, 2);
        //denseA(0, 0) = 1; denseA(0, 1) = 2;
        //denseA(1, 0) = 3; denseA(1, 1) = 4;

        //DenseMatrix<int> denseB(2, 2);
        //denseB(0, 0) = 5; denseB(0, 1) = 6;
        //denseB(1, 0) = 7; denseB(1, 1) = 8;

        //std::cout << "Dense Matrix A:\n";
        //denseA.Print();
        //std::cout << "\nDense Matrix B:\n";
        //denseB.Print();

        //// Операции с плотными матрицами
        //auto denseC = DenseMatrix<int>(denseA + denseB);
        //std::cout << "\nA + B:\n";
        //denseC.Print();

        //auto denseD = DenseMatrix<int>(denseA - denseB);
        //std::cout << "\nA - B:\n";
        //denseD.Print();

        //auto denseE = DenseMatrix<int>(denseA * denseB);
        //std::cout << "\nA * B:\n";
        //denseE.Print();

        //// Создаем диагональные матрицы
        //DiagonalMatrix<int> diagA(3);
        //diagA(0, 0) = 1; diagA(1, 1) = 3; diagA(2, 2) = 6;

        //DiagonalMatrix<int> diagB(3);
        //diagB(0, 0) = 2; diagB(1, 1) = 4; diagB(2, 2) = 10;

        //std::cout << "\nDiagonal Matrix A:\n";
        //diagA.Print();
        //std::cout << "\nDiagonal Matrix B:\n";
        //diagB.Print();

        //// Операции с диагональными матрицами
        //auto diagC = DiagonalMatrix<int>(diagA + diagB);
        //std::cout << "\nA + B:\n";
        //diagC.Print();

        //auto diagD = DiagonalMatrix<int>(diagA - diagB);
        //std::cout << "\nA - B:\n";
        //diagD.Print();

        //auto diagE = DiagonalMatrix<int>(diagA * diagB);
        //std::cout << "\nA * B:\n";
        //diagE.Print();

        //std::cout << "\nБлочная матрица состоящая из DenseMatrix:\n" << std::endl;

        //// Создаем блочные матрицы 2x2 блоков, каждый из которых 2x2 элементы
        //BlockMatrix<int, DenseMatrix> blockMatrixA(2, 2, 2, 2);
        //blockMatrixA.CreateBlock(0, 0, new DenseMatrix<int>(2, 2));
        //blockMatrixA(0, 0) = 1; blockMatrixA(0, 1) = 2;
        //blockMatrixA(1, 0) = 3; blockMatrixA(1, 1) = 4;

        //blockMatrixA.CreateBlock(0, 1, new DenseMatrix<int>(2, 2));
        //blockMatrixA(0, 2) = 5; blockMatrixA(0, 3) = 6;
        //blockMatrixA(1, 2) = 7; blockMatrixA(1, 3) = 8;

        //blockMatrixA.CreateBlock(1, 0, new DenseMatrix<int>(2, 2));
        //blockMatrixA(2, 0) = 9; blockMatrixA(2, 1) = 10;
        //blockMatrixA(3, 0) = 11; blockMatrixA(3, 1) = 12;

        //blockMatrixA.CreateBlock(1, 1, new DenseMatrix<int>(2, 2));
        //blockMatrixA(2, 2) = 13; blockMatrixA(2, 3) = 14;
        //blockMatrixA(3, 2) = 15; blockMatrixA(3, 3) = 16;

        //blockMatrixA(2, 2) = 22; blockMatrixA(2, 3) = 22;
        //blockMatrixA(3, 2) = 22; blockMatrixA(3, 3) =22;

        //std::cout << "Block Matrix A:\n";
        //blockMatrixA.Print();

        //BlockMatrix<int, DenseMatrix> blockMatrixB(2, 2, 2, 2);
        //blockMatrixB.CreateBlock(0, 0, new DenseMatrix<int>(2, 2));
        //blockMatrixB(0, 0) = 1; blockMatrixB(0, 1) = 1;
        //blockMatrixB(1, 0) = 1; blockMatrixB(1, 1) = 1;

        //blockMatrixB.CreateBlock(0, 1, new DenseMatrix<int>(2, 2));
        //blockMatrixB(0, 2) = 2; blockMatrixB(0, 3) = 2;
        //blockMatrixB(1, 2) = 2; blockMatrixB(1, 3) = 2;

        //blockMatrixB.CreateBlock(1, 0, new DenseMatrix<int>(2, 2));
        //blockMatrixB(2, 0) = 3; blockMatrixB(2, 1) = 3;
        //blockMatrixB(3, 0) = 3; blockMatrixB(3, 1) = 3;

        //blockMatrixB.CreateBlock(1, 1, new DenseMatrix<int>(2, 2));
        //blockMatrixB(2, 2) = 4; blockMatrixB(2, 3) = 4;
        //blockMatrixB(3, 2) = 4; blockMatrixB(3, 3) = 4;

        //std::cout << "\nBlock Matrix B:\n";
        //blockMatrixB.Print();

        //// Операции
        //BlockMatrix<int, DenseMatrix> blockMatrixC = blockMatrixA + blockMatrixB;
        //std::cout << "\nA + B:\n";
        //blockMatrixC.Print();

        //BlockMatrix<int, DenseMatrix> blockMatrixD = blockMatrixA - blockMatrixB;
        //std::cout << "\nA - B:\n";
        //blockMatrixD.Print();

        //// Вызов метода kroneckerProduct
        //auto kroneckerResult = blockMatrixA.kroneckerProduct(blockMatrixB);
        //std::cout << "\nKronecker Product of A and B:\n";
        //kroneckerResult.Print();

        ////Диагональные матрицы

        //std::cout << "\nБлочная матрица состоящая из DiagonalMatrix:\n" << std::endl;

        //BlockMatrix<int, DiagonalMatrix> blockMatrixA1(2, 2, 2, 2);
        //blockMatrixA1.CreateBlock(0, 0, new DiagonalMatrix<int>({ 1, 4 }));
        //blockMatrixA1.CreateBlock(0, 1, new DiagonalMatrix<int>({ 5, 8 }));
        //blockMatrixA1.CreateBlock(1, 0, new DiagonalMatrix<int>({ 9, 12 }));
        //blockMatrixA1.CreateBlock(1, 1, new DiagonalMatrix<int>({ 13, 16 }));

        //std::cout << "Block Diagonal Matrix A:\n";
        //blockMatrixA1.Print();

        //BlockMatrix<int, DiagonalMatrix> blockMatrixB1(2, 2, 2, 2);
        //blockMatrixB1.CreateBlock(0, 0, new DiagonalMatrix<int>({ 1, 1 }));
        //blockMatrixB1.CreateBlock(0, 1, new DiagonalMatrix<int>({ 2, 2 }));
        //blockMatrixB1.CreateBlock(1, 0, new DiagonalMatrix<int>({ 3, 3 }));
        //blockMatrixB1.CreateBlock(1, 1, new DiagonalMatrix<int>({ 4, 4 }));

        //std::cout << "\nBlock Diagonal Matrix B:\n";
        //blockMatrixB1.Print();

        //// Операции
        //BlockMatrix<int, DiagonalMatrix> blockMatrixC1 = blockMatrixA1 + blockMatrixB1;
        //std::cout << "\nA + B:\n";
        //blockMatrixC1.Print();

        //BlockMatrix<int, DiagonalMatrix> blockMatrixD1 = blockMatrixA1 - blockMatrixB1;
        //std::cout << "\nA - B:\n";
        //blockMatrixD1.Print();

        //auto kroneckerResult1 = blockMatrixA1.kroneckerProduct(blockMatrixB1);
        //std::cout << "\nKronecker Product of A and B:\n";
        //kroneckerResult1.Print();

        //Работа с распределенным вектором

        //Первый вариант: классическая реализация без смещения для узла и устройства
        //std::cout << "\nКлассическая реализация VectorHCS без смещения для узла и устройства:\n";
        ////// Настройка параметров векторов
        //VectorParams vparams1;
        //vparams1.size = 10;          // Общий размер
        //vparams1.nodeOffset = 0;     // Смещение
        //vparams1.deviceOffset = 0;   // Смещение
        //vparams1.blockSize = 10;     // Работает с полным размером

        //VectorParams vparams2 = { 10, 0, 0, 10 }; // Второй вектор для теста, стандарт C++17 разрешает это делать

        //// Создание векторов
        //VectorHCS<double> vector1(vparams1, &cluster);
        //VectorHCS<double> vector2(vparams2, &cluster);

        //// Заполнение первых векторов значениями
        //for (size_t i = 0; i < vparams1.size; ++i) {
        //    vector1[i] = static_cast<double>(i + 1); // Заполнение значениями от 1 до 10
        //}

        //for (size_t i = 0; i < vparams2.size; ++i) {
        //    vector2[i] = static_cast<double>(i + 2); // Заполнение значениями от 2 до 11
        //}

        //// Печать элементов векторов
        //std::cout << "Vector 1:\n";
        //for (size_t i = 0; i < vparams1.size; ++i) {
        //    std::cout << vector1[i] << " ";
        //}
        //std::cout << std::endl;

        //std::cout << "Vector 2:\n";
        //for (size_t i = 0; i < vparams2.size; ++i) {
        //    std::cout << vector2[i] << " ";
        //}
        //std::cout << std::endl;

        //// Выполнение операции скалярного произведения
        //auto PlusProduct = vector1 + vector2;
        //std::cout << "Plus Product: " << PlusProduct[9] << std::endl;

        //// Выполнение операции скалярного произведения
        //double dotProduct = vector1.DotProduct(vector2);
        //std::cout << "Dot Product: " << dotProduct << std::endl;

        //// Умножение вектора на скаляр
        //double scalar = 2.0;
        //vector1.ScaleVector(scalar);
        //std::cout << "Vector 1 after scaling by " << scalar << ":\n";

        //for (size_t i = 0; i < vparams1.size; ++i) {
        //    std::cout << vector1[i] << " ";  // Печать измененного вектора
        //}
        //std::cout << std::endl;

        ////Первый вариант: классическая реализация без смещения для узла и устройства
        //std::cout << "\nКлассическая реализация VectorHCS co смещением для узла и устройства:\n";
        ////// Настройка параметров векторов
        //VectorParams vparams1_of;
        //vparams1_of.size = 10;          // Общий размер
        //vparams1_of.nodeOffset = 0;     // Смещение
        //vparams1_of.deviceOffset = 1;   // Смещение
        //vparams1_of.blockSize = 5;     // Работает с полным размером

        //VectorParams vparams2_of = { 10, 0, 1, 5 }; // Второй вектор для теста, стандарт C++17 разрешает это делать

        //// Создание векторов
        //VectorHCS<double> vector1_1(vparams1_of, &cluster);
        //VectorHCS<double> vector2_1(vparams2_of, &cluster);

        //// Заполнение первых векторов значениями
        //for (size_t i = 0; i < vparams1_of.size; ++i) {
        //    vector1_1[i] = static_cast<double>(i + 1); // Заполнение значениями от 1 до 10
        //}

        //for (size_t i = 0; i < vparams2_of.size; ++i) {
        //    vector2_1[i] = static_cast<double>(i + 2); // Заполнение значениями от 2 до 11
        //}

        //// Печать элементов векторов
        //std::cout << "Vector 1:\n";
        //for (size_t i = 0; i < vparams1_of.size; ++i) {
        //    std::cout << vector1_1[i] << " ";
        //}
        //std::cout << std::endl;

        //std::cout << "Vector 2:\n";
        //for (size_t i = 0; i < vparams2_of.size; ++i) {
        //    std::cout << vector2_1[i] << " ";
        //}
        //std::cout << std::endl;

        //// Выполнение операции скалярного произведения
        //double dotProduct_of = vector1_1.DotProduct(vector2_1);
        //std::cout << "Dot Product: " << dotProduct_of << std::endl;

        //// Выполнение операции скалярного произведения
        //double dotProduct_of1 = vector1_1.DotProduct(vector2_1);
        //std::cout << "Dot Product: " << dotProduct_of1 << std::endl;

        //// Умножение вектора на скаляр
        //double scalar_of = 2.0;
        //vector2_1.ScaleVector(scalar);
        //std::cout << "Vector 1 after scaling by " << scalar << ":\n";

        //for (size_t i = 0; i < vparams2_of.size; ++i) {
        //    std::cout << vector2_1[i] << " ";  // Печать измененного вектора
        //}
        //std::cout << std::endl;

           // Создаем кластер и добавляем узлы

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

        // Создаем узлы кластера
        ClusterNode node1("Node1", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN1", lanSpec} }, { {"SSD1", ssdSpec} }, { {"HDD1", hddSpec} });
        ClusterNode node2("Node2", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN2", lanSpec} }, { {"SSD2", ssdSpec} }, { {"HDD2", hddSpec} });
        ClusterNode node3("Node3", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN3", lanSpec} }, { {"SSD3", ssdSpec} }, { {"HDD3", hddSpec} });
        ClusterNode node4("Node4", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN4", lanSpec} }, { {"SSD4", ssdSpec} }, { {"HDD4", hddSpec} });

        // Создаем кластер и добавляем узлы
        Cluster cluster;
        cluster.AddNode(node1);
        cluster.AddNode(node2);
        cluster.AddNode(node3);
        cluster.AddNode(node4);

        // Тестируем функциональность кластера и узлов
        std::cout << "Node count: " << cluster.GetNodeCount() << std::endl;

        //Первый вариант: классическая реализация без смещения для узла и устройства
        std::cout << "\nКлассическая реализация VectorHCS без смещения для узла и устройств:\n";

    // Создаем параметры вектора
    VectorParams vparams = {16, 0, 0, 4}; // Вектор размером 16, блоки по 4 элемента, смещение узла 0, смещение устройства 0

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

    // Создаем второй вектор для операций
    VectorHCS<double> vec2(vparams, &cluster);
    for (size_t i = 0; i < vparams.size; ++i) {
        vec2[i] = static_cast<double>(i) * 2.0;
    }

    // Выводим данные вектора
    for (size_t i = 0; i < vparams.size; ++i) {
        std::cout << "vec2[" << i << "] = " << vec2[i] << std::endl;
    }

    // Сложение векторов
    VectorHCS<double> vecSum = vec + vec2;
    std::cout << "vecSum:" << std::endl;
    for (size_t i = 0; i < vparams.size; ++i) {
        std::cout << "vecSum[" << i << "] = " << vecSum[i] << std::endl;
    }

    // Вычитание векторов
    VectorHCS<double> vecDiff = vec - vec2;
    std::cout << "vecDiff:" << std::endl;
    for (size_t i = 0; i < vparams.size; ++i) {
        std::cout << "vecDiff[" << i << "] = " << vecDiff[i] << std::endl;
    }

    // Скалярное произведение
    double dotProduct = vec * vec2;
    std::cout << "Dot Product: " << dotProduct << std::endl;

    // Масштабирование вектора
    vec.ScaleVector(2.0);
    std::cout << "Scaled vec:" << std::endl;
    for (size_t i = 0; i < vparams.size; ++i) {
        std::cout << "vec[" << i << "] = " << vec[i] << std::endl;
    }

    //Первый вариант: классическая реализация со смещением для узла и устройств
    std::cout << "\nКлассическая реализация VectorHCS co смещением для узла и устройства:\n";

    // Создаем параметры вектора
    VectorParams vparams1 = { 16, 0, 1, 4 }; // Вектор размером 16, блоки по 4 элемента, смещение узла 0, смещение устройства 0

    // Создаем распределенный вектор
    VectorHCS<double> vec_of(vparams1, &cluster);

    // Заполняем вектор данными
    for (size_t i = 0; i < vparams1.size; ++i) {
        vec_of[i] = static_cast<double>(i);
    }

    // Выводим данные вектора
    for (size_t i = 0; i < vparams1.size; ++i) {
        std::cout << "vec_of[" << i << "] = " << vec_of[i] << std::endl;
    }

    // Создаем второй вектор для операций
    VectorHCS<double> vec2_of(vparams1, &cluster);
    for (size_t i = 0; i < vparams1.size; ++i) {
        vec2_of[i] = static_cast<double>(i) * 2.0;
    }

    // Выводим данные вектора
    for (size_t i = 0; i < vparams1.size; ++i) {
        std::cout << "vec2_of[" << i << "] = " << vec2_of[i] << std::endl;
    }

    // Сложение векторов
    VectorHCS<double> vecSum1 = vec_of + vec2_of;
    std::cout << "vecSum1:" << std::endl;
    for (size_t i = 0; i < vparams1.size; ++i) {
        std::cout << "vecSum1[" << i << "] = " << vecSum1[i] << std::endl;
    }

    // Вычитание векторов
    VectorHCS<double> vecDiff1 = vec_of - vec2_of;
    std::cout << "vecDiff1:" << std::endl;
    for (size_t i = 0; i < vparams1.size; ++i) {
        std::cout << "vecDiff1[" << i << "] = " << vecDiff1[i] << std::endl;
    }

    // Скалярное произведение
    double dotProduct1 = vec_of * vec2_of;
    std::cout << "Dot Product: " << dotProduct1 << std::endl;

    // Масштабирование вектора
    vec.ScaleVector(2.0);
    std::cout << "Scaled vec1:" << std::endl;
    for (size_t i = 0; i < vparams1.size; ++i) {
        std::cout << "vec1[" << i << "] = " << vec_of[i] << std::endl;
    }

    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
