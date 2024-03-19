#include <stdio.h>

int main(void){
    long long a,b;
    scanf("%lld%lld",&a,&b);

    if((a < 0 && b > 0) || (a > 0 && b < 0)) printf("No");
    else if(a < 0 && b < 0 && a + b > 0) printf("Yes");
    else if(a > 0 && b > 0 && a + b < 0) printf("Yes");
    else printf("No");
    //printf("%lld\n",a+b);
    
    return 0;
}