#include <boost/test/unit_test.hpp>
#include "../Lab/BlockMatrix.h"

BOOST_AUTO_TEST_SUITE(BlockMatrixTests) // ������ ������ ������ ��� ������� ������

// ������������ ������������ � ������� � ��������� ������� �������
BOOST_AUTO_TEST_CASE(BlockMatrixTestConstructorAndAccess) {
    BlockMatrix<double, DenseMatrix> blockMatrix(2, 2, 2, 2); // ������� ������� ������� �� 2x2 ������, ������ �������� 2x2

    BlockMatrix<int, DenseMatrix> blockMatrixA(2, 2, 2, 2);

    // ������� ������� ������� 2x2 ������, ������ �� ������� 2x2 ��������
        // ��������� �������� � �����
    // ���� (0, 0):
    // [ 1.0, 2.0 ]
    // [ 3.0, 4.0 ]
    
    blockMatrixA.setBlock(0, 0, new DenseMatrix<int>(2, 2));
    blockMatrixA(0, 0) = 1; blockMatrixA(0, 1) = 2;
    blockMatrixA(1, 0) = 3; blockMatrixA(1, 1) = 4;

    // ���� (0, 1):
    // [ 5.0, 6.0 ]
    // [ 7.0, 8.0 ]

    blockMatrixA.setBlock(0, 1, new DenseMatrix<int>(2, 2));
    blockMatrixA(0, 2) = 5; blockMatrixA(0, 3) = 6;
    blockMatrixA(1, 2) = 7; blockMatrixA(1, 3) = 8;


    // ���� (1, 0):
    // [ 9.0, 10.0 ]
    // [ 11.0, 12.0 ]
    blockMatrixA.setBlock(1, 0, new DenseMatrix<int>(2, 2));
    blockMatrixA(2, 0) = 9; blockMatrixA(2, 1) = 10;
    blockMatrixA(3, 0) = 11; blockMatrixA(3, 1) = 12;

    // ���� (1, 1):
    // [ 13.0, 14.0 ]
    // [ 15.0, 16.0 ]
    blockMatrixA.setBlock(1, 1, new DenseMatrix<int>(2, 2));
    blockMatrixA(2, 2) = 13; blockMatrixA(2, 3) = 14;
    blockMatrixA(3, 2) = 15; blockMatrixA(3, 3) = 16;


    // �������� ������� � ������ � �� ���������
    BOOST_CHECK_EQUAL(blockMatrixA(0, 0), 1);   //���� ������� �������� ������ �������
    BOOST_CHECK_EQUAL(blockMatrixA(0, 3), 6);   // ���� ���������� �������� ������ ������
    BOOST_CHECK_EQUAL(blockMatrixA(1, 2), 7);   // ���� �������� �� ������� �����
    BOOST_CHECK_EQUAL(blockMatrixA(2, 1), 10);  // ���� �������� ������� ���� �������� �����
    BOOST_CHECK_EQUAL(blockMatrixA(3, 3), 16);  // ���� ���������� ��������
}

