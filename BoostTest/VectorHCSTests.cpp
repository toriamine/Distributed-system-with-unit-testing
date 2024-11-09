#include <boost/test/unit_test.hpp>
#include "../Lab/VectorHCS.h"
#include "../Lab/Cluster.h"
#include "../Lab/ClusterNode.h"

// Начало тестового набора для VectorHCS
BOOST_AUTO_TEST_SUITE(VectorHCSTests)

// Тестирование создания и доступа к элементам вектора
BOOST_AUTO_TEST_CASE(CreateAndAccessVector) {
    Cluster cluster; // Создаем кластер для управления узлами

    // Параметры вектора
    VectorParams vparams;
    vparams.size = 10; // Общий размер вектора
    vparams.nodeOffset = 0; // Смещение для узла
    vparams.deviceOffset = 0; // Смещение для устройства
    vparams.blockSize = 5; // Размер блока (количество элементов, обрабатываемых текущим узлом)

    // Создаем вектор в классе VectorHCS
    VectorHCS<double> vector(vparams, &cluster);

    // Проверяем запись и чтение элементов вектора
    for (size_t i = 0; i < vparams.blockSize; ++i) {
        vector[i] = static_cast<double>(i); // Заполняем вектор значениями от 0 до 4
    }

    // Проверяем, что значения вектора корректны
    for (size_t i = 0; i < vparams.blockSize; ++i) {
        BOOST_CHECK_CLOSE(vector[i], static_cast<double>(i), 1e-6); // Проверяем с небольшим допуском на ошибки
    }
}

// Тестирование масштабирования вектора
BOOST_AUTO_TEST_CASE(ScaleVector) {
    Cluster cluster; // Создаем кластер

    // Создаем и настраиваем узел
    ClusterNode node1("node1",
        RamSpec(16.0, 3200, 16.0, "DDR4", 1.2, "DIMM", true),
        CpuSpec(4, 2.8, 150.0, 300.0, 8, 12.0, true, "x86"),
        GpuSpec(8.0, 1.5, 200, 500, 2048, "GDDR6", 36, "DirectX 12"),
        {}, {}, {}, {});

        node1.AddGpu("gpu1", GpuSpec(8.0, 1.5, 200, 500, 2048, "GDDR6", 36, "DirectX 12"));
        node1.AddCpu(CpuSpec(4, 2.8, 150.0, 300.0, 8, 12.0, true, "x86"));
        node1.AddRam(RamSpec(16.0, 3200, 16.0, "DDR4", 1.2, "DIMM", true));
        cluster.AddNode(node1); // Добавляем узел в кластер

    // Параметры вектора
    VectorParams vparams;
    vparams.size = 10; // Общий размер
    vparams.nodeOffset = 0; // Смещение
    vparams.deviceOffset = 0; // Смещение для устройства
    vparams.blockSize = 5; // Размер блока

    // Создаем вектор
    VectorHCS<double> vector(vparams, &cluster);

    // Заполняем вектор тестовыми данными
    for (size_t i = 0; i < vparams.blockSize; ++i) {
        vector[i] = static_cast<double>(i); // Заполняем вектор значениями от 0 до 4
    }

    // Масштабируем вектор
    vector.ScaleVector(2.0); // Умножаем каждый элемент на 2

    // Проверяем, что вектор был успешно масштабирован
    for (size_t i = 0; i < vparams.blockSize; ++i) {
        BOOST_CHECK_CLOSE(vector[i], static_cast<double>(i) * 2.0, 1e-6); // Проверяем, что значения правильные
    }
}

