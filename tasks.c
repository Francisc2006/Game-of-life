#include "tasks.h"
#include "functii_uzuale.h"
#include "f_stive+liste.h"

void task_1(FILE* fin, FILE* fout, char** mat, int** mat_vec, int n, int m, int k) {
    afisare_matrice(mat, n, m, fout);

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
        afisare_matrice(mat, n, m, fout);
    }
}

void task_2(FILE* fin, FILE* fout, char** mat, int** mat_vec, int n, int m, int k) {
    // initializare stiva
    Node_stack* stackTop = NULL;
    for (int l = 1; l <= k; l++)
    {
        creare_mat_vec(mat, mat_vec, n, m);
        Node_list* head = NULL;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                //verificare conditii game of life
                if (mat[i][j] == 'X')
                {
                    if (mat_vec[i][j] < 2 || mat_vec[i][j] > 3) {
                        mat[i][j] = '+';
                        addAtEnd(&head, i, j);
                    }
                }
                else if (mat[i][j] == '+')
                {
                    if (mat_vec[i][j] == 3) {
                        mat[i][j] = 'X';
                        addAtEnd(&head, i, j);
                    }
                }
            }
        }
        push(&stackTop, head);
        deleteList(&head);
    }

    //rearanjare stiva
    Node_stack *reversed = NULL;
    while(!isEmpty(stackTop)) {
        Data *val = pop(&stackTop);
        push(&reversed, val);
    }

    printStack(reversed, fout);

    //stergere stiva si liste
    deleteStack(&reversed);
}