# ifndef FILE_H
# define FILE_H

# include "file.h"
# include "E:\C23Exe\libs\data_structures\matrix\matrix.h"
# include "E:\C23Exe\libs\data_structures\vector\vector.h"
# include "E:\C23Exe\libs\data_structures\void_vector\void_vector.h"
# include <memory.h>
# include <math.h>
# include <time.h>
# include "E:\C23Exe\libs\data_structures\string\string_.h"
# define NOT_ASCII -1
# define CHARACTERS 97
# define MAX_LENGTH_STRING 200
# define MAX_AMOUNT_SPORTSMAN 20

void generateRandomSquareMatrixFile(const char *filename, size_t n) {
    srand(time(NULL));

    FILE *f = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol generateRandomMatrixFile didnt open\n");

        exit(1);
    }

    fprintf(f, "%lld\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++)
            fprintf(f, "%d ", rand() % 10);

        fprintf(f, "\n");
    }

    perror("generateRandomMatrixFile Write");

    fclose(f);
}

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

    free(n_array);
    freeMemMatrices(ms, count_of_matrices);
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

void generateFloatFile(const char* filename, int n) {
    srand(time(NULL));

    FILE* f = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol generateFloat didnt open\n");

        exit(1);
    }

    for (size_t i = 0; i < n; i++)
        fprintf(f, "%f ", 10.0 * rand() / RAND_MAX);

    perror("generateFloat Write");

    fclose(f);
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

void generateExpressionFile(char *filename) {
    srand(time(NULL));

    FILE *f = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol generateExpression didnt open\n");

        exit(1);
    }

    int n1 = rand() % 10;
    int n2 = rand() % 10;
    int n3 = rand() % 10;

    char operators[] = "*+-/";

    char operator_1 = operators[rand() % 4];
    char operator_2 = operators[rand() % 4];

    if (rand() % 2) {
        fprintf(f, "%d %c %d", n1, operator_1, n2);
    } else
        fprintf(f, "%d %c %d %c %d", n1, operator_1, n2, operator_2, n3);

    perror("generateExpression Write");

    fclose(f);
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
            case NOT_ASCII:
                result = operand_1;
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
            case NOT_ASCII:
                break;
            default:
                fprintf(stderr, "not arithmetic operator\n");

                exit(1);
        }
    }

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

void generateStringFile(const char* filename, char* source_string) {
    FILE* f = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol generateStringFile didnt open\n");

        exit(1);
    }

    int string_length = strlen_(source_string);

    for (size_t i = 0; i <= string_length; i++)
        fprintf(f, "%c", source_string[i]);

    perror("generateStringFile Write");

    fclose(f);
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

void generateStringsFile(const char *filename, int lines, int count_of_words) {
    srand(time(NULL));

    FILE *f = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol generateStringsFile didnt open\n");

        exit(1);
    }

    int word_size = rand() % lines;

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < count_of_words; ++j) {
            for (int k = 0; k < rand() % word_size + 1; ++k)
                fprintf(f, "%c", 'a');

            fprintf(f, " ");
        }

        fprintf(f, "\n");
    }

    perror("generateStringsFile Write");

    fclose(f);
}

BagOfWords bag;

