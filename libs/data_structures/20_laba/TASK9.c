# include <stdio.h>
# include "E:\C23Exe\libs\data_structures\matrix\matrix.h"
# include "E:\C23Exe\libs\data_structures\19_laba\file.h"

void writeNumsInFile(int *nums, size_t n, char *filename) {
    FILE *f = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol Task 9 didnt open\n");

        exit(1);
    }

    for (size_t i = 0; i < n; i++)
        fprintf(f, "%d ", nums[i]);

    perror("Task 9 Read writeNumsInFile");

    fclose(f);
}

void onlyLessNumFile(char* border, char *source_file, char *create_file) {
    FILE *source = fopen(source_file, "r");

    if (errno != 0) {
        fprintf(stderr, "lol Task 9 didnt open\n");

        exit(1);
    }

    FILE *create = fopen(create_file, "w");

    if (errno != 0) {
        fprintf(stderr, "lol Task 9 didnt open\n");

        exit(1);
    }

    int num, b;
    sscanf(border, "%d", &b);

    while (fscanf(source, "%d", &num) == 1)
        if (num < b)
            fprintf(create, "%d ", num);

    perror("Task 9 Read source");

    fclose(source);

    perror("Task 9 Read create");

    fclose(create);
}

void test_onlyLessNumFile(int argc, char *argv[]) {
    int nums[] = {5, 8, 7,2, 1, 6};

    writeNumsInFile(nums, 6, argv[2]);
    onlyLessNumFile(argv[1], argv[2], argv[3]);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Incorrect count of arguments\n");

        return 1;
    }

    test_onlyLessNumFile(argc, argv);

    return 0;
}