# ifndef INC_MATRIX_H
# define INC_MATRIX_H

#include "matrix.h"
# include <malloc.h>
# include <stdint.h>
# include <stdio.h>
# include <assert.h>
# include <stdbool.h>
# include <memory.h>
# include <math.h>

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

//выполняет сортировку вставками строк матрицы m по неубыванию значения функции criteria применяемой для строк.
void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int)){
    int *criteria_array = (int*)malloc(sizeof(int) * m.nRows);

    for (int i = 0; i < m.nRows; i++)
        criteria_array[i] = criteria(m.values[i], m.nCols);

    for (int i = 1; i < m.nRows; i++){
        int t = criteria_array[i];
        int j = i;

        while (j > 0 && criteria_array[j - 1] > t) {
            criteria_array[j] = criteria_array[j - 1];
            swapRows(m, j, j-1);
            j--;
        }

        criteria_array[j] = t;
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

void swapMaxAndMinRows(matrix m){
    position pos_min = getMinValuePos(m);
    position pos_max = getMaxValuePos(m);

    if (pos_min.rowIndex != pos_max.rowIndex)
        swapRows(m, pos_min.rowIndex, pos_max.rowIndex);
}

//возвращает максимальный элемент массива.
int getMax(int *a, int n){
    int max = INT_MIN;

    for (int i = 0; i < n; i++)
        if (a[i] > max)
            max = a[i];

    return max;
}

void sortRowsByMinElement(matrix m){
    insertionSortRowsMatrixByRowCriteria(m, getMax);
}

//возвращает минимальный элемент массива.
int getMin(int *a, int n){
    int min = INT_MAX;

    for (int i = 0; i < n; i++)
        if (a[i] < min)
            min = a[i];

    return min;
}

void sortColsByMinElement(matrix m){
    selectionSortColsMatrixByColCriteria(m, getMin);
}

//возвращает произведение матриц m1 и m2.
matrix mulMatrices(matrix m1, matrix m2){
    matrix mul_m;

    mul_m.nRows = m1.nRows <= m2.nRows ? m1.nRows : m2.nRows;
    mul_m.nCols = m1.nCols <= m2.nCols ? m1.nCols : m2.nCols;

    mul_m = getMemMatrix(mul_m.nRows, mul_m.nCols);

    for (int i = 0; i < m1.nRows; i++)
        for (int j = 0; j < m2.nCols; j++){
            mul_m.values[i][j] = 0;

            for (int k = 0; k < m1.nCols; k++)
                mul_m.values[i][j] += m1.values[i][k] * m2.values[k][j];
        }

    return mul_m;
}

void getSquareOfMatrixIfSymmetric(matrix *m){
    if (!isSymmetricMatrix(m))
        return;

    matrix square_m = mulMatrices(*m, *m);

    freeMemMatrix(m);

    *m = square_m;

    freeMemMatrix(&square_m);
}

//проверка, что все элементы массива уникальны.
bool isUnique(int *a, int n){
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] == a[j])
                return 0;

    return 1;
}

//возвращает сумму элементов массива.
int getSum(int *a, int n){
    int sum = 0;

    for (int i = 0; i < n; i++)
        sum += a[i];

    return sum;
}

void transposeIfMatrixHasNotEqualSumOfRows(matrix m){
    int *sum_array = (int *)(malloc(sizeof(int) * m.nRows));

    for (int i = 0; i < m.nRows; i++)
        sum_array[i] = getSum(m.values[i], m.nCols);

    if (isUnique(sum_array, m.nRows))
        transposeSquareMatrix(&m);

    free(sum_array);
}

bool isMutuallyInverseMatrices(matrix m1, matrix m2){
    matrix E_M1M2 = mulMatrices(m1, m2);
    matrix E_M2M1 = mulMatrices(m2, m1);

    bool is_E = isEMatrix(&E_M1M2) && isEMatrix(&E_M2M1);

    freeMemMatrix(&E_M1M2);
    freeMemMatrix(&E_M2M1);

    return is_E;
}

