#include <stdio.h>
#include <cs50.h>

int main(void) {
    int arr[] = {302, 54, 34, 12, 56, 0, 4, 1, 76, 98};
    int n = 10;
    printf("Unsorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%i ", arr[i]);
    }
    printf("\n");
    // first loop for each element
    // second loop for finding the smallest element and swapping
    int temp;
    for (int i =0; i < n-1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[i]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%i ", arr[i]);
    }
    printf("\n");
}