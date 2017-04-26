/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */

bool search(int value, int values[], int n)
{
    // Check value is positive
    if(value < 0)
    {
        return false;
    }
    
    // Set initial left and right values
    int left = 0;
    int right = n - 1;
    
    // While there are still elements in the list
    while(left <= right)
    {
        // Set middle
        int middle = (left + right) / 2;
        
        // If value is equal to middle, return true
        if(value == values[middle])
        {
            return true;
        }
        
        // If value is less than middle, set right to one less than middle
        else if(value < values[middle])
        {
            right = middle - 1;
        }
        
        // If value is greater than middle, set left to one more than middle
        else
        {
            left = middle + 1;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Selection sort algorithm
    // Iterate through first element of array to penultimate element of array
    for(int i = 0; i < n ; i++)
    {
        // Set minimum
        int min = i;
        
        // Iterate through second element of array to the last element and check for minimum value in an array
        for(int j = i + 1; j < n; j++)
        {
            // Find minimum value and set it as minimum
            if(values[j] < values[min])
            {
                min = j;
            }
        }
        
        // Check if minimum changed
        if(min != i)
        {
            // Swap
            int temp = values[min];
            values[min] = values[i];
            values[i] = temp;
        }
    }
    return;
}