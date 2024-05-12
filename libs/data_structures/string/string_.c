# ifndef STRING_H
# define STRING_H

#define ASSERT_STRING(expected, got) assertString(expected, got, \
__FILE__, __FUNCTION__, __LINE__)
#define MAX_STRING_SIZE 100
#define MAX_N_WORDS_IN_STRING 100
#define MAX_WORD_SIZE 20
#define CHARACTERS 97

# include <assert.h>
# include <ctype.h>
# include <memory.h>
# include <stdio.h>
# include "string_.h"
#include <stdlib.h>

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

//возвращает указатель на первый пробельный
//символ, расположенный на ленте памяти, начиная с begin и заканчивая ноль-символом.
// Если символ не найден, возвращается адрес первого ноль-символа
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
    while (beginSource != endSource) {
        if (f(*beginSource)) {
            *beginDestination = *beginSource;

            beginDestination++;
        }

        beginSource++;
    }

    *beginDestination = '\0';

    return beginDestination;
}

void test_copyIf_ifDigit(){
    char s[] = "5He6l7lo8";
    char s_dist[10];
    char s_cmp[10] = "5678";

    copyIf(s, s + 9, s_dist, isdigit);

    assert(strcmp_(s_dist, s_cmp) == 0);
}

void test_copyIf(){
    test_copyIf_ifDigit();
}

//записывает по адресу beginDestination элементы из фрагмента памяти начиная с rbeginSource заканчивая rendSource,
//удовлетворяющие функции-предикату f. Функция возвращает значение beginDestination по окончанию работы функции.
char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int)){
    while (rbeginSource != rendSource) {
        if (f(*(rbeginSource - 1))) {
            *beginDestination = *(rbeginSource - 1);

            beginDestination++;
        }

        rbeginSource--;
    }
    beginDestination[*(rbeginSource - 1)] = '\0';

    return beginDestination;
}

void test_copyIfReverse_ifDigit(){
    char s[] = "5He6l7lo8";
    char s_dist[10];
    char s_cmp[10] = "8765";

    copyIfReverse(&s[9], &s[0], s_dist, isdigit);

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
    char s[] = "abc";
    char s_test[] = "abc";

    removeNonLetters(s);

    ASSERT_STRING(s_test, s);
}

void test_removeNonLetters_spacesAndLetters(){
    char s[] = "a b c";
    char s_test[] = "abc";

    removeNonLetters(s);

    ASSERT_STRING(s_test, s);
}

void test_removeNonLetters(){
    test_removeNonLetters_zeroLetters();
    test_removeNonLetters_noSpaces();
    test_removeNonLetters_spacesAndLetters();
}

void* removeExtraSpaces(char *s){
    char *read = s;
    char *write = s;

    while(*read){
        if(isspace(*read)){
            if(write > s)
                *write++ = *read;

            while (*read && isspace(*read))
                read++;

            if(!*read)
                break;
        }

        *write++ = *read;
        read++;
    }

    while (write > s && isspace(*(write - 1)))
        write--;

    *write = '\0';
}

void test_removeExtraSpaces_zeroLetters(){
    char s[] = "";
    char s_test[] = "";

    removeExtraSpaces(s);

    ASSERT_STRING(s_test, s);
}

void test_removeExtraSpaces_noSpaces(){
    char s[] = "123";
    char s_test[] = "123";

    removeExtraSpaces(s);

    ASSERT_STRING(s_test, s);
}

void test_removeExtraSpaces_normalSpaces(){
    char s[] = "1 2 3";
    char s_test[] = "1 2 3";

    removeExtraSpaces(s);

    ASSERT_STRING(s_test, s);
}

void test_removeExtraSpaces_extraSpaces(){
    char s[] = "  1  2   3  ";
    char s_test[] = "1 2 3";

    removeExtraSpaces(s);

    ASSERT_STRING(s_test, s);
}

void test_removeExtraSpaces(){
    test_removeExtraSpaces_zeroLetters();
    test_removeExtraSpaces_noSpaces();
    test_removeExtraSpaces_normalSpaces();
    test_removeExtraSpaces_extraSpaces();
}

//хранит позиции начала и конца слова
typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа
} WordDescriptor;

//считывание слова с начала строки
int getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);

    if (*word->begin == '\0')
        return 0;

    word->end = findSpace(word->begin);

    return 1;
}

