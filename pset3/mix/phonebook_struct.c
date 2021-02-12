#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    string name;
    string number;
}
person;


int main(void) {
    person people[4];
    people[0].name = "EMMA";
    people[0].number = "691-9080000";
    people[1].name = "RODRIGO";
    people[1].number = "691-9080001";
    people[2].name = "BRIAN";
    people[2].number = "691-9080002";
    people[3].name = "DAVID";
    people[3].number = "691-9080003";

    for (int i = 0; i < 4; i++) {
        if (strcmp(people[i].name, "EMMA") == 0) {
            printf("%s\n", people[i].number);
            return 0;
        }
    }
    printf("Not Found\n");
    return 1;
}