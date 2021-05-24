#ifndef __SELECT_DATA__
#define __SELECT_DATA__

#include "structures.h"

void print_secondary(var_t *head);

void inf_select(fix_t *country);
var_t *put_in_head(var_t *aux1, var_t *head);
void free_list(var_t *to_free);
void dea_select(fix_t *country);
void ratioinf_select(fix_t *country);
void ratiodea_select(fix_t *country);

#endif