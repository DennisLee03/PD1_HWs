#include <stdio.h>
#include <string.h>

typedef union uFloat {
    unsigned int patternBase10;
    float value;
} uF;
typedef union uDouble {
    unsigned long long patternBase10;
    double value;
} uD;

typedef struct sFloat {
    unsigned int mantissa : 23;
    unsigned int exponent : 8;
    unsigned int sign : 1;
} sF;
typedef struct sDouble {
    unsigned long long mantissa : 52;
    unsigned long long exponent : 11;
    unsigned long long sign : 1;
} sD;

typedef union uFloatBitField {
    float f;
    sF s;
} uFBF;
typedef union uDoubleBitField {
    double d;
    sD s;
} uDBF;



void outputPattern(void* x, int type);

//(a)transform by integer pointer:
void byPtrToFloatingPoint(char* x, int type);
void byPtrToBitPattern(void *x, int type);

//(b)transform by union:
void byUnionToFloatingPoint(void* uu, char* x, int type);

//(c)transform by bitfield:
void byBitFieldToFloatingPoint(void* uu, char* x, int type);

int main()
{
    char opt;
    char bitPattern[64];

    printf("Enter a or b or c or d to :\n(a)transform by integer pointer\n(b)transform by union\n(c)transform by bitfield\n(d)exit the program\n");
    while(scanf("%c", &opt))
    {
        char D;
        while ((D = getchar()) != '\n' && D != EOF);

        if(opt == 'a')//(a)transform by integer pointer:
        {
            float f;
            double d;

            printf("Eneter a number: ");
            scanf("%f", &f);
            byPtrToBitPattern(&f, 1);
            printf("Eneter a 32-bit bit pattern: ");
            scanf("%s", bitPattern);
            byPtrToFloatingPoint(bitPattern, 1);

            printf("Eneter a number: ");
            scanf("%lf", &d);
            byPtrToBitPattern(&d, 2);
            printf("Eneter a 64-bit bit pattern: ");
            scanf("%s", bitPattern);
            byPtrToFloatingPoint(bitPattern, 2);

            while ((D = getchar()) != '\n' && D != EOF);
        }

        if(opt == 'b')//(b)transform by union:
        {
            uF uf;
            uD ud;

            printf("Eneter a number: ");
            scanf("%f", &uf.value);
            outputPattern(&uf.value, 1);
            printf("Eneter a 32-bit bit pattern: ");
            scanf("%s", bitPattern);
            byUnionToFloatingPoint(&uf, bitPattern, 1);

            printf("Eneter a number: ");
            scanf("%lf", &ud.value);
            outputPattern(&ud.value, 2);
            printf("Eneter a 64-bit bit pattern: ");
            scanf("%s", bitPattern);
            byUnionToFloatingPoint(&ud, bitPattern, 2);

            while ((D = getchar()) != '\n' && D != EOF);
        }

        if(opt == 'c')//(c)transform by bitfield:
        {
            uFBF fbf;
            uDBF dbf;

            printf("Eneter a number: ");
            scanf("%f", &fbf.f);
            outputPattern(&fbf, 3);
            printf("Eneter a 32-bit bit pattern: ");
            scanf("%s", bitPattern);
            byBitFieldToFloatingPoint(&fbf, bitPattern, 1);

            printf("Eneter a number: ");
            scanf("%lf", &dbf.d);
            outputPattern(&dbf, 4);
            printf("Eneter a 64-bit bit pattern: ");
            scanf("%s", bitPattern);
            byBitFieldToFloatingPoint(&dbf, bitPattern, 2);

            while ((D = getchar()) != '\n' && D != EOF);
        }

        if(opt == 'd') return 0;

        printf("= = = = = = = = = = = = = = = = = =\n");
        printf("Enter a or b or c or d to :\n(a)transform by integer pointer\n(b)transform by union\n(c)transform by bitfield\n(d)exit the program\n");
    }
}

void byPtrToBitPattern(void *x, int type)
{
    if(type == 1)
    {
        int* ptr = (int*)x;
        float* f = (float*)x;
        
        outputPattern(ptr, type);
    }

    if(type == 2)
    {
        long long* ptr = (long long*)x;
        double* d = (double*)x;

        outputPattern(ptr, type);
    }
}

