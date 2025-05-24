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

void preorder(Node_tree *root, char **mat, int **mat_vec, int n, int m, int index, FILE* fout, int task) {
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

        if (task == 3) {
            afisare_matrice(mat, n, m, fout);
        }
        else if (task == 4) {
            rezolva_t4(mat, mat_vec, n, m, fout);
        }

        char** mat_copy = (char**)malloc(n * sizeof(char*));
        for (int i = 0; i < n; i++)
        {
            mat_copy[i] = (char*)malloc(m * sizeof(char));
        }
        copiere_matrice(mat_copy, mat, n, m);

        preorder(root->left, mat_copy, mat_vec, n, m, 1, fout, task);     
        copiere_matrice(mat_copy, mat, n, m);
        preorder(root->right, mat_copy, mat_vec, n, m, 2, fout, task);

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

//grafuri

void DFS_scan(Graph *g, int *visited, int i, int *comp, int comp_id) {
    int j;
    visited[i] = 1;
    comp[i] = comp_id;
    for (j = 0; j < g->V; j++) 
        if (g->a[i][j] == 1 && visited[j] == 0)
            DFS_scan(g, visited, j, comp, comp_id);
}

void DFS(Graph *g, int *comp, int *nr_comp_conexe) {
    int i, visited[g->V], comp_id = 0;
    for (i = 0; i < g->V; i++) visited[i] = 0;
    for (i = 0; i < g->V; i++) {
        if (visited[i] == 0) {
            comp_id ++;
            DFS_scan(g, visited, i, comp, comp_id);
        }
    }
    *nr_comp_conexe = comp_id;
}

int hamPath(Graph g, int pos, int *component, int nr_noduri, int *path, int *visited) {
    if (pos == nr_noduri) return 1;

    for (int k = 0; k < nr_noduri; k++) {
        int node = component[k];
        if (g.a[path[pos-1]][node] == 1 && visited[node] == 0) { //verific daca nodul curent are muchie catre nodul anterior si daca nu a mai fost vizitat
            path[pos] = node;
            visited[node] = 1;
            if (hamPath(g, pos + 1, component, nr_noduri, path, visited)) return 1;
            else {
                path[pos] = -1;
                visited[node] = 0;
            }
        }
    }

    return 0;
}

//task 4
void rezolva_t4(char **mat, int **mat_vec, int n, int m, FILE* fout) {
            Graph g;
            int nr_noduri = 0, suma_grade = 0;

            int** mat_graph = (int**)malloc(n * sizeof(int*)); //matricea care contine nodurile grafului
            for (int i = 0; i < n; i++)
            {
                mat_graph[i] = (int*)malloc(m * sizeof(int));
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    mat_graph[i][j] = -1;
                }
            }

            creare_mat_vec(mat, mat_vec, n, m);

            for (int i = 0; i < n; i ++) {
                for (int j = 0; j < m; j++) {
                    if (mat[i][j] == 'X') {
                        suma_grade = suma_grade + mat_vec[i][j];
                        mat_graph[i][j] = nr_noduri;
                        nr_noduri++;
                    }
                }
            }

            g.V = nr_noduri;
            g.E = suma_grade / 2;

            //declarare celule din grafic
            Cell celula[g.V];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (mat_graph[i][j] != -1) {
                        celula[mat_graph[i][j]].lin = i;
                        celula[mat_graph[i][j]].col = j;
                    }
                }
            }

            g.a = (int**)malloc((g.V) * sizeof(int*));
            for (int i = 0; i < g.V; i++)
            {
                g.a[i] = (int*)malloc((g.V) * sizeof(int));
            }

            //construire matrice de adiacenta
            const int directie_i[8] = {-1, -1, -1, 0, 0, 1, 1, 1}; //vectori cu directiile vecinilor pentu linii
            const int directie_j[8] = {-1, 0, 1, -1, 1, -1, 0, 1}; //vectori cu directiile vecinilor pentu coloane
            int lin, col;
            int nr_directii = 8;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (mat_graph[i][j] != -1) {
                        for (int p = 0 ; p < nr_directii; p++)
                        {
                            lin = i + directie_i[p];
                            col = j + directie_j[p];
                            if (lin >= 0 && lin <n && col >=0 && col < m)
                            {
                                if (mat[lin][col] == 'X')
                                {
                                    g.a[mat_graph[i][j]][mat_graph[lin][col]] = 1;
                                    g.a[mat_graph[lin][col]][mat_graph[i][j]] = 1;
                                }
                            }
                        }
                    }

                }
            }

            //determinare componente conexe;
            int comp[g.V], nr_comp_conexe = 0;
            for (int i = 0; i < g.V; i++) comp[i] = 0;
            DFS(&g, comp, &nr_comp_conexe);

            int max_length = -1;
            int max_path[g.V];
            //determinare componenta curenta
            for (int l = 1; l <= nr_comp_conexe; l++) {
                int crt_component[g.V];
                int nr_noduri = 0; //numarul de noduri din fiecare componenta
                for (int i = 0; i < g.V; i++) {
                    if (comp[i] == l) {
                        crt_component[nr_noduri] = i;
                        nr_noduri++;
                    }
                }
                
                //cautare lant hamiltonian pentru feicare componenta
                int path[nr_noduri], visited[g.V];
                for (int j = 0; j < nr_noduri; j++) {
                    path[j] = -1;
                }
                for (int j = 0; j < g.V; j++) {
                    visited[j] = 0;
                }

                path[0] = crt_component[0]; //adaugam primul nod in path
                visited[path[0]] = 1;
                int ok = hamPath(g, 1, crt_component, nr_noduri, path, visited);

                if (ok == 1) { //daca lantul incepe cu primul nod (majoritatea cazurilor)
                    if (nr_noduri > max_length) {
                        max_length = nr_noduri;
                        for (int i = 0; i < nr_noduri; i ++) max_path[i] = path[i];
                    }
                }
                else { //daca nu ...
                    visited[path[0]] = 0;
                    for (int j = 1; j < nr_noduri; j++) {
                        path[0] = crt_component[j];
                        visited[path[0]] = 1;
                        ok =  hamPath(g, 1, crt_component, nr_noduri, path, visited);
                        if (ok == 1 && nr_noduri > max_length) {
                            max_length = nr_noduri;
                            for (int i = 0; i < nr_noduri; i ++) max_path[i] = path[i];
                        }
                        visited[path[0]] = 0;
                    }
                }
            }

            if (max_length != -1) {
                fprintf(fout, "%d\n", max_length - 1);
                for (int i = 0; i < max_length; i++) {
                    fprintf(fout, "(%d,%d)", celula[max_path[i]].lin, celula[max_path[i]].col);
                    if (i != max_length - 1) fprintf(fout, " ");
                }
                fprintf(fout, "\n");
            }
            else {
                fprintf(fout, "-1\n");
            }

            eliberare_mat_int(mat_vec, n);
            eliberare_mat_int(g.a, g.V);
            eliberare_mat_int(mat_graph, n);
}

