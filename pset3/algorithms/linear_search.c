#include <stdio.h>
#include <cs50.h>

/* iterate from left to right, searching for a specified element */

int main(void) {
    int arr[] = {16, 80, 3, 4, 6, 8, 9, 12};
    int target = get_int("Enter the number that you want to find: ");
    for (int i = 0; i < 8; i++) {
        if (arr[i] == target) {
            return printf("Target found!\n");
        }
    }
    printf("There is no such element in array.\n");
}