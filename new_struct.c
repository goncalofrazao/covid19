#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"

fix_t *create_new_fix(char *country, char *initials, char *continent, long population){
    fix_t *result = (fix_t*) malloc(sizeof(fix_t));
    strcpy(result->country, country);
    strcpy(result->initials, initials);
    strcpy(result->continent, continent);
    result->population = population;
    result->next = NULL;
    return result;
}

var_t *create_new_var(int week, int year, char *indicator, int weekly_count, float rate_14_day, int cumulative_count){
    var_t *result = (var_t*) malloc(sizeof(var_t));
    result->week = week;
    result->year = year;
    if(strcmp(indicator, "deaths") == 0){
        result->weekly_deaths = weekly_count;
        result->racio_deaths = rate_14_day;
        result->cumulative_deaths = cumulative_count;
    }else{
        result->weekly_cases = weekly_count;
        result->racio_cases = rate_14_day;
        result->cumulative_cases = cumulative_count;
    }
    result->next = NULL;
    return result;
}

fix_t *insert_at_head_fix(fix_t *head, fix_t *fix_to_insert){
    fix_to_insert->next = head;
    return fix_to_insert;
}

var_t *insert_at_head_var(var_t *head, var_t *var_to_insert){
    var_to_insert->next = head;
    return var_to_insert;
}

void update_struct_cases(var_t *point, int weekly_count, float rate_14_day, int cumulative_count){
    point->weekly_cases = weekly_count;
    point->racio_cases = rate_14_day;
    point->cumulative_cases = cumulative_count;
}

void update_struct_deaths(var_t *point, int weekly_count, float rate_14_day, int cumulative_count){
    point->weekly_deaths = weekly_count;
    point->racio_deaths = rate_14_day;
    point->cumulative_deaths = cumulative_count;
}