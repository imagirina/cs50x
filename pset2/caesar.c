#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[]) // Words in command line
{
    if (argc != 2) // If there is no words in command-line or more than one argument
    {
        printf("Usage: ./caesar key\n");
        return 1;
    } 
    for (int i = 0, keylength = strlen(argv[1]); i < keylength; i++) // Try argv[i] != '\0'
    {
        if ((isdigit(argv[1][i]) == 0)) // Argument is not a numeric character ***isdigit() from <ctype.h>***
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    int key = atoi(argv[1]); // Convert string to an integer ***atoi() from <stdio.h>***
    string plaintext = get_string("plaintext: ");
    int plainlength = strlen(plaintext);
    // int ciphertext[plainlength]; // Initialization of the array
    printf("ciphertext: ");
    for (int i = 0; i < plainlength; i++)
    {
        int c = (int) plaintext[i]; // Explicit casting (explicitly casts one datatype to another)
        // We can skip isalpha() and use isupper() and islower() instead
        if (isupper(plaintext[i]) != 0) // ('Z' - 'A' + key) % 26                                
        {
            //ciphertext[i] = (char)((c + key)%26); 
            //printf("Char: %c, Ascii: %i, Cipher: %c\n", plaintext[i], c, ciphertext[i]); 
            printf("%c", (plaintext[i] - 'A' + key) % 26 + 'A');
            //printf("%c", ciphertext[i]);
        } 
        else if (islower(plaintext[i]) != 0) // ('z' - 'a' + key) % 26
        {
            //ciphertext[i] = (char)((c + key)%26); 
            //printf("Char: %c, Ascii: %i, Cipher: %c\n", plaintext[i], c, ciphertext[i]);     
            printf("%c", (plaintext[i] - 'a' + key) % 26 + 'a');            
            //printf("%c", ciphertext[i]);            
        }
        else 
        {
            printf("%c", plaintext[i]); // If char is not a letter just print it as is
        }               
    }
    printf("\n");
    return 0;               
}

/*
Plaintext - unincripted text
Ciphertext - encrypted text

Print the key at the command line
If key is absent or is not a number or has more than one argument print "Usage: ./caesar key" else


(Iterate over the provided argument to make sure all characters are digits)
Convert that command-line argument from a string to an int
prompt the message asking to print plaintext

Iterate over each character of the plaintext:
If it is an uppercase letter, rotate it, preserving case, then print out the rotated character
If it is a lowercase letter, rotate it, preserving case, then print out the rotated character
If it is neither, print out the character as is

Print a newline
*/