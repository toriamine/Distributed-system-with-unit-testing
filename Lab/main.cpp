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
    AppParams appParams;
    if (!appParams.ParseCommandLine(argc, argv))
        return 1;

    try {
        Geometry2D geometry2D(appParams);
        geometry2D.Print();

        // Создаем спецификации устройств с новыми параметрами
        RamSpec ramSpec(32.0, 3200.0, 16.0, "DDR4", 1.2, "DIMM", true);  // Размер, МГц, задержка, тип памяти, напряжение, форм-фактор, поддержка ECC

        CpuSpec cpuSpec(8, 3.6, 95.0, 300.0, 16, 12.0, true, "x86"); // Ядра, Тактовая частота, Потребляемая мощность, Тепловая мощность, Потоки, Размер кэша, Встроенная графика, Архитектура

        GpuSpec gpuSpec(8.0, 1800.0, 250.0, 500.0, 2048, "GDDR6", 36, "DirectX 12"); // Объем памяти, Тактовая частота, Потребляемая мощность, Пропускная способность, CUDA ядра, Тип памяти, Ядра трассировки лучей, Поддержка API

        std::unordered_map<std::string, GpuSpec> gpuSpecs = {
            {"GPU1", GpuSpec(4.0, 1600.0, 180.0, 300.0, 1024, "GDDR5", 20, "DirectX 11")},
            {"GPU2", GpuSpec(6.0, 1700.0, 220.0, 400.0, 1280, "GDDR5", 26, "DirectX 12")},
        };

        LanSpec lanSpec(20.0, 100.0, "Ethernet", "802.11ac", 5.0); // Потребляемая мощность, Пропускная способность, Тип интерфейса, Поддерживаемые протоколы, Задержка

        SSDSpec ssdSpec(500.0, 550.0, 500.0, "2.5\"", "SATA", 1000.0, 800.0, 300.0); // Размер, Скорость чтения, Скорость записи, Форм-фактор, Интерфейс, Скорость случайного чтения, Скорость случайной записи, Надежность

        HDDSpec hddSpec(1000.0, 160.0, 150.0, 7200, 64.0, "3.5\"", 8.0); // Размер, Скорость чтения, Скорость записи, RPM, Размер буфера, Форм-фактор, Среднее время поиска

        // Создаем узел кластера
        ClusterNode node1("Node1", ramSpec, cpuSpec, gpuSpec, gpuSpecs, { {"LAN1", lanSpec} }, { {"SSD1", ssdSpec} }, { {"HDD1", hddSpec} });

        // Создаем кластер и добавляем узел
        Cluster cluster;
        cluster.AddNode(node1);

        // Тестируем функциональность кластера и узлов
        std::cout << "Node count: " << cluster.GetNodeCount() << std::endl;

        const ClusterNode* node = cluster.GetNode("Node1");
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
        std::cout << "Node not found" << std::endl;
    }

        /*
        // Создать плотную матрицу 3x3
        DenseMatrix<double> denseMatrix = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 16.0},
            {7.0, 8.0, 9.0}
        };
        std::cout << "Dense Matrix:\n";
        denseMatrix.Print();

        // Создать диагональную матрицу 3x3
        DiagonalMatrix<double> diagonalMatrix(3);
        diagonalMatrix(0, 0) = 1.0;
        diagonalMatrix(1, 1) = 2.0;
        diagonalMatrix(2, 2) = 3.0;
        std::cout << "Diagonal Matrix:\n";
        diagonalMatrix.Print();

        // Создаем блочную матрицу из 2x2 блоков, каждый размером 2x2
        BlockMatrix<double, DenseMatrix> blockMatrix(2, 2, 2, 2);

        // Установим значения в блоки
        // Блок (0, 0):
        // Установим значения в блоки
        // Блок (0, 0):
        blockMatrix.block(0, 0)(0, 0) = 1.0;
        blockMatrix.block(0, 0)(0, 1) = 2.0;
        blockMatrix.block(0, 0)(1, 0) = 3.0;
        blockMatrix.block(0, 0)(1, 1) = 4.0;

        // Блок (0, 1):
        blockMatrix.block(0, 1)(0, 0) = 5.0;
        blockMatrix.block(0, 1)(0, 1) = 6.0;
        blockMatrix.block(0, 1)(1, 0) = 7.0;
        blockMatrix.block(0, 1)(1, 1) = 8.0;
        */
        // Создаем заполненные матрицы 2x2
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

        // Операции с плотными матрицами
        auto denseC = DenseMatrix<int>(denseA + denseB);
        std::cout << "\nA + B:\n";
        denseC.Print();

        auto denseD = DenseMatrix<int>(denseA - denseB);
        std::cout << "\nA - B:\n";
        denseD.Print();

        auto denseE = DenseMatrix<int>(denseA * denseB);
        std::cout << "\nA * B:\n";
        denseE.Print();

        // Создаем диагональные матрицы
        DiagonalMatrix<int> diagA(2);
        diagA(0, 0) = 1; diagA(1, 1) = 3;

        DiagonalMatrix<int> diagB(2);
        diagB(0, 0) = 2; diagB(1, 1) = 4;

        std::cout << "\nDiagonal Matrix A:\n";
        diagA.Print();
        std::cout << "\nDiagonal Matrix B:\n";
        diagB.Print();

        // Операции с диагональными матрицами
        auto diagC = DiagonalMatrix<int>(diagA + diagB);
        std::cout << "\nA + B:\n";
        diagC.Print();

        auto diagD = DiagonalMatrix<int>(diagA - diagB);
        std::cout << "\nA - B:\n";
        diagD.Print();

        auto diagE = DiagonalMatrix<int>(diagA * diagB);
        std::cout << "\nA * B:\n";
        diagE.Print();

        // Создаем блочные матрицы
        BlockMatrix<int, DenseMatrix> blockMatrixA(1, 1, 2, 2);
        blockMatrixA.setBlock(0, 0, new DenseMatrix<int>(2, 2));
        blockMatrixA(0, 0) = 1; blockMatrixA(0, 1) = 2;
        blockMatrixA(1, 0) = 3; blockMatrixA(1, 1) = 4;

        BlockMatrix<int, DenseMatrix> blockMatrixB(1, 1, 2, 2);
        blockMatrixB.setBlock(0, 0, new DenseMatrix<int>(2, 2));
        blockMatrixB(0, 0) = 5; blockMatrixB(0, 1) = 6;
        blockMatrixB(1, 0) = 7; blockMatrixB(1, 1) = 8;

        std::cout << "\nBlock Matrix A:\n";
        blockMatrixA.Print();
        std::cout << "\nBlock Matrix B:\n";
        blockMatrixB.Print();

        // Операции с блочными матрицами
        auto blockC = blockMatrixA + blockMatrixB;
        std::cout << "\nBlock A + Block B:\n";
        blockC.Print();

        auto blockD = blockMatrixA - blockMatrixB;
        std::cout << "\nBlock A - Block B:\n";
        blockD.Print();

        auto blockE = blockMatrixA * blockMatrixB;
        std::cout << "\nBlock A * Block B:\n";
        blockE.Print();

        // Произведение Кронекера
        /*auto kroneckerResult = blockMatrixA.kroneckerProduct(blockMatrixB);
        std::cout << "\nKronecker Product of Block A and Block B:\n";
        kroneckerResult.Print();*/


        // Выводим всю блочную матрицу
        /*std::cout << "Block Matrix:" << std::endl;
        blockMatrix.Print();*/

        // Настройка параметров векторов
        VectorParams vparams1;
        vparams1.size = 10;          // Общий размер
        vparams1.nodeOffset = 0;     // Смещение
        vparams1.deviceOffset = 0;   // Смещение
        vparams1.blockSize = 10;     // Работает с полным размером

        VectorParams vparams2 = { 10, 0, 0, 10 }; // Второй вектор для теста

        // Создание векторов
        VectorHCS<double> vector1(vparams1, &cluster);
        VectorHCS<double> vector2(vparams2, &cluster);

        // Заполнение первых векторов значениями
        for (size_t i = 0; i < vparams1.size; ++i) {
            vector1[i] = static_cast<double>(i + 1); // Заполнение значениями от 1 до 10
        }

        for (size_t i = 0; i < vparams2.size; ++i) {
            vector2[i] = static_cast<double>(i + 2); // Заполнение значениями от 2 до 11
        }

        // Печать элементов векторов
        std::cout << "Vector 1:\n";
        for (size_t i = 0; i < vparams1.size; ++i) {
            std::cout << vector1[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "Vector 2:\n";
        for (size_t i = 0; i < vparams2.size; ++i) {
            std::cout << vector2[i] << " ";
        }
        std::cout << std::endl;

        // Выполнение операции скалярного произведения
        double dotProduct = vector1.DotProduct(vector2);
        std::cout << "Dot Product: " << dotProduct << std::endl;

        // Умножение вектора на скаляр
        double scalar = 2.0;
        vector1.ScaleVector(scalar);
        std::cout << "Vector 1 after scaling by " << scalar << ":\n";

        for (size_t i = 0; i < vparams1.size; ++i) {
            std::cout << vector1[i] << " ";  // Печать измененного вектора
        }
        std::cout << std::endl;

    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
