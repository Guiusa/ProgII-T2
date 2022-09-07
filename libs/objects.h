#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>
#include <stdlib.h>

#include "display.h"

#define WT 14
#define HT 10

int* criaGrid();
int* criaSquares();

int newGen(int* grid, int* squares);
void printaGens(int* grid);

void desenhaPontos(Window win, int* grid, int* squares, ALLEGRO_FONT* font);