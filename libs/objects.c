#include "objects.h"
#include "allegro5/allegro_primitives.h"

int* criaGrid(){
    int* fullGrid = malloc(WT * HT * sizeof(int));

    for(int i = 0; i<HT; i++) 
        for(int j = 0; j<WT; j++) 
            fullGrid[(i*WT) + j] = 0;
    
    return fullGrid;
}

int* criaSquares(){
    int* squares = malloc(100 * sizeof(int));
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

void geracaoSquares(int* gridLine){
    int* aux = gridLine;
    for(int j = 0; j<WT; j++){
        int p = random()%100;
        if(p>50)
            aux[WT+j] = 2;
    }
}

int checaFim(int* gridLine){
    for(int j = 0; j < WT; j++)
        if(gridLine[j] != 0)
            return 1;
    return 0;
}

int newGen(int* grid){
    for(int i = HT-2; i>0; i--) for(int j = 0; j<WT; j++)
        grid[(i*WT) + j] = grid[((i-1)*WT) + j];
    for(int j = 0; j<WT; j++) grid[j] = 0;
    
    geracaoSquares(grid);
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


void desenhaBolas(Window win, int* grid){
    for(int i = 0; i<HT; i++) for(int j = 0; j<WT; j++)
        if(grid[(i*WT) + j] == 1){
            al_draw_filled_circle(((j+1)*3+((j+0.5)*54)), (i+0.5)*54, 13.5, AMARELO);
        }

}