//считывание слова с конца строки
bool getWordReverse(char *rbegin, char *rend, WordDescriptor *word){
    word->end = findNonSpaceReverse(rbegin, rend);

    if (word->end == rend)
        return 0;

    word->begin = findSpaceReverse(word->end, rend) + 1;

    return 1;
}

char _stringBuffer[MAX_STRING_SIZE + 1];

void digitToStart(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end,_stringBuffer);
    char *recPosition = copyIfReverse(endStringBuffer,_stringBuffer,word.begin, isdigit);

    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}

void digitToStartWholeString(char *beginString) {
    char *beginSearch = beginString;
    WordDescriptor word;

    while (getWord(beginSearch, &word)) {
        digitToStart(word);

        beginSearch = word.end;
    }
}

void test_digitToStartWholeString_zeroLetters(){
    char s[] = "";
    char s_test[] = "";

    digitToStartWholeString(s);

    ASSERT_STRING(s_test, s);
}

void test_digitToStartWholeString_onlyDigits(){
    char s[] = "123";
    char s_test[] = "321";

    digitToStartWholeString(s);

    ASSERT_STRING(s_test, s);
}

void test_digitToStartWholeString_charactersAndDigits(){
    char s[] = "1AB32";
    char s_test[] = "231AB";

    digitToStartWholeString(s);

    ASSERT_STRING(s_test, s);
}

void test_digitToStartWholeString(){
    test_digitToStartWholeString_zeroLetters();
    test_digitToStartWholeString_onlyDigits();
    test_digitToStartWholeString_charactersAndDigits();
}

void digitToStartNotReverse(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end,_stringBuffer);
    char *recPosition = copyIf(_stringBuffer,endStringBuffer,word.begin, isdigit);

    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}

void digitToStartNotReverseWholeString(char *beginString) {
    char *beginSearch = beginString;
    WordDescriptor word;

    while (getWord(beginSearch, &word)) {
        digitToStartNotReverse(word);

        beginSearch = word.end;
    }
}

void test_digitToStartNotReverseWholeString_zeroLetters(){
    char s[] = "";
    char s_test[] = "";

    digitToStartNotReverseWholeString(s);

    ASSERT_STRING(s_test, s);
}

void test_digitToStartNotReverseWholeString_onlyDigits(){
    char s[] = "123";
    char s_test[] = "123";

    digitToStartNotReverseWholeString(s);

    ASSERT_STRING(s_test, s);
}

void test_digitToStartNotReverseWholeString_charactersAndDigits(){
    char s[] = "1AB32";
    char s_test[] = "132AB";

    digitToStartNotReverseWholeString(s);

    ASSERT_STRING(s_test, s);
}

void test_digitToStartNotReverseWholeString(){
    test_digitToStartNotReverseWholeString_zeroLetters();
    test_digitToStartNotReverseWholeString_onlyDigits();
    test_digitToStartNotReverseWholeString_charactersAndDigits();
}

void replaceDigitsBySpaces(char *s) {
    WordDescriptor word;

    if (!getWord(s, &word))
        return;

    char *endStringBuffer = copy(word.begin, word.end, _stringBuffer);
    char *buf = _stringBuffer;

    *endStringBuffer = '\0';

    while (*buf != '\0') {
        if (isdigit(*buf))
            for (int i = 0; i < *buf - '0'; i++)
                *s++ = ' ';
        else
            *s++ = *buf;

        buf++;
    }

    *s = '\0';
}

void test_replaceDigitsBySpaces_zeroLetters(){
    char s[MAX_STRING_SIZE] = "";
    char s_test[] = "";

    replaceDigitsBySpaces(s);

    ASSERT_STRING(s_test, s);
}

void test_replaceDigitsBySpaces_onlyDigits(){
    char s[MAX_STRING_SIZE] = "223";
    char s_test[] = "       ";

    replaceDigitsBySpaces(s);

    ASSERT_STRING(s_test, s);
}

void test_replaceDigitsBySpaces_charactersAndDigits(){
    char s[MAX_STRING_SIZE] = "2AB35";
    char s_test[] = "  AB        ";

    replaceDigitsBySpaces(s);

    ASSERT_STRING(s_test, s);
}

void test_replaceDigitsBySpaces(){
    test_replaceDigitsBySpaces_zeroLetters();
    test_replaceDigitsBySpaces_onlyDigits();
    test_replaceDigitsBySpaces_charactersAndDigits();
}

