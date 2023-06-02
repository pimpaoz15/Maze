/******************************************************************************
 *
 * File Name: cheapest.c
 *	      (c) Miguel Cardoso e Manuel Guilherme
 *
 * NAME
 *     Cheapest
 *
 * DESCRIPTION
 *		implements algorithm to obtain cheapest path in a maze
 *
 *****************************************************************************/


#include "maze.h"
#include "queue.h"
#include "variants.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "minheap.h"
#define INF INT_MAX


/******************************************************************************
 * LessNumo()
 *
 * Arguments: a, b - 2 Items to be compared
 * Returns: Integer with the results of the comparison
 * Side-Effects: none
 *
 * Description: Comparison function with abstract type to be passed as argument;
 *              Function is specific for Cell variables
 *
 *****************************************************************************/
int LessNum(Item a, Item b)
{
  Cell *proca = (Cell*) a;
  Cell *procb = (Cell*) b;
  int aa, bb;

  aa = proca->prio;
  bb = procb->prio;

  return (aa < bb);
}

/******************************************************************************
 * IncluiCell()
 *
 * Arguments: h - pointer to heap
 *            x, y, val - int with information of a Cell
 *             D - char that says in what way was the Cell inserted (up, down, left, right)
 * Returns: void
 * Side-Effects: none
 *
 * Description: Interface for the insert option
 *
 *****************************************************************************/
void IncluiCell(Heap *h, int x, int y, int val, char D){
  Cell *element;

    element = (Cell *) malloc(sizeof(Cell));
    element->pid_x = x;
    element->pid_y = y;
    element->prio = val;
    element->direction = D;

    insert(h, (Item) element);
  return;  
}

/********************************************************************
 * LookFor()
 * Not used
 * Returns the index of a certain Cell in the array; Looks from bottom to up
 *********************************************************************/
int LookFor(Heap *h, int index, int oldprio, int x, int y){
    if(index < 0 ) return -1;
    Cell *aux;
    aux = (Cell*) h->arr[index];
    if(index == 0 && (aux->prio != oldprio || aux->pid_x != x || aux->pid_y != y)) return -1; 
    if(aux->prio != oldprio || aux->pid_x != x || aux->pid_y != y){
      index = LookFor(h, index -1, oldprio, x, y);
    }
    return index;
};



/******************************************************************************
 * cheapestPath()
 *
 * Arguments: M - a maze
 *            fOut - out file pointer
 * 
 * Returns: void
 * Side-Effects: none
 *
 * Description: Calculates minimum cost from two cells in a maze. Inspired and
 *              adapted from Dijkstra's Algorithm.
 *
 *****************************************************************************/
