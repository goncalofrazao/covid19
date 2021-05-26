#ifndef __CONSOLE__
#define __CONSOLE__

char *get_input_file_name(int argc, char **argv);
char *get_ouput_file_name(int argc, char **argv);
char *get_L(int argc, char **argv);
char *get_S(int argc, char **argv, int *year, int *week);
char *get_D(int argc, char **argv);
char *get_P(int argc, char **argv, int *n, int *year, int *week, int *max_year, int *max_week);
int check_dates(int year1, int week1, int year2, int week2);
void change_dates(int *year1, int *week1, int *year2, int *week2);
void console_error();

#endif