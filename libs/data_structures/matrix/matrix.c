# ifndef INC_MATRIX_H
# define INC_MATRIX_H

#include "matrix.h"
# include <malloc.h>
# include <stdint.h>
# include <stdio.h>
# include <assert.h>
# include <stdbool.h>
# include <memory.h>

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

    int *temp = m.values[i1];

    m.values[i1] = m.values[i2];
    m.values[i2] = temp;
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

        for (int j = 0; j < m.nRows; j++)
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

//возвращает значение ’истина’, если матрица m является квадратной, ложь – в противном случае.
bool isSquareMatrix(matrix *m){
    return m->nRows == m->nCols;
}

// возвращает значение ’истина’, если матрицы m1 и m2 равны, ложь – в противном случае.
bool areTwoMatricesEqual(matrix *m1, matrix *m2){
    if (!((m1->nRows == m2->nRows) && (m1->nCols == m2->nCols)))
        return 0;

    for (int i = 0; i < m1->nRows; i++)
        if (memcmp(m1->values[i], m2->values[i], sizeof(int) * m1->nCols) != 0)
            return 0;

    return 1;
}

//возвращает значение ’истина’, если матрица m является единичной, ложь – в противном случае.
bool isEMatrix(matrix *m){
    if (!isSquareMatrix(m))
        return 0;

    for (int i = 0; i < m->nRows; i++)
        for (int j = 0; j < m->nCols; j++){
            if ((i == j && m->values[i][j] != 1) || (i != j && m->values[i][j] != 0))
                return 0;
        }

    return 1;
}

//возвращает значение ’истина’, если матрица m является симметричной, ложь – в противном случае.
bool isSymmetricMatrix(matrix *m){
    if (!isSquareMatrix(m))
        return 0;

    for (int i = 0; i < m->nRows; i++)
        for (int j = 0; j < m->nCols; j++){
            if ((i < j) && (m->values[i][j] != m->values[j][i]))
                return 0;
        }

    return 1;
}

//транспонирует квадратную матрицу m.
void transposeSquareMatrix(matrix *m){
    assert(isSquareMatrix(m));

    for (int i = 0; i < m->nRows; i++)
        for (int j = 0; j < m->nCols; j++)
            if (i < j){
                int temp = m->values[i][j];

                m->values[i][j] = m->values[j][i];
                m->values[j][i] = temp;
            }
}

//транспонирует матрицу m.
void transposeMatrix(matrix *m){
    if (isSquareMatrix(m))
        transposeSquareMatrix(m);

    if (m->nRows < m->nCols){
        m->values = (int*)realloc(m->values, sizeof(int) * m->nCols);
        for (int i = m->nRows; i < m->nCols; i++)
            m->values[i] = (int*) calloc(m->nCols, sizeof(int));
        int temp = m->nRows;

        m->nRows = m->nCols;

        transposeSquareMatrix(m);

        m->nCols = temp;

        for (int i = 0; i < m->nRows; i++)
            m->values[i] = (int *) realloc(m->values[i], sizeof(int) * m->nCols);
    }else{
        for (int i = 0; i < m->nRows; i++) {
            m->values[i] = (int *) realloc(m->values[i], sizeof(int) * m->nRows);

            for (int j = m->nCols; j < m->nRows; j++)
                m->values[i][j] = 0;
        }

        int temp = m->nCols;

        m->nCols = m->nRows;

        transposeSquareMatrix(m);

        m->nRows = temp;

        for (int i = m->nRows; i < m->nCols;i++)
            free(m->values[i]);

        m->values = (int*)realloc(m->values, sizeof(int) * m->nRows);
    }
}

//возвращает позицию минимального элемента матрицы m.
position getMinValuePos(matrix m){
    int min = INT_MAX;
    position pos;

    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; j++)
            if (m.values[i][j] < min) {
                min = m.values[i][j];
                pos.rowIndex = i;
                pos.colIndex = j;
            }

    return pos;
}

//возвращает позицию максимального элемента матрицы m.
position getMaxValuePos(matrix m){
    int max = INT_MIN;
    position pos;

    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; j++)
            if (m.values[i][j] > max) {
                max = m.values[i][j];
                pos.rowIndex = i;
                pos.colIndex = j;
            }

    return pos;
}

//возвращает матрицу размера nRows на nCols, построенную из элементов массива a
matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols){
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;

    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];

    return m;
}

//возвращает указатель на нулевую матрицу массива из nMatrices матриц, размещенных
//в динамической памяти, построенных из элементов массива a
matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols){
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int l = 0;

    for (size_t k = 0; k < nMatrices; k++)
        for (size_t i = 0; i < nRows; i++)
            for (size_t j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];

    return ms;
}

void test_swapRows() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1,2,3,
                    4,5,6,
                    7,8,9
            },
            3, 3
    );

    swapRows(m, 1, 2);

    matrix test_m = createMatrixFromArray(
            (int[]) {
                    1,2,3,
                    7,8,9,
                    4,5,6
            },
            3, 3
    );

    assert(areTwoMatricesEqual(&m, &test_m));

    freeMemMatrix(&m);
    freeMemMatrix(&test_m);
}

void test_swapColumns() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1,2,3,
                    4,5,6,
                    7,8,9
            },
            3, 3
    );

    swapColumns(m, 1, 2);

    matrix test_m = createMatrixFromArray(
            (int[]) {
                    1,3,2,
                    4,6,5,
                    7,9,8
            },
            3, 3
    );

    assert(areTwoMatricesEqual(&m, &test_m));

    freeMemMatrix(&m);
    freeMemMatrix(&test_m);
}

