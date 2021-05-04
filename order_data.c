#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "new_struct.h"
#include "order_data.h"

int high_or_low(char *word1, char *word2){
    if(*(word1) < *(word2))
        return 1;
    else if(*(word1) > *(word2))
        return 0;
    else
        return high_or_low(++word1, ++word2);
}

fix_t *find_country(fix_t *head, char *country){
    while (head != NULL){
        if(strcmp(head->country, country) == 0){
            return head;
        }else{
            head = head->next;
        }
    }
    return NULL;
}

var_t *find_date(var_t *head, int week, int year){
    var_t *aux = head;
    while(aux != NULL){
        if(aux->week == week && aux->year == year){
            return insert_at_head_var(head, aux);
        }else{
            aux = aux->next;
        }
    }
    return NULL;
}

fix_t *alphabetical(fix_t *head){
    fix_t *aux1 = head;
    fix_t *aux2 = aux1->next;
    do{
        if(high_or_low(aux1->country, aux2->country) == 1){
            aux1 = aux2;
            aux2 = aux2->next;
        }else{
            aux1->next = aux2->next;
            if (aux2->next != NULL)
                aux2->next->previous = aux1;
            aux2->next = aux1;
            if (aux1 != head){
                aux1->previous->next = aux2;
                aux2->previous = aux1->previous;
            }else{
                head = aux2;
                aux2->previous = NULL;
            }
            aux1->previous = aux2;
            aux1 = head;
            aux2 = aux1->next;
        }
    }while(aux2 != NULL);
    return head;
}

fix_t *population(fix_t *head){
    fix_t *aux1 = head;
    fix_t *aux2 = aux1->next;
    do{
        if(aux1->population > aux2->population){
            aux1 = aux2;
            aux2 = aux2->next;
        }else{
            if(aux1->population == aux2->population && high_or_low(aux1->country, aux2->country) == 1){
                aux1 = aux2;
                aux2 = aux2->next;
            }else{
                aux1->next = aux2->next;
                if (aux2->next != NULL)
                    aux2->next->previous = aux1;
                aux2->next = aux1;
                if (aux1 != head){
                    aux1->previous->next = aux2;
                    aux2->previous = aux1->previous;
                }else{
                    head = aux2;
                    aux2->previous = NULL;
                }
                aux1->previous = aux2;
                aux1 = head;
                aux2 = aux1->next;
            }
        }
    }while(aux2 != NULL);
    return head;
}

fix_t *decreasin_cases(fix_t *head, int week, int year){
    fix_t *aux1 = head;
    fix_t *aux2 = aux1->next;
    do{
        aux1->var = find_date(aux1->var, week, year);
        aux2->var = find_date(aux2->var, week, year);
        if(aux1->var->cumulative_cases > aux2->var->cumulative_cases){
            aux1 = aux2;
            aux2 = aux2->next;
        }else{
            if( (aux1->var->cumulative_cases == aux2->var->cumulative_cases) && (high_or_low(aux1->country, aux2->country) == 1) ){
                aux1 = aux2;
                aux2 = aux2->next;
            }else{
                aux1->next = aux2->next;
                if (aux2->next != NULL)
                    aux2->next->previous = aux1;
                aux2->next = aux1;
                if (aux1 != head){
                    aux1->previous->next = aux2;
                    aux2->previous = aux1->previous;
                }else{
                    head = aux2;
                    aux2->previous = NULL;
                }
                aux1->previous = aux2;
                aux1 = head;
                aux2 = aux1->next;
            }
        }
    }while(aux2 != NULL);
    return head;
}

fix_t *decreasin_deaths(fix_t *head, int week, int year){
    fix_t *aux1 = head;
    fix_t *aux2 = aux1->next;
    do{
        aux1->var = find_date(aux1->var, week, year);
        aux2->var = find_date(aux2->var, week, year);
        if(aux1->var->cumulative_deaths > aux2->var->cumulative_deaths){
            aux1 = aux2;
            aux2 = aux2->next;
        }else{
            if( (aux1->var->cumulative_deaths == aux2->var->cumulative_deaths) && (high_or_low(aux1->country, aux2->country) == 1) ){
                aux1 = aux2;
                aux2 = aux2->next;
            }else{
                aux1->next = aux2->next;
                if (aux2->next != NULL)
                    aux2->next->previous = aux1;
                aux2->next = aux1;
                if (aux1 != head){
                    aux1->previous->next = aux2;
                    aux2->previous = aux1->previous;
                }else{
                    head = aux2;
                    aux2->previous = NULL;
                }
                aux1->previous = aux2;
                aux1 = head;
                aux2 = aux1->next;
            }
        }
    }while(aux2 != NULL);
    return head;
}
