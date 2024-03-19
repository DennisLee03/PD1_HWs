#include "hw8-2.h"

void modify(int* a,int val)
{
    ((val % 2) == 0) ? (*a = 1) : (*a = 0);
}

int query(int (*mp)[131][131][131],char a[4],char b[4])
{    
    return ((((*mp)[a[0]][a[1]][a[2]] + (*mp)[b[0]][b[1]][b[2]]) % 2) ? 1 : 0);
}