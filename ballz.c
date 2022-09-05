#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//#include "libs/display.h"
#include "libs/ball.h"
#include "libs/objects.h"

#include <math.h>

#include "allegro5/allegro_primitives.h"

#define WIDTH 800
#define HEIGHT 600
#define BALL_SIZE 15

int main() {
    srand(time(NULL));
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
    fundo = createImg("imgsGame/fundoMenu.jpg", WIDTH, HEIGHT, menu);
    play = createImg("imgsGame/botaoPlay.png", 512, 192, menu);
    record = createImg("imgsGame/botaoRecord.png", 512, 192, menu);

    al_draw_bitmap(fundo, 0, 0, 0);
    al_draw_bitmap(play, 144, 84, 0);
    al_draw_bitmap(record, 144, 324, 0);
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
                if(ev.mouse.x >= 144 && ev.mouse.x <= 656){
                    if(ev.mouse.y >= 84 && ev.mouse.y <= 276){
                        rodarJogo = true;
                        sairMenu = true;
                    }
                    else if(ev.mouse.y >= 324 && ev.mouse.y <= 516){
                        sairMenu = true;
                        rodarRecorde = true;
                    }
                }
                break;
        }
    }
    deinitWindow(menu);

    if(rodarJogo){
        int tamBolas = 1;
        int timeStamp;
        int* grid = criaGrid();
        newGen(grid);
        
        int* squares = criaSquares();

        
        ball* bola;
        bola = criaBola(WIDTH/2, HEIGHT-BALL_SIZE/2); 

        ALLEGRO_BITMAP* fundoG = createImg("imgsGame/fundoGame.jpg", WIDTH, HEIGHT, menu);
        ALLEGRO_BITMAP* img = createImg("imgsGame/ball.png", BALL_SIZE, BALL_SIZE, game);
        game = initWindow(WIDTH, HEIGHT);
        
        ball** vBolas = initVtBolas(bola);
        
        bool redraw;
        bool is_down = false;
        bool shoot = false;
        bool first = true;

        int xBalls;
        int countBolas;
        float x, y, dist;

        while(rodarJogo){
            redraw = false;

            ALLEGRO_EVENT ev;
            al_wait_for_event(game.event_queue, &ev);
        
            switch(ev.type){
                case ALLEGRO_EVENT_TIMER:
                    redraw = true;
                    timeStamp++;
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
                    if(!shoot && ev.mouse.y < 0.9*HEIGHT){
                        dist = distance(vBolas[0]->x, vBolas[0]->y, ev.mouse.x, ev.mouse.y);
                        for(int i = 0; i<tamBolas; i++){
                            int counterAux = 1;
                            vBolas[i]->vx = 16*vector(ev.mouse.x, vBolas[i]->x, dist);
                            vBolas[i]->vy = 16*vector(ev.mouse.y, vBolas[i]->y, dist);
                            vBolas[i]->justShoot = true;
                            vBolas[i]->ballsMoving = true;
                            vBolas[i]->shootOthers = true;
                        }
                        timeStamp = -1;
                        first=true;
                        shoot = true;
                        countBolas = 0;
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
                    al_draw_bitmap(fundoG, 0, 0, 0);
                    for(int i = 0; i<tamBolas; i++){
                        if(vBolas[i]->ballsMoving){
                            if((vBolas[i]->x < BALL_SIZE/2 || vBolas[i]->x > WIDTH-BALL_SIZE/2) && vBolas[i]->y < 0.9*HEIGHT - BALL_SIZE/2){
                                vBolas[i]->vx = -vBolas[i]->vx;
                                vBolas[i]->justShoot = false;
                            }
                            if(vBolas[i]->y < BALL_SIZE/2){
                                vBolas[i]->vy = -vBolas[i]->vy;
                                vBolas[i]->justShoot = false;
                            }
                            if(vBolas[i]->y + BALL_SIZE/2 > 0.9*HEIGHT && !vBolas[i]->justShoot){
                                if(first){
                                    xBalls = vBolas[i]->x;
                                    first = false;
                                }
                                vBolas[i]->x = xBalls;
                                vBolas[i]->ballsMoving = false;
                                vBolas[i]->vx = 0.0;
                                vBolas[i]->vy = 0.0;
                                vBolas[i]->y = HEIGHT-BALL_SIZE/2;
                                vBolas[i]->ballsMoving = false;
                            }
                            if(todasPararam(vBolas, tamBolas)){
                                shoot = false;
                                newGen(grid);
                                for(int i = 0; i<countBolas; i++){
                                    ball* aux = criaBola(vBolas[i]->x, HEIGHT-BALL_SIZE/2);
                                    vBolas = maisVetorBolas(vBolas, aux, tamBolas);
                                    tamBolas++;
                                }
                            }
                            
                            
                            
                            int i1 = ((vBolas[i]->y + vBolas[i]->vy)/54) ;
                            int i2 = ((vBolas[i]->x + vBolas[i]->vx)/57);
                            int index = i1*WT + i2;
                            
                            if(grid[index] == 1 && (distance(vBolas[i]->x, vBolas[i]->y, ((i2+1)*3+((i2+0.5)*54)), (i1+0.5)*54)) < 13.5) {
                                grid[index] = 0;
                                countBolas++;
                            }
                            if(vBolas[i]->shootOthers){
                                if(timeStamp >= i*10-1 && timeStamp <=i*10+1){
                                    vBolas[i]->x = vBolas[i]->x + vBolas[i]->vx;
                                    vBolas[i]->y = vBolas[i]->y + vBolas[i]->vy;
                                    vBolas[i]->shootOthers = false;
                                }
                            }
                            else{
                                vBolas[i]->x = vBolas[i]->x + vBolas[i]->vx;
                                vBolas[i]->y = vBolas[i]->y + vBolas[i]->vy;
                            }
                        }
                    }
                    if(is_down && !shoot)
                        al_draw_line(bola->x, bola->y, x, y, MARROM_CLARO, 2);
                    al_draw_line(0, 0.9*HEIGHT, WIDTH, 0.9*HEIGHT, VERDE_ESCURO, 1);
                    desenhaPontos(game, grid);
                    for(int i=0; i<tamBolas; i++)
                        al_draw_bitmap(img, vBolas[i]->x - BALL_SIZE/2, vBolas[i]->y - BALL_SIZE/2, 0);
                    
                    al_flip_display();
                }
            }
        }
    }

    else if(rodarRecorde){
        telaRecorde = initWindow(WIDTH, HEIGHT);
        ALLEGRO_BITMAP* fundoRec = createImg("imgsGame/fundoRecord.jpg", WIDTH, HEIGHT, telaRecorde);

    
        al_draw_bitmap(fundoRec, 0, 0, 0);
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