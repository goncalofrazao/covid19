#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "structures.h"

#define MAXLEN 1000

fix_t *read_input(char *what_to_read, char *filename);
void _op(fix_t *head, char *filename);
void output(fix_t *head, char *filename);
void binary_output(fix_t *head, char *filename);
fix_t *binary_input(char *filename);
int count_var(var_t *head);
int count_fix(fix_t *head);
void check_string(char *check);
void check_int(char *check);
void check_float(char *check);
void check_line(char *line);
void check_date(char *date);
void read_error();

#endif // INPUT_H_INCLUDED
