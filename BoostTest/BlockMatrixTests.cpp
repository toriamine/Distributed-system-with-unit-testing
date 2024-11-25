#include <boost/test/unit_test.hpp>
#include "../Lab/BlockMatrix.h"
#include "../Lab/BlockMatrix.cpp"

BOOST_AUTO_TEST_SUITE(BlockMatrixTests) // ������ ������ ������ ��� ������� ������

// ������������ ������������ � ������� � ��������� ������� �������
BOOST_AUTO_TEST_CASE(BlockMatrixTestConstructorAndAccess) {
    BlockMatrix<double, DenseMatrix> blockMatrix(2, 2, 2, 2); // ������� ������� ������� �� 2x2 ������, ������ �������� 2x2

    BlockMatrix<int, DenseMatrix> a(2, 2, 2, 2);

    // ������� ������� ������� 2x2 ������, ������ �� ������� 2x2 ��������
        // ��������� �������� � �����
    // ���� (0, 0):
    // [ 1.0, 2.0 ]
    // [ 3.0, 4.0 ]

    a.setBlock(0, 0, new DenseMatrix<int>(2, 2));
    a(0, 0) = 1; a(0, 1) = 2;
    a(1, 0) = 3; a(1, 1) = 4;

    // ���� (0, 1):
    // [ 5.0, 6.0 ]
    // [ 7.0, 8.0 ]

    a.setBlock(0, 1, new DenseMatrix<int>(2, 2));
    a(0, 2) = 5; a(0, 3) = 6;
    a(1, 2) = 7; a(1, 3) = 8;


    // ���� (1, 0):
    // [ 9.0, 10.0 ]
    // [ 11.0, 12.0 ]
    a.setBlock(1, 0, new DenseMatrix<int>(2, 2));
    a(2, 0) = 9; a(2, 1) = 10;
    a(3, 0) = 11; a(3, 1) = 12;

    // ���� (1, 1):
    // [ 13.0, 14.0 ]
    // [ 15.0, 16.0 ]
    a.setBlock(1, 1, new DenseMatrix<int>(2, 2));
    a(2, 2) = 13; a(2, 3) = 14;
    a(3, 2) = 15; a(3, 3) = 16;


    // �������� ������� � ������ � �� ���������
    BOOST_CHECK_EQUAL(a(0, 0), 1);   //���� ������� �������� ������ �������
    BOOST_CHECK_EQUAL(a(0, 3), 6);   // ���� ���������� �������� ������ ������
    BOOST_CHECK_EQUAL(a(1, 2), 7);   // ���� �������� �� ������� �����
    BOOST_CHECK_EQUAL(a(2, 1), 10);  // ���� �������� ������� ���� �������� �����
    BOOST_CHECK_EQUAL(a(3, 3), 16);  // ���� ���������� ��������
}

