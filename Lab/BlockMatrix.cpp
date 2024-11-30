#include "BlockMatrix.h"

// Конструктор
template<typename T, template <typename> class MatrixType>
BlockMatrix<T, MatrixType>::BlockMatrix(size_t blockRows, size_t blockCols, size_t blockSizeRows, size_t blockSizeCols)
    : _RowsBlock(blockRows), _ColsBlock(blockCols),
    _FullRowsBlockSize(blockSizeRows), _FullColsBlockSize(blockSizeCols),
    blocks(blockRows, std::vector<MatrixType<T>*>(blockCols, nullptr)) {}

// Деструктор
template<typename T, template <typename> class MatrixType>
BlockMatrix<T, MatrixType>::~BlockMatrix() {
    for (size_t i = 0; i < _RowsBlock; ++i) {
        for (size_t j = 0; j < _ColsBlock; ++j) {
            delete blocks[i][j];
        }
    }
}

// Создание блока
template<typename T, template <typename> class MatrixType>
void BlockMatrix<T, MatrixType>::CreateBlock(size_t row, size_t col, MatrixType<T>* block) {
    if (row >= _RowsBlock || col >= _ColsBlock) {
        throw std::out_of_range("Индекс блока вышел за диапазон");
    }
    delete blocks[row][col];
    blocks[row][col] = block;
}

// Модифицируемый оператор ()
template<typename T, template <typename> class MatrixType>
T& BlockMatrix<T, MatrixType>::operator()(size_t i, size_t j) {
    /*Т.к. блоки установлены в единую матрицу, то доступ к ним будет в единой матрице, а не по отдельным блокам*/
    if (blocks[i / _FullRowsBlockSize][j / _FullColsBlockSize]) {
        return (*blocks[i / _FullRowsBlockSize][j / _FullColsBlockSize])(i % _FullRowsBlockSize, j % _FullColsBlockSize);
    }
    else {
        throw std::out_of_range("Запрашиваемого блока в матрице нет");
    }
}

//Константный оператор ()
template<typename T, template <typename> class MatrixType>
const T& BlockMatrix<T, MatrixType>::operator()(size_t i, size_t j) const {
    if (blocks[i / _FullRowsBlockSize][j / _FullColsBlockSize]) {
        return (*blocks[i / _FullRowsBlockSize][j / _FullColsBlockSize])(i % _FullRowsBlockSize, j % _FullColsBlockSize);
    }
    else {
        throw std::out_of_range("Запрашиваемого блока в матрице нет");
    }
}

// Возвращает количество строк
template<typename T, template <typename> class MatrixType>
size_t BlockMatrix<T, MatrixType>::rows() const {
    return _RowsBlock * _FullRowsBlockSize;
}

// Возвращает количество столбцов
template<typename T, template <typename> class MatrixType>
size_t BlockMatrix<T, MatrixType>::cols() const {
    return _ColsBlock * _FullColsBlockSize;
}

// Оператор сложения
template<typename T, template <typename> class MatrixType>
BlockMatrix<T, MatrixType> BlockMatrix<T, MatrixType>::operator+(const BlockMatrix& other) const {
    // Проверка: совпадает ли количество блоков и размеры каждого блока
    if (_RowsBlock != other._RowsBlock) {
        throw std::runtime_error("Не совпадает количество блоков по строкам");
    }

    if (_ColsBlock != other._ColsBlock) {
        throw std::runtime_error("Не совпадает количество блоков по столбцам");
    }

    if (_FullRowsBlockSize != other._FullRowsBlockSize) {
        throw std::runtime_error("Не совпадают размеры блоков по строкам");
    }

    if (_FullColsBlockSize != other._FullColsBlockSize) {
        throw std::runtime_error("Не совпадают размеры блоков по столбцам");
    }
    BlockMatrix result(_RowsBlock, _ColsBlock, _FullRowsBlockSize, _FullColsBlockSize);
    for (size_t i = 0; i < _RowsBlock; ++i) {
        for (size_t j = 0; j < _ColsBlock; ++j) {
            if (blocks[i][j] && other.blocks[i][j]) {
                result.blocks[i][j] = new MatrixType<T>(*blocks[i][j] + *other.blocks[i][j]);
            }
        }
    }
    return result;
}

// Оператор вычитания
template<typename T, template <typename> class MatrixType>
BlockMatrix<T, MatrixType> BlockMatrix<T, MatrixType>::operator-(const BlockMatrix& other) const {
    // Проверка: совпадает ли количество блоков и размеры каждого блока
    if (_RowsBlock != other._RowsBlock) {
        throw std::runtime_error("Не совпадает количество блоков по строкам");
    }

    if (_ColsBlock != other._ColsBlock) {
        throw std::runtime_error("Не совпадает количество блоков по столбцам");
    }

    if (_FullRowsBlockSize != other._FullRowsBlockSize) {
        throw std::runtime_error("Не совпадают размеры блоков по строкам");
    }

    if (_FullColsBlockSize != other._FullColsBlockSize) {
        throw std::runtime_error("Не совпадают размеры блоков по столбцам");
    }
    BlockMatrix result(_RowsBlock, _ColsBlock, _FullRowsBlockSize, _FullColsBlockSize);
    for (size_t i = 0; i < _RowsBlock; ++i) {
        for (size_t j = 0; j < _ColsBlock; ++j) {
            if (blocks[i][j] && other.blocks[i][j]) {
                result.blocks[i][j] = new MatrixType<T>(*blocks[i][j] - *other.blocks[i][j]);
            }
        }
    }
    return result;
}

