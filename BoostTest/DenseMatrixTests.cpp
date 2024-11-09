#include <boost/test/unit_test.hpp>
#include "../Lab/DenseMatrix.h"
#include <stdexcept>

BOOST_AUTO_TEST_SUITE(DenseMatrixTests)

// Тестирует конструктор класса DenseMatrix
BOOST_AUTO_TEST_CASE(DenseConstructorTest) {
    // Создаем 3x3 матрицу
    DenseMatrix<double> mat(3, 3);
    // Проверяем, что количество строк равно 3
    BOOST_CHECK_EQUAL(mat.rows(), 3);
    // Проверяем, что количество колонок равно 3
    BOOST_CHECK_EQUAL(mat.cols(), 3);

    // Проверка, что все элементы матрицы равны нулю
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            BOOST_CHECK_EQUAL(mat(i, j), 0.0); // Все элементы должны равняться 0.0
        }
    }
}

// Тестирует инициализацию с использованием списков
BOOST_AUTO_TEST_CASE(DenseInitializerListTest) {
    // Создаем матрицу 2x3 с начальным заполнением
    DenseMatrix<double> mat{ {1, 2, 3}, {4, 5, 6} };
    // Проверяем размерности матрицы
    BOOST_CHECK_EQUAL(mat.rows(), 2); // Две строки
    BOOST_CHECK_EQUAL(mat.cols(), 3); // Три колонки

    // Проверяем значения отдельных элементов матрицы
    BOOST_CHECK_EQUAL(mat(0, 0), 1); // Первый элемент
    BOOST_CHECK_EQUAL(mat(1, 2), 6); // Последний элемент
}

// Тестирует операцию сложения матриц
BOOST_AUTO_TEST_CASE(DenseAdditionTest) {
    // Создаем две матрицы 2x2
    DenseMatrix<double> mat1{ {1, 2}, {3, 4} };
    DenseMatrix<double> mat2{ {5, 6}, {7, 8} };
    // Сложение матриц
    DenseMatrix<double> result = mat1 + mat2;

    // Проверяем значения элементов результирующей матрицы
    BOOST_CHECK_EQUAL(result(0, 0), 6); // 1 + 5 = 6
    BOOST_CHECK_EQUAL(result(1, 1), 12); // 4 + 8 = 12
}

// Тестирует операцию вычитания матриц
BOOST_AUTO_TEST_CASE(DenseSubtractionTest) {
    // Создаем две матрицы 2x2
    DenseMatrix<double> mat1{ {5, 6}, {7, 8} };
    DenseMatrix<double> mat2{ {1, 2}, {3, 4} };
    // Вычитание матриц
    DenseMatrix<double> result = mat1 - mat2;

    // Проверяем значения элементов результирующей матрицы
    BOOST_CHECK_EQUAL(result(0, 0), 4); // 5 - 1 = 4
    BOOST_CHECK_EQUAL(result(1, 1), 4); // 8 - 4 = 4
}

// Тестирует операцию умножения матриц
BOOST_AUTO_TEST_CASE(DenseMultiplicationTest) {
    // Создаем две матрицы 2x2
    DenseMatrix<double> mat1{ {1, 2}, {3, 4} };
    DenseMatrix<double> mat2{ {2, 0}, {1, 2} };
    // Умножение матриц
    DenseMatrix<double> result = mat1 * mat2;

    // Проверяем значения элементов результирующей матрицы
    BOOST_CHECK_EQUAL(result(0, 0), 4); // 1*2 + 2*1 = 4
    BOOST_CHECK_EQUAL(result(1, 1), 8); // 3*0 + 4*2 = 8
}

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

BOOST_AUTO_TEST_CASE(MatrixTestDense1) {
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