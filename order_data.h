#ifndef __ORDER_DATA__
#define __ORDER_DATA__

#include "structures.h"

/* This funtion orders a list alphabetically */
fix_t *alpha_order(fix_t *head);
/* This funtion swaps 2 elements of a list */
fix_t *swap(fix_t *left, fix_t *right);
/* This funtion orders a list from highest to lowest population */
fix_t *pop_order(fix_t *head);
/*This funtion orders a list from highest to lowest infected in a specific date */
fix_t *inf_order(fix_t *head, int year, int week);
/*This funtion orders a list from highest to lowest deaths in a specific date */
fix_t *dea_order(fix_t *head, int year, int week);

#endif
