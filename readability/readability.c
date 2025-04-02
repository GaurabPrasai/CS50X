#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string word);
int count_sentences(string sentences);

int main(void)
{
    string text = get_string("Text: ");

    int letters = count_letters(text);
    // printf("letters: %i\n", letters);

    int words = count_words(text);
    // printf("Words: %i\n", words);

    int sentences = count_sentences(text);
    // printf("sentences: %i\n", sentences);

    float L = (float) letters / words * 100;
    float S = (float) sentences / words * 100;

    float output = 0.0588 * L - 0.296 * S - 15.8;
    int Final_output = round(output);
    // printf("output:%d\n",Final_output);

    if (Final_output < 1)
    {
        printf("Before Grade 1\n");
    }

    if (Final_output >= 16)
    {
        printf("Grade 16+\n");
    }

    if (Final_output > 1 && Final_output <= 15)
    {
        printf("Grade %d\n", Final_output);
    }
}

int count_letters(string text)
{
    int total_letter = 0;

    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (isalpha(text[i]))
        {
            total_letter++;
        }
    }
    return total_letter;
}

int count_words(string word)
{
    int spaces = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isspace(word[i]))
        {
            spaces++;
        }
    }
    return spaces += 1;
}

int count_sentences(string sentences)
{
    int half_punc = 0;

    for (int i = 0; sentences[i] != '\0'; i++)
    {
        if (sentences[i] == '.' || sentences[i] == '!' || sentences[i] == '?')
        {
            half_punc++;
        }
    }
    return half_punc;
}
