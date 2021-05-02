#include <stdio.h>
#include <stdlib.h>

struct node{
    int value;
    struct node* next;
};
typedef struct node node_t;


void printlist(node_t *head)
{
    node_t *temporary = head;

    while (temporary != NULL){
        printf("%d - ", temporary->value);
        temporary = temporary->next;
    }
    printf("\n");
}

node_t *create_new_node(int value){
    node_t *result = (node_t*) malloc(sizeof(node_t));
    result->value = value;
    result->next = NULL;
    return result;
}

node_t *insert_at_head(node_t *head, node_t *node_to_insert){
    node_to_insert->next = head;
    return node_to_insert;
}



int main()
{
    node_t *head = NULL;
    node_t *tmp;
    
    for (int i = 1; i < 10; i++){
        tmp = create_new_node(i);
        head = insert_at_head(head, tmp);
    }
    
    printlist(head);

    return 0;
}