//оставляет только самое длинное слово в файле
void onlyLongestWordFile(const char* filename){
    FILE* file = fopen(filename, "r");

    if (errno != 0) {
        fprintf(stderr, "lol Task 5 didnt open\n");

        exit(1);
    }

    char buff[MAX_WORD_SIZE] = "";
    char* rec_ptr = stringBuf;

    fgets(buff, sizeof(buff), file);

    size_t length = strlen_(buff);

    length = length == 0 ? 1 : length;

    rec_ptr = copy(buff, buff + length - 1, rec_ptr);
    *rec_ptr++ = ' ';

    size_t amount_word_in_line = 0;
    char* begin_search = stringBuf;

    while (getWordWithoutSpace(begin_search, &bag.words[bag.size])) {
        begin_search = bag.words[bag.size].end + 1;
        amount_word_in_line++;
        bag.size++;
    }

    while (fgets(buff, sizeof(buff), file)) {
        rec_ptr = copy(buff, buff + strlen_(buff) - 1, rec_ptr);
        *rec_ptr++ = ' ';

        while (getWordWithoutSpace(begin_search, &bag.words[bag.size])) {
            begin_search = bag.words[bag.size].end + 1;
            bag.size++;
        }
    }

    perror("Task 5 Read");

    fclose(file);

    file = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol Task 5 didnt open\n");

        exit(1);
    }

    for (size_t i = 0; i < bag.size; i += amount_word_in_line) {
        WordDescriptor word_max_length = bag.words[i];
        size_t max_length = word_max_length.end - word_max_length.begin + 1;

        for (size_t j = i + 1; j < i + amount_word_in_line; j++) {
            size_t current_length = bag.words[j].end - bag.words[j].begin + 1;

            if (current_length > max_length) {
                word_max_length = bag.words[j];
                max_length = current_length;
            }
        }

        char* write_ptr = word_max_length.begin;

        while (write_ptr <= word_max_length.end) {
            fprintf(file, "%c", *write_ptr);

            write_ptr++;
        }

        fprintf(file, "\n");
    }

    freeBagOfWords(&bag);

    perror("Task 5 Write");

    fclose(file);
}

void test_onlyLongestWordFile(){
    const char filename[] = "E:\\C23Exe\\libs\\data_structures\\19_laba\\5\\task.txt";

    FILE *f = fopen(filename, "w");

    if (errno != 0) {
        fprintf(stderr, "lol Task 5 Test didnt open\n");

        exit(1);
    }

    char s1[] = "barbiturat";
    char s2[] = "bar";

    fprintf(f, "%s\n", s1);
    fprintf(f, "%s\n", s2);

    perror("Task 5 Test Write");

    fclose(f);

    onlyLongestWordFile(filename);

    f = fopen(filename, "r");

    if (errno != 0) {
        fprintf(stderr, "lol Task 5 Test didnt open\n");

        exit(1);
    }

    char s1_read[50] = "";
    fscanf(f, "%s\n", s1_read);

    char s2_read[50] = "";
    fscanf(f, "%s\n", s2_read);

    assert((strcmp(s1_read, "barbiturat") == 0) && (strcmp(s2_read, "") == 0));
}

typedef struct monomial {
    int degree;
    double coefficient;
} monomial;

double getValueOfMonomial(struct monomial mono, double x) {
    return pow(x, mono.degree) * mono.coefficient;
}

void generatePolynomialFile(const char *filename) {
    srand(time(NULL));

    FILE *f = fopen(filename, "wb");

    if (errno != 0) {
        fprintf(stderr, "lol generatePolynomialFile didnt open\n");

        exit(1);
    }

    int count_of_polynamial = rand() % + 2;

    for (int i = 0; i < count_of_polynamial; ++i) {
        count_of_polynamial = rand() % + 2;

        monomial mono;

        for (int j = 0; j <= count_of_polynamial; ++j) {
            mono.degree = count_of_polynamial - i;
            mono.coefficient = 2.0 * rand() / RAND_MAX - 1.0;

            fwrite(&mono, sizeof(monomial), 1, f);
        }
    }

    perror("generatePolynomialFile Write binary");

    fclose(f);
}

//Удаляет многочлен, чей x является корнем
void deletePolynomialFile(const char *filename, double x) {
    vectorVoid v = createVectorV(16, sizeof(monomial));

    FILE *file = fopen(filename, "rb");

    if (errno != 0) {
        fprintf(stderr, "lol Task 6 didnt open\n");

        exit(1);
    }

    monomial mono;

    while (fread(&mono, sizeof(monomial), 1, file) == 1)
        pushBackV(&v, &mono);

    perror("Task 6 Read binary");

    fclose(file);

    file = fopen(filename, "wb");

    if (errno != 0) {
        fprintf(stderr, "lol Task 6 didnt open\n");

        exit(1);
    }

    monomial m;

    vectorVoid temp = createVectorV(8, sizeof(monomial));

    double result = 0;

    for (size_t i = 0; i < v.size; i++) {
        getVectorValueV(&v, i, &m);
        pushBackV(&temp, &m);

        result += getValueOfMonomial(m, x);

        if (m.degree == 0) {
            if (fabs(result) >= 0.001) {
                monomial temp_mono;

                for (size_t j = 0; j < temp.size; j++) {
                    getVectorValueV(&temp, j, &temp_mono);

                    fwrite(&temp_mono, sizeof(monomial), 1, file);
                }
            }

            result = 0;
        }
    }

    perror("Task 6 Write binary");

    fclose(file);

    clearV(&v);
    clearV(&temp);
}

