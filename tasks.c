#include "tasks.h"
#include "functii_uzuale.h"
#include "f_structuri.h"


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
        Node_list* copie = copieLista(head);
        push(&stackTop, copie);
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

void task_3(FILE* fin, FILE* fout, char** mat, int** mat_vec, int n, int m, int k) {

    // initializare arbore
    Node_tree *root = NULL;
    root = (Node_tree*)malloc(sizeof(Node_tree));
    root->left = root->right = NULL;
    root->val = NULL;

    //initilaizare lista
    Node_list *head_root = NULL;

    //creare lista noduri pentru radacina arborelui
    for (int i = 0; i  < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == 'X') {
                addAtEnd(&head_root, i, j);
            }
        }
    }
    root->val = head_root;

    char** mat_copy = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++)
    {
        mat_copy[i] = (char*)malloc(m * sizeof(char));
    }

    copiere_matrice(mat_copy, mat, n, m);
    initTree(&(root->left));
    initTree(&(root->right));
    make_b_tree(&(root->left), mat_copy, mat_vec, n, m, k);
    copiere_matrice(mat_copy, mat, n, m);
    make_org_tree(&(root->right), mat_copy, mat_vec, n, m, k);

    copiere_matrice(mat_copy, mat, n, m);
    afisare_matrice(mat, n, m, fout);
    int task = 3;
    preorder(root->left, mat_copy, mat_vec, n, m, 1, fout, task);
    copiere_matrice(mat_copy, mat, n, m);
    preorder(root->right, mat_copy, mat_vec, n, m, 2, fout, task);

    eliberare_mat_char(mat_copy, n);
    free_tree(root);
}

void task_4(FILE* fin, FILE* fout, char** mat, int** mat_vec, int n, int m, int k) {
    // initializare arbore
    Node_tree *root = NULL;
    root = (Node_tree*)malloc(sizeof(Node_tree));
    root->left = root->right = NULL;
    root->val = NULL;

    //initilaizare lista
    Node_list *head_root = NULL;

    //creare lista noduri pentru radacina arborelui
    for (int i = 0; i  < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == 'X') {
                addAtEnd(&head_root, i, j);
            }
        }
    }
    root->val = head_root;

    char** mat_copy = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++)
    {
        mat_copy[i] = (char*)malloc(m * sizeof(char));
    }
    copiere_matrice(mat_copy, mat, n, m);
    initTree(&(root->left));
    initTree(&(root->right));
    make_b_tree(&(root->left), mat_copy, mat_vec, n, m, k);
    copiere_matrice(mat_copy, mat, n, m);
    make_org_tree(&(root->right), mat_copy, mat_vec, n, m, k);

    copiere_matrice(mat_copy, mat, n, m);
    int task = 4;
    rezolva_t4(mat_copy, mat_vec, n, m, fout);
    preorder(root->left, mat_copy, mat_vec, n, m, 1, fout, task);
    copiere_matrice(mat_copy, mat, n, m);
    preorder(root->right, mat_copy, mat_vec, n, m, 2, fout, task);

    eliberare_mat_char(mat_copy, n);
    free_tree(root);
}