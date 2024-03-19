#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int condition = 0;

void Homework6_1();
void Homework6_2();
void Homework6_3();
void Homework6_4();

void Swap(long long **M, int row, int column);

long long RAN(int x);
long long RAN_VAL(int min, int max);
long long RAN_LEN(int min, int max);

int main() {

    srand((unsigned)time(NULL));

    int option;
    scanf("%d", &option);

    if(option == 1) Homework6_1();
    if(option == 2) Homework6_2();
    if(option == 3) Homework6_3();
    if(option == 4) Homework6_4();

    return 0;
}

void Homework6_1() {

    long long length = RAN_LEN(5000, 200000);//決定序列長度, range[5000, 200000];兩個參數為上下界
    printf("\n");
    long long *A = (long long*)malloc(length * sizeof(long long));

    for(long long i = 0;i < length;i++) {
        A[i] = RAN_VAL(1, 1000000000);//產生序列元素的值，range[1, 1000000000];一個參數為max
        if(i != length - 1) printf(" ");
    }printf("\n");

    for(long long i = 0;i < length;i++) {
        printf("%lld", A[length - i - 1]);
        if(i != length - 1) printf(" ");
    }

    free(A);

    return;
}

void Homework6_2() {

    long long length = RAN_LEN(5000, 200000);//決定序列長度, range[5000, 200000]
    printf("\n");
    long long *A = (long long*)malloc(length * sizeof(long long));

    long long index;
    long long count = 0;
    for(long long i = 0;i < length;i++) A[i] = 0;

    condition = 1;

    while(count != (length - 1)) {
        index = RAN_VAL(1, length);
        if(A[index - 1] != 1) {
            A[index - 1] = 1;
            printf("%lld", index);
            if(count != length - 2) printf(" ");
            count += 1;
        }//產生不重複的序列元素，range[1, length]，會少產生一數字
    }printf("\n");

    condition = 0;

    for(long long i = 0;i < length;i++) if(A[i] != 1) printf("%lld", i + 1);

    free(A);

    return;
}

void Homework6_3() {

    long long length = RAN_LEN(50000, 100000);//決定序列長度, range[50000, 100000]
    printf("\n");

    long long *A = (long long*)malloc(length * sizeof(long long));
    long long *B = (long long*)malloc(length * sizeof(long long));

    for(long long i = 0;i < length;i++) {
        A[i] = RAN_VAL(1, 1000000000);//產生序列元素的值，range[1, 1000000000]
        if(i != length - 1) printf(" ");
        if(i == 0) B[i] = A[i];
        else B[i] = B[i-1] + A[i];
    }printf("\n");

    long long qt = RAN_LEN(50000, 100000);//產生計算區間和次數，range[50000, 100000]
    printf("\n");
    long long l, r;//1 <= L <= R <= length

    long long *qsum = (long long*)malloc(qt * sizeof(long long));

    for(long long i = 0;i < qt;i++) {
        l = RAN_VAL(1, length);
        printf(" ");
        r = RAN_VAL(l, length);
        printf("\n");
        if(l == 1) qsum[i] = B[r - 1];
        else qsum[i] = B[r - 1] - B[l - 2];
    }

    for(long long i = 0;i < qt;i++) {
        printf("%lld", qsum[i]);
        if(i != qt - 1) printf("\n");
    }

    free(A);
    free(B);
    free(qsum);

    return;
}

void Homework6_4() {
    //列(row)、行(column);range[500, 1000]
    int row = RAN_LEN(500, 1000);
    printf(" ");
    int column = RAN_LEN(500, 1000);
    printf("\n");

    long long **M = (long long **)malloc(row * sizeof(long long *));
    for(long long i = 0;i < row;i++) M[i] = (long long *)malloc(column * sizeof(long long));

    for(long long i = 0;i < row;i++) 
        for(long long j = 0;j < column;j++) {
             M[i][j] = RAN_VAL(1, 1000);//矩陣元素值，range[1, 1000]
             if(j == column - 1) printf("\n");
             if(j != column - 1) printf(" ");
        }

    Swap(M, row, column);//五次的座標交換

    for(long long i = 0;i < row;i++) {
        for(long long j = 0;j < column;j++) {
            printf("%lld", M[i][j]);
            if((j == column - 1) && i != row - 1) printf("\n");
             if(j != column - 1) printf(" ");
        } 
    }

    free(M);

    return;
}

void Swap(long long **M, int row, int column) {
    long long buf;

    long long x1[5], y1[5], x2[5], y2[5];
    for(long long i = 0;i < 5;i++){
        x1[i] = RAN_VAL(1, row);
        printf(" ");
        y1[i] = RAN_VAL(1, column);
        printf(" ");
        x2[i] = RAN_VAL(1, row); 
        printf(" ");
        y2[i] = RAN_VAL(1, column);
        printf("\n");
    }//x: range[1, column]; y: range[1, row]
    for(long long i = 0;i < 5;i++) {
        buf = M[x1[i] - 1][y1[i] - 1];
        M[x1[i] - 1][y1[i] - 1] = M[x2[i] - 1][y2[i] - 1];
        M[x2[i] - 1][y2[i] - 1] = buf;
    }
}

long long RAN_LEN(int min, int max) {

    long long length = (rand() % (max - min + 1) + min);

    printf("%lld", length);

    return length;
}

long long RAN_VAL(int min, int max) {

    long long value = ((rand() % (max - min + 1)) + min);

    if(condition == 0) {
        printf("%lld", value);
        return value;
    }

    if(condition == 1) return value;
}
