---
marp: true
theme: gaia
paginate: true
---
##  *HW11作業描述* 
*   **思維與過程: 2 ~ 40**
*   **執行的結果: 41**
*   **three figures: 42 ~ 45**
---
######  ***思維與過程***
*   先定義structure的內容
```clike
typedef struct prefix{//定義節點的內容
    unsigned int ip;
    unsigned char len;
    struct prefix *next;
} sPrefix;
```
---
######  ***思維與過程***
*   根據作業說明寫好函數的定義，順便寫上中文註解
*   文本需要透過main傳入，所以需要文本的函數都加上**char \*txt**參數
*   其他參數根據我的需求寫入
```clike
void input(char *txt, sPrefix routingTable[]);
//從routing_table讀IPv4的數據存入sPrefix型態的array中 =>(a)
//計算讀了幾筆IP =>(b)

void length_distribution(sPrefix routingTable[]);
//計算sPrefix型態的陣列中，length = 0、1、2.....32的IP各幾筆 => (c)

```
---
######  ***思維與過程***
```clike
void segment(sPrefix ***headArr, sPrefix *routingTable, sPrefix *special, int d);
//傳入參數，去做分組。length < d都進入"the special group"，做為一個組別
//length >= d為可以進行IP分組的條件 => (d)(e)
//可以分組的IP再按照前d個bit相同分為同一組
//輸出每個group組員(元素)的數量 => (f)
//每個group組成各自的linked list => (g)

void prefix_insert(char *txt, sPrefix ***headArr, int d);
//從inserted_prefixes檔案中，逐一插入其中的prefix進入各組linked list中 => (h)
//要注意此IP是否原本就存在，存在就不要再insert一次了

void prefix_delete(char *txt, sPrefix ***headArr, int d);
//根據deleted_prefixes的prefixes去刪除linked lists中的prefixes => (i)

void search(char *txt, sPrefix **headArr, int d);
//根據trace_file中的IP去尋找linked lists中是否存在此IP => (j)

```
---
######  ***思維與過程***
*   接著一次實作一個function，並執行幾次
*   按照作業說明的順序去實作
*   首先實作**input(...)**
    1.  透過字串暫存每一行的prefix
    2.  格式化掃描字串暫存在bits陣列，len中
    3.  把bits(透過位移)、len以unsigned number存入routingTable陣列
    4.  順便計算儲存次數
---
######  ***思維與過程***
```clike
//實作input(...)
void input(char *txt, sPrefix routingTable[])
{
    char line[20];
    unsigned int bits[4];
    unsigned char len;
    FILE *file = fopen(txt, "r");

    if (file == NULL) {
        perror("開啟input檔案失敗");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while(fgets(line, sizeof(line), file) != NULL) 
    {
        sscanf(line, "%u.%u.%u.%u/%hhu", bits, bits+1, bits+2, bits+3, &len);
        routingTable[i].ip = (*bits << 24) + (*(bits+1) << 16) + (*(bits+2) << 8) + (*(bits+3));
        routingTable[i].len = len;
        i++;
    }
    printf("The total number of prefixes in the input file is : %d.\n", i);
}
```
---
######  ***思維與過程***
*   實作**length_distribution(...)**
    1.  把input後的rountingTable陣列作為參數傳入
    2.  使用迴圈歷遍整個陣列，透過另一陣列去計數
    3.  length陣列就是透過.len去定位哪個元素要加1
```clike
//實作length_distribution(...)
void length_distribution(sPrefix routingTable[])
{
    int length[33] = {0};

    int i = 0;
    while(routingTable[i].ip != 0) length[routingTable[i++].len] += 1;

    for(i = 0; i < 33; i++) printf("The number of prefixes with prefix length %d = %d.\n", i, length[i]);
}
```
---
######  ***思維與過程***
*   實作**segment(...)**
    1.  這邊使用到了headArr去作為各個group的head
    2.  buffer用來計算此IP是group幾
    3.  透過d值去取得headArr的大小
    4.  使用了一個global array去計算list裡有幾個成員
    5.  透過while迴圈去產生linked lists
    6.  length < d則存入special陣列
    7.  其中**link(...)** 用來形成linked list
