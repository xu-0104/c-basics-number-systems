#include <stdio.h>

void print_binary_any(int n);

int main(void)
{
    int tests[] = {0, 1, 13, 200, 255, 256, 1024, 2147483647};
    int len = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < len; i++) {
        printf("%10d -> ", tests[i]);
        print_binary_any(tests[i]);
        printf("\n");
    }
    return 0;
}

void print_binary_any(int n)
{
    if (n == 0) {               // 特例：while 迴圈一次都不會跑
        printf("0");
        return;
    }

    int bits[32];               // int 最多 32 bit，不會超出範圍
    int count = 0;

    while (n > 0) {
        bits[count] = n % 2;    // 存餘數
        n = n / 2;
        count++;
    }

    for (int i = count - 1; i >= 0; i--) {   // 倒著印
        printf("%d", bits[i]);
    }
}