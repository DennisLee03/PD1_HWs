/*測試從多層迴圈去推枚舉單一元素的遞迴函數*/

#include <stdio.h>

int A[4];
int used[4];
int n = 4;
int count = 0;

/*void f0();
void f1();
void f2();
void f3();*/

void print_ans();

void r(int x);

int main() {
    
    for(int i = 0; i < n; i++) used[i] = 0;
    /*int level[3];

    printf("By loop:\n");
    for(level[0] = 0; level[0] < 3; level[0]++) {//f0
        A[0] = level[0];
        for(level[1] = 0; level[1] < 3; level[1]++) {//f1
            A[1] = level[1];
            for(level[2] = 0; level[2] < 3; level[2]++) {//f2
                A[2] = level[2];
                if(A[0] != A[1] && A[2] != A[1] && A[2] != A[0])
                    printf("%d %d %d\n", A[0], A[1], A[2]);
            }
        }
    }//f0(f1(f2()))

    printf("By function:\n");
    f0();*/

    printf("By recursive:\n");
    r(0);

    return 0;
}

/*void f0() {
    for(int i = 0; i < 3; i++) {
        A[0] = i;
        f1();
    }
}

void f1() {
    for(int i = 0; i < 3; i++) {
        A[1] = i;
        f2();
    }
}

void f2() {
    for(int i = 0; i < 3; i++) {
        A[2] = i;
        f3();
    }
}

void f3() {
    print_ans();
}*/

void r(int x) {//x represents xth for loop

    if(x == n) {
        print_ans();
        return;
    }

    for(int i = 0; i < n; i++) {
        if(used[i] == 0) {//剪枝
            used[i] = 1;
            A[x] = i;
            r(x + 1);
            used[i] = 0;
        }
    }
}

void print_ans() {

    for(int i = 0; i < n; i++) {
        printf("%d ", A[i] + 1);
        if(i == (n - 1)) {
            printf("\n");
            printf("= = = %d = = =\n", ++count);
        }
    }

    return;
}