# ifndef STRING_H
# define STRING_H

# include <assert.h>

//нахождение длины строки
int findLength(const char *str) {
    int length = 0;

    while (*str) {
        length++;
        str++;
    }

    return length;
}

void test_findLength_zeroLength(){
    char s[] = "";

    assert(findLength(s) == 0);
}

void test_findLength_notZeroLength(){
    char s[] = "Hello";

    assert(findLength(s) == 5);
}

void test_findLength(){
    test_findLength_zeroLength();
    test_findLength_notZeroLength();
}

//тестирует функции, написанные выше
void test(){
    test_findLength();
}

# endif