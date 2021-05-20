#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "restrict_data.h"
#include "structures.h"

void remove_struct(fix_t *aux)
{
    aux->next = aux->next->next;
    free(aux->next);
}

fix_t *min_pop(fix_t *head, int n)
{
    int i = 0;
    fix_t list_head;
    list_head.next = head;
    fix_t *aux1 = &list_head;
    while(aux1->next != NULL){
        if(aux1->next->population < (n * 1000))
            remove_struct(aux1);
        if(aux1->next != NULL)
            aux1 = aux1->next;
        printf("%d -- %x -- %s\n", i, aux1, aux1->name);
        i++;
    }
    return list_head.next;
}