int getSum(int *a, int n){
    int sum = 0;

    for (size_t i = 0; i < n; i++)
        sum += a[i];

    return sum;
}

void test_insertionSortRowsMatrixByRowCriteria() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    4,5,6,
                    1,2,3,
                    7,8,9
            },
            3, 3
    );

    insertionSortRowsMatrixByRowCriteria(m, getSum);

    matrix test_m = createMatrixFromArray(
            (int[]) {
                    1,2,3,
                    4,5,6,
                    7,8,9
            },
            3, 3
    );

    assert(areTwoMatricesEqual(&m, &test_m));

    freeMemMatrix(&m);
    freeMemMatrix(&test_m);
}

void test_selectionSortColsMatrixByColCriteria() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1,3,2,
                    4,6,5,
                    7,9,8
            },
            3, 3
    );

    selectionSortColsMatrixByColCriteria(m, getSum);

    matrix test_m = createMatrixFromArray(
            (int[]) {
                    1,2,3,
                    4,5,6,
                    7,8,9
            },
            3, 3
    );

    assert(areTwoMatricesEqual(&m, &test_m));

    freeMemMatrix(&m);
    freeMemMatrix(&test_m);
}

void test_isSquareMatrixT() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1,3,2,
                    4,6,5,
                    7,9,8
            },
            3, 3
    );

    assert(isSquareMatrix(&m));

    freeMemMatrix(&m);
}

void test_isSquareMatrixF() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1,3,
                    4,6,
                    7,9
            },
            3, 2
    );

    assert(!isSquareMatrix(&m));

    freeMemMatrix(&m);
}

void test_isSquareMatrix() {
    test_isSquareMatrixT();
    test_isSquareMatrixF();
}

void test_isEMatrixF1() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1,3,2,
                    4,6,5,
                    7,9,8
            },
            3, 3
    );

    assert(!isEMatrix(&m));

    freeMemMatrix(&m);
}

void test_isEMatrixT() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1,0,0,
                    0,1,0,
                    0,0,1
            },
            3, 3
    );

    assert(isEMatrix(&m));

    freeMemMatrix(&m);
}

void test_isEMatrixF2() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1,0,
                    0,1,
                    0,0
            },
            3, 3
    );

    assert(!isEMatrix(&m));

    freeMemMatrix(&m);
}

void test_isEMatrix() {
    test_isEMatrixF1();
    test_isEMatrixT();
    test_isEMatrixF2();
}

void test_isSymmetricMatrixT() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1,2,3,
                    2,5,6,
                    3,6,9
            },
            3, 3
    );

    assert(isSymmetricMatrix(&m));

    freeMemMatrix(&m);
}

void test_isSymmetricMatrixF() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1,2,3,
                    4,5,6,
                    7,8,9
            },
            3, 3
    );

    assert(!isSymmetricMatrix(&m));

    freeMemMatrix(&m);
}

void test_isSymmetricMatrix() {
    test_isSymmetricMatrixT();
    test_isSymmetricMatrixF();
}

void test_transposeSquareMatrix() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1,2,3,
                    4,5,6,
                    7,8,9
            },
            3, 3
    );

    transposeSquareMatrix(&m);

    matrix test_m = createMatrixFromArray(
            (int[]) {
                    1,4,7,
                    2,5,8,
                    3,6,9
            },
            3, 3
    );

    assert(areTwoMatricesEqual(&m, &test_m));

    freeMemMatrix(&m);
    freeMemMatrix(&test_m);
}

void test_transposeMatrix1() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1,2,3,
                    4,5,6
            },
            2, 3
    );

    transposeMatrix(&m);

    matrix test_m = createMatrixFromArray(
            (int[]) {
                    1,4,
                    2,5,
                    3,6
            },
            3, 2
    );

    assert(areTwoMatricesEqual(&m, &test_m));

    freeMemMatrix(&m);
    freeMemMatrix(&test_m);
}

void test_transposeMatrix2() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1,4,
                    2,5,
                    3,6
            },
            3, 2
    );

    transposeMatrix(&m);

    matrix test_m = createMatrixFromArray(
            (int[]) {
                    1,2,3,
                    4,5,6
            },
            2, 3
    );

    assert(areTwoMatricesEqual(&m, &test_m));

    freeMemMatrix(&m);
    freeMemMatrix(&test_m);
}

void test_transposeMatrix() {
    test_transposeMatrix1();
    test_transposeMatrix2();
}

void test_getMinValuePos() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    2,4,
                    1,5,
                    3,6
            },
            3, 2
    );

    position p = getMinValuePos(m);

    assert((p.rowIndex == 1) && (p.colIndex == 0));

    freeMemMatrix(&m);
}

void test_getMaxValuePos() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    2,4,
                    1,6,
                    3,5
            },
            3, 2
    );

    position p = getMaxValuePos(m);

    assert((p.rowIndex == 1) && (p.colIndex == 1));

    freeMemMatrix(&m);
}

//проводит автоматизированное тестирование библиотеки
void test(){
    test_swapRows();
    test_swapColumns();
    test_insertionSortRowsMatrixByRowCriteria();
    test_selectionSortColsMatrixByColCriteria();
    test_isSquareMatrix();
    test_isEMatrix();
    test_isSymmetricMatrix();
    test_transposeSquareMatrix();
    test_transposeMatrix();
    test_getMinValuePos();
    test_getMaxValuePos();
}

# endif