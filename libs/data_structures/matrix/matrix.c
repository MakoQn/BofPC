# ifndef INC_MATRIX_H
# define INC_MATRIX_H

#include "matrix.h"
# include <malloc.h>
# include <stdint.h>
# include <stdio.h>
# include <assert.h>

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
    assert((i1 < m.nRows) && (i2 < m.nRows) && (i1 > -1) && (i2 > -1));

    int temp = *m.values[i1];

    *m.values[i1] = *m.values[i2];
    *m.values[i2] = temp;
}

//обмен колонок с порядковыми номерами j1 и j2 в матрице m.
void swapColumns(matrix m, int j1, int j2){
    assert((j1 < m.nCols) && (j2 < m.nCols) && (j1 > -1) && (j2 > -1));

    for (int i = 0; i < m.nRows; i++){
        int temp = m.values[i][j1];

        m.values[i][j1] = m.values[i][j2];
        m.values[i][j2] = temp;
    }
}

//возвращает сумму элементов массива.
int getSum(int *a, int n){
    int sum = 0;

    for (int i = 0; i < n; i++)
        sum += a[i];

    return sum;
}

// выполняет сортировку вставками строк матрицы m по неубыванию значения функции criteria применяемой для строк.
void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int)){
    int *criteria_array = (int*)malloc(sizeof(int) * m.nRows);

    for (int i = 0; i < m.nRows; i++)
        criteria_array[i] = criteria(m.values[i], m.nCols);

    for (size_t i = 1; i < m.nRows; i++){
        int t = criteria_array[i];
        int j = i;

        while (j > 0 && criteria_array[j - 1] > t) {
            criteria_array[j] = criteria_array[j - 1];
            j--;
        }

        criteria_array[j] = t;
        swapRows(m, i, j);
    }

    free(criteria_array);
}

//выполняет сортировку выбором столбцов матрицы m по неубыванию значения функции criteria применяемой для столбцов.
void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int)){
    int *criteria_array = (int*)malloc(sizeof(int) * m.nCols);

    for (int i = 0; i < m.nCols; i++){
        int *col = (int*)malloc(sizeof(int) * m.nRows);

        for (int j = 0; j < m.nRows; i++)
            col[j] = m.values[j][i];

        criteria_array[i] = criteria(col, m.nRows);

        free(col);
    }

    for (int i = 0; i < m.nCols - 1; i++) {
        int minPos = i;

        for (int j = i + 1; j < m.nCols; j++)
            if (criteria_array[j] < criteria_array[minPos])
                minPos = j;

        int temp = criteria_array[i];

        criteria_array[i] = criteria_array[minPos];
        criteria_array[minPos] = temp;

        swapColumns(m, i, minPos);
    }
}

# endif