void replace(char *source, char *w1, char *w2) {
    size_t w1Size = strlen_(w1);
    size_t w2Size = strlen_(w2);
    WordDescriptor word1 = {w1, w1 + w1Size};
    WordDescriptor word2 = {w2, w2 + w2Size};
    char *readPtr, *recPtr;

    if (w1Size >= w2Size) {
        readPtr = source;
        recPtr = source;
    } else {
        copy(source, getEndOfString(source), _stringBuffer);
        readPtr = _stringBuffer;
        recPtr = source;
    }

    WordDescriptor word = {readPtr, readPtr + w1Size};

    while (*readPtr != '\0') {
        if (*readPtr == *word1.begin) {
            if (strcmp_(word1.begin,word.begin) >= 0) {
                copy(word2.begin,word2.end,recPtr);
                readPtr+=w1Size;
                recPtr+=w2Size;
            }else
                *recPtr++=*readPtr++;
        }else
            *recPtr++=*readPtr++;
    }

    *recPtr='\0';
}

void test_replace_zeroWords(){
    char s[] = "";
    char s_test[] = "";

    replace(s, "my", "our");

    ASSERT_STRING(s_test, s);
}

void test_replace_notReplaced(){
    char s[] = "Its our place";
    char s_test[] = "Its our place";

    replace(s, "my", "our");

    ASSERT_STRING(s_test, s);
}

void test_replace_replaced(){
    char s[] = "Its our place";
    char s_test[] = "Its my place";

    replace(s, "our", "my");

    ASSERT_STRING(s_test, s);
}

void test_replace(){
    test_replace_zeroWords();
    test_replace_notReplaced();
    test_replace_replaced();
}

int areWordsEqual(WordDescriptor w1, WordDescriptor w2){
    return strcmp_(w1.begin, w2.begin);
};

bool wordsAreOrdered(char *s){
    char *beginSearch = s;
    WordDescriptor current;

    if (!getWord(beginSearch, &current))
        return 1;

    WordDescriptor previous = current;

    while (getWord(beginSearch, &current)){
        if (areWordsEqual(current, previous) < 0)
            return 0;

        beginSearch = current.end;
        previous = current;
    }

    return 1;
}

void test_wordsAreOrdered_zeroWords(){
    char s[] = "";

    assert(wordsAreOrdered(s));
}

void test_wordsAreOrdered_unordered(){
    char s[] = "cd ab";

    assert(!wordsAreOrdered(s));
}

void test_wordsAreOrdered_ordered(){
    char s[] = "ab cd";

    assert(wordsAreOrdered(s));
}

void test_wordsAreOrdered(){
    test_wordsAreOrdered_zeroWords();
    test_wordsAreOrdered_unordered();
    test_wordsAreOrdered_ordered();
}

//структура, которая хранит начало
//и конец каждого слова исходной строки
typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;

BagOfWords _bag;
BagOfWords _bag2;

void getBagOfWords(BagOfWords *bag, char *s){
    char *beginSearch = s;
    WordDescriptor word;

    bag->size = 0;
    while (getWord(beginSearch, &word)){
        bag->words[bag->size++] = word;
        beginSearch = word.end;
    }
}

void printReverse(char *s){
    getBagOfWords(&_bag, s);
    for (int i = _bag.size - 1; i >= 0; i--){
        char *endStringBuffer = copy(_bag.words[i].begin, _bag.words[i].end, _stringBuffer);
        *endStringBuffer = '\0';
        printf("%s\n", _stringBuffer);
    }
}

void test_printReverse_zeroWords(){
    char s[] = "";

    printReverse(s);
}

void test_printReverse_notEmpty(){
    char s[] = "A BC  D";

    printReverse(s);
}

void test_printReverse(){
    test_printReverse_zeroWords();
    test_printReverse_notEmpty();
}

bool isPalindrome(char *begin, char *end) {
    end--;

    while (end - begin > 0)
        if (*begin++ != *end--)
            return 0;

    return 1;
}

char* findNonPunct(char *begin){
    while (*begin != '\0' && (isspace(*begin) || ispunct(*begin)))
        begin++;

    return begin;
}

char* findPunct(char *begin){
    while (*begin != '\0' && !ispunct(*begin))
        begin++;

    return begin;
}

int getWordPunct(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonPunct(beginSearch);

    if (*word->begin == '\0')
        return 0;

    word->end = findPunct(word->begin);

    return 1;
}

int countPalindromes(char *s){
    char *beginSearch = s;
    WordDescriptor word;
    int count_of_palindromes = 0;

    while (getWordPunct(beginSearch, &word)) {
        count_of_palindromes += isPalindrome(word.begin, word.end);

        beginSearch = word.end;
    }

    return count_of_palindromes;
}

