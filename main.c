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

void test(){
    test_pushBack_emptyVector();
    test_pushBack_fullVector();
}

int main() {

    return 0;
}