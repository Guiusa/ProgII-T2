#include "objects.h"
#include "allegro5/allegro_primitives.h"
#include <math.h>

int* criaGrid(){
    int* fullGrid = malloc(WT * HT * sizeof(int));

    for(int i = 0; i<HT; i++) 
        for(int j = 0; j<WT; j++) 
            fullGrid[(i*WT) + j] = 0;
    
    return fullGrid;
}

int* criaSquares(){
    int* squares = malloc(WT * HT * sizeof(int));
    return squares;
}


void geracaoPontos(int* gridLine){
    int* aux = gridLine;
    for(int j = 0; j<WT; j++){
        int p = random()%100;
        if(p>90)
            aux[WT+j] = 1;
    } 
}

void geracaoSquares(int* gridLine, int* squares, int lvl){
    int* aux = gridLine;

    for(int j = 0; j<WT; j++){
        int p = random()%100;
        if(p>60){
            aux[WT+j] = 2;
            squares[WT+j] = (random()%(lvl)) + lvl;
        }
    }
}

int checaFim(int* gridLine){
    for(int j = 0; j < WT; j++)
        if(gridLine[j + (HT-1)*WT] == 2)
            return 1;
    return 0;
}

int newGen(int* grid, int* squares, int lvl){
    for(int i = HT-1; i>0; i--) for(int j = 0; j<WT; j++){
        grid[(i*WT) + j] = grid[((i-1)*WT) + j];
        squares[(i*WT) + j] = squares[((i-1)*WT) + j];
    }
    for(int j = 0; j<WT; j++){
        grid[j] = 0;
        squares[j] = 0;
    } 
    
    geracaoSquares(grid, squares, lvl);
    geracaoPontos(grid);

    return checaFim(grid);    
}

void printaGens(int* grid){
    for(int i=0; i<HT; i++){
        for(int j = 0; j<WT; j++) printf("%d ", grid[(i*WT) + j]);
        printf("\n");
    }
}
// 1 for points, 2 for squares and 0 for neither one


void desenhaPontos(Window win, int* grid, int* squares, ALLEGRO_FONT* font, ALLEGRO_BITMAP* tijolo, ALLEGRO_BITMAP* ponto){
    for(int i = 0; i<HT; i++) for(int j = 0; j<WT; j++){
        if(grid[(i*WT) + j] == 1){
            al_draw_bitmap(ponto, ((j+1)*3+((j+0.5)*54) - 14), ((i+0.5)*54)-14, 0);
        }
        else if(grid[(i*WT) + j] == 2){
            char vida[3];
            sprintf(vida, "%d", squares[(i*WT) + j]);
            int x = ((j+1)*3+(j*54));
            int y = i*54;
            al_draw_bitmap(tijolo, x, y, 0);
            al_draw_text(font, VERMELHO_PEDRO, x+27, y+15, ALLEGRO_ALIGN_CENTRE, vida);
        }
    }
}

void printaLevel(ALLEGRO_FONT* font, int q, Window win){
    char quant[3];
    sprintf(quant, "%d", q);
    al_draw_text(font, VERMELHO_PEDRO, 750, 550, ALLEGRO_ALIGN_CENTRE, "LEVEL:");
    al_draw_text(font, VERMELHO_PEDRO, 750, 570, ALLEGRO_ALIGN_CENTRE, quant);
}

int checarRecord(int lvl){
    FILE* file = fopen(".rcd", "r+");
    int aux;
    fscanf(file, "%d", &aux);
    if(lvl > aux || aux > 20000){
        fseek(file, 0, SEEK_SET);
        fprintf(file, "%d", lvl);
    }
    fclose(file);
}

void imgsRecorde(ALLEGRO_BITMAP** imgs){
    FILE* file = fopen(".rcd", "r");
    int total, uni, dez, cen;
    fscanf(file, "%d", &total);
    uni = total%10;
    total = floor(total/10);
    dez = total%10;
    total = floor(total/10);
    cen = total;

    al_draw_bitmap(imgs[cen], 256, 175, 0);
    al_draw_bitmap(imgs[dez], 352, 175, 0);
    al_draw_bitmap(imgs[uni], 448, 175, 0);

    fclose(file);
}