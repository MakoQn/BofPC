# include <stdio.h>
# include "E:\C23Exe\libs\data_structures\matrix\matrix.h"
# include "E:\C23Exe\libs\data_structures\19_laba\file.h"
# define MAX_COUNT_OF_DOMAINS 200
# define MAX_LENGTH_STRING 200

void fulfillQuery(matrix *m, matrix *array_of_query){
    for (size_t i = 0; i < array_of_query->nRows; i++)
        for (size_t j = array_of_query->values[i][0]; j <=  array_of_query->values[i][2]; j++)
            for (size_t k = array_of_query->values[i][1]; k <=  array_of_query->values[i][3]; k++)
                m->values[j][k]++;
}

void test_fulfillQuery(){
    matrix m = createMatrixFromArray((int []){
            0,0,0,
            0,0,0,
            0,0,0
    }, 3, 3);

    matrix array_of_query = createMatrixFromArray((int []){
            1,1,2, 2,
            0,0,1, 1
    }, 2, 4);

    fulfillQuery(&m, &array_of_query);

    matrix expected_m = createMatrixFromArray((int []){
            1,1,0,
            1,2,1,
            0,1,1
    }, 3, 3);

    assert(areTwoMatricesEqual(&m, &expected_m));

    freeMemMatrix(&m);
    freeMemMatrix(&array_of_query);
    freeMemMatrix(&expected_m);
}

size_t countOfNeighbors(matrix m, int row, int col){
    size_t count_of_neighbors = 0;

    for (int i = row - 1; i < row + 2; i++)
        for (int j = col - 1; j < col + 2; j++)
            if ((i > -1 && i < m.nRows && j > -1 && j < m.nCols) && m.values[i][j] && (row != i || col != j))
                count_of_neighbors++;

    return count_of_neighbors;
}

bool isAlive(matrix m, int i, int j, size_t count_of_neighbors) {
    return ((m.values[i][j] == 1 && (count_of_neighbors == 2 || count_of_neighbors == 3)) || (m.values[i][j] == 0 && count_of_neighbors == 3));
}

matrix live(matrix m){
    matrix refreshedMatrix = getMemMatrix(m.nRows, m.nCols);

    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; j++) {
            size_t count_neighbors = countOfNeighbors(m, i, j);

            refreshedMatrix.values[i][j] = isAlive(m, i, j, count_neighbors);
        }

    return refreshedMatrix;
}

void test_live(){
    matrix m = createMatrixFromArray((int[]) {
                                             0, 1, 0,
                                             0, 0, 1,
                                             1, 1, 1,
                                             0, 0, 0},
                                     4, 3);

    matrix refreshedM = live(m);

    matrix expected_m = createMatrixFromArray((int[]) {
                                                      0, 0, 0,
                                                      1, 0, 1,
                                                      0, 1, 1,
                                                      0, 1, 0},
                                              4, 3);

    assert(areTwoMatricesEqual(&refreshedM, &expected_m));

    freeMemMatrix(&m);
    freeMemMatrix(&refreshedM);
    freeMemMatrix(&expected_m);
}

int compare(const void *arg1, const void *arg2){
    return *(int *)arg1 - *(int *)arg2;
};

void getPixelsValue(int *a, matrix m, size_t row, size_t col){
    size_t k = 0;

    for (size_t i = row - 1; i < row + 2; i++){
        for (size_t j = col - 1; j < col + 2; j++)
            if (i != row || j != col)
                a[k++] = m.values[i][j];
    }

    qsort(a, 8, sizeof(int), compare);
}

void medianFilter(matrix *m, size_t frame_size){
    int frame[frame_size * frame_size - 1];

    for (size_t i = 1; i < frame_size - 1; i++)
        for (size_t j = 1; j < frame_size - 1; j++) {
            getPixelsValue(frame, *m, i, j);
            int median = (frame[frame_size] + frame[frame_size + 1]) / 2;

            m->values[i][j] = median;
        }
}

