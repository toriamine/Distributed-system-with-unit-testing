#include <boost/test/unit_test.hpp>
#include "../Lab/BlockMatrix.h"
#include "../Lab/BlockMatrix.cpp"

BOOST_AUTO_TEST_SUITE(BlockMatrixTests) // Начало набора тестов для блочных матриц

// Тестирование конструктора и доступа к элементам блочной матрицы
BOOST_AUTO_TEST_CASE(BlockMatrixTestConstructorAndAccess) {
    BlockMatrix<double, DenseMatrix> blockMatrix(2, 2, 2, 2); // Создаем блочную матрицу из 2x2 блоков, каждый размером 2x2

    BlockMatrix<int, DenseMatrix> a(2, 2, 2, 2);

    // Создаем блочные матрицы 2x2 блоков, каждый из которых 2x2 элементы
        // Установим значения в блоки
    // Блок (0, 0):
    // [ 1.0, 2.0 ]
    // [ 3.0, 4.0 ]

    a.CreateBlock(0, 0, new DenseMatrix<int>(2, 2));
    a(0, 0) = 1; a(0, 1) = 2;
    a(1, 0) = 3; a(1, 1) = 4;

    // Блок (0, 1):
    // [ 5.0, 6.0 ]
    // [ 7.0, 8.0 ]

    a.CreateBlock(0, 1, new DenseMatrix<int>(2, 2));
    a(0, 2) = 5; a(0, 3) = 6;
    a(1, 2) = 7; a(1, 3) = 8;


    // Блок (1, 0):
    // [ 9.0, 10.0 ]
    // [ 11.0, 12.0 ]
    a.CreateBlock(1, 0, new DenseMatrix<int>(2, 2));
    a(2, 0) = 9; a(2, 1) = 10;
    a(3, 0) = 11; a(3, 1) = 12;

    // Блок (1, 1):
    // [ 13.0, 14.0 ]
    // [ 15.0, 16.0 ]
    a.CreateBlock(1, 1, new DenseMatrix<int>(2, 2));
    a(2, 2) = 13; a(2, 3) = 14;
    a(3, 2) = 15; a(3, 3) = 16;


    // Проверка доступа к блокам и их элементам
    BOOST_CHECK_EQUAL(a(0, 0), 1);   //Тест первого элемента первой матрицы
    BOOST_CHECK_EQUAL(a(0, 3), 6);   // Тест последнего элемента первой строки
    BOOST_CHECK_EQUAL(a(1, 2), 7);   // Тест элемента из второго блока
    BOOST_CHECK_EQUAL(a(2, 1), 10);  // Тест элемента второго ряда третьего блока
    BOOST_CHECK_EQUAL(a(3, 3), 16);  // Тест последнего элемента
}

