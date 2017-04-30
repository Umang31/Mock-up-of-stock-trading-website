#include <cs50.h>       
#include <stdio.h>
#include <stdlib.h>

// Set constant for buffer size
#define BUFFER_SIZE 512

int main(int argc, char* argv[])
{
    // Ensure proper usage
    if(argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    
    // Open memory card file
    FILE* input = fopen(argv[1], "r");
    if (input == NULL)
    {
        fprintf(stderr, "Could not open file.\n");
        return 2;
    }
    
    // Create buffer
    unsigned char buffer[BUFFER_SIZE];
    
    // Filename counter
    int filecount = 0;
    
    FILE* picture = NULL; 
    
    // Check if we've found a jpeg, set it to false
    int jpg_found = 0;
    
    // Go through cardfile until there aren't any blocks left
    while (fread(buffer, BUFFER_SIZE, 1, input) == 1)
    {
        // Read first 4 bytes of buffer and see if jpg signature is using bitwise on last byte
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            if (jpg_found == 1)
            {
                // We found the start of a new pic so close out current picture
                fclose(picture);
            }
            else
            {
                // jpg discovered
                jpg_found = 1;
            }
            
            char filename[8];
            sprintf(filename, "%03d.jpg", filecount);
            picture = fopen(filename, "a");
            filecount++;
        }
        
        if (jpg_found == 1)
        {
            // Write 512 bytes to file once we start finding jpgs
            fwrite(&buffer, BUFFER_SIZE, 1, picture);
        }
        
    }

    // Close files
    fclose(input);
    fclose(picture);

    return 0;
}