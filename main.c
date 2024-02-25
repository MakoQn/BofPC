# include <stdio.h>
# include <assert.h>
# include "E:\C23Exe\libs\data_structures\bitset\bitset.h"
# include "E:\C23Exe\libs\data_structures\unordered_set\unordered_set.h"
# include "E:\C23Exe\libs\data_structures\ordered_set\ordered_set.h"
# include "E:\C23Exe\libs\data_structures\vector\vector.h"

void test_pushBack_emptyVector(){
    vector v = createVector(0);

    pushBack(&v, 5);
    assert(getVectorValue(&v, 0) == 5);
}

void test_pushBack_fullVector(){
    vector v = createVector(2);

    pushBack(&v, 1);
    pushBack(&v, 2);
    pushBack(&v, 3);

    assert(getVectorValue(&v, 2) == 3);
}

void test_popBack_notEmptyVector(){
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(v.size == 1);
    popBack(&v);
    assert(v.size == 0);
    assert(v.capacity == 1);
}

void test_atVector_notEmptyVector(){
    vector v = createVector(2);
    pushBack(&v, 1);
    pushBack(&v, 2);
    int *e = atVector(&v, 0);
    assert(*e == 1);
}

void test_atVector_requestToLastElement(){
    vector v = createVector(2);
    pushBack(&v, 1);
    pushBack(&v, 2);
    int *e = atVector(&v, 1);
    assert(*e == 2);
}

void test_back_oneElementInVector(){
    vector v = createVector(1);
    pushBack(&v, 1);
    int *e = back(&v);
    assert(*e == 1);
}

void test_front_oneElementInVector(){
    vector v = createVector(1);
    pushBack(&v, 1);
    int *e = front(&v);
    assert(*e == 1);
}

void test(){
    test_pushBack_emptyVector();
    test_pushBack_fullVector();
    test_popBack_notEmptyVector();
    test_atVector_notEmptyVector();
    test_atVector_requestToLastElement();
    test_back_oneElementInVector();
    test_front_oneElementInVector();
}

int main() {
    test();

    return 0;
}