#include <boost/test/unit_test.hpp>
#include "../Lab/Geometry2D.cpp"
#include "../Lab/AppParams.cpp"
#include <iostream>
#include <map>

BOOST_AUTO_TEST_SUITE(GeometryTests) // Объявляем набор тестов для Geometry2D

// Тестовый случай для загрузки геометрических данных и их вывода
BOOST_AUTO_TEST_CASE(GeometryTests_LoadAndPrintGeometry) {
    // Создание параметров приложения из командной строки
    // Конструктор принимает имя программы и соответствующие параметры
    const char* argv[] = {
        "program_name",
        "-ffgeom", "Geometry_TXT_Format",
        "-fpgeom", "geometry2d.txt", //Этот файл должен быть в папке BoostTest
        "-ffgrid", "grid2d_params_TXT_Format",
        "-fpgrid", "grid2d_params.txt"
    };
    int argc = sizeof(argv) / sizeof(argv[0]); // Определяем количество аргументов

    // Создание объекта AppParams для парсинга аргументов командной строки
    AppParams appParams;

    // Проверяем, что параметры успешно распарсены
    BOOST_REQUIRE(appParams.ParseCommandLine(argc, const_cast<char**>(argv)));

    // Создание объекта Geometry2D с распарсенными параметрами
    Geometry2D geometry2D(appParams);

    // Выводим информацию о геометрии в консоль
    geometry2D.Print();

    // Выполняем проверки некоторых значений данных геометрии
    // Пример проверки: значение в (0, 0) должно быть 0
    BOOST_CHECK_EQUAL(geometry2D.GetData(0, 0), 0);
    // Пример проверки: значение в (1, 2) должно быть 0
    BOOST_CHECK_EQUAL(geometry2D.GetData(1, 2), 0);
    // Пример проверки: значение в (4, 4) должно быть 1
    BOOST_CHECK_EQUAL(geometry2D.GetData(4, 4), 1);
}

// Тестовый случай для проверки обработки ошибок при несуществующем файле
BOOST_AUTO_TEST_CASE(GeometryTests_FailOnInvalidFile) {
    // Создание массива аргументов, где указан несуществующий файл
    const char* argv[] = {
        "program_name",
        "-ffgeom", "Geometry_TXT_Format",
        "-fpgeom", "non_existing_file.txt",
        "-ffgrid", "grid2d_params_TXT_Format",
        "-fpgrid", "grid2d_params.txt" //Этот файл должен быть в папке BoostTest
    };

    int argc = sizeof(argv) / sizeof(argv[0]); // Определяем количество аргументов

    // Создание объекта AppParams для парсинга аргументов командной строки
    AppParams appParams;

    // Проверяем, что параметры успешно распарсены
    BOOST_REQUIRE(appParams.ParseCommandLine(argc, const_cast<char**>(argv)));

    // Проверка, что конструктор Geometry2D выбрасывает исключение
    // При попытке создать объект Geometry2D с неправильным файлом
    BOOST_CHECK_THROW({
        Geometry2D geometry2D(appParams); // Ожидаем выброс исключения
        }, std::runtime_error); // Проверка на тип исключения
}

BOOST_AUTO_TEST_SUITE_END() // Завершаем набор тестов