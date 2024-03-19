#include "hw8-1.h"
#include <stdlib.h>

void init(int*** mp)
{
    for(int i = 0; i < 130 ; i++){
        mp[i] = (int**)malloc( 130 * sizeof(int*) );
        for(int j = 0; j < 130; j++){
            mp[i][j] = (int*)malloc( 130 * sizeof(int) );
            for(int k = 0; k < 130; k++){
                mp[i][j][k] = 1;
            }
        }
    }
}

void modify(int* a,int val)
{
    *a = val;
}

int query(int**** mp,char a[4],char b[4])
{
    int temp = abs((*mp)[a[0]][a[1]][a[2]] + (*mp)[b[0]][b[1]][b[2]]);
    return ((temp % 2) ? 1 : 0);
}