void test_deletePolynomialFile(){
    char filename[] = "E:\\C23Exe\\libs\\data_structures\\19_laba\\6\\task.txt";

    double x = 2.0;
    monomial x1 = {.coefficient = 3.0, .degree = 2.0};
    monomial x2 = {.coefficient = 10, .degree = -2};
    monomial x3 = {.coefficient = 0, .degree = 0};

    FILE *file = fopen(filename, "wb");

    if (errno != 0) {
        fprintf(stderr, "lol Task 6 Test didnt open\n");

        exit(1);
    }

    fwrite(&x1, sizeof(monomial), 1, file);
    fwrite(&x2, sizeof(monomial), 1, file);
    fwrite(&x3, sizeof(monomial), 1, file);

    perror("Task 6 Write Test binary");

    fclose(file);

    deletePolynomialFile(filename, x);

    file = fopen(filename, "rb");

    if (errno != 0) {
        fprintf(stderr, "lol Task 6 Test didnt open\n");

        exit(1);
    }

    monomial res_x1;
    fread(&res_x1, sizeof(monomial), 1, file);

    monomial res_x2;
    fread(&res_x2, sizeof(monomial), 1, file);

    monomial res_x3;
    fread(&res_x3, sizeof(monomial), 1, file);

    perror("Task 6 Read Test binary");

    fclose(file);

    assert(x1.coefficient - res_x1.coefficient <= 0.0001 && x1.degree == res_x1.degree);
    assert(x2.coefficient - res_x2.coefficient <= 0.0001 && x2.degree == res_x2.degree);
    assert(x3.coefficient - res_x3.coefficient <= 0.0001 && x3.degree == res_x3.degree);
}

void generateNumbersFile(char *filename){
    srand(time(NULL));

    FILE *f = fopen(filename, "wb");

    if (errno != 0) {
        fprintf(stderr, "lol generateNumbersFile didnt open\n");

        exit(1);
    }

    int count_of_numbers = (int) rand() % 10 + 1;

    for (int i = 0; i < count_of_numbers; ++i) {
        int x = rand() % 200 - 100;

        fwrite(&x, sizeof(int), 1, f);
    }

    perror("generateNumbersFile Write binary");

    fclose(f);
}

//Перемещает положительные числа в начало, а отрицательные - в конец
void positiveNegativeOrderFile(const char* filename){
    vector positive_num = createVector(2);
    vector negative_num = createVector(2);

    FILE* f = fopen(filename, "rb");

    if (errno != 0) {
        fprintf(stderr, "lol Task 7 didnt open\n");

        exit(1);
    }

    int curr;

    while (fread(&curr, sizeof(int), 1, f) == 1) {
        if (curr >= 0)
            pushBack(&positive_num, curr);
        else
            pushBack(&negative_num, curr);
    }

    perror("Task 7 Read binary");

    fclose(f);

    f = fopen(filename, "wb");

    if (errno != 0) {
        fprintf(stderr, "lol Task 7 didnt open\n");

        exit(1);
    }

    for (int i = 0; i < positive_num.size; i++)
        fwrite(positive_num.data + i, sizeof(int), 1, f);

    for (int i = 0; i < negative_num.size; i++)
        fwrite(negative_num.data + i, sizeof(int), 1, f);

    deleteVector(&positive_num);
    deleteVector(&negative_num);

    perror("Task 7 Write binary");

    fclose(f);
}

