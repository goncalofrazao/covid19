#ifndef __RESTRICT_DATA__
#define __RESTRICT_DATA__

#include "structures.h"

/* This funtion removes a fix struct from list */
void remove_fix(fix_t *aux);
/* This funtion removes a var struct from list */
void remove_var(var_t *to_remove);
/* This funtion removes from the list every country that does not respect the minimum population */
fix_t *min_pop(fix_t *head, int n);
/* This funtion removes from the list every country that does not respect the maximum population */
fix_t *max_pop(fix_t *head, int n);
/* This funtion removes all weeks that are not between 2 weeks of input. If the highest and the lowest weeks are the same, it restricts all countries to that week */
void restrict_weeks(fix_t *head, int min_week, int min_year, int max_week, int max_year);
/* This funtion checks if the week is in the period of time to restrict */
int check_week(int year, int week, int min_week, int min_year, int max_week, int max_year);


#endif
