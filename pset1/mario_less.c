#include <stdio.h>
#include <cs50.h>

int get_right_int(string prompt);
int main(void)
{
    // Prompt user for height (integer between 1 and 8)
    int num = get_right_int("Height: ");
    for (int i = 0; i < num; i++) 
    {
        for (int j = 0; j < num; j++)
        {
            if (j >= num - 1 - i) 
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n"); // Print New Line
    }
}
int get_right_int(string prompt) 
{
    int number; // Assign just once
    do 
    {
        number = get_int("%s", prompt); // Getting the integer from the user
    }
    while (number < 1 || number > 8);
    return number;
}

/*
1. Prompt user for height
2. If height less than 1 or bigger than 8 -> go to step 1
3. If height between the 1 and 8 (including) follow the step 4
4. Print as many lines as the prompted heigh (iteration)
  i. On iteration i print the '#' i times. End by printing a new line.
*/
  
  