//возвращает максимальный элемент среди a и b.
int max(int a, int b){
    return a >= b ? a : b;
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m){
    int size_of_array_of_maxes = m.nCols + m.nRows - 2;
    int *array_of_maxes = (int *) malloc(sizeof(int) * size_of_array_of_maxes);

    for (int i = 0; i < size_of_array_of_maxes; i++)
        array_of_maxes[i] = INT_MIN;

    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; j++)
            if (i != j){
                int diff = abs(i - j - 1);
                array_of_maxes[diff] = max(m.values[i][j], array_of_maxes[diff]);
            }

    int sum = getSum(array_of_maxes, size_of_array_of_maxes);

    free(array_of_maxes);

    return sum;
}

int getMinInArea(matrix m){
    position pos_of_max = getMaxValuePos(m);

    int min = INT_MAX;

    for (int i = 0; i < pos_of_max.rowIndex; i++)
        for (int j = 0; j < m.nCols; j++)
            if ((j >= pos_of_max.colIndex - (pos_of_max.rowIndex - i)) && (j <= pos_of_max.colIndex + (pos_of_max.rowIndex - i)))
                if (m.values[i][j] < min)
                    min = m.values[i][j];

    return min;
}

float getDistance(int *a, int n){
    float d = 0;

    for (int i = 0; i < n; i++)
        d += a[i] * a[i];

    return sqrt(d);
}

//выполняет сортировку вставками строк матрицы m по неубыванию значения функции criteria применяемой для строк(float).
void insertionSortRowsMatrixByRowCriteriaF(matrix m, float (*criteria)(int *, int)){
    float *criteria_array = (float*)malloc(sizeof(int) * m.nRows);

    for (int i = 0; i < m.nRows; i++)
        criteria_array[i] = criteria(m.values[i], m.nCols);

    for (int i = 1; i < m.nRows; i++){
        float t = criteria_array[i];
        int j = i;

        while (j > 0 && criteria_array[j - 1] > t) {
            criteria_array[j] = criteria_array[j - 1];
            swapRows(m, j, j-1);
            j--;
        }

        criteria_array[j] = t;
    }

    free(criteria_array);
}

void sortByDistances(matrix m){
    insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
}

int cmp_long_long(const void *pa, const void *pb){
    return *(long long *)pa - *(long long *)pb;
}

int countNUnique(long long *a, int n){
    qsort(a, n, sizeof (long long), cmp_long_long);

    int count_of_unique = n == 0 ? 1 : 0 ;
    int i = 0;

    while (i < n) {
        int l = 0;
        int r = n - 1;

        while (l <= r) {
            int mid = l + (r - l) / 2;

            if (a[mid] == a[i]) {
                i = mid;
                l = mid + 1;
            }
            else if (a[mid] > a[i])
                r = mid - 1;
            else
                l = mid + 1;
        }

        i++;
        count_of_unique++;
    }

    return count_of_unique;
}

int countEqClassesByRowsSum(matrix m){
    long long *sum_array = (long long *) malloc(sizeof(long long) * m.nRows);

    for (int i = 0; i < m.nRows; i++)
        sum_array[i] = getSum(m.values[i], m.nCols);

    int count_of_unique = countNUnique(sum_array, m.nRows);

    free(sum_array);

    return count_of_unique;
}

int getNSpecialElement(matrix m){
    int k = 0;

    for (int i = 0; i < m.nCols; i++){
        int *col_array = (int *) malloc(sizeof(int) * m.nRows);

        for (int j = 0; j < m.nRows; j++)
            col_array[j] = m.values[j][i];

        int sum = getSum(col_array, m.nRows);

        free(col_array);

        for (int j = 0; j < m.nRows; j++)
            if (2 * m.values[j][i] > sum){
                k++;
                break;
            }
    }

    return k;
}

position getLeftMin(matrix m){
    return getMinValuePos(m);
}

void swapPenultimateRow(matrix m){
    position left_min_pos = getLeftMin(m);

    int *col_array = (int *) malloc(sizeof(int) * m.nRows);

    for (int i = 0; i < m.nRows;i++)
        col_array[i] = m.values[i][left_min_pos.colIndex];

    int pre_last_row = m.nRows - 2;

    for (int i = left_min_pos.colIndex; i <= left_min_pos.colIndex; i++)
        for (int j = 0; j < m.nRows; j++)
            m.values[pre_last_row][j] = col_array[j];

    free(col_array);
}

