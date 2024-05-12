# ifndef FILE_H
# define FILE_H

# include "file.h"
# include "E:\C23Exe\libs\data_structures\matrix\matrix.h"
# include "E:\C23Exe\libs\data_structures\vector\vector.h"
# include "E:\C23Exe\libs\data_structures\void_vector\void_vector.h"
# include <memory.h>
# include <math.h>
# include "E:\C23Exe\libs\data_structures\string\string_.h"
# define NOT_ASCII -1
# define CHARACTERS 97

//транспонирует квадратную матрицу в файле
void squareMatricesFileTransponse(const char* filename) {
    FILE *f = fopen(filename, "r");

    if (errno != 0) {
        fprintf(stderr, "lol Task 1 didnt open\n");

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
        fprintf(stderr, "lol Task 1 didnt open\n");

        exit(1);
    }

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
    const char filename[] = "E:\\C23Exe\\libs\\data_structures\\19_laba\\1\\task.txt";

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
        fprintf(stderr, "lol Task 1 Test didnt open\n");

        exit(1);
    }

    fprintf(f, "%d\n", 3);

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

    perror("Task 1 Write test");

    fclose(f);

    transposeSquareMatrix(&m1);
    transposeSquareMatrix(&m2);

    squareMatricesFileTransponse(filename);

    f = fopen(filename, "r");

    if (errno != 0) {
        fprintf(stderr, "lol Task 1 Test didnt open\n");

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

//переводит число с фиксированной точкой в число с плавающей точкой.
void fixedPointIntoFloatPointFile(const char* filename) {
    FILE *f = fopen(filename, "r");

    if (errno != 0) {
        fprintf(stderr, "lol Task 2 didnt open\n");

        exit(1);
    }

    vectorVoid num = createVectorV(0, sizeof(float));
    vector count_of_digits = createVector(0);

    while (!feof(f)) {
        float x;
        fscanf(f, "%f", &x);

        pushBackV(&num, &x);
    }

    perror("Task 2 Read");

    fclose(f);

    for (int i = 0; i < num.size; i++){
        float x;

        getVectorValueV(&num, i, &x);

        int count = 0;

        if (abs(x) >= 1) {
            while (abs(x) >= 1) {
                x /= 10;
                count++;
            }

            x *= 10;
            count--;
        }else
            while (abs(x) < 1) {
                x *= 10;
                count--;
            }

        setVectorValueV(&num, i, &x);
        pushBack(&count_of_digits, count);
    }

    f = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol Task 2 didnt open\n");

        exit(1);
    }

    for (size_t i = 0; i < num.size; i++) {
        float x;
        int count;

        getVectorValueV(&num, i, &x);
        count = getVectorValue(&count_of_digits, i);

        fprintf(f, "%.2fE%d\n", x, count);
    }

    perror("Task 2 Write");

    fclose(f);

    clearV(&num);
    clear(&count_of_digits);
}

void test_fixedPointIntoFloatPointFile(){
    const char filename[] = "E:\\C23Exe\\libs\\data_structures\\19_laba\\2\\task.txt";

    float n1 = 100.1546;
    float n2 = 0.5346;
    float n3 = 0.000783;

    FILE *f = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol Task 2 Test didnt open\n");

        exit(1);
    }

    fprintf(f, "%f\n", n1);
    fprintf(f, "%f\n", n2);
    fprintf(f, "%f", n3);

    perror("Task 2 Write Test");

    fclose(f);

    fixedPointIntoFloatPointFile(filename);

    f = fopen(filename, "r");

    if (errno != 0) {
        fprintf(stderr, "lol Task 2 Test didnt open\n");

        exit(1);
    }

    FILE *f_test;

    const char filename_test[] = "E:\\C23Exe\\libs\\data_structures\\19_laba\\2\\test_task.txt";

    f_test = fopen(filename_test, "r");

    if (errno != 0) {
        fprintf(stderr, "lol Task 2 Test (test) didnt open\n");

        exit(1);
    }

    while (!feof(f_test)){
        char* s[100];
        char* s_test[100];

        fgets(s, 100, f);
        fgets(s_test, 100, f_test);

        assert(strcmp(s, s_test) == 0);

        perror("Task 2 s, s_test is equal");
    }

    perror("Task 2 Read Test file");

    fclose(f);

    perror("Task 2 Read Test file_test");

    fclose(f_test);
}

