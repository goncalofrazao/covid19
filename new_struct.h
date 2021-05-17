#ifndef __NEW_STRUCT__
#define __NEW_STRUCT__

#include "structures.h"

fix_t *find_country(fix_t *head, char *country);
fix_t *create_country(char *name, char *initials, char *continent, unsigned long population);
fix_t *insert_fix(fix_t *aux, fix_t *head);
var_t *find_date(var_t *head, int year, int week);
var_t *create_date(int year, int week, char *indicator, int weekly_count, double rate_14_day, int cumulative_count);
void update_date(var_t *aux, char *indicator, int weekly_count, double rate_14_day, int cumulative_count);
var_t *insert_var(var_t *aux, var_t *head);

#endif