---
######  ***思維與過程***
```clike
//實作segment(...)
void segment(sPrefix ***headArr, sPrefix *routingTable, sPrefix *special, int d)
{
    unsigned int size = 1 << d;
    *headArr = (sPrefix**)malloc(sizeof(sPrefix*) * size);

    for(int k = 0; k < size; k++) numOfGroupMembers[k] = 0;

    int i = 0;
    int j = 0;
    while(routingTable[i].ip != 0)//linking
    {
        if(routingTable[i].len >= d)
        {
            int buffer = (routingTable[i].ip >> (32 - d));
            sPrefix *temp = (*headArr)[buffer];
            numOfGroupMembers[buffer] += 1;
            link(&((*headArr)[buffer]), routingTable[i].ip, routingTable[i].len);
        } else {
            special[j++].ip = routingTable[i].ip;
        } i++;
    }
}
```
---
######  ***思維與過程***
*   **link(...)**
    1.  常規作法，只是資料欄是兩個，一個IP、一個length
    2.  分割出這個函數也方便之後insert使用
```clike
void link(sPrefix** head, unsigned int newIp, unsigned char newLen)
{
    sPrefix *temp;
    temp = (sPrefix*)malloc(sizeof(sPrefix));
    temp->ip = newIp;
    temp->len = newLen;
    temp->next = *head;
    *head = temp;
}
```
---
######  ***思維與過程***
*   實作**prefix_insert(...)**
    *   拆成三個部分(因為marp會吃掉我的一些內容)
        1.  使用的變數與參數
        2.  暫存陣列
        3.  能不能進入其歸屬的list
```clike
void prefix_insert(char *txt, sPrefix ***headArr, int d)
{
    //使用的變數與參數
    //暫存陣列
    //能不能進入其歸屬的list
}
```
---
######  ***思維與過程***
*   實作**prefix_insert(...)**
    *   使用的變數與參數
        1.  如同input(...)用幾個變數去暫時儲存資訊
        2.  一個暫時讀入全部資訊的陣列insertArr
        3.  FILE_SIZE是一個macro，是我隨便定義的一個大數字
```clike
    unsigned int size = 1 << d;
    char line[20];
    unsigned int bits[4];
    unsigned char len;
    sPrefix insertArr[FILE_SIZE] = {0};
    FILE *file = fopen(txt, "r");
```
---
######  ***思維與過程***
*   實作**prefix_insert(...)**
    *   暫存陣列
        1.  透過字串暫存每一行的prefix
        2.  格式化掃描字串暫存在bits陣列，len中
        3.  把bits(透過位移)、len以unsigned number存入insertArr
        4.  沒有length的prefix在按照規則賦值
        5.  然後幫insertArr由小到大排序
        (我不確定到底要不要in the increasing order)
---
######  ***思維與過程***
```clike
    while(fgets(line, sizeof(line), file) != NULL) //讀入暫時使用的陣列中
    {
        len = 0;
        sscanf(line, "%u.%u.%u.%u/%hhu", bits, bits+1, bits+2, bits+3, &len);

        insertArr[i].ip = (*bits << 24) + (*(bits+1) << 16) + (*(bits+2) << 8) + (*(bits+3));
        if(len == 0)
        {
            len += 8;
            if(*(bits+1) != 0) {
                len += 8;
                if(*(bits+2) != 0) {
                    len += 8;
                    if(*(bits+3) != 0) {
                        len += 8;
                    }
                }
            }
        } insertArr[i].len = len;
        i++;
    } qSort(insertArr, 0, i - 1);//由小到大排列insertArr的元素
```
---
######  ***思維與過程***
*   **qSort(...)**
    *   常規作法，只是這次是數據是IP變成32bit的unsigned number去sort
*   **swap(...)**
    *   在qSort中使用到，用來交換數據，只是這裡交換兩個資料欄位
