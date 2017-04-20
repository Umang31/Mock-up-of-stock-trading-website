#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        printf("Height: ");
        height = get_int();
    }
    while (height < 0 || height > 23);
    
    for (int i = 0; i < height; i++)
    {
        for (int spaces = (height - (i + 1)); spaces > 0; spaces--)
        {
            printf(" ");
        }
        
        for (int hashes = 0; hashes <= (i + 1) ; hashes++)
        {
            printf("#");
        }
        
        printf("\n");
    }
}