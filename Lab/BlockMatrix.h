#pragma once // Защита от многократного подключения файла

#include "Matrix.h"
#include "DenseMatrix.h"
#include "DiagonalMatrix.h"
#include <vector>
#include <stdexcept>
#include <iostream>

template <typename T, template<typename> class MatrixType>
class BlockMatrix : public Matrix<T> {
private:
    size_t blockRows_, blockCols_;
    size_t blockSizeRows_, blockSizeCols_;
    std::vector<std::vector<MatrixType<T>*>> blocks;

public:
    BlockMatrix(size_t blockRows, size_t blockCols, size_t blockSizeRows, size_t blockSizeCols)
        : blockRows_(blockRows), blockCols_(blockCols),
        blockSizeRows_(blockSizeRows), blockSizeCols_(blockSizeCols),
        blocks(blockRows, std::vector<MatrixType<T>*>(blockCols, nullptr)) {}

    ~BlockMatrix() {
        for (size_t i = 0; i < blockRows_; ++i) {
            for (size_t j = 0; j < blockCols_; ++j) {
                delete blocks[i][j];
            }
        }
    }

    void setBlock(size_t row, size_t col, MatrixType<T>* block) {
        if (row >= blockRows_ || col >= blockCols_) {
            throw std::out_of_range("Block index out of range");
        }
        delete blocks[row][col];
        blocks[row][col] = block;
    }

    T& operator()(size_t i, size_t j) {
        size_t blockRowIdx = i / blockSizeRows_;
        size_t blockColIdx = j / blockSizeCols_;
        size_t internalRowIdx = i % blockSizeRows_;
        size_t internalColIdx = j % blockSizeCols_;

        if (blocks[blockRowIdx][blockColIdx]) {
            return (*blocks[blockRowIdx][blockColIdx])(internalRowIdx, internalColIdx);
        }
        else {
            throw std::out_of_range("Block not set");
        }
    }

    const T& operator()(size_t i, size_t j) const {
        size_t blockRowIdx = i / blockSizeRows_;
        size_t blockColIdx = j / blockSizeCols_;
        size_t internalRowIdx = i % blockSizeRows_;
        size_t internalColIdx = j % blockSizeCols_;

        if (blocks[blockRowIdx][blockColIdx]) {
            return (*blocks[blockRowIdx][blockColIdx])(internalRowIdx, internalColIdx);
        }
        else {
            throw std::out_of_range("Block not set");
        }
    }

    size_t rows() const override {
        return blockRows_ * blockSizeRows_;
    }

    size_t cols() const override {
        return blockCols_ * blockSizeCols_;
    }

    BlockMatrix operator+(const BlockMatrix& other) const {
        BlockMatrix result(blockRows_, blockCols_, blockSizeRows_, blockSizeCols_);
        for (size_t i = 0; i < blockRows_; ++i) {
            for (size_t j = 0; j < blockCols_; ++j) {
                if (blocks[i][j] && other.blocks[i][j]) {
                    result.blocks[i][j] = new MatrixType<T>(*blocks[i][j] + *other.blocks[i][j]);
                }
            }
        }
        return result;
    }

    BlockMatrix operator-(const BlockMatrix& other) const {
        BlockMatrix result(blockRows_, blockCols_, blockSizeRows_, blockSizeCols_);
        for (size_t i = 0; i < blockRows_; ++i) {
            for (size_t j = 0; j < blockCols_; ++j) {
                if (blocks[i][j] && other.blocks[i][j]) {
                    result.blocks[i][j] = new MatrixType<T>(*blocks[i][j] - *other.blocks[i][j]);
                }
            }
        }
        return result;
    }

    BlockMatrix operator*(const BlockMatrix& other) const {
        if (blockCols_ != other.blockRows_) {
            throw std::invalid_argument("Block matrices have incompatible dimensions for multiplication");
        }

        BlockMatrix result(blockRows_, other.blockCols_, blockSizeRows_, other.blockSizeCols_);
        for (size_t i = 0; i < blockRows_; ++i) {
            for (size_t j = 0; j < other.blockCols_; ++j) {
                for (size_t k = 0; k < blockCols_; ++k) {
                    if (blocks[i][k] && other.blocks[k][j]) {
                        if (!result.blocks[i][j]) {
                            result.blocks[i][j] = new MatrixType<T>(*blocks[i][k] * *other.blocks[k][j]);
                        }
                        else {
                            *result.blocks[i][j] = *result.blocks[i][j] + (*blocks[i][k] * *other.blocks[k][j]);
                        }
                    }
                }
            }
        }
        return result;
    }

    void Print() const override {
        for (size_t i = 0; i < rows(); ++i) {
            for (size_t j = 0; j < cols(); ++j) {
                std::cout << operator()(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }

    BlockMatrix<T, MatrixType> kroneckerProduct(const BlockMatrix<T, MatrixType>& other) const;
};

template<typename T, template <typename> class MatrixType>
BlockMatrix<T, MatrixType> BlockMatrix<T, MatrixType>::kroneckerProduct(const BlockMatrix<T, MatrixType>& other) const {
    size_t resultBlockRows = blockRows_ * other.blockRows_;
    size_t resultBlockCols = blockCols_ * other.blockCols_;
    size_t internalRows = blockSizeRows_ * other.blockSizeRows_;
    size_t internalCols = blockSizeCols_ * other.blockSizeCols_;

    BlockMatrix<T, MatrixType> result(resultBlockRows, resultBlockCols, internalRows, internalCols);

    for (size_t i = 0; i < blockRows_; ++i) {
        for (size_t j = 0; j < blockCols_; ++j) {
            if (blocks[i][j]) {
                const MatrixType<T>& aBlock = *blocks[i][j];

                for (size_t k = 0; k < other.blockRows_; ++k) {
                    for (size_t l = 0; l < other.blockCols_; ++l) {
                        if (other.blocks[k][l]) {
                            const MatrixType<T>& bBlock = *other.blocks[k][l];

                            MatrixType<T>* blockProduct;
                            if constexpr (std::is_same<MatrixType<T>, DiagonalMatrix<T>>::value) {
                                size_t blockSize = blockSizeRows_ * other.blockSizeRows_; // Квадратная форма
                                blockProduct = new DiagonalMatrix<T>(blockSize);
                            }
                            else {
                                blockProduct = new DenseMatrix<T>(blockSizeRows_ * other.blockSizeRows_, blockSizeCols_ * other.blockSizeCols_);
                            }

                            for (size_t bi = 0; bi < blockSizeRows_; ++bi) {
                                for (size_t bj = 0; bj < blockSizeCols_; ++bj) {
                                    for (size_t bk = 0; bk < other.blockSizeRows_; ++bk) {
                                        for (size_t bl = 0; bl < other.blockSizeCols_; ++bl) {
                                            (*blockProduct)(bi * other.blockSizeRows_ + bk, bj * other.blockSizeCols_ + bl) =
                                                aBlock(bi, bj) * bBlock(bk, bl);
                                        }
                                    }
                                }
                            }

                            size_t resultBlockRow = i * other.blockRows_ + k;
                            size_t resultBlockCol = j * other.blockCols_ + l;

                            result.setBlock(resultBlockRow, resultBlockCol, blockProduct);
                        }
                    }
                }
            }
        }
    }
    return result;
}





