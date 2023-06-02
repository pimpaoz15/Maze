/**********************************************
Raiders of All Pyramids

(C) Manuel Guilherme & Miguel Cardoso
Algoritmos e Estruturas de Dados, 2021
Instituto Superior Técnico
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"
#include "variants.h"
#include "minheap.h"


int main(int argc, char *argv[]) {
    FILE *fIn, *fOut;
    int L = 0, C = 0, i=0;
    //aux1=0, aux2=0, P=0, V=0;
    //char *mode;
    Grid *M;


    //verifiesArguments(argc, argv);

    fIn = fopen(argv[1], "r");
    if (fIn == NULL) exit(0); //Error opening file

    fOut = openfOut(argv[1]);


    //mode = (char *) malloc(2 * sizeof(char));
    //if (mode == NULL) exit(0);

    while (1) {
        i++;
        if(fscanf(fIn, "%d %d", &L, &C)!=2) exit(0);
        M = createMaze(L + 1, C + 1);

        if (fscanf(fIn, "%d %d", &M->end[0], &M->end[1]) == 2) {
            
            /*
            if(strcmp(mode,"A6")==0){
                if(fscanf(fIn, "%d %d", &aux1, &aux2) != 2) exit(0);
            }
            */
            if(i>1) fprintf(fOut, "\n\n");
            fillMaze(M, fIn);
            cheapestPath(M, fOut);

            /*
            if (strcmp(mode, "A1") == 0) fprintf(fOut, "%d\n\n", a1(M, M->end[0], M->end[1]));
            if (strcmp(mode, "A2") == 0) fprintf(fOut, "%d\n\n", a2(M, M->end[0], M->end[1]));
            if (strcmp(mode, "A3") == 0) fprintf(fOut, "%d\n\n", a3(M, M->end[0], M->end[1]));
            if (strcmp(mode, "A4") == 0) fprintf(fOut, "%d\n\n", a4(M, M->end[0], M->end[1]));
            if (strcmp(mode, "A5") == 0) fprintf(fOut, "%d\n\n", a5(M, M->end[0], M->end[1]));
            if (strcmp(mode, "A6")==0) fprintf(fOut, "%d\n\n", a6(M, aux1, aux2));
            */
            deleteMaze(M);
        } else break;
    }

    /* close all open files*/
    fclose(fIn);
    fclose(fOut);

    return (0);
}

/*------------------ createMaze -----------------------------
Does: Allocates a grid to serve as maze
Recieves: L, C - int that defines grid size
Returns: M - a pointer to the maze
Side-Effects: Allocates memory for the maze
-------------------------------------------------------*/
Grid *createMaze(int L, int C) {
    Grid *M;
    int i = 0;
    M = (Grid *) malloc(sizeof(Grid));
    if (M == NULL) exit(0); //Error creating maze

    M->L = L - 1;
    M->C = C - 1;

    M->end = (int *) malloc(2 * sizeof(int));
    if (M->end == NULL) exit(0);

    M->maze = (int **) malloc(sizeof(int *) * L);

    if (M->maze == NULL) exit(0);

    for (i = 0; i < L; i++) {
        M->maze[i] = (int *) calloc(C, sizeof(int));
        if (M->maze[i] == NULL) exit(0);
    }

    return M;
}


/*------------------ deleteMaze -----------------------------
Does: Eliminates a maze
Recieves: M - a grid to eliminate
Returns: void
Side-Effects: Frees all memory allocated to M
-------------------------------------------------------*/
void deleteMaze(Grid *M) {
    int i=0;
    if (M->end != NULL) free(M->end);
    M->end = NULL;

    for (i = 0; i <= M->L; i++) {
        if(M->maze[i] != NULL) free(M->maze[i]);
        M->maze[i] = NULL;
    }

    if (M->maze != NULL) free(M->maze);
    M->maze = NULL;

    if (M != NULL) free(M);
    M = NULL;

    return;
}

/*------------------ fillMaze -----------------------------
Does: reads a file and puts info in the maze
Recieves: M - a grid ro fill with info
          fpIn - a file to read from
Returns: void
Side-Effects: none
-------------------------------------------------------*/
void fillMaze(Grid *M, FILE *fpIn) {
    int L, C, V, P; //auxiliar

    //Collects number P
    if (fscanf(fpIn, "%d", &P) != 1) exit(0);

    //Reads info of the maze and puts it into the structure
    while (P != 0) {
        if (fscanf(fpIn, "%d %d %d", &L, &C, &V) != 3) exit(0);
        M->maze[L][C] = V;
        P--;
    }

    return;
}

/*------------------ verifiesArguments ---------------------
Does: verifies arguments passed
Recieves: argc, argv
Returns: void
Side-Effects: exits if args not ok
-------------------------------------------------------*/
void verifiesArguments(int argc, char *argv[]) {
    
    int aux = 0;

    if (argc != 2) exit(0); // Checks number of arguments

    //Checks file extension
    aux = strlen(argv[2]);
    if (aux < 4) exit(0);
    if (argv[2][aux - 3] != '.' && argv[2][aux - 2] != 'i' && argv[2][aux - 1] != 'n')
        exit(0);

    return;
    
}
/*------------------ openfOut ---------------------
Does: opens Out file
Recieves: nomeIn - name of the file
Returns: void
Side-Effects: opens file
-------------------------------------------------------*/
FILE *openfOut(char *nomeIn) {
    int aux = 0;
    char *nomeOut;
    FILE *fOut;

    aux = strlen(nomeIn);

    nomeOut = (char *) malloc((strlen(nomeIn) + 3) * sizeof(char));
    if (nomeOut == NULL) exit(0);

    strcpy(nomeOut, nomeIn);

    nomeOut[aux + 1] = '\0';
    nomeOut[aux] = 'l';
    nomeOut[aux - 1] = 'o';
    nomeOut[aux - 2] = 's';


    fOut = fopen(nomeOut, "w");

    free(nomeOut);

    return fOut;
}