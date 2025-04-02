#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Enter the number:\n");

    // temporary variables
    long temp = number;
    long originalNumber = number;

    bool isValid = true;

    // Calculate the checksum
    int i = 0;
    int checksum = 0;

    while (number != 0)
    {
        int digit = number % 10; // Get the rightmost digit

        if (i % 2 != 0) // Get the odd digits
        {

            digit = digit * 2;

            if (digit > 9)
            {
                digit -= 9;
            }
            checksum += digit;
        }

        if (i % 2 == 0) // Get the even digits
        {
            checksum += digit;
        }

        number /= 10; // Remove the rightmost digit
        i++;
    }

    if (checksum % 10 != 0)
    {
        isValid = false;
        printf("INVALID\n");
    }

    // printf("sum:%i\n", checksum);

    // check the card length and starting digit
    long count = 0;
    do
    {
        temp /= 10;
        count++;
    }
    while (temp != 0);
    // printf("card length:%li\n", count);

    // Find first two digits
    long firstTwoDigits = originalNumber;

    while (firstTwoDigits >= 100)
    {
        firstTwoDigits /= 10;
    }
    // printf("2 digits are:%li\n", firstTwoDigits);

    if (isValid)
    {
        if (count == 15 && (firstTwoDigits == 34 || firstTwoDigits == 37))
        {
            printf("AMEX\n");
        }
        else if (count == 16 && (firstTwoDigits >= 51 && firstTwoDigits <= 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((count == 13 || count == 16) && (firstTwoDigits >= 40 && firstTwoDigits <= 49))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}