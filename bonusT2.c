#include "functii_uzuale.h"
#include "f_structuri.h"
#include <string.h>
#include <stdlib.h>

#define MAX_LINIE 1024

int main(int argc, const char* argv[]) {

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
    int k, n, m;
    char linie[MAX_LINIE];
    fscanf(fin,"%d%d%d", &k, &n, &m);
    fgetc(fin);

    //alocare dinamica matrice
    char** mat = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++)
    {
        mat[i] = (char*)malloc(m * sizeof(char));
    }

    citire_matrice(mat, n, m, fin);

    Node_stack* stackTop = NULL;
    for (int i = 0; i <= k; i++) {
        Node_list* head = NULL;
        fgets(linie, MAX_LINIE, fin); //citesc toata linia
        
        char *p;
        int lin, col;
        int ok = 0;
        p = strtok(linie," \n");
        while (p != NULL) { //separa fiecare numar
            int coordonata = atoi(p); // converteste un numar din char in int 
            if (ok == 0) {
                lin = coordonata;
                ok = 1;
            }
            else if (ok == 1) {
                col = coordonata;
                addAtEnd(&head, lin, col);
                ok = 0;
            }
            p = strtok(NULL, " \n");
        }
        Node_list* copie = copieLista(head);
        push(&stackTop, copie);
        deleteList(&head);
    }


    Node_stack* top = stackTop;
    while (top != NULL) {        
        Node_list* head = top->val;
        while (head != NULL) {
            if (mat[head->l][head->c] == '+') mat[head->l][head->c] = 'X';
            else if (mat[head->l][head->c] == 'X') mat[head->l][head->c] = '+';
            head = head->next;
        }
        deleteList(&head);
        top = top->next;
        
    }
    deleteStack(&stackTop);

    afisare_matrice(mat, n, m, fout);

    eliberare_mat_char(mat, n);
    fclose(fin);
    fclose(fout);
    
    return 0;
}