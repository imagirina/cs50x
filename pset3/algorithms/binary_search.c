#include <stdio.h>
#include <cs50.h>

/* starting point of binary search is a sorted array */

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 19, 135};
    for (int i = 0; i < 12; i++) {
        printf("%i ", arr[i]);
    }
    printf("\n");
    int target = get_int("Enter the number that you want to find: ");

    int start = 0; // index.   arr[0]
    int size = sizeof(arr) / sizeof(arr[0]); /* sizeof(int) - but if you change the type you will have a bug, so its better to use arr[0] */
    int end = size - 1; // arr[size - 1]
    int middle = (start + end)/2; // arr[size/2]

    while ((start != end) & (start < end)) {
        //printf("Start: %i, End:%i\n", start, end);
        middle = (start + end)/2;
        //printf("Middle: %i\n", middle);
        if (target == arr[middle]) {
            return printf("Element foud!\n");
        }
        else if (middle == (end - 1) && arr[end] == target) {
            return printf("Element foud!\n");
        }
        else if (arr[middle] < target) {
            start = middle + 1;
        }
        else { // (arr[middle] > target)
            end = middle - 1;
        }
    }
    return printf("Element NOT foud!\n");
}



