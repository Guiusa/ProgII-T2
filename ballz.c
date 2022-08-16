#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Graficos */
#include "display.h"
#include "allegro5/allegro_primitives.h"

#define WIDTH 800
#define HEIGHT 600
#define BALL_SIZE 15

int main() {
    al_init_primitives_addon();
    
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
    ALLEGRO_BITMAP* bola;
    
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
        bola = createImg("imgsGame/ball.png", BALL_SIZE, BALL_SIZE, game);
    
        bool redraw;
        bool is_down = false;
        int x, y;

        while(rodarJogo){
            redraw = false;

            ALLEGRO_EVENT ev;
            al_wait_for_event(game.event_queue, &ev);
        
            switch(ev.type){
                case ALLEGRO_EVENT_TIMER:
                    redraw = true;
                    break;
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    rodarJogo = false;
                    deinitWindow(game);
                    break;
                case ALLEGRO_EVENT_KEY_UP:
                    if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                        deinitWindow(game);
                        rodarJogo = false;
                    }
                    break;
                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                    is_down = true;
                    break;
                case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                    is_down = false;
                    break;
                case ALLEGRO_EVENT_MOUSE_AXES:
                    if(ev.mouse.y <= 0.9*HEIGHT){
                        x = ev.mouse.x;
                        y = ev.mouse.y;
                    }   
                    break;
            }

            if(redraw){
                if(al_is_event_queue_empty(game.event_queue)){
                    al_clear_to_color(PIXEL(0, 0, 0));
                    
                    if(is_down){
                        al_draw_line(WIDTH/2, HEIGHT - BALL_SIZE, x, y, MARROM_CLARO, 2);
                    }
                    al_draw_bitmap(bola, WIDTH/2 - BALL_SIZE/2, HEIGHT-BALL_SIZE, 0);
                    al_draw_line(0, 0.9*HEIGHT, WIDTH, 0.9*HEIGHT, VERDE_ESCURO, 1);
                    al_flip_display();
                }
            }
        }
    }

    else if(rodarRecorde){
        int txtH, txtW;
        telaRecorde = initWindow(WIDTH, HEIGHT);
        
        ALLEGRO_BITMAP* txt = createTxt(60,"SEU RECORDE É:", &txtW, &txtH, telaRecorde);
    
        al_draw_bitmap(fundo, 0, 0, 0);
        al_draw_bitmap(txt, WIDTH/2 - txtW/2, HEIGHT/2 - txtH/2, 0);
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