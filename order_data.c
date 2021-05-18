#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "structures.h"
#include "order_data.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: alpha_order
 * 
 * Arguments: fix_t *head -- head of the list to order
 * 
 * Return: head -- head of the list ordered
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
        // aux 2 points to aux 1 next struct
        if(strcmp(aux2->name, aux2->next->name) > 0){   // change elements order if they are not ordered
            aux1->next = swap(aux2, aux2->next);
            aux1 = &head_struct;
        }else{                                          // go next elements
            aux1 = aux1->next;
        }
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