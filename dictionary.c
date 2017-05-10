/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<math.h>

#include "dictionary.h"

// Define size of hashtable
#define HASHTABLE_SIZE 100000 

// Define struct for Linked-List i.e. Create a node
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

// Create Hash-Table
node* hashtable[HASHTABLE_SIZE];

// Create Hash function
int hash(const char *word)
{
    int hash = 0;
    int n;
    for(int i = 0; word[i] != '\0'; i++)
    {
        // Check if alphabet or comma
        if(isalpha(word[i]))
        {
            n = word[i] - 'a' + 1;
        }
        
        else
        {
            n = 27;
        }
        
        hash = ((hash << 3) + n) % HASHTABLE_SIZE;
    }
    return hash;
}

// Global variable declaration to count size of dictionary
int dictionary_size = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // Create temperary variable that stores lower case version of the word
    char temp[LENGTH + 1];
    int len = strlen(word);
    
    for(int i = 0; i < len; i++)
    {
        temp[i] = tolower(word[i]);
    }
    temp[len] = '\0';
    
    // Find the index of the array, word should be in
    int index = hash(temp);
    
    // If hashtable is empty at index, return false
    if(hashtable[index] == NULL)
    {
        return false;
    }
    
    // Create cursor to compare to word
    node* cursor = hashtable[index];
    
    // If hashtable is not empty at index, iterate through words and compare
    while(cursor != NULL)
    {
        if(strcmp(temp, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    
    // Return false if word is not found
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
// Open dictionary
    FILE* file = fopen(dictionary, "r");
    if(file == NULL)
    {
        return false;
    }
    
    // Create an array for word
    char word[LENGTH + 1];
    
    // Scan through the file and put each word in the hash table
    while(fscanf(file, "%s\n", word) != EOF)
    {
        // Increment dictionary size
        dictionary_size++;
        
        // Allocate memory for new word
        node* new_word = malloc(sizeof(node));
        
        // Put word in the new node
        strcpy(new_word->word, word);
        
        // Find the index of the array to put the word in the hash table
        int index = hash(word);
        
        // If hashtable is empty, insert the new word
        if(hashtable[index] == NULL)
        {
            hashtable[index] = new_word;
            new_word->next = NULL;
        }
        
        // If hashtable is not empty at index, append
        else
        {
            new_word->next = hashtable[index];
            hashtable[index] = new_word;
        }
    }
    
    // Close file
    fclose(file);
    
    // Retuen true if successful
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // If dictionary is loaded, return number of words
    if(dictionary_size > 0)
    {
        return dictionary_size;
    }
    
    // If dictionary hasn't been loaded, return 0
    else
    {
        return 0;
    }
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // Create variable index and set it to 0
    int index = 0;
    
    // Iterate through entire hashtable array
    while(index < HASHTABLE_SIZE)
    {
        // Check if hashtable is empty at index
        if(hashtable[index] == NULL)
        {
            // Increment index
            index++;
        }
        
        // If hashtable is not empty, iterate through nodes and start unloading
        else
        {
            while(hashtable[index] != NULL)
            {
                node* cursor = hashtable[index];
                hashtable[index] = cursor->next;
                free(cursor);
            }
            
            // Once hashtable is empty at index, go to next index
            index++;
        }
    }
    
    // Return true if successful
    return true;
}