BOOST_AUTO_TEST_CASE(BlockMatrixTestAddition) {
    BlockMatrix<double, DenseMatrix> a(2, 2, 2, 2); // ������� ������ ������� ������� 2x2
    BlockMatrix<double, DenseMatrix> b(2, 2, 2, 2); // ������� ������ ������� ������� 2x2

    // ���������� ������� A
    a.setBlock(0, 0, new DenseMatrix<double>(2, 2));
    a(0, 0) = 1; a(0, 1) = 2; // ��������� ������ ����
    a(1, 0) = 3; a(1, 1) = 4;

    a.setBlock(0, 1, new DenseMatrix<double>(2, 2));
    a(0, 0 + 2) = 5; a(0, 1 + 2) = 6; // ��������� ������ ���� (������ ���� ������ ������)
    a(1, 0 + 2) = 7; a(1, 1 + 2) = 8;

    a.setBlock(1, 0, new DenseMatrix<double>(2, 2));
    a(0 + 2, 0) = 9; a(0 + 2, 1) = 10; // ��������� ������ ���� (������ ���� ������ ������)
    a(1 + 2, 0) = 11; a(1 + 2, 1) = 12;

    a.setBlock(1, 1, new DenseMatrix<double>(2, 2));
    a(0 + 2, 0 + 2) = 13; a(0 + 2, 1 + 2) = 14; // ��������� ��������� ���� (������ ���� ������ ������)
    a(1 + 2, 0 + 2) = 15; a(1 + 2, 1 + 2) = 16;

    // ���������� ������� B
    b.setBlock(0, 0, new DenseMatrix<double>(2, 2));
    b(0, 0) = 1; b(0, 1) = 1; // ��������� ������ ����
    b(1, 0) = 1; b(1, 1) = 1;

    b.setBlock(0, 1, new DenseMatrix<double>(2, 2));
    b(0, 0 + 2) = 2; b(0, 1 + 2) = 2; // ��������� ������ ���� (������ ���� ������ ������)
    b(1, 0 + 2) = 2; b(1, 1 + 2) = 2;

    b.setBlock(1, 0, new DenseMatrix<double>(2, 2));
    b(0 + 2, 0) = 3; b(0 + 2, 1) = 3; // ��������� ������ ���� (������ ���� ������ ������)
    b(1 + 2, 0) = 3; b(1 + 2, 1) = 3;

    b.setBlock(1, 1, new DenseMatrix<double>(2, 2));
    b(0 + 2, 0 + 2) = 4; b(0 + 2, 1 + 2) = 4; // ��������� ��������� ���� (������ ���� ������ ������)
    b(1 + 2, 0 + 2) = 4; b(1 + 2, 1 + 2) = 4;

    // ��������� �������� ��������
    BlockMatrix<double, DenseMatrix> c = a + b;
    std::cout << "\nA + B:\n";
    c.Print();

    // ��������� ��������� ��������
    BOOST_CHECK_EQUAL(c(0, 0), 2);   // 1 + 1
    BOOST_CHECK_EQUAL(c(0, 1), 3);   // 2 + 1
    BOOST_CHECK_EQUAL(c(1, 0), 4);   // 3 + 1
    BOOST_CHECK_EQUAL(c(1, 1), 5);   // 4 + 1

    BOOST_CHECK_EQUAL(c(0, 2), 7);   // 5 + 2
    BOOST_CHECK_EQUAL(c(0, 3), 8);   // 6 + 2
    BOOST_CHECK_EQUAL(c(1, 2), 9);   // 7 + 2
    BOOST_CHECK_EQUAL(c(1, 3), 10);  // 8 + 2

    BOOST_CHECK_EQUAL(c(2, 0), 12);  // 9 + 3
    BOOST_CHECK_EQUAL(c(2, 1), 13);  // 10 + 3
    BOOST_CHECK_EQUAL(c(3, 0), 14);  // 11 + 3
    BOOST_CHECK_EQUAL(c(3, 1), 15);  // 12 + 3

    BOOST_CHECK_EQUAL(c(2, 2), 17);  // 13 + 4
    BOOST_CHECK_EQUAL(c(2, 3), 18);  // 14 + 4
    BOOST_CHECK_EQUAL(c(3, 2), 19);  // 15 + 4
    BOOST_CHECK_EQUAL(c(3, 3), 20);  // 16 + 4
}

