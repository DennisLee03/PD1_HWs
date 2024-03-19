#include <stdio.h>
#include <stdlib.h>
#define MaxCap 20//硬碟的最大容量

//定義檔案的型態(只是為了讓我容易讀)，原本用int F[20][2]，但我會忘記0、1分別代表甚麼
struct node {
    int name;
    int size;
};
typedef struct node N;

struct node File[MaxCap + 1];
int now_used[MaxCap + 1] = {0};//挑選過程中，用來暫時儲存哪幾號使用過
int the_chosen[MaxCap + 1] = {0};//選中哪幾號刪除
int cap = 0;//已佔用個數
int target_num, target_sum;//輸入的刪除個數、總和大小目標值
int min_difference;//最小差距
int count;//計算是否選到target_num的值

void Afile();
void Qfile();
void solve(int idx, int sum);
void delete();
void list();

int main() 
{
    for(int i = 0; i < (MaxCap + 1); i++) //-1表示空的空間
    {
        File[i].name = -1;
        File[i].size = -1;
    }

    int op;
    printf("Options: ");
    while(scanf("%d", &op))
    {
        if(op == 0) list();
        if(op == 1) Afile();//新增
        if(op == 2) Qfile();//檢查存在與否
        if(op == 3) return 0;//結束

        printf("Options: ");
    }
}

void Afile() 
{
    int name, size;
    printf("Please input file name and file size: "); 
    scanf("%d %d", &name, &size);

    cap += 1;
    File[cap - 1].name = name;
    File[cap - 1].size = size;

    if(cap > MaxCap) delete();
}

void Qfile() 
{
    int name;
    printf("Please input the file name: ");
    scanf("%d", &name);

    for(int i = 0;i < (MaxCap + 1);i++) 
    {
        if(File[i].name == name) 
        {
            printf("YES\n");
            return;//找到一筆符合輸出Yes，並且回去main()
        }
    }
    printf("NO\n");//沒有任何一筆資料符合，則輸出No
}

void solve(int idx, int now_sum) 
{
    if(count >= target_num) //選擇數量達target_num，進行計算與儲存
    {
        int buffer = abs(target_sum - now_sum);

        if(buffer < min_difference) 
        {
            min_difference = buffer;//記錄下更好的解
            for(int i = 0; i < (MaxCap + 1); i++) the_chosen[i] = now_used[i];//記錄下選擇的序號
        }

        return;//修改完差值回上一層繼續搜尋更優的解
    }
    
    if(idx == (MaxCap + 1)) return;//超出範圍回前一層函數

    now_used[idx] = 1;
    count += 1;
    solve(idx + 1, now_sum + File[idx].size);//選擇此檔案
    
    now_used[idx] = 0;
    count -= 1;
    solve(idx + 1, now_sum);//不選此檔案
}

void list()
{
    for(int i = 0; i < MaxCap + 1; i++)
        printf("[%d]_Name[%d]_Size[%d]\n", i, File[i].name, File[i].size);
}

void delete()
{
    count = 0; min_difference = 1000000000;//刪除前先初始化

    printf("Hard drive exceeds its capacity, please enter the number of files to be deleted: ");
    scanf("%d %d", &target_num, &target_sum);//num<= 21; sum <= 1000000000
        
    solve(0, 0);//挑出來的序號儲存在the_chosen陣列中

    int j = 0, k = 0;
    N *temp = (N *)malloc(sizeof(N) * (MaxCap + 1 - target_num));//3
    while(j < (MaxCap + 1 - target_num))
    {
        /*從最高位往下找未被刪除的檔案，暫時儲存在temp中*/
        if(the_chosen[MaxCap - k] == 0)
        {
            temp[j].name = File[MaxCap - k].name;
            temp[j].size = File[MaxCap - k].size;
            j += 1;
        }
        k += 1;
    }

    j = 0; k = 0;
    for(int i = 0; i < (MaxCap + 1); i++) 
    {
        /*將要被刪的檔案的名稱輸出*/
        if(the_chosen[i]) 
        {
            printf("%d", File[i].name);//輸出檔案名
            if(k < (target_num - 1))
            {
                printf(" ");
                k += 1;
            }
            cap -= 1;//下降占用量
            the_chosen[i] = 0;//重置序號
        }
        /*將剩餘檔案從序號0開始存放*/
        if(i < (MaxCap - target_num + 1)) 
        {
            File[i].name = temp[j].name;
            File[i].size = temp[j].size;
            j += 1;
        }
        /*其餘空間設為未占用(-1)*/
        else 
        {
            File[i].name = -1;
            File[i].size = -1;
        }
    }printf("\n");
}