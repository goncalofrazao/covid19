#include "structures.h"

#ifndef _DATA_
#define _DATA_

int high_or_low(char *word1, char *word2);
fix_t *find_country(fix_t *head, char *country);
var_t *find_date(var_t *head, int week, int year);
fix_t *alphabetical(fix_t *head);
fix_t *population(fix_t *head);
fix_t *decreasin(fix_t *head, int week, int year, char *indicator);

#endif