void test_medianFilter(){
    matrix m = createMatrixFromArray((int[]){
                                             10, 20, 30,
                                             25, 35, 45,
                                             15, 25, 35},
                                     3, 3);

    medianFilter(&m, 3);

    matrix expected_m = createMatrixFromArray((int[]){
                                                      10, 20, 30,
                                                      25, 25, 45,
                                                      15, 25, 35},
                                              3, 3);

    assert(areTwoMatricesEqual(&m, &expected_m));

    freeMemMatrix(&m);
    freeMemMatrix(&expected_m);
}

typedef struct domain{
    size_t count_of_visits;
    char name[MAX_LENGTH_STRING];
} domain;

size_t searchDomainInResults(const domain *r, size_t size, char *s) {
    for(size_t i = 0; i < size; i++)
        if (strcmp(r[i].name, s) == 0)
            return i;

    return size;
}

bool searchNumFromArray(const size_t *a, size_t length, size_t num) {
    for (size_t i = 0; i < length; i++)
        if (num == a[i])
            return 1;

    return 0;
}

void handlerDotPrtNotNull(domain *a, size_t i, char *dot, domain *r, size_t *size_r) {
    strcpy(a[i].name, dot + 1);
    size_t pos = searchDomainInResults(r, *size_r, a[i].name);

    if (pos == *size_r){
        r[*size_r] = a[i];
        *size_r += 1;
    }else
        r[pos].count_of_visits += a[i].count_of_visits;
}

void outputDomains(domain *r, size_t size) {
    for (size_t i = 0; i < size; i++)
        printf("%d %s\n", r[i].count_of_visits, r[i].name);
}

void countOfVisits(domain *cpdomains, size_t size) {
    domain r[MAX_COUNT_OF_DOMAINS];
    size_t close_i[size];
    size_t count_of_close = 0;
    size_t size_r = 0;

    for (size_t i = 0; i < size; i++)
        r[size_r++] = cpdomains[i];

    while (count_of_close != size)
        for (size_t i = 0; i < size; i++)
            if (!searchNumFromArray(close_i, count_of_close, i)){
                char *dot = strchr(cpdomains[i].name, '.');

                if (dot != NULL)
                    handlerDotPrtNotNull(cpdomains, i, dot, r, &size_r);
                else
                    close_i[count_of_close++] = i;
            }

    outputDomains(r, size_r);
}

void test_countOfVisits(){
    domain cpdomains[4] = {{900, "google.mail.com"},
                           {50,  "yahoo.com"},
                           {1,   "intel.mail.com"},
                           {5,   "wiki.org"}};

    countOfVisits(cpdomains, 4);
}

size_t countOfSubmatrix(matrix m) {
    matrix nums = getMemMatrix(m.nRows, m.nCols);
    size_t count_of_submatrix = 0;

    for (size_t i = 0; i < m.nRows; i++)
        for (size_t j = 0; j < m.nCols; j++) {
            if (m.values[i][j] == 1) {
                if (i != 0)
                    nums.values[i][j] = nums.values[i - 1][j] + 1;
                else
                    nums.values[i][j] = 1;
            }else
                nums.values[i][j] = 0;
        }

    for (size_t j = 0; j < m.nCols; j++)
        for (size_t i = 0; i < m.nRows; i++)
            for (size_t k = j + 1; k < m.nCols + 1; k++) {
                int min = nums.values[i][j];

                for (size_t l = j; l < k; l++)
                    if (nums.values[i][l] < min)
                        min = nums.values[i][l];

                count_of_submatrix += min;
            }

    freeMemMatrix(&nums);

    return count_of_submatrix;
}

void test_countOfSubmatrix(){
    matrix m = createMatrixFromArray((int[]){
                                             1, 0, 1,
                                             1, 1, 0,
                                             1, 1, 0},
                                     3, 3);

    size_t answer = countOfSubmatrix(m);

    assert(answer == 13);

    freeMemMatrix(&m);
}

