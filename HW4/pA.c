#include <stdio.h>

int main()
{
    int days,starting_day;
    printf("Enter number of days in month: \n");
    scanf("%d",&days);
    printf("Enter starting day of the week (1=Sun, 7=Sat): \n");
    scanf("%d",&starting_day);

    for(int i = 1;i < starting_day;i++) printf("   ");
    for(int i = 1;i < days + 1;i++){
        printf("%2d", i);
        if(i != days && ((i + starting_day - 1) % 7) != 0) printf(" ");
        if(((i + starting_day - 1) % 7) == 0) printf("\n");
        //if(i == days) printf("\n");
    }

    return 0;
}