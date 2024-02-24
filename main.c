# include <stdio.h>
# include <assert.h>
# include "E:\C23Exe\libs\data_structures\bitset\bitset.h"
# include "E:\C23Exe\libs\data_structures\unordered_set\unordered_set.h"
# include "E:\C23Exe\libs\data_structures\ordered_set\ordered_set.h"
# include "E:\C23Exe\libs\data_structures\vector\vector.h"

void test_bitset_union1(){
    bitset set1 = bitset_create_from_array((int[]){1, 2}, 2, 3);
    bitset set2 = bitset_create_from_array((int[]){2, 3}, 2, 3);
    bitset resSet = bitset_union(set1, set2);
    bitset expectSet = bitset_create_from_array((int[]){1, 2, 3}, 3, 3);
    assert(bitset_isEqual(resSet, expectSet));
}

void test_bitset_union2(){
    bitset set1 = bitset_create_from_array((int[]){1, 2, 3}, 3, 3);
    bitset set2 = bitset_create_from_array((int[]){}, 0, 3);
    bitset resSet = bitset_union(set1, set2);
    bitset expectSet = bitset_create_from_array((int[]){1, 2, 3}, 3, 3);
    assert(bitset_isEqual(resSet, expectSet));
}

void test_bitset_union(){
    test_bitset_union1();
    test_bitset_union2();
}

void test_bitset_intersection1(){
    bitset set1 = bitset_create_from_array((int[]){1, 2}, 2, 3);
    bitset set2 = bitset_create_from_array((int[]){2, 3}, 2, 3);
    bitset resSet = bitset_intersection(set1, set2);
    bitset expectSet = bitset_create_from_array((int[]){2}, 1, 3);
    assert(bitset_isEqual(resSet, expectSet));
}

void test_bitset_intersection2(){
    bitset set1 = bitset_create_from_array((int[]){1, 2, 3}, 3, 3);
    bitset set2 = bitset_create_from_array((int[]){}, 0, 3);
    bitset resSet = bitset_intersection(set1, set2);
    bitset expectSet = bitset_create_from_array((int[]){}, 0, 3);
    assert(bitset_isEqual(resSet, expectSet));
}

void test_bitset_intersection(){
    test_bitset_intersection1();
    test_bitset_intersection2();
}

void test_bitset_difference1(){
    bitset set1 = bitset_create_from_array((int[]){1, 2}, 2, 3);
    bitset set2 = bitset_create_from_array((int[]){2, 3}, 2, 3);
    bitset resSet = bitset_difference(set1, set2);
    bitset expectSet = bitset_create_from_array((int[]){1}, 1, 3);
    assert(bitset_isEqual(resSet, expectSet));
}

void test_bitset_difference2(){
    bitset set1 = bitset_create_from_array((int[]){1, 2, 3}, 3, 3);
    bitset set2 = bitset_create_from_array((int[]){}, 0, 3);
    bitset resSet = bitset_difference(set1, set2);
    bitset expectSet = bitset_create_from_array((int[]){1, 2, 3}, 3, 3);
    assert(bitset_isEqual(resSet, expectSet));
}

void test_bitset_difference(){
    test_bitset_difference1();
    test_bitset_difference2();
}

void test_bitset_symmetricDifference1(){
    bitset set1 = bitset_create_from_array((int[]){1, 2}, 2, 3);
    bitset set2 = bitset_create_from_array((int[]){2, 3}, 2, 3);
    bitset resSet = bitset_symmetricDifference(set1, set2);
    bitset expectSet = bitset_create_from_array((int[]){1, 3}, 2, 3);
    assert(bitset_isEqual(resSet, expectSet));
}

void test_bitset_symmetricDifference2(){
    bitset set1 = bitset_create_from_array((int[]){1, 2, 3}, 3, 3);
    bitset set2 = bitset_create_from_array((int[]){}, 0, 3);
    bitset resSet = bitset_symmetricDifference(set1, set2);
    bitset expectSet = bitset_create_from_array((int[]){1, 2, 3}, 3, 3);
    assert(bitset_isEqual(resSet, expectSet));
}

