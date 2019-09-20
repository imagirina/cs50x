#include <stdio.h>
#include <math.h>
#include <cs50.h>

long get_right_number(string prompt);
int findTotalDigits(long number);
int find_first_two_digits(long n, int c);
int main(void) 
{
    long number = get_right_number("Add the credit card number: ");    
    int count = findTotalDigits(number);
    int digits = find_first_two_digits(number, count);   
    if ((count == 13 || count == 16) && (digits == 40 || digits == 41 || digits == 42 || digits == 43 || digits == 44 || digits == 45 
                                         || digits == 46 || digits == 47 || digits == 48 || digits == 49))
    {
        printf("VISA\n");
    } 
    else if (count == 15 && (digits == 34 || digits == 37))
    {
        printf("AMEX\n");        
    } 
    else if (count == 16 && (digits == 51 || digits == 52 || digits == 53 || digits == 54 || digits == 55)) 
    {
        printf("MASTERCARD\n");                
    } 
    else 
    {
        printf("INVALID\n");       
    }    
}

long get_right_number(string prompt) 
{
    long number;
    do
    {
        number = get_long("%s", prompt);
    }
    while (number < 0);
    return number;
}

int findTotalDigits(long n) 
{ 
    int count = 0; 
    while (n != 0) 
    { 
        n = n / 10; 
        ++count;
    } 
    return count; 
} 

int find_first_two_digits(long n, int c) 
{ 
    // Remove last digit from number till only two digits are left 
    int count = 0; 
    do 
    {
        n = n / 10; 
        ++count;
    }
    while (count != c - 2);
    // Return the two digits
    return n; 
} 
/*
AMEX - 15-digit long (starts with 34 or 37) +
VISA 13 and 16-digit (all visa numbers stars with 4)
MASTERCARD - 16-digit long (starts with 51, 52, 53, 54, 55)
INVALID

1. find the number of digits in input
2. check the first 1-2 numbers 
*/

