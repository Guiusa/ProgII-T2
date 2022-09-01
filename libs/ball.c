#include "ball.h"
#include <math.h>

ball* criaBola(float x, float y){
    ball* bola = malloc(sizeof(ball*));
    bola->x = x;
    bola->y = y;
    bola->vx = 0.0;
    bola->vy = 0.0;
    bola->justShoot = true;
    bola->ballsMoving = false;
    return bola;
}

float distance(float x1, float y1, int x2, int y2){
    float sqrX = x2-x1;
    sqrX = sqrX*sqrX;

    float sqrY = y2-y1;
    sqrY = sqrY*sqrY;

    float result = sqrt(sqrX + sqrY);

    return result;
}

float vector(int k2, float k1, float dist){
    float result = (k2-k1) / dist;
    return (result);
}

ball** initVtBolas(ball* bola){
    ball** aux = malloc(sizeof(ball*));
    aux[0] = bola;
    return aux;
}

ball** maisVetorBolas(ball** bolas, ball* aux, int tam){
    bolas = realloc(bolas, (tam+1)*sizeof(ball*));
    bolas[tam] = aux;
    return bolas;
}

int todasPararam(ball** bolas, int tam){
    for(int i = 0; i < tam; i++)
        if(bolas[i]->ballsMoving)
            return 0;
    return 1;
}