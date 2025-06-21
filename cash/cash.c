#include <stdio.h>

int calculate_value(int cents, int coin_value);
int get_cents(void);

int main(void)
{
    int n = get_cents(); //This function gets the job done, but it can't handle other data types like strings

    int quarters = calculate_value(n, 25);
    n = n - (quarters * 25);

    int dimes = calculate_value(n, 10);
    n = n - (dimes * 10);

    int nickles = calculate_value(n, 5);
    n = n - (nickles * 5);

    int pennies = calculate_value(n, 1);
    n = n - (pennies * 1);

    int sum = quarters + dimes + nickles + pennies;

    printf("%d\n", sum);
}

int get_cents(void)
{
    int n;
    do
    {
        printf("Change Owed: ");
        scanf("%d", &n);
    }
    while (n < 0);
    return n;
}

int calculate_value(int cents, int coin_value)
{
    return cents / coin_value;
}
