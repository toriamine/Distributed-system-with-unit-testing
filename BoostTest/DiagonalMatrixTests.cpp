#include <boost/test/unit_test.hpp>
#include "../Lab/DiagonalMatrix.cpp"

BOOST_AUTO_TEST_SUITE(DiagonalMatrixTests) // ������ ������ ������ ��� ������������ ������

// ������������ ������������ � ������� � ���������
BOOST_AUTO_TEST_CASE(DiagonalMatrixTests_ConstructorTest) {

    DiagonalMatrix<double> mat(3); // ������� ������������ ������� 3x3

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
    BOOST_CHECK_EQUAL(mat(0, 2), 0.0); // �������, ��� ������� � (0, 2) ����� 0.0
    BOOST_CHECK_EQUAL(mat(1, 0), 0.0); // �������, ��� ������� � (1, 0) ����� 0.0
    BOOST_CHECK_EQUAL(mat(1, 2), 0.0); // �������, ��� ������� � (1, 2) ����� 0.0
    BOOST_CHECK_EQUAL(mat(2, 0), 0.0); // �������, ��� ������� � (2, 0) ����� 0.0
    BOOST_CHECK_EQUAL(mat(2, 1), 0.0); // �������, ��� ������� � (2, 1) ����� 0.0
}

// ������������ �������� ������������ ������
BOOST_AUTO_TEST_CASE(DiagonalMatrixTests_AdditionTest) {

    DiagonalMatrix<int> matrixA{ 1, 2, 3 };
    DiagonalMatrix<int> matrixB{ 4, 5, 6 };
    DiagonalMatrix<int> result = matrixA + matrixB;

    BOOST_CHECK_EQUAL(result(0, 0), 5);
    BOOST_CHECK_EQUAL(result(1, 1), 7);
    BOOST_CHECK_EQUAL(result(2, 2), 9);

    BOOST_CHECK_EQUAL(result(0, 1), 0);
    BOOST_CHECK_EQUAL(result(0, 2), 0);
    BOOST_CHECK_EQUAL(result(1, 0), 0);
    BOOST_CHECK_EQUAL(result(1, 2), 0);
    BOOST_CHECK_EQUAL(result(2, 0), 0);
    BOOST_CHECK_EQUAL(result(2, 1), 0);

}

// ������������ ��������� ������������ ������
BOOST_AUTO_TEST_CASE(DiagonalMatrixTests_SubtractionTest) {

    DiagonalMatrix<int> matrixA{ 5, 6, 7 };
    DiagonalMatrix<int> matrixB{ 2, 1, 0 };
    DiagonalMatrix<int> result = matrixA - matrixB;

    BOOST_CHECK_EQUAL(result(0, 0), 3);
    BOOST_CHECK_EQUAL(result(1, 1), 5);
    BOOST_CHECK_EQUAL(result(2, 2), 7);

    BOOST_CHECK_EQUAL(result(0, 1), 0);
    BOOST_CHECK_EQUAL(result(0, 2), 0);
    BOOST_CHECK_EQUAL(result(1, 0), 0);
    BOOST_CHECK_EQUAL(result(1, 2), 0);
    BOOST_CHECK_EQUAL(result(2, 0), 0);
    BOOST_CHECK_EQUAL(result(2, 1), 0);

}

// ������������ ��������� ������������ ������
BOOST_AUTO_TEST_CASE(DiagonalMatrixTests_MultiplicationTest) {

    DiagonalMatrix<int> matrixA{ 1, 2, 3 };
    DiagonalMatrix<int> matrixB{ 4, 5, 6 };
    DiagonalMatrix<int> result = matrixA * matrixB;

    BOOST_CHECK_EQUAL(result(0, 0), 4);
    BOOST_CHECK_EQUAL(result(1, 1), 10);
    BOOST_CHECK_EQUAL(result(2, 2), 18);

    BOOST_CHECK_EQUAL(result(0, 1), 0);
    BOOST_CHECK_EQUAL(result(0, 2), 0);
    BOOST_CHECK_EQUAL(result(1, 0), 0);
    BOOST_CHECK_EQUAL(result(1, 2), 0);
    BOOST_CHECK_EQUAL(result(2, 0), 0);
    BOOST_CHECK_EQUAL(result(2, 1), 0);

}

// ������������ ��������� ���������� ����� � ��������
BOOST_AUTO_TEST_CASE(DiagonalMatrixTests_SizeTest) {

    DiagonalMatrix<int> matrix(3); // �������� ������������ ������� 3x3 � ������
    BOOST_CHECK_EQUAL(matrix.rows(), 3);
    BOOST_CHECK_EQUAL(matrix.cols(), 3);

}

// ������������ �������� ������������� ������
BOOST_AUTO_TEST_CASE(DiagonalMatrixTests_IncompatibleAddition) {

    DiagonalMatrix<double> a{ 1, 2 }; // ������� ������ ������������ ������� �������� 2x2
    DiagonalMatrix<double> b{ 1, 2, 3 }; // ������� ������ ������������ ������� �������� 3x3

    // ���������, ��� �������� ���� ������ �������� ����������
    BOOST_CHECK_THROW(a + b, std::invalid_argument); // ������� ���������� ��� �������� ������������� ������

}

// ������������ ��������� ������������� ������
BOOST_AUTO_TEST_CASE(DiagonalMatrixTests_IncompatibleMultiplication) {

    DiagonalMatrix<double> a{ 1, 2, 3 }; // ������� ������ ������������ ������� �������� 3x3
    DiagonalMatrix<double> b{ 1, 2 }; // ������� ������ ������������ ������� �������� 2x2

    // ���������, ��� ��������� ���� ������ �������� ����������
    BOOST_CHECK_THROW(a * b, std::invalid_argument); // ������� ���������� ��� ��������� ������������� ������

}

BOOST_AUTO_TEST_CASE(DiagonalMatrixTests_IncompatibleSubtraction) {

    DiagonalMatrix<double> a{ 1, 2, 3 }; // ������� ������ ������������ ������� �������� 3x3
    DiagonalMatrix<double> b{ 1, 2 }; // ������� ������ ������������ ������� �������� 2x2

    // ���������, ��� ��������� ���� ������ �������� ����������
    BOOST_CHECK_THROW(a - b, std::invalid_argument); // ������� ���������� ��� ��������� ������������� ������

}

BOOST_AUTO_TEST_SUITE_END() // ����� ������ ������ ��� ������������ ������