BOOST_AUTO_TEST_CASE(BlockMatrixTestAddition) {
    BlockMatrix<double, DenseMatrix> a(2, 2, 2, 2); // Создаем первую блочную матрицу 2x2
    BlockMatrix<double, DenseMatrix> b(2, 2, 2, 2); // Создаем вторую блочную матрицу 2x2

    // Заполнение матрицы A
    a.CreateBlock(0, 0, new DenseMatrix<double>(2, 2));
    a(0, 0) = 1; a(0, 1) = 2; // Заполняем первый блок
    a(1, 0) = 3; a(1, 1) = 4;

    a.CreateBlock(0, 1, new DenseMatrix<double>(2, 2));
    a(0, 0 + 2) = 5; a(0, 1 + 2) = 6; // Заполняем второй блок (первый блок второй строки)
    a(1, 0 + 2) = 7; a(1, 1 + 2) = 8;

    a.CreateBlock(1, 0, new DenseMatrix<double>(2, 2));
    a(0 + 2, 0) = 9; a(0 + 2, 1) = 10; // Заполняем третий блок (второй блок первой строки)
    a(1 + 2, 0) = 11; a(1 + 2, 1) = 12;

    a.CreateBlock(1, 1, new DenseMatrix<double>(2, 2));
    a(0 + 2, 0 + 2) = 13; a(0 + 2, 1 + 2) = 14; // Заполняем четвертый блок (второй блок второй строки)
    a(1 + 2, 0 + 2) = 15; a(1 + 2, 1 + 2) = 16;

    // Заполнение матрицы B
    b.CreateBlock(0, 0, new DenseMatrix<double>(2, 2));
    b(0, 0) = 1; b(0, 1) = 1; // Заполняем первый блок
    b(1, 0) = 1; b(1, 1) = 1;

    b.CreateBlock(0, 1, new DenseMatrix<double>(2, 2));
    b(0, 0 + 2) = 2; b(0, 1 + 2) = 2; // Заполняем второй блок (первый блок второй строки)
    b(1, 0 + 2) = 2; b(1, 1 + 2) = 2;

    b.CreateBlock(1, 0, new DenseMatrix<double>(2, 2));
    b(0 + 2, 0) = 3; b(0 + 2, 1) = 3; // Заполняем третий блок (второй блок первой строки)
    b(1 + 2, 0) = 3; b(1 + 2, 1) = 3;

    b.CreateBlock(1, 1, new DenseMatrix<double>(2, 2));
    b(0 + 2, 0 + 2) = 4; b(0 + 2, 1 + 2) = 4; // Заполняем четвертый блок (второй блок второй строки)
    b(1 + 2, 0 + 2) = 4; b(1 + 2, 1 + 2) = 4;

    // Выполняем операцию сложения
    BlockMatrix<double, DenseMatrix> c = a + b;
    std::cout << "\nA + B:\n";
    c.Print();

    // Проверяем результат сложения
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
    BlockMatrix<double, DenseMatrix> a(2, 2, 2, 2); // Создаем первую блочную матрицу 2x2
    BlockMatrix<double, DenseMatrix> b(2, 2, 2, 2); // Создаем вторую блочную матрицу 2x2

    // Заполнение матрицы A
    a.CreateBlock(0, 0, new DenseMatrix<double>(2, 2));
    a(0, 0) = 10; a(0, 1) = 12;
    a(1, 0) = 14; a(1, 1) = 16;

    a.CreateBlock(0, 1, new DenseMatrix<double>(2, 2));
    a(0, 2) = 18; a(0, 3) = 20;
    a(1, 2) = 22; a(1, 3) = 24;

    a.CreateBlock(1, 0, new DenseMatrix<double>(2, 2));
    a(2, 0) = 26; a(2, 1) = 28;
    a(3, 0) = 30; a(3, 1) = 32;

    a.CreateBlock(1, 1, new DenseMatrix<double>(2, 2));
    a(2, 2) = 34; a(2, 3) = 36;
    a(3, 2) = 38; a(3, 3) = 40;

    // Заполнение матрицы B
    b.CreateBlock(0, 0, new DenseMatrix<double>(2, 2));
    b(0, 0) = 5; b(0, 1) = 6;
    b(1, 0) = 7; b(1, 1) = 8;

    b.CreateBlock(0, 1, new DenseMatrix<double>(2, 2));
    b(0, 2) = 9; b(0, 3) = 10;
    b(1, 2) = 11; b(1, 3) = 12;

    b.CreateBlock(1, 0, new DenseMatrix<double>(2, 2));
    b(2, 0) = 13; b(2, 1) = 14;
    b(3, 0) = 15; b(3, 1) = 16;

    b.CreateBlock(1, 1, new DenseMatrix<double>(2, 2));
    b(2, 2) = 17; b(2, 3) = 18;
    b(3, 2) = 19; b(3, 3) = 20;

    // Вычитание двух блочных матриц
    BlockMatrix<double, DenseMatrix> result = a - b;

    // Проверка результатов вычитания
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

// Тестирование сложения несовместимых матриц
BOOST_AUTO_TEST_CASE(BlockMatrixTestIncompatibleAddition) {
    BlockMatrix<double, DenseMatrix> a(2, 2, 2, 2); // Создаем первую блочную матрицу 2x2
    BlockMatrix<double, DenseMatrix> b(3, 2, 2, 2); // Создаем вторую блочную матрицу 3x2 (несовместимый размер)

    // Проверяем, что сложение этих матриц вызывает исключение
    BOOST_CHECK_THROW(a + b, std::runtime_error);
}

// Тестирование умножения несовместимых матриц
BOOST_AUTO_TEST_CASE(BlockMatrixTestIncompatibleMultiplication) {
    BlockMatrix<double, DenseMatrix> a(2, 2, 2, 2); // Создаем первую блочную матрицу 2x2
    BlockMatrix<double, DenseMatrix> b(3, 2, 2, 2); // Создаем вторую блочную матрицу 3x2 (несовместимые размеры)

    // Проверяем, что умножение этих матриц вызывает исключение
    BOOST_CHECK_THROW(a - b, std::runtime_error);
}

BOOST_AUTO_TEST_CASE(BlockMatrixTestKroneckerProduct) {
    // Создаем блочные матрицы 1x1 с блоками размером 2x2
    BlockMatrix<int, DenseMatrix> A(1, 1, 2, 2); // 1 блок по 2 строки, 1 блок по 2 столбца
    BlockMatrix<int, DenseMatrix> B(1, 1, 2, 2); // 1 блок по 2 строки, 1 блок по 2 столбца

    // Заполнение матрицы A
    A.CreateBlock(0, 0, new DenseMatrix<int>(2, 2)); // Блок A[0][0]
    A(0, 0) = 1; A(0, 1) = 2; // Заполняем первый блок
    A(1, 0) = 3; A(1, 1) = 4;

    // Заполнение матрицы B
    B.CreateBlock(0, 0, new DenseMatrix<int>(2, 2)); // Блок B[0][0]
    B(0, 0) = 5; B(0, 1) = 6; // Заполняем первый блок
    B(1, 0) = 7; B(1, 1) = 8;

    // Выполнить произведение Кронекера
    BlockMatrix<int, DenseMatrix> result = A.kroneckerProduct(B);

    // Ожидаемая матрица C после произведения Кронекера
    // C = A(0,0) * B
    // Результирующая матрица будет 4x4 (2*2 и 2*2):
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

    // Проверка результата на соответствие ожидаемому
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            BOOST_CHECK_EQUAL(result(i, j), expectedResult[i][j]);
        }
    }
}

