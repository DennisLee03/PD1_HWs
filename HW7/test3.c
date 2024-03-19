/*作業的DFS練習與推論*/

#include <stdio.h>
#include <stdlib.h>

int target_num, target_sum;
int choose[3] = {0};//0表示沒有選
int the_chosen[3] = {0};
int File[3] = {6, 4, 1};
int count = 0;
int min_difference = 1000000000;

void solve(int idx, int now_sum);

int main() {

    scanf("%d %d", &target_num, &target_sum);

    solve(0, 0);

    printf("%d\n", min_difference);

    for(int i = 0; i < 3; i++) {
        if(the_chosen[i]) {
            printf("%d", File[i]);
            if(i != 2) printf("_");
        }
        if(i == 2) printf("~\n");
    }

    return 0;
}

void solve(int idx, int now_sum) {

    if(count >= target_num) {

        int buffer = abs(target_sum - now_sum);

        if(buffer < min_difference) {
            min_difference = buffer;

            for(int i = 0; i < 3; i++) {
                the_chosen[i] = choose[i];
            }
        }
        return;
    }
    
    if(idx == 3) return;

    choose[idx] = 1;
    count += 1;
    solve(idx + 1, now_sum + File[idx]);
    
    choose[idx] = 0;
    count -= 1;
    solve(idx + 1, now_sum);
}