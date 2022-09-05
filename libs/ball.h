#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>
#include <stdlib.h>

struct ball_t {
    float x, y, vx, vy;
    bool justShoot, ballsMoving, shootOthers;
};
typedef struct ball_t ball;

ball* criaBola(float x, float y);

ball** maisVetorBolas(ball** bolas, ball* aux, int tam);
ball** initVtBolas(ball* bola);

float distance(float x1, float y1, int x2, int y2);
float vector(int k2, float k1, float dist);

int todasPararam(ball** bolas, int tam);