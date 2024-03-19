#include<math.h>
#include<stdio.h>
int main(){
   int a,b,c;
   double ans;
   scanf("%d %d %d", &a, &b, &c);
   ans = pow(a*c, 0.5) + pow(a, b) + log10(a*b*c);
   printf("%.3f\n", ans);
   return 0;
}
