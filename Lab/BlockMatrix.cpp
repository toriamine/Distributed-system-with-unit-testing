#include "BlockMatrix.h"

// �����������
template<typename T, template <typename> class MatrixType>
BlockMatrix<T, MatrixType>::BlockMatrix(size_t blockRows, size_t blockCols, size_t blockSizeRows, size_t blockSizeCols)
    : _RowsBlock(blockRows), _ColsBlock(blockCols),
    _FullRowsBlockSize(blockSizeRows), _FullColsBlockSize(blockSizeCols),
    blocks(blockRows, std::vector<MatrixType<T>*>(blockCols, nullptr)) {}

// ����������
template<typename T, template <typename> class MatrixType>
BlockMatrix<T, MatrixType>::~BlockMatrix() {
    for (size_t i = 0; i < _RowsBlock; ++i) {
        for (size_t j = 0; j < _ColsBlock; ++j) {
            delete blocks[i][j];
        }
    }
}

// �������� �����
template<typename T, template <typename> class MatrixType>
void BlockMatrix<T, MatrixType>::CreateBlock(size_t row, size_t col, MatrixType<T>* block) {
    if (row >= _RowsBlock || col >= _ColsBlock) {
        throw std::out_of_range("������ ����� ����� �� ��������");
    }
    delete blocks[row][col];
    blocks[row][col] = block;
}

// �������������� �������� ()
template<typename T, template <typename> class MatrixType>
T& BlockMatrix<T, MatrixType>::operator()(size_t i, size_t j) {
    /*�.�. ����� ����������� � ������ �������, �� ������ � ��� ����� � ������ �������, � �� �� ��������� ������*/
    if (blocks[i / _FullRowsBlockSize][j / _FullColsBlockSize]) {
        return (*blocks[i / _FullRowsBlockSize][j / _FullColsBlockSize])(i % _FullRowsBlockSize, j % _FullColsBlockSize);
    }
    else {
        throw std::out_of_range("�������������� ����� � ������� ���");
    }
}

//����������� �������� ()
template<typename T, template <typename> class MatrixType>
const T& BlockMatrix<T, MatrixType>::operator()(size_t i, size_t j) const {
    if (blocks[i / _FullRowsBlockSize][j / _FullColsBlockSize]) {
        return (*blocks[i / _FullRowsBlockSize][j / _FullColsBlockSize])(i % _FullRowsBlockSize, j % _FullColsBlockSize);
    }
    else {
        throw std::out_of_range("�������������� ����� � ������� ���");
    }
}

// ���������� ���������� �����
template<typename T, template <typename> class MatrixType>
size_t BlockMatrix<T, MatrixType>::rows() const {
    return _RowsBlock * _FullRowsBlockSize;
}

// ���������� ���������� ��������
template<typename T, template <typename> class MatrixType>
size_t BlockMatrix<T, MatrixType>::cols() const {
    return _ColsBlock * _FullColsBlockSize;
}

