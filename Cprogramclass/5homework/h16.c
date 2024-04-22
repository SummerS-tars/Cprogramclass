#include <stdio.h>

void input(int **arr, int size) {
    printf("输入 %d 个数字:\n", size);
    for (int i = 0; i < size; i++) {
        arr[i] = (int*)malloc(sizeof(int));
        scanf("%d", arr[i]);
    }
}

void output(int **arr, int size) {
    printf("数组元素: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", *arr[i]);
    }
    printf("\n");
}

void sort(int **arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (*arr[j] > *arr[j + 1]) {
                int *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}