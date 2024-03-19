#include <stdio.h>

void f(int x);
void ff(void* x);

int main()
{
    int x = 10;

    void * fptr = &f;

    ff(f);

    return 0;

}

void f(int x)
{
    printf("Square of x = %d\n", x * x);
}

void ff(void* x)
{
    (*f)(19);
}