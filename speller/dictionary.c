// Implements a dictionary's functionality
#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
// const unsigned int N = 26;
const unsigned int N = 100000;

// Global variable for size function
int count;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    int index = hash(word);

    node *cursor = table[index];

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';

    unsigned long hash_value = 5381;
    int i = 0;

    while (word[i] != '\0')
    {
        char insensetive_word = toupper(word[i]);
        hash_value = (((hash_value * 33) + hash_value) + (insensetive_word - 'A')) % 100000;
        i++;
    }

    return hash_value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char word[LENGTH + 1];
    int index;
    count = 0;

    // Open the dictonary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Error opening file!");
        return false;
    }

    while (fscanf(file, "%s", word) != EOF)
    {

        // Create a new node and copy the word into it
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word);

        // Hash the word to get an index

        index = hash(word);

        // Insert the node into the hash table at the index

        n->next = table[index];
        table[index] = n;

        count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *cursor;
    node *temp;

    for (int i = 0; i < N; i++)
    {
        cursor = table[i];

        while (cursor != NULL)
        {
            temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
}
