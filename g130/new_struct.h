#ifndef __NEW_STRUCT__
#define __NEW_STRUCT__

#include "structures.h"

/* This function goes through all list elements to check if there is already a struct in the list for the country */
fix_t *find_country(fix_t *head, char *country);
/* This funtion creates a struct for a country. */
fix_t *create_country(char *name, char *initials, char *continent, unsigned long population);
/* This function puts head pointing to struct to insert, and next of struct to insert pointing into old head. */
fix_t *insert_fix(fix_t *aux, fix_t *head);
/* This function goes through all list elements to check if there is already a struct in the list for the date */
var_t *find_date(var_t *head, int year, int week);
/* This funtion creates a struct for a date. */
var_t *create_date(int year, int week, char *indicator, int weekly_count, double rate_14_day, int cumulative_count);
/* This funtion updates data of a date. */
void update_date(var_t *aux, char *indicator, int weekly_count, double rate_14_day, int cumulative_count);
/* This function puts head pointing to struct to insert, and next of struct to insert pointing into old head. */
var_t *insert_var(var_t *aux, var_t *head);

#endif