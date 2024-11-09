#include <boost/test/unit_test.hpp>
#include "../Lab/DenseMatrix.h"
#include "../Lab/DiagonalMatrix.h"
#include "../Lab/BlockMatrix.h"

BOOST_AUTO_TEST_SUITE(MatrixTests)

BOOST_AUTO_TEST_CASE(MatrixTestDense) {
    DenseMatrix<double> mat1{ {1, 2}, {3, 4} };
    DenseMatrix<double> mat2{ {5, 6}, {7, 8} };

    // Сложение
    DenseMatrix<double> resultAdd = mat1 + mat2;
    BOOST_CHECK_EQUAL(resultAdd(0, 0), 6);
    BOOST_CHECK_EQUAL(resultAdd(1, 1), 12);

    // Вычитание
    DenseMatrix<double> resultSub = mat2 - mat1;
    BOOST_CHECK_EQUAL(resultSub(0, 0), 4);
    BOOST_CHECK_EQUAL(resultSub(1, 1), 4);

    // Умножение
    DenseMatrix<double> resultMul = mat1 * mat2;
    BOOST_CHECK_EQUAL(resultMul(0, 0), 19);
    BOOST_CHECK_EQUAL(resultMul(0, 1), 22);
    BOOST_CHECK_EQUAL(resultMul(1, 0), 43);
    BOOST_CHECK_EQUAL(resultMul(1, 1), 50);
}

BOOST_AUTO_TEST_CASE(MatrixTestDiagonal) {
    DenseMatrix<double> mat1{ {1, 2}, {3, 4} };
    DenseMatrix<double> mat2{ {5, 6}, {7, 8} };

    // Сложение
    DenseMatrix<double> resultAdd = mat1 + mat2;
    BOOST_CHECK_EQUAL(resultAdd(0, 0), 6);
    BOOST_CHECK_EQUAL(resultAdd(1, 1), 12);

    // Вычитание
    DenseMatrix<double> resultSub = mat2 - mat1;
    BOOST_CHECK_EQUAL(resultSub(0, 0), 4);
    BOOST_CHECK_EQUAL(resultSub(1, 1), 4);

    // Умножение
    DenseMatrix<double> resultMul = mat1 * mat2;
    BOOST_CHECK_EQUAL(resultMul(0, 0), 19); // 1*5 + 2*7
    BOOST_CHECK_EQUAL(resultMul(0, 1), 22); // 1*6 + 2*8
    BOOST_CHECK_EQUAL(resultMul(1, 0), 43); // 3*5 + 4*7
    BOOST_CHECK_EQUAL(resultMul(1, 1), 50); // 3*6 + 4*8
}

BOOST_AUTO_TEST_CASE(MatrixTestBlock) {
    // Correct initialization of BlockMatrix
    size_t blockRows = 2; // Number of rows in each block
    size_t blockCols = 2; // Number of columns in each block
    BlockMatrix<double> block1(2, 2, blockRows, blockCols); // 2x2 blocks of 2x2 size
    BlockMatrix<double> block2(2, 2, blockRows, blockCols); // 2x2 blocks of 2x2 size

    // Set values for the blocks in block1
    block1(0, 0)(0, 0) = 1;
    block1(0, 0)(0, 1) = 2;
    block1(0, 1)(0, 0) = 3;
    block1(0, 1)(0, 1) = 4;

    // Set values for the blocks in block2
    block2(0, 0)(0, 0) = 5;
    block2(0, 0)(0, 1) = 6;
    block2(0, 1)(0, 0) = 7;
    block2(0, 1)(0, 1) = 8;

    // Сложение
    BlockMatrix<double> resultAdd = block1 + block2;
    BOOST_CHECK_EQUAL(resultAdd(0, 0)(0, 0), 6);
    BOOST_CHECK_EQUAL(resultAdd(0, 0)(0, 1), 8);
    BOOST_CHECK_EQUAL(resultAdd(0, 1)(0, 0), 10);
    BOOST_CHECK_EQUAL(resultAdd(0, 1)(0, 1), 12);

    // Вычитание
    BlockMatrix<double> resultSub = block2 - block1;
    BOOST_CHECK_EQUAL(resultSub(0, 0)(0, 0), 4);
    BOOST_CHECK_EQUAL(resultSub(0, 0)(0, 1), 4);
    BOOST_CHECK_EQUAL(resultSub(0, 1)(0, 0), 4);
    BOOST_CHECK_EQUAL(resultSub(0, 1)(0, 1), 4);
}

BOOST_AUTO_TEST_SUITE_END()
