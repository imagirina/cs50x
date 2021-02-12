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
    int flag = 0;
    for (int i = 0; i < n-1; i++) {
        flag = 0;
        for (int j = 0; j < n-1-i; j++) { // number of comparison is i-value, the inner loop.
            if ((arr[j] > arr[j+1])) {
                arr[j] = arr[j] + arr[j+1];     // temp = arr[j]
                arr[j+1] = arr[j] - arr[j+1];   // arr[j] = arr[j+1]
                arr[j] = arr[j] - arr[j+1];     // arr[j+1] = temp
                flag = 1; // if we don't go ti comparison it means that no swappint is done and flag = 0, so we can break the loop
            }
        }
        if (flag == 0) {
            break;
        }
    }
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%i ", arr[i]);
    }
    printf("\n");
}

// To avoid unnesessery comparison we need to write j < n - 1 - i;