#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size

    int startPop;
    do
    {
        startPop = get_int("Start Size:\n");
    }
    while (startPop < 9);

    // TODO: Prompt for end size

    int endPop;
    do
    {
        endPop = get_int("End Size:\n");
    }
    while (endPop < startPop);

    // TODO: Calculate number of years until we reach threshold

    int year = 0;
    while (startPop < endPop)
    {
        startPop = startPop + (startPop / 3) - (startPop / 4);
        year++;
    }

    // TODO: Print number of years

    printf("Years: %i", year);
    printf("\n");
}