void test_countPalindromes_zeroWords(){
    char s[] = "";

    assert(!countPalindromes(s));
}

void test_countPalindromes_zeroPalindromes(){
    char s[] = "cdv,abc";

    assert(!countPalindromes(s));
}

void test_countPalindromes_onePalindrome(){
    char s[] = "cdc,abc";

    assert(countPalindromes(s) == 1);
}

void test_countPalindromes(){
    test_countPalindromes_zeroWords();
    test_countPalindromes_zeroPalindromes();
    test_countPalindromes_onePalindrome();
}

void alternateWords(char *s, char *s1, char *s2) {
    char *beginString = s;
    bool isW1Found = true, isW2Found;
    char *beginSearch1 = s1, *beginSearch2 = s2;
    WordDescriptor word1, word2;

    while (isW1Found || isW2Found) {
        isW1Found = getWord(beginSearch1, &word1);
        isW2Found = getWord(beginSearch2, &word2);

        if (isW1Found) {
            beginString = copy(word1.begin, word1.end, beginString);
            *beginString++ = ' ';
            beginSearch1 = word1.end;
        }
        if (isW2Found) {
            beginString = copy(word2.begin, word2.end, beginString);
            *beginString++ = ' ';
            beginSearch2 = word2.end;
        }
    }
    *(beginString - 1) = '\0';
}

void test_alternateWords_zeroWords(){
    char s[30] = "";
    char s1[] = "";
    char s2[] = "";
    char s_test[] = "";

    alternateWords(s, s1, s2);

    ASSERT_STRING(s_test, s);
}

void test_alternateWords_w1AndW2AreEqualCount(){
    char s[30] = "";
    char s1[] = "A A A";
    char s2[] = "B B B";
    char s_test[] = "A B A B A B";

    alternateWords(s, s1, s2);

    ASSERT_STRING(s_test, s);
}

void test_alternateWords_w1AndW2ArentEqualCount(){
    char s[30] = "";
    char s1[] = "A A A";
    char s2[] = "B B";
    char s_test[] = "A B A B A";

    alternateWords(s, s1, s2);

    ASSERT_STRING(s_test, s);
}

void test_alternateWords(){
    test_alternateWords_zeroWords();
    test_alternateWords_w1AndW2AreEqualCount();
    test_alternateWords_w1AndW2ArentEqualCount();
}

void reverse(char* begin, char* end){
    char temp;

    while (begin < end) {
        temp = *begin;
        *begin++ = *end;
        *end-- = temp;
    }
}

void writeWordsInReverseOrder(char *s) {
    char *word_begin = NULL;
    char *beginString = s;

    while (*beginString) {
        if ((word_begin == NULL) && (*beginString != ' ')) {
            word_begin = beginString;
        }

        if (word_begin && ((*beginString + 1 == ' ') || (*beginString + 1 == '\0'))) {
            reverse(word_begin, beginString);
            word_begin = NULL;
        }
        beginString++;
    }

    reverse(s, beginString - 1);
}

void test_writeWordsInReverseOrder_zeroWords(){
    char s[] = "";
    char s_test[] = "";

    writeWordsInReverseOrder(s);

    ASSERT_STRING(s_test, s);
}

void test_writeWordsInReverseOrder_oneWord(){
    char s[] = "A";
    char s_test[] = "A";

    writeWordsInReverseOrder(s);

    ASSERT_STRING(s_test, s);
}

void test_writeWordsInReverseOrder_moreThanOneWord(){
    char s[] = "A B C D";
    char s_test[] = "D C B A";

    writeWordsInReverseOrder(s);

    ASSERT_STRING(s_test, s);
}

void test_writeWordsInReverseOrder(){
    test_writeWordsInReverseOrder_zeroWords();
    test_writeWordsInReverseOrder_oneWord();
    test_writeWordsInReverseOrder_moreThanOneWord();
}

typedef enum WordBeforeFirstWordWithAReturnCode {
    FIRST_WORD_WITH_A,
    NOT_FOUND_A_WORD_WITH_A,
    WORD_FOUND,
    EMPTY_STRING
} WordBeforeFirstWordWithAReturnCode;

