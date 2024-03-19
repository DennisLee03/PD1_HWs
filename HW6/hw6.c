#include <stdio.h>
#include <stdlib.h>

void Homework6_1();
void Homework6_2();
void Homework6_3();
void Homework6_4();

void Swap(int **M);

int main() {

    int option;
    scanf("%d", &option);

    if(option == 1) Homework6_1();
    if(option == 2) Homework6_2();
    if(option == 3) Homework6_3();
    if(option == 4) Homework6_4();

    return 0;
}

void Homework6_1() {

    int x;
    scanf("%d", &x);
    int *A = (int*)malloc(x * sizeof(int));

    for(int i = 0;i < x;i++) scanf("%d", &A[i]);

    for(int i = 0;i < x;i++) {
        printf("%d", A[x - i - 1]);
        if(i != x - 1) printf(" ");
    }

    free(A);

    return;
}

void Homework6_2() {

    int x;
    scanf("%d", &x);

    int *A = (int*)malloc(x * sizeof(int));

    int index;
    for(int i = 0;i < x - 1;i++) {
        scanf("%d", &index);
        A[index - 1] = 1;
    }

    for(int i = 0;i < x;i++) {
        if(A[i] != 1) printf("%d", i + 1);
    }

    free(A);

    return;
}

void Homework6_3() {

    long long x, qt, l, r;
    scanf("%lld", &x);

    long long *A = (long long*)malloc(x * sizeof(long long));
    long long *B = (long long*)malloc(x * sizeof(long long));

    for(long long i = 0;i < x;i++) {
        scanf("%lld", &A[i]);
        if(i == 0) B[i] = A[i];
        else B[i] = B[i-1] + A[i];
    }

    scanf("%lld", &qt);

    long long *qsum = (long long*)malloc(qt * sizeof(long long));

    for(long long i = 0;i < qt;i++) {
        scanf("%lld %lld", &l, &r);
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

    int x, y;//x為列(row)、y為行(column)
    scanf("%d %d", &x, &y);

    int **M = (int **)malloc(x * sizeof(int *));
    for(int i = 0;i < x;i++) M[i] = (int *)malloc(y * sizeof(int));

    for(int i = 0;i < x;i++) 
        for(int j = 0;j < y;j++)
            scanf("%d", &M[i][j]);
    
    Swap(M);

    for(int i = 0;i < x;i++) {
        for(int j = 0;j < y;j++) {
            printf("%d", M[i][j]);
            if((j + 1) != y) printf(" ");
            if(((j + 1) == y) && ( (i + 1) != x)) printf("\n");
        } 
    }

    free(M);

    return;
}

void Swap(int **M) {

    int buf;
    int x1[5], y1[5], x2[5], y2[5];

    for(int i = 0;i < 5;i++){
        scanf("%d %d %d %d", &x1[i], &y1[i], &x2[i], &y2[i]);
    }

    for(int i = 0;i < 5;i++) {
        buf = M[x1[i] - 1][y1[i] - 1];
        M[x1[i] - 1][y1[i] - 1] = M[x2[i] - 1][y2[i] - 1];
        M[x2[i] - 1][y2[i] - 1] = buf;
    }
}

