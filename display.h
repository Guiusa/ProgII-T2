#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char R, G, B;
}   Pixel;
#define PIXEL(r,g,b) (al_map_rgb((unsigned char) r, (unsigned char) g, (unsigned char) b))

typedef struct {
    ALLEGRO_EVENT_QUEUE* event_queue;
    ALLEGRO_TIMER* timer;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_DISPLAY_MODE disp_data;
} Window;

Window initWindow(int widt, int height);