void test_bitset_symmetricDifference(){
    test_bitset_symmetricDifference1();
    test_bitset_symmetricDifference2();
}

void test_bitset_complement1(){
    bitset set1 = bitset_create_from_array((int[]){1, 3, 4}, 3, 5);
    bitset resSet = bitset_complement(set1);
    bitset expectSet = bitset_create_from_array((int[]){0, 2, 5}, 3, 5);
    assert(bitset_isEqual(resSet, expectSet));
}

void test_bitset_complement2(){
    bitset set1 = bitset_create_from_array((int[]){}, 0, 3);
    bitset resSet = bitset_complement(set1);
    bitset expectSet = bitset_create_from_array((int[]){0, 1, 2, 3}, 4, 3);
    assert(bitset_isEqual(resSet, expectSet));
}

void test_bitset_complement(){
    test_bitset_complement1();
    test_bitset_complement2();
}

void test_bitset_subset1(){
    bitset set1 = bitset_create_from_array((int[]){1, 2, 3}, 3, 3);
    bitset set2 = bitset_create_from_array((int[]){1, 3}, 2, 3);
    bool res = bitset_isSubset(set1, set2);
    bool expect = 1;
    assert(res == expect);
}

void test_bitset_subset2(){
    bitset set1 = bitset_create_from_array((int[]){1, 2, 3}, 3, 3);
    bitset set2 = bitset_create_from_array((int[]){1, 4}, 2, 4);
    bool res = bitset_isSubset(set1, set2);
    bool expect = 0;
    assert(res == expect);
}

void test_bitset_subset(){
    test_bitset_subset1();
    test_bitset_subset2();
}

void test_bitset_in1(){
    bitset set1 = bitset_create_from_array((int[]){1, 2, 3}, 3, 3);
    bool res = bitset_in(set1, 1);
    bool expect = 1;
    assert(res == expect);
}

void test_bitset_in2(){
    bitset set1 = bitset_create_from_array((int[]){1, 2, 3}, 3, 3);
    bool res = bitset_in(set1, 4);
    bool expect = 0;
    assert(res == expect);
}

void test_bitset_in(){
    test_bitset_in1();
    test_bitset_in2();
}

void test_bitset_insert(){
    bitset set1 = bitset_create_from_array((int[]){1, 3}, 2, 3);
    bitset_insert(&set1, 2);
    bitset expectSet = bitset_create_from_array((int[]){1, 2, 3}, 3, 3);
    assert(bitset_isEqual(set1, expectSet));
}

void test_bitset_deleteElement1(){
    bitset set1 = bitset_create_from_array((int[]){1, 2, 3}, 3, 3);
    bitset_deleteElement(&set1, 2);
    bitset expectSet = bitset_create_from_array((int[]){1,  3}, 2, 3);
    assert(bitset_isEqual(set1, expectSet));
}

void test_bitset_deleteElement2(){
    bitset set1 = bitset_create_from_array((int[]){1, 3}, 2, 3);
    bitset_deleteElement(&set1, 2);
    bitset expectSet = bitset_create_from_array((int[]){1, 3}, 2, 3);
    assert(bitset_isEqual(set1, expectSet));
}

void test_bitset_deleteElement(){
    test_bitset_deleteElement1();
    test_bitset_deleteElement2();
}

void test_bitset(){
    test_bitset_union();
    test_bitset_intersection();
    test_bitset_difference();
    test_bitset_symmetricDifference();
    test_bitset_complement();
    test_bitset_subset();
    test_bitset_in();
    test_bitset_insert();
    test_bitset_deleteElement();
}

void test_unordered_array_set_union1(){
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]){1, 2}, 2);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]){2, 3}, 2);
    unordered_array_set resSet = unordered_array_set_union(set1, set2);
    unordered_array_set expectSet = unordered_array_set_create_from_array((int[]){1, 2, 3}, 3);
    assert(unordered_array_set_isEqual(resSet, expectSet));

    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(resSet);
    unordered_array_set_delete(expectSet);
}

