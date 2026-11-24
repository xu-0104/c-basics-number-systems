
#include <stdio.h>

int main(void)
{
    int a[5];
    int len = 5;

  
    for (int i = 0; i < len; i++) {
        printf("請輸入第 %d 個整數：", i + 1);
        if (scanf("%d", &a[i]) != 1) {
            printf("輸入錯誤，不是整數！\n");
            return 1;
        }
    }


    int sum = 0;
    int max = a[0];
    int min = a[0];
    for (int i = 0; i < len; i++) {
        sum += a[i];
        if (a[i] > max) {
            max = a[i];
        }
        if (a[i] < min) {
            min = a[i];
        }
    }
    printf("總和：%d\n", sum);
    printf("最大值：%d\n", max);
    printf("最小值：%d\n", min);

    
    printf("倒序：");
    for (int i = len - 1; i >= 0; i--) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}