BOOST_AUTO_TEST_CASE(BlockMatrixTestAddition) {
    BlockMatrix<double, DenseMatrix> a(2, 2, 2, 2); // ������� ������ ������� ������� 2x2
    BlockMatrix<double, DenseMatrix> b(2, 2, 2, 2); // ������� ������ ������� ������� 2x2

    a.setBlock(0, 0, new DenseMatrix<double>(2, 2));
    a(0, 0) = 1; a(0, 1) = 2;
    a(1, 0) = 3; blockMatrixA(1, 1) = 4;

    blockMatrixA.setBlock(0, 1, new DenseMatrix<int>(2, 2));
    blockMatrixA(0, 2) = 5; blockMatrixA(0, 3) = 6;
    blockMatrixA(1, 2) = 7; blockMatrixA(1, 3) = 8;

    blockMatrixA.setBlock(1, 0, new DenseMatrix<int>(2, 2));
    blockMatrixA(2, 0) = 9; blockMatrixA(2, 1) = 10;
    blockMatrixA(3, 0) = 11; blockMatrixA(3, 1) = 12;

    blockMatrixA.setBlock(1, 1, new DenseMatrix<int>(2, 2));
    blockMatrixA(2, 2) = 13; blockMatrixA(2, 3) = 14;
    blockMatrixA(3, 2) = 15; blockMatrixA(3, 3) = 16;

    std::cout << "Block Matrix A:\n";
    blockMatrixA.Print();

    BlockMatrix<int, DenseMatrix> blockMatrixB(2, 2, 2, 2);
    blockMatrixB.setBlock(0, 0, new DenseMatrix<int>(2, 2));
    blockMatrixB(0, 0) = 1; blockMatrixB(0, 1) = 1;
    blockMatrixB(1, 0) = 1; blockMatrixB(1, 1) = 1;

    blockMatrixB.setBlock(0, 1, new DenseMatrix<int>(2, 2));
    blockMatrixB(0, 2) = 2; blockMatrixB(0, 3) = 2;
    blockMatrixB(1, 2) = 2; blockMatrixB(1, 3) = 2;

    blockMatrixB.setBlock(1, 0, new DenseMatrix<int>(2, 2));
    blockMatrixB(2, 0) = 3; blockMatrixB(2, 1) = 3;
    blockMatrixB(3, 0) = 3; blockMatrixB(3, 1) = 3;

    blockMatrixB.setBlock(1, 1, new DenseMatrix<int>(2, 2));
    blockMatrixB(2, 2) = 4; blockMatrixB(2, 3) = 4;
    blockMatrixB(3, 2) = 4; blockMatrixB(3, 3) = 4;

    // ���������� ������ ������� a
    // ���� (0, 0):
    // [ 1.0, 2.0 ]
    // [ 3.0, 4.0 ]
    a(0, 0)(0, 0) = 1.0;
    a(0, 0)(0, 1) = 2.0;
    a(0, 0)(1, 0) = 3.0;
    a(0, 0)(1, 1) = 4.0;

    // ���������� ������ ������� b
    // ���� (0, 0):
    // [ 5.0, 6.0 ]
    // [ 7.0, 8.0 ]
    b(0, 0)(0, 0) = 5.0;
    b(0, 0)(0, 1) = 6.0;
    b(0, 0)(1, 0) = 7.0;
    b(0, 0)(1, 1) = 8.0;

    BlockMatrix<double, DenseMatrix>* result = static_cast<BlockMatrix<double, DenseMatrix>*>(a + b);

    // �������� ����������� ��������
    // ��������� ���������:
    // [ 1.0 + 5.0, 2.0 + 6.0 ]  => [ 6.0, 8.0 ]
    // [ 3.0 + 7.0, 4.0 + 8.0 ]  => [ 10.0, 12.0 ]
    BOOST_CHECK_EQUAL((*result)(0, 0)(0, 0), 6.0);  // �������� ����� ������� ��������
    BOOST_CHECK_EQUAL((*result)(0, 0)(1, 1), 12.0); // �������� ����� ������� ��������

    delete result;
}

BOOST_AUTO_TEST_CASE(BlockMatrixTestSubtraction) {
    BlockMatrix<double, DenseMatrix> a(2, 2, 2, 2); // ������� ������ ������� ������� 2x2
    BlockMatrix<double, DenseMatrix> b(2, 2, 2, 2); // ������� ������ ������� ������� 2x2

    // ���������� ������ ������� a
    // ���� (0, 0):
    // [ 10.0, 12.0 ]
    // [ 14.0, 16.0 ]
    a(0, 0)(0, 0) = 10.0;
    a(0, 0)(0, 1) = 12.0;
    a(0, 0)(1, 0) = 14.0;
    a(0, 0)(1, 1) = 16.0;

    // ���������� ������ ������� b
    // ���� (0, 0):
    // [ 5.0, 6.0 ]
    // [ 7.0, 8.0 ]
    b(0, 0)(0, 0) = 5.0;
    b(0, 0)(0, 1) = 6.0;
    b(0, 0)(1, 0) = 7.0;
    b(0, 0)(1, 1) = 8.0;

    BlockMatrix<double, DenseMatrix>* result = static_cast<BlockMatrix<double, DenseMatrix>*>(a - b); // ��������� ���� ������� ������

    // �������� ����������� ���������
    // ��������� ���������:
    // [ 10.0 - 5.0, 12.0 - 6.0 ] => [ 5.0, 6.0 ]

    // [ 14.0 - 7.0, 16.0 - 8.0 ] => [ 7.0, 8.0 ]
    BOOST_CHECK_EQUAL((*result)(0, 0)(0, 0), 5.0);  // �������� �������� ������� ��������
    BOOST_CHECK_EQUAL((*result)(0, 0)(1, 1), 8.0); // �������� �������� ������� ��������

    delete result;
}