bool isNonDescendingSorted(int *a, int n){
    for (int i = 0; i < n - 1; i++)
        if (a[i] > a[i + 1])
            return 0;

    return 1;
}

bool hasAllNonDescendingRows(matrix m){
    for (int i = 0; i < m.nRows; i++)
        if (isNonDescendingSorted(m.values[i], m.nCols) == 0)
            return 0;

    return 1;
}

int countNonDescendingRowsMatrices(matrix *ms, int nMatrix){
    int count_of_matrices = 0;

    for (int i = 0; i < nMatrix; i++)
        if (hasAllNonDescendingRows(ms[i]))
            count_of_matrices++;

    return count_of_matrices;
}

int countValues(const int *a, int n, int value){
    int count_of_values = 0;

    for (int i = 0; i < n; i++)
        if (a[i] == value)
            count_of_values++;

    return count_of_values;
}

int countZeroRows(matrix m){
    int count_of_rows = 0;

    for (int i = 0; i < m.nRows; i++)
        if (countValues(m.values[i], m.nCols, 0) == m.nCols)
            count_of_rows++;

    return count_of_rows;
}

void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix){
    int max_count_of_zero_rows = INT_MIN;

    for (int i = 0; i < nMatrix; i++){
        int count_of_zero_rows = countZeroRows(ms[i]);

        max_count_of_zero_rows = max(max_count_of_zero_rows, count_of_zero_rows);
    }

    for (int i = 0; i < nMatrix; i++){
        int count_of_zero_rows = countZeroRows(ms[i]);

        if (count_of_zero_rows == max_count_of_zero_rows)
            outputMatrix(ms[i]);
    }
}

int getMaxValue(matrix m){
    int max_value = INT_MIN;

    for (int i = 0; i < m.nRows; i++){
        int max_of_row = getMax(m.values[i], m.nCols);

        max_value = max(max_of_row, max_value);
    }

    return max_value;
}

int min2(int a, int b){
    return a <= b ? a : b;
}

void printMatrixWithMinNorm(matrix *ms, int nMatrix){
    int min_norm = INT_MAX;

    for (int i = 0; i < nMatrix; i++){
        int norm = getMaxValue(ms[i]);

        min_norm = min2(norm, min_norm);
    }

    for (int i = 0; i < nMatrix; i++){
        int norm = getMaxValue(ms[i]);

        if (norm == min_norm)
            outputMatrix(ms[i]);
    }
}

bool isSpecialElement(int *a, int n, int j){
    for (int i = j - 1; i >= 0; i--)
            if (a[i] > a[j])
                return 0;

    for (int i = j + 1; i < n; i++)
        if (a[i] < a[j])
            return 0;

    return 1;
}

int getNSpecialElement2(matrix m){
    int count_of_specials = 0;

    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; j++)
            if (isSpecialElement(m.values[i], m.nCols, j))
                count_of_specials++;

    return count_of_specials;
}

double getScalarProduct(int *a, int *b, int n){
    double scalar_product = 0;

    for (int i = 0; i < n; i++)
        scalar_product += a[i] * b[i];

    return scalar_product;
}

double getVectorLength(int *a, int n){
    double vector_length = 0;

    for (int i = 0; i < n; i++)
        vector_length += a[i] * a[i];

    return sqrt(vector_length);
}

double getCosine(int *a, int *b, int n){
    double length_product = (getVectorLength(a, n) * getVectorLength(b, n));

    assert(length_product != 0);

    return getScalarProduct(a, b, n) / length_product;
}

double absDouble(double a){
    return a < 0 ? -a : a;
}

int getVectorIndexWithMaxAngle(matrix m, int *b) {
    int index_of_vector_max_angle;
    double min_cos = 2;

    for (int i = 0; i < m.nRows; i++) {
        double abs_cos = absDouble(getCosine(m.values[i], b, m.nCols));

        if (abs_cos < min_cos) {
            index_of_vector_max_angle = i;
            min_cos = abs_cos;
        }
    }

    return index_of_vector_max_angle;
}

