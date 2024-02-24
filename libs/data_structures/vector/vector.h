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

// возвращает пустой вектор вместимости capacity
vector createVector(size_t capacity);

//изменяет количество памяти выделенное
//под хранение элементов вектора
void reserve(vector *v, size_t newCapacity);

//удаляет элементы из контейнера
//но не освобождает выделенную память
void clear(vector *v);

//освобождает память, выделенную под
//неиспользуемые элементы
void shrinkToFit(vector *v);

//освобождает память, выделенную вектору
void deleteVector(vector *v);

# endif