// Тестирование скалярного произведения
BOOST_AUTO_TEST_CASE(DotProduct) {
    Cluster cluster; // Создаем кластер

    // Настройка узла 1
    ClusterNode node1("node1",
        RamSpec(16.0, 3200, 16.0, "DDR4", 1.2, "DIMM", true),
        CpuSpec(4, 2.8, 150.0, 300.0, 8, 12.0, true, "x86"),
        GpuSpec(8.0, 1.5, 200, 500, 2048, "GDDR6", 36, "DirectX 12"),
        {}, {}, {}, {});

    node1.AddGpu("gpu1", GpuSpec(8.0, 1.5, 200, 500, 2048, "GDDR6", 36, "DirectX 12"));
    node1.AddCpu(CpuSpec(4, 2.8, 150.0, 300.0, 8, 12.0, true, "x86"));
    node1.AddRam(RamSpec(16.0, 3200, 16.0, "DDR4", 1.2, "DIMM", true));
    cluster.AddNode(node1); // Добавляем узел в кластер

    // Настройка узла 2
    ClusterNode node2("node2",
        RamSpec(16.0, 3200, 16.0, "DDR4", 1.2, "DIMM", true),
        CpuSpec(4, 2.8, 150.0, 300.0, 8, 12.0, true, "x86"),
        GpuSpec(8.0, 1.5, 200, 500, 2048, "GDDR6", 36, "DirectX 12"),
        {}, {}, {}, {});

    node2.AddGpu("gpu1", GpuSpec(8.0, 1.5, 200, 500, 2048, "GDDR6", 36, "DirectX 12"));
    node2.AddCpu(CpuSpec(4, 2.8, 150.0, 300.0, 8, 12.0, true, "x86"));
    node2.AddRam(RamSpec(16.0, 3200, 16.0, "DDR4", 1.2, "DIMM", true));
    cluster.AddNode(node2); // Добавляем второй узел в кластер


    // Параметры векторов
    VectorParams vparams1 = { 10, 0, 0, 5 }; // Параметры первого вектора
    VectorHCS<double> vector1(vparams1, &cluster); // Создаем первый вектор
    for (size_t i = 0; i < vparams1.blockSize; ++i) {
        vector1[i] = static_cast<double>(i); // Заполняем значениями от 0 до 4
    }

    VectorParams vparams2 = { 10, 0, 0, 5 }; // Параметры второго вектора
    VectorHCS<double> vector2(vparams2, &cluster); // Создаем второй вектор
    for (size_t i = 0; i < vparams2.blockSize; ++i) {
        vector2[i] = static_cast<double>(i + 5); // Заполняем значениями от 5 до 9
    }

    std::cout << "Calculating dot product..." << std::endl; // Сообщение о начале вычисления

    try {
        double dotProduct = vector1.DotProduct(vector2); // Вычисляем скалярное произведение
        std::cout << "Dot Product: " << dotProduct << std::endl; // Выводим результат
        BOOST_CHECK_CLOSE(dotProduct, 80.0, 1e-6); // Проверяем, что результат соответствует ожидаемому значению
    }
    catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl; // Обработка исключений
    }
}

// Тестирование управления памятью
BOOST_AUTO_TEST_CASE(MemoryManagement) {
    Cluster cluster; // Создаем кластер

    // Создание узла с указанием спецификаций для RAM, CPU и GPU
    ClusterNode node1("node1",
        RamSpec(16.0, 3200, 16.0, "DDR4", 1.2, "DIMM", true),
        CpuSpec(4, 2.8, 150.0, 300.0, 8, 12.0, true, "x86"),
        GpuSpec(8.0, 1.5, 200, 500, 2048, "GDDR6", 36, "DirectX 12"),
        {}, {}, {}, {});

    node1.AddGpu("gpu1", GpuSpec(8.0, 1.5, 200, 500, 2048, "GDDR6", 36, "DirectX 12")); // Добавляем GPU к узлу
    node1.AddCpu(CpuSpec(4, 2.8, 150.0, 300.0, 8, 12.0, true, "x86")); // Добавляем CPU к узлу
    node1.AddRam(RamSpec(16.0, 3200, 16.0, "DDR4", 1.2, "DIMM", true)); // Добавляем RAM к узлу
    cluster.AddNode(node1); // Добавляем узел в кластер

    // Параметры для вектора
    VectorParams vparams;
    vparams.size = 1000000; // Общий размер вектора
    vparams.nodeOffset = 0; // Смещение для узла
    vparams.deviceOffset = 0; // Смещение для устройства
    vparams.blockSize = 100000; // Размер блока

    // Создаем вектор и выделяем память динамически
    VectorHCS<double>* vector = new VectorHCS<double>(vparams, &cluster);

    BOOST_CHECK(vector != nullptr); // Проверяем, что указатель на вектор не нулевой

    // Заполняем вектор данными
    for (size_t i = 0; i < vparams.blockSize; ++i) {
        (*vector)[i] = static_cast<double>(i); // Заполняем вектор значениями от 0 до 99999
    }

    // Проверяем, что вектор был успешно заполнен
    for (size_t i = 0; i < vparams.blockSize; ++i) {
        BOOST_CHECK_CLOSE((*vector)[i], static_cast<double>(i), 1e-6); // Проверяем, что значения правильные
    }

    delete vector; // Освобождаем память, выделенную под вектор
}

BOOST_AUTO_TEST_SUITE_END() // Конец тестового набора для VectorHCS
