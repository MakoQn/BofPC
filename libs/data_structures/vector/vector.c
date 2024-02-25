# ifndef INC_VECTOR_H
# define INC_VECTOR_H

# include <stdio.h>
# include <malloc.h>
# include <stdint.h>
# include <stdbool.h>
# include "vector.h"

typedef struct vector {
    int *data; // указатель на элементы вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
} vector;

//возвращает пустой вектор вместимости capacity
vector createVector(size_t capacity){
    if (capacity == 0)
        return (vector) {
                NULL,
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
    if (newCapacity == v->capacity)
        return;

    if (newCapacity == 0){
        v->data = NULL;
        v->size = 0;
        v->capacity = 0;

        free(v->data);

        return;
    }else if (newCapacity < v->capacity){
        v->size = newCapacity;
        v->capacity = newCapacity;
    }else{
        int *a = (int*)malloc(sizeof(int) * (newCapacity - v->capacity));

        if (a == NULL){
            free(a);

            fprintf(stderr, "bad alloc");
            exit(1);
        }else {
            free(a);

            v->capacity = newCapacity;
        }
    }

    v->data = (int*)realloc(v->data, newCapacity);
}


//удаляет элементы из контейнера
//но не освобождает выделенную память
void clear(vector *v){
    *v = createVector(v->capacity);
}

//освобождает память, выделенную под
//неиспользуемые элементы.
void shrinkToFit(vector *v){
    reserve(v, v->size);
}

//освобождает память, выделенную вектору
void deleteVector(vector *v){
    reserve(v, 0);
}

//проверка на то, является ли вектор пустым
bool isEmpty(vector *v){
    return v->size == 0;
}

//проверка на то, является ли вектор полным
bool isFull(vector *v){
    return v->size == v->capacity;
}

//возвращает i-ый элемент вектора v
int getVectorValue(vector *v, size_t i){
    return v->data[i];
}

//добавляет элемент x в конец вектора v
void pushBack(vector *v, int x){
    if (v->capacity == 0){
        reserve(v, 1);
        v->data[v->size] = x;
        v->size++;
    }else if (v->size == v->capacity){
        reserve(v, v->capacity * 2);
        v->data[v->size] = x;
        v->size++;
    }else{
        v->data[v->size] = x;
        v->size++;
    }
}

//удаляет последний элемент из вектора
void popBack(vector *v){
    if (v->size == 0) {
        fprintf(stderr, "vector is empty");
        exit(1);
    }else
        v->size--;
}

//возвращает указатель на index-ый элемент вектора
int* atVector(vector *v, size_t index){
    if (v->size == 0){
        fprintf(stderr, "vector is empty");
        exit(1);
    }else if (index > v->size){
        fprintf(stderr, "%s %d %s", "IndexError: a[", index, "] is not exists");
        exit(1);
    }else
        return &v->data[index];
}

//возвращает указатель на последний элемент вектора
int* back(vector *v){
    if (v->size == 0) {
        fprintf(stderr, "vector is empty");
        exit(1);
    }else
        return &v->data[--v->size];
}

//возвращает указатель на нулевой элемент вектора
int* front(vector *v){
    if (v->size == 0) {
        fprintf(stderr, "vector is empty");
        exit(1);
    }else
        return &v->data[0];
}

# endif