bool isLettersInWord(WordDescriptor word, char character) {
    char *beginString = word.begin;

    while (beginString != word.end) {
        if (*beginString == character)
            return 1;

        beginString++;
    }

    return 0;
}

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char* s, WordDescriptor *word) {
    char *begin_search = s;
    WordDescriptor word1;

    if (!getWord(begin_search, &word1)) {
        return EMPTY_STRING;
    }

    begin_search = word1.end + 1;

    if (isLettersInWord(word1, 'A') || isLettersInWord(word1, 'a')) {
        return FIRST_WORD_WITH_A;
    }

    WordDescriptor word2;

    while (getWord(begin_search, &word2)) {
        if (isLettersInWord(word2, 'A') || isLettersInWord(word2, 'a')) {
            *word = word1;

            return WORD_FOUND;
        }

        word1 = word2;
        begin_search = word2.end + 1;
    }

    return NOT_FOUND_A_WORD_WITH_A;
}

void test_getWordBeforeFirstWordWithA(){
    WordDescriptor word;
    char s1[] = "";
    assert(getWordBeforeFirstWordWithA(s1, &word) == EMPTY_STRING);

    char s2[] = "ABC";
    assert(getWordBeforeFirstWordWithA(s2, &word) == FIRST_WORD_WITH_A);

    char s3[] = "BC A";
    assert(getWordBeforeFirstWordWithA(s3, &word) == WORD_FOUND);

    char got[MAX_WORD_SIZE];
    copy(word.begin, word.end, got);
    got[word.end - word.begin] = '\0';
    ASSERT_STRING("BC", got);

    char s4[] = "B Q WE YR OW IR";
    assert(getWordBeforeFirstWordWithA(s4, &word) == NOT_FOUND_A_WORD_WITH_A);
}

void wordDescriptorToString(WordDescriptor word, char* dest) {
    if (word.begin == NULL && word.end == NULL)
        return;

    while (word.begin <= word.end) {
        *dest = *word.begin;
        word.begin++;
        dest++;
    }

    *dest = '\0';
}

void freeBagOfWords(BagOfWords * bag) {
    for (size_t i = 0; i < bag->size; i++) {
        bag->words[i].begin = NULL;
        bag->words[i].end = NULL;
    }

    bag->size = 0;
}

bool isWordsEqual(const WordDescriptor word1, const WordDescriptor  word2) {
    char* begin1 = word1.begin;
    char* begin2 = word2.begin;

    while (begin1 < word1.end && begin2 < word2.end) {
        if (*begin1 != *begin2)
            return false;

        begin1++;
        begin2++;
    }

    if (word1.end - begin1 > 0 || word2.end - begin2 > 0)
        return false;

    return true;
}

bool getWordWithoutSpace(char* begin_search, WordDescriptor * word) {
    word->begin = findNonSpace(begin_search);

    if (*word->begin == '\0')
        return 0;

    word->end = findSpace(word->begin) - 1;

    return 1;
}

WordDescriptor lastWordInFirstStringInSecondString(char *s1, char *s2){
    freeBagOfWords(&_bag);
    freeBagOfWords(&_bag2);
    char *beginsearch1 = s1;
    char *beginsearch2 = s2;

    while (getWordWithoutSpace(beginsearch1, &_bag.words[_bag.size])) {
        beginsearch1 = _bag.words[_bag.size].end + 1;
        _bag.size++;
    }

    while (getWordWithoutSpace(beginsearch2, &_bag2.words[_bag2.size])) {
        beginsearch2 = _bag2.words[_bag2.size].end + 1;
        _bag2.size++;
    }

    WordDescriptor word = {.begin = NULL, .end = NULL};

    for (int i = (int) _bag.size - 1; i >= 0; i--)
        for (int j = 0; j < _bag2.size; j++)
            if (isWordsEqual(_bag.words[i], _bag2.words[j])) {
                word = _bag.words[i];
                freeBagOfWords(&_bag);
                freeBagOfWords(&_bag2);
            }

    return word;
};

void test_lastWordInFirstStringInSecondString_zeroWords(){
    char s1[] = "";
    char s2[] = "";

    WordDescriptor word = lastWordInFirstStringInSecondString(s1,s2);

    assert(word.begin == NULL && word.end == NULL);
}
void test_lastWordInFirstStringInSecondString_oneWord(){
    char s1[] = "Ni in Pairs";
    char s2[] = "in Alabama";
    char dest[MAX_WORD_SIZE] = "";

    WordDescriptor word = lastWordInFirstStringInSecondString(s1,s2);
    wordDescriptorToString(word,dest);

    ASSERT_STRING("in", dest);
}
void test_lastWordInFirstStringInSecondString_moreThanOneWord(){
    char s1[] = "I buy the new forggys on the gs";
    char s2[] = "on the baobab";
    char dest[MAX_N_WORDS_IN_STRING] = "";

    WordDescriptor word = lastWordInFirstStringInSecondString(s1,s2);
    wordDescriptorToString(word,dest);

    ASSERT_STRING("the", dest);
}
void test_lastWordInFirstStringInSecondString(){
    test_lastWordInFirstStringInSecondString_zeroWords();
    test_lastWordInFirstStringInSecondString_oneWord();
    test_lastWordInFirstStringInSecondString_moreThanOneWord();
}

