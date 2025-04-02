// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

void myFunction(char argv[]);

void myFunction(char argv[])
{
    for (int i = 0; argv[i] != '\0'; i++)
    {
        char currentChar = argv[i];
        switch (currentChar)
        {
            case 'a':
                printf("6");
                break;
            case 'e':
                printf("3");
                break;
            case 'i':
                printf("1");
                break;
            case 'o':
                printf("0");
                break;
            default:
                printf("%c", currentChar);
                break;
        }
    }
}

int main(int argc, char *argv[])
{
    // program for taking the command line arguments
    if (argc != 2)
    {
        printf("Usage: %s word\n", argv[0]);
        return 1;
    }
    else
    {
        myFunction(argv[1]);
        printf("\n");
    }
}
