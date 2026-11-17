
#include <stdio.h>

int num;
int numdex;
int numhex;
int numoct;

int main(void){
    printf("請輸入一個整數:");
    scanf("%d",&num);
    printf("十進位:");
    printf("%d\n",num);
    printf("十六進位:0x");
    printf("%x\n",num);
    printf("八進位:");
    printf("%o\n",num);
}
