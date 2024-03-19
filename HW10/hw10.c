#include <stdio.h>
#include <stdlib.h>

typedef double (*F)(double x, int n);

double power(double x, int n);
double multiply(double x, int n);
double divide(double x, int n);

double powerpower(F f, double x, int n, int m);

int main(int argc, char *argv[])//filename x n m
{
    double x = atof(argv[1]);
    int n = atoi(argv[2]), m = atoi(argv[3]);

    printf("x = %g, n = %d, m = %d\n", x, n, m);

    printf("(x^n)^m = %g\n", powerpower(power, x, n, m));
    printf("(x*n)^m = %g\n", powerpower(multiply, x, n, m));
    printf("(x/n)^m = %g\n", powerpower(divide, x, n, m));

    return 0;
}

double power(double x, int n)
{
    int p = abs(n);
    double result = 1.0;

    while (p > 0) 
    {
        if (p % 2 == 1) result *= x;
        x *= x;
        p /= 2;
    }

    return ((n > 0) ? result : (1.0 / result));
}

double multiply(double x, int n)
{
    return(x * (double)n);
}

double divide(double x, int n)
{
    return(x / (double)n);
}

double powerpower(F f, double x, int n, int m)
{
    return(power((f(x, n)), m));
}
