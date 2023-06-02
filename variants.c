
/******************************************************************************
* variants.c
* (c) Miguel Cardoso & Manuel Guilherme
* AED 2021 - 1S
*
* DESCRIPTION
*	Implements variants A1-A6
*
******************************************************************************/
#include "maze.h"
#include "queue.h"
#include "variants.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/*------------------ NOTA -----------------------------
 * As células podem ter três cores possíveis
 * Pretas - V = -1 Paredes Indestrutíveis
 * Bracas - V = 0 Caminho Livre
 * Cinzentas - V = x (x>0) Parede Destrutível com custo x
 -------------------------------------------------------*/

/*------------------ A1 -----------------------------
 * para as coordenadas (l; c) identificar
 * o tipo de célula
-------------------------------------------------------*/

int a1(Grid *M, int L, int C){
    if(L<=0 || L>M->L || C<=0 || C>M->C) return(-2); //out of the maze
    return(M->maze[L][C]);
}


/*------------------ A2 -----------------------------
 * para as coordenadas (l; c) indicar se existe
 * algum vizinho que seja célula branca
-------------------------------------------------------*/
int a2(Grid *M, int L, int C){
    if(L<=0 || L>M->L || C<=0 || C>M->C) return(-2); //out of the maze
    if(L!=1){
        if(M->maze[L-1][C]==0) return 1; //up
    }
    if(L!=M->L){
        if(M->maze[L+1][C]==0) return 1; //down
    }
    if(C!=1){
        if(M->maze[L][C-1]==0) return 1; //left
    }
    if(C!=M->C){
    if(M->maze[L][C+1]==0) return 1; //right
    }
    return 0; //negative answer
}

/*------------------ A3 -----------------------------
 * para as coordenadas (l; c) indicar se existe algum
 * vizinho que seja célula cinzenta
-------------------------------------------------------*/
int a3(Grid *M, int L, int C){
    if(L<=0 || L>M->L || C<=0 || C>M->C) return(-2); //out of the maze
    if(L!=1){
        if(M->maze[L-1][C]>0) return 1; //up
    }
    if(L!=M->L){
        if(M->maze[L+1][C]>0) return 1; //down
    }
    if(C!=1){
        if(M->maze[L][C-1]>0) return 1; //left
    }
    if(C!=M->C){
        if(M->maze[L][C+1]>0) return 1; //right
    }
    return 0; //negative answer
}



/*------------------ A4 -----------------------------
 * para as coordenadas (l; c) indicar se existe
 * algum vizinho que seja célula negra
-------------------------------------------------------*/
int a4(Grid *M, int L, int C){
    if(L<=0 || L>M->L || C<=0 || C>M->C) return(-2); //out of the maze
     if(L!=1){
        if(M->maze[L-1][C]<0) return 1; //up
    }
    if(L!=M->L){
        if(M->maze[L+1][C]<0) return 1; //down
    }
    if(C!=1){
        if(M->maze[L][C-1]<0) return 1; //left
    }
    if(C!=M->C){
        if(M->maze[L][C+1]<0) return 1; //right
    }
    return 0; //negative answer
}


/*------------------ A5 -----------------------------
 * para as coordenadas (l; c), se forem as coordenadas
 * de uma célula cinzenta, indicar se é quebrével
-------------------------------------------------------*/
int a5(Grid *M, int L, int C) {
    if (L <= 0 || L > M->L || C <= 0 || C > M->C) return (-2); //out of the maze
    if (a1(M, L, C) <= 0) return -1; //(l; c) does not correspond to a grey cell

    if(check_up(M, L, C) == 1 && check_down(M, L, C) == 1)
        return 1;
    if(check_right(M, L, C) == 1 && check_left(M, L, C) == 1)
        return 1;

    return 0; //negative answer
}

int check_up(Grid *M, int L, int C) {
    int l; //aux variables that represent the cell on top of the given one

    l = L - 1;

    if (l <= 0 || l > M->L || C <= 0 || C > M->C) return (-2); //out of the maze
    if (M->maze[l][C] == 0) return 1; //if the cell on top of the given one is white

    return 0;
}

