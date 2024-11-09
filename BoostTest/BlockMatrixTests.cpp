#include <boost/test/unit_test.hpp>
#include "../Lab/BlockMatrix.h"

BOOST_AUTO_TEST_SUITE(BlockMatrixTests) // Начало набора тестов для блочных матриц

// Тестирование конструктора и доступа к элементам блочной матрицы
BOOST_AUTO_TEST_CASE(BlockMatrixTestConstructorAndAccess) {
    BlockMatrix<double> blockMatrix(2, 2, 2, 2); // Создаем блочную матрицу из 2x2 блоков, каждый размером 2x2

    // Установим значения в блоки
    // Блок (0, 0):
    // [ 1.0, 2.0 ]
    // [ 3.0, 4.0 ]
    blockMatrix(0, 0)(0, 0) = 1.0;
    blockMatrix(0, 0)(0, 1) = 2.0;
    blockMatrix(0, 0)(1, 0) = 3.0;
    blockMatrix(0, 0)(1, 1) = 4.0;

    // Блок (0, 1):
    // [ 5.0, 6.0 ]
    // [ 7.0, 8.0 ]
    blockMatrix(0, 1)(0, 0) = 5.0;
    blockMatrix(0, 1)(0, 1) = 6.0;
    blockMatrix(0, 1)(1, 0) = 7.0;
    blockMatrix(0, 1)(1, 1) = 8.0;

    // Блок (1, 0):
    // [ 9.0, 10.0 ]
    // [ 11.0, 12.0 ]
    blockMatrix(1, 0)(0, 0) = 9.0;
    blockMatrix(1, 0)(0, 1) = 10.0;
    blockMatrix(1, 0)(1, 0) = 11.0;
    blockMatrix(1, 0)(1, 1) = 12.0;

    // Блок (1, 1):
    // [ 13.0, 14.0 ]
    // [ 15.0, 16.0 ]
    blockMatrix(1, 1)(0, 0) = 13.0;
    blockMatrix(1, 1)(0, 1) = 14.0;
    blockMatrix(1, 1)(1, 0) = 15.0;
    blockMatrix(1, 1)(1, 1) = 16.0;

    // Проверка доступа к блокам и их элементам
    BOOST_CHECK_EQUAL(blockMatrix(0, 0)(0, 0), 1.0); // Проверка первого элемента первого блока
    BOOST_CHECK_EQUAL(blockMatrix(0, 1)(1, 0), 7.0); // Проверка второго элемента второго блока
    BOOST_CHECK_EQUAL(blockMatrix(1, 1)(0, 1), 14.0); // Проверка второго элемента четвертого блока
}

BOOST_AUTO_TEST_CASE(BlockMatrixTestAddition) {
    BlockMatrix<double> a(2, 2, 2, 2); // Создаем первую блочную матрицу 2x2
    BlockMatrix<double> b(2, 2, 2, 2); // Создаем вторую блочную матрицу 2x2

    // Заполнение блоков матрицы a
    // Блок (0, 0):
    // [ 1.0, 2.0 ]
    // [ 3.0, 4.0 ]
    a(0, 0)(0, 0) = 1.0;
    a(0, 0)(0, 1) = 2.0;
    a(0, 0)(1, 0) = 3.0;
    a(0, 0)(1, 1) = 4.0;

    // Заполнение блоков матрицы b
    // Блок (0, 0):
    // [ 5.0, 6.0 ]
    // [ 7.0, 8.0 ]
    b(0, 0)(0, 0) = 5.0;
    b(0, 0)(0, 1) = 6.0;
    b(0, 0)(1, 0) = 7.0;
    b(0, 0)(1, 1) = 8.0;

    BlockMatrix<double> result = a + b; // Сложение двух блочных матриц

    // Проверка результатов сложения
    // Ожидаемый результат:
    // [ 1.0 + 5.0, 2.0 + 6.0 ]  => [ 6.0, 8.0 ]
    // [ 3.0 + 7.0, 4.0 + 8.0 ]  => [ 10.0, 12.0 ]
    BOOST_CHECK_EQUAL(result(0, 0)(0, 0), 6.0);  // Проверка суммы первого элемента
    BOOST_CHECK_EQUAL(result(0, 0)(1, 1), 12.0); // Проверка суммы второго элемента
}

