#include <boost/test/unit_test.hpp>
#include "../Lab/DiagonalMatrix.h"
#include "../Lab/DiagonalMatrix.cpp"
#include "../Lab/Matrix.h"

BOOST_AUTO_TEST_SUITE(DiagonalMatrixTests) // ������ ������ ������ ��� ������������ ������

// ������������ ������������ � ������� � ���������
BOOST_AUTO_TEST_CASE(ConstructorAndAccess) {
    DiagonalMatrix<double> mat(3, 3); // ������� ������������ ������� 3x3

    // ������������� �������� �� ������� ���������
    mat(0, 0) = 1.0; // ������ ������� (0, 0)
    mat(1, 1) = 2.0; // ������ ������� (1, 1)
    mat(2, 2) = 3.0; // ������ ������� (2, 2)

    // ��������� ������������ ������� � ������������ ���������
    BOOST_CHECK_EQUAL(mat(0, 0), 1.0); // �������, ��� ������� � (0, 0) ����� 1.0
    BOOST_CHECK_EQUAL(mat(1, 1), 2.0); // �������, ��� ������� � (1, 1) ����� 2.0
    BOOST_CHECK_EQUAL(mat(2, 2), 3.0); // �������, ��� ������� � (2, 2) ����� 3.0

    // �������� �������� ��� ������� ���������
    BOOST_CHECK_EQUAL(mat(0, 1), 0.0); // �������, ��� ������� � (0, 1) ����� 0.0
    BOOST_CHECK_EQUAL(mat(1, 0), 0.0); // �������, ��� ������� � (1, 0) ����� 0.0
}

// ������������ �������� ������������ ������
BOOST_AUTO_TEST_CASE(Addition) {
    DiagonalMatrix<double> a(3, 3); // ������� ������ ������������ ������� 3x3
    DiagonalMatrix<double> b(3, 3); // ������� ������ ������������ ������� 3x3

    // ���������� ������� a
    a(0, 0) = 1.0; // (0, 0)
    a(1, 1) = 2.0; // (1, 1)
    a(2, 2) = 3.0; // (2, 2)

    // ���������� ������� b
    b(0, 0) = 4.0; // (0, 0)
    b(1, 1) = 5.0; // (1, 1)
    b(2, 2) = 6.0; // (2, 2)

    DiagonalMatrix<double>* result = static_cast<DiagonalMatrix<double>*>(a + b); // �������� ���� ������������ ������

    // �������� ����������� ��������
    BOOST_CHECK_EQUAL((*result)(0, 0), 5.0);// �������, ��� (0, 0) ����� 1.0 + 4.0 = 5.0
    BOOST_CHECK_EQUAL((*result)(1, 1), 7.0); // �������, ��� (1, 1) ����� 2.0 + 5.0 = 7.0
    BOOST_CHECK_EQUAL((*result)(2, 2), 9.0);// �������, ��� (2, 2) ����� 3.0 + 6.0 = 9.0

    delete result;
}

// ������������ ��������� ������������ ������
BOOST_AUTO_TEST_CASE(Subtraction) {
    DiagonalMatrix<double> a(3, 3); // ������� ������ ������������ ������� 3x3
    DiagonalMatrix<double> b(3, 3); // ������� ������ ������������ ������� 3x3

    // ���������� ������� a
    a(0, 0) = 5.0; // (0, 0)
    a(1, 1) = 6.0; // (1, 1)
    a(2, 2) = 7.0; // (2, 2)

    // ���������� ������� b
    b(0, 0) = 3.0; // (0, 0)
    b(1, 1) = 2.0; // (1, 1)
    b(2, 2) = 1.0; // (2, 2)

    DiagonalMatrix<double>* result = static_cast<DiagonalMatrix<double>*>(a - b); // ��������� ���� ������������ ������

    // �������� ����������� ���������
    BOOST_CHECK_EQUAL((*result)(0, 0), 2.0); // �������, ��� (0, 0) ����� 5.0 - 3.0 = 2.0
    BOOST_CHECK_EQUAL((*result)(1, 1), 4.0); // �������, ��� (1, 1) ����� 6.0 - 2.0 = 4.0
    BOOST_CHECK_EQUAL((*result)(2, 2), 6.0); // �������, ��� (2, 2) ����� 7.0 - 1.0 = 6.0

    delete result;
}

// ������������ ��������� ������������ ������
BOOST_AUTO_TEST_CASE(Multiplication) {
    DiagonalMatrix<double> a(3, 3); // ������� ������ ������������ ������� 3x3
    DiagonalMatrix<double> b(3, 3); // ������� ������ ������������ ������� 3x3

    // ���������� ������� a
    a(0, 0) = 1.0; // (0, 0)
    a(1, 1) = 2.0; // (1, 1)
    a(2, 2) = 3.0; // (2, 2)

    // ���������� ������� b
    b(0, 0) = 4.0; // (0, 0)
    b(1, 1) = 5.0; // (1, 1)
    b(2, 2) = 6.0; // (2, 2)

    DiagonalMatrix<double>* result = static_cast<DiagonalMatrix<double>*>(a * b); // ��������� ���� ������������ ������

    // �������� ����������� ���������

    BOOST_CHECK_EQUAL((*result)(0, 0), 4.0); // �������, ��� (0, 0) ����� 1.0 * 4.0 = 4.0
    BOOST_CHECK_EQUAL((*result)(1, 1), 10.0); // �������, ��� (1, 1) ����� 2.0 * 5.0 = 10.0
    BOOST_CHECK_EQUAL((*result)(2, 2), 18.0); // �������, ��� (2, 2) ����� 3.0 * 6.0 = 18.0

    delete result;
}

// ������������ �������� ������������� ������
BOOST_AUTO_TEST_CASE(IncompatibleAddition) {
    DiagonalMatrix<double> a(2, 3); // ������� ������ ������������ ������� 2x3
    DiagonalMatrix<double> b(3, 2); // ������� ������ ������������ ������� 3x2

    // ���������, ��� �������� ���� ������ �������� ����������
    BOOST_CHECK_THROW(a + b, std::runtime_error); // ������� ���������� ��� �������� ������������� ������
}

// ������������ ��������� ������������� ������
BOOST_AUTO_TEST_CASE(IncompatibleMultiplication) {
    DiagonalMatrix<double> a(3, 3); // ������� ������ ������������ ������� 3x3
    DiagonalMatrix<double> b(2, 3); // ������� ������ ������������ ������� 2x3 (������������� �������)

    // ���������, ��� ��������� ���� ������ �������� ����������
    BOOST_CHECK_THROW(a * b, std::runtime_error); // ������� ���������� ��� ��������� ������������� ������
}



BOOST_AUTO_TEST_SUITE_END() // ����� ������ ������ ��� ������������ ������
