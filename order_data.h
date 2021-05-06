#include "structures.h"

#ifndef _DATA_
#define _DATA_

int high_or_low(char *word1, char *word2);
fix_t *find_country(fix_t *head, char *country);
var_t *find_date(var_t *head, int week, int year);
void alphabetical(fix_t **head);
void population(fix_t **head);
void decreasin_cases(fix_t **head, int week, int year);
void decreasin_deaths(fix_t **head, int week, int year);

#endif