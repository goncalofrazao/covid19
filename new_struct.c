#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "structures.h"
#include "new_struct.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: find_country
 * 
 * Arguments: fix_t *head -- pointer to the head of list of countries
 *            char *country -- country to find
 * 
 * Return: NULL if does not find the country
 *         head -- pointer to country if finds the contry
 * 
 * Description: This function goes through all list elements to check if 
 *              there is already a struct in the list for the country
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

fix_t *find_country(fix_t *head, char *country)
{
    // go through all elements of list
    while(head != NULL){
        // return pointer to element if finds the country
        if(strcmp(head->name, country) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: create_country
 * 
 * Arguments: char *name -- name of the country
 *            char *initials -- initials of the country
 *            char *continent -- continent of the country
 *            uint32_t population -- population of the country
 * 
 * Return: aux -- pointer to struct of the country
 * 
 * Description: This funtion creates a struct for a country.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

fix_t *create_country(char *name, char *initials, char *continent, unsigned long population)
{
    // allocate memory
    fix_t *aux = (fix_t*) malloc(sizeof(fix_t));
    // set parameters
    strcpy(aux->name, name);
    strcpy(aux->initials, initials);
    strcpy(aux->continent, continent);
    aux->population = population;
    // initialize nexts = NULL
    aux->next = NULL;
    aux->var = NULL;
    return aux;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: insert_fix
 * 
 * Arguments: fix_t *insert -- pointer to struct to insert in list
 *            fix_t *head -- head of the list to insert
 * 
 * Return: insert -- new head of the list
 * 
 * Description: This function puts head pointing to struct to insert,
 *              and next of struct to insert pointing into old head.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

fix_t *insert_fix(fix_t *insert, fix_t *head)
{
    insert->next = head;       // next of struct to insert points to old head
    return insert;             // return new head
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: find_date
 * 
 * Arguments: var_t *head -- pointer to the head of list of countries
 *            int year -- year of the date to find
 *            int week -- week of the date to find
 * 
 * Return: NULL if does not find the date
 *         head -- pointer to date if finds the date
 * 
 * Description: This function goes through all list elements to check if 
 *              there is already a struct in the list for the date
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

var_t *find_date(var_t *head, int year, int week)
{
    // go through all elements of list
    while(head != NULL){
        // return pointer to element if finds the date
        if(head->year == year && head->week == week)
            return head;
        head = head->next;
    }
    return NULL;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: create_date
 * 
 * Arguments: int year -- year of the date
 *            int week -- week of the date
 *            char *indicator -- the information to update (deaths vs cases)
 *            int weekly_count -- weekly count about the indicator
 *            double rate_14_day -- rate of last 14 days about the indicator
 *            int cumulative_count -- cumulative count of the indicator
 * 
 * Return: aux -- pointer to struct of the date
 * 
 * Description: This funtion creates a struct for a date.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

var_t *create_date(int year, int week, char *indicator, int weekly_count, double rate_14_day, int cumulative_count)
{
    // allocate memory for the struct
    var_t *aux = (var_t*) malloc(sizeof(var_t));
    // set global stats
    aux->week = week;
    aux->year = year;
    aux->next = NULL;
    if(strcmp(indicator, "cases") == 0){        // set cases stats
        aux->cases = 1;
        aux->deaths = 0;
        aux->weekly_cases = weekly_count;
        aux->rate_cases = rate_14_day;
        aux->cumulative_cases = cumulative_count;
    }else{                                      // set deaths stats
        aux->deaths = 1;
        aux->cases = 0;
        aux->weekly_deaths = weekly_count;
        aux->rate_deaths = rate_14_day;
        aux->cumulative_deaths = cumulative_count;
    }
    return aux;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: update_date
 * 
 * Arguments: var_t *aux -- struct to update
 *            char *indicator -- the information to update (deaths vs cases)
 *            int weekly_count -- weekly count about the indicator
 *            double rate_14_day -- rate of last 14 days about the indicator
 *            int cumulative_count -- cumulative count of the indicator
 * 
 * Return: no return
 * 
 * Description: This funtion updates data of a date.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void update_date(var_t *aux, char *indicator, int weekly_count, double rate_14_day, int cumulative_count)
{
    if(strcmp(indicator, "cases") == 0){        // update cases stats
        aux->weekly_cases = weekly_count;
        aux->rate_cases = rate_14_day;
        aux->cumulative_cases = cumulative_count;
        aux->cases = 1;
    }
    else{                                      // update deaths stats
        aux->weekly_deaths = weekly_count;
        aux->rate_deaths = rate_14_day;
        aux->cumulative_deaths = cumulative_count;
        aux->deaths = 1;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funtion name: insert_var
 * 
 * Arguments: var_t *insert -- pointer to struct to insert in list
 *            var_t *head -- head of the list to insert
 * 
 * Return: insert -- new head of the list
 * 
 * Description: This function puts head pointing to struct to insert,
 *              and next of struct to insert pointing into old head.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

var_t *insert_var(var_t *insert, var_t *head)
{
    insert->next = head;       // next of struct to insert points to old head
    return insert;             // return new head
}
