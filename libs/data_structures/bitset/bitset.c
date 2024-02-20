# ifndef INC_BITSET_H
# define INC_BITSET_H

# include <stdint.h>
# include <stdbool.h>
# include <assert.h>
# include <stdio.h>
# include "bitset.h"

typedef struct bitset {
    uint32_t values ; // множество
    uint32_t maxValue; // максимальный элемент универсума
} bitset;

// возвращает пустое множество c универсумом 0, 1,..., maxValue
bitset bitset_create (unsigned maxValue){
    assert(maxValue < 32);

    bitset set;

    set.maxValue = maxValue;
    set.values = 0;

    return set;
};

// возвращает значение ’истина’, если значение value имеется в множестве set
// иначе - ’ложь’
bool bitset_in (bitset set ,unsigned int value){
    return (set.values >> value) & 1;
};

// возвращает значение ’истина’, если множества set1 и set2 равны
// иначе - ’ложь’
bool bitset_isEqual ( bitset set1 , bitset set2 ){
    return set1.values == set2.values;
};

// возвращает значение ’истина’ если множество subset
// является подмножеством множества set, иначе - ’ложь’.
bool bitset_isSubset ( bitset subset , bitset set ){
    return (subset.values & set.values) == set.values;
};

// добавляет элемент value в множество set
void bitset_insert ( bitset * set , unsigned int value ){
    (*set).values |= (1 << value);
};

// возвращает множество, состоящее из элементов массива a размера size.
bitset bitset_create_from_array (int *a, size_t size, unsigned maxValue){
    bitset set = bitset_create(maxValue);

    for (size_t i = 0; i < size; i++)
        bitset_insert(&set, a[i]);

    return set;
};

// удаляет элемент value из множества set
void bitset_deleteElement ( bitset * set , unsigned int value ){
    (*set).values &= (~(1 << value));
};

// возвращает объединение множеств set1 и set2
bitset bitset_union ( bitset set1 , bitset set2 ){
    assert(set1.maxValue == set2.maxValue);

    bitset union_set;

    union_set.values = set1.values | set2.values;

    return union_set;
};

// возвращает пересечение множеств set1 и set2
bitset bitset_intersection ( bitset set1 , bitset set2 ){
    assert(set1.maxValue == set2.maxValue);

    bitset intersection_set;

    intersection_set.values = set1.values & set2.values;

    return intersection_set;
};

// возвращает разность множеств set1 и set2
bitset bitset_difference ( bitset set1 , bitset set2 ){
    assert(set1.maxValue == set2.maxValue);

    bitset difference_set;

    difference_set.values = set1.values & (~set2.values);

    return difference_set;
};

// возвращает симметрическую разность множеств set1 и set2
bitset bitset_symmetricDifference ( bitset set1 , bitset set2 ){
    assert(set1.maxValue == set2.maxValue);

    bitset symmetricDifference_set;

    symmetricDifference_set.values = set1.values ^ set2.values;

    return symmetricDifference_set;
};

// возвращает дополнение до универсума множества set
bitset bitset_complement ( bitset set ){
    bitset complement_set = bitset_create(set.maxValue);

    uint32_t n = (31 - set.maxValue);

    complement_set.values = (((~set.values) << n) >> n);

    return complement_set;
};

// вывод множества set
void bitset_print ( bitset set ){
    for (int i = set.maxValue; i >= 0;i--){
        printf("%d", (set.values >> i) & 1);
    }
};

# endif