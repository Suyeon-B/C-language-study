#include <stdio.h>

int main_loop(void)
{
    // for (int i = 0; i < 10; i++)
    // {
    //     printf("Hello World\n");
    // }

    // int i = 0;
    // while (i < 10)
    // {
    //     printf("Hello World\n");
    //     i++;
    // }

    /*
     *
     **
     ***
     ****
     *****
     */
    // for (int i = 1; i <= 5; i++)
    // {
    //     for (int j = 1; j <= i; j++)
    //     {
    //         printf("*");
    //     }
    //     printf("\n");
    // }

    /*
     *
     **
     ***
     ****
     *****
     */
    // for (int i = 1; i <= 5; i++)
    // {
    //     for (int j = 1; j <= 5 - i; j++)
    //     {
    //         printf(" ");
    //     }
    //     for (int j = 1; j <= i; j++)
    //     {
    //         printf("*");
    //     }
    //     printf("\n");
    // }

    // 피라미드를 쌓아라 - 프로젝트
    printf("몇 층까지 쌓겠느냐? ");
    int floor;
    scanf("%d", &floor);

    for (int i = 0; i <= floor; i++)
    {
        for (int j = 0; j <= floor - i; j++)
        {
            printf(" ");
        }
        for (int k = 0; k < i * 2 + 1; k++)
        {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}