#include <stdio.h>
#include <stdlib.h>

void creare_mat_vec(char** mat, int** mat_vec, int n, int m);
void citire_matrice(char** mat, int n, int m, FILE* fin);
void afisare_matrice(char** mat, int n, int m, FILE* fout);
void eliberare_mat_int(int** mat, int n);
void eliberare_mat_char(char** mat, int n);