void test_unordered_array_set_union2(){
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]){1, 2}, 2);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]){}, 0);
    unordered_array_set resSet = unordered_array_set_union(set1, set2);
    unordered_array_set expectSet = unordered_array_set_create_from_array((int[]){1, 2}, 2);
    assert(unordered_array_set_isEqual(resSet, expectSet));

    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(resSet);
    unordered_array_set_delete(expectSet);
}

void test_unordered_array_set_union(){
    test_unordered_array_set_union1();
    test_unordered_array_set_union2();
}

void test_unordered_array_set_intersection1(){
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]){1, 2}, 2);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]){2, 3}, 2);
    unordered_array_set resSet = unordered_array_set_intersection(set1, set2);
    unordered_array_set expectSet = unordered_array_set_create_from_array((int[]){2}, 1);
    assert(unordered_array_set_isEqual(resSet, expectSet));

    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(resSet);
    unordered_array_set_delete(expectSet);
}

void test_unordered_array_set_intersection2(){
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]){1, 2}, 2);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]){}, 0);
    unordered_array_set resSet = unordered_array_set_intersection(set1, set2);
    unordered_array_set expectSet = unordered_array_set_create_from_array((int[]){}, 0);
    assert(unordered_array_set_isEqual(resSet, expectSet));

    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(resSet);
    unordered_array_set_delete(expectSet);
}

void test_unordered_array_set_intersection(){
    test_unordered_array_set_intersection1();
    test_unordered_array_set_intersection2();
}

void test_unordered_array_set_difference1(){
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]){1, 2}, 2);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]){2, 3}, 2);
    unordered_array_set resSet = unordered_array_set_difference(set1, set2);
    unordered_array_set expectSet = unordered_array_set_create_from_array((int[]){1}, 1);
    assert(unordered_array_set_isEqual(resSet, expectSet));

    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(resSet);
    unordered_array_set_delete(expectSet);
}

void test_unordered_array_set_difference2(){
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]){1, 2}, 2);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]){}, 0);
    unordered_array_set resSet = unordered_array_set_difference(set1, set2);
    unordered_array_set expectSet = unordered_array_set_create_from_array((int[]){1, 2}, 2);
    assert(unordered_array_set_isEqual(resSet, expectSet));

    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(resSet);
    unordered_array_set_delete(expectSet);
}

void test_unordered_array_set_difference(){
    test_unordered_array_set_difference1();
    test_unordered_array_set_difference2();
}

void test_unordered_array_set_symmetricDifference1(){
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]){1, 2}, 2);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]){2, 3}, 2);
    unordered_array_set resSet = unordered_array_set_symmetricDifference(set1, set2);
    unordered_array_set expectSet = unordered_array_set_create_from_array((int[]){1, 3}, 2);
    assert(unordered_array_set_isEqual(resSet, expectSet));

    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(resSet);
    unordered_array_set_delete(expectSet);
}

void test_unordered_array_set_symmetricDifference2(){
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]){1, 2}, 2);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]){1, 2}, 2);
    unordered_array_set resSet = unordered_array_set_symmetricDifference(set1, set2);
    unordered_array_set expectSet = unordered_array_set_create_from_array((int[]){}, 0);
    assert(unordered_array_set_isEqual(resSet, expectSet));

    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(resSet);
    unordered_array_set_delete(expectSet);
}

void test_unordered_array_set_symmetricDifference(){
    test_unordered_array_set_symmetricDifference1();
    test_unordered_array_set_symmetricDifference2();
}

void test_unordered_array_set_complement1(){
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]){1, 2}, 2);
    unordered_array_set U = unordered_array_set_create_from_array((int[]){1, 2, 3}, 3);
    unordered_array_set resSet = unordered_array_set_complement(set1, U);
    unordered_array_set expectSet = unordered_array_set_create_from_array((int[]){3}, 1);
    assert(unordered_array_set_isEqual(resSet, expectSet));

    unordered_array_set_delete(set1);
    unordered_array_set_delete(U);
    unordered_array_set_delete(resSet);
    unordered_array_set_delete(expectSet);
}