void test_positiveNegativeOrderFile_negative(){
    const char filename[] = "E:\\C23Exe\\libs\\data_structures\\19_laba\\7\\task_1.txt";

    int n1 = -712;
    int n2 = -5556;
    int n3 = -456;

    FILE *file = fopen(filename, "wb");

    if (errno != 0) {
        fprintf(stderr, "lol Task 7 Test1 didnt open\n");

        exit(1);
    }

    fwrite(&n1, sizeof(int), 1, file);
    fwrite(&n2, sizeof(int), 1, file);
    fwrite(&n3, sizeof(int), 1, file);

    perror("Task 7 Write Test1 binary");

    fclose(file);

    positiveNegativeOrderFile(filename);

    file = fopen(filename, "rb");

    if (errno != 0) {
        fprintf(stderr, "lol Task 7 Test1 didnt open\n");

        exit(1);
    }

    int read_n1, read_n2, read_n3;

    fread(&read_n1, sizeof(int), 1, file);
    fread(&read_n2, sizeof(int), 1, file);
    fread(&read_n3, sizeof(int), 1, file);

    perror("Task 7 Read Test1 binary");

    fclose(file);

    assert(n1 == read_n1);
    assert(n2 == read_n2);
    assert(n3 == read_n3);
}

void test_positiveNegativeOrderFile_positive(){
    const char filename[] = "E:\\C23Exe\\libs\\data_structures\\19_laba\\7\\task_2.txt";

    int n1 = 712;
    int n2 = 5556;
    int n3 = 456;

    FILE *file = fopen(filename, "wb");

    if (errno != 0) {
        fprintf(stderr, "lol Task 7 Test2 didnt open\n");

        exit(1);
    }

    fwrite(&n1, sizeof(int), 1, file);
    fwrite(&n2, sizeof(int), 1, file);
    fwrite(&n3, sizeof(int), 1, file);

    perror("Task 7 Write Test2 binary");

    fclose(file);

    positiveNegativeOrderFile(filename);

    file = fopen(filename, "rb");

    if (errno != 0) {
        fprintf(stderr, "lol Task 7 Test2 didnt open\n");

        exit(1);
    }

    int read_n1, read_n2, read_n3;

    fread(&read_n1, sizeof(int), 1, file);
    fread(&read_n2, sizeof(int), 1, file);
    fread(&read_n3, sizeof(int), 1, file);

    perror("Task 7 Read Test2 binary");

    fclose(file);

    assert(n1 == read_n1);
    assert(n2 == read_n2);
    assert(n3 == read_n3);
}

void test_positiveNegativeOrderFile_positiveAndNegative(){
    const char filename[] = "E:\\C23Exe\\libs\\data_structures\\19_laba\\7\\task_3.txt";

    int n1 = -712;
    int n2 = 5556;
    int n3 = -456;

    FILE *file = fopen(filename, "wb");

    if (errno != 0) {
        fprintf(stderr, "lol Task 7 Test3 didnt open\n");

        exit(1);
    }

    fwrite(&n1, sizeof(int), 1, file);
    fwrite(&n2, sizeof(int), 1, file);
    fwrite(&n3, sizeof(int), 1, file);

    perror("Task 7 Write Test2 binary");

    fclose(file);

    positiveNegativeOrderFile(filename);

    file = fopen(filename, "rb");

    if (errno != 0) {
        fprintf(stderr, "lol Task 7 Test3 didnt open\n");

        exit(1);
    }

    int read_n1, read_n2, read_n3;

    fread(&read_n1, sizeof(int), 1, file);
    fread(&read_n2, sizeof(int), 1, file);
    fread(&read_n3, sizeof(int), 1, file);

    perror("Task 7 Read Test3 binary");

    fclose(file);

    assert(n2 == read_n1);
    assert(n1 == read_n2);
    assert(n3 == read_n3);
}

void test_positiveNegativeOrderFile(){
    test_positiveNegativeOrderFile_negative();
    test_positiveNegativeOrderFile_positive();
    test_positiveNegativeOrderFile_positiveAndNegative();
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void transpMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++)
        for (int j = i + 1; j < m->nCols; j++)
            swap(&m->values[i][j], &m->values[j][i]);
}

void generateNonSymmetricSquareMatrixFile(const char *filename) {
    srand(time(NULL));

    FILE *f = fopen(filename, "wb");

    if (errno != 0) {
        fprintf(stderr, "lol generateNonSymmetricSquareMatrix didnt open\n");

        exit(1);
    }

    int n = rand() % 2 + 2;
    fwrite(&n, sizeof(int), 1, f);
    int count_of_matrix = rand() % 3 + 1;

    for (int k = 0; k < count_of_matrix; k++) {
        matrix m = getMemMatrix(n, n);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                m.values[i][j] = rand() % 100;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                fwrite(&m.values[i][j], sizeof(int), n * n, f);

        freeMemMatrix(&m);
    }

    perror("generateNonSymmetricSquareMatrix Write binary");

    fclose(f);
}

