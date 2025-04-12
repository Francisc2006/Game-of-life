#include "f_stive+liste.h"

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

  