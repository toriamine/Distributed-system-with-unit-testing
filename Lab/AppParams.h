#pragma once

#include <string>

// ����� AppParams ��� �������� � ��������� ���������� ���������� (������ ����� ��������� ������)
class AppParams {
public:
    // ������ � ���� � ������ ���������
    std::string geometryFileFormat;  // ������ ����� ���������
    std::string geometryFilePath;    // ���� � ����� ���������

    // ������ � ���� � ������ �����
    std::string gridFileFormat;       // ������ ����� �����
    std::string gridFilePath;         // ���� � ����� �����

    // ����� ��� �������� ���������� ��������� ������
    bool ParseCommandLine(int argc, char* argv[]);
};
