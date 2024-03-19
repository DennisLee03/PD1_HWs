/*真值表枚舉*/

#include <stdio.h>

int A[5] = {1, 2, 3, 4, 5};
int n = 5;
int k = 3;
int choose[5];

void truth_table(int x, int ones, int zeros);
//void truth_table(int x);
void print_table();

int main() {

    /*int level[3];

    for(level[0] = 0; level[0] < 2; level[0]++) {
        A[0] = level[0];
        for(level[1] = 0; level[1] < 2; level[1]++) {
            A[1] = level[1];
            for(level[2] = 0; level[2] < 2; level[2]++) {
                A[2] = level[2];
                print_table();
            }   
        }
    }*/

    truth_table(0, 0, 0);

    return 0;
}

/*void truth_table(int x) {

    if(x == n) {
        print_table();
        return;
    }

    for(int i = 0; i < 2; i++) {
        choose[x] = i;
        truth_table(x + 1);
    }
}*/

void truth_table(int x, int ones, int zeros) {
    if (x == n) {
        if (ones == k && zeros == n - k) {
            print_table();
        }
        return;
    }

    // Choose 1
    choose[x] = 1;
    truth_table(x + 1, ones + 1, zeros);

    // Choose 0
    choose[x] = 0;
    truth_table(x + 1, ones, zeros + 1);
}

void print_table() {

    int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += A[i] * choose[i];
        printf("%d ", choose[i]);
    }
    printf("\n= = = %d = = =\n", sum);
}

/*void print_table() {

    printf("{");
    for(int i = 0; i < n; i++) {
        if(A[i] * choose[i] != 0) printf("%d ", A[i] * choose[i]);
        if(i == n - 1) printf("}\n");
    }
}*/
