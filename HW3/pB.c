#include <stdio.h>

int main(void){
    int a, b, c;
    int prize = 0;

    scanf("%d-%d-%d", &a, &b, &c);

    if(a == b && b == c) prize = 300;

    else {
        if(a + b < c) prize = 150;

        else {
            if(a == c) prize = 100;

            else {
                if(a < b) prize = 50;
            }
        }
    }

    printf("%d", prize);

    return 0;
}