long long getScalarProductRowAndCol(matrix m, int i, int j){
    int *col_array = (int *)malloc(sizeof(int) * m.nRows);

    for (int i = 0; i < m.nRows; i++)
        col_array[i] = m.values[i][j];

    long long scalar_product = getScalarProduct(m.values[i], col_array, m.nRows);

    free(col_array);

    return scalar_product;
}

long long getSpecialScalarProduct(matrix m){
    position max_element = getMaxValuePos(m);
    position min_element = getMinValuePos(m);

    return getScalarProductRowAndCol(m, max_element.rowIndex, min_element.colIndex);
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

void test_swapMaxAndMinRows_maxAndMinInDiffRows(){
    matrix m = createMatrixFromArray(
            (int[]) {
                    1,2,3,
                    4,5,6,
                    7,8,9

            }, 3, 3);

    swapMaxAndMinRows(m);

    matrix test_m = createMatrixFromArray(
            (int[]) {
                    7,8,9,
                    4,5,6,
                    1,2,3

            }, 3, 3);

    assert(areTwoMatricesEqual(&m, &test_m));

    freeMemMatrix(&m);
    freeMemMatrix(&test_m);
}

void test_swapMaxAndMinRows_maxAndMinInSameRows(){
    matrix m = createMatrixFromArray(
            (int[]) {
                    1,2,9,
                    4,5,6,
                    7,8,3

            }, 3, 3);

    swapMaxAndMinRows(m);

    matrix test_m = createMatrixFromArray(
            (int[]) {
                    1,2,9,
                    4,5,6,
                    7,8,3

            }, 3, 3);

    assert(areTwoMatricesEqual(&m, &test_m));

    freeMemMatrix(&m);
    freeMemMatrix(&test_m);
}

void test_swapMaxAndMinRows(){
    test_swapMaxAndMinRows_maxAndMinInDiffRows();
    test_swapMaxAndMinRows_maxAndMinInSameRows();
}

void test_sortRowsByMinElement_maxElementsDiff(){
    matrix m = createMatrixFromArray(
            (int[]) {
                    7,1,2,
                    1,8,1,
                    3,2,3

            }, 3, 3);

    sortRowsByMinElement(m);

    matrix test_m = createMatrixFromArray(
            (int[]) {
                    3,2,3,
                    7,1,2,
                    1,8,1

            }, 3, 3);

    assert(areTwoMatricesEqual(&m, &test_m));

    freeMemMatrix(&m);
    freeMemMatrix(&test_m);
}

void test_sortRowsByMinElement_maxElementsSemiDiff(){
    matrix m = createMatrixFromArray(
            (int[]) {
                    7,1,2,
                    1,7,1,
                    3,2,3

            }, 3, 3);

    sortRowsByMinElement(m);

    matrix test_m = createMatrixFromArray(
            (int[]) {
                    3,2,3,
                    7,1,2,
                    1,7,1

            }, 3, 3);

    assert(areTwoMatricesEqual(&m, &test_m));

    freeMemMatrix(&m);
    freeMemMatrix(&test_m);
}

void test_sortRowsByMinElement_maxElementsSame(){
    matrix m = createMatrixFromArray(
            (int[]) {
                    7,1,2,
                    1,7,1,
                    7,2,7

            }, 3, 3);

    sortRowsByMinElement(m);

    matrix test_m = createMatrixFromArray(
            (int[]) {
                    7,1,2,
                    1,7,1,
                    7,2,7

            }, 3, 3);

    assert(areTwoMatricesEqual(&m, &test_m));

    freeMemMatrix(&m);
    freeMemMatrix(&test_m);
}

void test_sortRowsByMinElement(){
    test_sortRowsByMinElement_maxElementsDiff();
    test_sortRowsByMinElement_maxElementsSemiDiff();
    test_sortRowsByMinElement_maxElementsSame();
}

void test_sortColsByMinElement_minElementsSemiDiff(){
    matrix m = createMatrixFromArray(
            (int[]) {
                    3,5,2,4,3,3,
                    2,5,1,8,2,7,
                    6,1,4,4,8,3

            }, 3, 6);

    sortColsByMinElement(m);

    matrix test_m = createMatrixFromArray(
            (int[]) {
                    5,2,3,3,3,4,
                    5,1,2,2,7,8,
                    1,4,6,8,3,4

            }, 3, 6);

    assert(areTwoMatricesEqual(&m, &test_m));

    freeMemMatrix(&m);
    freeMemMatrix(&test_m);
}

void test_sortColsByMinElement_minElementsDiff(){
    matrix m = createMatrixFromArray(
            (int[]) {
                    3,5,7,4,9,3,
                    2,5,6,8,7,7,
                    6,1,8,4,8,3

            }, 3, 6);

    sortColsByMinElement(m);

    matrix test_m = createMatrixFromArray(
            (int[]) {
                    5,3,3,4,7,9,
                    5,2,7,8,6,7,
                    1,6,3,4,8,8

            }, 3, 6);

    assert(areTwoMatricesEqual(&m, &test_m));

    freeMemMatrix(&m);
    freeMemMatrix(&test_m);
}

void test_sortColsByMinElement(){
    test_sortColsByMinElement_minElementsSemiDiff();
    test_sortColsByMinElement_minElementsDiff();
}

void test_getSquareOfMatrixIfSymmetric_symmetric(){
    matrix m = createMatrixFromArray(
            (int[]) {
                    1,2,3,
                    2,5,6,
                    3,6,9

            }, 3, 3);

    getSquareOfMatrixIfSymmetric(&m);

    matrix test_m = createMatrixFromArray(
            (int[]) {
                    14,30,42,
                    30,65,90,
                    42,90,126

            }, 3, 3);

    assert(areTwoMatricesEqual(&m, &test_m));

    freeMemMatrix(&m);
    freeMemMatrix(&test_m);
}

void test_getSquareOfMatrixIfSymmetric_notSymmetric(){
    matrix m = createMatrixFromArray(
            (int[]) {
                    1,2,3,
                    4,5,6,
                    7,8,9

            }, 3, 3);

    getSquareOfMatrixIfSymmetric(&m);

    matrix test_m = createMatrixFromArray(
            (int[]) {
                    14,30,42,
                    30,65,90,
                    42,90,126

            }, 3, 3);

    assert(!areTwoMatricesEqual(&m, &test_m));

    freeMemMatrix(&m);
    freeMemMatrix(&test_m);
}

void test_getSquareOfMatrixIfSymmetric_notSquare(){
    matrix m = createMatrixFromArray(
            (int[]) {
                    1,2,
                    4,5,
                    7,8

            }, 3, 2);

    getSquareOfMatrixIfSymmetric(&m);

    matrix test_m = createMatrixFromArray(
            (int[]) {
                    14,30,42,
                    30,65,90,
                    42,90,126

            }, 3, 3);

    assert(!areTwoMatricesEqual(&m, &test_m));

    freeMemMatrix(&m);
    freeMemMatrix(&test_m);
}

void test_getSquareOfMatrixIfSymmetric(){
    test_getSquareOfMatrixIfSymmetric_symmetric();
    test_getSquareOfMatrixIfSymmetric_notSymmetric();
    test_getSquareOfMatrixIfSymmetric_notSquare();
}

void test_transposeIfMatrixHasNotEqualSumOfRows_HasNotEqualSum(){
    matrix m = createMatrixFromArray(
            (int[]) {
                    1,2,3,
                    4,5,6,
                    7,8,9
            },
            3, 3
    );

    transposeIfMatrixHasNotEqualSumOfRows(m);

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

void test_transposeIfMatrixHasNotEqualSumOfRows_HasEqualSum(){
    matrix m = createMatrixFromArray(
            (int[]) {
                    1,2,3,
                    1,2,3,
                    7,8,9
            },
            3, 3
    );

    transposeIfMatrixHasNotEqualSumOfRows(m);

    matrix test_m = createMatrixFromArray(
            (int[]) {
                    1,2,3,
                    1,2,3,
                    7,8,9
            },
            3, 3
    );

    assert(areTwoMatricesEqual(&m, &test_m));

    freeMemMatrix(&m);
    freeMemMatrix(&test_m);
}

void test_transposeIfMatrixHasNotEqualSumOfRows(){
    test_transposeIfMatrixHasNotEqualSumOfRows_HasNotEqualSum();
    test_transposeIfMatrixHasNotEqualSumOfRows_HasEqualSum();
}

void test_isMutuallyInverseMatrices_T(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1,0,0,
                    1,-1,0,
                    1,0,1
            },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1,0,0,
                    1,-1,0,
                    -1,0,1
            },
            3, 3
    );

    assert(isMutuallyInverseMatrices(m1, m2));

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_isMutuallyInverseMatrices_F(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1,0,0,
                    1,-1,0,
                    1,0,1
            },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1,0,0,
                    1,-1,0,
                    1,0,1
            },
            3, 3
    );

    assert(!isMutuallyInverseMatrices(m1, m2));

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_isMutuallyInverseMatrices(){
    test_isMutuallyInverseMatrices_T();
    test_isMutuallyInverseMatrices_F();
}

