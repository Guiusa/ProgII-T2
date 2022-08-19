#include "ball.h"
#include <math.h>

ball* criaBola(float x, float y){
    ball* bola = malloc(sizeof(ball*));
    bola->x = x;
    bola->y = y;
    bola->vx = 0.0;
    bola->vy = 0.0;
    bola->img = NULL;
    return bola;
}

float distance(float x1, float y1, float x2, float y2){
    float sqrX = x2-x1;
    sqrX = sqrX*sqrX;

    float sqrY = y2-y1;
    sqrY = sqrY*sqrY;

    float result = sqrt(sqrX + sqrY);

    return result;
}
float vector(float k2, float k1, float dist){
    return ((k2-k1) / dist);
}