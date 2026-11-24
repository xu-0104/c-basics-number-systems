/* baseconv.c：命令列進位轉換工具
   用法：baseconv <dec|hex|bin|oct> <數字>
   例：  baseconv hex C8   →  印出十進位、十六進位、八進位、二進位

   這是起始模板：照 notes/06-baseconv.md 的步驟，把每個 TODO 完成。
   測試：powershell -ExecutionPolicy Bypass -File tests\run_tests.ps1 */

#include <stdio.h>
#include <string.h>

#define MAX_VALUE 4294967295LL      // unsigned int 最大值 = 0xFFFFFFFF

int digit_value(char c);
long long parse_number(const char s[], int base);
void print_binary_grouped(unsigned int n);
void print_usage(void);

int main(int argc, char *argv[])
{
    // TODO 步驟 1：參數數量不對（argc != 3）→ 印用法，return 1

    // TODO 步驟 2：用 strcmp 判斷 argv[1] 是 dec / hex / bin / oct，決定 base
    //              都不是 → 印錯誤訊息和用法，return 1
    (void)argc;   // 寫完步驟 1、2 後刪掉這兩行（只是讓編譯器暫時不警告）
    (void)argv;

    // TODO 步驟 3：呼叫 parse_number(argv[2], base)，結果 < 0 → return 2

    // TODO 步驟 4：印出十進位、十六進位、八進位、二進位

    return 0;
}

int digit_value(char c)
{
    // TODO 步驟 3：從第 4 課的 hex_digit_value 改過來
    (void)c;
    return -1;
}

long long parse_number(const char s[], int base)
{
    // TODO 步驟 3：value = value * base + d，並檢查非法字元和溢位
    (void)s;
    (void)base;
    return -1;
}

void print_binary_grouped(unsigned int n)
{
    // TODO 步驟 4：從第 5 課的 print_binary_any 改過來，每 4 bit 空一格
    (void)n;
}

void print_usage(void)
{
    printf("用法：baseconv <dec|hex|bin|oct> <數字>\n");
    printf("例：  baseconv dec 200\n");
    printf("      baseconv hex C8\n");
    printf("      baseconv bin 11001000\n");
}
