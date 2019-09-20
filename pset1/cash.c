// Greedy Algorithm - finds the optimal solution for the problem
#include <stdio.h>
#include <cs50.h>
#include <math.h>

float give_right_amount(string prompt);
int main(void)
{
    // For keeping track of coins 
    int coins_used;
    // Prompting user for amount of change
    float amount_in_dollars = give_right_amount("Change: ");
    int amount = round(amount_in_dollars * 100); // Converting $ into cents
    while (amount >= 25)
    {     
        coins_used = amount / 25;
        amount = amount % 25;           
    }
    while (amount < 25 && amount >= 10)
    {       
        coins_used = coins_used + amount / 10;
        amount = amount % 10;
    } 
    while (amount < 10 && amount >= 5) 
    {
        coins_used = coins_used + amount / 5;
        amount = amount % 5;
    } 
    if (amount < 5)
    {
        coins_used = coins_used + amount;      
    }
    printf("%i\n", coins_used);
}

float give_right_amount(string prompt)
{
    float amount_in_dollars;
    do
    {
        amount_in_dollars = get_float("%s", prompt);
    }
    while (amount_in_dollars <= 0);
    return amount_in_dollars;        
}

