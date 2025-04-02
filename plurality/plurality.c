#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int swap_counter = 1;
    candidate temp;

    while (swap_counter != 0)
    {
        swap_counter = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[i].votes < candidates[i + 1].votes)
            {
                temp = candidates[i];
                candidates[i] = candidates[i + 1];
                candidates[i + 1] = temp;
                swap_counter++;
            }
        }
    }
    for (int j = 1; j < candidate_count; j++)
    {
        if (candidates[j].votes == candidates[0].votes)
        {
            for (int k = 0; candidates[k].votes == candidates[0].votes; k++)
            {
                printf("%s\n", candidates[k].name);
            }
        }
        else
        {
            break;
        }
        return;
    }
    printf("%s", candidates[0].name);
    printf("\n");
    return;
}