// Метод для вывода всей блочной матрицы
template<typename T, template <typename> class MatrixType>
void BlockMatrix<T, MatrixType>::Print() const {
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < cols(); ++j) {
            std::cout << operator()(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

//Метод Кронекера
template<typename T, template <typename> class MatrixType>
BlockMatrix<T, MatrixType> BlockMatrix<T, MatrixType>::kroneckerProduct(const BlockMatrix<T, MatrixType>& other) const {
    size_t resultBlockRows = _RowsBlock * other._RowsBlock;
    size_t resultBlockCols = _ColsBlock * other._ColsBlock;
    size_t internalRows = _FullRowsBlockSize * other._FullRowsBlockSize;
    size_t internalCols = _FullColsBlockSize * other._FullColsBlockSize;

    BlockMatrix<T, MatrixType> result(resultBlockRows, resultBlockCols, internalRows, internalCols);

    for (size_t i = 0; i < _RowsBlock; ++i) {
        for (size_t j = 0; j < _ColsBlock; ++j) {
            if (blocks[i][j]) {
                const MatrixType<T>& aBlock = *blocks[i][j];

                for (size_t k = 0; k < other._RowsBlock; ++k) {
                    for (size_t l = 0; l < other._ColsBlock; ++l) {
                        if (other.blocks[k][l]) {
                            const MatrixType<T>& bBlock = *other.blocks[k][l];

                            MatrixType<T>* blockProduct;
                            if constexpr (std::is_same<MatrixType<T>, DiagonalMatrix<T>>::value) {
                                size_t blockSize = _FullRowsBlockSize * other._FullRowsBlockSize; // Квадратная форма
                                blockProduct = new DiagonalMatrix<T>(blockSize);
                            }
                            else {
                                blockProduct = new DenseMatrix<T>(_FullRowsBlockSize * other._FullRowsBlockSize, _FullColsBlockSize * other._FullColsBlockSize);
                            }

                            for (size_t bi = 0; bi < _FullRowsBlockSize; ++bi) {
                                for (size_t bj = 0; bj < _FullColsBlockSize; ++bj) {
                                    for (size_t bk = 0; bk < other._FullRowsBlockSize; ++bk) {
                                        for (size_t bl = 0; bl < other._FullColsBlockSize; ++bl) {
                                            (*blockProduct)(bi * other._FullRowsBlockSize + bk, bj * other._FullColsBlockSize + bl) =
                                                aBlock(bi, bj) * bBlock(bk, bl);
                                        }
                                    }
                                }
                            }

                            size_t resultBlockRow = i * other._RowsBlock + k;
                            size_t resultBlockCol = j * other._ColsBlock + l;

                            result.CreateBlock(resultBlockRow, resultBlockCol, blockProduct);
                        }
                    }
                }
            }
        }
    }
    return result;
}

// Явная инстанциация для стандартных числовых типов и двух типов матриц DiagonalMatrix и DenseMatrix.

//Для DenseMatrix

template class BlockMatrix<int, DenseMatrix>;                       // int: 32-битное целое число (в большинстве сред).
template class BlockMatrix<unsigned int, DenseMatrix>;              // unsigned int: Беззнаковое 32-битное целое число.
template class BlockMatrix<short, DenseMatrix>;                     // short: Обычно 16-битное целое число.
template class BlockMatrix<unsigned short, DenseMatrix>;            // unsigned short: Беззнаковое 16-битное целое число.
template class BlockMatrix<long, DenseMatrix>;                       // long: Обычно 32-битное целое, но в некоторых средах это 64-битное целое (например, на 64-разрядных системах).
template class BlockMatrix<unsigned long, DenseMatrix>;              // unsigned long: Беззнаковое представление long.
template class BlockMatrix<long long, DenseMatrix>;                 // long long: Гарантирует минимум 64 бита.
template class BlockMatrix<unsigned long long, DenseMatrix>;        // unsigned long long: Беззнаковое представление long long.
template class BlockMatrix<float, DenseMatrix>;                      // float: Обычно 32-битное представление числа с плавающей точкой.
template class BlockMatrix<double, DenseMatrix>;                     // double: Обычно 64-битное представление числа с плавающей точкой.
template class BlockMatrix<long double, DenseMatrix>;                // long double: Обычно расширенное представление числа с плавающей точкой, минимум 80 бит.

//Для DiagonalMatrix

template class BlockMatrix<int, DiagonalMatrix>;                       // int: 32-битное целое число (в большинстве сред).
template class BlockMatrix<unsigned int, DiagonalMatrix>;              // unsigned int: Беззнаковое 32-битное целое число.
template class BlockMatrix<short, DiagonalMatrix>;                     // short: Обычно 16-битное целое число.
template class BlockMatrix<unsigned short, DiagonalMatrix>;            // unsigned short: Беззнаковое 16-битное целое число.
template class BlockMatrix<long, DiagonalMatrix>;                       // long: Обычно 32-битное целое, но в некоторых средах это 64-битное целое (например, на 64-разрядных системах).
template class BlockMatrix<unsigned long, DiagonalMatrix>;              // unsigned long: Беззнаковое представление long.
template class BlockMatrix<long long, DiagonalMatrix>;                 // long long: Гарантирует минимум 64 бита.
template class BlockMatrix<unsigned long long, DiagonalMatrix>;        // unsigned long long: Беззнаковое представление long long.
template class BlockMatrix<float, DiagonalMatrix>;                      // float: Обычно 32-битное представление числа с плавающей точкой.
template class BlockMatrix<double, DiagonalMatrix>;                     // double: Обычно 64-битное представление числа с плавающей точкой.
template class BlockMatrix<long double, DiagonalMatrix>;                // long double: Обычно расширенное представление числа с плавающей точкой, минимум 80 бит.