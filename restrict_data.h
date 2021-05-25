#ifndef __RESTRICT_DATA__
#define __RESTRICT_DATA__

#include "structures.h"

void remove_fix(fix_t *aux);
void remove_var(var_t *to_remove);
fix_t *min_pop(fix_t *head, int n);
fix_t *max_pop(fix_t *head, int n);
void restrict_week(fix_t *head, int week, int year);
void restrict_weeks(fix_t *head, int min_week, int min_year, int max_week, int max_year);
int check_week(int year, int week, int min_week, int min_year, int max_week, int max_year);
void print_secondary(var_t *aux);

#endif