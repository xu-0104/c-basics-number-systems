/* 04_hex_digit.c：把十六進位「字元」轉成數值（期末作品零件 #2）
   原理：字元就是 ASCII 數字，'0'~'9'、'A'~'F'、'a'~'f' 各自連續
         '7' - '0' = 55 - 48 = 7
         'C' - 'A' + 10 = 67 - 65 + 10 = 12
   錯誤時回傳 -1（正確值一定是 0~15，-1 不可能是答案） */

#include <stdio.h>

int hex_digit_value(char c);

int main(void)
{
    // 數字
    printf("'0' -> %d\n", hex_digit_value('0'));
    printf("'7' -> %d\n", hex_digit_value('7'));
    printf("'9' -> %d\n", hex_digit_value('9'));
    // 大寫
    printf("'A' -> %d\n", hex_digit_value('A'));
    printf("'F' -> %d\n", hex_digit_value('F'));
    // 小寫
    printf("'a' -> %d\n", hex_digit_value('a'));
    printf("'f' -> %d\n", hex_digit_value('f'));
    // 錯誤輸入（邊界值：'@' 在 'A' 前一格，'G' 在 'F' 後一格）
    printf("'@' -> %d\n", hex_digit_value('@'));
    printf("'G' -> %d\n", hex_digit_value('G'));
    printf("'z' -> %d\n", hex_digit_value('z'));

    return 0;
}

int hex_digit_value(char c)
{
    if (c >= '0' && c <= '9') {         // 數字字元
        return c - '0';
    }
    if (c >= 'A' && c <= 'F') {         // 大寫 A~F
        return c - 'A' + 10;
    }
    if (c >= 'a' && c <= 'f') {         // 小寫 a~f
        return c - 'a' + 10;
    }
    return -1;                          // 都不是 → 錯誤
}