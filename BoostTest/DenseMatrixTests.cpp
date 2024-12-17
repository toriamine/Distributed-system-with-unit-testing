#include <boost/test/unit_test.hpp>
#include "../Lab/DenseMatrix.cpp"

BOOST_AUTO_TEST_SUITE(DenseMatrixTests)

// ��������� ����������� ������ DenseMatrix
BOOST_AUTO_TEST_CASE(DenseMatrixTests_ConstructorTest) {

    // ������� 3x3 �������
    DenseMatrix<double> mat(3, 3);

    // ���������, ��� ���������� ����� ����� 3
    BOOST_CHECK_EQUAL(mat.rows(), 3);

    // ���������, ��� ���������� ������� ����� 3
    BOOST_CHECK_EQUAL(mat.cols(), 3);

    // ��������, ��� ��� �������� ������� ����� ����
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            BOOST_CHECK_EQUAL(mat(i, j), 0.0); // ��� �������� ������ ���� ����� 0.0
        }
    }

}

// ��������� ������������� � �������������� �������
BOOST_AUTO_TEST_CASE(DenseMatrixTests_InitializerListTest) {

    // ������� ������� 2x3 � �������������� ������
    DenseMatrix<double> mat{ {1, 2, 3}, {4, 5, 6} };

    // ��������� ����������� �������
    BOOST_CHECK_EQUAL(mat.rows(), 2); // ��� ������
    BOOST_CHECK_EQUAL(mat.cols(), 3); // ��� �������

    // ��������� �������� ��������� �������
    BOOST_CHECK_EQUAL(mat(0, 0), 1);
    BOOST_CHECK_EQUAL(mat(0, 1), 2);
    BOOST_CHECK_EQUAL(mat(0, 2), 3);
    BOOST_CHECK_EQUAL(mat(1, 0), 4);
    BOOST_CHECK_EQUAL(mat(1, 1), 5);
    BOOST_CHECK_EQUAL(mat(1, 2), 6);

}

// ��������� �������� �������� ������
BOOST_AUTO_TEST_CASE(DenseMatrixTests_AdditionTest) {

    // ������� ��� ������� 2x2
    DenseMatrix<double> mat1{ {1, 2}, {3, 4} };
    DenseMatrix<double> mat2{ {5, 6}, {7, 8} };

    // �������� ������
    DenseMatrix<double> result = mat1 + mat2;

    // ��������� �������� ��������� �������������� �������
    BOOST_CHECK_EQUAL(result(0, 0), 6);
    BOOST_CHECK_EQUAL(result(0, 1), 8);
    BOOST_CHECK_EQUAL(result(1, 0), 10);
    BOOST_CHECK_EQUAL(result(1, 1), 12);

}

// ��������� �������� ��������� ������
BOOST_AUTO_TEST_CASE(DenseMatrixTests_SubtractionTest) {

    // ������� ��� ������� 2x2
    DenseMatrix<double> mat1{ {5, 6}, {7, 8} };
    DenseMatrix<double> mat2{ {1, 2}, {3, 4} };

    // ��������� ������
    DenseMatrix<double> result = mat1 - mat2;

    // ��������� �������� ��������� �������������� �������
    BOOST_CHECK_EQUAL(result(0, 0), 4);
    BOOST_CHECK_EQUAL(result(0, 1), 4);
    BOOST_CHECK_EQUAL(result(1, 0), 4);
    BOOST_CHECK_EQUAL(result(1, 1), 4);

}

// ��������� �������� ��������� ������
BOOST_AUTO_TEST_CASE(DenseMatrixTests_MultiplicationTest) {

    // ������� ��� ������� 2x2
    DenseMatrix<double> mat1{ {1, 2}, {3, 4} };
    DenseMatrix<double> mat2{ {5, 6}, {7, 8} };

    // ��������� ������
    DenseMatrix<double> result = mat1 * mat2;

    // ��������� �������� ��������� �������������� �������
    BOOST_CHECK_EQUAL(result(0, 0), 19); // 1*5 + 2*7 = 19
    BOOST_CHECK_EQUAL(result(0, 1), 22); // 1*6 + 2*8 = 22
    BOOST_CHECK_EQUAL(result(1, 0), 43); // 3*5 + 4*7 = 43
    BOOST_CHECK_EQUAL(result(1, 1), 50); // 3*6 + 4*8 = 50

}

BOOST_AUTO_TEST_CASE(DenseMatrixTests_IncompatibleDimensionsTest) {
    DenseMatrix<double> mat1{ {1, 2} };  // 1x2
    DenseMatrix<double> mat2{ {1}, {2} }; // 2x1

    BOOST_CHECK_THROW(mat1 + mat2, std::invalid_argument);
    BOOST_CHECK_THROW(mat1 - mat2, std::invalid_argument);
    BOOST_CHECK_THROW(mat1 * mat2, std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()