void generateSymmetricMatrixFile(const char *filename) {
    srand(time(NULL));

    FILE *f = fopen(filename, "wb");

    if (errno != 0) {
        fprintf(stderr, "lol generateSymmetricMatrix didnt open\n");

        exit(1);
    }

    int n = rand() % 2 + 2;
    fwrite(&n, sizeof(int), 1, f);
    int count_of_matrix = rand() % 3 + 1;

    for (int k = 0; k < count_of_matrix; k++) {
        matrix m = getMemMatrix(n, n);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i < j){
                    m.values[i][j] = rand() % 100;
                    m.values[i][j] = m.values[j][i];
                }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                fwrite(&m.values[i][j], sizeof(int), n * n, f);

        freeMemMatrix(&m);
    }

    perror("generateSymmetricMatrix Write binary");

    fclose(f);
}

//транспонирует матрицу в файле, если она не симметрична
void transposeNonSymmetricMatrixFile(const char *filename) {
    FILE *f = fopen(filename, "r+b");

    if (errno != 0) {
        fprintf(stderr, "lol Task 8 didnt open\n");

        exit(1);
    }

    int n;
    fread(&n, sizeof(int), 1, f);

    while (!feof(f)) {
        matrix m = getMemMatrix(n, n);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                fread(&m.values[i][j], sizeof(int), 1, f);

        if (!isSymmetricMatrix(&m)) {
            transpMatrix(&m);

            int count_of_elements = n * n;

            fseek(f, -(long int) count_of_elements * sizeof(int), SEEK_CUR);

            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    fwrite(&m.values[i][j], sizeof(int), 1, f);

            fseek(f, (long int) count_of_elements * sizeof(int), SEEK_CUR);
        }

        freeMemMatrix(&m);
    }

    perror("Task 8 Read binary");

    fclose(f);
}

