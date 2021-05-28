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
    var_t *aux1 = country->var;
    // create auxiliar struct
    var_t *saver = init_auxiliar_struct(country->var);
    // just put in head if list has more than 1 struct
    if(aux1->next != NULL){
        // find the week with most cases
        while(aux1->next != NULL){
            // if it finds one struct with more cases, saves it in saver
            if(aux1->next->weekly_cases > saver->next->weekly_cases){
                saver = aux1;
            }
            aux1 = aux1->next;
        }
        // put the week with most cases in head of the list of dates
        country->var = put_in_head(saver, country->var);
        // free all other dates
        free_list(country->var->next);
        // no deaths to output
        country->var->deaths = 0;
        country->var->next = NULL;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: put_in_head
 * 
 * Arguments: var_t *aux1 -- pointer to the element of the list before
 *                           the week to put in head
 * 
 * Return: aux2 -- the pointer to the new head
 * 
 * Description: This function removes the next struct of input and puts
 *              it in head
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

var_t *put_in_head(var_t *to_put, var_t *head)
{
    // save struct to put in head
    var_t *aux1 = to_put->next;
    // if struct to put in head is not the struct that is already in the head
    if (aux1 != head){
        // remove element of the middle of the list
        to_put->next = to_put->next->next;
        // struct to put in the head points to the old head
        aux1->next = head;
    }
    // return the new head of list
    return aux1;
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
    // loop all list
    while(to_free != NULL){
        // save next struct to free
        aux1 = to_free->next;
        // free struct
        free(to_free);
        // set next struct to free
        to_free = aux1;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: dea_select
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
    var_t *aux1 = country->var;
    // create auxiliar struct
    var_t *saver = init_auxiliar_struct(country->var);
    // just put in head if list has more than 1 struct
    if(aux1->next != NULL){
        // find the week with most deaths
        while(aux1->next != NULL){
            // if it finds one struct with more deaths, saves it in saver
            if(aux1->next->weekly_deaths > saver->next->weekly_deaths){
                saver = aux1;
            }
            aux1 = aux1->next;
        }
        // put the week with most cases in head of the list of dates
        country->var = put_in_head(saver, country->var);
        // free all other dates
        free_list(country->var->next);
        // no cases to output
        country->var->cases = 0;
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
    var_t *aux1 = country->var;
    // create auxiliar struct
    var_t *saver = init_auxiliar_struct(country->var);
    if(aux1->next != NULL){
        // find the week with most ratio of cases
        while(aux1->next != NULL){
            // if it finds one struct with more ratio of cases, saves it in saver
            if(aux1->next->rate_cases > saver->next->rate_cases){
                saver = aux1;
            }
            aux1 = aux1->next;
        }
        // put the week with most ratio of cases in head of the list of dates
        country->var = put_in_head(saver, country->var);
        // free all other dates
        free_list(country->var->next);
        // no deaths to output
        country->var->deaths = 0;
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
    var_t *aux1 = country->var;
    // create auxiliar struct
    var_t *saver = init_auxiliar_struct(country->var);
    if(aux1->next != NULL){
        // find the week with most ratio of deaths
        while(aux1->next != NULL){
            // if it finds one struct with more ratio of deaths, saves it in saver
            if(aux1->next->rate_deaths > saver->next->rate_deaths){
                saver = aux1;
            }
            aux1 = aux1->next;
        }
        // put the week with most ratio of deaths in head of the list of dates
        country->var = put_in_head(saver, country->var);
        // free all other dates
        free_list(country->var->next);
        // no deaths to output
        country->var->cases = 0;
        country->var->next = NULL;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: init_auxiliar_struct
 * 
 * Arguments: var_t *head -- pointer to the head of the list where it is
 *                           supposed to create an auxiliar struct
 * 
 * Return: &aux_struct -- pointer to the new auxiliar struct
 * 
 * Description: This funtion creates an auxiliar struct and puts it 
 *              pointing to the head of the list.
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

var_t *init_auxiliar_struct(var_t *head)
{
    // create a struct of type var
    static var_t aux_struct;
    // put the struct pointing to the head
    aux_struct.next = head;
    // return a pointer to auxiliar struct
    return &aux_struct;
}
