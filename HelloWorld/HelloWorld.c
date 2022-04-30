#include <stdio.h>

int main(void)
{
    int a = 1;
    int *ptr = &a;
    printf("%d\n", a);
    // printf("%p\n", &a);
    printf("%d\n", *ptr); // 1

    // printf("%p\n", &ptr);
    printf("%p\n", &a);
    return 0;
}