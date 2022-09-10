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

int newGen(int* grid, int* squares, int lvl);
void printaGens(int* grid);

void desenhaPontos(Window win, int* grid, int* squares, ALLEGRO_FONT* font, ALLEGRO_BITMAP* tijolo, ALLEGRO_BITMAP* ponto);
void printaLevel(ALLEGRO_FONT* font, int q, Window win);

int checarRecord(int lvl);
void imgsRecorde(ALLEGRO_BITMAP** imgs);