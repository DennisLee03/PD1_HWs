#include <stdio.h>
#include <string.h>
#include <float.h>

void outputPattern(void* x);
void byPtrToFloatingPoint(char* x);
void byPtrToBitPattern(void *x);

int main()
{
    float f;
    double d;
    char bitPattern[64];
    char D;

    scanf("%f", &f);
    while ((D = getchar()) != '\n' && D != EOF);
    byPtrToBitPattern(&f);

    scanf("%s", bitPattern);
    while ((D = getchar()) != '\n' && D != EOF);
    byPtrToFloatingPoint(bitPattern);
    
    printf("%.100e\n", FLT_MIN);
    printf("%.100e\n", FLT_TRUE_MIN);

    return 0;
}

void byPtrToBitPattern(void *x)
{
    int* ptr = (int*)x;
    float* f = (float*)x;
    outputPattern(ptr);
}

void outputPattern(void* x)
{
    int *ptr = (int*)x;
    float* f = (float*)x;

    for(int i = 31; i >= 0; i--) printf("%d", ((*ptr) >> i) & 1);
    printf("\n");
}

void byPtrToFloatingPoint(char* x)
{
    int sign = 0, exponent = 0, mantissa = 0;

    for (int j = 0; j < 32; j++) {
        if (j == 0) {
            sign = x[0] - 48;
        } else if (j > 0 && j < 9) {
            exponent = (exponent << 1) + x[j] - 48;
        } else {
            mantissa = (mantissa << 1) + x[j] - 48;
        }
    }
    int temp = (sign << 31) + (exponent << 23) + mantissa;
    float* ptr = (float*)&temp;

    printf("%.100e\n", *ptr);
}