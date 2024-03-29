#ifndef INC_VOID_VECTOR_H
#define INC_VOID_VECTOR_H

#include <limits.h>
# include <stdint.h>
# include <malloc.h>
# include <stdio.h>
# include <string.h>
#include "void_vector.h"

typedef struct vectorVoid {
    void *data; // указатель на нулевой элемент вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
    size_t baseTypeSize; // размер базового типа:
                        // например, если вектор хранит int -
                        // то поле baseTypeSize = sizeof(int)
                        // если вектор хранит float -
                        // то поле baseTypeSize = sizeof(float)
} vectorVoid;

//возвращает пустой вектор вместимостью n и размером базового типа baseTypeSize
vectorVoid createVectorV(size_t n, size_t baseTypeSize){
    if (n == 0)
        return (vectorVoid) {
                NULL,
                0,
                n,
                baseTypeSize
        };
    else{
        vectorVoid *a = malloc(sizeof(baseTypeSize) * n);

        if (a == NULL){
            free(a);

            fprintf(stderr, "bad alloc");
            exit(1);
        }else{
            free(a);

            return (vectorVoid) {
                    malloc(sizeof(baseTypeSize) * n),
                    0,
                    n,
                    baseTypeSize
            };
        }
    }
}

//изменяет количество памяти выделенное
//под хранение элементов вектора
void reserveV(vectorVoid *v, size_t newCapacity){
    if (newCapacity == v->capacity)
        return;

    if (newCapacity == 0){
        v->data = NULL;
        v->size = 0;
        v->capacity = 0;
        v->baseTypeSize = 0;

        free(v->data);

        return;
    }else if (newCapacity < v->capacity){
        v->size = newCapacity;
        v->capacity = newCapacity;
    }else{
        vectorVoid *a = malloc(sizeof(v->baseTypeSize) * (newCapacity - v->capacity));

        if (a == NULL){
            free(a);

            fprintf(stderr, "bad alloc");
            exit(1);
        }else {
            free(a);

            v->capacity = newCapacity;
        }
    }

    v->data = realloc(v->data, sizeof(v->baseTypeSize) * newCapacity);
}

//освобождает память, выделенную под
//неиспользуемые элементы
void shrinkToFitV(vectorVoid *v){
    reserveV(v, v->size);
}

//удаляет элементы из контейнера
//но не освобождает выделенную память
void clearV(vectorVoid *v){
    *v = createVectorV(v->capacity, v->baseTypeSize);
}

//освобождает память, выделенную вектору
void deleteVectorV(vectorVoid *v){
    reserveV(v, 0);
}

//проверка на то, является ли вектор пустым
bool isEmptyV(vectorVoid *v){
    return v->size == 0;
}

//проверка на то, является ли вектор полным
bool isFullV(vectorVoid *v){
    return v->size == v->capacity;
}

//записывает по адресу destination index-ый элемент вектора v
void getVectorValueV(vectorVoid *v, size_t index, void *destination){
    char *source = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}

//записывает на index-ый элемент вектора v значение, расположенное по
//адресу source
void setVectorValueV(vectorVoid *v, size_t index, void *source){
    char *destination = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}

//удаляет последний элемент из вектора
void popBackV(vectorVoid *v){
    if (v->size == 0) {
        fprintf(stderr, "vector is empty");
        exit(1);
    }else
        v->size--;
}

//добавляет значение, записанное по адресу source, в конец вектора v
void pushBackV(vectorVoid *v, void *source){
    if (v->capacity == 0){
        reserveV(v, 1);
        setVectorValueV(v, v->size, source);
        v->size++;
    }else if (v->size == v->capacity){
        reserveV(v, v->capacity * 2);
        setVectorValueV(v, v->size, source);
        v->size++;
    }else{
        setVectorValueV(v, v->size, source);
        v->size++;
    }
}

# endif