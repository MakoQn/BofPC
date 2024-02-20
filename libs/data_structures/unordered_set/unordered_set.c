# ifndef INC_UNORDERED_ARRAY_SET_H
# define INC_UNORDERED_ARRAY_SET_H

# include <stdlib.h>
# include <stdint.h>
# include <assert.h>
# include <memory.h>
# include <malloc.h>
# include <stdio.h>
# include <stdbool.h>
# include "E:\C23Exe\libs\algorithms\array\array.h"
# include "unordered_set.h"

typedef struct unordered_array_set {
    int * data ; // элементы множества
    size_t size ; // количество элементов в множестве
    size_t capacity ; // максимальное количество элементов в множестве
} unordered_array_set ;

// сжимает макс вместимость множества до количества элементов
// в данном множестве
static void unordered_array_set_shrink_to_fit(unordered_array_set *a){
    if (a->size != a->capacity) {
        a->data = (int*)realloc(a->data, sizeof(int)*a->size);
        a->capacity = a->size;
    }
}

// возвращает пустое множество для capacity элементов
unordered_array_set unordered_array_set_create(size_t capacity){
    return (unordered_array_set) {
            (int *)malloc(sizeof(int) * capacity),
            0,
            capacity
    };
};

// возвращает позицию элемента в множестве,
// если значение value имеется в множестве set, иначе - n
size_t unordered_array_set_in(unordered_array_set *set, int value){
    return linearSearch_(set->data, set->size, value);
};

// возбуждает исключение, если в множество по адресу set
// нельзя вставить элемент
void unordered_array_set_isAbleAppend(unordered_array_set *set){
    assert(set->size < set->capacity);
};

// добавляет элемент value в множество set
void unordered_array_set_insert(unordered_array_set *set, int value){
    if (unordered_array_set_in(set, value) == set->size) {
        unordered_array_set_isAbleAppend(set);
        append_(set->data, &set->size, value);
    }
};

// возвращает множество, состоящее из элементов массива a размера size.
unordered_array_set unordered_array_set_create_from_array(const int *a, size_t size){
    unordered_array_set set = unordered_array_set_create(size);

    for (size_t i = 0; i < size; i++)
        append_(set.data, &set.size, a[i]);

    return set;
};

//Возвращает истина, если subset включен в set, иначе ложь.
bool unordered_array_set_isSubset(unordered_array_set subset, unordered_array_set set){
    if (set.size < subset.size)
        return 0;

    for (size_t i = 0; i < subset.size; i++)
        if (unordered_array_set_in(&set, subset.data[i]) == set.size)
            return 0;

    return 1;
};

int compare( const void *arg1, const void *arg2 ){
    return *(int *)arg1 - *(int *)arg2;
};

// возвращает значение ’истина’, если элементы множеств set1 и set2 равны
// иначе - ’ложь’
bool unordered_array_set_isEqual(unordered_array_set set1, unordered_array_set set2){
    qsort(set1.data, set1.size, sizeof (int), compare);
    qsort(set2.data, set2.size, sizeof (int), compare);

    return (set1.size == set2.size) && ((memcmp(set1.data, set2.data, sizeof (int) * set1.size)) == 0);
};

// удаляет элемент value из множества set
void unordered_array_set_deleteElement(unordered_array_set *set, int value){
    deleteByPosUnsaveOrder_(set->data, &set->size, unordered_array_set_in(set, value));
};

// возвращает объединение множеств set1 и set2.
unordered_array_set unordered_array_set_union(unordered_array_set set1, unordered_array_set set2){
    unordered_array_set union_set = unordered_array_set_create(set1.size + set2.size);

    for (size_t i = 0; i < set1.size; i++)
        append_(union_set.data, &union_set.size, set1.data[i]);

    for (size_t i = 0; i < set2.size; i++)
        unordered_array_set_insert(&union_set, set2.data[i]);

    unordered_array_set_shrink_to_fit(&union_set);

    return union_set;
};

// возвращает пересечение множеств set1 и set2
unordered_array_set unordered_array_set_intersection(unordered_array_set set1, unordered_array_set set2){
    unordered_array_set intersection_set = unordered_array_set_create(set1.size < set2.size ? set1.size : set2.size);

    for (size_t i = 0; i < set1.size; i++)
        if (unordered_array_set_in(&set2, set1.data[i]) != set2.size)
            append_(intersection_set.data, &intersection_set.size, set1.data[i]);

    unordered_array_set_shrink_to_fit(&intersection_set);

    return intersection_set;
};

// возвращает разность множеств set1 и set2
unordered_array_set unordered_array_set_difference(unordered_array_set set1, unordered_array_set set2){
    unordered_array_set difference_set = unordered_array_set_create(set1.size);

    for (size_t i = 0; i < set1.size; i++)
        if (unordered_array_set_in(&set2, set1.data[i]) == set2.size)
            append_(difference_set.data, &difference_set.size, set1.data[i]);

    unordered_array_set_shrink_to_fit(&difference_set);

    return difference_set;
};

// возвращает дополнение до универсума множества set2
unordered_array_set unordered_array_set_complement(unordered_array_set set, unordered_array_set universumSet){
    assert(unordered_array_set_isSubset(set, universumSet));

    unordered_array_set complement_set = unordered_array_set_difference(universumSet, set);

    unordered_array_set_shrink_to_fit(&complement_set);

    return complement_set;
};

// освобождает память, занимаемую множеством set
void unordered_array_set_delete(unordered_array_set set){
    free(set.data);
};

// возвращает симметрическую разность множеств set1 и set2
unordered_array_set unordered_array_set_symmetricDifference(unordered_array_set set1, unordered_array_set set2){
    unordered_array_set diff_Set1_Set2 = unordered_array_set_difference(set1, set2);
    unordered_array_set diff_Set2_Set1 = unordered_array_set_difference(set2, set1);

    unordered_array_set symmetricDifference_set = unordered_array_set_union(diff_Set1_Set2, diff_Set2_Set1);

    unordered_array_set_delete(diff_Set1_Set2);
    unordered_array_set_delete(diff_Set2_Set1);

    unordered_array_set_shrink_to_fit(&symmetricDifference_set);

    return symmetricDifference_set;
};

// вывод множества set
void unordered_array_set_print(unordered_array_set set){
    for (size_t i = 0; i < set.size; i++)
        printf("%d", set.data[i]);
};

# endif