/* 02_print_bases.c：輸入一個整數，印出十進位、十六進位、八進位
   觀念：數字在記憶體裡只有一份，%d / %X / %o 只是「印出來的樣子」不同
   測試：200 → 200、0xC8、0310 */

#include <stdio.h>

int main(void){
    int num;

    printf("請輸入一個整數:");
    if (scanf("%d", &num) != 1) {
        printf("輸入錯誤，不是整數！\n");
        return 1;
    }
    printf("十進位:%d\n", num);
    printf("十六進位:0x%X\n", num);
    printf("八進位:0%o\n", num);

    return 0;
}
