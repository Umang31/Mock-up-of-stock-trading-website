#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy infile outfile\n");
        return 1;
    }

    // Convert command-line value to int
    int n = atoi(argv[1]);
    
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
    
    // Check if n is between 1 and 100
    if(n < 0 || n > 100)
    {
        printf("Please enter number between 1 and 100\n");
        return 1;
    }

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    BITMAPFILEHEADER bf_new;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    // Set new BITMAPFILEHEADER to original BITMAPFILEHEADER
    bf_new = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    BITMAPINFOHEADER bi_new;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    // Set new BITMAPINFOHEADER to original BITMAPINFOHEADER
    bi_new = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // Update width and height
    bi_new.biWidth = bi.biWidth * n;
    bi_new.biHeight = bi.biHeight * n;
    
    // Determine padding for scalelines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding =  (4 - (bi_new.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // Set new file size
    bf_new.bfSize = 54 + (bi_new.biWidth * sizeof(RGBTRIPLE) + new_padding) * abs(bi_new.biHeight);
    bi_new.biSizeImage = bf_new.bfSize - 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_new, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_new, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        int counter = 0;

        while (counter < n)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                 
                // each pixel will be printed out factor times
                int pixelcounter = 0;
 
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
             
                // write RGB triple to outfile
                while (pixelcounter < n)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    pixelcounter++;
                }
            }
             
            // add new padding
            for (int k = 0; k < new_padding; k++)
                fputc(0x00, outptr);
             
            // seek back to the beginning of row in input file, but not after iteration of printing
            if (counter < (n - 1))
                fseek(inptr, -(bi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
             
            counter++;
        }
         
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}