BOOST_AUTO_TEST_CASE(BlockMatrixTestMultiplication) {
    BlockMatrix<double, DenseMatrix> a(2, 2, 2, 2); // ������� ������ ������� ������� 2x2
    BlockMatrix<double, DenseMatrix> b(2, 2, 2, 2); // ������� ������ ������� ������� 2x2

    // ���������� ������ ������� a
    // ���� (0, 0):
    // [ 1.0, 2.0 ]
    // [ 3.0, 4.0 ]
    a(0, 0)(0, 0) = 1.0;
    a(0, 0)(0, 1) = 2.0;
    a(0, 0)(1, 0) = 3.0;
    a(0, 0)(1, 1) = 4.0;

    // ���������� ������ ������� b
    // ���� (0, 0):
    // [ 5.0, 6.0 ]
    // [ 7.0, 8.0 ]
    b(0, 0)(0, 0) = 5.0;
    b(0, 0)(0, 1) = 6.0;
    b(0, 0)(1, 0) = 7.0;
    b(0, 0)(1, 1) = 8.0;

    BlockMatrix<double, DenseMatrix>* result = static_cast<BlockMatrix<double, DenseMatrix>*>(a * b); // ��������� ���� ������� ������

    // �������� ����������� ���������
    // ��������� ���������:
    // [ (1.0*5.0 + 2.0*7.0), (1.0*6.0 + 2.0*8.0) ]
    // [ (3.0*5.0 + 4.0*7.0), (3.0*6.0 + 4.0*8.0) ]
    // = [ 19.0, 22.0 ]
    BOOST_CHECK_EQUAL((*result)(0, 0)(0, 0), 19.0); // �������� ������� ��������
    BOOST_CHECK_EQUAL((*result)(0, 0)(0, 1), 22.0); // �������� ������� ��������

    delete result;
}

// ������������ �������� ������������� ������
BOOST_AUTO_TEST_CASE(BlockMatrixTestIncompatibleAddition) {
    BlockMatrix<double, DenseMatrix> a(2, 2, 2, 2); // ������� ������ ������� ������� 2x2
    BlockMatrix<double, DenseMatrix> b(3, 2, 2, 2); // ������� ������ ������� ������� 3x2 (������������� ������)

    // ���������, ��� �������� ���� ������ �������� ����������
    BOOST_CHECK_THROW(a + b, std::runtime_error);
}

// ������������ ��������� ������������� ������
BOOST_AUTO_TEST_CASE(BlockMatrixTestIncompatibleMultiplication) {
    BlockMatrix<double> a(2, 2, 2, 2); // ������� ������ ������� ������� 2x2
    BlockMatrix<double> b(3, 2, 2, 2); // ������� ������ ������� ������� 3x2 (������������� �������)

    // ���������, ��� ��������� ���� ������ �������� ����������
    BOOST_CHECK_THROW(a * b, std::runtime_error);
}

