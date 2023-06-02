#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <stdio.h>

typedef struct {
    int L;
    int C;
    int *end;
    int **maze;
} Grid;


void verifiesArguments(int argc, char *argv[]);

Grid *createMaze(int L, int C);

void deleteMaze(Grid *M);

void fillMaze(Grid *M, FILE *fIn);

FILE *openfOut(char *nomeIn);

FILE *openIn(char *name);

#endif