// �������� ��������
template<typename T, template <typename> class MatrixType>
BlockMatrix<T, MatrixType> BlockMatrix<T, MatrixType>::operator+(const BlockMatrix& other) const {
    // ��������: ��������� �� ���������� ������ � ������� ������� �����
    if (_RowsBlock != other._RowsBlock) {
        throw std::runtime_error("�� ��������� ���������� ������ �� �������");
    }

    if (_ColsBlock != other._ColsBlock) {
        throw std::runtime_error("�� ��������� ���������� ������ �� ��������");
    }

    if (_FullRowsBlockSize != other._FullRowsBlockSize) {
        throw std::runtime_error("�� ��������� ������� ������ �� �������");
    }

    if (_FullColsBlockSize != other._FullColsBlockSize) {
        throw std::runtime_error("�� ��������� ������� ������ �� ��������");
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

// �������� ���������
template<typename T, template <typename> class MatrixType>
BlockMatrix<T, MatrixType> BlockMatrix<T, MatrixType>::operator-(const BlockMatrix& other) const {
    // ��������: ��������� �� ���������� ������ � ������� ������� �����
    if (_RowsBlock != other._RowsBlock) {
        throw std::runtime_error("�� ��������� ���������� ������ �� �������");
    }

    if (_ColsBlock != other._ColsBlock) {
        throw std::runtime_error("�� ��������� ���������� ������ �� ��������");
    }

    if (_FullRowsBlockSize != other._FullRowsBlockSize) {
        throw std::runtime_error("�� ��������� ������� ������ �� �������");
    }

    if (_FullColsBlockSize != other._FullColsBlockSize) {
        throw std::runtime_error("�� ��������� ������� ������ �� ��������");
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

// ����� ��� ������ ���� ������� �������
template<typename T, template <typename> class MatrixType>
void BlockMatrix<T, MatrixType>::Print() const {
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < cols(); ++j) {
            std::cout << operator()(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

//����� ���������
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
                                size_t blockSize = _FullRowsBlockSize * other._FullRowsBlockSize; // ���������� �����
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

// ����� ������������ ��� ����������� �������� ����� � ���� ����� ������ DiagonalMatrix � DenseMatrix.

//��� DenseMatrix

template class BlockMatrix<int, DenseMatrix>;                       // int: 32-������ ����� ����� (� ����������� ����).
template class BlockMatrix<unsigned int, DenseMatrix>;              // unsigned int: ����������� 32-������ ����� �����.
template class BlockMatrix<short, DenseMatrix>;                     // short: ������ 16-������ ����� �����.
template class BlockMatrix<unsigned short, DenseMatrix>;            // unsigned short: ����������� 16-������ ����� �����.
template class BlockMatrix<long, DenseMatrix>;                       // long: ������ 32-������ �����, �� � ��������� ������ ��� 64-������ ����� (��������, �� 64-��������� ��������).
template class BlockMatrix<unsigned long, DenseMatrix>;              // unsigned long: ����������� ������������� long.
template class BlockMatrix<long long, DenseMatrix>;                 // long long: ����������� ������� 64 ����.
template class BlockMatrix<unsigned long long, DenseMatrix>;        // unsigned long long: ����������� ������������� long long.
template class BlockMatrix<float, DenseMatrix>;                      // float: ������ 32-������ ������������� ����� � ��������� ������.
template class BlockMatrix<double, DenseMatrix>;                     // double: ������ 64-������ ������������� ����� � ��������� ������.
template class BlockMatrix<long double, DenseMatrix>;                // long double: ������ ����������� ������������� ����� � ��������� ������, ������� 80 ���.

//��� DiagonalMatrix

template class BlockMatrix<int, DiagonalMatrix>;                       // int: 32-������ ����� ����� (� ����������� ����).
template class BlockMatrix<unsigned int, DiagonalMatrix>;              // unsigned int: ����������� 32-������ ����� �����.
template class BlockMatrix<short, DiagonalMatrix>;                     // short: ������ 16-������ ����� �����.
template class BlockMatrix<unsigned short, DiagonalMatrix>;            // unsigned short: ����������� 16-������ ����� �����.
template class BlockMatrix<long, DiagonalMatrix>;                       // long: ������ 32-������ �����, �� � ��������� ������ ��� 64-������ ����� (��������, �� 64-��������� ��������).
template class BlockMatrix<unsigned long, DiagonalMatrix>;              // unsigned long: ����������� ������������� long.
template class BlockMatrix<long long, DiagonalMatrix>;                 // long long: ����������� ������� 64 ����.
template class BlockMatrix<unsigned long long, DiagonalMatrix>;        // unsigned long long: ����������� ������������� long long.
template class BlockMatrix<float, DiagonalMatrix>;                      // float: ������ 32-������ ������������� ����� � ��������� ������.
template class BlockMatrix<double, DiagonalMatrix>;                     // double: ������ 64-������ ������������� ����� � ��������� ������.
template class BlockMatrix<long double, DiagonalMatrix>;                // long double: ������ ����������� ������������� ����� � ��������� ������, ������� 80 ���.