BOOST_AUTO_TEST_CASE(BlockMatrixTestSubtraction) {
    BlockMatrix<double, DenseMatrix> a(2, 2, 2, 2); // ������� ������ ������� ������� 2x2
    BlockMatrix<double, DenseMatrix> b(2, 2, 2, 2); // ������� ������ ������� ������� 2x2

    // ���������� ������� A
    a.setBlock(0, 0, new DenseMatrix<double>(2, 2));
    a(0, 0) = 10; a(0, 1) = 12;
    a(1, 0) = 14; a(1, 1) = 16;

    a.setBlock(0, 1, new DenseMatrix<double>(2, 2));
    a(0, 2) = 18; a(0, 3) = 20;
    a(1, 2) = 22; a(1, 3) = 24;

    a.setBlock(1, 0, new DenseMatrix<double>(2, 2));
    a(2, 0) = 26; a(2, 1) = 28;
    a(3, 0) = 30; a(3, 1) = 32;

    a.setBlock(1, 1, new DenseMatrix<double>(2, 2));
    a(2, 2) = 34; a(2, 3) = 36;
    a(3, 2) = 38; a(3, 3) = 40;

    // ���������� ������� B
    b.setBlock(0, 0, new DenseMatrix<double>(2, 2));
    b(0, 0) = 5; b(0, 1) = 6;
    b(1, 0) = 7; b(1, 1) = 8;

    b.setBlock(0, 1, new DenseMatrix<double>(2, 2));
    b(0, 2) = 9; b(0, 3) = 10;
    b(1, 2) = 11; b(1, 3) = 12;

    b.setBlock(1, 0, new DenseMatrix<double>(2, 2));
    b(2, 0) = 13; b(2, 1) = 14;
    b(3, 0) = 15; b(3, 1) = 16;

    b.setBlock(1, 1, new DenseMatrix<double>(2, 2));
    b(2, 2) = 17; b(2, 3) = 18;
    b(3, 2) = 19; b(3, 3) = 20;

    // ��������� ���� ������� ������
    BlockMatrix<double, DenseMatrix> result = a - b;

    // �������� ����������� ���������
    BOOST_CHECK(result(0, 0) == 5);   // 10 - 5
    BOOST_CHECK(result(0, 1) == 6);   // 12 - 6
    BOOST_CHECK(result(1, 0) == 7);   // 14 - 7
    BOOST_CHECK(result(1, 1) == 8);   // 16 - 8

    BOOST_CHECK(result(0, 2) == 9);   // 18 - 9
    BOOST_CHECK(result(0, 3) == 10);  // 20 - 10
    BOOST_CHECK(result(1, 2) == 11);  // 22 - 11
    BOOST_CHECK(result(1, 3) == 12);  // 24 - 12

    BOOST_CHECK(result(2, 0) == 13);  // 26 - 13
    BOOST_CHECK(result(2, 1) == 14);  // 28 - 14
    BOOST_CHECK(result(3, 0) == 15);  // 30 - 15
    BOOST_CHECK(result(3, 1) == 16);  // 32 - 16

    BOOST_CHECK(result(2, 2) == 17);  // 34 - 17
    BOOST_CHECK(result(2, 3) == 18);  // 36 - 18
    BOOST_CHECK(result(3, 2) == 19);  // 38 - 19
    BOOST_CHECK(result(3, 3) == 20);  // 40 - 20
}

