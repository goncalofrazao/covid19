#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "select_data.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: inf_select
 * 
 * Arguments: fix_t *country -- pointer to the country to select the
 *                              week with most cases.
 * 
 * Return: no return
 * 
 * Description: This function puts in the head of a country the week 
 *              with the most cases and libert all memory allocated
 *              for other weeks.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void inf_select(fix_t *country)
{
    var_t list_head;
    list_head.next = country->var;
    var_t *aux1 = country->var;
    var_t *saver = &list_head;
    //printf("getting in\n");
    // find the week with most cases
    if(aux1->next != NULL){
        while(aux1->next != NULL){
            if(aux1->next->weekly_cases > saver->next->weekly_cases){
                saver = aux1;
            }
            aux1 = aux1->next;
        }
        // put the week with most cases in head of the list of dates
        country->var = put_in_head(saver);
        // free all other dates
        free_list(country->var->next);
        country->var->next = NULL;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: put_in_head
 * 
 * Arguments: var_t *aux1 -- pointer to the element of the list before
 *                           the week to put in head
 * 
 * Return: aux2 -- the pointer to the week with most cases
 * 
 * Description: This function removes the week with most cases from the
 *              list.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

var_t *put_in_head(var_t *aux1)
{
    var_t *aux2 = aux1->next;
    // remove element of the list
    aux1->next = aux1->next->next;
    return aux2;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: free_list
 * 
 * Arguments: var_t *aux1 -- pointer to the first element of the list
 *                           to libert.
 * 
 * Return: no return
 * 
 * Description: This function liberts fully a list
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void free_list(var_t *to_free)
{
    var_t *aux1;
    while(to_free != NULL){
        aux1 = to_free->next;
        free(to_free);
        to_free = aux1;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: dea    _select
 * 
 * Arguments: fix_t *country -- pointer to the country to select the
 *                              week with most deaths.
 * 
 * Return: no return
 * 
 * Description: This function puts in the head of a country the week 
 *              with the most deaths and libert all memory allocated
 *              for other weeks.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void dea_select(fix_t *country)
{
    var_t list_head;
    list_head.next = country->var;
    var_t *aux1 = country->var;
    var_t *saver = &list_head;
    //printf("getting in\n");
    // find the week with most cases
    if(aux1->next != NULL){
        while(aux1->next != NULL){
            if(aux1->next->weekly_deaths > saver->next->weekly_deaths){
                saver = aux1;
            }
            aux1 = aux1->next;
        }
        // put the week with most cases in head of the list of dates
        country->var = put_in_head(saver);
        // free all other dates
        free_list(country->var->next);
        country->var->next = NULL;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: ratioinf_select
 * 
 * Arguments: fix_t *country -- pointer to the country to select the
 *                              week with most deaths.
 * 
 * Return: no return
 * 
 * Description: This function puts in the head of a country the week 
 *              with the most ratio of infected and libert all memory
 *              allocated for other weeks.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void ratioinf_select(fix_t *country)
{
    var_t list_head;
    list_head.next = country->var;
    var_t *aux1 = country->var;
    var_t *saver = &list_head;
    //printf("getting in\n");
    // find the week with most cases
    if(aux1->next != NULL){
        while(aux1->next != NULL){
            if(aux1->next->rate_cases > saver->next->rate_cases){
                saver = aux1;
            }
            aux1 = aux1->next;
        }
        // put the week with most cases in head of the list of dates
        country->var = put_in_head(saver);
        // free all other dates
        free_list(country->var->next);
        country->var->next = NULL;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: ratiodea_select
 * 
 * Arguments: fix_t *country -- pointer to the country to select the
 *                              week with most deaths.
 * 
 * Return: no return
 * 
 * Description: This function puts in the head of a country the week 
 *              with the most ratio of deaths and libert all memory
 *              allocated for other weeks.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void ratiodea_select(fix_t *country)
{
    var_t list_head;
    list_head.next = country->var;
    var_t *aux1 = country->var;
    var_t *saver = &list_head;
    //printf("getting in\n");
    // find the week with most cases
    if(aux1->next != NULL){
        while(aux1->next != NULL){
            if(aux1->next->rate_deaths > saver->next->rate_deaths){
                saver = aux1;
            }
            aux1 = aux1->next;
        }
        // put the week with most cases in head of the list of dates
        country->var = put_in_head(saver);
        // free all other dates
        free_list(country->var->next);
        country->var->next = NULL;
    }
}