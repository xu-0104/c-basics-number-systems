/* 04_fibonacci.c：費氏數列，迴圈版 vs 遞迴版
   F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2)
   結論：遞迴版好寫但重複計算，O(2^n)；迴圈版只記前兩個數，O(n) */

#include <stdio.h>
#include <time.h>

int fib_loop(int n);
int fib_rec(int n);

long long calls = 0;    // 全域變數：計算 fib_rec 被呼叫幾次

int main(void)
{
   
    printf(" n | 迴圈版 | 遞迴版\n");
    for (int i = 0; i <= 20; i++) {
        printf("%2d | %6d | %6d\n", i, fib_loop(i), fib_rec(i));
    }

  
    calls = 0;
    int r = fib_rec(30);
    printf("\nfib_rec(30) = %d，被呼叫了 %lld 次\n", r, calls);

    // 3. 比較 n = 40 的速度
    clock_t start = clock();
    r = fib_rec(40);
    double sec = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("fib_rec(40)  = %d，花了 %.3f 秒\n", r, sec);

    start = clock();
    r = fib_loop(40);
    sec = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("fib_loop(40) = %d，花了 %.3f 秒\n", r, sec);

    return 0;
}


int fib_loop(int n)
{
    if (n < 2) {
        return n;
    }
    int a = 0, b = 1;           // a = F(i-2)，b = F(i-1)
    for (int i = 2; i <= n; i++) {
        int c = a + b;     
        a = b;             
        b = c;
    }
    return b;
}


int fib_rec(int n)
{
    calls++;
    if (n < 2) {                
        return n;
    }
    return fib_rec(n - 1) + fib_rec(n - 2);
}