BOOST_AUTO_TEST_CASE(BlockMatrixTestDiagonalConstructorAndAccess) {
    BlockMatrix<double, DiagonalMatrix> blockMatrix(2, 2, 2, 2); // Создаем блочную матрицу из 2x2 блоков, каждый размером 2x2

    // Создаем блочные матрицы 2x2 блоков, каждый из которых 2x2 элементы
    // Установим значения в блоки
    // Блок (0, 0):
    // [ 1.0, 0.0 ]
    // [ 0.0, 2.0 ]
    blockMatrix.CreateBlock(0, 0, new DiagonalMatrix<double>({ 1, 2 }));

    // Блок (0, 1):
    // [ 3.0, 0.0 ]
    // [ 0.0, 4.0 ]
    blockMatrix.CreateBlock(0, 1, new DiagonalMatrix<double>({ 3, 4 }));

    // Блок (1, 0):
    // [ 5.0, 0.0 ]
    // [ 0.0, 6.0 ]
    blockMatrix.CreateBlock(1, 0, new DiagonalMatrix<double>({ 5, 6 }));

    // Блок (1, 1):
    // [ 7.0, 0.0 ]
    // [ 0.0, 8.0 ]
    blockMatrix.CreateBlock(1, 1, new DiagonalMatrix<double>({ 7, 8 }));

    // Проверка доступа к блокам и их элементам
    BOOST_CHECK_EQUAL(blockMatrix(0, 0), 1);   // Проверяем первый элемент первого блока
    BOOST_CHECK_EQUAL(blockMatrix(1, 1), 2);   // Проверяем второй элемент первого блока
    BOOST_CHECK_EQUAL(blockMatrix(0, 2), 3);   // Проверяем первый элемент второго блока
    BOOST_CHECK_EQUAL(blockMatrix(1, 3), 4);   // Проверяем второй элемент второго блока
    BOOST_CHECK_EQUAL(blockMatrix(2, 0), 5);   // Проверяем первый элемент третьего блока
    BOOST_CHECK_EQUAL(blockMatrix(3, 1), 6);   // Проверяем второй элемент третьего блока
    BOOST_CHECK_EQUAL(blockMatrix(2, 2), 7);   // Проверяем первый элемент четвертого блока
    BOOST_CHECK_EQUAL(blockMatrix(3, 3), 8);   // Проверяем второй элемент четвертого блока
}

