#include<stdio.h>
int main()
{
   int n ,k1 ,k2 ,k3;
   int tot_parti;
   double tot_mon ,avg;
   scanf("%d %d %d %d",&n ,&k1 ,&k2 ,&k3);
   tot_parti = k1 + k2 + k3;
   tot_mon = ( (k1 - k1/3) + (k2 - k2/3) + (k3 - k3/3) ) * n;
   avg = tot_mon/tot_parti;
   printf("%.3f\n",avg);
   return 0;
}
