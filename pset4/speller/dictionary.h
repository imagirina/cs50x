// Declares a dictionary's functionality
// The prototypes for the functions declared here, so we can use #include in both speller.c and dictionary.c

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45 // a "preprocessor directive" that defines a "constant" called LENGTH that has a value of 45
//  In fact, clang will replace any mentions of LENGTH in your own code with, literally, 45.
// In other words, it’s not a variable, just a find-and-replace trick.

// Prototypes
// char * is what we used to call string
bool load(const char *dictionary);
unsigned int size(void);
bool check(const char *word); // the same as check(const string word);
bool unload(void);

#endif // DICTIONARY_H
