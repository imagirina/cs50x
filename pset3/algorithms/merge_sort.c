#include <stdio.h>
#include <cs50.h>

void printArray(int A[], int size)
{
    for (int i = 0; i < size; i++) {
        printf("%i ", A[i]);
    }
    printf("\n");
}

int merge(int arr[], int Lb,  int mid, int Ub) {
    int i = Lb;
    int j = mid + 1;
    int k = Ub;
    int b[7];
    while (i <= mid && j <= Ub) {
        if (arr[i] <= arr[j]) {
            printf("%i < %i ", arr[i], arr[j]);
            printf("\n");
            b[k] = arr[i];
            printf("b[k] = %i \n", b[k]);
            i++;
        }
        else {
            b[k] = arr[j];
            j++;
        }
        k++;
    }
    if (i > mid) { // i reached its upper bound, copy the remainint elements if there are any
        while (j <= Ub) {
            b[k] = arr[j];
            j++;
            k++;
        }
    }
    else { // j reached its upper bound, copy the remaining elements if there are any
        while (i <= mid) {
            b[k] = arr[i];
            i++;
            k++;
        }
    }

    // Copy array b into arr
    /* for (int k = Lb; k <= Ub; k++) {
        arr[k] = b[k];
        printf("%i \n", arr[k]);
    }*/
    return 0;
}

int mergeSort(int arr[], int Lb, int Ub) {
    if (Lb < Ub) {
        int mid = Lb+(Ub-Lb)/2; //mid = (Lb + Ub)/2; avoids overflow for large Lb and Ub
        printf("Lb - %i, ", arr[Lb]);
        printf("Ub - %i, ", arr[Ub]);
        printf("Mid - %i ", arr[mid]);
        printf("\n");
        // Divide and Conquer
        mergeSort(arr, Lb, mid);
        mergeSort(arr, mid+1, Ub);
        // Combine
        merge(arr, Lb,  mid, Ub);
    }
    return 0;
}

int main(void) {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Unsorted array: ");
    printArray(arr, n);
    printf("size of array = %i\n", n);
    int Lb = 0; //arr[0]
    int Ub = n - 1; // arr[n]
    //int mid;
    mergeSort(arr, Lb, Ub);  // sort the array
    printf("Sorted array: ");
    printArray(arr, n);
    return 0;
}