void test_findSumOfMaxesOfPseudoDiagonal(){
    matrix m = createMatrixFromArray(
            (int[]) {
                    3,2,5, 4,
                    1,3,6, 3,
                    3,2,1, 2
            },
            3, 4
    );

    assert(findSumOfMaxesOfPseudoDiagonal(m) == 20);

    freeMemMatrix(&m);
}

void test_getMinInArea_colsOutside(){
    matrix m = createMatrixFromArray(
            (int[]) {

                    10,7,5, 6,
                    3,11,8, 9,
                    4,1,12, 2
            },
            3, 4
    );

    assert(getMinInArea(m) == 5);

    freeMemMatrix(&m);
}

void test_getMinInArea_colsInside(){
    matrix m = createMatrixFromArray(
            (int[]) {

                    6,8,9, 2,
                    7,12,3, 4,
                    10,11,5, 1
            },
            3, 4
    );

    assert(getMinInArea(m) == 6);

    freeMemMatrix(&m);
}

void test_getMinInArea(){
    test_getMinInArea_colsOutside();
    test_getMinInArea_colsInside();
}

void test_sortByDistances(){
    matrix points = createMatrixFromArray(
            (int[]) {

                    7,12,3,
                    6,8,9,
                    10,11,5
            },
            3, 3
    );

    sortByDistances(points);

    matrix test_points = createMatrixFromArray(
            (int[]) {

                    6,8,9,
                    7,12,3,
                    10,11,5
            },
            3, 3
    );

    assert(areTwoMatricesEqual(&points, &test_points));

    freeMemMatrix(&points);
    freeMemMatrix(&test_points);
}

