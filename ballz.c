#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "libs/display.h"
#include "libs/ball.h"
#include "libs/objects.h"

#include <math.h>

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
        int* grid = criaGrid();
        newGen(grid);

        int* squares = criaSquares();

        ball* bola;
        bola = criaBola(WIDTH/2, HEIGHT-BALL_SIZE/2); 
        bola->img = createImg("imgsGame/ball.png", BALL_SIZE, BALL_SIZE, game);
        game = initWindow(WIDTH, HEIGHT);
        
        
        bool redraw;
        bool is_down = false;
        bool balls_moving = false;
        bool just_shoot = true;
        float x, y, dist;

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
                    if(!balls_moving && ev.mouse.y < 0.9*HEIGHT){
                        dist = distance(bola->x, bola->y, ev.mouse.x, ev.mouse.y);
                        bola->vx = 16*vector(ev.mouse.x, bola->x, dist);
                        bola->vy = 16*vector(ev.mouse.y, bola->y, dist);
                        balls_moving = true;
                    }
                
                    
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
                    if(balls_moving){
                        if(bola->x < BALL_SIZE/2 || bola->x > WIDTH-BALL_SIZE/2){
                            bola->vx = -bola->vx;
                            just_shoot = false;
                        }
                        if(bola->y < BALL_SIZE/2){
                            bola->vy = -bola->vy;
                            just_shoot = false;
                        }
                        if(bola->y + BALL_SIZE/2 > 0.9*HEIGHT && !just_shoot){
                            balls_moving = false;
                            bola->vx = 0.0;
                            bola->vy = 0.0;
                            bola->y = HEIGHT-BALL_SIZE/2;
                            just_shoot = true;
                            
                            newGen(grid);
                        }
                        
                        if(bola->y < 0.9*HEIGHT){
                            int i1 = ((bola->y + bola->vy)/54) ;
                            int i2 = ((bola->x + bola->vx)/57);
                            int index = i1*WT + i2;
                            if(grid[index] == 1 && (distance(bola->x, bola->y, ((i2+1)*3+((i2+0.5)*54)), (i1+0.5)*54)) < 13.5) grid[index] = 0;
                        }



                        bola->x = bola->x + bola->vx;
                        bola->y = bola->y + bola->vy;
                    }
                    if(is_down && !balls_moving){
                        al_draw_line(bola->x, bola->y, x, y, MARROM_CLARO, 2);
                    }
                    al_draw_line(0, 0.9*HEIGHT, WIDTH, 0.9*HEIGHT, VERDE_ESCURO, 1);
                    desenhaBolas(game, grid);
                    al_draw_bitmap(bola->img, bola->x - BALL_SIZE/2, bola->y - BALL_SIZE/2, 0);
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