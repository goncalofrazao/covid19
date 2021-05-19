#ifndef __SELECT_DATA__
#define __SELECT_DATA__

#include "structures.h"

void inf_select(fix_t *country);
var_t *put_in_head(var_t *aux1);
void free_list(var_t *to_free);
void dea_select(fix_t *country);
void ratioinf_select(fix_t *country);
void ratiodea_select(fix_t *country);

#endif