void outputPattern(void* x, int type)
{//輸出bit patterb的函數，主要透過and運算每個bit是否為1
    if(type == 1)
    {
        int *ptr = (int*)x;
        float* f = (float*)x;

        printf("Bit pattern for float %f: ", *f);
        for(int i = 31; i >= 0; i--)
        {
            printf("%d", ((*ptr) >> i) & 1);
            //if(i == 31 || i == 23) printf(" ");
        }
    }

    if(type == 2)
    {
        long long* ptr = (long long*)x;
        double* d = (double*)x;

        printf("Bit pattern for double %lf: ", *d);
        for(int i = 63; i >= 0; i--)
        {
            printf("%lld", ((*ptr) >> i) & 1);
            //if(i == 63 || i == 52) printf(" ");
        }
    }

    if(type == 3)
    {
        uFBF* ptr = (uFBF*)x;
        printf("Bit pattern for float %f: ", ptr->f);
        printf("%d", ptr->s.sign);
        //printf(" ");
        for(int i = 7; i >= 0; i--) printf("%d", ((ptr->s.exponent) >> i) & 1);
        //printf(" ");
        for(int i = 22; i >= 0; i--) printf("%d", ((ptr->s.mantissa) >> i) & 1);
    }

    if(type == 4)
    {
        uDBF* ptr = (uDBF*)x;
        printf("Bit pattern for double %lf: ", ptr->d);
        printf("%d", ptr->s.sign);
        //printf(" ");
        for(int i = 10; i >= 0; i--) printf("%d", ((ptr->s.exponent) >> i) & 1);
        //printf(" ");
        for(int i = 51; i >= 0; i--) printf("%d", (int)((ptr->s.mantissa) >> i) & 1);
    }

    printf("\n");
}

void byPtrToFloatingPoint(char* x, int type)
{
    //'0' = 48, '1' = 49(需要減去48)
    printf("The number for the bit pattern equals to ");
    if(type == 1)
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
        }//printf("%d %d %d\n", sign, exponent, mantissa);
        int temp = (sign << 31) + (exponent << 23) + mantissa;
        float* ptr = (float*)&temp;//printf("%d\n", temp);

        printf("%f\n", *ptr);
    }

    if(type == 2)
    {
        long long sign = 0, exponent = 0, mantissa = 0;
        for (int j = 0; j < 64; j++) {
            if (j == 0) {
                sign = x[0] - 48;
            } else if (j > 0 && j < 12) {
                exponent = (exponent << 1) + x[j] - 48;
            } else {
                mantissa = (mantissa << 1) + x[j] - 48;
            }
        }//printf("%d %d %d\n", sign, exponent, mantissa);
        long long temp = (sign << 63) + (exponent << 52) + mantissa;
        double* ptr = (double*)&temp;//printf("%d\n", temp);

        printf("%lf\n", *ptr);
    }
}

void byUnionToFloatingPoint(void* uu, char* x, int type)
{
    printf("The number for the bit pattern equals to ");
    if(type == 1)
    {
        uF* u = (uF*)uu;
        int sign = 0, exponent = 0, mantissa = 0;
        for (int j = 0; j < 32; j++) {
            if (j == 0) {
                sign = x[0] - 48;
            } else if (j > 0 && j < 9) {
                exponent = (exponent << 1) + x[j] - 48;
            } else {
                mantissa = (mantissa << 1) + x[j] - 48;
            }
        }u->patternBase10 = (sign << 31) + (exponent << 23) + mantissa;

        printf("%f\n", u->value);
    }

    if(type == 2)
    {
        uD* u = (uD*)uu;
        long long sign = 0, exponent = 0, mantissa = 0;
        for (int j = 0; j < 64; j++) {
            if (j == 0) {
                sign = x[0] - 48;
            } else if (j > 0 && j < 12) {
                exponent = (exponent << 1) + x[j] - 48;
            } else {
                mantissa = (mantissa << 1) + x[j] - 48;
            }
        }u->patternBase10 = (sign << 63) + (exponent << 52) + mantissa;

        printf("%lf\n", u->value);
    }
}

void byBitFieldToFloatingPoint(void* uu, char* x, int type)
{
    printf("The number for the bit pattern equals to ");
    if(type == 1)
    {
        uFBF* u = (uFBF*)uu;
        u->s.sign = 0;u->s.exponent = 0;u->s.mantissa = 0;
        for (int j = 0; j < 32; j++) {
            if (j == 0) {
                u->s.sign = x[0] - 48;
            } else if (j > 0 && j < 9) {
                u->s.exponent = (u->s.exponent << 1) + x[j] - 48;
            } else {
                u->s.mantissa = (u->s.mantissa << 1) + x[j] - 48;
            }
        }

        printf("%f\n", u->f);
    }

    if(type == 2)
    {
        uDBF* u = (uDBF*)uu;
        u->s.sign = 0;u->s.exponent = 0;u->s.mantissa = 0;
        for (int j = 0; j < 64; j++) {
            if (j == 0) {
                u->s.sign = x[0] - 48;
            } else if (j > 0 && j < 12) {
                u->s.exponent = (u->s.exponent << 1) + x[j] - 48;
            } else {
                u->s.mantissa = (u->s.mantissa << 1) + x[j] - 48;
            }
        }

        printf("%lf\n", u->d);
    }
}
