#include "functii_uzuale.h"

void creare_mat_vec(char** mat, int** mat_vec, int n, int m)
{
    int i, j;
    const int directie_i[8] = {-1, -1, -1, 0, 0, 1, 1, 1}; //vectori cu directiile vecinilor pentu linii
    const int directie_j[8] = {-1, 0, 1, -1, 1, -1, 0, 1}; //vectori cu directiile vecinilor pentu coloane
    int lin, col;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            int nr_vecini = 0;
            int nr_directii = 8;
            for (int p = 0 ; p < nr_directii; p++)
            {
                lin = i + directie_i[p];
                col = j + directie_j[p];
                if (lin >= 0 && lin <n && col >=0 && col < m)
                {
                    if (mat[lin][col] == 'X')
                    {
                        nr_vecini++;
                    }
                }
            }
            mat_vec[i][j] = nr_vecini; //initializare element matrice cu numarul de vecini vii
        }
    }

}

void citire_matrice(char** mat, int n, int m, FILE* fin)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            char c;
            do
            {
                c = getc(fin);
            }
            while (c == '\n' || c == '\r' || c == ' ' || c == '\t');
            mat[i][j] = c;
        }
    }
}

void afisare_matrice(char** mat, int n, int m, FILE* fout)
{
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fprintf(fout, "%c", mat[i][j]);
        }
        fprintf(fout, "\n");
    }
    fprintf(fout, "\n");
}

void copiere_matrice(char **mat_copy, char** mat, int n, int m){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            mat_copy[i][j] = mat[i][j];
        }
    }

}


void eliberare_mat_int(int** mat, int n) {
    for (int i = 0; i < n; i++)
    {
        free(mat[i]);
    }
    free(mat);
}

void eliberare_mat_char(char** mat, int n) {
    for (int i = 0; i < n; i++)
    {
        free(mat[i]);
    }
    free(mat);
}


