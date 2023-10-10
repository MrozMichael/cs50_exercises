#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

int calculate_level(string);
int count_letters(string);
int count_words(string);
int count_sentences(string);

int main(void)
{
    string text = get_string("Text: ");
    int grade = calculate_level(text);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

int calculate_level(string text)
{
    float index = 0;
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    // printf("Letter count: %i, Word Count: %i, sent count: %i\n", letters, words, sentences);
    float hundred_words = words / 100.0;
    index = 0.0588 * (letters / hundred_words) - 0.296 * (sentences / hundred_words) - 15.8;

    return round(index);
}

int count_letters(string text)
{
    int letters = 0;
    int i = 0;
    while (text[i] != '\0')
    {
        // check ascii range
        if (isalpha(text[i]))
        {
            letters++;
        }
        i++;
    }
    return letters;
}

int count_words(string text)
{
    int words = 0;
    int i = 0;
    while (text[i] != '\0')
    {
        if (isspace(text[i]))
        {
            words++;
        }
        i++;
    }
    words++;
    return words;
}

int count_sentences(string text)
{
    int sentences = 0;
    int i = 0;
    while (text[i] != '\0')
    {
        char current = text[i];
        //as per instructions, this counts as a sentence break.
        if (current == 63 || current == 46 || current == 33)
        { // ? . ! ascii values
            sentences++;
        }
        i++;
    }
    return sentences;
}