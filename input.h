#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "structures.h"

#define MAXLEN 1000

/* This function reads the input file name */
fix_t *read_input(char *what_to_read, char *filename);
/* This function creates a .csv file with the data from the structures */
void output(fix_t *head, char *filename);
/* This function creates a .dat binary file with the data from the structures */
void binary_output(fix_t *head, char *filename);
/* This function reads the .dat input file */
fix_t *binary_input(char *filename);
/* This function counts the number of var_t type structures */
int count_var(var_t *head);
/* This function counts the number of fix_t type structures */
int count_fix(fix_t *head);
/* Checks if string only has characters from a to z, A to Z or space. If it doesn't, it ends the program */
void check_string(char *check, fix_t *head);
/* Checks if string only has numbers. If it doesn't, it ends the program */
void check_int(char *check, fix_t *head);
/* Checks if string only has numbers and one '.'. If it doesn't, it ends the program */
void check_float(char *check, fix_t *head);
/* Counts the number of commas in the string. If the number is different than 8, it ends the program */
void check_line(char *line, fix_t *head);
/* Check if string only has number and one '-'. If it doesn't, it ends the program */
void check_date(char *date, fix_t *head);
/* Check if string is different than "cases" and "deaths" it ends the program */
void check_indicator(char *indicator, fix_t *head);
/* Prints error message and ends program */
void read_error();
/* This function liberts fully a list */
void free_full_list(fix_t *head);

#endif // INPUT_H_INCLUDED