BOOST_AUTO_TEST_CASE(BlockMatrixTestSubtraction) {
    BlockMatrix<double> a(2, 2, 2, 2); // Создаем первую блочную матрицу 2x2
    BlockMatrix<double> b(2, 2, 2, 2); // Создаем вторую блочную матрицу 2x2

    // Заполнение блоков матрицы a
    // Блок (0, 0):
    // [ 10.0, 12.0 ]
    // [ 14.0, 16.0 ]
    a(0, 0)(0, 0) = 10.0;
    a(0, 0)(0, 1) = 12.0;
    a(0, 0)(1, 0) = 14.0;
    a(0, 0)(1, 1) = 16.0;

    // Заполнение блоков матрицы b
    // Блок (0, 0):
    // [ 5.0, 6.0 ]
    // [ 7.0, 8.0 ]
    b(0, 0)(0, 0) = 5.0;
    b(0, 0)(0, 1) = 6.0;
    b(0, 0)(1, 0) = 7.0;
    b(0, 0)(1, 1) = 8.0;

    BlockMatrix<double> result = a - b; // Вычитание двух блочных матриц

    // Проверка результатов вычитания
    // Ожидаемый результат:
    // [ 10.0 - 5.0, 12.0 - 6.0 ] => [ 5.0, 6.0 ]

    // [ 14.0 - 7.0, 16.0 - 8.0 ] => [ 7.0, 8.0 ]
    BOOST_CHECK_EQUAL(result(0, 0)(0, 0), 5.0);  // Проверка разности первого элемента
    BOOST_CHECK_EQUAL(result(0, 0)(1, 1), 8.0); // Проверка разности второго элемента
}

BOOST_AUTO_TEST_CASE(BlockMatrixTestMultiplication) {
    BlockMatrix<double> a(2, 2, 2, 2); // Создаем первую блочную матрицу 2x2
    BlockMatrix<double> b(2, 2, 2, 2); // Создаем вторую блочную матрицу 2x2

    // Заполнение блоков матрицы a
    // Блок (0, 0):
    // [ 1.0, 2.0 ]
    // [ 3.0, 4.0 ]
    a(0, 0)(0, 0) = 1.0;
    a(0, 0)(0, 1) = 2.0;
    a(0, 0)(1, 0) = 3.0;
    a(0, 0)(1, 1) = 4.0;

    // Заполнение блоков матрицы b
    // Блок (0, 0):
    // [ 5.0, 6.0 ]
    // [ 7.0, 8.0 ]
    b(0, 0)(0, 0) = 5.0;
    b(0, 0)(0, 1) = 6.0;
    b(0, 0)(1, 0) = 7.0;
    b(0, 0)(1, 1) = 8.0;

    BlockMatrix<double> result = a * b; // Умножение двух блочных матриц

    // Проверка результатов умножения
    // Ожидаемый результат:
    // [ (1.0*5.0 + 2.0*7.0), (1.0*6.0 + 2.0*8.0) ]
    // [ (3.0*5.0 + 4.0*7.0), (3.0*6.0 + 4.0*8.0) ]
    // = [ 19.0, 22.0 ]
    BOOST_CHECK_EQUAL(result(0, 0)(0, 0), 19.0); // Проверка первого элемента
    BOOST_CHECK_EQUAL(result(0, 0)(0, 1), 22.0); // Проверка второго элемента
}

// Тестирование сложения несовместимых матриц
BOOST_AUTO_TEST_CASE(BlockMatrixTestIncompatibleAddition) {
    BlockMatrix<double> a(2, 2, 2, 2); // Создаем первую блочную матрицу 2x2
    BlockMatrix<double> b(3, 2, 2, 2); // Создаем вторую блочную матрицу 3x2 (несовместимый размер)

    // Проверяем, что сложение этих матриц вызывает исключение
    BOOST_CHECK_THROW(a + b, std::runtime_error);
}

