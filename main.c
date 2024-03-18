# include <stdio.h>
# include <assert.h>
# include "libs\data_structures\matrix\matrix.h"

void task1(matrix m){
    position pos_min = getMinValuePos(m);
    position pos_max = getMaxValuePos(m);

    if (pos_min.rowIndex != pos_max.rowIndex)
        swapRows(m, pos_min.rowIndex, pos_max.rowIndex);
}

void test_task1_maxAndMinInDiffRows(){
    matrix m = createMatrixFromArray(
            (int[]) {
                        1,2,3,
                        4,5,6,
                        7,8,9

            }, 3, 3);

    task1(m);

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

void test_task1_maxAndMinInSameRows(){
    matrix m = createMatrixFromArray(
            (int[]) {
                    1,2,9,
                    4,5,6,
                    7,8,3

            }, 3, 3);

    task1(m);

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

void test_task1(){
    test_task1_maxAndMinInDiffRows();
    test_task1_maxAndMinInSameRows();
}

int main() {
    test_task1();

    return 0;
}

