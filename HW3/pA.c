#include <stdio.h>
#include <math.h>

int main(void)
{
    float a,b,c;
    scanf("(%f,%f,%f)",&a,&b,&c);
    
    /*float s1 = ( a + b + c ) / 2;
    float ans1 = sqrt(s1*(s1-a)*(s1-b)*(s1-c));*/

	double s2 = ( a + b + c ) / 2;
    double ans2 = sqrt(s2*(s2-a)*(s2-b)*(s2-c));
    
    printf("Area of triangle (%d,%d,%d) is %d.\n",(int)a,(int)b,(int)c,(int)ans2);
}