void test_countEqClassesByRowsSum_normalSize(){
    matrix m = createMatrixFromArray(
            (int[]) {

                    7,1,
                    2,7,
                    5,4,
                    4,3,
                    1,6,
                    8,0
            },
            6, 2
    );

    assert(countEqClassesByRowsSum(m) == 3);

    freeMemMatrix(&m);
}

void test_countEqClassesByRowsSum_zeroSize(){
    matrix m = createMatrixFromArray(
            (int[]) {
            },
            0, 0
    );

    assert(countEqClassesByRowsSum(m) == 1);

    freeMemMatrix(&m);
}

void test_countEqClassesByRowsSum(){
    test_countEqClassesByRowsSum_normalSize();
    test_countEqClassesByRowsSum_zeroSize();
}

void test_getNSpecialElement_specialElementsExist(){
    matrix m = createMatrixFromArray(
            (int[]) {

                    3,5,5,4,
                    2,3,6,7,
                    12,2,1,2
            },
            3, 4
    );

    assert(getNSpecialElement(m) == 2);

    freeMemMatrix(&m);
}

void test_getNSpecialElement_specialElementsNotExistAllEqual(){
    matrix m = createMatrixFromArray(
            (int[]) {

                    1,1,1,1,
                    1,1,1,1,
                    1,1,1,1
            },
            3, 4
    );

    assert(getNSpecialElement(m) == 0);

    freeMemMatrix(&m);
}

