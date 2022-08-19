#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>
#include <stdlib.h>

struct ball_t {
    float x, y, vx, vy;
    ALLEGRO_BITMAP* img;
};
typedef struct ball_t ball;

ball* criaBola(float x, float y);

float distance(float x1, float y1, float x2, float y2);
float vector(float k2, float k1, float dist);