#include <stdio.h>
#include <stdlib.h>

int Ocondition = 0, Acondition = 0;
int A = 0, B = 0, C = 0, Price = 0, Box = 0;

void Openning();
void List();
void Adding();
int gcd(int m, int n);

int main(void){
    int n = 0;
    int numScanned = 0;

    printf("//////////Welcome to NCKU-PD1-Kirby-Shop\\\\\\\\\\\\\\\\\\\\\n");
    printf("Options: (1)Openning (2)List (3)Adding (4)Exit\n");
    
    while((numScanned = scanf("%d", &n)) + 1 ){
        char D;
        while ((D = getchar()) != '\n' && D != EOF);
        if(n >= 1 && n <= 4){
            if(n == 1) Openning();
            if(n == 2) List();
            if(n == 3) Adding();
            if(n == 4) return 0;
            n = 0;
        }
        else printf("Error: Please try again!\n");
        printf("Options: (1)Openning (2)List (3)Adding (4)Exit\n");
    }
    return 0;
}

void Openning(){
    if(Ocondition == 0){
        printf("Your shop is openning!\n");
        Ocondition = 1;
    }
    else printf("Your Kirby shop has already opened :(\n");

    return;
}

void List(){
    printf("===================================\n");
    printf("Kirby-A: %d\n", A);
    printf("Kirby-B: %d\n", B);
    printf("Kirby-C: %d\n", C);
    printf("Kirby: %d, Money: %d\n", A + B + C, Price);
    printf("===================================\n");

    return;
}

void Adding(){
    if(Ocondition == 0){
        printf("Your Kirby shop has not opened\n");
        return;
    }

    int a = 0, b = 0, c = 0, box = 0, price = 0;
    int numScanned = 0;
    
    printf("Please enter three numbers: ");

    while(((numScanned = scanf("%d %d %d", &a, &b, &c)) + 1)){

        char D = '0';
        while ((D = getchar()) != '\n' && D != EOF){
            if(D != '0'){
                Acondition = 1;
                a = 0;
                b = 0;
                c = 0;
            }
        }

        if(a > 0 && b > 0 && c > 0){
            box = gcd(a, gcd(b, c));
            price = (a + b + c) - 2 * box;
            printf("Divide these Kirbys into %d boxes, with the number of Kirby in each box being %d, %d, and %d\n", box, a/box, b/box, c/box);
            printf("Price: %d\n", price);
            A += a;
            B += b;
            C += c;
            Box += box;
            Price += price;

            Acondition = 0;

            return;
            }
        else if(a == -1 && b == -1 && c == -1 && Acondition){
            Acondition = 0;
            return;
        }
        else {
            printf("Error: Please try again or enter '-1 -1 -1' to make a new options: ");
            Acondition = 1;
        }//當輸入非正數的時候 => 輸入三正整數去做打包；輸入-1 -1 -1重選option
    }
}

int gcd(int m, int n){
    int t = 1;
    while(t != 0) {
        t = m % n;
        m = n;
        n = t;
    }
    return m;
}
