#include <boost/test/unit_test.hpp>
#include "../Lab/Geometry2D.cpp"
#include "../Lab/AppParams.cpp"
#include <iostream>
#include <map>

BOOST_AUTO_TEST_SUITE(GeometryTests) // ��������� ����� ������ ��� Geometry2D

// �������� ������ ��� �������� �������������� ������ � �� ������
BOOST_AUTO_TEST_CASE(GeometryTests_LoadAndPrintGeometry) {
    // �������� ���������� ���������� �� ��������� ������
    // ����������� ��������� ��� ��������� � ��������������� ���������
    const char* argv[] = {
        "program_name",
        "-ffgeom", "Geometry_TXT_Format",
        "-fpgeom", "geometry2d.txt", //���� ���� ������ ���� � ����� BoostTest
        "-ffgrid", "grid2d_params_TXT_Format",
        "-fpgrid", "grid2d_params.txt"
    };
    int argc = sizeof(argv) / sizeof(argv[0]); // ���������� ���������� ����������

    // �������� ������� AppParams ��� �������� ���������� ��������� ������
    AppParams appParams;

    // ���������, ��� ��������� ������� ����������
    BOOST_REQUIRE(appParams.ParseCommandLine(argc, const_cast<char**>(argv)));

    // �������� ������� Geometry2D � ������������� �����������
    Geometry2D geometry2D(appParams);

    // ������� ���������� � ��������� � �������
    geometry2D.Print();

    // ��������� �������� ��������� �������� ������ ���������
    // ������ ��������: �������� � (0, 0) ������ ���� 0
    BOOST_CHECK_EQUAL(geometry2D.GetData(0, 0), 0);
    // ������ ��������: �������� � (1, 2) ������ ���� 0
    BOOST_CHECK_EQUAL(geometry2D.GetData(1, 2), 0);
    // ������ ��������: �������� � (4, 4) ������ ���� 1
    BOOST_CHECK_EQUAL(geometry2D.GetData(4, 4), 1);
}

// �������� ������ ��� �������� ��������� ������ ��� �������������� �����
BOOST_AUTO_TEST_CASE(GeometryTests_FailOnInvalidFile) {
    // �������� ������� ����������, ��� ������ �������������� ����
    const char* argv[] = {
        "program_name",
        "-ffgeom", "Geometry_TXT_Format",
        "-fpgeom", "non_existing_file.txt",
        "-ffgrid", "grid2d_params_TXT_Format",
        "-fpgrid", "grid2d_params.txt" //���� ���� ������ ���� � ����� BoostTest
    };

    int argc = sizeof(argv) / sizeof(argv[0]); // ���������� ���������� ����������

    // �������� ������� AppParams ��� �������� ���������� ��������� ������
    AppParams appParams;

    // ���������, ��� ��������� ������� ����������
    BOOST_REQUIRE(appParams.ParseCommandLine(argc, const_cast<char**>(argv)));

    // ��������, ��� ����������� Geometry2D ����������� ����������
    // ��� ������� ������� ������ Geometry2D � ������������ ������
    BOOST_CHECK_THROW({
        Geometry2D geometry2D(appParams); // ������� ������ ����������
        }, std::runtime_error); // �������� �� ��� ����������
}

BOOST_AUTO_TEST_SUITE_END() // ��������� ����� ������