#ifndef __CONSOLE__
#define __CONSOLE__

#include "structures.h"

/* This function identifies the pointer to the input filename */
char *get_input_file_name(int argc, char **argv);
/* This function identifies the pointer to the output filename */
char *get_ouput_file_name(int argc, char **argv);
/* This function identifies the pointer to the string after -L */
char *get_L(int argc, char **argv);
/* This function gets the S option and checks if it is valid */
order_data get_S(int argc, char **argv, int *year, int *week);
/* This function gets the D option and checks if it is valid */
select_data get_D(int argc, char **argv);
/* This function gets the P option and checks if it is valid */
restrict_data get_P(int argc, char **argv, int *n, int *year, int *week, int *max_year, int *max_week);
/* This function checks if date 1 is earlier than date 2 */
int check_dates(int year1, int week1, int year2, int week2);
/* This function changes 2 dates */
void change_dates(int *year1, int *week1, int *year2, int *week2);
/* This function prints help msg and exit program */
void console_error();

#endif