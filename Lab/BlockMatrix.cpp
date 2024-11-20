#include "BlockMatrix.h"

// Конструктор
template<typename T, template <typename> class MatrixType>
BlockMatrix<T, MatrixType>::BlockMatrix(size_t blockRows, size_t blockCols, size_t rows, size_t cols)
    : blockRows(blockRows), blockCols(blockCols),
          numBlocksRows((rows + blockRows - 1) / blockRows), // Округление вверх
          numBlocksCols((cols + blockCols - 1) / blockCols) {
        blocks.resize(numBlocksRows, std::vector<MatrixType<T>*>(numBlocksCols, nullptr));
    }

// Деструктор
template<typename T, template <typename> class MatrixType>
BlockMatrix<T, MatrixType>::~BlockMatrix() {
    for (size_t i = 0; i < numBlocksRows; ++i) {
        for (size_t j = 0; j < numBlocksCols; ++j) {
            delete blocks[i][j]; // Освобождаем память для каждого блока
        }
    }
}

// Установить блок
template<typename T, template <typename> class MatrixType>
void BlockMatrix<T, MatrixType>::setBlock(size_t row, size_t col, MatrixType<T>* block) {
    if (row >= numBlocksRows || col >= numBlocksCols) {
        throw std::out_of_range("Block index out of range");
    }
    blocks[row][col] = block; // Устанавливаем указатель на блок
}

// Оператор доступа к элементам
template<typename T, template <typename> class MatrixType>
T& BlockMatrix<T, MatrixType>::operator()(size_t i, size_t j) {
    if (i >= rows() || j >= cols()) {
        throw std::out_of_range("Index out of range");
    }

    size_t blockRow = i / blockRows;
    size_t blockCol = j / blockCols;
    size_t localRow = i % blockRows;
    size_t localCol = j % blockCols;

    if (!blocks[blockRow][blockCol]) {
        throw std::runtime_error("Block is not set");
    }

    return (*blocks[blockRow][blockCol])(localRow, localCol);
}

template<typename T, template <typename> class MatrixType>
const T& BlockMatrix<T, MatrixType>::operator()(size_t i, size_t j) const {
    if (i >= rows() || j >= cols()) {
        throw std::out_of_range("Index out of range");
    }

    size_t blockRow = i / blockRows;
    size_t blockCol = j / blockCols;
    size_t localRow = i % blockRows;
    size_t localCol = j % blockCols;

    if (!blocks[blockRow][blockCol]) {
        throw std::runtime_error("Block is not set");
    }

    return (*blocks[blockRow][blockCol])(localRow, localCol);
}

// Возвращает количество строк
template<typename T, template <typename> class MatrixType>
size_t BlockMatrix<T, MatrixType>::rows() const {
    return numBlocksRows * blockRows;
}

// Возвращает количество столбцов
template<typename T, template <typename> class MatrixType>
size_t BlockMatrix<T, MatrixType>::cols() const {
    return numBlocksCols * blockCols;
}

// Метод для вывода всей блочной матрицы
template<typename T, template <typename> class MatrixType>
void BlockMatrix<T, MatrixType>::Print() const {
    std::cout << "Block Matrix:\n";
    for (size_t i = 0; i < numBlocksRows; ++i) {
        for (size_t j = 0; j < numBlocksCols; ++j) {
            std::cout << "Block [" << i << "][" << j << "]:\n";
            if (blocks[i][j]) { // Если блок установлен, печатаем его
                blocks[i][j]->Print();
            }
            else {
                std::cout << "Block is empty\n";
            }
        }
        std::cout << std::endl;
    }
}

// Оператор сложения
template<typename T, template <typename> class MatrixType>
BlockMatrix<T, MatrixType> BlockMatrix<T, MatrixType>::operator+(const BlockMatrix<T, MatrixType>& other) const {
    if (numBlocksRows != other.numBlocksRows || numBlocksCols != other.numBlocksCols) {
        throw std::invalid_argument("Block matrices must have the same dimensions for addition.");
    }

    BlockMatrix<T, MatrixType> result(blockRows, blockCols, rows(), cols());

    for (size_t i = 0; i < numBlocksRows; ++i) {
        for (size_t j = 0; j < numBlocksCols; ++j) {
            if (blocks[i][j] && other.blocks[i][j]) {
                result.setBlock(i, j, new MatrixType<T>(*(blocks[i][j]) + *(other.blocks[i][j])));
            }
            else if (blocks[i][j]) {
                result.setBlock(i, j, new MatrixType<T>(*(blocks[i][j])));
            }
            else if (other.blocks[i][j]) {
                result.setBlock(i, j, new MatrixType<T>(*(other.blocks[i][j])));
            }
        }
    }

    return result;
}

