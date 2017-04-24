#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void initials_of_name(string name);

int main(void)
{
    // Get a input from user
    string name = get_string();
    initials_of_name(name);
}

// Function to print initials of user's input
void initials_of_name(string name)
{
    // Print the first initial in Uppercase
    printf("%c", toupper(name[0]));
    
    // Look for other words, and if they exist; print their first initial in Uppercase
    for (int i = 0, n = strlen(name); i < n; i++)
    {
        if (name[i] == ' ' && name[i + 1] != '\0')
        {
            printf("%c", toupper(name[i + 1]));
        }
    }
    
    printf("\n");
}