//BOOST_AUTO_TEST_CASE(BlockMatrixTestMultiplication) {
//    BlockMatrix<double, DenseMatrix> a(2, 2, 2, 2); // ������� ������ ������� ������� 2x2
//    BlockMatrix<double, DenseMatrix> b(2, 2, 2, 2); // ������� ������ ������� ������� 2x2
//
//    // ���������� ������� A
//    a.setBlock(0, 0, new DenseMatrix<double>(2, 2));
//    a(0, 0) = 1; a(0, 1) = 2; // ������ ����
//    a(1, 0) = 3; a(1, 1) = 4;
//
//    a.setBlock(0, 1, new DenseMatrix<double>(2, 2));
//    a(0, 2) = 5; a(0, 3) = 6; // ������ ����
//    a(1, 2) = 7; a(1, 3) = 8;
//
//    a.setBlock(1, 0, new DenseMatrix<double>(2, 2));
//    a(2, 0) = 9; a(2, 1) = 10; // ������ ����
//    a(3, 0) = 11; a(3, 1) = 12;
//
//    a.setBlock(1, 1, new DenseMatrix<double>(2, 2));
//    a(2, 2) = 13; a(2, 3) = 14; // ��������� ����
//    a(3, 2) = 15; a(3, 3) = 16;
//
//    std::cout << "\n������� a: \n";
//    a.Print();
//    
//
//    // ���������� ������� B
//    b.setBlock(0, 0, new DenseMatrix<double>(2, 2));
//    b(0, 0) = 1; b(0, 1) = 2; // ������ ����
//    b(1, 0) = 3; b(1, 1) = 4;
//
//    b.setBlock(0, 1, new DenseMatrix<double>(2, 2));
//    b(0, 2) = 5; b(0, 3) = 6; // ������ ����
//    b(1, 2) = 7; b(1, 3) = 8;
//
//    b.setBlock(1, 0, new DenseMatrix<double>(2, 2));
//    b(2, 0) = 9; b(2, 1) = 10; // ������ ����
//    b(3, 0) = 11; b(3, 1) = 12;
//
//    b.setBlock(1, 1, new DenseMatrix<double>(2, 2));
//    b(2, 2) = 13; b(2, 3) = 14; // ��������� ����
//    b(3, 2) = 15; b(3, 3) = 16;
//
//    std::cout << "\n������� b: \n";
//    b.Print();
//
//    // ��������� ���� ������� ������
//    BlockMatrix<double, DenseMatrix> result = a * b;
//
//    std::cout << "\nResult: \n";
//    result.Print();
//
//    // �������� ����������� ���������
//    BOOST_CHECK_EQUAL(result(0, 0), 118);   // (1*1 + 2*3 + 5*9 + 6*11) = 70
//    BOOST_CHECK_EQUAL(result(0, 1), 132);  // (1*2 + 2*4 + 5*10 + 6*12) = 158
//    BOOST_CHECK_EQUAL(result(0, 2), 174);   // (5*1 + 6*3 + 7*9 + 8*11) = 74
//    BOOST_CHECK_EQUAL(result(0, 3), 188);  // (5*2 + 6*4 + 7*10 + 8*12) = 178
//
//    BOOST_CHECK_EQUAL(result(1, 0), 166);  // (3*1 + 4*3 + 7*9 + 8*11) = 158
//    BOOST_CHECK_EQUAL(result(1, 1), 188);  // (3*2 + 4*4 + 7*10 + 8*12) = 382
//    BOOST_CHECK_EQUAL(result(1, 2), 254);  // (7*1 + 8*3) = 170
//    BOOST_CHECK_EQUAL(result(1, 3), 276);  // (7*2 + 8*4) = 390
//
//    BOOST_CHECK_EQUAL(result(2, 0), 310);  // (9*1 + 10*3 + 11*9 + 12*11) = 314
//    BOOST_CHECK_EQUAL(result(2, 1), 356);  // (9*2 + 10*4 + 11*10 + 12*12) = 782
//    BOOST_CHECK_EQUAL(result(2, 2), 494);  // (11*1 + 12*3) = 388
//    BOOST_CHECK_EQUAL(result(2, 3), 540);  // (11*2 + 12*4) = 928
//}

// ������������ �������� ������������� ������
BOOST_AUTO_TEST_CASE(BlockMatrixTestIncompatibleAddition) {
    BlockMatrix<double, DenseMatrix> a(2, 2, 2, 2); // ������� ������ ������� ������� 2x2
    BlockMatrix<double, DenseMatrix> b(3, 2, 2, 2); // ������� ������ ������� ������� 3x2 (������������� ������)

    // ���������, ��� �������� ���� ������ �������� ����������
    BOOST_CHECK_THROW(a + b, std::runtime_error);
}

// ������������ ��������� ������������� ������
BOOST_AUTO_TEST_CASE(BlockMatrixTestIncompatibleMultiplication) {
    BlockMatrix<double, DenseMatrix> a(2, 2, 2, 2); // ������� ������ ������� ������� 2x2
    BlockMatrix<double, DenseMatrix> b(3, 2, 2, 2); // ������� ������ ������� ������� 3x2 (������������� �������)

    // ���������, ��� ��������� ���� ������ �������� ����������
    BOOST_CHECK_THROW(a - b, std::runtime_error);
}

