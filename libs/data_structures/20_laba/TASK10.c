# ifndef TASK10_H
# define TASK10_H

# include <stdio.h>
# include <signal.h>
# include "E:\C23Exe\libs\data_structures\19_laba\file.h"
# define MAX_LENGTH_STRING 200

void writeTextInFile(char *filename, char *text){
    FILE *f = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol Task 10 didnt open\n");

        exit(1);
    }

    fprintf(f, "%s", text);

    perror("Task 10 write writeTextInFile");

    fclose(f);
}

FILE *f;
int N;
bool flag = 1;

void printNLines(int param){
    char line[MAX_STRING_SIZE];

    for (int i = 0; i < N; i++) {
        if (fgets(line, MAX_STRING_SIZE, f))
            printf("%s", line);
        else
            exit(0);
    }
}

int main(int argc, char *argv[]){
    if (argc != 3) {
        printf("Incorrect count of arguments\n");

        return 1;
    }

    writeTextInFile(argv[1], "First\nSecond\nThird\nFourth");

    signal(SIGINT, &printNLines);
    N = atoi(argv[2]);
    f = fopen(argv[1], "r");
    getchar();

    if (errno != 0) {
        fprintf(stderr, "lol Task 10 didnt open\n");

        exit(1);
    }

    perror("Task 10 Read");

    fclose(f);

    return 0;
}

# endif