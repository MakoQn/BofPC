# ifndef FILE_H
# define FILE_H

# include "E:\C23Exe\libs\data_structures\matrix\matrix.h"
# include "E:\C23Exe\libs\data_structures\vector\vector.h"
# include "E:\C23Exe\libs\data_structures\void_vector\void_vector.h"
# include <memory.h>
# include <math.h>
# include "E:\C23Exe\string\string_.h"

//транспонирует квадратную матрицу в файле
void squareMatrixFileTransponse(const char* filename);

//переводит число с фиксированной точкой в число с плавающей точкой.
void fixedPointIntoFloatPointFile(const char* filename);

//проводит автоматизированное тестирование функций
void testFile();

# endif