#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "restrict_data.h"
#include "structures.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: remove_struct_fix
 * 
 * Arguments: fix_t *to_remove -- pointer to list element to delete
 *            fix_t **head -- double pointer to head of the list
 * 
 * Return: none
 * 
 * Side-effects: - libert allocated memory for the list element to delete
 * 
 *               - if there is previous changes the 'next' of the element
 * before to the next of the element to delete, else puts head in next
 * 
 *               - changes the 'previous' of the next element to the
 * previous element or to NULL if there is no previous
 * 
 * Description: This function deletes a element of a list of type fix
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void remove_struct_fix(fix_t *to_remove, fix_t **head)
{
    if (to_remove->previous != NULL)
    {
        to_remove->previous->next = to_remove->next;
    }
    else
    {
        (*head) = to_remove->next;
    }
    to_remove->next->previous = to_remove->previous;
    free(to_remove);
}

void remove_struct_var(var_t *to_remove, var_t **head)
{
    if (to_remove->previous != NULL)
    {
        to_remove->previous->next = to_remove->next;
    }
    else
    {
        (*head) = to_remove->next;
    }
    to_remove->next->previous = to_remove->previous;
    free(to_remove);
}

void min_habitants(int n, fix_t **head)
{
    fix_t *aux = (*head);
    n = n * 1000;
    while (head != NULL)
    {
        if (aux->population < n)
        {
            remove_struct_fix(aux, head);
        }
    }
}

void max_habitants(int n, fix_t **head)
{
    fix_t *aux = (*head);
    n = n * 1000;
    while (head != NULL)
    {
        if (aux->population > n)
        {
            remove_struct_fix(aux, head);
        }
    }
}

void only_date(var_t **head, int year, int week)
{
    var_t *aux = (*head);
    var_t *tmp;
    while (aux != NULL)
    {
        tmp = aux->next;
        if (aux->year != year || aux->week != week)
        {
            remove_struct_var(aux, head);
        }
        aux = tmp;
    }
}

void between_date(var_t **head, int year_max, int week_max, int year_min, int week_min)
{
    var_t *aux = (*head);
    var_t *tmp;
    while (aux != NULL)
    {
        tmp = aux->next;
        if ((aux->year < year_min) || (aux->year == year_min && aux->week < week_min))
        {
            remove_struct_var(aux, head);
        }
        if ((aux->year > year_max) || (aux->year == year_max && aux->week > week_max))
        {
            remove_struct_var(aux, head);
        }
        aux = tmp;
    }
}