// ������������ �������� ������� ������ � ���������� ���� int
BOOST_AUTO_TEST_CASE(BlockMatrixTestMatrixAdditionTest) {
    BlockMatrix<int, DenseMatrix> matrixA(2, 2, 1, 1); // ������� ������� ������� 2x2 � ������� 1x1
    // ���������� ������ ������� A
    // ���� (0, 0):
    // [ 1 ]
    matrixA(0, 0)(0, 0) = 1;
    // ���� (0, 1):
    // [ 2 ]
    matrixA(0, 1)(0, 0) = 2;
    // ���� (1, 0):
    // [ 3 ]
    matrixA(1, 0)(0, 0) = 3;
    // ���� (1, 1):
    // [ 4 ]
    matrixA(1, 1)(0, 0) = 4;

    BlockMatrix<int, DenseMatrix> matrixB(2, 2, 1, 1); // ������� ������� ������� 2x2 � ������� 1x1
    // ���������� ������ ������� B
    // ���� (0, 0):
    // [ 5 ]
    matrixB(0, 0)(0, 0) = 5;
    // ���� (0, 1):
    // [ 6 ]
    matrixB(0, 1)(0, 0) = 6;
    // ���� (1, 0):
    // [ 7 ]
    matrixB(1, 0)(0, 0) = 7;
    // ���� (1, 1):
    // [ 8 ]
    matrixB(1, 1)(0, 0) = 8;

    BlockMatrix<int, DenseMatrix>* result = static_cast<BlockMatrix<int, DenseMatrix>*>(matrixA + matrixB); // �������� ���� ������� ������

    // �������� ����������� ��������
    // ��������� ���������:
    // [ 1 + 5, 2 + 6 ] => [ 6, 8 ]
    // [ 3 + 7, 4 + 8 ] => [ 10, 12 ]
    BOOST_CHECK_EQUAL((*result)(0, 0)(0, 0), 6);  // �������� ����� ������� ��������
    BOOST_CHECK_EQUAL((*result)(0, 1)(0, 0), 8);  // �������� ����� ������� ��������
    BOOST_CHECK_EQUAL((*result)(1, 0)(0, 0), 10); // �������� ����� �������� ��������
    BOOST_CHECK_EQUAL((*result)(1, 1)(0, 0), 12); // �������� ����� ���������� ��������

    delete result;
}

