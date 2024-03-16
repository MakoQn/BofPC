# ifndef INC_MATRIX_H
# define INC_MATRIX_H

#include "matrix.h"
# include <malloc.h>
# include <stdint.h>
# include <stdio.h>

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

    m->values = NULL;
    m->nRows = 0;
    m->nCols = 0;
}

//освобождает память, выделенную под хранение массива ms из nMatrices матриц.
void freeMemMatrices(matrix *ms, int nMatrices){
    for (int i = 0; i < nMatrices; i++)
        freeMemMatrix(&ms[i]);
}

//ввод матрицы m.
void inputMatrix(matrix *m){
    for (int i = 0; i < m->nRows;i++){
        printf("%d row\n", i + 1);

        for (int j = 0; j < m->nCols;i++)
            scanf("%d", &m->values[i][j]);
    }

    printf("\n");
}

//ввод массива из nMatrices матриц, хранящейся по адресу ms.
void inputMatrices(matrix *ms, int nMatrices){
    for (int i = 0;i < nMatrices; i++) {
        printf("%d matrix\n", i + 1);
        inputMatrix(&ms[i]);
    }
}

//вывод матрицы m.
void outputMatrix(matrix m){
    for (int i = 0; i < m.nRows;i++) {
        for (int j = 0; j < m.nCols; j++)
            printf("%d ", m.values[i][j]);

        printf("\n");
    }
}

// вывод массива из nMatrices матриц, хранящейся по адресу ms.
void outputMatrices(matrix *ms, int nMatrices){
    for (int i = 0; i < nMatrices; i++) {
        printf("%d matrix\n", i + 1);
        outputMatrix(ms[i]);
    }
}

//обмен строк с порядковыми номерами i1 и i2 в матрице m.
void swapRows(matrix m, int i1, int i2){
    int temp = *m.values[i1];

    *m.values[i1] = *m.values[i2];
    *m.values[i2] = temp;
}

//обмен колонок с порядковыми номерами j1 и j2 в матрице m.
void swapColumns(matrix m, int j1, int j2){
    for (int i = 0; i < m.nRows; i++){
        int temp = m.values[i][j1];

        m.values[i][j1] = m.values[i][j2];
        m.values[i][j2] = temp;
    }
}

# endif