# ifndef FILE_H
# define FILE_H

# include "E:\C23Exe\libs\data_structures\matrix\matrix.h"
# include <memory.h>

//транспонирует квадратную матрицу в файле
void squareMatrixFileTransponse(const char* filename);

//переводит число с фиксированной точкой в число с плавающей точкой.
void fixedPointIntoFloatPointFile(const char* filename);

//проводит автоматизированное тестирование функций
void testFile();

# endif