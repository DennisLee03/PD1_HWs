#include <stdio.h>
#include <stdlib.h>

int main() {
    int i, n;
    printf("请输入数组的大小： ");
    scanf("%d", &n);

    int *myArray = (int*)malloc(n * sizeof(int)); // 使用malloc动态分配数组

    if (myArray == NULL) {
        printf("内存分配失败\n");
        return 1;
    }

    printf("请输入 %d 个整数：\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &myArray[i]);
    }

    printf("您输入的数组是：\n");
    for (i = 0; i < n; i++) {
        printf("%d ", myArray[i]);
    }

    free(myArray); // 释放动态分配的内存

    return 0;
}