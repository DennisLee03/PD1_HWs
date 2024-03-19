#include <stdio.h>

double f(double x);

int main(void){
    int n;
    double ans = 0.0;
    scanf("%d", &n);
    //printf("%Lf\n", f(n));
    for(double i = 0.0;i < n + 1;i++) ans += 1.0/f(i);
    printf("%.12lf", ans);

    return 0;
}

double f(double x){
    if(x == 0) return 1.0;
    x *= f(x - 1);
    return x;
}