---
######  ***思維與過程***
```clike
void qSort(sPrefix *arr, int left, int right) 
{
    if (left >= right) return;

    int l = left + 1;
    int r = right;
    unsigned int pivot = arr[left].ip;

    while (1) {
        while (l <= right) {
            if (arr[l].ip > pivot) break;
            l++;
        }

        while (r > left) {
            if (arr[r].ip < pivot) break;
            r--;
        }

        if (l > r) break;

        swap(&arr[l], &arr[r]);
    }

    swap(&arr[left], &arr[r]);

    qSort(arr, left, r - 1);
    qSort(arr, r + 1, right);
}
```
---
######  ***思維與過程***
```clike
void swap(sPrefix* a, sPrefix* b)
{
    sPrefix temp;
    temp.ip = (*b).ip;
    temp.len = (*b).len;
    (*b).ip = (*a).ip;
    (*b).len = (*a).len;
    (*a).ip = temp.ip;
    (*a).len = temp.len;
}
```
---
######  ***思維與過程***
*   實作**prefix_insert(...)**
    *   能不能進入其歸屬的list
        1.  先檢查IP的length
        2.  算出group幾(buffer)
        3.  一個一個找串列中是否有重複
        4.  沒重複就進入串列，順便計算串列成員數量
---
######  ***思維與過程***
```clike
    i = 0;
    while(insertArr[i].ip != 0)//把array中的資料insert入list
    {
        if(insertArr[i].len >= d)//length依舊要符合segment時的條件
        {
            int buffer = (insertArr[i].ip >> (32 - d));//決定此元素屬於哪個group
            sPrefix *temp = (*headArr)[buffer];

            int condition = 1;
            while(temp != NULL)
            {
                if(temp->ip == insertArr[i].ip && temp->len == insertArr[i].len)//prefix相同 => 不insert
                {
                    condition = 0;
                    break;
                } temp = temp->next;
            } if(condition) {
                numOfGroupMembers[buffer] += 1;
                link(&((*headArr)[buffer]), insertArr[i].ip, insertArr[i].len);
            }
        } i++;
    }
```
---
######  ***思維與過程***
*   實作**prefix_delete(...)**
    *   拆成三個部分
        1.  使用的變數與參數
        2.  暫存陣列
        3.  能不能刪除
```clike
void prefix_delete(char *txt, sPrefix ***headArr, int d)
{
    //使用的變數與參數
    //暫存陣列
    //能不能刪除
}
```
---
######  ***思維與過程***
*   實作**prefix_delete(...)**
    *   使用的變數與參數
        1.  如同input(...)用幾個變數去暫時儲存資訊
        2.  一個暫時讀入全部資訊的陣列delArr
        3.  FILE_SIZE是一個macro，是我隨便定義的一個大數字
```clike
    unsigned int size = 1 << d;
    char line[20];
    unsigned int bits[4];
    unsigned char len;
    sPrefix delArr[FILE_SIZE] = {0};
    FILE *file = fopen(txt, "r");
```
---
######  ***思維與過程***
*   實作**prefix_delete(...)**
    *   暫存陣列
        1.  透過字串暫存每一行的prefix
        2.  格式化掃描字串暫存在bits陣列，len中
        3.  把bits(透過位移)、len以unsigned number存入delArr
        4.  沒有length的prefix在按照規則賦值
        5.  最後存入delArr中
---
######  ***思維與過程***
```clike
    int i = 0;
    while(fgets(line, sizeof(line), file) != NULL) 
    {
        len = 0;
        sscanf(line, "%u.%u.%u.%u/%hhu", bits, bits+1, bits+2, bits+3, &len);

        delArr[i].ip = (*bits << 24) + (*(bits+1) << 16) + (*(bits+2) << 8) + (*(bits+3));
        if(len == 0)
        {
            len += 8;
            if(*(bits+1) != 0) {
                len += 8;
                if(*(bits+2) != 0) {
                    len += 8;
                    if(*(bits+3) != 0) {
                        len += 8;
                    }
                }
            }
        } delArr[i].len = len;
        i++;
    }//讀取要刪除的文本
```
---
######  ***思維與過程***
*   實作**prefix_delete(...)**
    *    能不能刪除
        1.  先檢查IP的length
        2.  算出group幾(buffer)
        3.  一個一個找串列中是否有此prefix
        4.  有就刪除，沒有就不動作
        5.  其中**delete(...)** 用來刪除list裡的成員
