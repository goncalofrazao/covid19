#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "restrict_data.h"
#include "structures.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: remove_struct
 * 
 * Arguments: fix_t *to_remove -- pointer to the previous struct of 
 *                                struct to remove
 * 
 * Return: no return
 * 
 * Description: This funtion removes a struct from list
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void remove_struct(fix_t *to_remove)
{
    // save struct to free
    fix_t *aux = to_remove->next;
    // remove struct
    to_remove->next = to_remove->next->next;
    // libert memory of struct
    free(aux);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: min_pop
 * 
 * Arguments: fix_t *head -- head of list to restrict
 *            int n -- minimum number of population in thousands
 * 
 * Return: list_head.next -- new head of the list
 * 
 * Description: This funtion removes from the list every country that 
 *              does not respect the minimum population
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

fix_t *min_pop(fix_t *head, int n)
{
    // create an auxiliar struct in top of list
    fix_t list_head;
    list_head.next = head;
    fix_t *aux1 = &list_head;
    // loop all list
    while(aux1->next != NULL){
        // if population is not enought, remove struct
        if(aux1->next->population < (n * 1000))
            remove_struct(aux1);
        // go next struct
        if(aux1->next != NULL){
            aux1 = aux1->next;
        }
    }
    return list_head.next;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: max_pop
 * 
 * Arguments: fix_t *head -- head of list to restrict
 *            int n -- max number of population in thousands
 * 
 * Return: list_head.next -- new head of the list
 * 
 * Description: This funtion removes from the list every country that 
 *              does not respect the maximum population
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

fix_t *max_pop(fix_t *head, int n)
{
    // create an auxiliar struct in top of list
    fix_t list_head;
    list_head.next = head;
    fix_t *aux1 = &list_head;
    // loop all list
    while(aux1->next != NULL){
        // if population is too much, remove struct
        if(aux1->next->population > (n * 1000))
            remove_struct(aux1);
        // go next struct
        if(aux1->next != NULL){
            aux1 = aux1->next;
        }
    }
    return list_head.next;
}