void test_unordered_array_set_complement2(){
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]){}, 0);
    unordered_array_set U = unordered_array_set_create_from_array((int[]){1, 2, 3}, 3);
    unordered_array_set resSet = unordered_array_set_complement(set1, U);
    unordered_array_set expectSet = unordered_array_set_create_from_array((int[]){1, 2, 3}, 3);
    assert(unordered_array_set_isEqual(resSet, expectSet));

    unordered_array_set_delete(set1);
    unordered_array_set_delete(U);
    unordered_array_set_delete(resSet);
    unordered_array_set_delete(expectSet);
}

void test_unordered_array_set_complement(){
    test_unordered_array_set_complement1();
    test_unordered_array_set_complement2();
}

void test_unordered_array_set_subset1(){
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]){1, 2, 3}, 3);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]){1, 2, 3}, 3);
    bool res = unordered_array_set_isSubset(set1, set2);
    bool expect = 1;
    assert(res == expect);

    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
}

void test_unordered_array_set_subset2(){
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]){1, 2, 3}, 3);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]){}, 0);
    bool res = unordered_array_set_isSubset(set1, set2);
    bool expect = 0;
    assert(res == expect);

    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
}

void test_unordered_array_set_subset(){
    test_unordered_array_set_subset1();
    test_unordered_array_set_subset2();
}

void test_unordered_array_set_in1(){
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]){1, 2, 3}, 3);
    size_t res = unordered_array_set_in(set1, 2);
    size_t expect = 1;
    assert(res == expect);

    unordered_array_set_delete(set1);
}

void test_unordered_array_set_in2(){
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]){1, 2, 3}, 3);
    size_t res = unordered_array_set_in(set1, 4);
    size_t expect = 3;
    assert(res == expect);

    unordered_array_set_delete(set1);
}

void test_unordered_array_set_in(){
    test_unordered_array_set_in1();
    test_unordered_array_set_in2();
}

void test_unordered_array_set_insert(){
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]){1}, 2);
    printf("%d", set1.size);
    printf("%d", set1.capacity);
    unordered_array_set_insert(&set1, 2);
    printf("%d", set1.size);
    printf("%d", set1.capacity);
    unordered_array_set expectSet = unordered_array_set_create_from_array((int[]){1, 2}, 2);
    assert(unordered_array_set_isEqual(set1, expectSet));

    unordered_array_set_delete(set1);
    unordered_array_set_delete(expectSet);
}

void test_unordered_array_set_deleteElement(){
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]){1}, 1);
    unordered_array_set_deleteElement(&set1, 1);
    unordered_array_set expectSet = unordered_array_set_create_from_array((int[]){}, 0);
    assert(unordered_array_set_isEqual(set1, expectSet));

    unordered_array_set_delete(set1);
    unordered_array_set_delete(expectSet);
}

void test_unordered_array_set(){
    test_unordered_array_set_union();
    test_unordered_array_set_intersection();
    test_unordered_array_set_difference();
    test_unordered_array_set_symmetricDifference();
    test_unordered_array_set_complement();
    test_unordered_array_set_subset();
    test_unordered_array_set_in();
    test_unordered_array_set_insert();
    test_unordered_array_set_deleteElement();
}

void test_ordered_array_set_union1(){
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]){1, 2}, 2);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]){2, 3}, 2);
    ordered_array_set resSet = ordered_array_set_union(set1, set2);
    ordered_array_set expectSet = ordered_array_set_create_from_array((int[]){1, 2, 3}, 3);
    assert(ordered_array_set_isEqual(resSet, expectSet));

    ordered_array_set_delete(set1);
    ordered_array_set_delete(set2);
    ordered_array_set_delete(resSet);
    ordered_array_set_delete(expectSet);
}

