#include "functii_uzuale.h"
#include "tasks.h"

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

    //efectuare taskuri
    if (t == 1) {
        task_1(fin, fout, mat, mat_vec, n, m, k);
    }
    else if (t == 2) {
        task_2(fin, fout, mat, mat_vec, n, m ,k);
    }
    else if (t == 3) {
        task_3(fin, fout, mat, mat_vec, n, m ,k);
    }

    // eliberare spatiu de memorie
    eliberare_mat_char(mat, n);
    eliberare_mat_int(mat_vec, n);

    // inchidere fisiere
    fclose(fin);
    fclose(fout);

    return 0;
}