// Тестирование умножения несовместимых матриц
BOOST_AUTO_TEST_CASE(BlockMatrixTestIncompatibleMultiplication) {
    BlockMatrix<double> a(2, 2, 2, 2); // Создаем первую блочную матрицу 2x2
    BlockMatrix<double> b(3, 2, 2, 2); // Создаем вторую блочную матрицу 3x2 (несовместимые размеры)

    // Проверяем, что умножение этих матриц вызывает исключение
    BOOST_CHECK_THROW(a * b, std::runtime_error);
}

// Тестирование сложения блочных матриц с элементами типа int
BOOST_AUTO_TEST_CASE(BlockMatrixTestMatrixAdditionTest) {
    BlockMatrix<int> matrixA(2, 2, 1, 1); // Создаем блочную матрицу 2x2 с блоками 1x1
    // Заполнение блоков матрицы A
    // Блок (0, 0):
    // [ 1 ]
    matrixA(0, 0)(0, 0) = 1;
    // Блок (0, 1):
    // [ 2 ]
    matrixA(0, 1)(0, 0) = 2;
    // Блок (1, 0):
    // [ 3 ]
    matrixA(1, 0)(0, 0) = 3;
    // Блок (1, 1):
    // [ 4 ]
    matrixA(1, 1)(0, 0) = 4;

    BlockMatrix<int> matrixB(2, 2, 1, 1); // Создаем блочную матрицу 2x2 с блоками 1x1
    // Заполнение блоков матрицы B
    // Блок (0, 0):
    // [ 5 ]
    matrixB(0, 0)(0, 0) = 5;
    // Блок (0, 1):
    // [ 6 ]
    matrixB(0, 1)(0, 0) = 6;
    // Блок (1, 0):
    // [ 7 ]
    matrixB(1, 0)(0, 0) = 7;
    // Блок (1, 1):
    // [ 8 ]
    matrixB(1, 1)(0, 0) = 8;

    BlockMatrix<int> result = matrixA + matrixB; // Сложение двух блочных матриц

    // Проверка результатов сложения
    // Ожидаемый результат:
    // [ 1 + 5, 2 + 6 ] => [ 6, 8 ]
    // [ 3 + 7, 4 + 8 ] => [ 10, 12 ]
    BOOST_CHECK_EQUAL(result(0, 0)(0, 0), 6);  // Проверка суммы первого элемента
    BOOST_CHECK_EQUAL(result(0, 1)(0, 0), 8);  // Проверка суммы второго элемента
    BOOST_CHECK_EQUAL(result(1, 0)(0, 0), 10); // Проверка суммы третьего элемента
    BOOST_CHECK_EQUAL(result(1, 1)(0, 0), 12); // Проверка суммы четвертого элемента
}

BOOST_AUTO_TEST_CASE(BlockMatrixTestKroneckerProductTest) {
    BlockMatrix<int> A(3, 2, 1, 1);
    A(0, 0)(0, 0) = 1;
    A(0, 1)(0, 0) = 2;
    A(1, 0)(0, 0) = 3;
    A(1, 1)(0, 0) = 4;
    A(2, 0)(0, 0) = 1;
    A(2, 1)(0, 0) = 0;

    BlockMatrix<int> B(2, 3, 1, 1);
    B(0, 0)(0, 0) = 0;
    B(0, 1)(0, 0) = 5;
    B(0, 2)(0, 0) = 2;
    B(1, 0)(0, 0) = 6;
    B(1, 1)(0, 0) = 7;
    B(1, 2)(0, 0) = 3;

    BlockMatrix<int> result = A.KroneckerProduct(B);

    // Поскольку A имеет 3 строки и 2 столбца, а B имеет 2 строки и 3 столбца,
    // результирующая матрица будет иметь (3*2) x (2*3) = 6 x 6.

    // Проверяем все значения в результате произведения Кронекера

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