//решает арифметическое выражение из файла
void solveTextExpressionFile(const char* filename){
    FILE *f = fopen(filename, "r+");

    if (errno != 0) {
        fprintf(stderr, "lol Task 3 didnt open\n");

        exit(1);
    }

    int operand_1, operand_2, operand_3;
    char operator_1 = NOT_ASCII;
    char operator_2 = NOT_ASCII;
    float result;

    fscanf(f, "%d %c %d %c %d", &operand_1, &operator_1, &operand_2, &operator_2, &operand_3);

    if (operator_2 != NOT_ASCII){
        if (((operator_2 == '*') || (operator_2 == '/')) && (((operator_1 == '+') || (operator_1 == '-')))) {
            switch (operator_2) {
                case '/':
                    if (operand_3 == 0) {
                        fprintf(stderr, "operand 3 is zero\n");

                        exit(1);
                    }

                    result = operand_2 / operand_3;
                    break;
                case '*':
                    result = operand_2 * operand_3;
                    break;
                default:
                    fprintf(stderr, "not arithmetic operator\n");

                    exit(1);
            }

            switch (operator_1) {
                case '-':
                    result = operand_1 - result;
                    break;
                case '+':
                    result = operand_1 + result;
                    break;
                default:
                    fprintf(stderr, "not arithmetic operator\n");

                    exit(1);
            }
        }else{
            switch (operator_1) {
                case '+':
                    result = operand_1 + operand_2;
                    break;
                case '-':
                    result = operand_1 - operand_2;
                    break;
                case '*':
                    result = operand_1 * operand_2;
                    break;
                case '/':
                    if (operand_2 == 0) {
                        fprintf(stderr, "operand 3 is zero\n");

                        exit(1);
                    }

                    result = operand_1 / operand_2;
                    break;
                default:
                    fprintf(stderr, "not arithmetic operator\n");

                    exit(1);
            }

            switch (operator_2) {
                case '+':
                    result += operand_3;
                    break;
                case '-':
                    result -= operand_3;
                    break;
                case '*':
                    result *= operand_3;
                    break;
                case '/':
                    if (operand_3 == 0) {
                        fprintf(stderr, "operand 3 is zero\n");

                        exit(1);
                    }

                    result /= operand_3;
                    break;
                default:
                    fprintf(stderr, "not arithmetic operator\n");

                    exit(1);
            }
        }
    }else if (operator_1 != NOT_ASCII)
        switch (operator_1) {
            case '+':
                result = operand_1 + operand_2;
                break;
            case '-':
                result = operand_1 - operand_2;
                break;
            case '*':
                result = operand_1 * operand_2;
                break;
            case '/':
                if (operand_2 == 0) {
                    fprintf(stderr, "operand 3 is zero\n");

                    exit(1);
                }

                result = operand_1 / operand_2;
                break;
            default:
                fprintf(stderr, "not arithmetic operator\n");

                exit(1);
        }else
            result = operand_1;

    fseek(f, 0, SEEK_END);
    fprintf(f, " = %.2f", result);

    perror("Task 3 Read");

    fclose(f);
}

void test_solveTextExpressionFile_sampleAddition(){
    const char filename[] = "E:\\C23Exe\\libs\\data_structures\\19_laba\\3\\task_1.txt";

    FILE *f = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol Task 3 Test1 didnt open\n");

        exit(1);
    }

    char exp[] = "1+1";

    fputs(exp, f);

    perror("Task 3 Test1 Write");

    fclose(f);

    solveTextExpressionFile(filename);

    fopen(filename, "r");

    if (errno != 0) {
        fprintf(stderr, "lol Task 3 Test1 didnt open\n");

        exit(1);
    }

    char read_exp[100] = "";
    fgets(read_exp, 100, f);

    perror("Task 3 Test1 Read");

    fclose(f);

    char solve_exp[] = "1+1 = 2.00";

    assert(strcmp(read_exp, solve_exp) == 0);
}

