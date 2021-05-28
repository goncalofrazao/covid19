#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "order_data.h"
#include "new_struct.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: alpha_order
 * 
 * Arguments: fix_t *head -- head of the list to order
 * 
 * Return: head_struct.next -- head of the list ordered
 * 
 * Description: This funtion orders a list alphabetically.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

fix_t *alpha_order(fix_t *head)
{
    fix_t head_struct;             // auxiliar struct to save head
    head_struct.next = head;
    fix_t *aux1 = &head_struct;
    fix_t *aux2 = aux1->next;

    // ends funtion if list has less than 2 elements
    if(head == NULL || head->next == NULL)
        return head;
    
    // loop to go through all list
    while(aux2->next != NULL){
        if(strcmp(aux2->name, aux2->next->name) < 0){   // go next elements if elements are ordered
            aux1 = aux1->next;
        }else{                                          // change elements order if they are not ordered
            aux1->next = swap(aux2, aux2->next);
            aux1 = &head_struct;
        }
        // aux 2 points to aux 1 next struct
        aux2 = aux1->next;
    }
    return head_struct.next;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: swap
 * 
 * Arguments: fix_t *left -- left element to swap
 *            fix_t *right -- right element to swap
 * 
 * Return: right -- next of previous element
 * 
 * Description: This funtion swaps 2 elements of a list.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

fix_t *swap(fix_t *left, fix_t *right)
{
    left->next = right->next;
    right->next = left;
    return right;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: pop_order
 * 
 * Arguments: fix_t *head -- head of the list to order
 * 
 * Return: head_struct.next -- head of the list ordered
 * 
 * Description: This funtion orders a list from highest to lowest population.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

fix_t *pop_order(fix_t *head)
{
    fix_t head_struct;             // auxiliar struct to save head
    head_struct.next = head;
    fix_t *aux1 = &head_struct;
    fix_t *aux2 = aux1->next;

    // ends funtion if list has less than 2 elements
    if(head == NULL || head->next == NULL)
        return head;
    
    // loop to go through all list
    while(aux2->next != NULL){
        if(aux2->population > aux2->next->population){   // go next elements if elements are ordered by population
            aux1 = aux1->next;
        }
        // order alphabetically if population is the same
        // if alphabetical order is done
        else if(aux2->population == aux2->next->population && strcmp(aux2->name, aux2->next->name) < 0){ 
            aux1 = aux1->next;
        }
        // swap
        else{
            aux1->next = swap(aux2, aux2->next);
            aux1 = &head_struct;
        }
        // aux 2 points to aux 1 next struct
        aux2 = aux1->next;
    }
    return head_struct.next;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: inf_order
 * 
 * Arguments: fix_t *head -- head of the list to order
 *            int year -- year to compare
 *            int week -- week to compare
 * 
 * Return: head_struct.next -- head of the list ordered
 * 
 * Description: This funtion orders a list from highest to lowest 
 *              infected in a specific date.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

fix_t *inf_order(fix_t *head, int year, int week)
{
    fix_t head_struct;             // auxiliar struct to save head
    head_struct.next = head;
    fix_t *aux1 = &head_struct;
    fix_t *aux2 = aux1->next;
    var_t *aux3;
    var_t *aux4;

    // ends funtion if list has less than 2 elements
    if(head == NULL || head->next == NULL)
        return head;
    
    // loop to go through all list
    while(aux2->next != NULL){
        aux3 = find_date(aux2->var, year, week);
        aux4 = find_date(aux2->next->var, year, week);
        if(aux3->weekly_cases > aux4->weekly_cases){   // go next elements if elements are ordered by population
            aux1 = aux1->next;
        }
        // order alphabetically if population is the same
        // if alphabetical order is done
        else if(aux3->weekly_cases == aux4->weekly_cases && strcmp(aux2->name, aux2->next->name) < 0){ 
            aux1 = aux1->next;
        }
        // swap
        else{
            aux1->next = swap(aux2, aux2->next);
            aux1 = &head_struct;
        }
        // aux 2 points to aux 1 next struct
        aux2 = aux1->next;
    }
    return head_struct.next;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: dea_order
 * 
 * Arguments: fix_t *head -- head of the list to order
 *            int year -- year to compare
 *            int week -- week to compare
 * 
 * Return: head_struct.next -- head of the list ordered
 * 
 * Description: This funtion orders a list from highest to lowest 
 *              deaths in a specific date.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

fix_t *dea_order(fix_t *head, int year, int week)
{
    fix_t head_struct;             // auxiliar struct to save head
    head_struct.next = head;
    fix_t *aux1 = &head_struct;
    fix_t *aux2 = aux1->next;
    var_t *aux3;
    var_t *aux4;

    // ends funtion if list has less than 2 elements
    if(head == NULL || head->next == NULL)
        return head;
    
    // loop to go through all list
    while(aux2->next != NULL){
        aux3 = find_date(aux2->var, year, week);
        aux4 = find_date(aux2->next->var, year, week);
        if(aux3->weekly_deaths > aux4->weekly_deaths){   // go next elements if elements are ordered by population
            aux1 = aux1->next;
        }
        // order alphabetically if population is the same
        // if alphabetical order is done
        else if(aux3->weekly_deaths == aux4->weekly_deaths && strcmp(aux2->name, aux2->next->name) < 0){ 
            aux1 = aux1->next;
        }
        // swap
        else{
            aux1->next = swap(aux2, aux2->next);
            aux1 = &head_struct;
        }
        // aux 2 points to aux 1 next struct
        aux2 = aux1->next;
    }
    return head_struct.next;
}
