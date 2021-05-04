#include "structures.h"

#ifndef _NEW_STRUCT_
#define _NEW_STRUCT_

fix_t *create_new_fix(char *country, char *initials, char *continent, long population);
var_t *create_new_var(int week, int year, char *indicator, int weekly_count, float rate_14_day, int cumulative_count);
fix_t *insert_at_head_fix(fix_t *head, fix_t *fix_to_insert);
var_t *insert_at_head_var(var_t *head, var_t *var_to_insert);
void update_struct_cases(var_t *point, int weekly_count, float rate_14_day, int cumulative_count);
void update_struct_deaths(var_t *point, int weekly_count, float rate_14_day, int cumulative_count);

#endif