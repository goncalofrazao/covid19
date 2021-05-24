#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "restrict_data.h"
#include "structures.h"
#include "select_data.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: remove_fix
 * 
 * Arguments: fix_t *to_remove -- pointer to the previous struct of 
 *                                struct to remove
 * 
 * Return: no return
 * 
 * Description: This funtion removes a fix struct from list
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void remove_fix(fix_t *to_remove)
{
    // save struct to free
    fix_t *aux = to_remove->next;
    // remove struct
    to_remove->next = to_remove->next->next;
    // libert memory of struct
    free(aux);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: remove_var
 * 
 * Arguments: var_t *to_remove -- pointer to the previous struct of 
 *                                struct to remove
 * 
 * Return: no return
 * 
 * Description: This funtion removes a var struct from list
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void remove_var(var_t *to_remove)
{
    // save struct to free
    var_t *aux = to_remove->next;
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
            remove_fix(aux1);
        // go next struct
        else
            aux1 = aux1->next;
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
            remove_fix(aux1);
        // go next struct
        else
            aux1 = aux1->next;
        
    }
    return list_head.next;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: restrict_wee
 * 
 * Arguments: fix_t *head -- head of list to restrict
 *            int week -- week to restrict
 *            int year -- year of the week to restrict
 * 
 * Return: list_head.next -- new head of the list
 * 
 * Description: This funtion removes from the list all weeks of all 
 *              countries except the week that is not supposed to remove
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void restrict_week(fix_t *head, int week, int year)
{
    // create an auxiliar struct to the top of the list
    var_t list_head;
    var_t *aux1 = &list_head;
    var_t *saver;
    // loop all countries
    while(head != NULL){
        // next of auxiliar struct points to head of variable data
        list_head.next = head->var;
        // find the week
        while(aux1->next != NULL){
            if(aux1->next->week == week && aux1->next->year == year){
                saver = aux1;
                break;
            }
            aux1 = aux1->next;
        }
        // put the week in the head
        head->var = put_in_head(saver, head->var);
        // free all other dates
        free_list(head->var->next);
        head->var->next = NULL;
        head = head->next;
    }
}