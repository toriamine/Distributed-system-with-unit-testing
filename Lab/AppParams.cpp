#include "AppParams.h"
#include <iostream>
#include <map>
#include <vector>

bool AppParams::ParseCommandLine(int argc, char* argv[]) {
    // Создание отображения аргументов и соответствующих полей класса
    std::map<std::string, std::string*> argMap = {
        {"-ffgeom", &geometryFileFormat}, // Флаг формата файла геометрии
        {"-fpgeom", &geometryFilePath},   // Флаг пути к файлу геометрии
        {"-ffgrid", &gridFileFormat},      // Флаг формата файла сетки
        {"-fpgrid", &gridFilePath}         // Флаг пути к файлу сетки
    };

    // Список обязательных аргументов
    std::vector<std::string> requiredArgs = {
        "-ffgeom", "-fpgeom", "-ffgrid", "-fpgrid"
    };

    // Перебор аргументов командной строки
    for (int i = 1; i < argc; i++) {
        std::string arg(argv[i]); // Преобразование C-строки в std::string

        // Используем auto для автоматического определения типа для итератора
        // Тип: std::map<std::string, std::string*>::iterator
        //iterator - для контейнера для использования second(value), first(key)
        auto it = argMap.find(arg); // Поиск аргумента в карте

        if (it != argMap.end()) { // Если найден
            if (++i < argc) { // Проверка наличия следующего аргумента
                *(it->second) = argv[i]; // Заполнение соответствующего поля

                // Удаление аргумента из списка обязательных, если он был предоставлен
                // auto выводит тип: std::vector<std::string>::iterator
                auto pos = std::find(requiredArgs.begin(), requiredArgs.end(), arg);
                if (pos != requiredArgs.end())
                    requiredArgs.erase(pos);
            }
            else {
                std::cerr << "Отсутствует значение для аргумента: " << arg << std::endl; // Ошибка: значение не указано
                return false;
            }
        }
        else {
            std::cerr << "Неизвестный аргумент: " << arg << std::endl; // Ошибка: неверный аргумент
            std::cerr << "Использование: " << argv[0] << " -ffgeom <формат> -fpgeom <путь> -ffgrid <формат> -fpgrid <путь>" << std::endl;
            return false;
        }
    }

    // Проверка отсутствия обязательных аргументов
    // Если есть отсутствующие обязательные аргументы, выводим их на экран
    if (!requiredArgs.empty()) {
        std::cerr << "Отсутствуют обязательные аргументы: ";

        for (std::size_t i = 0; i < requiredArgs.size(); ++i) {
            std::cerr << requiredArgs[i]; // Вывод пропущенного аргумента
            if (i < requiredArgs.size() - 1) { // Проверка, если не последний элемент
                std::cerr << " "; // Добавляем пробел между аргументами
            }
        }

        std::cerr << std::endl;
        return false;
    }

    return true; // Парсинг завершен успешно
}