//// ������������ �������� ������� ������ � ���������� ���� int
//BOOST_AUTO_TEST_CASE(BlockMatrixTestMatrixAdditionTest) {
//    BlockMatrix<int, DenseMatrix> matrixA(2, 2, 1, 1); // ������� ������� ������� 2x2 � ������� 1x1
//    // ���������� ������ ������� A
//    // ���� (0, 0):
//    // [ 1 ]
//    matrixA(0, 0)(0, 0) = 1;
//    // ���� (0, 1):
//    // [ 2 ]
//    matrixA(0, 1)(0, 0) = 2;
//    // ���� (1, 0):
//    // [ 3 ]
//    matrixA(1, 0)(0, 0) = 3;
//    // ���� (1, 1):
//    // [ 4 ]
//    matrixA(1, 1)(0, 0) = 4;
//
//    BlockMatrix<int, DenseMatrix> matrixB(2, 2, 1, 1); // ������� ������� ������� 2x2 � ������� 1x1
//    // ���������� ������ ������� B
//    // ���� (0, 0):
//    // [ 5 ]
//    matrixB(0, 0)(0, 0) = 5;
//    // ���� (0, 1):
//    // [ 6 ]
//    matrixB(0, 1)(0, 0) = 6;
//    // ���� (1, 0):
//    // [ 7 ]
//    matrixB(1, 0)(0, 0) = 7;
//    // ���� (1, 1):
//    // [ 8 ]
//    matrixB(1, 1)(0, 0) = 8;
//
//    BlockMatrix<int, DenseMatrix>* result = static_cast<BlockMatrix<int, DenseMatrix>*>(matrixA + matrixB); // �������� ���� ������� ������
//
//    // �������� ����������� ��������
//    // ��������� ���������:
//    // [ 1 + 5, 2 + 6 ] => [ 6, 8 ]
//    // [ 3 + 7, 4 + 8 ] => [ 10, 12 ]
//    BOOST_CHECK_EQUAL((*result)(0, 0)(0, 0), 6);  // �������� ����� ������� ��������
//    BOOST_CHECK_EQUAL((*result)(0, 1)(0, 0), 8);  // �������� ����� ������� ��������
//    BOOST_CHECK_EQUAL((*result)(1, 0)(0, 0), 10); // �������� ����� �������� ��������
//    BOOST_CHECK_EQUAL((*result)(1, 1)(0, 0), 12); // �������� ����� ���������� ��������
//
//    delete result;
//}

BOOST_AUTO_TEST_CASE(BlockMatrixTestKroneckerProduct) {
    // ������� ������� ������� 1x1 � ������� �������� 2x2
    BlockMatrix<int, DenseMatrix> A(1, 1, 2, 2); // 1 ���� �� 2 ������, 1 ���� �� 2 �������
    BlockMatrix<int, DenseMatrix> B(1, 1, 2, 2); // 1 ���� �� 2 ������, 1 ���� �� 2 �������

    // ���������� ������� A
    A.setBlock(0, 0, new DenseMatrix<int>(2, 2)); // ���� A[0][0]
    A(0, 0) = 1; A(0, 1) = 2; // ��������� ������ ����
    A(1, 0) = 3; A(1, 1) = 4;

    // ���������� ������� B
    B.setBlock(0, 0, new DenseMatrix<int>(2, 2)); // ���� B[0][0]
    B(0, 0) = 5; B(0, 1) = 6; // ��������� ������ ����
    B(1, 0) = 7; B(1, 1) = 8;

    // ��������� ������������ ���������
    BlockMatrix<int, DenseMatrix> result = A.kroneckerProduct(B);

    // ��������� ������� C ����� ������������ ���������
    // C = A(0,0) * B
    // �������������� ������� ����� 4x4 (2*2 � 2*2):
    //    | 1*5  1*6  2*5  2*6 |
    //    | 1*7  1*8  2*7  2*8 |
    //    | 3*5  3*6  4*5  4*6 |
    //    | 3*7  3*8  4*7  4*8 |
    int expectedResult[4][4] = {
        {  5,  6, 10, 12 }, // 1*5, 1*6, 2*5, 2*6
        {  7,  8, 14, 16 }, // 1*7, 1*8, 2*7, 2*8
        { 15, 18, 20, 24 }, // 3*5, 3*6, 4*5, 4*6
        { 21, 24, 28, 32 }  // 3*7, 3*8, 4*7, 4*8
    };

    // �������� ���������� �� ������������ ����������
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            BOOST_CHECK_EQUAL(result(i, j), expectedResult[i][j]);
        }
    }
}
//BOOST_AUTO_TEST_CASE(MatrixTestBlock) {
//    // Correct initialization of BlockMatrix
//    size_t blockRows = 2; // Number of rows in each block
//    size_t blockCols = 2; // Number of columns in each block
//    BlockMatrix<double, DenseMatrix> block1(2, 2, blockRows, blockCols); // 2x2 blocks of 2x2 size
//    BlockMatrix<double, DenseMatrix> block2(2, 2, blockRows, blockCols); // 2x2 blocks of 2x2 size
//
//    // Set values for the blocks in block1
//    block1(0, 0)(0, 0) = 1;
//    block1(0, 0)(0, 1) = 2;
//    block1(0, 1)(0, 0) = 3;
//    block1(0, 1)(0, 1) = 4;
//
//    // Set values for the blocks in block2
//    block2(0, 0)(0, 0) = 5;
//    block2(0, 0)(0, 1) = 6;
//    block2(0, 1)(0, 0) = 7;
//    block2(0, 1)(0, 1) = 8;
//
//    // ��������
//    BlockMatrix<double, DenseMatrix>* resultAdd = static_cast<BlockMatrix<double, DenseMatrix>*>(block1 + block2);
//    BOOST_CHECK_EQUAL((*resultAdd)(0, 0)(0, 0), 6);
//    BOOST_CHECK_EQUAL((*resultAdd)(0, 0)(0, 1), 8);
//    BOOST_CHECK_EQUAL((*resultAdd)(0, 1)(0, 0), 10);
//    BOOST_CHECK_EQUAL((*resultAdd)(0, 1)(0, 1), 12);
//
//    // ���������
//    BlockMatrix<double, DenseMatrix>* resultSub = static_cast<BlockMatrix<double, DenseMatrix>*>(block1 - block2);
//    BOOST_CHECK_EQUAL((*resultSub)(0, 0)(0, 0), 4);
//    BOOST_CHECK_EQUAL((*resultSub)(0, 0)(0, 1), 4);
//    BOOST_CHECK_EQUAL((*resultSub)(0, 1)(0, 0), 4);
//    BOOST_CHECK_EQUAL((*resultSub)(0, 1)(0, 1), 4);
//
//    delete resultAdd;
//    delete resultSub;
//}


