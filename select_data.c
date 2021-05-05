#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"

var_t *max_cases(var_t *head)
{
    var_t *tmp = head;
    var_t *aux;
    do
    {
        aux = tmp->next;
        if (tmp->weekly_cases > head->weekly_cases)
        {
            tmp->next = head;
            head = tmp;
        }
        tmp = aux;
    } while (tmp != NULL);
    return head;
}

var_t *max_deaths(var_t *head)
{
    var_t *tmp = head;
    var_t *aux;
    do
    {
        aux = tmp->next;
        if (tmp->weekly_deaths > head->weekly_deaths)
        {
            tmp->next = head;
            head = tmp;
        }
        tmp = aux;
    } while (tmp != NULL);
    return head;
}

var_t *max_cases_rate(var_t *head)
{
    var_t *tmp = head;
    var_t *aux;
    do
    {
        aux = tmp->next;
        if (tmp->racio_cases > head->racio_cases)
        {
            tmp->next = head;
            head = tmp;
        }
        tmp = aux;
    } while (tmp != NULL);
    return head;
}

var_t *max_deaths_rate(var_t *head)
{
    var_t *tmp = head;
    var_t *aux;
    do
    {
        aux = tmp->next;
        if (tmp->racio_deaths > head->racio_deaths)
        {
            tmp->next = head;
            head = tmp;
        }
        tmp = aux;
    } while (tmp != NULL);
    return head;
}