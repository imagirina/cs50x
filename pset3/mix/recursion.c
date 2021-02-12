#include <stdio.h>
#include <cs50.h>

void draw(int h);

int main(void) {
    int height = get_int("Height: ");
    draw(height);
}

void draw(int h) {
    if (h == 0) {
        return; //base case, just do nothing. It is just error check just to make sure I would not do it forever
    }
    draw(h - 1);
    for (int i = 0; i < h; i++) {
        printf("#");
    }
    printf("\n");
}