BOOST_AUTO_TEST_CASE(BlockMatrixTestDiagonalConstructorAndAccess) {
    BlockMatrix<double, DiagonalMatrix> blockMatrix(2, 2, 2, 2); // ������� ������� ������� �� 2x2 ������, ������ �������� 2x2

    // ������� ������� ������� 2x2 ������, ������ �� ������� 2x2 ��������
    // ��������� �������� � �����
    // ���� (0, 0):
    // [ 1.0, 0.0 ]
    // [ 0.0, 2.0 ]
    blockMatrix.setBlock(0, 0, new DiagonalMatrix<double>({ 1, 2 }));

    // ���� (0, 1):
    // [ 3.0, 0.0 ]
    // [ 0.0, 4.0 ]
    blockMatrix.setBlock(0, 1, new DiagonalMatrix<double>({ 3, 4 }));

    // ���� (1, 0):
    // [ 5.0, 0.0 ]
    // [ 0.0, 6.0 ]
    blockMatrix.setBlock(1, 0, new DiagonalMatrix<double>({ 5, 6 }));

    // ���� (1, 1):
    // [ 7.0, 0.0 ]
    // [ 0.0, 8.0 ]
    blockMatrix.setBlock(1, 1, new DiagonalMatrix<double>({ 7, 8 }));

    // �������� ������� � ������ � �� ���������
    BOOST_CHECK_EQUAL(blockMatrix(0, 0), 1);   // ��������� ������ ������� ������� �����
    BOOST_CHECK_EQUAL(blockMatrix(1, 1), 2);   // ��������� ������ ������� ������� �����
    BOOST_CHECK_EQUAL(blockMatrix(0, 2), 3);   // ��������� ������ ������� ������� �����
    BOOST_CHECK_EQUAL(blockMatrix(1, 3), 4);   // ��������� ������ ������� ������� �����
    BOOST_CHECK_EQUAL(blockMatrix(2, 0), 5);   // ��������� ������ ������� �������� �����
    BOOST_CHECK_EQUAL(blockMatrix(3, 1), 6);   // ��������� ������ ������� �������� �����
    BOOST_CHECK_EQUAL(blockMatrix(2, 2), 7);   // ��������� ������ ������� ���������� �����
    BOOST_CHECK_EQUAL(blockMatrix(3, 3), 8);   // ��������� ������ ������� ���������� �����
}

