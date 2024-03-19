#include<stdio.h>
int Swap(int x);
int main(){
   int i,si;
   scanf("%d",&i);
   si = Swap(i);
   printf("%d\n",si *2023);
   return 0;
}
int Swap(int x){
   int ud, td, newx;
   ud = x % 10;
   td = (x % 100 - ud) / 10;
   newx = x - 10 * td - ud + 10 * ud + td;
   return newx;
}
