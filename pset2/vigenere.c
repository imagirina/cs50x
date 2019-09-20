#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int shift(char c); // It takes a single character as input and output an integer

int main(int argc, string argv[])
{
    if (argc != 2) // No words in command line
    {
        printf("Usage: ./caesar keyword\n");
        return 1;
    }           
    for (int i = 0, keylenght = strlen(argv[1]); i < keylenght; i++)
    {
        if (isdigit(argv[1][i]) > 0) //Argument is a numeric character or use isalpha
        {
            printf("Usage: ./caesar keyword\n");
            return 1;
        }                           
    }
    string plaintext = get_string("plaintext: "); 
    printf("ciphertext: ");            
    for (int i = 0, j = 0, plainlenght = strlen(plaintext); i < strlen(plaintext); i++)
    {
        // The ASCII value of A is 65. The ASCII value of a is 97.
        int key = shift(argv[1][j]);
        if (isupper(plaintext[i]) != 0)                               
        {
            printf("%c", (plaintext[i] - 'A' + key) % 26 + 'A');
//            printf("%c", argv[1][j]);
            j++;
        } 
        else if (islower(plaintext[i]) != 0)
        {
            printf("%c", (plaintext[i] - 'a' + key) % 26 + 'a');            
            j++;
        }
        else // If cha is not a letter
        {
            printf("%c", plaintext[i]);

        }                  
        if (j > strlen(argv[1]) - 1)
        {
            j = 0;
        }              
    }
    
    
    printf("\n");
    return 0;
}

int shift(char c)
{
    int key = (int) c; 
    if (islower(c) != 0) 
    {
        key = (key - 97) % 26;
    }
    if (isupper(c) != 0)
    {
        key = (key - 65) % 26;       
    }
    return key;
}