void test_ordered_array_set_union2(){
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]){1, 2}, 2);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]){}, 0);
    ordered_array_set resSet = ordered_array_set_union(set1, set2);
    ordered_array_set expectSet = ordered_array_set_create_from_array((int[]){1, 2}, 2);
    assert(ordered_array_set_isEqual(resSet, expectSet));

    ordered_array_set_delete(set1);
    ordered_array_set_delete(set2);
    ordered_array_set_delete(resSet);
    ordered_array_set_delete(expectSet);
}

void test_ordered_array_set_union(){
    test_ordered_array_set_union1();
    test_ordered_array_set_union2();
}

void test_ordered_array_set_intersection1(){
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]){1, 2}, 2);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]){2, 3}, 2);
    ordered_array_set resSet = ordered_array_set_intersection(set1, set2);
    ordered_array_set expectSet = ordered_array_set_create_from_array((int[]){2}, 1);
    assert(ordered_array_set_isEqual(resSet, expectSet));

    ordered_array_set_delete(set1);
    ordered_array_set_delete(set2);
    ordered_array_set_delete(resSet);
    ordered_array_set_delete(expectSet);
}

void test_ordered_array_set_intersection2(){
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]){1, 2}, 2);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]){}, 0);
    ordered_array_set resSet = ordered_array_set_intersection(set1, set2);
    ordered_array_set expectSet = ordered_array_set_create_from_array((int[]){}, 0);
    assert(ordered_array_set_isEqual(resSet, expectSet));

    ordered_array_set_delete(set1);
    ordered_array_set_delete(set2);
    ordered_array_set_delete(resSet);
    ordered_array_set_delete(expectSet);
}

void test_ordered_array_set_intersection(){
    test_ordered_array_set_intersection1();
    test_ordered_array_set_intersection2();
}

void test_ordered_array_set_difference1(){
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]){1, 2}, 2);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]){2, 3}, 2);
    ordered_array_set resSet = ordered_array_set_difference(set1, set2);
    ordered_array_set expectSet = ordered_array_set_create_from_array((int[]){1}, 1);
    assert(ordered_array_set_isEqual(resSet, expectSet));

    ordered_array_set_delete(set1);
    ordered_array_set_delete(set2);
    ordered_array_set_delete(resSet);
    ordered_array_set_delete(expectSet);
}

void test_ordered_array_set_difference2(){
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]){1, 2}, 2);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]){}, 0);
    ordered_array_set resSet = ordered_array_set_difference(set1, set2);
    ordered_array_set expectSet = ordered_array_set_create_from_array((int[]){1, 2}, 2);
    assert(ordered_array_set_isEqual(resSet, expectSet));

    ordered_array_set_delete(set1);
    ordered_array_set_delete(set2);
    ordered_array_set_delete(resSet);
    ordered_array_set_delete(expectSet);
}

void test_ordered_array_set_difference(){
    test_ordered_array_set_difference1();
    test_ordered_array_set_difference2();
}

void test_ordered_array_set_symmetricDifference1(){
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]){1, 2}, 2);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]){2, 3}, 2);
    ordered_array_set resSet = ordered_array_set_symmetricDifference(set1, set2);
    ordered_array_set expectSet = ordered_array_set_create_from_array((int[]){1, 3}, 2);
    assert(ordered_array_set_isEqual(resSet, expectSet));

    ordered_array_set_delete(set1);
    ordered_array_set_delete(set2);
    ordered_array_set_delete(resSet);
    ordered_array_set_delete(expectSet);
}

void test_ordered_array_set_symmetricDifference2(){
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]){1, 2}, 2);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]){1, 2}, 2);
    ordered_array_set resSet = ordered_array_set_symmetricDifference(set1, set2);
    ordered_array_set expectSet = ordered_array_set_create_from_array((int[]){}, 0);
    assert(ordered_array_set_isEqual(resSet, expectSet));

    ordered_array_set_delete(set1);
    ordered_array_set_delete(set2);
    ordered_array_set_delete(resSet);
    ordered_array_set_delete(expectSet);
}

void test_ordered_array_set_symmetricDifference(){
    test_ordered_array_set_symmetricDifference1();
    test_ordered_array_set_symmetricDifference2();
}