void test_transposeNonSymmetricMatrixFile(){
    const char filename[] = "E:\\C23Exe\\libs\\data_structures\\19_laba\\8\\task.txt";

    FILE *f = fopen(filename, "wb");

    if (errno != 0) {
        fprintf(stderr, "lol Task 8 Test didnt open\n");

        exit(1);
    }

    int n = 3;

    matrix m1 = createMatrixFromArray((int[]) {1, 0, 0,
                                               0, 1, 0,
                                               0, 0, 1}, 3, 3);

    matrix m2 = createMatrixFromArray((int[]) {5, 6, 9,
                                               6, 5, 6,
                                               7, 8, 9}, 3, 3);

    fwrite(&n, sizeof(int), 1, f);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fwrite(&m1.values[i][j], sizeof(int), 1, f);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fwrite(&m2.values[i][j], sizeof(int), 1, f);

    perror("Task 8 Write Test binary");

    fclose(f);

    transposeNonSymmetricMatrixFile(filename);

    f = fopen(filename, "rb");

    if (errno != 0) {
        fprintf(stderr, "lol Task 8 Test didnt open\n");

        exit(1);
    }

    int read_n;

    matrix check1 = createMatrixFromArray((int[]) {1, 0, 0,
                                                   0, 1, 0,
                                                   0, 0, 1}, 3, 3);

    matrix check2 = createMatrixFromArray((int[]) {5, 6, 7,
                                                   6, 5, 8,
                                                   9, 6, 9}, 3, 3);

    fread(&read_n, sizeof(int), 1, f);

    matrix read_m1 = getMemMatrix(read_n, read_n);
    matrix read_m2 = getMemMatrix(read_n, read_n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fread(&read_m1.values[i][j], sizeof(int), 1, f);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fread(&read_m2.values[i][j], sizeof(int), 1, f);

    perror("Task 8 Read Test binary");

    fclose(f);

    assert((areTwoMatricesEqual(&read_m1, &check1)) && (areTwoMatricesEqual(&read_m2, &check2)) && (read_n == n));

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
    freeMemMatrix(&check1);
    freeMemMatrix(&check2);
    freeMemMatrix(&read_m1);
    freeMemMatrix(&read_m2);
}

typedef struct sportsman {
    char name[MAX_LENGTH_STRING];
    int max_result;
} sportsman;

static void generateNameFile(char *s) {
    int name_length = rand() % 30 + 5;

    char *rec_ptr = s;

    for (int i = 0; i < name_length; i++) {
        *rec_ptr = rand() % 26 + 97;
        rec_ptr++;
    }

    *rec_ptr = '\0';
}

void generateTeamFile(const char *filename, const int n) {
    srand(time(NULL));

    FILE *f = fopen(filename, "wb");

    if (errno != 0) {
        fprintf(stderr, "lol generateTeamFile didnt open\n");

        exit(1);
    }

    for (int i = 0; i < n; i++) {
        sportsman s;

        generateNameFile(s.name);

        s.max_result = (double) rand() / 100;

        fwrite(&s, sizeof(sportsman), 1, f);
    }

    perror("generateTeamFile Write binary");

    fclose(f);
}

void fromHiToLo(sportsman sm[], const int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (sm[j].max_result < sm[j + 1].max_result) {
                sportsman temp = sm[j];

                sm[j] = sm[j + 1];
                sm[j + 1] = temp;
            }
}

//Отбирает лучших спортсменов в команду
void createBestTeamFile(const char *filename, const int n){
    FILE *f = fopen(filename, "rb");

    if (errno != 0) {
        fprintf(stderr, "lol Task 9 didnt open\n");

        exit(1);
    }

    sportsman *team = (sportsman*)malloc(MAX_AMOUNT_SPORTSMAN * sizeof(sportsman));
    sportsman *rec = team;

    int count_of_sportsmans = 0;

    while (fread(rec, sizeof(sportsman), 1, f) == 1) {
        rec++;
        count_of_sportsmans++;
    }

    perror("Task 9 Read binary");

    fclose(f);

    f = fopen(filename, "wb");

    if (errno != 0) {
        fprintf(stderr, "lol Task 9 didnt open\n");

        exit(1);
    }

    fromHiToLo(team, count_of_sportsmans);

    int count_of_sportsmans_in_team = count_of_sportsmans >= n ? n : count_of_sportsmans;

    for (int i = 0; i < count_of_sportsmans_in_team; i++) {
        fwrite(team + i, sizeof(sportsman), 1, f);
    }

    free(team);

    perror("Task 9 Write binary");

    fclose(f);
}

void test_createBestTeamFile(){
    char filename[] = "E:\\C23Exe\\libs\\data_structures\\19_laba\\9\\task.txt";

    FILE *f = fopen(filename, "wb");

    if (errno != 0) {
        fprintf(stderr, "lol Task 9 Test didnt open\n");

        exit(1);
    }

    sportsman s1 = {.name = "Max", .max_result = 395};
    sportsman s2 = {.name = "Lewis", .max_result = 395};
    sportsman s3 = {.name = "Alonso", .max_result = 393};
    sportsman s4 = {.name = "Sorgio", .max_result = 396};
    sportsman s5 = {.name = "Estenba", .max_result = 200};

    fwrite(&s1, sizeof(sportsman), 1, f);
    fwrite(&s2, sizeof(sportsman), 1, f);
    fwrite(&s3, sizeof(sportsman), 1, f);
    fwrite(&s4, sizeof(sportsman), 1, f);
    fwrite(&s5, sizeof(sportsman), 1, f);

    perror("Task 9 Write Test binary");

    fclose(f);

    createBestTeamFile(filename, 5);

    f = fopen(filename, "rb");

    if (errno != 0) {
        fprintf(stderr, "lol Task 9 Test didnt open\n");

        exit(1);
    }

    sportsman read_s1, read_s2, read_s3, read_s4;

    fread(&read_s1, sizeof(sportsman), 1, f);
    fread(&read_s2, sizeof(sportsman), 1, f);
    fread(&read_s3, sizeof(sportsman), 1, f);
    fread(&read_s4, sizeof(sportsman), 1, f);

    perror("Task 9 Read Test binary");

    fclose(f);

    assert((strcmp(&s4.name, &read_s1.name) == 0) && (strcmp(&s1.name, &read_s2.name) == 0)
            && (strcmp(&s2.name, &read_s3.name) == 0) && (strcmp(&s3.name, &read_s4.name) == 0));
}

typedef struct warehouse {
    char *name_of_product;
    int price;
    int total_cost;
    int quantity;
} warehouse;

typedef struct order {
    char *order_name;
    int quantity;
} order;

void generateWarehouseAndOrders(const char* f_filename, const char* q_filename) {
    srand(time(NULL));

    FILE* f = fopen(f_filename, "wb");

    if (errno != 0) {
        fprintf(stderr, "generateWarehouseAndOrders didnt open\n");

        exit(1);
    }

    FILE* q = fopen(q_filename, "wb");

    if (errno != 0) {
        fprintf(stderr, "generateWarehouseAndOrders didnt open\n");

        exit(1);
    }

    int count_of_product = rand() % 15 + 1;
    int count_of_order = count_of_product % 2 + 1;

    for (int i = 0; i < count_of_product; i++) {
        warehouse product = {.price = rand() % 100 + 1, .quantity = rand() % 20 + 1, .total_cost = product.price * product.quantity};
        order ord;

        int name_length = rand() % 10 + 1;
        char* product_rec_ptr = product.name_of_product;
        char* order_rec_ptr = ord.order_name;

        for (int j = 0; j < name_length; j++) {
            char ch = rand() % 26 + 97;

            *product_rec_ptr = ch;
            product_rec_ptr++;

            if (count_of_order > 0) {
                *order_rec_ptr = ch;
                order_rec_ptr++;
            }
        }

        *product_rec_ptr = '\0';

        if (count_of_order > 0) {
            *order_rec_ptr = '\0';

            ord.quantity = rand() % 25 + 1;
        }

        fwrite(&product, sizeof(warehouse), 1, f);

        if (count_of_order > 0)
            fwrite(&ord, sizeof(order), 1, q);


        count_of_order--;
    }

    perror("generateWarehouseAndOrders F Write binary");

    fclose(f);

    perror("generateWarehouseAndOrders Q Write binary");

    fclose(q);
}

//Обновляет информацию в файле f об оставшихся продуктах на складе, исходя из информации о заказах в файле q
void refreshInformationFile(const char* f_filename, size_t *products_size, const char* q_filename, size_t orders_size){
    FILE *file;
    warehouse products[*products_size];
    order orders[orders_size];
    size_t products_left_size = 0;
    warehouse products_left[*products_size];

    file = fopen(f_filename, "rb");

    fread(products, sizeof(warehouse), *products_size, file);

    fclose(file);

    file = fopen(q_filename, "rb");

    fread(orders, sizeof(order), orders_size, file);

    fclose(file);

    for (size_t j = 0; j < *products_size; j++) {
        for (size_t i = 0; i < orders_size; i++) {
            if (products[j].name_of_product == orders[i].order_name) {
                if (products[j].quantity > orders[i].quantity) {
                    products_left[products_left_size].name_of_product = orders[i].order_name;
                    products_left[products_left_size].price = products[j].price;
                    products_left[products_left_size].quantity = products[j].quantity - orders[i].quantity;
                    products_left[products_left_size].total_cost = products_left[products_left_size].price * products_left[products_left_size].quantity;
                    products_left_size++;
                }
            }
        }
    }

    *products_size = products_left_size;

    file = fopen(f_filename, "wb");

    fwrite(products_left, sizeof(warehouse), products_left_size, file);

    fclose(file);
}

void test_refreshInformationFile(){
    const char f_filename[] = "E:\\C23Exe\\libs\\data_structures\\19_laba\\10\\f.txt";
    const char q_filename[] = "E:\\C23Exe\\libs\\data_structures\\19_laba\\10\\q.txt";

    size_t count_of_product = 2;
    warehouse p1 = {.name_of_product = "bread", .price = 5, .total_cost = 15, .quantity = 3};
    warehouse p2 = {.name_of_product = "butter", .price = 7, .total_cost = 14, .quantity = 2};
    size_t count_of_order = 2;
    order ord1 = {.order_name = "bread", .quantity = 2};
    order ord2 = {.order_name = "butter", .quantity = 5};

    FILE* f = fopen(f_filename, "wb");

    if (errno != 0) {
        fprintf(stderr, "lol Task 10 Test didnt open\n");

        exit(1);
    }

    fwrite(&p1, sizeof(warehouse), 1, f);
    fwrite(&p2, sizeof(warehouse), 1, f);

    perror("Task 10 F Write binary");

    fclose(f);

    f = fopen(q_filename, "wb");

    if (errno != 0) {
        fprintf(stderr, "lol Task 10 Test didnt open\n");

        exit(1);
    }

    fwrite(&ord1, sizeof(order), 1, f);
    fwrite(&ord2, sizeof(order), 1, f);

    perror("Task 10 Q Write binary");

    fclose(f);

    refreshInformationFile(f_filename, &count_of_product, q_filename, count_of_order);

    warehouse read_product;

    f = fopen(f_filename, "rb");

    if (errno != 0) {
        fprintf(stderr, "lol Task 10 Test didnt open\n");

        exit(1);
    }

    fread(&read_product, sizeof(warehouse), 1, f);

    perror("Task 10 F Read binary");

    fclose(f);

    assert((strcmp(p1.name_of_product, read_product.name_of_product) == 0) && (read_product.quantity == 1) && (read_product.total_cost == 5));
}

void fulfillQuery(matrix *m, matrix *array_of_query){
    for (size_t i = 0; i < array_of_query->nRows; i++)
        for (size_t j = array_of_query->values[i][0]; j <=  array_of_query->values[i][2]; j++)
            for (size_t k = array_of_query->values[i][1]; k <=  array_of_query->values[i][3]; k++)
                m->values[j][k]++;
}

void test_fulfillQuery(){
    matrix m = createMatrixFromArray((int []){
                                    0,0,0,
                                    0,0,0,
                                    0,0,0
    }, 3, 3);

    matrix array_of_query = createMatrixFromArray((int []){
            1,1,2, 2,
            0,0,1, 1
    }, 2, 4);

    fulfillQuery(&m, &array_of_query);

    matrix expected_m = createMatrixFromArray((int []){
            1,1,0,
            1,2,1,
            0,1,1
    }, 3, 3);

    assert(areTwoMatricesEqual(&m, &expected_m));

    freeMemMatrix(&m);
    freeMemMatrix(&array_of_query);
    freeMemMatrix(&expected_m);
}

size_t countOfNeighbors(matrix m, int row, int col){
    size_t count_of_neighbors = 0;

    for (int i = row - 1; i < row + 2; i++)
        for (int j = col - 1; j < col + 2; j++)
            if ((i > -1 && i < m.nRows && j > -1 && j < m.nCols) && m.values[i][j] && (row != i || col != j))
                count_of_neighbors++;

    return count_of_neighbors;
}

bool isAlive(matrix m, int i, int j, size_t count_of_neighbors) {
    return ((m.values[i][j] == 1 && (count_of_neighbors == 2 || count_of_neighbors == 3)) || (m.values[i][j] == 0 && count_of_neighbors == 3));
}

matrix live(matrix m){
    matrix refreshedMatrix = getMemMatrix(m.nRows, m.nCols);

    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; j++) {
            size_t count_neighbors = countOfNeighbors(m, i, j);

            refreshedMatrix.values[i][j] = isAlive(m, i, j, count_neighbors);
        }

    return refreshedMatrix;
}

void test_live(){
    matrix m = createMatrixFromArray((int[]) {
                                                 0, 1, 0,
                                                 0, 0, 1,
                                                 1, 1, 1,
                                                 0, 0, 0},
                                         4, 3);
    matrix refreshedM = live(m);
    matrix expected_m = createMatrixFromArray((int[]) {
                                                    0, 0, 0,
                                                    1, 0, 1,
                                                    0, 1, 1,
                                                    0, 1, 0},
                                            4, 3);

    assert(areTwoMatricesEqual(&refreshedM, &expected_m));

    freeMemMatrix(&m);
    freeMemMatrix(&refreshedM);
    freeMemMatrix(&expected_m);
}

//проводит автоматизированное тестирование функций
void testFile(){
    test_squareMatrixFileTransponse();
    test_fixedPointIntoFloatPointFile();
    test_solveTextExpressionFile();
    test_saveOnlySpecialWordsFile();
    test_onlyLongestWordFile();
    test_deletePolynomialFile();
    test_positiveNegativeOrderFile();
    test_transposeNonSymmetricMatrixFile();
    test_createBestTeamFile();
    test_refreshInformationFile();
    test_fulfillQuery();
    test_live();
}

# endif