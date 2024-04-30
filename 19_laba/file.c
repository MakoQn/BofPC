# ifndef FILE_H
# define FILE_H

# include "file.h"
# include "E:\C23Exe\libs\data_structures\matrix\matrix.h"

//транспонирует квадратную матрицу в файле
void squareMatrixFileTransponse(const char* filename) {
    FILE *f = fopen(filename, "r");

    if (f == NULL) {
        fprintf(stderr, "lol didnt open %s \n", filename);

        exit(1);
    }

    size_t n;
    fscanf(f, "%llu", &n);

    matrix m = getMemMatrix(n ,  n);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            fscanf(f, "%d", &m.values[i][j]);

    fclose(f);

    transposeSquareMatrix(&m);

    f = fopen(filename, "w");

    if (f == NULL) {
        fprintf(stderr, "lol didnt open %s \n", filename);

        exit(1);
    }

    fprintf(f, "%d\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++)
            fprintf(f, "%d ", m.values[i][j]);

        fprintf(f, "\n");
    }

    fclose(f);

    freeMemMatrix(&m);
}

void test_squareMatrixFileTransponse(){
    const char filename[] = "E:\\C23Exe\\19_laba\\1\\task.txt";

    matrix m = createMatrixFromArray((int []) {
                                    1,2,3,
                                    4,5,6,
                                    7,8,9
                                 },3,3);

    FILE *f = fopen(filename, "w");

    fprintf(f, "%d\n", 3);

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            fprintf(f, "%d ", m.values[i][j]);
        }

        fprintf(f, "\n");
    }

    fclose(f);

    squareMatrixFileTransponse(filename);

    transposeSquareMatrix(&m);

    matrix file_m = getMemMatrix(3,3);

    int n;
    f = fopen(filename, "r");
    fscanf(f, "%d\n", &n);

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            fscanf(f, "%d", &file_m.values[i][j]);

    fclose(f);

    assert((areTwoMatricesEqual(&m,&file_m)) && (n == 3));

    freeMemMatrix(&m);
    freeMemMatrix(&file_m);
}

//проводит автоматизированное тестирование функций
void testFile(){
    test_squareMatrixFileTransponse();
}

# endif