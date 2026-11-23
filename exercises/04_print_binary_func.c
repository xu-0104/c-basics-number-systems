
#include <stdio.h>

void print_binary(int n);

int main(void){

    for (int i = 0; i <= 15; i++) {
    printf("%2d = ", i);      
    print_binary(i);            
    printf(" = 0x%X\n", i);     
    }

    return 0;
}


void print_binary(int n)
{
    for (int w = 128; w >= 1; w /= 2) {
        if (n >= w) {
            printf("1");
            n -= w;
        } else {
            printf("0");
        }
        if (w == 16) {
            printf(" ");
        }
    }
}