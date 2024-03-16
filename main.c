# include <stdio.h>
# include <assert.h>
# include "libs\data_structures\vector\vector.h"
# include "libs\data_structures\void_vector\void_vector.h"
# include "libs\data_structures\matrix\matrix.h"

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
    size_t n;
    scanf("%zd", &n);

    vectorVoid v_float = createVectorV(0, sizeof(float));

    for (int i = 0; i < n; i++) {
        float x;
        scanf("%f", &x);
        pushBackV(&v_float, &x);
    }
    for (int i = 0; i < n; i++) {
        float x;
        getVectorValueV(&v_float, i, &x);
        printf("%f ", x);
    }

    vectorVoid v_int = createVectorV(0, sizeof(int));

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        pushBackV(&v_int, &x);
    }
    for (int i = 0; i < n; i++) {
        int x;
        getVectorValueV(&v_int, i, &x);
        printf("%d ", x);
    }


    return 0;
}

