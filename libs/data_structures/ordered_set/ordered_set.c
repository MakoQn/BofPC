# ifndef INC_ORDERED_ARRAY_SET_H
# define INC_ORDERED_ARRAY_SET_H

# include <stdint.h>
# include <assert.h>
# include <memory.h>
# include <malloc.h>
# include <stdio.h>
# include <stdbool.h>
# include "E:\C23Exe\libs\algorithms\array\array.h"
# include "ordered_set.h"

typedef struct ordered_array_set {
    int *data; // элементы множества
    size_t size; // количество элементов в множестве
    size_t capacity; // максимальное количество элементов в множестве
} ordered_array_set;

// возвращает пустое множество, в которое можно вставить capacity элементов
ordered_array_set ordered_array_set_create(size_t capacity){
    return (ordered_array_set) {
            (int *)malloc(sizeof(int) * capacity),
            0,
            capacity
    };
};

// сжимает макс вместимость множества до количества элементов
// в данном множестве
static void ordered_array_set_shrink_to_fit(ordered_array_set *a){
    if (a->size != a->capacity) {
        a->data = (int*)realloc(a->data, sizeof(int)*a->size);
        a->capacity = a->size;
    }
}

// возвращает множество, состоящее из элементов массива a размера size
ordered_array_set ordered_array_set_create_from_array(const int *a, size_t size){
    ordered_array_set set = ordered_array_set_create(size);

    for (size_t i = 0; i < size; i++)
        append_(set.data, &set.size, a[i]);

    return set;
};

// возвращает значение позицию элемента в множестве,
// если значение value имеется в множестве set,
// иначе - n
size_t ordered_array_set_in(ordered_array_set *set, int value){
    return binarySearch_(set->data, set->size, value);
};

// возвращает значение ’истина’, если элементы множеств set1 и set2 равны
// иначе - ’ложь’
bool ordered_array_set_isEqual(ordered_array_set set1, ordered_array_set set2){
    return (set1.size == set2.size) && ((memcmp(set1.data, set2.data, sizeof (int) * set1.size)) == 0);
};

// возвращает значение ’истина’, если subset является подмножеством set
// иначе - ’ложь’
bool ordered_array_set_isSubset(ordered_array_set subset, ordered_array_set set){
    if (subset.size > set.size)
        return 0;

    for (size_t i = 0; i < subset.size; i++)
        if (binarySearch_(set.data, set.size, subset.data[i]) == set.size)
            return 0;

    return 1;
};

// возбуждает исключение, если в множество по адресу set
// нельзя вставить элемент
void ordered_array_set_isAbleAppend(ordered_array_set *set){
    assert(set->size < set->capacity);
};

// добавляет элемент value в множество set
void ordered_array_set_insert(ordered_array_set *set, int value){
    if (ordered_array_set_in(set, value) == set->size) {
        ordered_array_set_isAbleAppend(set);
        insert_(set->data, &set->size, linearSearch_(set->data, set->size, value), value);
    }
};

// удаляет элемент value из множества set
void ordered_array_set_deleteElement(ordered_array_set *set, int value){
    deleteByPosSaveOrder_(set->data, &set->size, ordered_array_set_in(set, value));
};

// возвращает объединение множеств set1 и set2
ordered_array_set ordered_array_set_union(ordered_array_set set1, ordered_array_set set2){
    ordered_array_set union_set = ordered_array_set_create(set1.size + set2.size);

    for (size_t i = 0; i < set1.size; i++)
        append_(union_set.data, &union_set.size, set1.data[i]);

    for (size_t i = 0; i < set2.size; i++)
        ordered_array_set_insert(&union_set, set2.data[i]);

    ordered_array_set_shrink_to_fit(&union_set);

    return union_set;
};

// возвращает пересечение множеств set1 и set2
ordered_array_set ordered_array_set_intersection(ordered_array_set set1, ordered_array_set set2){
    ordered_array_set intersection_set = ordered_array_set_create(set1.size < set2.size ? set1.size : set2.size);

    for (size_t i = 0; i < set1.size; i++)
        if (ordered_array_set_in(&set2, set1.data[i]) != set2.size)
            append_(intersection_set.data, &intersection_set.size, set1.data[i]);

    ordered_array_set_shrink_to_fit(&intersection_set);

    return intersection_set;
};

// возвращает разность множеств set1 и set2
ordered_array_set ordered_array_set_difference(ordered_array_set set1, ordered_array_set set2){
    ordered_array_set difference_set = ordered_array_set_create(set1.size);

    for (size_t i = 0; i < set1.size; i++)
        if (ordered_array_set_in(&set2, set1.data[i]) == set2.size)
            append_(difference_set.data, &difference_set.size, set1.data[i]);

    ordered_array_set_shrink_to_fit(&difference_set);

    return difference_set;
};

// освобождает память, занимаемую множеством set
void ordered_array_set_delete(ordered_array_set set){
    free(set.data);
};

// возвращает симметрическую разность множеств set1 и set2
ordered_array_set ordered_array_set_symmetricDifference(ordered_array_set set1, ordered_array_set set2){
    ordered_array_set diff_Set1_Set2 = ordered_array_set_difference(set1, set2);
    ordered_array_set diff_Set2_Set1 = ordered_array_set_difference(set2, set1);

    ordered_array_set symmetricDifference_set = ordered_array_set_union(diff_Set1_Set2, diff_Set2_Set1);

    ordered_array_set_delete(diff_Set1_Set2);
    ordered_array_set_delete(diff_Set2_Set1);

    ordered_array_set_shrink_to_fit(&symmetricDifference_set);

    return symmetricDifference_set;
};

// возвращает дополнение до универсума universumSet множества set
ordered_array_set ordered_array_set_complement(ordered_array_set set, ordered_array_set universumSet){
    assert(ordered_array_set_isSubset(set, universumSet));

    ordered_array_set complement_set = ordered_array_set_difference(universumSet, set);

    ordered_array_set_shrink_to_fit(&complement_set);

    return complement_set;
};

// вывод множества set
void ordered_array_set_print(ordered_array_set set){
    for (size_t i = 0; i < set.size; i++)
        printf("%d", set.data[i]);
};

# endif