#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    string input = get_string("Message: ");
    // int bit = 0;
    int store[8] = {0};
    int value;
    for (int i = 0; input[i] != '\0'; i++)
    {
        // converting character inside string into ASCII value

        int ascii_value = (int) input[i];
        // printf("Ascii: %d", ascii_value);

        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            store[j] = ascii_value % 2;
            ascii_value /= 2;
        }
        for (int m = BITS_IN_BYTE - 1; m >= 0; m--)
        {
            print_bulb(store[m]);
        }

        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
