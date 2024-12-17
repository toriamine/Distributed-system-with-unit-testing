#include <boost/test/unit_test.hpp>
#include "../Lab/DiagonalMatrix.cpp"

BOOST_AUTO_TEST_SUITE(DiagonalMatrixTests) // Начало набора тестов для диагональных матриц

// Тестирование конструктора и доступа к элементам
BOOST_AUTO_TEST_CASE(DiagonalMatrixTests_ConstructorTest) {

    DiagonalMatrix<double> mat(3); // Создаем диагональную матрицу 3x3

    // Устанавливаем значения на главной диагонали
    mat(0, 0) = 1.0; // Задаем элемент (0, 0)
    mat(1, 1) = 2.0; // Задаем элемент (1, 1)
    mat(2, 2) = 3.0; // Задаем элемент (2, 2)

    // Проверяем корректность доступа к диагональным элементам
    BOOST_CHECK_EQUAL(mat(0, 0), 1.0); // Ожидаем, что матрица в (0, 0) равна 1.0
    BOOST_CHECK_EQUAL(mat(1, 1), 2.0); // Ожидаем, что матрица в (1, 1) равна 2.0
    BOOST_CHECK_EQUAL(mat(2, 2), 3.0); // Ожидаем, что матрица в (2, 2) равна 3.0

    // Проверка значений вне главной диагонали
    BOOST_CHECK_EQUAL(mat(0, 1), 0.0); // Ожидаем, что матрица в (0, 1) равна 0.0
    BOOST_CHECK_EQUAL(mat(0, 2), 0.0); // Ожидаем, что матрица в (0, 2) равна 0.0
    BOOST_CHECK_EQUAL(mat(1, 0), 0.0); // Ожидаем, что матрица в (1, 0) равна 0.0
    BOOST_CHECK_EQUAL(mat(1, 2), 0.0); // Ожидаем, что матрица в (1, 2) равна 0.0
    BOOST_CHECK_EQUAL(mat(2, 0), 0.0); // Ожидаем, что матрица в (2, 0) равна 0.0
    BOOST_CHECK_EQUAL(mat(2, 1), 0.0); // Ожидаем, что матрица в (2, 1) равна 0.0
}

// Тестирование сложения диагональных матриц
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

// Тестирование вычитания диагональных матриц
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

// Тестирование умножения диагональных матриц
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

// Тестирование получения количества строк и столбцов
BOOST_AUTO_TEST_CASE(DiagonalMatrixTests_SizeTest) {

    DiagonalMatrix<int> matrix(3); // Создание диагональной матрицы 3x3 с нулями
    BOOST_CHECK_EQUAL(matrix.rows(), 3);
    BOOST_CHECK_EQUAL(matrix.cols(), 3);

}

// Тестирование сложения несовместимых матриц
BOOST_AUTO_TEST_CASE(DiagonalMatrixTests_IncompatibleAddition) {

    DiagonalMatrix<double> a{ 1, 2 }; // Создаем первую диагональную матрицу размером 2x2
    DiagonalMatrix<double> b{ 1, 2, 3 }; // Создаем вторую диагональную матрицу размером 3x3

    // Проверяем, что сложение этих матриц вызывает исключение
    BOOST_CHECK_THROW(a + b, std::invalid_argument); // Ожидаем исключение при сложении несовместимых матриц

}

// Тестирование умножения несовместимых матриц
BOOST_AUTO_TEST_CASE(DiagonalMatrixTests_IncompatibleMultiplication) {

    DiagonalMatrix<double> a{ 1, 2, 3 }; // Создаем первую диагональную матрицу размером 3x3
    DiagonalMatrix<double> b{ 1, 2 }; // Создаем вторую диагональную матрицу размером 2x2

    // Проверяем, что умножение этих матриц вызывает исключение
    BOOST_CHECK_THROW(a * b, std::invalid_argument); // Ожидаем исключение при умножении несовместимых матриц

}

BOOST_AUTO_TEST_CASE(DiagonalMatrixTests_IncompatibleSubtraction) {

    DiagonalMatrix<double> a{ 1, 2, 3 }; // Создаем первую диагональную матрицу размером 3x3
    DiagonalMatrix<double> b{ 1, 2 }; // Создаем вторую диагональную матрицу размером 2x2

    // Проверяем, что умножение этих матриц вызывает исключение
    BOOST_CHECK_THROW(a - b, std::invalid_argument); // Ожидаем исключение при умножении несовместимых матриц

}

BOOST_AUTO_TEST_SUITE_END() // Конец набора тестов для диагональных матриц