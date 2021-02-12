#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    string names[4] = {"EMMA", "RODRIGO", "BRIAN", "DAVID"};
    string numbers[4] = {"691-9080000", "415-9876543", "901-7654545", "309-6566565"};
    for (int i = 0; i < 4; i++) {
        if (strcmp(names[i], "EMMA") == 0) {
            printf("%s\n", numbers[i]);
            return 0;
        }
    }
    printf("Not Found\n");
    return 1;
}