#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "structures.h"

#define MAXLEN 1000

fix_t *read_input();
void _op(fix_t *head);
void output(fix_t *head);
void binary_output(fix_t *head);
int count_var(var_t *head);
fix_t *binary_input();

#endif // INPUT_H_INCLUDED
