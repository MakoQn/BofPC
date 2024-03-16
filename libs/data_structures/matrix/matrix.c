# ifndef INC_MATRIX_H
# define INC_MATRIX_H

#include "matrix.h"
# include <malloc.h>
# include <stdint.h>

typedef struct matrix {
    int **values; // элементы матрицы
    int nRows; // количество рядов
    int nCols; // количество столбцов
} matrix;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;

//размещает в динамической памяти матрицу размером nRows на nCols.
matrix getMemMatrix(int nRows, int nCols){
    int **values = (int **) malloc(sizeof(int*) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix){values, nRows, nCols};
}

//размещает в динамической памяти массив из nMatrices матриц размером nRows на nCols.
matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols){
    matrix *ms = (matrix*) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

// освобождает память, выделенную под хранение матрицы m.
void freeMemMatrix(matrix *m){
    for (int i = 0; i < m->nRows;i++)
        free(m->values[i]);

    free(m->values);

    m->values == NULL;
    m->nRows = 0;
    m->nCols = 0;
}

//освобождает память, выделенную под хранение массива ms из nMatrices матриц.
void freeMemMatrices(matrix *ms, int nMatrices){
    for (int i = 0; i < nMatrices; i++)
        freeMemMatrix(&ms[i]);
}

# endif