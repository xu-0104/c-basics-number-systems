/* 03_diamond.c：輸入 n，印出菱形（上半部 n 行、下半部 n-1 行）
   規律：第 i 行 → 空白 n-i 個、星星 2*i-1 個
   教訓：沒檢查 scanf 時輸入 abc，n 是垃圾值（實測約 20 億），
         程式會停不下來，印出好幾 GB 的空白 → 一定要檢查回傳值 */

#include <stdio.h>

int main(void){
   int n;
   printf("請輸入 n (1~50): ");
   if (scanf("%d", &n) != 1) {
      printf("輸入錯誤，不是整數！\n");
      return 1;
   }
   if (n < 1 || n > 50) {
      printf("超出範圍！只能輸入 1~50\n");
      return 1;
   }

   //上半部
   for(int i=1;i<=n;i++){
      for(int j=0;j<n-i;j++)
         printf(" ");
      for(int j=0;j<2*i-1;j++)
         printf("*");
      printf("\n");
   }

   //下半部
   for(int i=n-1;i>=1;i--){
      for(int j=0;j<n-i;j++)
         printf(" ");
      for(int j=0;j<2*i-1;j++)
         printf("*");
      printf("\n");
   }
   return 0;
}
