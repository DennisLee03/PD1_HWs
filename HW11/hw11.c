#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define FILE_SIZE 100000

typedef struct prefix{//定義節點的內容
    unsigned int ip;
    unsigned char len;
    struct prefix *next;
} sPrefix;

unsigned int *numOfGroupMembers;

void link(sPrefix** head, unsigned int newIp, unsigned char newLen);
void delete(sPrefix** head, unsigned int delIp, unsigned char delLen);
int surfTheList(sPrefix *head, unsigned int ipValue);
void printIpv4List(sPrefix* head);
void outputGroups(sPrefix **headArr, sPrefix *special, int d);
void qSort(sPrefix* arr, int left, int right);
void swap(sPrefix* a, sPrefix* b);
void printBinary(int num, int shift);

void input(char *txt, sPrefix routingTable[]);
//從routing_table讀IPv4的數據存入sPrefix型態的array中 =>(a)
//計算讀了幾筆IP =>(b)

void length_distribution(sPrefix routingTable[]);
//計算sPrefix型態的陣列中，length = 0、1、2.....32的IP各幾筆 => (c)

void segment(sPrefix ***headArr, sPrefix *routingTable, sPrefix *special, int d);
//傳入參數，去做分組。length < d都進入"the special group"，做為一個組別；length >= d為可以進行網路分組的條件，假設d = 8，那麼length = 8、9、10、......、32都是可以進行分組的IP => (d)(e)
//可以分組的IP再按照前d個bit相同分為同一組，假設d = 8，前8個bit為0000000的組別進入group 0，為00000001進入group 1，......為11111111進入group 255(2^d - 1)
//輸出每個group組員(元素)的數量 => (f)
//每個group組成各自的linked list(g)

void prefix_insert(char *txt, sPrefix ***headArr, int d);
//從inserted_prefixes檔案中，逐一插入其中的prefix進入各組linked list中 => (h)
//要注意此IP是否原本就存在，存在就不要再insert一次了

void prefix_delete(char *txt, sPrefix ***headArr, int d);
//根據deleted_prefixes檔案中要刪除的prefixes去刪除linked lists中的prefixes => (i)

void search(char *txt, sPrefix **headArr, int d);
//根據trace_file中的IP去尋找linked lists中是否存在此IP然後report the search is successful or failed => (j)

unsigned long long int begin,end;

unsigned long long int rdtsc()//32-bit
{
	unsigned long long int x;
	__asm__ volatile ("rdtsc" : "=A" (x));
	return x;
}

unsigned long long int rdtsc_64bits()//64-bit
{
   unsigned long long int x;
   unsigned a, d;

   __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));

   return ((unsigned long long)a) | (((unsigned long long)d) << 32);;
}

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

    unsigned long long insertClock, deleteClock, searchClock;

    begin = rdtsc();
    prefix_insert(argv[2], &headArr, d);
    end = rdtsc();
    insertClock = end - begin;

    begin = rdtsc();
    prefix_delete(argv[3], &headArr, d);
    end = rdtsc();
    deleteClock = end - begin;

    outputGroups(headArr, special, d);

    begin = rdtsc();
    search(argv[4], headArr, d);
    end = rdtsc();
    searchClock = end - begin;

    FILE *file = fopen("clock_data.csv", "a");

    if (file == NULL) {
        fprintf(stderr, "excel打不開啦!!!!\n");
        return 1;
    }

    fprintf(file, "%llu,%llu,%llu\n", insertClock, deleteClock, searchClock);

    fclose(file);
    
    return 0;
}

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

void length_distribution(sPrefix routingTable[])
{
    int length[33] = {0};

    int i = 0;
    while(routingTable[i].ip != 0) length[routingTable[i++].len] += 1;

    for(i = 0; i < 33; i++) printf("The number of prefixes with prefix length %d = %d.\n", i, length[i]);
}

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

void prefix_insert(char *txt, sPrefix ***headArr, int d)
{
    unsigned int size = 1 << d;
    char line[20];
    unsigned int bits[4];
    unsigned char len;
    sPrefix insertArr[FILE_SIZE] = {0};

    FILE *file = fopen(txt, "r");

    if (file == NULL) {
        perror("開啟insert檔案失敗");
        exit(EXIT_FAILURE);
    }

    int i = 0;
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
    } qSort(insertArr, 0, i - 1);//由小到大排列insertArr的元素後再insert

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
            }

            if(condition) 
            {
                numOfGroupMembers[buffer] += 1;
                link(&((*headArr)[buffer]), insertArr[i].ip, insertArr[i].len);
            }
        } 
        i++;
    }
}

void prefix_delete(char *txt, sPrefix ***headArr, int d)
{
    unsigned int size = 1 << d;
    char line[20];
    unsigned int bits[4];
    unsigned char len;
    sPrefix delArr[FILE_SIZE] = {0};

    FILE *file = fopen(txt, "r");

    if (file == NULL) {
        perror("開啟delete檔案失敗");
        exit(EXIT_FAILURE);
    }

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
}

void search(char *txt, sPrefix **headArr, int d)
{
    unsigned int size = 1 << d;
    char line[20];
    unsigned int bits[4];
    sPrefix searchArr[FILE_SIZE] = {0};

    FILE *file = fopen(txt, "r");

    if (file == NULL) {
        perror("開啟search檔案失敗");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while(fgets(line, sizeof(line), file) != NULL) 
    {
        sscanf(line, "%u.%u.%u.%u", bits, bits+1, bits+2, bits+3);

        searchArr[i].ip = (*bits << 24) + (*(bits+1) << 16) + (*(bits+2) << 8) + (*(bits+3));

        i++;
    }

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
    fclose(file);
}

void link(sPrefix** head, unsigned int newIp, unsigned char newLen)
{
    sPrefix *temp;
    temp = (sPrefix*)malloc(sizeof(sPrefix));
    temp->ip = newIp;
    temp->len = newLen;
    temp->next = *head;
    *head = temp;
}

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

int surfTheList(sPrefix *head, unsigned int ipValue)
{
    while (head != NULL)
    {
        if(head->ip == ipValue) return 1;
        head = head->next;
    }

    return 0;
}

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

void printBinary(int num, int shift)
{
    if(shift == 0) return;

    printf("%d", (num >> shift - 1) & 1);
    printBinary(num, shift - 1);
}