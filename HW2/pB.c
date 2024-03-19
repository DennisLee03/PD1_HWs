#include<stdio.h>

int main()
{
   int n ,k1 ,k2 ,k3, tot_mon;

   scanf("%d %d %d %d",&n ,&k1 ,&k2 ,&k3);

   tot_mon = ( (k1 - k1/3) + (k2 - k2/3) + (k3 - k3/3) ) * n;

   printf("%d\n", tot_mon);

   return 0;
}
