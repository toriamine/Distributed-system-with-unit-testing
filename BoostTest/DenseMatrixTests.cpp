#include <boost/test/unit_test.hpp>
#include "../Lab/DenseMatrix.cpp"

BOOST_AUTO_TEST_SUITE(DenseMatrixTests)

// Тестирует конструктор класса DenseMatrix
BOOST_AUTO_TEST_CASE(DenseMatrixTests_ConstructorTest) {

    // Создаем 3x3 матрицу
    DenseMatrix<double> mat(3, 3);

    // Проверяем, что количество строк равно 3
    BOOST_CHECK_EQUAL(mat.rows(), 3);

    // Проверяем, что количество колонок равно 3
    BOOST_CHECK_EQUAL(mat.cols(), 3);

    // Проверка, что все элементы матрицы равны нулю
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            BOOST_CHECK_EQUAL(mat(i, j), 0.0); // Все элементы должны быть равны 0.0
        }
    }

}

// Тестирует инициализацию с использованием списков
BOOST_AUTO_TEST_CASE(DenseMatrixTests_InitializerListTest) {

    // Создаем матрицу 2x3 с использованием списка
    DenseMatrix<double> mat{ {1, 2, 3}, {4, 5, 6} };

    // Проверяем размерности матрицы
    BOOST_CHECK_EQUAL(mat.rows(), 2); // Две строки
    BOOST_CHECK_EQUAL(mat.cols(), 3); // Три колонки

    // Проверяем значения элементов матрицы
    BOOST_CHECK_EQUAL(mat(0, 0), 1);
    BOOST_CHECK_EQUAL(mat(0, 1), 2);
    BOOST_CHECK_EQUAL(mat(0, 2), 3);
    BOOST_CHECK_EQUAL(mat(1, 0), 4);
    BOOST_CHECK_EQUAL(mat(1, 1), 5);
    BOOST_CHECK_EQUAL(mat(1, 2), 6);

}

// Тестирует операцию сложения матриц
BOOST_AUTO_TEST_CASE(DenseMatrixTests_AdditionTest) {

    // Создаем две матрицы 2x2
    DenseMatrix<double> mat1{ {1, 2}, {3, 4} };
    DenseMatrix<double> mat2{ {5, 6}, {7, 8} };

    // Сложение матриц
    DenseMatrix<double> result = mat1 + mat2;

    // Проверяем значения элементов результирующей матрицы
    BOOST_CHECK_EQUAL(result(0, 0), 6);
    BOOST_CHECK_EQUAL(result(0, 1), 8);
    BOOST_CHECK_EQUAL(result(1, 0), 10);
    BOOST_CHECK_EQUAL(result(1, 1), 12);

}

// Тестирует операцию вычитания матриц
BOOST_AUTO_TEST_CASE(DenseMatrixTests_SubtractionTest) {

    // Создаем две матрицы 2x2
    DenseMatrix<double> mat1{ {5, 6}, {7, 8} };
    DenseMatrix<double> mat2{ {1, 2}, {3, 4} };

    // Вычитание матриц
    DenseMatrix<double> result = mat1 - mat2;

    // Проверяем значения элементов результирующей матрицы
    BOOST_CHECK_EQUAL(result(0, 0), 4);
    BOOST_CHECK_EQUAL(result(0, 1), 4);
    BOOST_CHECK_EQUAL(result(1, 0), 4);
    BOOST_CHECK_EQUAL(result(1, 1), 4);

}

// Тестирует операцию умножения матриц
BOOST_AUTO_TEST_CASE(DenseMatrixTests_MultiplicationTest) {

    // Создаем две матрицы 2x2
    DenseMatrix<double> mat1{ {1, 2}, {3, 4} };
    DenseMatrix<double> mat2{ {5, 6}, {7, 8} };

    // Умножение матриц
    DenseMatrix<double> result = mat1 * mat2;

    // Проверяем значения элементов результирующей матрицы
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