void cheapestPath(Grid *M, FILE *fOut){

    //Destination out of the maze
    if (M->end[0] <= 0 || M->end[0] > M->L || M->end[1] <= 0 || M->end[1] > M->C){
            fprintf(fOut, "-1\n");
            return;
    }

    //Destination is not white cell
    if(M->maze[M->end[0]][M->end[1]] != 0){
            fprintf(fOut, "-1\n");
            return;
    }

    //Destination is the source
    if(M->end[0]==1 && M->end[1]==1){
            fprintf(fOut, "0\n");
            return;
    }

    //aux items
    int x, y, d;
    Heap *h;
    Cell *u;

    //Holds the cheapest distance from source to [x][y]
    int dist[M->L +1][M->C +1];
    for(x = 1; x <= M->L; x++){
        for(y = 1; y <= M->C; y++){
            dist[x][y] = INT_MAX;
        }
    }
    
    dist[1][1] = 0;

    //prev holds the parent of every cell in the path: useful for pathtracing
    Parent **prev;
    prev = (Parent**) malloc((M->L+1)*sizeof(Parent*));
    if(prev == NULL) exit(0);

    for(x=0; x <= M->L; x++){
        prev[x] = (Parent *) malloc((M->C + 1)*sizeof(Parent));
        for(y=0; y <= M->C; y++){
            prev[x][y].A = -1;
            prev[x][y].B = -1;
        }
    }


    //True if vertex [x][y] is included in cheapest path or cheapest distance from src to i is finalized
    bool sptSet[M->L +1][M->C +1];
    memset(sptSet, false, sizeof(sptSet));

    h = CreateHeap(M->C * M->L,0);

    //puts source in the heap 
    IncluiCell(h, 1, 1, 0, '-');

    //repeats while heap is not empty
    while(h->count != 0){

        //Get top value on minHeap
        u = PopMin(h);
        x = u->pid_x;
        y = u->pid_y;
        d = u->direction;
        free(u);

        if(a5(M, x, y) == 0) continue; //if not breakable ->co

        //updates distance from neigbour cells + puts them in the heap

        //up
        if(x != 1 && !(M->maze[x][y]>0 && d != 'U')){
            if(!sptSet[x-1][y] && M->maze[x-1][y] != -1 && (!(x==2 && M->maze[x-1][y] !=0))){
                if(dist[x][y] + M->maze[x-1][y] < dist[x-1][y]){
                    dist[x-1][y] = dist[x][y] + M->maze[x-1][y];
                    prev[x-1][y].A = x;
                    prev[x-1][y].B = y;
                }
                IncluiCell(h, x-1, y, dist[x-1][y], 'U');
                sptSet[x-1][y] = true;
            } 
        }

        //down
        if(x != M->L && !(M->maze[x][y]>0 && d != 'D')){
            if(!sptSet[x+1][y] && M->maze[x+1][y] != -1 && (!(x == (M->C-1) && M->maze[x+1][y] != 0))){
                if(dist[x][y] + M->maze[x+1][y] < dist[x+1][y]){
                    dist[x+1][y] = dist[x][y] + M->maze[x+1][y];
                    prev[x+1][y].A = x;
                    prev[x+1][y].B = y;
                }

                IncluiCell(h, x+1, y, dist[x+1][y], 'D');
                sptSet[x+1][y] = true;
            }
        }

        //left
        if(y != 1 && !(M->maze[x][y]>0 && d != 'L')){
            if(!sptSet[x][y-1] && M->maze[x][y-1] != -1 && (!(y==2 && M->maze[x][y-1] !=0))){
                if(dist[x][y] + M->maze[x][y-1] < dist[x][y-1]){
                    dist[x][y-1] = dist[x][y] + M->maze[x][y-1];
                    prev[x][y-1].A = x;
                    prev[x][y-1].B = y;
                }
                IncluiCell(h, x, y-1, dist[x][y-1], 'L');
                sptSet[x][y-1] = true;
            }
        }

        //right
        if(y != M->C && !(M->maze[x][y]>0 && d != 'R')){
            if(!sptSet[x][y+1] && M->maze[x][y+1] != -1 && (!(y== (M->C -1) && M->maze[x][y+1] != 0))){
                if(dist[x][y] + M->maze[x][y+1] < dist[x][y+1]){
                    dist[x][y+1] = dist[x][y] + M->maze[x][y+1];
                    prev[x][y+1].A = x;
                    prev[x][y+1].B = y;
                }
                IncluiCell(h, x, y+1, dist[x][y+1], 'R');
                sptSet[x][y+1] = true;
            }
        }
    }

    FreeHeap(h);

    if(dist[M->end[0]][M->end[1]] == INT_MAX){
            fprintf(fOut, "-1\n");
            return;
    }

    if(dist[M->end[0]][M->end[1]] == 0){
            fprintf(fOut, "0\n");
            return;
    }  

    fprintf(fOut, "%d\n", dist[M->end[0]][M->end[1]]);
    printPath(fOut, M, prev, 0, M->end[0], M->end[1]);

    for(x=0; x <= M->L; x++){
        if(prev[x] != NULL){
            free(prev[x]);
            prev[x] = NULL;
        }
    }
    free(prev);

    return;
}

/******************************************************************************
 * printPath()
 *
 * Arguments: M - a maze
 *            fOut - out file pointer
 *            prev - parent matrix
 *            count - keep track of broken cells
 *            j, k - destination cell coordinates
 * 
 * Returns: void
 * Side-Effects: none
 *
 * Description: Prints the path between (1,1) and (j,k), ignoring white cells
 *
 *****************************************************************************/
void printPath(FILE *fOut, Grid *M, Parent **prev, int count, int j, int k){
    
    if (prev[j][k].A == -1){
        fprintf(fOut, "%d\n", count);
        return;
    }
   
    if(M->maze[j][k] > 0) count++;
    
    printPath(fOut, M, prev, count, prev[j][k].A, prev[j][k].B);

    if(M->maze[j][k] > 0) fprintf(fOut, "%d %d %d\n", j, k, M->maze[j][k]);

}