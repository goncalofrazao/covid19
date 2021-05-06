#include "structures.h"

#ifndef _RESTRICT_DATA_
#define _RESTRICT_DATA_

void remove_struct_fix(fix_t *to_remove, fix_t **head);
void remove_struct_var(var_t *to_remove, var_t **head);
void min_habitants(int n, fix_t **head);
void max_habitants(int n, fix_t **head);
void only_date(var_t **head, int year, int week);
void between_date(var_t **head, int year_max, int week_max, int year_min, int week_min);

#endif