#include <cs50.h>
#include <stdio.h>

int get_right_height(string prompt);
int main(void)
{
    int height = get_right_height("Height: ");
    int width = (height * 2) + 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j >= height + 3 + i)
            {
                printf("");
            } 
            else if (j >= height - 1 - i && j != height && j != height + 1)
            {
                printf("#");
            } 
            else
            {
                printf(" ");
            }            
        }
        printf("\n");
    }
}

int get_right_height(string prompt) 
{
    int height;
    do 
    {
        height = get_int("%s", prompt);
    }
    while (height < 1 || height > 8);
    return height;
}