BOOST_AUTO_TEST_CASE(BlockMatrixTestAdditionDiagonal) {
    BlockMatrix<double, DiagonalMatrix> a(2, 2, 2, 2); // Создаем первую блочную матрицу 2x2
    BlockMatrix<double, DiagonalMatrix> b(2, 2, 2, 2); // Создаем вторую блочную матрицу 2x2

    // Заполнение матрицы A
    a.CreateBlock(0, 0, new DiagonalMatrix<double>({ 1, 2 })); // Блок (0, 0)
    a.CreateBlock(0, 1, new DiagonalMatrix<double>({ 3, 4 })); // Блок (0, 1)
    a.CreateBlock(1, 0, new DiagonalMatrix<double>({ 5, 6 })); // Блок (1, 0)
    a.CreateBlock(1, 1, new DiagonalMatrix<double>({ 7, 8 })); // Блок (1, 1)

    // Заполнение матрицы B
    b.CreateBlock(0, 0, new DiagonalMatrix<double>({ 1, 1 })); // Блок (0, 0)
    b.CreateBlock(0, 1, new DiagonalMatrix<double>({ 2, 2 })); // Блок (0, 1)
    b.CreateBlock(1, 0, new DiagonalMatrix<double>({ 3, 3 })); // Блок (1, 0)
    b.CreateBlock(1, 1, new DiagonalMatrix<double>({ 4, 4 })); // Блок (1, 1)

    // Выполняем операцию сложения
    BlockMatrix<double, DiagonalMatrix> c = a + b;

    // Проверяем результат сложения
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
    blockMatrixA.CreateBlock(0, 0, new DiagonalMatrix<int>({ 1, 4 }));

    BlockMatrix<int, DiagonalMatrix> blockMatrixB(3, 3, 2, 2); // Несовместимые размеры (3x3)

    BOOST_CHECK_THROW(blockMatrixA + blockMatrixB, std::runtime_error);
}

BOOST_AUTO_TEST_CASE(IncompatibleBlockMatrixMultiplicationTest) {
    BlockMatrix<int, DiagonalMatrix> blockMatrixA(3, 2, 2, 2); // 3 строки, 2 колонки
    BlockMatrix<int, DiagonalMatrix> blockMatrixB(2, 3, 2, 2); // 2 строки, 3 колонки

    BOOST_CHECK_THROW(blockMatrixA - blockMatrixB, std::runtime_error); // Ожидаем исключение
}

BOOST_AUTO_TEST_CASE(IncompatibleBlockMatrixAdditionTestBlock) {
    BlockMatrix<int, DiagonalMatrix> blockMatrixA(2, 2, 2, 2);
    blockMatrixA.CreateBlock(0, 0, new DiagonalMatrix<int>({ 1, 4 }));

    BlockMatrix<int, DiagonalMatrix> blockMatrixB(2, 2, 2, 1); // Разное количество блоков

    BOOST_CHECK_THROW(blockMatrixA + blockMatrixB, std::runtime_error);
}

BOOST_AUTO_TEST_CASE(BlockMatrixTestSubtractionDiagonal) {
    BlockMatrix<double, DiagonalMatrix> a(2, 2, 2, 2); // Создаем первую блочную матрицу 2x2
    BlockMatrix<double, DiagonalMatrix> b(2, 2, 2, 2); // Создаем вторую блочную матрицу 2x2

    // Заполнение матрицы A
    a.CreateBlock(0, 0, new DiagonalMatrix<double>({ 5, 6 })); // Блок (0, 0)
    a.CreateBlock(0, 1, new DiagonalMatrix<double>({ 7, 8 })); // Блок (0, 1)
    a.CreateBlock(1, 0, new DiagonalMatrix<double>({ 9, 10 })); // Блок (1, 0)
    a.CreateBlock(1, 1, new DiagonalMatrix<double>({ 11, 12 })); // Блок (1, 1)

    // Заполнение матрицы B
    b.CreateBlock(0, 0, new DiagonalMatrix<double>({ 1, 1 })); // Блок (0, 0)
    b.CreateBlock(0, 1, new DiagonalMatrix<double>({ 2, 2 })); // Блок (0, 1)
    b.CreateBlock(1, 0, new DiagonalMatrix<double>({ 3, 3 })); // Блок (1, 0)
    b.CreateBlock(1, 1, new DiagonalMatrix<double>({ 4, 4 })); // Блок (1, 1)

    // Выполняем операцию вычитания
    BlockMatrix<double, DiagonalMatrix> c = a - b;

    // Проверяем результат вычитания
    BOOST_CHECK_EQUAL(c(0, 0), 4);   // 5 - 1
    BOOST_CHECK_EQUAL(c(1, 1), 5);   // 6 - 1
    BOOST_CHECK_EQUAL(c(0, 2), 5);   // 7 - 2
    BOOST_CHECK_EQUAL(c(1, 3), 6);   // 8 - 2
    BOOST_CHECK_EQUAL(c(2, 0), 6);   // 9 - 3
    BOOST_CHECK_EQUAL(c(3, 1), 7);   // 10 - 3
    BOOST_CHECK_EQUAL(c(2, 2), 7);   // 11 - 4
    BOOST_CHECK_EQUAL(c(3, 3), 8);   // 12 - 4
}

BOOST_AUTO_TEST_SUITE_END()