
#include <stdio.h>

int hex_digit_value(char c);

int main(void)
{
    char s[9];                          // 最多 8 個字 + 1 個 '\0'

    printf("請輸入十六進位數字（最多 8 位）：");
    if (scanf("%8s", s) != 1) {         // 字串陣列不用加 &
        printf("讀取失敗！\n");
        return 1;
    }

    unsigned int value = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        int d = hex_digit_value(s[i]);
        if (d == -1) {
            printf("第 %d 個字元 '%c' 不合法！\n", i + 1, s[i]);
            return 1;
        }
        value = value * 16 + d;
    }

    printf("0x%s = %u\n", s, value);
    return 0;
}

int hex_digit_value(char c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    return -1;
}