int check_down(Grid *M, int L, int C) {
    int l; //aux variable that represent the cell on top of the given one

    l = L + 1;

    if (l <= 0 || l > M->L || C <= 0 || C > M->C) return (-2); //out of the maze
    if (M->maze[l][C] == 0) return 1; //if the cell under the given one is white

    return 0;
}

int check_left(Grid *M, int L, int C) {
    int c; //aux variables that represent the cell on top of the given one

    c = C - 1;

    if (L <= 0 || L > M->L || c <= 0 || c > M->C) return (-2); //out of the maze
    if (M->maze[L][c] == 0) return 1; //if the cell on the left side of the given one is white

    return 0;
}

int check_right(Grid *M, int L, int C) {
    int c; //aux variables that represent the cell on top of the given one

    c = C + 1;

    if (L <= 0 || L > M->L || c <= 0 || c > M->C) return (-2); //out of the maze
    if (M->maze[L][c] == 0) return 1; //if the cell on the right side of the given one is white

    return 0;
}

/*------------------ A6 -----------------------------
 * para as coordenadas (l1; c1) e (l2; c2), se ambas
 * forem células brancas, indicar se pertencem àmesma sala
-------------------------------------------------------*/
int a6(Grid *G, int xS, int yS){
    bool visited[G->L][G->C];
    memset(visited, false, sizeof visited);
    Queue *q = QueueNew();
    qNode *s, *current;
    if(G->end[0]<=0 || G->end[0]>G->L || G->end[1]<=0 || G->end[1]>G->C) return(-2); //out of the maze
    if(xS<=0 || xS>G->L || yS<=0 || yS>G->C) return(-2); //out of the maze
    if(G->maze[xS][yS] != 0 || G->maze[G->end[0]][G->end[1]] != 0) return 0;
    // Mark the source cell as visited
    visited[xS][yS] = true;
    
    s = (qNode*) malloc(sizeof(qNode));
    if(s == NULL) exit(0);

    s->x = xS;
    s->y = yS;
    s->dist = 0;

    InsertLast(q, s);

    while(!qEmpty(q)){
        current = GetFirst(q);

        if(current->x == G->end[0] && current->y == G->end[1]){
            free(current);
            return 1; //if we got to the desired destination, return 1
        }

        //otherwise, add adjacent cells to the queue and continue
        //left:
        if(current->x > 1){
            if(G->maze[current->x -1][current->y] == 0 && !visited[current->x -1][current->y]){
                visited[current->x -1][current->y] = true;
                s = (qNode*) malloc(sizeof(qNode));
                if(s == NULL) exit(0);
                s->x = current->x -1;
                s->y = current->y;
                s->dist = current->dist + 1;
                InsertLast(q, s);
            }
        }

        //right
        if(current->x < G->L){
            if(G->maze[current->x +1][current->y] == 0 && !visited[current->x +1][current->y]){
                visited[current->x +1][current->y] = true;
                s = (qNode*) malloc(sizeof(qNode));
                if(s == NULL) exit(0);
                s->x = current->x +1;
                s->y = current->y;
                s->dist = current->dist + 1;
                InsertLast(q, s);
            }
        }

        //up
        if(current->y > 1){
            if(G->maze[current->x][current->y -1] == 0 && !visited[current->x][current->y -1]){
                visited[current->x][current->y -1] = true;
                s = (qNode*) malloc(sizeof(qNode));
                if(s == NULL) exit(0);
                s->x = current->x;
                s->y = current->y -1;
                s->dist = current->dist + 1;
                InsertLast(q, s);
            }
        }

        //down
        if(current->y < G->C){
            if(G->maze[current->x][current->y +1] == 0 && !visited[current->x][current->y +1]){
                visited[current->x][current->y +1] = true;
                s = (qNode*) malloc(sizeof(qNode));
                if(s == NULL) exit(0);
                s->x = current->x;
                s->y = current->y +1;
                s->dist = current->dist + 1;
                InsertLast(q, s);
            }
        }
        free(current);
    }
    if(q != NULL){
        free(q);
        q = NULL;
    }
    // Return 0 if destination cannot be reached
    return 0;
}