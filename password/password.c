// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and "
               "symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool has_upper = false, has_lower = false, has_num = false, has_symbol = false;

    for (int i = 0, n = strlen(password); i < n; i++)
    {
        if (isupper(password[i]))
        {
            has_upper = true;
        }
        if (islower(password[i]))
        {
            has_lower = true;
        }
        if (isdigit(password[i]))
        {
            has_num = true;
        }
        if (!isalnum(password[i]) && !isspace(password[i]))
        {
            has_symbol = true;
        }
    }

    if (has_upper && has_lower && has_num && has_symbol)
    {
        return true;
    }
    return false;
}
