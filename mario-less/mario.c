#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = printf("Height: \n");
        scanf("%d", &n);
    }
    while (n > 8 || n < 1);

    for (int i = n; i >= 1; i--)
    {

        for (int j = 1; j <= n; j++)
        {
            if (j < i)
            {
                printf(" ");
            }

            else
            {
                printf("#");
            }
        }

        printf("\n");
    }
}
