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

void restrict_weeks(fix_t *head, int min_week, int min_year, int max_week, int max_year)
{
    // create auxiliar struct
    var_t *aux1;
    var_t *save;
    while(head != NULL){
		aux1 = init_auxiliar_struct(head->var);
		save = aux1;
		while(aux1->next != NULL){
			if(check_week(aux1->next->year, aux1->next->week, min_week, min_year, max_week, max_year) == -1)
				remove_var(aux1);
			else
				aux1 = aux1->next;
		}
		head->var = save->next;
		head=head->next;
	}
}

int check_week(int year, int week, int min_week, int min_year, int max_week, int max_year)
{
    if(year < min_year || year > max_year){
        return -1;
    }
    if(year == min_year && week < min_week){
        return -1;
    }
    if(year == max_year && week > max_week){
        return -1;
    }
    return 1;
}