void test_solveTextExpressionFile_sampleAdditionUnaryMinus(){
    const char filename[] = "E:\\C23Exe\\libs\\data_structures\\19_laba\\3\\task_2.txt";

    FILE *f = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol Task 3 Test2 didnt open\n");

        exit(1);
    }

    char exp[] = "-1+1";

    fputs(exp, f);

    perror("Task 3 Test2 Write");

    fclose(f);

    solveTextExpressionFile(filename);

    fopen(filename, "r");

    if (errno != 0) {
        fprintf(stderr, "lol Task 3 Test2 didnt open\n");

        exit(1);
    }

    char read_exp[100] = "";
    fgets(read_exp, 100, f);

    perror("Task 3 Test2 Read");

    fclose(f);

    char solve_exp[] = "-1+1 = 0.00";

    assert(strcmp(read_exp, solve_exp) == 0);
}

void test_solveTextExpressionFile_twoOperators(){
    const char filename[] = "E:\\C23Exe\\libs\\data_structures\\19_laba\\3\\task_3.txt";

    FILE *f = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol Task 3 Test3 didnt open\n");

        exit(1);
    }

    char exp[] = "1+5-9";

    fputs(exp, f);

    perror("Task 3 Test3 Write");

    fclose(f);

    solveTextExpressionFile(filename);

    fopen(filename, "r");

    if (errno != 0) {
        fprintf(stderr, "lol Task 3 Test3 didnt open\n");

        exit(1);
    }

    char read_exp[100] = "";
    fgets(read_exp, 100, f);

    perror("Task 3 Test3 Read");

    fclose(f);

    char solve_exp[] = "1+5-9 = -3.00";

    assert(strcmp(read_exp, solve_exp) == 0);
}

void test_solveTextExpressionFile_oneOperand(){
    const char filename[] = "E:\\C23Exe\\libs\\data_structures\\19_laba\\3\\task_4.txt";

    FILE *f = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol Task 3 Test4 didnt open\n");

        exit(1);
    }

    char exp[] = "2";

    fputs(exp, f);

    perror("Task 3 Test4 Write");

    fclose(f);

    solveTextExpressionFile(filename);

    fopen(filename, "r");

    if (errno != 0) {
        fprintf(stderr, "lol Task 3 Test4 didnt open\n");

        exit(1);
    }

    char read_exp[100] = "";
    fgets(read_exp, 100, f);

    perror("Task 3 Test4 Read");

    fclose(f);

    char solve_exp[] = "2 = 2.00";

    assert(strcmp(read_exp, solve_exp) == 0);
}

void test_solveTextExpressionFile_secondOperationHighestPriority(){
    const char filename[] = "E:\\C23Exe\\libs\\data_structures\\19_laba\\3\\task_5.txt";

    FILE *f = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol Task 3 Test5 didnt open\n");

        exit(1);
    }

    char exp[] = "1+9/3";

    fputs(exp, f);

    perror("Task 3 Test5 Write");

    fclose(f);

    solveTextExpressionFile(filename);

    fopen(filename, "r");

    if (errno != 0) {
        fprintf(stderr, "lol Task 3 Test5 didnt open\n");

        exit(1);
    }

    char read_exp[100] = "";
    fgets(read_exp, 100, f);

    perror("Task 3 Test5 Read");

    fclose(f);

    char solve_exp[] = "1+9/3 = 4.00";

    assert(strcmp(read_exp, solve_exp) == 0);
}

void test_solveTextExpressionFile(){
    test_solveTextExpressionFile_sampleAddition();
    test_solveTextExpressionFile_sampleAdditionUnaryMinus();
    test_solveTextExpressionFile_twoOperators();
    test_solveTextExpressionFile_oneOperand();
    test_solveTextExpressionFile_secondOperationHighestPriority();
}

bool lettersBelongWord(WordDescriptor letters_sequence, WordDescriptor word) {
    bool include[26] = {0};
    char* begin = word.begin;
    char* end = word.end + 1;

    while (begin != end) {
        if (isalpha(*begin))
            include[*begin - CHARACTERS] = 1;

        begin++;
    }

    while (letters_sequence.begin <= letters_sequence.end) {
        if (!include[*letters_sequence.begin - CHARACTERS])
            return 0;

        letters_sequence.begin++;
    }

    return 1;
}

int compar(const void* s1, const void* s2) {
    return *(const unsigned char*) s1 - *(const unsigned char*) s2;
}

char stringBuf[MAX_STRING_SIZE + 1];

