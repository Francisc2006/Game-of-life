#include "f_stive+liste+arbori.h"
#include "functii_uzuale.h"

void push(Node_stack** top, Data *v) {
    Node_stack* newNode_stack = (Node_stack*)malloc(sizeof(Node_stack));
    newNode_stack->val = v;
    newNode_stack->next = *top;
    *top = newNode_stack;
}

Data* pop(Node_stack** top) {
    if (isEmpty(*top)) return NULL;
    Node_stack *temp = (*top);
    Data* aux = temp->val;
    *top = (*top)->next;
    free(temp);

    return aux;
}

int isEmpty(Node_stack* top) {
    return top == NULL;
}

void deleteList(Node_list **head) {
    Node_list *headcopy;
    while (*head != NULL) {
        headcopy = (*head)->next;
        free(*head);
        *head = headcopy;
    }
    *head = NULL;
} 

void deleteStack(Node_stack** top) {
    Node_stack* temp = NULL;
    while ((*top) != NULL) {  
        temp = *top;
        deleteList(&(*top)->val);
        *top = (*top)->next;
        free(temp);
    }
}

void printList(Node_list* head, FILE* fout) { 
    while (head != NULL) {
        fprintf(fout, " %d %d", head->l, head->c);
        head = head->next;
    }
}

void printStack(Node_stack* top, FILE* fout) {
    int i = 1;
    while (top != NULL) {
        fprintf(fout, "%d", i++);
        printList(top->val, fout);
        top = top->next;
        fprintf(fout, "\n");
    }
}

void addAtEnd(Node_list** head, int l, int c) {
    Node_list *aux = *head;
    Node_list *newNode = (Node_list*)malloc(sizeof(Node_list));
    newNode->l = l;
    newNode->c = c;
    if (*head == NULL) {
        *head = newNode;
    }
    else {
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = newNode;
        newNode->next = NULL;
    }
}

// arbori

void initTree(Node_tree **root) {
    *root = (Node_tree*)malloc(sizeof(Node_tree));
    (*root)->left = (*root)->right = NULL;
    (*root)->val = NULL;
}

void make_b_tree(Node_tree **root,  char **mat, int **mat_vec, int n, int m, int k) {
    
    if (k == 0) return;

    creare_mat_vec(mat, mat_vec, n, m);
    Node_list *head = NULL;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mat[i][j] == '+')
            {
                if (mat_vec[i][j] == 2)
                {
                    mat[i][j] = 'X';
                    addAtEnd(&head, i, j);
                }
            }
        }
    }

    (*root)->val = head;
    deleteList(&head);

    char** mat_copy = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++)
    {
        mat_copy[i] = (char*)malloc(m * sizeof(char));
    }
    copiere_matrice(mat_copy, mat, n, m);

    k--;
    if (k > 0) {
        initTree(&((*root)->left));
        initTree(&((*root)->right));
    }
    make_b_tree(&((*root)->left), mat_copy, mat_vec, n, m, k);
    copiere_matrice(mat_copy, mat, n, m);
    make_org_tree(&((*root)->right), mat_copy, mat_vec, n, m, k);

    eliberare_mat_char(mat_copy, n);
}


void make_org_tree(Node_tree **root,  char **mat, int **mat_vec, int n, int m, int k) {
    
    if (k == 0) return;
    
    creare_mat_vec(mat, mat_vec, n, m);
    
    Node_list *head = NULL;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mat[i][j] == 'X')
            {
                if (mat_vec[i][j] < 2 || mat_vec[i][j] > 3) 
                {
                    mat[i][j] = '+';
                    addAtEnd(&head, i, j);
                }
            }
            else if (mat[i][j] == '+')
            {
                if (mat_vec[i][j] == 3) 
                {
                    mat[i][j] = 'X';
                    addAtEnd(&head, i, j);
                }
            }
        }
    }

    (*root)->val = head;
    deleteList(&head);

    char** mat_copy = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++)
    {
        mat_copy[i] = (char*)malloc(m * sizeof(char));
    }

    copiere_matrice(mat_copy, mat, n, m);

    k--;
    if (k > 0) {
        initTree(&((*root)->left));
        initTree(&((*root)->right));
    }
    make_org_tree(&((*root)->right), mat_copy, mat_vec, n, m, k);
    copiere_matrice(mat_copy, mat, n, m);
    make_b_tree(&((*root)->left), mat_copy, mat_vec, n, m, k);
    
    eliberare_mat_char(mat_copy, n);
}

void preorder(Node_tree *root, char **mat, int n, int m, int index, FILE* fout) {
    if (root) {
        Node_list *head = root->val;
        if (index == 1) { //index = 1 inseamna parcurgere in stanga
            while (head != NULL) {
                mat[head->l][head->c] = 'X';
                head = head->next;
            }
        }
        if (index == 2) { //index  = 2 inseamna parcurgere in dreapta
            while (head != NULL) {
                if (mat[head->l][head->c] == '+') mat[head->l][head->c] = 'X';
                else if (mat[head->l][head->c] == 'X') mat[head->l][head->c] = '+';
                head = head->next;
            }

        }
        deleteList(&head);
        afisare_matrice(mat, n, m, fout);

        char** mat_copy = (char**)malloc(n * sizeof(char*));
        for (int i = 0; i < n; i++)
        {
            mat_copy[i] = (char*)malloc(m * sizeof(char));
        }
        copiere_matrice(mat_copy, mat, n, m);

        preorder(root->left, mat_copy, n, m, 1, fout);     
        copiere_matrice(mat_copy, mat, n, m);
        preorder(root->right, mat_copy, n, m, 2, fout);

        eliberare_mat_char(mat_copy, n);
    }
}

void free_tree(Node_tree* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    deleteList(&(root->val));
    free(root);
}