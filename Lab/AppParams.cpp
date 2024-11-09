#include "AppParams.h"
#include <iostream>
#include <map>
#include <vector>

bool AppParams::ParseCommandLine(int argc, char* argv[]) {
    // �������� ����������� ���������� � ��������������� ����� ������
    std::map<std::string, std::string*> argMap = {
        {"-ffgeom", &geometryFileFormat}, // ���� ������� ����� ���������
        {"-fpgeom", &geometryFilePath},   // ���� ���� � ����� ���������
        {"-ffgrid", &gridFileFormat},      // ���� ������� ����� �����
        {"-fpgrid", &gridFilePath}         // ���� ���� � ����� �����
    };

    // ������ ������������ ����������
    std::vector<std::string> requiredArgs = {
        "-ffgeom", "-fpgeom", "-ffgrid", "-fpgrid"
    };

    // ������� ���������� ��������� ������
    for (int i = 1; i < argc; i++) {
        std::string arg(argv[i]); // �������������� C-������ � std::string

        // ���������� auto ��� ��������������� ����������� ���� ��� ���������
        // ���: std::map<std::string, std::string*>::iterator
        //iterator - ��� ���������� ��� ������������� second(value), first(key)
        auto it = argMap.find(arg); // ����� ��������� � �����

        if (it != argMap.end()) { // ���� ������
            if (++i < argc) { // �������� ������� ���������� ���������
                *(it->second) = argv[i]; // ���������� ���������������� ����

                // �������� ��������� �� ������ ������������, ���� �� ��� ������������
                // auto ������� ���: std::vector<std::string>::iterator
                auto pos = std::find(requiredArgs.begin(), requiredArgs.end(), arg);
                if (pos != requiredArgs.end())
                    requiredArgs.erase(pos);
            }
            else {
                std::cerr << "����������� �������� ��� ���������: " << arg << std::endl; // ������: �������� �� �������
                return false;
            }
        }
        else {
            std::cerr << "����������� ��������: " << arg << std::endl; // ������: �������� ��������
            std::cerr << "�������������: " << argv[0] << " -ffgeom <������> -fpgeom <����> -ffgrid <������> -fpgrid <����>" << std::endl;
            return false;
        }
    }

    // �������� ���������� ������������ ����������
    // ���� ���� ������������� ������������ ���������, ������� �� �� �����
    if (!requiredArgs.empty()) {
        std::cerr << "����������� ������������ ���������: ";

        for (std::size_t i = 0; i < requiredArgs.size(); ++i) {
            std::cerr << requiredArgs[i]; // ����� ������������ ���������
            if (i < requiredArgs.size() - 1) { // ��������, ���� �� ��������� �������
                std::cerr << " "; // ��������� ������ ����� �����������
            }
        }

        std::cerr << std::endl;
        return false;
    }

    return true; // ������� �������� �������
}