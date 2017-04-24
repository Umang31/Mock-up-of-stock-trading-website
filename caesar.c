#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void ciphertext(string plaintext, int key);

// Accept command-line argument from user
int main(int argc, string argv[])
{
    // Validate command-line input from user
    if(argc != 2)
    {
        printf("Missing command-line argument or more than one command line argument entered\n");
        
        // Print return value for error
        return 1;
    }
    
    // Convert key to integer
    int key = atoi(argv[1]);
    
    // Get plaintext from user
    printf("plaintext: ");
    string plaintext = get_string();
    
    // Print the ciphertext
    printf("ciphertext: ");
    ciphertext(plaintext, key);
    
    // Print return value
    return 0;
}

// Function to convert plaintext to ciphertext
void ciphertext(string plaintext, int key)
{
    // Convert plaintext to individual character
    for(int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // Check if the character is in Uppercase
        if(isupper(plaintext[i]))
        {
            // Convert and print plaintext character to ciphertext character
            printf("%c", ((plaintext[i] - 65 + key) % 26) + 65);
        }
        
        // Check if the character is in Lowercase
        else if(islower(plaintext[i]))
        {
            // Convert and print plaintext character to ciphertext character
            printf("%c", ((plaintext[i] - 97 + key) % 26) + 97);
        }
        
        // Check if any other value
        else
        {
            // Print without any conversion
            printf("%c", plaintext[i]);   
        }
    }
    
    // Print newline after printing ciphertext
    printf("\n");
}