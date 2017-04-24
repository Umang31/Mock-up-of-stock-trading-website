#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void ciphertext(string plaintext, string key, int key_length);

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
    else
    {
        for(int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            // Check if the command-line input is alphabetic or not
            if(!isalpha(argv[1][i]))
            {
                printf("Please input alphabetic characters only\n");
                
                // Print return value if command-line input is non-alphabetic
                return 1;
            }
        }
    }
    
    string key = argv[1];
    int key_length = strlen(key);
    
    // Get plaintext from user
    printf("plaintext: ");
    string plaintext = get_string();
    
    // Print the ciphertext
    printf("ciphertext: ");
    ciphertext(plaintext, key, key_length);
    
    // Print return value
    return 0;
}

// Function to convert plaintext to ciphertext
void ciphertext(string plaintext, string key, int key_length)
{
    // Convert plaintext to individual character
    for(int i = 0, j = 0, n = strlen(plaintext); i < n; i++)
    {
        // Wrap around key characters if key length is less than plaintext
        int letter_key = tolower(key[j % key_length]) - 97;
        
        // Check if the character is in Uppercase
        if(isupper(plaintext[i]))
        {
            // Convert and print plaintext character to ciphertext character
            printf("%c", ((plaintext[i] - 65 + letter_key) % 26) + 65);
            
            // Increment value of j so that the next character of plaintext uses next character value of key
            j++;
        }
        
        // Check if the character is in Lowercase
        else if(islower(plaintext[i]))
        {
            // Convert and print plaintext character to ciphertext character
            printf("%c", ((plaintext[i] - 97 + letter_key) % 26) + 97);
            
            // Increment value of j so that the next character of plaintext uses next character value of key
            j++;
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