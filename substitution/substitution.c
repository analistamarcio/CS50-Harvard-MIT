#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        // checks if there is only one command line argument
        printf("Invalid or missing key.\nUsage: ./substitution key\n");
        return 1;
    }
    else
    {
        // checks if the key is 26 characters long
        if (strlen(argv[1]) != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else
        {
            for (int i = 0; i < 25; i++)
            {
                // checks if there is only valid characteres
                if ((argv[1][i] >= 'a' && argv[1][i] <= 'z') || (argv[1][i] >= 'A' && argv[1][i] <= 'Z'))
                {
                    int count = 0;
                    int c = tolower(argv[1][i]);
                    for (int j = i + 1; j < 26; j++)
                    {
                        // checks if there is repeated characters
                        if (c == tolower(argv[1][j]))
                        {
                            printf("Key must not contain repeated characteres.\n");
                            return 1;
                        }
                    }
                }
                else
                {
                    printf("Key must only contain alphabetic characters (A to Z).\n");
                    return 1;
                }
            }
        }
        string text = get_string("plaintext: ");
        printf("ciphertext: ");
        string lowerarr = "abcdefghijklmnopqrstuvwxyz";
        for (int i = 0, n = strlen(text); i < n; i++)
        {
            // go through each letter of the text to encrypt
            if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
            {
                for (int j = 0; j < 26; j++)
                {
                    // finds the position of the letter in the alphabet
                    if (tolower(text[i]) == lowerarr[j])
                    {
                        if (text[i] >= 'a')
                        {
                            printf("%c", tolower(argv[1][j]));
                        }
                        else
                        {
                            printf("%c", toupper(argv[1][j]));
                        }
                        break;
                    }
                }
            }
            else
            {
                printf("%c", text[i]);
            }
        }
        printf("\n");
    }
}
