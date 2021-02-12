#include <stdio.h>
#include <cs50.h>

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%i ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int arr[] = {302, 54, 34, 12, 56, 0, 4, 1, 76, 98};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Unsorted array: ");
    printArray(arr, n);
    int i, j, temp;
    for (i = 1; i < n; i++) {
        temp = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > temp) {
            arr[j+1] = arr[j];
            j = j - 1;
        }
        arr[j+1] = temp;
    }
    printf("Sorted array: ");
    printArray(arr, n);
}