//сохраняет только те слова, которые содержат данную последовательность символов
void saveOnlySpecialWordsFile(const char* filename, char* letters_sequence){
    FILE* file = fopen(filename, "r");

    if (errno != 0) {
        fprintf(stderr, "lol Task 4 didnt open\n");

        exit(1);
    }

    fseek(file, 0, SEEK_END);

    size_t length = ftell(file);

    fseek(file, 0, SEEK_SET);

    if (length == 0)
        return;

    fread(stringBuf, sizeof(char), length, file);

    stringBuf[length] = '\0';

    perror("Task 4 Read");

    fclose(file);

    WordDescriptor word;

    getWordWithoutSpace(letters_sequence, &word);
    qsort(word.begin, word.end - word.begin + 1, sizeof(char), compar);

    BagOfWords words = {.size = 0};
    char* begin_search = stringBuf;

    while (getWordWithoutSpace(begin_search, &words.words[words.size])) {
        begin_search = words.words[words.size].end + 1;
        words.size++;
    }

    file = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol Task 4 didnt open\n");

        exit(1);
    }

    for (size_t i = 0; i < words.size; i++) {
        if (lettersBelongWord(word, words.words[i])) {
            while (words.words[i].begin <= words.words[i].end) {
                fprintf(file, "%c", *words.words[i].begin);

                words.words[i].begin++;
            }

            fprintf(file, " ");
        }
    }

    fprintf(file, "%c", '\0');

    perror("Task 4 Write");

    fclose(file);
}

void test_saveOnlySpecialWordsFile_zeroWordsInFile(){
    const char filename[] = "E:\\C23Exe\\libs\\data_structures\\19_laba\\4\\task_1.txt";

    FILE *f = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol Task 4 Test1 didnt open\n");

        exit(1);
    }

    fputs("", f);

    perror("Task 4 Test1 Write");

    fclose(f);

    char letters_sequence[] = "baobab";

    saveOnlySpecialWordsFile(filename, letters_sequence);

    f = fopen(filename, "r");

    if (errno != 0) {
        fprintf(stderr, "lol Task 4 Test1 didnt open\n");

        exit(1);
    }

    char read_words[100] = "";
    fgets(read_words, 100, f);

    perror("Task 4 Test1 Read");

    fclose(f);

    assert(strcmp(read_words, "") == 0);
}

void test_saveOnlySpecialWordsFile_noOneWillSave(){
    const char filename[] = "E:\\C23Exe\\libs\\data_structures\\19_laba\\4\\task_2.txt";

    FILE *f = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol Task 4 Test2 didnt open\n");

        exit(1);
    }

    fputs("aboba", f);

    perror("Task 4 Test2 Write");

    fclose(f);

    char letters_sequence[] = "pepe";

    saveOnlySpecialWordsFile(filename, letters_sequence);

    f = fopen(filename, "r");

    if (errno != 0) {
        fprintf(stderr, "lol Task 4 Test2 didnt open\n");

        exit(1);
    }

    char read_words[100] = "";
    fgets(read_words, 100, f);

    perror("Task 4 Test2 Read");

    fclose(f);

    assert(strcmp(read_words, "") == 0);
}

void test_saveOnlySpecialWordsFile_wordWillSave(){
    const char filename[] = "E:\\C23Exe\\libs\\data_structures\\19_laba\\4\\task_3.txt";

    FILE *f = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol Task 4 Test3 didnt open\n");

        exit(1);
    }

    fputs("AABBAAAA AAAAAA DDDDCCC", f);

    perror("Task 4 Test3 Write");

    fclose(f);

    char letters_sequence[] = "AABB";

    saveOnlySpecialWordsFile(filename, letters_sequence);

    f = fopen(filename, "r");

    if (errno != 0) {
        fprintf(stderr, "lol Task 4 Test3 didnt open\n");

        exit(1);
    }

    char read_words[100] = "";
    fgets(read_words, 100, f);

    perror("Task 4 Test3 Read");

    fclose(f);

    assert(strcmp(read_words, "AABBAAAA ") == 0);
}

void test_saveOnlySpecialWordsFile(){
    test_saveOnlySpecialWordsFile_zeroWordsInFile();
    test_saveOnlySpecialWordsFile_noOneWillSave();
    test_saveOnlySpecialWordsFile_wordWillSave();
}

//проводит автоматизированное тестирование функций
void testFile(){
    test_squareMatrixFileTransponse();
    test_fixedPointIntoFloatPointFile();
    test_solveTextExpressionFile();
    test_saveOnlySpecialWordsFile();
}

# endif