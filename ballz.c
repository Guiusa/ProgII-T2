#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Graficos */
#include "display.h"

#define WIDTH 800
#define HEIGHT 600
#define BALL_SIZE 15

int main() {
    Window menu;
    menu = initWindow(WIDTH, HEIGHT);
    
    //Window win;
    //ALLEGRO_BITMAP* ball;
    //ball = createImg("ball.png", BALL_SIZE, BALL_SIZE, win);
    // al_draw_bitmap(ball, WIDTH/2 - BALL_SIZE/2, HEIGHT - BALL_SIZE, 0);
    
    ALLEGRO_BITMAP* fundo; 
    ALLEGRO_BITMAP* play;
    ALLEGRO_BITMAP* record;
    
    fundo = createImg("fundoMenu.png", WIDTH, HEIGHT, menu);
    play = createImg("botaoPlay.png", 640, 240, menu);
    record = createImg("botaoRecord.png", 640, 240, menu);
    
    al_draw_bitmap(fundo, 0, 0, 0);
    al_draw_bitmap(play, 80, 60, 0);
    al_draw_bitmap(record, 80, 300, 0);
    al_flip_display();

    printf("\n\nENTER para encerrar o programa");
    getchar();

    deinitWindow(menu);
}