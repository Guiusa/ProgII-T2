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
    Window game;
    //ALLEGRO_BITMAP* ball;
    //ball = createImg("ball.png", BALL_SIZE, BALL_SIZE, win);
    // al_draw_bitmap(ball, WIDTH/2 - BALL_SIZE/2, HEIGHT - BALL_SIZE, 0);
    
    bool sairMenu = false;
    bool rodarJogo = false;
    ALLEGRO_BITMAP* fundo; 
    ALLEGRO_BITMAP* play;
    ALLEGRO_BITMAP* record;
    
    menu = initWindow(WIDTH, HEIGHT);
    fundo = createImg("imgsGame/fundoMenu.png", WIDTH, HEIGHT, menu);
    play = createImg("imgsGame/botaoPlay.png", 640, 240, menu);
    record = createImg("imgsGame/botaoRecord.png", 640, 240, menu);
    
    al_draw_bitmap(fundo, 0, 0, 0);
    al_draw_bitmap(play, 80, 60, 0);
    al_draw_bitmap(record, 80, 300, 0);
    al_flip_display();
    
    while(!sairMenu){
        ALLEGRO_EVENT ev;
        al_wait_for_event(menu.event_queue, &ev);
        
        switch(ev.type){
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                sairMenu = true;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    sairMenu = true;    
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if((ev.mouse.x >= 80 && ev.mouse.x <= 720) && (ev.mouse.y >= 60 && ev.mouse.y <= 300)){
                    printf("PLAY\n");
                    rodarJogo = true;
                    sairMenu = true;
                }
                break;
        }
    }
    deinitWindow(menu);

    if(rodarJogo)
        game = initWindow(WIDTH, HEIGHT);

    while(rodarJogo){
        ALLEGRO_EVENT ev;
        al_wait_for_event(game.event_queue, &ev);

        switch(ev.type){
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                rodarJogo = false;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    rodarJogo = false;
        }
    }

    deinitWindow(game);
}