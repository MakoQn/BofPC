# ifndef STRING_H
# define STRING_H

# include <assert.h>
# include <ctype.h>
# include <stdio.h>

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

//количество символов в строке
size_t strlen_(const char *begin) {
    char *end = begin;
    while (*end != '\0')
        end++;
    return end - begin;
}

void test_strlen__zeroLength(){
    char s[] = "";

    assert(strlen_(s) == 0);
}

void test_strlen__noSymbols(){
    char s[5] = "";

    assert(strlen_(s) == 0);
}

void test_strlen__notNoSymbols(){
    char s[10] = "Hello";

    assert(strlen_(s) == 5);
}

void test_strlen_(){
    test_strlen__zeroLength();
    test_strlen__noSymbols();
    test_strlen__notNoSymbols();
}

//возвращает указатель на первый элемент с кодом ch, расположенным на ленте памяти между
//адресами begin и end не включая end. Если символ не найден, возвращается значение end.
char* find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch)
        begin++;

    return begin;
}

//возвращает указатель на первый
//символ, отличный от пробельных, расположенный на ленте памяти, начиная с begin и заканчивая ноль-символом.
// Если символ не найден, возвращается адрес первого ноль-символа
char* findNonSpace(char *begin){
    while (*begin != '\0' && isspace(*begin))
        begin++;

    return begin;
}

void test_findNonSpace_noSymbols(){
    char s[] = "   ";

    assert(*findNonSpace(s) == '\0');
}

void test_findNonSpace_noSpaces(){
    char s[] = "Hello";

    assert(*findNonSpace(s) == 'H');
}

void test_findNonSpace_spacesAndSymbols(){
    char s[] = " Hel lo";

    assert(*findNonSpace(s) == 'H');
}

void test_findNonSpace(){
    test_findNonSpace_noSymbols();
    test_findNonSpace_noSpaces();
    test_findNonSpace_spacesAndSymbols();
}

char* findSpace(char *begin){
    while (*begin != '\0' && !isspace(*begin))
        begin++;

    return begin;
}

void test_findSpace_noSymbols(){
    char s[] = "  ";

    assert(findSpace(s) == &s[0]);
}

void test_findSpace_noSpaces(){
    char s[] = "Hello";

    assert(*findSpace(s) == '\0');
}

void test_findSpace_spacesAndSymbols(){
    char s[] = "Hel lo";

    assert(findSpace(s) == &s[3]);
}

void test_findSpace(){
    test_findSpace_noSymbols();
    test_findSpace_noSpaces();
    test_findSpace_spacesAndSymbols();
}

//возвращает указатель на первый справа символ, отличный от пробельных,
//расположенный на ленте памяти, начиная с rbegin (последний символ
//строки, за которым следует ноль-символ) и заканчивая rend (адрес символа перед началом строки). Если символ не найден, возвращается адрес rend.
char* findNonSpaceReverse(char *rbegin, const char *rend){
    while(rbegin > rend && isspace(*rbegin))
        rbegin--;

    return rbegin;
}

void test_findNonSpaceReverse_noSymbols(){
    char s[] = "  ";

    assert(*findNonSpaceReverse(&s[1], &s[0]) == s[0]);
}

void test_findNonSpaceReverse_noSpaces(){
    char s[] = "Hello";

    assert(*findNonSpaceReverse(&s[4], &s[0]) == 'o');
}

void test_findNonSpaceReverse_spacesAndSymbols(){
    char s[] = "Hel lo ";

    assert(*findNonSpaceReverse(&s[5], &s[0]) == 'o');
}

void test_findNonSpaceReverse(){
    test_findNonSpaceReverse_noSymbols();
    test_findNonSpaceReverse_noSpaces();
    test_findNonSpaceReverse_spacesAndSymbols();
}

//возвращает указатель на первый пробельный символ справа, расположенный на ленте памяти, начиная с rbegin и заканчивая rend. Если символ не найден,
//возвращается адрес rend.
char* findSpaceReverse(char *rbegin, const char *rend){
    while(rbegin > rend && !isspace(*rbegin))
        rbegin--;

    return rbegin;
}

void test_findSpaceReverse_noSymbols(){
    char s[] = "  ";

    assert(*findSpaceReverse(&s[1], &s[0]) == s[1]);
}

void test_findSpaceReverse_noSpaces(){
    char s[] = "Hello";

    assert(*findSpaceReverse(&s[4], &s[0]) == s[0]);
}

void test_findSpaceReverse_spacesAndSymbols(){
    char s[] = " Hel lo";

    assert(*findSpaceReverse(&s[6], &s[0]) == s[4]);
}

void test_findSpaceReverse(){
    test_findSpaceReverse_noSymbols();
    test_findSpaceReverse_noSpaces();
    test_findSpaceReverse_spacesAndSymbols();
}

//сравнение строк, если строки раны - возвращает 0, или если lhs распологается до rhs - отрицательное значение, иначе положительное значение
int strcmp(const char *lhs, const char *rhs){
    int diff = 0;

    while (*lhs++ && *rhs++ && diff == 0)
        diff += *lhs - *rhs;

    return diff;
}

void test_strcmp_noSymbolsEqual(){
    char s1[] = "  ";
    char s2[] = "  ";

    assert(strcmp(s1, s2) == 0);
}

void test_strcmp_noSpacesEqual(){
    char s1[] = "Hello";
    char s2[] = "Hello";

    assert(strcmp(s1, s2) == 0);
}

void test_strcmp_spacesAndSymbols(){
    char s1[] = "Hello";
    char s2[] = " Hel lo";

    assert(strcmp(s1, s2) != 0);
}

void test_strcmp(){
    test_strcmp_noSymbolsEqual();
    test_strcmp_noSpacesEqual();
    test_strcmp_spacesAndSymbols();
}

//тестирует функции, написанные выше
void test(){
    test_findLength();
    test_strlen_();
    test_findNonSpace();
    test_findSpace();
    test_findNonSpaceReverse();
    test_findSpaceReverse();
    test_strcmp();
}

# endif