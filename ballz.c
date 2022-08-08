#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Graficos */
#include "display.h"

#define HEIGHT 600
#define WIDTH 800

int main() {
    Window win;
    win = initWindow(WIDTH, HEIGHT);

    printf("\n\nENTER para encerrar esta porra");
    getchar();

    deinitWindow(win);
}