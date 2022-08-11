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
    Window telaRecorde;
    //ALLEGRO_BITMAP* ball;
    //ball = createImg("ball.png", BALL_SIZE, BALL_SIZE, win);
    // al_draw_bitmap(ball, WIDTH/2 - BALL_SIZE/2, HEIGHT - BALL_SIZE, 0);
    
    bool sairMenu = false;
    bool rodarJogo = false;
    bool rodarRecorde = false;
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
                if(ev.mouse.x >= 80 && ev.mouse.x <= 720){
                    if(ev.mouse.y >= 60 && ev.mouse.y <= 300){
                        rodarJogo = true;
                        sairMenu = true;
                    }
                    else if(ev.mouse.y >= 300 && ev.mouse.y <= 540){
                        sairMenu = true;
                        rodarRecorde = true;
                        printf("RECORDE\n");
                    }
                }
                break;
        }
    }
    deinitWindow(menu);

    if(rodarJogo){
        game = initWindow(WIDTH, HEIGHT);
        while(rodarJogo){
            ALLEGRO_EVENT ev;
            al_wait_for_event(game.event_queue, &ev);

            switch(ev.type){
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    rodarJogo = false;
                    deinitWindow(game);
                    break;
                case ALLEGRO_EVENT_KEY_UP:
                    if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                        deinitWindow(game);
                        rodarJogo = false;
                    }
            }
        }
    }
    else if(rodarRecorde){
        int txtH, txtW;
        telaRecorde = initWindow(WIDTH, HEIGHT);
        
        ALLEGRO_BITMAP* txt = createTxt("SEU RECORDE É:", &txtW, &txtW, telaRecorde);
    
        al_draw_bitmap(fundo, 0, 0, 0);
        al_draw_bitmap(txt, WIDTH/2, HEIGHT/2, 0);

        al_flip_display();

        while(rodarRecorde){
            ALLEGRO_EVENT ev;
            al_wait_for_event(telaRecorde.event_queue, &ev);

            switch(ev.type){
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    rodarRecorde = false;
                    deinitWindow(telaRecorde);
                    break;
                case ALLEGRO_EVENT_KEY_UP:
                    if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                        rodarRecorde = false;
                        deinitWindow(telaRecorde);
                    }
            }
        }
    }


    al_destroy_bitmap(fundo);
    al_destroy_bitmap(play);
    al_destroy_bitmap(record);
}