BOOST_AUTO_TEST_CASE(BlockMatrixTestKroneckerProductTest) {
    BlockMatrix<int, DenseMatrix> A(3, 2, 1, 1);
    A(0, 0)(0, 0) = 1;
    A(0, 1)(0, 0) = 2;
    A(1, 0)(0, 0) = 3;
    A(1, 1)(0, 0) = 4;
    A(2, 0)(0, 0) = 1;
    A(2, 1)(0, 0) = 0;

    BlockMatrix<int, DenseMatrix> B(2, 3, 1, 1);
    B(0, 0)(0, 0) = 0;
    B(0, 1)(0, 0) = 5;
    B(0, 2)(0, 0) = 2;
    B(1, 0)(0, 0) = 6;
    B(1, 1)(0, 0) = 7;
    B(1, 2)(0, 0) = 3;

    BlockMatrix<int, DenseMatrix> result = A.KroneckerProduct(B);

    // ��������� A ����� 3 ������ � 2 �������, � B ����� 2 ������ � 3 �������,
    // �������������� ������� ����� ����� (3*2) x (2*3) = 6 x 6.

    // ��������� ��� �������� � ���������� ������������ ���������

    BOOST_CHECK_EQUAL(result(0, 0)(0, 0), 0);
    BOOST_CHECK_EQUAL(result(0, 1)(0, 0), 5);
    BOOST_CHECK_EQUAL(result(0, 2)(0, 0), 2);
    BOOST_CHECK_EQUAL(result(0, 3)(0, 0), 0);
    BOOST_CHECK_EQUAL(result(0, 4)(0, 0), 10);
    BOOST_CHECK_EQUAL(result(0, 5)(0, 0), 4);

    BOOST_CHECK_EQUAL(result(1, 0)(0, 0), 6);
    BOOST_CHECK_EQUAL(result(1, 1)(0, 0), 7);
    BOOST_CHECK_EQUAL(result(1, 2)(0, 0), 3);
    BOOST_CHECK_EQUAL(result(1, 3)(0, 0), 12);
    BOOST_CHECK_EQUAL(result(1, 4)(0, 0), 14);
    BOOST_CHECK_EQUAL(result(1, 5)(0, 0), 6);

    BOOST_CHECK_EQUAL(result(2, 0)(0, 0), 0);
    BOOST_CHECK_EQUAL(result(2, 1)(0, 0), 15);
    BOOST_CHECK_EQUAL(result(2, 2)(0, 0), 6);
    BOOST_CHECK_EQUAL(result(2, 3)(0, 0), 0);
    BOOST_CHECK_EQUAL(result(2, 4)(0, 0), 20);
    BOOST_CHECK_EQUAL(result(2, 5)(0, 0), 8);


    BOOST_CHECK_EQUAL(result(3, 0)(0, 0), 18);
    BOOST_CHECK_EQUAL(result(3, 1)(0, 0), 21);
    BOOST_CHECK_EQUAL(result(3, 2)(0, 0), 9);
    BOOST_CHECK_EQUAL(result(3, 3)(0, 0), 24);
    BOOST_CHECK_EQUAL(result(3, 4)(0, 0), 28);
    BOOST_CHECK_EQUAL(result(3, 5)(0, 0), 12);

    BOOST_CHECK_EQUAL(result(4, 0)(0, 0), 0);
    BOOST_CHECK_EQUAL(result(4, 1)(0, 0), 5);
    BOOST_CHECK_EQUAL(result(4, 2)(0, 0), 2);
    BOOST_CHECK_EQUAL(result(4, 3)(0, 0), 0);
    BOOST_CHECK_EQUAL(result(4, 4)(0, 0), 0);
    BOOST_CHECK_EQUAL(result(4, 5)(0, 0), 0);



    BOOST_CHECK_EQUAL(result(5, 0)(0, 0), 6);
    BOOST_CHECK_EQUAL(result(5, 1)(0, 0), 7);
    BOOST_CHECK_EQUAL(result(5, 2)(0, 0), 3);
    BOOST_CHECK_EQUAL(result(5, 3)(0, 0), 0);
    BOOST_CHECK_EQUAL(result(5, 4)(0, 0), 0);
    BOOST_CHECK_EQUAL(result(5, 5)(0, 0), 0);
}

BOOST_AUTO_TEST_CASE(MatrixTestBlock) {
    // Correct initialization of BlockMatrix
    size_t blockRows = 2; // Number of rows in each block
    size_t blockCols = 2; // Number of columns in each block
    BlockMatrix<double, DenseMatrix> block1(2, 2, blockRows, blockCols); // 2x2 blocks of 2x2 size
    BlockMatrix<double, DenseMatrix> block2(2, 2, blockRows, blockCols); // 2x2 blocks of 2x2 size

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

    // ��������
    BlockMatrix<double, DenseMatrix>* resultAdd = static_cast<BlockMatrix<double, DenseMatrix>*>(block1 + block2);
    BOOST_CHECK_EQUAL((*resultAdd)(0, 0)(0, 0), 6);
    BOOST_CHECK_EQUAL((*resultAdd)(0, 0)(0, 1), 8);
    BOOST_CHECK_EQUAL((*resultAdd)(0, 1)(0, 0), 10);
    BOOST_CHECK_EQUAL((*resultAdd)(0, 1)(0, 1), 12);

    // ���������
    BlockMatrix<double, DenseMatrix>* resultSub = static_cast<BlockMatrix<double, DenseMatrix>*>(block1 - block2);
    BOOST_CHECK_EQUAL((*resultSub)(0, 0)(0, 0), 4);
    BOOST_CHECK_EQUAL((*resultSub)(0, 0)(0, 1), 4);
    BOOST_CHECK_EQUAL((*resultSub)(0, 1)(0, 0), 4);
    BOOST_CHECK_EQUAL((*resultSub)(0, 1)(0, 1), 4);

    delete resultAdd;
    delete resultSub;
}

BOOST_AUTO_TEST_SUITE_END()
