/* 03_print_binary.c：輸入 0~255，印出 8 位元二進位，每 4 bit 空一格
   方法：第 1 課的「能減就減」——權重 128 → 1，n >= 權重就印 1 並減掉
   測試：200 → 1100 1000、211 → 1101 0011、100 → 0110 0100、
         233 → 1110 1001、0 → 0000 0000、255 → 1111 1111；
         256、-1、abc 都會印出錯誤訊息 */

#include <stdio.h>

int main(void){
    int n;
    printf("請輸入0~255的整數:");
    if (scanf("%d", &n) != 1) {
        printf("輸入錯誤，不是整數！\n");
        return 1;
    }

    if(n<0 || n>255){
        printf("超出範圍！只能輸入 0~255\n");
        return 1;
    }

    for(int w = 128;w>=1;w/=2){
        if(n>=w){
            printf("1");
            n -=w;
        }else{
            printf("0");
        }
        if (w == 16) {
            printf(" ");    // 前 4 bit 印完，空一格（剛好對應 1 個 hex 數字）
        }
    }
    printf("\n");

    return 0;
}
