#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Elem_list{
    int l, c;
    struct Elem_list* next;
};

typedef struct Elem_list Node_list;

typedef Node_list Data;
struct Elem_stack{
    Data* val;
    struct Elem_stack * next ;
};
typedef struct Elem_stack Node_stack;

struct Elem_tree{
    Data* val;
    struct Elem_tree *left, *right ;
};
typedef struct Elem_tree Node_tree;

typedef struct {
    int V; //numar de nodiri
    int E; //numar de muchii
    int **a;
}Graph;


//stive
void push(Node_stack** top, Data *v);
Data* pop(Node_stack** top);
int isEmpty(Node_stack* top);
void deleteStack(Node_stack** top);
void printStack(Node_stack* top, FILE* fout);

//liste
void addAtEnd(Node_list** head, int l, int c);
void printList(Node_list* head, FILE* fout);
Node_list* copieLista(Node_list* head);
void deleteList(Node_list **head);

//arbori
void initTree(Node_tree **root);
void make_b_tree(Node_tree **root,  char **mat, int **mat_vec, int n, int m, int k);
void make_org_tree(Node_tree **root,  char **mat, int **mat_vec, int n, int m, int k);
void preorder(Node_tree *root, char **mat, int **mat_vec, int n, int m, int index, FILE* fout, int task);
void free_tree(Node_tree* root);

//grafuri
void DFS_scan(Graph *g, int *visited, int i, int *comp, int comp_id);
void DFS(Graph *g, int *comp, int *nr_comp_conexe);
int hamPath(Graph g, int pos, int *component, int nr_noduri, int *path, int *visited);

void rezolva_t4(char **mat, int **mat_vec, int n, int m, FILE* fout);
