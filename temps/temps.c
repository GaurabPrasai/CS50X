// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
}
avg_temp;

avg_temp temps[NUM_CITIES];

void sort_cities(void);

int main(void)
{
    temps[0].city = "Tokyo";
    temps[0].temp = 79;

    temps[1].city = "Rio";
    temps[1].temp = 70;

    temps[2].city = "Berlin";
    temps[2].temp = 73;

    temps[3].city = "Nairobi";
    temps[3].temp = 70;

    temps[4].city = "Helsinki";
    temps[4].temp = 68;

    temps[5].city = "Oslo";
    temps[5].temp = 68;

    temps[6].city = "Moscow";
    temps[6].temp = 68;

    temps[7].city = "Denver";
    temps[7].temp = 88;

    temps[8].city = "Lisbon";
    temps[8].temp = 77;

    temps[9].city = "Stockholm";
    temps[9].temp = 68;

    sort_cities();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// TODO: Sort cities by temperature in descending order
void sort_cities(void)
{
    // Add your code here
    int swap_counter = 1;
    avg_temp nothing;

    while (swap_counter != 0)
    {
        swap_counter = 0;
        for (int i = 0; i < NUM_CITIES; i++)
        {
            if (temps[i].temp < temps[i + 1].temp)
            {
                nothing = temps[i];
                temps[i] = temps[i + 1];
                temps[i + 1] = nothing;
                swap_counter++;
            }
        }
    }
}
