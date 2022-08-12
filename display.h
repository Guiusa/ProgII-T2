#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>

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
void deinitWindow(Window win);

ALLEGRO_BITMAP* createImg(char* name, int width, int height, Window win);
ALLEGRO_BITMAP* createTxt(int size, char* texto, int* width, int* height, Window win);

#define MARROM_ESCURO PIXEL(172,116,31)
#define LARANJA PIXEL(232,179,13)
#define AMARELO PIXEL(250,212,89)
#define MARROM_CLARO PIXEL(252,245,164)
#define VERDE_ESCURO PIXEL(63, 144, 67)