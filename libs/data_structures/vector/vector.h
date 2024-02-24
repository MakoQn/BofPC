# ifndef INC_VECTOR_H
# define INC_VECTOR_H

# include <stdio.h>
# include <malloc.h>
# include <stdint.h>

typedef struct vector {
    int *data; // указатель на элементы вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
} vector;

vector createVector(size_t capacity);

# endif