// Оператор вычитания
template<typename T, template <typename> class MatrixType>
BlockMatrix<T, MatrixType> BlockMatrix<T, MatrixType>::operator-(const BlockMatrix<T, MatrixType>& other) const {
    if (numBlocksRows != other.numBlocksRows || numBlocksCols != other.numBlocksCols) {
        throw std::invalid_argument("Block matrices must have the same dimensions for subtraction.");
    }

    BlockMatrix<T, MatrixType> result(blockRows, blockCols, rows(), cols());

    for (size_t i = 0; i < numBlocksRows; ++i) {
        for (size_t j = 0; j < numBlocksCols; ++j) {
            if (blocks[i][j] && other.blocks[i][j]) {
                result.setBlock(i, j, new MatrixType<T>(*(blocks[i][j]) - *(other.blocks[i][j])));
            }
            else if (blocks[i][j]) {
                result.setBlock(i, j, new MatrixType<T>(*(blocks[i][j])));
            }
            else if (other.blocks[i][j]) {
                result.setBlock(i, j, new MatrixType<T>(*(other.blocks[i][j])));
            }
        }
    }

    return result;
}

template<typename T, template <typename> class MatrixType>
BlockMatrix<T, MatrixType> BlockMatrix<T, MatrixType>::operator*(const BlockMatrix<T, MatrixType>& other) const {
    if (cols() != other.rows()) {
        throw std::invalid_argument("Incompatible block matrix dimensions for multiplication.");
    }

    BlockMatrix<T, MatrixType> result(blockRows, other.blockCols, rows(), other.cols());

    for (size_t i = 0; i < numBlocksRows; ++i) {
        for (size_t j = 0; j < other.numBlocksCols; ++j) {
            result.setBlock(i, j, new MatrixType<T>(blockRows, other.blockCols)); // Создаем новый блок для результата
            for (size_t k = 0; k < numBlocksCols; ++k) {
                if (blocks[i][k] && other.blocks[k][j]) {
                    *result.blocks[i][j] = *result.blocks[i][j] + (*(blocks[i][k]) * (*(other.blocks[k][j])));
                }
            }
        }
    }

    return result;
}

// Метод для вычисления произведения Кронекера
//template<typename T, template <typename> class MatrixType>
//BlockMatrix<T, MatrixType> BlockMatrix<T, MatrixType>::kroneckerProduct(const BlockMatrix<T, MatrixType>& other) const {
//    size_t newM = blocks.size() * other.blocks.size(); // Новое количество строк
//    size_t newN = blocks[0].size() * other.blocks[0].size(); // Новое количество столбцов
//
//    // Получим размер блоков
//    size_t blockRows = blocks[0][0]->rows(); // Количество строк в блоках
//    size_t blockCols = blocks[0][0]->cols(); // Количество столбцов в блоках
//
//    // Результирующая блочная матрица будет содержать информацию о каждом блоке
//    BlockMatrix<T, MatrixType> result(newM, newN);
//
//    // Итерация по всем блокам текущей и другой блочной матрицы
//    for (size_t i = 0; i < blocks.size(); ++i) {
//        for (size_t j = 0; j < blocks[i].size(); ++j) {
//            if (blocks[i][j]) { // Проверяем, установлен ли блок
//                const MatrixType<T>& aBlock = *blocks[i][j];
//
//                for (size_t k = 0; k < other.blocks.size(); ++k) {
//                    for (size_t l = 0; l < other.blocks[k].size(); ++l) {
//                        if (other.blocks[k][l]) { // Проверяем, установлен ли блок другой матрицы
//                            const MatrixType<T>& bBlock = *other.blocks[k][l];
//
//                            for (size_t bi = 0; bi < blockRows; ++bi) {
//                                for (size_t bj = 0; bj < blockCols; ++bj) {
//                                    // Вычисление произведения элемент-wise
//                                    T value = aBlock(bi, bj) * bBlock(bi, bj);
//
//                                    // Вычисление индексов для результирующей матрицы
//                                    size_t resultRow = i * other.blocks.size() + k;
//                                    size_t resultCol = j * other.blocks[0].size() + l;
//
//                                    // Запись значения в результирующую блочную матрицу
//                                    result(resultRow, resultCol)(bi, bj) = value;
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//    return result; // Возвращает результирующую блочную матрицу
//}


template class BlockMatrix<int, DenseMatrix>;                      // int: 32-битное целое число (в большинстве сред).
//template class BlockMatrix<unsigned int>;              // unsigned int: Беззнаковое 32-битное целое число.
//template class BlockMatrix<short>;                     // short: Обычно 16-битное целое число.
//template class BlockMatrix<unsigned short>;            // unsigned short: Беззнаковое 16-битное целое число.
//template class BlockMatrix<long>;                       // long: Обычно 32-битное целое, но в некоторых средах это 64-битное целое (например, на 64-разрядных системах).
//template class BlockMatrix<unsigned long>;              // unsigned long: Беззнаковое представление long.
//template class BlockMatrix<long long>;                 // long long: Гарантирует минимум 64 бита.
//template class BlockMatrix<unsigned long long>;        // unsigned long long: Беззнаковое представление long long.
//template class BlockMatrix<float>;                      // float: Обычно 32-битное представление числа с плавающей точкой.
template class BlockMatrix<double, DenseMatrix>;                     // double: Обычно 64-битное представление числа с плавающей точкой.
//template class BlockMatrix<long double>;                // long double: Обычно расширенное представление числа с плавающей точкой, минимум 80 бит.