void test_ordered_array_set_complement1(){
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]){1, 2}, 2);
    ordered_array_set U = ordered_array_set_create_from_array((int[]){1, 2, 3}, 3);
    ordered_array_set resSet = ordered_array_set_complement(set1, U);
    ordered_array_set expectSet = ordered_array_set_create_from_array((int[]){3}, 1);
    assert(ordered_array_set_isEqual(resSet, expectSet));

    ordered_array_set_delete(set1);
    ordered_array_set_delete(U);
    ordered_array_set_delete(resSet);
    ordered_array_set_delete(expectSet);
}

void test_ordered_array_set_complement2(){
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]){}, 0);
    ordered_array_set U = ordered_array_set_create_from_array((int[]){1, 2, 3}, 3);
    ordered_array_set resSet = ordered_array_set_complement(set1, U);
    ordered_array_set expectSet = ordered_array_set_create_from_array((int[]){1, 2, 3}, 3);
    assert(ordered_array_set_isEqual(resSet, expectSet));

    ordered_array_set_delete(set1);
    ordered_array_set_delete(U);
    ordered_array_set_delete(resSet);
    ordered_array_set_delete(expectSet);
}

void test_ordered_array_set_complement(){
    test_ordered_array_set_complement1();
    test_ordered_array_set_complement2();
}

void test_ordered_array_set_subset1(){
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]){1, 2, 3}, 3);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]){1, 2, 3}, 3);
    bool res = ordered_array_set_isSubset(set1, set2);
    bool expect = 1;
    assert(res == expect);

    ordered_array_set_delete(set1);
    ordered_array_set_delete(set2);
}

void test_ordered_array_set_subset2(){
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]){1, 2, 3}, 3);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]){}, 0);
    bool res = ordered_array_set_isSubset(set1, set2);
    bool expect = 0;
    assert(res == expect);

    ordered_array_set_delete(set1);
    ordered_array_set_delete(set2);
}

void test_ordered_array_set_subset(){
    test_ordered_array_set_subset1();
    test_ordered_array_set_subset2();
}

void test_ordered_array_set_in1(){
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]){1, 2, 3}, 3);
    bool res = ordered_array_set_in(&set1, 2);
    bool expect = 1;
    assert(res == expect);

    ordered_array_set_delete(set1);
}

void test_ordered_array_set_in2(){
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]){1, 2, 3}, 3);
    bool res = ordered_array_set_in(&set1, 4);
    bool expect = 3;
    assert(res == expect);

    ordered_array_set_delete(set1);
}

void test_ordered_array_set_in(){
    test_ordered_array_set_in1();
    test_ordered_array_set_in2();
}

void test_ordered_array_set_insert(){
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]){1}, 2);
    ordered_array_set_insert(&set1, 2);
    ordered_array_set expectSet = ordered_array_set_create_from_array((int[]){1, 2}, 2);
    assert(ordered_array_set_isEqual(set1, expectSet));

    ordered_array_set_delete(set1);
    ordered_array_set_delete(expectSet);
}

void test_ordered_array_set_deleteElement(){
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]){1}, 1);
    ordered_array_set_deleteElement(&set1, 1);
    ordered_array_set expectSet = ordered_array_set_create_from_array((int[]){}, 0);
    assert(ordered_array_set_isEqual(set1, expectSet));

    ordered_array_set_delete(set1);
    ordered_array_set_delete(expectSet);
}

void test_ordered_array_set(){
    test_ordered_array_set_union();
    test_ordered_array_set_intersection();
    test_ordered_array_set_difference();
    test_ordered_array_set_symmetricDifference();
    test_ordered_array_set_complement();
    test_ordered_array_set_subset();
    test_ordered_array_set_in();
    test_ordered_array_set_insert();
    test_ordered_array_set_deleteElement();
}

void test(){
    test_bitset();
    test_unordered_array_set();
    test_ordered_array_set();
}

int main() {
    test();

    return 0;
}