void free_string(char* s) {
    char *ptr = s;
    while (*ptr) {
        *ptr = '\0';
        ptr++;
    }
}

bool areEqualWordsInString(char* s){
    char *beginBuffer=_stringBuffer;

    copy(s,s+ strlen_(s),_stringBuffer);

    while(getWordWithoutSpace(beginBuffer,&_bag.words[_bag.size])){
        beginBuffer=_bag.words[_bag.size].end+2;
        _bag.size++;
    }

    free_string(_stringBuffer);

    if(_bag.size<=1)
        return 0;
    for (int i = 0; i < _bag.size; ++i)
        for (int j = i+1; j < _bag.size; ++j)
            if(isWordsEqual(_bag.words[i],_bag.words[j])) {
                freeBagOfWords(&_bag);

                return 1;
            }
    freeBagOfWords(&_bag);

    return 0;
}


void test_areEqualWordsInString_zeroWords(){
    char s[] = "" ;

    assert(!areEqualWordsInString(s));
}
void test_areEqualWordsInString_noEqual(){
    char s[]="Niko Ni";

    assert(!areEqualWordsInString(s));
}
void test_areEqualWordsInString_equal(){
    char s[]="Niko Niko Ni";

    assert(areEqualWordsInString(s));
}
void test_areEqualWordsInString(){
    test_areEqualWordsInString_zeroWords();
    test_areEqualWordsInString_noEqual();
    test_areEqualWordsInString_equal();
}

int compare_letters(void* s1,void* s2){
    return *(char*)s1-*(char *) s2;
}

void sortWordLetters(WordDescriptor *word){
    qsort(word->begin,word->end - word->begin, sizeof (char ), (int (*)(const void *, const void*)) compare_letters);
}

bool areIdenticalWordsInString(char* s) {
    freeBagOfWords(&_bag);
    freeBagOfWords(&_bag2);
    char *beginBuffer = _stringBuffer;

    copy(s, s + strlen_(s), _stringBuffer);

    while (getWordWithoutSpace(beginBuffer, &_bag.words[_bag.size])) {
        beginBuffer = _bag.words[_bag.size].end + 2;
        _bag.size++;
    }

    free_string(_stringBuffer);

    if (_bag.size <= 1)
        return 0;

    for (size_t i = 0; i < _bag.size; ++i)
        sortWordLetters(&_bag.words[i]);

    for (size_t i = 0; i < _bag.size; ++i)
        for (size_t j = 0; j < _bag.size; ++j)
            if (isWordsEqual(_bag.words[i], _bag.words[j])){
                freeBagOfWords(&_bag);

                return 1;
            }

    freeBagOfWords(&_bag);

    return 0;
}

void test_areIdenticalWordsInString_zeroWords(){
    char s[] = "";

    assert(!areIdenticalWordsInString(s));
}

void test_areIdenticalWordsInString_Equal(){
    char s[]="AA AA";

    assert(areIdenticalWordsInString(s));
}

void test_areIdenticalWordsInString_noEqual(){
    char s[]="AA NN";

    assert(areIdenticalWordsInString(s));
}

void test_areIdenticalWordsInString(){
    test_areIdenticalWordsInString_zeroWords();
    test_areIdenticalWordsInString_Equal();
    test_areIdenticalWordsInString_noEqual();
}

void getWordExceptLast(char* source, char* dest) {
    char *beginSearch = source;

    while (getWordWithoutSpace(beginSearch, &_bag.words[_bag.size])) {
        beginSearch = _bag.words[_bag.size].end + 1;
        _bag.size++;
    }

    if (_bag.size == 0) {
        freeBagOfWords(&_bag);
        return;
    }

    WordDescriptor last_word = _bag.words[_bag.size - 1];

    char *rec_ptr = dest;

    for (size_t i = 0; i < _bag.size - 1; i++) {
        if (!isWordsEqual(_bag.words[i], last_word)) {
            rec_ptr = copy(_bag.words[i].begin, _bag.words[i].end + 1, rec_ptr);
            if (i != _bag.size - 2)
                *rec_ptr++ = ' ';
        }
    }

    *rec_ptr='\0';
    freeBagOfWords(&_bag);
}