void minStrNum(const char *p, size_t n, char *r, size_t *res_len) {
    char buf[MAX_LENGTH_STRING];
    size_t buf_len = 0;
    size_t r_len = 0;
    char num = '1';

    for (size_t i = 0; i < n; i++) {
        buf[buf_len++] = num++;

        if (p[i] == 'I')
            while (buf_len > 0)
                r[r_len++] = buf[--buf_len];
    }

    buf[buf_len++] = num;

    while (buf_len > 0)
        r[r_len++] = buf[--buf_len];

    r[r_len] = '\0';

    *res_len = r_len;
}

void test_minStrNum(){
    char pattern1[] = "IIIDIDDD";
    char got1[10];
    size_t res_len1;

    minStrNum(pattern1, 8, got1, &res_len1);

    char expected1[10] = "123549876";

    assert(strcmp(got1, expected1) == 0);

    char pattern2[] = "DDD";
    char got2[5];
    size_t res_len2;

    minStrNum(pattern2, 3, got2, &res_len2);

    char expected2[10] = "4321";

    assert(strcmp(got2, expected2) == 0);
}

typedef struct node{
    int level;
    int value;
    int index;
} node;

void maxElement(int *a, int level, int begin, int end, int *index, vectorVoid *r){
    (*index)++;

    if (end < begin) {
        node n = {level, -1, *index};

        pushBackV(r, &n);

        return;
    }

    if (end == begin) {
        node n = {level, a[end], *index};

        pushBackV(r, &n);

        return;
    }

    int max = INT_MIN;
    int max_i;

    for (int i = begin; i <= end; i++) {
        if (max < a[i]) {
            max = a[i];
            max_i = i;
        }
    }

    node n = {level, max, *index};

    pushBackV(r, &n);

    maxElement(a, level + 1, begin, max_i - 1, index, r);
    maxElement(a, level + 1, max_i + 1, end, index, r);
}

int compareTreeItemByLevel(const void *nodeArg1, const void *nodeArg2){
    node *node1 = (node*)nodeArg1;
    node *node2 = (node*)nodeArg2;
    int diff = node1->level - node2->level;

    if (diff == 0)
        return node1->index - node2->index;

    return diff;
}

vectorVoid breadthFirstSearch(int *nums, int l){
    vectorVoid r = createVectorV(9, sizeof(node));

    int index = 0;

    maxElement(nums, 0, 0, l - 1, &index, &r);
    qsort(r.data, r.size, sizeof(node), compareTreeItemByLevel);

    return r;
}

void test_breadthFirstSearch(){
    int nums[] = {3, 2, 1, 6, 0, 5};

    vectorVoid r = breadthFirstSearch(nums, 6);

    for (int i = 0; i < r.size; i++) {
        node n;

        getVectorValueV(&r, i, &n);

        printf("%d ", n.value);
    }

    deleteVectorV(&r);
}

void reshuffling(const char *s, size_t length, const size_t *indexes, char *new_s) {
    for (size_t i = 0; i < length; i++)
        new_s[i] = s[indexes[i]];

    new_s[length] = '\0';
}

void test_reshuffling(){
    char s1[] = "abc";
    size_t indexes1[] = {0, 1, 2};
    char got1[3];

    reshuffling(s1, 3, indexes1, got1);

    char expected1[4] = "abc";

    assert(strcmp(got1, expected1) == 0);

    char s2[] = "abap";
    size_t indexes2[] = {0, 3, 2, 1};
    char got2[4];

    reshuffling(s2, 4, indexes2, got2);

    char expected2[5] = "apab";

    assert(strcmp(got2, expected2) == 0);
}

int main() {
    test_fulfillQuery();
    test_live();
    test_medianFilter();
    test_countOfVisits();
    test_countOfSubmatrix();
    test_minStrNum();
    test_breadthFirstSearch();
    test_reshuffling();

    return 0;
}
