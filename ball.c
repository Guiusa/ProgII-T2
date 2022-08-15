#include "ball.h"

ball criaBola(){
    ball* bola = malloc(4 * sizeof(float));
    bola->x = 0.0;
    bola->y = 0.0;
    bola->vx = 0.0;
    bola->vy = 0.0;
    return *bola;
}