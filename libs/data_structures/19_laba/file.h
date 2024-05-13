# ifndef FILE_H
# define FILE_H

# include "E:\C23Exe\libs\data_structures\matrix\matrix.h"
# include "E:\C23Exe\libs\data_structures\vector\vector.h"
# include "E:\C23Exe\libs\data_structures\void_vector\void_vector.h"
# include <memory.h>
# include <math.h>
# include "E:\C23Exe\libs\data_structures\string\string_.h"
# define MAX_LENGTH_STRING 200
# define MAX_AMOUNT_SPORTSMAN 20

//транспонирует квадратную матрицу в файле
void squareMatrixFileTransponse(const char* filename);

//переводит число с фиксированной точкой в число с плавающей точкой.
void fixedPointIntoFloatPointFile(const char* filename);

//решает арифметическое выражение из файла
void solveTextExpressionFile(const char* filename);

//сохраняет только те слова, которые содержат данную последовательность символов
void saveOnlySpecialWordsFile(const char* filename, char* letters_sequence);

//оставляет только самое длинное слово в файле
void onlyLongestWordFile(const char* filename);

typedef struct monomial {
    int degree;
    double coefficient;
} monomial;

//Удаляет многочлен, чей x является корнем
void deletePolynomialFile(const char *filename, double x);

//Перемещает положительные числа в начало, а отрицательные - в конец
void positiveNegativeOrderFile(const char* filename);

//транспонирует матрицу в файле, если она не симметрична
void transposeNonSymmetricMatrixFile(const char *filename);

typedef struct sportsman {
    char name[MAX_LENGTH_STRING];
    int max_result;
} sportsman;

//Отбирает лучших спортсменов в команду
void createBestTeamFile(const char *filename, const int n);

typedef struct warehouse {
    char name_of_product[MAX_LENGTH_STRING];
    int price;
    int total_cost;
    int quantity;
} warehouse;

typedef struct order {
    char order_name[MAX_LENGTH_STRING];
    int quantity;
} order;

//Обновляет информацию в файле f об оставшихся продуктах на складе, исходя из информации о заказах в файле q
void refreshInformationFile(const char* f_filename, const char* q_filename);

//проводит автоматизированное тестирование функций
void testFile();

# endif