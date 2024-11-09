#pragma once

#include <string>

// Класс AppParams для хранения и обработки параметров приложения (запуск через командную строку)
class AppParams {
public:
    // Формат и путь к файлам геометрии
    std::string geometryFileFormat;  // Формат файла геометрии
    std::string geometryFilePath;    // Путь к файлу геометрии

    // Формат и путь к файлам сетки
    std::string gridFileFormat;       // Формат файла сетки
    std::string gridFilePath;         // Путь к файлу сетки

    // Метод для парсинга аргументов командной строки
    bool ParseCommandLine(int argc, char* argv[]);
};