void test_getWordExceptLast_zeroWords(){
    char s[]="";
    char dest[]="";

    getWordExceptLast(s,dest);

    ASSERT_STRING("" ,dest);
}
void test_getWordExceptLast_oneWord(){
    char s[]="ABOBA";
    char dest[MAX_WORD_SIZE]="";

    getWordExceptLast(s,dest);

    ASSERT_STRING("",dest);
}
void test_getWordExceptLast_moreThanOneWord(){
    char s[]="Bibis Meme Bobo Bibis";
    char dest[MAX_WORD_SIZE]="";

    getWordExceptLast(s,dest);

    ASSERT_STRING("Meme Bobo",dest);
}

void test_getWordExceptLast(){
    test_getWordExceptLast_zeroWords();
    test_getWordExceptLast_oneWord();
    test_getWordExceptLast_moreThanOneWord();
}

WordDescriptor findPrecedingWord(char *s1, char *s2) {
    freeBagOfWords(&_bag);
    freeBagOfWords(&_bag2);
    char *begin_search_1 = s1;
    char *begin_search_2 = s2;

    while (getWordWithoutSpace(begin_search_1, &_bag.words[_bag.size])) {
        begin_search_1 = _bag.words[_bag.size].end + 1;
        _bag.size++;
    }

    while (getWordWithoutSpace(begin_search_2, &_bag2.words[_bag2.size])) {
        begin_search_2 = _bag2.words[_bag2.size].end + 1;
        _bag2.size++;
    }

    bool stop = 0;

    WordDescriptor w;
    WordDescriptor preceding_w = {.begin = NULL, .end = NULL};

    for (size_t i = 1; i < _bag.size; i++) {
        w = _bag.words[i];
        for (size_t j = 0; j < _bag2.size; j++)
            if (isWordsEqual(w, _bag2.words[j])) {
                stop = 1;
                break;
            }
        if (stop) {
            preceding_w = _bag.words[i - 1];
            break;
        }
    }

    freeBagOfWords(&_bag);
    freeBagOfWords(&_bag2);

    return preceding_w;
}

void test_findPrecedingWord_zeroWords() {
    char s1[] = "";
    char s2[] = "";
    char dest[MAX_WORD_SIZE] = "";

    WordDescriptor word = findPrecedingWord(s1, s2);
    wordDescriptorToString(word, dest);

    ASSERT_STRING("", dest);
}

void test_findPrecedingWord_noEqual() {
    char s1[] = "";
    char s2[] = "Bibis";
    char dest[MAX_WORD_SIZE] = "";

    WordDescriptor word = findPrecedingWord(s1, s2);
    wordDescriptorToString(word, dest);

    ASSERT_STRING("", dest);
}

void test_findPrecedingWord_equal() {
    char s1[] = "Water Bibis";
    char s2[] = "Bibis";
    char dest[MAX_WORD_SIZE] = "";

    WordDescriptor word = findPrecedingWord(s1, s2);
    wordDescriptorToString(word, dest);

    ASSERT_STRING("Water", dest);
}

void test_findPrecedingWord() {
    test_findPrecedingWord_zeroWords();
    test_findPrecedingWord_noEqual();
    test_findPrecedingWord_equal();
}

bool isPalindromeWord(WordDescriptor *word) {
    char* end=word->end;
    char* begin=word->begin;

    end--;

    while (end - begin > 0) {
        if (*begin != *end)
            return false;

        begin++;
        end--;
    }

    return true;
}

void removePalindromeWord(char *s){
    char* begin = _stringBuffer;
    char* end = copy(s,s+ strlen_(s),_stringBuffer);
    char* rec_ptr = s;

    WordDescriptor word;

    while(getWord(begin,&word)){
        if(!isPalindromeWord(&word)) {
            rec_ptr = copy(word.begin, word.end, rec_ptr);
            if (word.end != end)
                *rec_ptr++ = ' ';
        }
        begin = word.end + 1;
    }

    *rec_ptr = '\0';
    free_string(_stringBuffer);
}

void test_removePalindromeWord_zeroWords() {
    char s[] = "";

    removePalindromeWord(s);

    ASSERT_STRING("", s);
}

