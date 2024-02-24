# ifndef INC_VECTOR_H
# define INC_VECTOR_H

# include <stdio.h>
# include <malloc.h>
# include <stdint.h>
# include "vector.h"

typedef struct vector {
    int *data; // указатель на элементы вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
} vector;

// возвращает пустой вектор вместимости capacity
vector createVector(size_t capacity){
    if (capacity == 0)
        return (vector) {
                0,
                capacity
        };
    else{
        int *a = (int*)malloc(sizeof(int) * capacity);

        if (a == NULL){
            free(a);

            fprintf(stderr, "bad alloc");
            exit(1);
        }else{
            free(a);

            return (vector) {
                    (int *)malloc(sizeof(int) * capacity),
                    0,
                    capacity
            };
        }
    }
};

//изменяет количество памяти выделенное
//под хранение элементов вектора
void reserve(vector *v, size_t newCapacity){
    if (newCapacity == 0){
        v->data = NULL;
        v->size = 0;
        v->capacity = 0;

        return;
    }else if (newCapacity > v->capacity){
        int *a = (int*)malloc(sizeof(int) * (newCapacity - v->capacity));

        if (a == NULL){
            free(a);

            fprintf(stderr, "bad alloc");
            exit(1);
        }else
            free(a);
    }

    v->data = realloc(v->data, newCapacity);
}

# endif