# ifndef FILE_H
# define FILE_H

# include "file.h"
# include "E:\C23Exe\libs\data_structures\matrix\matrix.h"
# include <memory.h>
# include "E:\C23Exe\string\string_.h"

//транспонирует квадратную матрицу в файле
void squarematricesFileTransponse(const char* filename) {
    FILE *f = fopen(filename, "r");

    if (errno != 0) {
        fprintf(stderr, "lol didnt open\n");

        exit(1);
    }

    int count_of_matrices = 0;
    int n;
    int *n_array = (int*) malloc(count_of_matrices);
    matrix *ms = (matrix*) malloc(count_of_matrices);

    while (!feof(f)){
        n_array = (int*)realloc(n_array, sizeof(int) * (count_of_matrices + 1));
        ms = (matrix*)realloc(ms, sizeof(matrix) * (count_of_matrices + 1));

        fscanf(f, "%d", &n);
        n_array[count_of_matrices] = n;

        matrix m = getMemMatrix(n, n);

        for (int i = 0; i < n;i++)
            for (int j = 0; j < n; j++)
                fscanf(f, "%d", &m.values[i][j]);

        ms[count_of_matrices] = m;

        count_of_matrices++;
    }

    perror("Task 1 Read");

    fclose(f);

    for (int i = 0; i < count_of_matrices; i++)
        transposeSquareMatrix(&ms[i]);

    f = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol didnt open\n");

        exit(1);
    }

    if (!feof(f))
        for (int i = 0; i < count_of_matrices; i++){
            fprintf(f, "%d\n", n_array[i]);

            for (int j = 0; j < n_array[i];j++) {
                for (int k = 0; k < n_array[i]; k++)
                    fprintf(f, "%d ", ms[i].values[j][k]);

                fprintf(f, "\n");
            }
        }

    perror("Task 1 Write");

    fclose(f);
}

void test_squareMatrixFileTransponse(){
    const char filename[] = "E:\\C23Exe\\19_laba\\1\\task.txt";

    matrix m1 = createMatrixFromArray((int []) {
                                    1,2,3,
                                    4,5,6,
                                    7,8,9
                                 },3,3);

    matrix m2 = createMatrixFromArray((int []) {
            1,2,
            4,5,
    },2,2);

    FILE *f = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol didnt open\n");

        exit(1);
    }

    fprintf(f, "%d\n", 3);

    if (!feof(f)) {
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                fprintf(f, "%d ", m1.values[i][j]);
            }

            fprintf(f, "\n");
        }

        fprintf(f, "%d\n", 2);

        for (size_t i = 0; i < 2; i++) {
            for (size_t j = 0; j < 2; j++) {
                fprintf(f, "%d ", m2.values[i][j]);
            }

            fprintf(f, "\n");
        }
    }

    perror("Task 1 Write test");

    fclose(f);

    transposeSquareMatrix(&m1);
    transposeSquareMatrix(&m2);

    squarematricesFileTransponse(filename);

    f = fopen(filename, "r");

    if (errno != 0) {
        fprintf(stderr, "lol didnt open\n");

        exit(1);
    }

    matrix test_m1;
    int n1;
    matrix test_m2;
    int n2;

    if (!feof(f)) {
        fscanf(f, "%d", &n1);

        test_m1 = getMemMatrix(n1, n1);

        for (size_t i = 0; i < n1; i++)
            for (size_t j = 0; j < n1; j++)
                fscanf(f, "%d", &test_m1.values[i][j]);

        assert((areTwoMatricesEqual(&m1,&test_m1)) && (n1 == 3));

        fscanf(f, "%d", &n2);

        test_m2 = getMemMatrix(n2, n2);

        for (size_t i = 0; i < n2; i++)
            for (size_t j = 0; j < n2; j++)
                fscanf(f, "%d", &test_m2.values[i][j]);

        assert((areTwoMatricesEqual(&m2,&test_m2)) && (n2 == 2));
    }

    perror("Task 1 Read test");

    fclose(f);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
    freeMemMatrix(&test_m1);
    freeMemMatrix(&test_m2);
}

int countOfRowsInFile(const char* filename){
    FILE *f;
    int errno;

    int count_of_rows = 0;

    f = fopen(filename, "r");

    while (ferror(f) == 0){
        count_of_rows++;

        fscanf(f, "\n");
    }

    fclose(f);
    perror("Task 1 Error: ");

    return count_of_rows;
}

//переводит число с фиксированной точкой в число с плавающей точкой.
void fixedPointIntoFloatPointFile(const char* filename) {
    FILE *f;
    int errno;

    int count_of_rows = countOfRowsInFile(f);
    char **values = (char **) malloc(sizeof (char*) * count_of_rows);

    f = fopen(filename, "r");

    while (!ferror(f))
        for (int i = 0; i < count_of_rows; i++)
            fscanf(f, "%s\n", values[i]);


    fclose(f);
    perror("Error: ");

    f = fopen(filename, "w");

    while (!ferror(f))
        for (int i = 0; i < count_of_rows; i++)
            fprintf(f, "%s.%s%sE\n", values[i][0], values[i][1], values[i][2]);

}

//проводит автоматизированное тестирование функций
void testFile(){
    test_squareMatrixFileTransponse();
}

# endif