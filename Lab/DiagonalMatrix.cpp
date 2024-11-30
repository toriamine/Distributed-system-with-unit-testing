#include "DiagonalMatrix.h"

// Конструктор
template<typename T>
DiagonalMatrix<T>::DiagonalMatrix(std::initializer_list<T> initializer_list)
    : data(initializer_list.size(), std::vector<T>(initializer_list.size(), T(0))) {
    size = initializer_list.size();
    size_t index = 0;
    for (auto& val : initializer_list) {
        data[index][index] = val;  // Заполните диагональные элементы
        ++index;
    }
}

// Конструктор для нулевой инициализации
template<typename T>
DiagonalMatrix<T>::DiagonalMatrix(size_t Size)
    : data(Size, std::vector<T>(Size, T(0))) {
    size = Size;
    for (size_t i = 0; i < size; ++i) {
        data[i][i] = T(0);  // Все элементы по умолчанию нули
    }
}

// Реализация операторов
   // Доступ к элементам матрицы
template <typename T>
T& DiagonalMatrix<T>::operator()(size_t i, size_t j) {
    if (i >= rows() || j >= cols()) {
        throw std::out_of_range("Index out of range");
    }
    return data[i][j];  
}

template <typename T>
const T& DiagonalMatrix<T>::operator()(size_t i, size_t j) const {
    if (i >= rows() || j >= cols()) {
        throw std::out_of_range("Index out of range");
    }
    return data[i][j];
}

// Метод получения количества строк
template <typename T>
size_t DiagonalMatrix<T>::rows() const {
    return size;
}

// Метод получения количества столбцов
template <typename T>
size_t DiagonalMatrix<T>::cols() const {
    return size;
}

template <typename T>
DiagonalMatrix<T> DiagonalMatrix<T>::operator+(const DiagonalMatrix<T>& other) const {
    // Проверка на несовместимые размеры
    if (rows() != other.rows()) {
        throw std::invalid_argument("Количество строк в матрицах не совпадает."); // Количество строк не совпадает
    }
    if (cols() != other.cols()) {
        throw std::invalid_argument("Количество столбцов в матрицах не совпадает."); // Количество столбцов не совпадает
    }

    DiagonalMatrix<T> result(rows());
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < rows(); ++j)
        {
            if (i == j)
            {
                result(i, j) = data[i][j] + other.data[i][j];
            }
            
        }
    }
    return result;
}

template <typename T>
DiagonalMatrix<T> DiagonalMatrix<T>::operator-(const DiagonalMatrix<T>& other) const {
    // Проверка на несовместимые размеры
    if (rows() != other.rows()) {
        throw std::invalid_argument("Количество строк в матрицах не совпадает."); // Количество строк не совпадает
    }
    if (cols() != other.cols()) {
        throw std::invalid_argument("Количество столбцов в матрицах не совпадает."); // Количество столбцов не совпадает
    }

    DiagonalMatrix<T> result(rows());
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < rows(); ++j)
        {
            if (i == j)
            {
                result(i, j) = data[i][j] - other.data[i][j];
            }

        }
    }
    return result;
}

template <typename T>
DiagonalMatrix<T> DiagonalMatrix<T>::operator*(const DiagonalMatrix<T>& other) const {

    // Проверка на несовместимые размеры (число столбцов первой должно совпадать с числом строк второй)
    if (cols() != other.rows()) {
        throw std::invalid_argument("Количество столбцов первой матрицы должно совпадать с количеством строк второй матрицы."); // Проверка совместимости для умножения
    }

    DiagonalMatrix<T> result(rows());
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < rows(); ++j)
        {
            if (i == j)
            {
                result(i, j) = data[i][j] * other.data[i][j];
            }

        }
    }
    return result;
}

// Метод для вывода матрицы
template <typename T>
void DiagonalMatrix<T>::Print() const {
    std::cout << "Diagonal Matrix:\n";
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < cols(); ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Явная инстанциация для стандартных числовых типов

template class DiagonalMatrix<int>;                       // int: 32-битное целое число (в большинстве сред).
template class DiagonalMatrix<unsigned int>;              // unsigned int: Беззнаковое 32-битное целое число.
template class DiagonalMatrix<short>;                     // short: Обычно 16-битное целое число.
template class DiagonalMatrix<unsigned short>;            // unsigned short: Беззнаковое 16-битное целое число.
template class DiagonalMatrix<long>;                       // long: Обычно 32-битное целое, но в некоторых средах это 64-битное целое (например, на 64-разрядных системах).
template class DiagonalMatrix<unsigned long>;              // unsigned long: Беззнаковое представление long.
template class DiagonalMatrix<long long>;                 // long long: Гарантирует минимум 64 бита.
template class DiagonalMatrix<unsigned long long>;        // unsigned long long: Беззнаковое представление long long.
template class DiagonalMatrix<float>;                      // float: Обычно 32-битное представление числа с плавающей точкой.
template class DiagonalMatrix<double>;                     // double: Обычно 64-битное представление числа с плавающей точкой.
template class DiagonalMatrix<long double>;                // long double: Обычно расширенное представление числа с плавающей точкой, минимум 80 бит.