---
######  ***思維與過程***
```clike
    i = 0;
    while(delArr[i].ip != 0)//deleting
    {
        if(delArr[i].len >= d)
        {
            int buffer = (delArr[i].ip >> (32 - d));
            sPrefix *temp = (*headArr)[buffer];
            int condition = 0;

            while(temp != NULL)
            {
                if(temp->ip == delArr[i].ip && temp->len == delArr[i].len)//prefix相同 => delete
                {
                    condition = 1;
                    break;
                }temp = temp->next;
            }

            if(condition) 
            {
                numOfGroupMembers[buffer] -= 1;
                delete(&((*headArr)[buffer]), delArr[i].ip, delArr[i].len);
            }
        } 
        i++;
    }
```
---
######  ***思維與過程***
*   **delete(...)**
    1.  常規作法，用兩個指標去current、prev去尋找要刪除的元素
    2.  最後free掉要刪除的資料
    3.  另外寫個函數讓程式碼較易讀   
---
######  ***思維與過程***
```clike
void delete(sPrefix** head, unsigned int delIp, unsigned char delLen)
{
    if(*head == NULL) return;

    sPrefix *prev = NULL, *current = *head;

    while(current != NULL)
    {
        if(current->ip == delIp && current->len == delLen) break;
        else
        {
            prev = current;
            current = current->next;
        }
    }

    if(current != NULL)
    {
        if(prev != NULL) prev->next = current->next;
        else *head = current->next;
    }

    free(current);
}
```
---
######  ***思維與過程***
*   實作**search(...)**
    *   拆成三個部分
        1.  使用的變數與參數
        2.  暫存陣列
        3.  瀏覽用函數
```clike
void search(char *txt, sPrefix **headArr, int d)
{
    //使用的變數與參數
    //暫存陣列
    //如何搜尋
}
```
---
######  ***思維與過程***
*   實作**search(...)**
    *   使用的變數與參數
        1.  如同input(...)用幾個變數去暫時儲存資訊
        2.  一個暫時讀入全部資訊的陣列searchArr
        3.  FILE_SIZE是一個macro，是我隨便定義的一個大數字
```clike
    unsigned int size = 1 << d;
    char line[20];
    unsigned int bits[4];
    sPrefix searchArr[FILE_SIZE] = {0};
    FILE *file = fopen(txt, "r");
```
---
######  ***思維與過程***
*   實作**search(...)**
    *   暫存陣列
        1.  透過字串暫存每一行的prefix
        2.  格式化掃描字串暫存在bits陣列，len中
        3.  把bits(透過位移)unsigned number存入searchArr
        4.  len不用處理，因為只是要查IP值而已
---
######  ***思維與過程***
```clike
    int i = 0;
    while(fgets(line, sizeof(line), file) != NULL) 
    {
        sscanf(line, "%u.%u.%u.%u", bits, bits+1, bits+2, bits+3);

        searchArr[i].ip = (*bits << 24) + (*(bits+1) << 16) + (*(bits+2) << 8) + (*(bits+3));

        i++;
    }
```
---
######  ***思維與過程***
*   實作**search(...)**
    *   如何搜尋
        1.  先算出IP屬於group幾(buffer)
        2.  透過surfTheList去尋找
        3.  有輸出successful，沒有輸出failed
        4.  其中**surfTheList(...)** 用來比對IP值並return 0或1
        5.  讓之後的selection能夠作選擇
---
######  ***思維與過程***
```clike
    i = 0;
    while(searchArr[i].ip != 0)
    {
        int buffer = (searchArr[i].ip >> (32 - d));
        sPrefix *temp = headArr[buffer];
        int condition;

        condition = surfTheList(headArr[buffer], searchArr[i].ip);

        if(condition)
            printf("successful\n");
        else
            printf("failed\n");
        i++;
    }
```
---
######  ***思維與過程***
*   **surfTheList(...)**
    1.  一個一個做比對
    2.  一旦找到就return 1，不再往下找
```clike
int surfTheList(sPrefix *head, unsigned int ipValue)
{
    while (head != NULL)
    {
        if(head->ip == ipValue) return 1;
        head = head->next;
    }
    return 0;
}
```
---
######  ***思維與過程***
*   **輸出groups**
    *   我寫了**outputGroups(...)** 來幫我輸出linked lists
    *   基本上就是按照補充說明output format去設計
    *   輸出group的二進制，自定義了**printBinary(...)**
    *   輸出list裡面的IP值，自定義了**printIpv4List(...)**
    *   最後輸出special group的成員
    *   輸出每個group的成員數目
