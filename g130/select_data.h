#ifndef __SELECT_DATA__
#define __SELECT_DATA__

#include "structures.h"

/*This function puts in the head of a country the week with the most cases and libert all memory allocated for other weeks */
void inf_select(fix_t *country);
/* This function removes the next struct of input and puts it in head */
var_t *put_in_head(var_t *aux1, var_t *head);
/* This function liberts fully a list */
void free_list(var_t *to_free);
/* This function puts in the head of a country the week with the most deaths and libert all memory allocated for other weeks */
void dea_select(fix_t *country);
/* This function puts in the head of a country the week with the most ratio of infected and libert all memory allocated for other weeks */
void ratioinf_select(fix_t *country);
/* This function puts in the head of a country the week with the most ratio of deaths and libert all memory allocated for other weeks */
void ratiodea_select(fix_t *country);
/* This funtion creates an auxiliar struct and puts it pointing to the head of the list */
var_t *init_auxiliar_struct(var_t *head);

#endif
