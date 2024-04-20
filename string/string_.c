# ifndef STRING_H
# define STRING_H

#define ASSERT_STRING(expected, got) assertString(expected, got, \
__FILE__, __FUNCTION__, __LINE__)


# include <assert.h>
# include <ctype.h>
# include <memory.h>
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

void test_find_T(){
    char s[] = "123456";

    assert(*find(&s[0], &s[4], (int)'3') == s[2]);
}

void test_find_F(){
    char s[] = "123456";

    assert(*find(&s[0], &s[3], (int)'7') != s[2]);
}

void test_find(){
    test_find_T();
    test_find_F();
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
int strcmp_(const char *lhs, const char *rhs){
    int diff = 0;

    while (*lhs++ && *rhs++ && diff == 0)
        diff += *lhs - *rhs;

    return diff;
}

void test_strcmp_noSymbolsEqual(){
    char s1[] = "  ";
    char s2[] = "  ";

    assert(strcmp_(s1, s2) == 0);
}

void test_strcmp_noSpacesEqual(){
    char s1[] = "Hello";
    char s2[] = "Hello";

    assert(strcmp_(s1, s2) == 0);
}

void test_strcmp_spacesAndSymbols(){
    char s1[] = "Hello";
    char s2[] = " Hel lo";

    assert(strcmp_(s1, s2) != 0);
}

void test_strcmp_moreMemThanNeeded(){
    char s1[10] = "Hello";
    char s2[15] = " Hel lo";

    assert(strcmp_(s1, s2) != 0);
}

void test_strcmp_positive(){
    char s1[] = "bb";
    char s2[] = "aa";

    assert(strcmp_(s1, s2) > 0);
}

void test_strcmp_negative(){
    char s1[] = "aa";
    char s2[] = "bb";

    assert(strcmp_(s1, s2) < 0);
}

void test_strcmp(){
    test_strcmp_noSymbolsEqual();
    test_strcmp_noSpacesEqual();
    test_strcmp_spacesAndSymbols();
    test_strcmp_moreMemThanNeeded();
    test_strcmp_positive();
    test_strcmp_negative();
}

//записывает по адресу beginDestination фрагмент памяти, начиная с адреса beginSource до endSource.
//Возвращает указатель на следующий свободный фрагмент памяти в destination
char* copy(const char *beginSource, const char *endSource, char *beginDestination){
    int size = endSource - beginSource;

    memcpy(beginDestination, beginSource, size);

    return beginDestination + size;
}

void test_copy_wholeWord(){
    char s[] = "Hello";
    char s_dist[10];

    assert(copy(&s[0], &s[5], s_dist) == &s_dist[5]);
}

void test_copy_halfWord(){
    char s[] = "Hello";
    char s_dist[10];

    assert(copy(&s[0], &s[3], s_dist) == &s_dist[3]);
}

void test_copy_notEmptyDist(){
    char s[] = "Hello";
    char s_dist[11] = "Hello";
    char s_cmp[11] = "HelloHello";

    copy(&s[0], &s[5], &s_dist[5]);

    assert(strcmp_(s_dist, s_cmp) == 0);
}

void test_copy_notEmptyDistReplaceHalfWord(){
    char s[] = "Hello";
    char s_dist[11] = "Hello";
    char s_cmp[11] = "HelHello";

    copy(&s[0], &s[5], &s_dist[3]);

    assert(strcmp_(s_dist, s_cmp) == 0);
}

void test_copy(){
    test_copy_wholeWord();
    test_copy_halfWord();
    test_copy_notEmptyDist();
    test_copy_notEmptyDistReplaceHalfWord();
}

//записывает по адресу beginDestination элементы из фрагмента памяти начиная с beginSource заканчивая endSource, удовлетворяющие функции-предикату f.
//Функция возвращает указатель на следующий свободный для записи фрагмент в памяти
char* copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int)){
    while (*beginSource++ < *endSource)
        if (f(*beginSource))
            memcpy(beginDestination, beginSource, sizeof *beginSource);

    return beginDestination;
}

void test_copyIf_ifDigit(){
    char s[] = "5He6l7lo8";
    char s_dist[10];
    char s_cmp[10] = "5678";

    copyIf(&s[0], &s[9], s_dist, isdigit);

    assert(strcmp_(s_dist, s_cmp) == 0);
}

void test_copyIf(){
    test_copyIf_ifDigit();
}

//записывает по адресу beginDestination элементы из фрагмента памяти начиная с rbeginSource заканчивая rendSource,
//удовлетворяющие функции-предикату f. Функция возвращает значение beginDestination по окончанию работы функции.
char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int)){
    while (*rbeginSource-- > *rendSource)
        if (f(*rbeginSource))
            memcpy(beginDestination, rbeginSource, sizeof *rbeginSource);

    return beginDestination;
}

void test_copyIfReverse_ifDigit(){
    char s[] = "5He6l7lo8";
    char s_dist[10];
    char s_cmp[10] = "8765";

    copyIfReverse(&s[0], &s[9], s_dist, isdigit);

    assert(strcmp_(s_dist, s_cmp) == 0);
}

void test_copyIfReverse(){
    test_copyIfReverse_ifDigit();
}

char* getEndOfString(char *s){
    return &s[strlen_(s)];
}

void removeNonLetters(char *s) {
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName,
                  int line) {
    if (strcmp_(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}

void test_getEndOfString_zeroLength(){
    char s[] = "";

    ASSERT_STRING(&s[0], getEndOfString(s));
}

void test_getEndOfString_notZeroLength(){
    char s[] = "123";

    ASSERT_STRING(&s[3], getEndOfString(s));
}

void test_getEndOfString(){
    test_getEndOfString_zeroLength();
    test_getEndOfString_notZeroLength();
}

void test_removeNonLetters_zeroLetters(){
    char s[] = "";
    char s_test[] = "";

    removeNonLetters(s);

    ASSERT_STRING(s_test, s);
}

void test_removeNonLetters_noSpaces(){
    char s[] = "123";
    char s_test[] = "123";

    removeNonLetters(s);

    ASSERT_STRING(s_test, s);
}

void test_removeNonLetters_spacesAndLetters(){
    char s[] = "1 2 3";
    char s_test[] = "123\0 2 3";

    removeNonLetters(s);

    ASSERT_STRING(s_test, s);
}

void test_removeNonLetters(){
    test_removeNonLetters_zeroLetters();
    test_removeNonLetters_noSpaces();
    test_removeNonLetters_spacesAndLetters();
}

//тестирует функции, написанные выше
void test(){
    test_findLength();
    test_strlen_();
    test_find();
    test_findNonSpace();
    test_findSpace();
    test_findNonSpaceReverse();
    test_findSpaceReverse();
    test_strcmp();
    test_copy();
    test_copyIf();
    test_copyIfReverse();
    test_getEndOfString();
    test_removeNonLetters();
}

# endif