BOOST_AUTO_TEST_CASE(BlockMatrixTestAdditionDiagonal) {
    BlockMatrix<double, DiagonalMatrix> a(2, 2, 2, 2); // ������� ������ ������� ������� 2x2
    BlockMatrix<double, DiagonalMatrix> b(2, 2, 2, 2); // ������� ������ ������� ������� 2x2

    // ���������� ������� A
    a.setBlock(0, 0, new DiagonalMatrix<double>({ 1, 2 })); // ���� (0, 0)
    a.setBlock(0, 1, new DiagonalMatrix<double>({ 3, 4 })); // ���� (0, 1)
    a.setBlock(1, 0, new DiagonalMatrix<double>({ 5, 6 })); // ���� (1, 0)
    a.setBlock(1, 1, new DiagonalMatrix<double>({ 7, 8 })); // ���� (1, 1)

    // ���������� ������� B
    b.setBlock(0, 0, new DiagonalMatrix<double>({ 1, 1 })); // ���� (0, 0)
    b.setBlock(0, 1, new DiagonalMatrix<double>({ 2, 2 })); // ���� (0, 1)
    b.setBlock(1, 0, new DiagonalMatrix<double>({ 3, 3 })); // ���� (1, 0)
    b.setBlock(1, 1, new DiagonalMatrix<double>({ 4, 4 })); // ���� (1, 1)

    // ��������� �������� ��������
    BlockMatrix<double, DiagonalMatrix> c = a + b;

    // ��������� ��������� ��������
    BOOST_CHECK_EQUAL(c(0, 0), 2);   // 1 + 1
    BOOST_CHECK_EQUAL(c(1, 1), 3);   // 2 + 1
    BOOST_CHECK_EQUAL(c(0, 2), 5);   // 3 + 2
    BOOST_CHECK_EQUAL(c(1, 3), 6);   // 4 + 2
    BOOST_CHECK_EQUAL(c(2, 0), 8);   // 5 + 3
    BOOST_CHECK_EQUAL(c(3, 1), 9);   // 6 + 3
    BOOST_CHECK_EQUAL(c(2, 2), 11);  // 7 + 4
    BOOST_CHECK_EQUAL(c(3, 3), 12);  // 8 + 4
}

BOOST_AUTO_TEST_CASE(IncompatibleBlockMatrixAdditionTest) {
    BlockMatrix<int, DiagonalMatrix> blockMatrixA(2, 2, 2, 2);
    blockMatrixA.setBlock(0, 0, new DiagonalMatrix<int>({ 1, 4 }));

    BlockMatrix<int, DiagonalMatrix> blockMatrixB(3, 3, 2, 2); // ������������� ������� (3x3)

    BOOST_CHECK_THROW(blockMatrixA + blockMatrixB, std::runtime_error);
}

BOOST_AUTO_TEST_CASE(IncompatibleBlockMatrixMultiplicationTest) {
    BlockMatrix<int, DiagonalMatrix> blockMatrixA(3, 2, 2, 2); // 3 ������, 2 �������
    BlockMatrix<int, DiagonalMatrix> blockMatrixB(2, 3, 2, 2); // 2 ������, 3 �������

    BOOST_CHECK_THROW(blockMatrixA - blockMatrixB, std::runtime_error); // ������� ����������
}

BOOST_AUTO_TEST_CASE(IncompatibleBlockMatrixAdditionTestBlock) {
    BlockMatrix<int, DiagonalMatrix> blockMatrixA(2, 2, 2, 2);
    blockMatrixA.setBlock(0, 0, new DiagonalMatrix<int>({ 1, 4 }));

    BlockMatrix<int, DiagonalMatrix> blockMatrixB(2, 2, 2, 1); // ������ ���������� ������

    BOOST_CHECK_THROW(blockMatrixA + blockMatrixB, std::runtime_error);
}