void test_getNSpecialElement_specialElementsExistMaxLessSum(){
    matrix m = createMatrixFromArray(
            (int[]) {

                    7,5,5,4,
                    6,3,6,7,
                    12,2,1,4
            },
            3, 4
    );

    assert(getNSpecialElement(m) == 0);

    freeMemMatrix(&m);
}

void test_getNSpecialElement(){
    test_getNSpecialElement_specialElementsExist();
    test_getNSpecialElement_specialElementsNotExistAllEqual();
    test_getNSpecialElement_specialElementsExistMaxLessSum();
}

void test_swapPenultimateRow_minInCol(){
    matrix m = createMatrixFromArray(
            (int[]) {

                    1,2,3,
                    4,5,6,
                    7,8,1
            },
            3, 3
    );

    swapPenultimateRow(m);

    matrix test_m = createMatrixFromArray(
            (int[]) {

                    1,2,3,
                    1,4,7,
                    7,8,1
            },
            3, 3
    );

    assert(areTwoMatricesEqual(&m, &test_m));

    freeMemMatrix(&m);
    freeMemMatrix(&test_m);
}

void test_swapPenultimateRow_minInPreLastRow(){
    matrix m = createMatrixFromArray(
            (int[]) {

                    2,2,3,
                    4,5,1,
                    7,8,9
            },
            3, 3
    );

    swapPenultimateRow(m);

    matrix test_m = createMatrixFromArray(
            (int[]) {

                    2,2,3,
                    3,1,9,
                    7,8,9
            },
            3, 3
    );

    assert(areTwoMatricesEqual(&m, &test_m));

    freeMemMatrix(&m);
    freeMemMatrix(&test_m);
}

void test_swapPenultimateRow(){
    test_swapPenultimateRow_minInCol();
    test_swapPenultimateRow_minInPreLastRow();
}

void test_countNonDescendingRowsMatrices(){
    matrix *ms = createArrayOfMatrixFromArray(
            (int[]) {

                    7,1,
                    1,1,
                    1,6,
                    2,2,
                    5,4,
                    2,3,
                    1,3,
                    7,9
            },
            4, 2, 2
    );

    assert(countNonDescendingRowsMatrices(ms, 4) == 2);

    freeMemMatrices(ms, 4);
}

void test_countZeroRows(){
    matrix m = createMatrixFromArray(
            (int[]) {

                    0,0,0,
                    4,5,0,
                    7,0,9
            },
            3, 3
    );

    assert(countZeroRows(m) == 1);

    freeMemMatrix(&m);
}

void test_getNSpecialElement2(){
    matrix m = createMatrixFromArray(
            (int[]) {

                    2,3,5,5,4,
                    6,2,3,8,12,
                    12,12,2,1,2
            },
            3, 5
    );

    assert(getNSpecialElement2(m) == 4);

    freeMemMatrix(&m);
}

void test_getVectorIndexWithMaxAngle(){
    matrix m = createMatrixFromArray(
            (int[]) {
                3,0,4,
                4,0,4,
                10,0,6
            },
            3, 3
    );

    assert(getVectorIndexWithMaxAngle(m,(int[]){1,1,1}) == 2);

    freeMemMatrix(&m);
}

void test_getSpecialScalarProduct(){
    matrix m = createMatrixFromArray(
            (int[]) {
                    2,3,4,
                    4,10,4,
                    9,6,1
            },
            3, 3
    );

    assert(getSpecialScalarProduct(m) == 60);

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
    test_swapMaxAndMinRows();
    test_sortRowsByMinElement();
    test_sortColsByMinElement();
    test_getSquareOfMatrixIfSymmetric();
    test_transposeIfMatrixHasNotEqualSumOfRows();
    test_isMutuallyInverseMatrices();
    test_findSumOfMaxesOfPseudoDiagonal();
    test_getMinInArea();
    test_sortByDistances();
    test_countEqClassesByRowsSum();
    test_getNSpecialElement();
    test_swapPenultimateRow();
    test_countNonDescendingRowsMatrices();
    test_countZeroRows();
    test_getNSpecialElement2();
    test_getVectorIndexWithMaxAngle();
    test_getSpecialScalarProduct();
}

# endif