#include <stdio.h>

int main(void){

    int n = 0;
    int a = 0, b = 0, c = 0;

    n = scanf("%d%d%d",&a ,&b ,&c);
    char D = 'Q';
    while ((D = getchar()) != '\n' && D != EOF){
        if(D != 'Q'){
            printf("input too much\n");
            printf("in while in if %c\n",D);
        }
        printf("in while %c\n",D);
    }
    printf("outside %c\n",D);
    printf("(%d %d %d)  n = %d\n",a ,b ,c ,n);

    return 0;
}
