#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
            mat_vec[i][j] = nr_vecini; //initializare element matrice cu numarul de vecnin vii
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
            while (c == '\n');
            mat[i][j] = c;
        }
    }
}

void afisare(char** mat, int n, int m, FILE* fout)
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

int main(int argc, const char* argv[])
{
    // deschidere fisiere
    FILE* fin;
    if ((fin = fopen(argv[1],"rt")) == NULL)
    {
        puts("Fisierul input nu a putut fi deschis \n");
        exit(1);
    }

    FILE* fout;
    if ((fout = fopen(argv[2],"wt")) == NULL)
    {
        puts("Fisierul output nu a putut fi deschis \n");
        exit(1);
    }

    // citire date de intrare
    int t, n, m, k;
    fscanf(fin, "%d%d%d%d", &t, &n, &m, &k);

    //alocare dinamica matrici
    char** mat = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++)
    {
        mat[i] = (char*)malloc(m * sizeof(char));
    }

    int** mat_vec = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        mat_vec[i] = (int*)malloc(m * sizeof(int));
    }

    // citire elemente matrice din fisier
    citire_matrice(mat, n, m, fin);

    afisare(mat, n, m, fout); // afisare matrice initiala

    for (int l = 1; l <= k; l++)
    {
        creare_mat_vec(mat, mat_vec, n, m);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                //verificare conditii game of life
                if (mat[i][j] == 'X')
                {
                    if (mat_vec[i][j] < 2 || mat_vec[i][j] > 3)
                        mat[i][j] = '+';
                }
                else if (mat[i][j] == '+')
                {
                    if (mat_vec[i][j] == 3)
                        mat[i][j] = 'X';
                }
            }
        }
        afisare(mat, n, m, fout);
    }

    // eliberare spatiu de memorie
    for (int i = 0; i < n; i++)
    {
        free(mat[i]);
    }
    free(mat);

    for (int i = 0; i < n; i++)
    {
        free(mat_vec[i]);
    }
    free(mat_vec);

    // inchidere fisiere
    fclose(fin);
    fclose(fout);

    return 0;
}


