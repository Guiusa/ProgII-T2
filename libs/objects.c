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

void geracaoSquares(int* gridLine, int* squares){
    int* aux = gridLine;
    for(int j = 0; j<WT; j++){
        int p = random()%100;
        if(p>60){
            aux[WT+j] = 2;
            squares[WT+j] = (random()%10) + 1;
        }
    }
}

int checaFim(int* gridLine){
    for(int j = 0; j < WT; j++)
        if(gridLine[j + (HT-1)*WT] != 0)
            return 1;
    return 0;
}

int newGen(int* grid, int* squares){
    for(int i = HT-1; i>0; i--) for(int j = 0; j<WT; j++){
        grid[(i*WT) + j] = grid[((i-1)*WT) + j];
        squares[(i*WT) + j] = squares[((i-1)*WT) + j];
    }
    for(int j = 0; j<WT; j++){
        grid[j] = 0;
        squares[j] = 0;
    } 
    
    geracaoSquares(grid, squares);
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


void desenhaPontos(Window win, int* grid, int* squares, ALLEGRO_FONT* font){
    for(int i = 0; i<HT; i++) for(int j = 0; j<WT; j++){
        if(grid[(i*WT) + j] == 1){
            al_draw_filled_circle(((j+1)*3+((j+0.5)*54)), (i+0.5)*54, 13.5, VERMELHO_PEDRO);
        }
        else if(grid[(i*WT) + j] == 2){
            char vida[3];
            sprintf(vida, "%d", squares[(i*WT) + j]);
            int x = ((j+1)*3+(j*54));
            int y = i*54;
            al_draw_filled_rectangle(x, y, x+54, y+54, VERMELHO_PEDRO);
            al_draw_text(font, PIXEL(0, 0, 0), x+27, y+15, ALLEGRO_ALIGN_CENTRE, vida);
        }
    }
}