void test_removePalindromeWord_noPalidrome(){
    char s[] = "aNg abc";

    removePalindromeWord(s);

    ASSERT_STRING("aNg abc", s);
}

void test_removePalindromeWord_palindromeIsExist(){
    char s[] = "aNa abc";

    removePalindromeWord(s);

    ASSERT_STRING("abc", s);
}

void test_removePalindromeWord(){
    test_removePalindromeWord_zeroWords();
    test_removePalindromeWord_noPalidrome();
    test_removePalindromeWord_palindromeIsExist();
}

void complementString(char *s1, char *s2, int n) {
    char *beginSearch = s2;

    while (getWordWithoutSpace(beginSearch, &_bag.words[_bag.size])) {
        beginSearch = _bag.words[_bag.size].end + 1;
        _bag.size++;
    }

    char *rec_ptr = getEndOfString(s1);

    *rec_ptr++ = ' ';

    for (size_t i = _bag.size - n; i < _bag.size; ++i) {
        rec_ptr = copy(_bag.words[i].begin, _bag.words[i].end + 1, rec_ptr);
        if (i != _bag.size - 1)
            *rec_ptr++ = ' ';
    }
    *rec_ptr = '\0';

    freeBagOfWords(&_bag);
}

void balanceString(char* s1, int n1, char* s2, int n2) {
    if (n1 < n2)
        complementString(s1, s2, n2 - n1);
    else if (n2 < n1)
        complementString(s2, s1, n1 - n2);
}

void test_complementString_zeroWords(){
    char s1[MAX_WORD_SIZE] = "";
    int n1 = 0;
    char s2[MAX_WORD_SIZE] = "";
    int n2 = 0;

    balanceString(s1, n1, s2, n2);

    ASSERT_STRING("",s1);
    ASSERT_STRING("",s2);
}

void test_complementString_notEqual() {
    char s1[MAX_WORD_SIZE] = "Frog Pepe";
    int n1 = 2;
    char s2[MAX_WORD_SIZE] = "Bobo";
    int n2 = 1;

    balanceString(s1, n1, s2, n2);

    ASSERT_STRING("Frog Pepe",s1);
    ASSERT_STRING("Bobo Pepe",s2);
}

void test_complementString_equal() {
    char s1[MAX_WORD_SIZE] = "Frog Pepe";
    int n1 = 2;
    char s2[MAX_WORD_SIZE] = "NiKo Ni";
    int n2 = 2;

    balanceString(s1, n1, s2, n2);

    ASSERT_STRING("Frog Pepe",s1);
    ASSERT_STRING("NiKo Ni",s2);
}

void test_complementString(){
    test_complementString_zeroWords();
    test_complementString_notEqual();
    test_complementString_equal();
}

bool lettersBelongString(char* string, WordDescriptor word){
    bool include[26] = {0};
    char *begin = string;
    char *end = getEndOfString(string);

    while (begin != end){
        if(isalpha(*begin))
            include[*begin-CHARACTERS] = 1;

        begin++;
    }

    while (word.begin != word.end){
        if(!include[*word.begin-CHARACTERS])
            return 0;

        word.begin++;
    }

    return 1;
}

void test_lettersBelongString_zeroWords(){
    char s[] = "";
    WordDescriptor word;

    getWord("", &word);

    assert(!lettersBelongString(s,word));
}

void test_lettersBelongString_include(){
    char s[]="Bebey shutnyara";
    WordDescriptor word;

    getWord("shut",&word);

    assert(lettersBelongString(s,word));
}

void test_lettersBelongString_notInclude(){
    char s[]="Bebey shutnyara";
    WordDescriptor word;

    getWord("putis",&word);

    assert(!lettersBelongString(s,word));
}

void test_lettersBelongString(){
    test_lettersBelongString_zeroWords();
    test_lettersBelongString_include();
    test_lettersBelongString_notInclude();
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
    test_removeExtraSpaces();
    test_digitToStartWholeString();
    test_digitToStartNotReverseWholeString();
    test_replaceDigitsBySpaces();
    test_replace();
    test_wordsAreOrdered();
    test_printReverse();
    test_countPalindromes();
    test_alternateWords();
    test_writeWordsInReverseOrder();
    test_getWordBeforeFirstWordWithA();
    test_lastWordInFirstStringInSecondString();
    test_areEqualWordsInString();
    test_areIdenticalWordsInString();
    test_getWordExceptLast();
    test_findPrecedingWord();
    test_removePalindromeWord();
    test_complementString();
    test_lettersBelongString();
}

# endif