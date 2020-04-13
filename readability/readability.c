#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");
    int scount = 0; // sentence count
    int lcount = 0; // letter count
    int wcount = 0; // word count
    int vchar = 0; // valid char [a-z, A-Z, -]
    for (int i = 0, n = strlen(text) + 1; i < n; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            lcount++;
            vchar = 1;
        }
        else
        {
            if (vchar == 1 && (text[i] == ' ' || text[i] == '\0'))
            {
                wcount++;
                vchar = 0;
            }
            if (text[i] == '.' || text[i] == '!' || text[i] == '?')
            {
                scount++;
            }
        }
    }
    float avglw = (float) lcount / (float) wcount * 100; // average number of letters per 100 words
    float avgsw = (float) scount / (float) wcount * 100; // average number of sentences per 100 words
    int cli = round(0.0588 * avglw - 0.296 * avgsw - 15.8); // Coleman-Liau index
    if (cli < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (cli >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", cli);
    }
}
