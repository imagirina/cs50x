// Implements a dictionary's functionality
// REMEMBER: a hash table is an array of linked lists (each element of array is a node* (node pointer))

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
// Each element in array is a node*
// Each node has a value and pointer to the next node
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
// Declared a global array with enough room for N pointers to nodes, where N is a bucket (each letter in alphabet), initialized above.
node *hashtable[N] = {NULL}; // Root for our hash table

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
// Returns 0 for any word that starts with an a (or A), 1 for any word that starts with a b (or B) ...
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary of words into memory (into a hashtable), returning true if successful else false
// For each word in a textfile store it in the data structure
bool load(const char *dictionary)
{
    // Code initialize all buckets (pointers) in hashtable to NULL
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }
    // Code that opens dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }
    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    // Code that iterates over that dictionary and reads the words therein, one at a time, into a buffer (i.e., string) called word
    while (fscanf(file, "%s", word) != EOF) // Execute until EOF reached
    {
        // For every word we scan we need to malloc() the node
        node *newnode = malloc(sizeof(node)); // *********Valgrind - Uninitialised value was created by a heap allocation
        // hashtable[i] is our bucket 0..26. If we run out of memory, malloc() return NULL. Else - return a pointer.

        // Initializing nodes with NULL (for valgrind)
        for (int i = 0; i < N; i++)
        {
            newnode->next = NULL;
        }

        if (newnode == NULL)
        {
            unload();
            return false;
        }
        // If succed copy word into the node
        strcpy(newnode->word, word); // Put string into a variable called word

        int key = hash(word); // Takes the str, returns an index (index < the number of buckets)

        // Check for empty lists
        if (hashtable[key] == NULL)
        {
            hashtable[key] = newnode; // Linking two nodes
            //printf("Hashtable[%i]->%s\n", key, newnode->word);
        }
        else // Bucket is not empty
        {
            newnode->next = hashtable[key];
            hashtable[key] = newnode;
            //printf("->%s\n", newnode->word);
        }
    }
    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int counter = 0;
    for (int i = 0; i < N; i++)
    {
        node *cursor = hashtable[i];
        while (cursor != NULL) // valgrind error!!!!!!!!!!!!!!!
        {
            counter++;
            cursor = cursor->next;
        }
    }
    return counter;
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // We do not need to lowercase given word
    // All alphabetic characters in string1 and string2 are converted to lowercase before comparison
    node *cursor = hashtable[hash(word)];
    while (cursor != NULL) // valgrind error!!!!!!!!!!!!!!!
    {
        if (strcasecmp(cursor->word, word) == 0) // 0 - the strings are equivalent
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = hashtable[i];
        while (cursor != NULL) // valgrind error!!!!!!!!!!!!!!!
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}