---
######  ***思維與過程***
```clike
void outputGroups(sPrefix **headArr, sPrefix *special, int d)
{
    unsigned int size = 1 << d;
    int i = 0;
    for(i = 0; i < size; i++) 
    {
        printf("|  ");
        printBinary(i, d);
        printf("  |");
        if(headArr[i] != NULL) printf(" ---> ");
        else printf("\n");
        printIpv4List(headArr[i]);
    }

    i = 0;
    printf("--------special group--------\n");
    while(special[i].ip != 0)
    {
        unsigned int temp = special[i++].ip;
        printf("%u.%u.%u.%u\n", (temp >> 24), ((temp << 8) >> 24), ((temp << 16) >> 24), ((temp << 24) >> 24));
    }
    printf("-----------------------------\n");

    for(unsigned int j = 0; j < size; j++) printf("The number of prefixes in group %u = %d\n", j, numOfGroupMembers[j]);
}
```
---
######  ***思維與過程***
```clike
/*輸出這個list裡面的所有成員*/
void printIpv4List(sPrefix* head)
{
    if(head == NULL) return;
    while (head != NULL)
    {
        printf("| %u.%u.%u.%u |", (head->ip >> 24), ((head->ip << 8) >> 24), ((head->ip << 16) >> 24), ((head->ip << 24) >> 24));
        if(head->next != NULL) printf(" ---> ");
        head = head->next;
    }
    printf("\n");
}

/*輸出group幾的二進制*/
void printBinary(int num, int shift)
{
    if(shift == 0) return;

    printf("%d", (num >> shift - 1) & 1);
    printBinary(num, shift - 1);
}
```
---
######  ***思維與過程***
```clike
/*所有函數的prototype*/
void link(sPrefix** head, unsigned int newIp, unsigned char newLen);
void delete(sPrefix** head, unsigned int delIp, unsigned char delLen);
int surfTheList(sPrefix *head, unsigned int ipValue);
void printIpv4List(sPrefix* head);
void outputGroups(sPrefix **headArr, sPrefix *special, int d);
void qSort(sPrefix* arr, int left, int right);
void swap(sPrefix* a, sPrefix* b);
void printBinary(int num, int shift);
void input(char *txt, sPrefix routingTable[]);
void length_distribution(sPrefix routingTable[]);
void segment(sPrefix ***headArr, sPrefix *routingTable, sPrefix *special, int d);
void prefix_insert(char *txt, sPrefix ***headArr, int d);
void prefix_delete(char *txt, sPrefix ***headArr, int d);
void search(char *txt, sPrefix **headArr, int d);
```
---
######  ***思維與過程***
```clike
/*main的編排*/
int main(int argc, char *argv[])
{
    int d = atoi(argv[5]);
    sPrefix routingTable[FILE_SIZE];
    sPrefix special[FILE_SIZE];
    sPrefix **headArr;
    numOfGroupMembers = (unsigned int*)malloc(sizeof(unsigned int) * (1 << d));

    input(argv[1], routingTable);
    length_distribution(routingTable);
    segment(&headArr, routingTable, special, d);
    prefix_insert(argv[2], &headArr, d);
    prefix_delete(argv[3], &headArr, d);
    outputGroups(headArr, special, d);
    search(argv[4], headArr, d);

    return 0;
}
```
---
######  ***思維與過程***
*   我並沒有在每個開文本的函數裡寫fclose()，沒寫的函數如果我寫在最後一行還是會segmentation fault，我自己也不清楚為甚麼
---
######  ***執行的結果***
1.  輸出routing_table裡面的prefix個數
2.  輸出長度分布
3.  輸出linked lists以及special group
4.  輸出各個group的成員數量
5.  輸出trace_file每一行IP搜尋成果successful or failed
6.  程式正常結束
---
######  ***three figures***
*   如何使用clock.c
    1.  把rdtsc()複製到hw11.c中
    2.  用兩個變數begin、end去記錄開始的clock
    3.  end - begin即函數的clock數
    4.  然後再把數據append進入.csv檔中
    ```clike
    begin = rdtsc();
    /*prefix_inset()或prefix_delete()或search()*/
    end = rdtsc();
    Clock = end - begin;
    FILE *file = fopen("clock_data.csv", "a");
    fprintf(file, "%llu\n", Clock);
    ```
---
######  ***Insertion figure***
---
######  ***Deletion figure***
---
######  ***Search figure***