BOOST_AUTO_TEST_CASE(BlockMatrixTestSubtractionDiagonal) {
    BlockMatrix<double, DiagonalMatrix> a(2, 2, 2, 2); // ������� ������ ������� ������� 2x2
    BlockMatrix<double, DiagonalMatrix> b(2, 2, 2, 2); // ������� ������ ������� ������� 2x2

    // ���������� ������� A
    a.setBlock(0, 0, new DiagonalMatrix<double>({ 5, 6 })); // ���� (0, 0)
    a.setBlock(0, 1, new DiagonalMatrix<double>({ 7, 8 })); // ���� (0, 1)
    a.setBlock(1, 0, new DiagonalMatrix<double>({ 9, 10 })); // ���� (1, 0)
    a.setBlock(1, 1, new DiagonalMatrix<double>({ 11, 12 })); // ���� (1, 1)

    // ���������� ������� B
    b.setBlock(0, 0, new DiagonalMatrix<double>({ 1, 1 })); // ���� (0, 0)
    b.setBlock(0, 1, new DiagonalMatrix<double>({ 2, 2 })); // ���� (0, 1)
    b.setBlock(1, 0, new DiagonalMatrix<double>({ 3, 3 })); // ���� (1, 0)
    b.setBlock(1, 1, new DiagonalMatrix<double>({ 4, 4 })); // ���� (1, 1)

    // ��������� �������� ���������
    BlockMatrix<double, DiagonalMatrix> c = a - b;

    // ��������� ��������� ���������
    BOOST_CHECK_EQUAL(c(0, 0), 4);   // 5 - 1
    BOOST_CHECK_EQUAL(c(1, 1), 5);   // 6 - 1
    BOOST_CHECK_EQUAL(c(0, 2), 5);   // 7 - 2
    BOOST_CHECK_EQUAL(c(1, 3), 6);   // 8 - 2
    BOOST_CHECK_EQUAL(c(2, 0), 6);   // 9 - 3
    BOOST_CHECK_EQUAL(c(3, 1), 7);   // 10 - 3
    BOOST_CHECK_EQUAL(c(2, 2), 7);   // 11 - 4
    BOOST_CHECK_EQUAL(c(3, 3), 8);   // 12 - 4
}

//BOOST_AUTO_TEST_CASE(BlockMatrixTestMultiplicationDiagonal) {
//    BlockMatrix<double, DiagonalMatrix> a(2, 2, 2, 2); // ������� ������ ������� ������� 2x2
//    BlockMatrix<double, DiagonalMatrix> b(2, 2, 2, 2); // ������� ������ ������� ������� 2x2
//
//    // ���������� ������� A
//    a.setBlock(0, 0, new DiagonalMatrix<double>({ 1, 2 })); // ���� (0, 0)
//    a.setBlock(0, 1, new DiagonalMatrix<double>({ 3, 4 })); // ���� (0, 1)
//    a.setBlock(1, 0, new DiagonalMatrix<double>({ 5, 6 })); // ���� (1, 0)
//    a.setBlock(1, 1, new DiagonalMatrix<double>({ 7, 8 })); // ���� (1, 1)
//
//    // ���������� ������� B
//    b.setBlock(0, 0, new DiagonalMatrix<double>({ 1, 0 })); // ���� (0, 0)
//    b.setBlock(0, 1, new DiagonalMatrix<double>({ 0, 2 })); // ���� (0, 1)
//    b.setBlock(1, 0, new DiagonalMatrix<double>({ 0, 3 })); // ���� (1, 0)
//    b.setBlock(1, 1, new DiagonalMatrix<double>({ 4, 0 })); // ���� (1, 1)
//
//    // ��������� �������� ���������
//    BlockMatrix<double, DiagonalMatrix> c = a * b;
//
//    // ��������� ��������� ���������
//    BOOST_CHECK_EQUAL(c(0, 0), 1);   // 1 * 1
//    BOOST_CHECK_EQUAL(c(0, 2), 6);   // 2 * 3
//    BOOST_CHECK_EQUAL(c(1, 0), 0);   // 0
//    BOOST_CHECK_EQUAL(c(1, 1), 28);  // 4 * 7
//    BOOST_CHECK_EQUAL(c(2, 0), 0);   // 0
//    BOOST_CHECK_EQUAL(c(3, 1), 0);   // 0
//}

BOOST_AUTO_TEST_SUITE_END()