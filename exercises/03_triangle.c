/* 03_triangle.c：輸入行數 n，印出靠右的三角形
   規律：第 i 行 → 空白 n-i 個、星星 i 個
   測試：n=4 正確；abc、0、-1、51 都會印出錯誤訊息並結束 */

#include <stdio.h>

int main(void){
   int n;
   printf("請輸入行數 n (1~50): ");
   if (scanf("%d", &n) != 1) {
      printf("輸入錯誤，不是整數！\n");
      return 1;
   }
   if (n < 1 || n > 50) {
      printf("超出範圍！只能輸入 1~50\n");
      return 1;
   }

   for(int i=1;i<=n;i++){
      for(int j=n-i;j>0;j--){
         printf(" ");
      }
      for(int k=0;k<i;k++){
         printf("*");
      }
      printf("\n");
   }

   return 0;
}
