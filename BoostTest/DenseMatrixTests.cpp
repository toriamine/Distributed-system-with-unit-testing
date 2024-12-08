#include <boost/test/unit_test.hpp>
#include "../Lab/DenseMatrix.h"
#include <stdexcept>

BOOST_AUTO_TEST_SUITE(DenseMatrixTests)

// ��������� ����������� ������ DenseMatrix
BOOST_AUTO_TEST_CASE(DenseConstructorTest) {
    // ������� 3x3 �������
    DenseMatrix<double> mat(3, 3);
    // ���������, ��� ���������� ����� ����� 3
    BOOST_CHECK_EQUAL(mat.rows(), 3);
    // ���������, ��� ���������� ������� ����� 3
    BOOST_CHECK_EQUAL(mat.cols(), 3);

    // ��������, ��� ��� �������� ������� ����� ����
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            BOOST_CHECK_EQUAL(mat(i, j), 0.0); // ��� �������� ������ ��������� 0.0
        }
    }
}

// ��������� ������������� � �������������� �������
BOOST_AUTO_TEST_CASE(DenseInitializerListTest) {
    // ������� ������� 2x3 � ��������� �����������
    DenseMatrix<double> mat{ {1, 2, 3}, {4, 5, 6} };
    // ��������� ����������� �������
    BOOST_CHECK_EQUAL(mat.rows(), 2); // ��� ������
    BOOST_CHECK_EQUAL(mat.cols(), 3); // ��� �������

    // ��������� �������� ��������� ��������� �������
    BOOST_CHECK_EQUAL(mat(0, 0), 1); // ������ �������
    BOOST_CHECK_EQUAL(mat(1, 2), 6); // ��������� �������
}

// ��������� �������� �������� ������
BOOST_AUTO_TEST_CASE(DenseAdditionTest) {
    // ������� ��� ������� 2x2
    DenseMatrix<double> mat1{ {1, 2}, {3, 4} };
    DenseMatrix<double> mat2{ {5, 6}, {7, 8} };
    // �������� ������
    DenseMatrix<double> result = mat1 + mat2;

    // ��������� �������� ��������� �������������� �������
    BOOST_CHECK_EQUAL(result(0, 0), 6); // 1 + 5 = 6
    BOOST_CHECK_EQUAL(result(1, 1), 12); // 4 + 8 = 12
}

// ��������� �������� ��������� ������
BOOST_AUTO_TEST_CASE(DenseSubtractionTest) {
    // ������� ��� ������� 2x2
    DenseMatrix<double> mat1{ {5, 6}, {7, 8} };
    DenseMatrix<double> mat2{ {1, 2}, {3, 4} };
    // ��������� ������
    DenseMatrix<double> result = mat1 - mat2;

    // ��������� �������� ��������� �������������� �������
    BOOST_CHECK_EQUAL(result(0, 0), 4); // 5 - 1 = 4
    BOOST_CHECK_EQUAL(result(1, 1), 4); // 8 - 4 = 4
}

// ��������� �������� ��������� ������
BOOST_AUTO_TEST_CASE(DenseMultiplicationTest) {
    // ������� ��� ������� 2x2
    DenseMatrix<double> mat1{ {1, 2}, {3, 4} };
    DenseMatrix<double> mat2{ {2, 0}, {1, 2} };
    // ��������� ������
    DenseMatrix<double> result = mat1 * mat2;

    // ��������� �������� ��������� �������������� �������
    BOOST_CHECK_EQUAL(result(0, 0), 4); // 1*2 + 2*1 = 4
    BOOST_CHECK_EQUAL(result(1, 1), 8); // 3*0 + 4*2 = 8
}

BOOST_AUTO_TEST_CASE(MatrixTestDense) {
    DenseMatrix<double> mat1{ {1, 2}, {3, 4} };
    DenseMatrix<double> mat2{ {5, 6}, {7, 8} };

    // ��������
    DenseMatrix<double> resultAdd = mat1 + mat2;
    BOOST_CHECK_EQUAL(resultAdd(0, 0), 6);
    BOOST_CHECK_EQUAL(resultAdd(1, 1), 12);

    // ���������
    DenseMatrix<double> resultSub = mat2 - mat1;
    BOOST_CHECK_EQUAL(resultSub(0, 0), 4);
    BOOST_CHECK_EQUAL(resultSub(1, 1), 4);

    // ���������
    DenseMatrix<double> resultMul = mat1 * mat2;
    BOOST_CHECK_EQUAL(resultMul(0, 0), 19);
    BOOST_CHECK_EQUAL(resultMul(0, 1), 22);
    BOOST_CHECK_EQUAL(resultMul(1, 0), 43);
    BOOST_CHECK_EQUAL(resultMul(1, 1), 50);
}

BOOST_AUTO_TEST_CASE(MatrixTestDense1) {
    DenseMatrix<double> mat1{ {1, 2}, {3, 4} };
    DenseMatrix<double> mat2{ {5, 6}, {7, 8} };

    // ��������
    DenseMatrix<double> resultAdd = mat1 + mat2;
    BOOST_CHECK_EQUAL(resultAdd(0, 0), 6);
    BOOST_CHECK_EQUAL(resultAdd(1, 1), 12);

    // ���������
    DenseMatrix<double> resultSub = mat2 - mat1;
    BOOST_CHECK_EQUAL(resultSub(0, 0), 4);
    BOOST_CHECK_EQUAL(resultSub(1, 1), 4);

    // ���������
    DenseMatrix<double> resultMul = mat1 * mat2;
    BOOST_CHECK_EQUAL(resultMul(0, 0), 19); // 1*5 + 2*7
    BOOST_CHECK_EQUAL(resultMul(0, 1), 22); // 1*6 + 2*8
    BOOST_CHECK_EQUAL(resultMul(1, 0), 43); // 3*5 + 4*7
    BOOST_CHECK_EQUAL(resultMul(1, 1), 50); // 3*6 + 4*8
}

/*
BOOST_AUTO_TEST_CASE(DenseIncompatibleDimensionsTest) {
    DenseMatrix<double> mat1{ {1, 2} };  // 1x2
    DenseMatrix<double> mat2{ {1}, {2} }; // 2x1

    BOOST_CHECK_THROW(mat1 + mat2, std::runtime_error);
    BOOST_CHECK_THROW(mat1 - mat2, std::runtime_error);
    BOOST_CHECK_THROW(mat1 * mat2, std::runtime_error);
}
*/

BOOST_AUTO_TEST_SUITE_END()