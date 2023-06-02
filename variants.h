#ifndef VARIANTS_H_INCLUDED
#define VARIANTS_H_INCLUDED

#include "maze.h"

typedef struct _parent{
    int A;
    int B;
} Parent;

int a1(Grid *M, int L, int C);
int a2(Grid *M, int L, int C);
int a3(Grid *M, int L, int C);
int a4(Grid *M, int L, int C);
int a5(Grid *M, int L, int C);
int a6(Grid *M, int xS, int yS);

int check_up(Grid *M, int L, int C);

int check_down(Grid *M, int L, int C);

int check_left(Grid *M, int L, int C);

int check_right(Grid *M, int L, int C);

void cheapestPath(Grid *M, FILE *fOut);

void printPath(FILE *fOut, Grid *M, Parent **prev, int count, int j, int k);
#endif