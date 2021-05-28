#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "console.h"
#include "structures.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: get_input_file_name
 *
 * Arguments: int argc -- number of arguments
 *            char **argv -- arguments of command line
 *
 * Return: argv[i + 1] -- pointer to first element of string after '-i'
 *         NULL -- just to avoid warning (program ends with console_error)
 *
 * Description: This function identifies the pointer to the input filename
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

char *get_input_file_name(int argc, char **argv)
{
    // search '-i'
    for(int i = 1; i < argc; i++){
        // return pointer to string after '-i'
        if(argv[i][0] == '-' && argv[i][1] == 'i' && strlen(argv[i]) == 2)
            return argv[i + 1];
    }
    // '-o' is a must in argv
    console_error();
    return NULL;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: get_output_file_name
 *
 * Arguments: int argc -- number of arguments
 *            char **argv -- arguments of command line
 *
 * Return: argv[i + 1] -- pointer to first element of string after '-o'
 *         NULL -- just to avoid warning (program ends with console_error)
 *
 * Description: This function identifies the pointer to the output filename
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

char *get_ouput_file_name(int argc, char **argv)
{
    // search '-o'
    for(int i = 1; i < argc; i++){
        // return pointer to string after '-o'
        if(argv[i][0] == '-' && argv[i][1] == 'o' && strlen(argv[i]) == 2)
            return argv[i + 1];
    }
    // '-o' is a must in argv
    console_error();
    return NULL;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: get_L
 *
 * Arguments: int argc -- number of arguments
 *            char **argv -- arguments of command line
 *
 * Return: argv[i + 1] -- pointer to first element of string after -L          
 *         NULL -- if there is no '-L'
 *
 * Description: This function identifies the pointer to the string after -L
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

char *get_L(int argc, char **argv)
{
    // search '-L'
    for(int i = 1; i < argc; i++){
        // return pointer to string after '-L'
        if(argv[i][0] == '-' && argv[i][1] == 'L' && strlen(argv[i]) == 2){
            // check if continent is valid
            if(strcmp(argv[i + 1], "all") != 0 && strcmp(argv[i + 1], "Europe") != 0 && strcmp(argv[i + 1], "Africa") != 0 && strcmp(argv[i + 1], "Asia") != 0 && strcmp(argv[i + 1], "Oceania") != 0 && strcmp(argv[i + 1], "America") != 0){
                printf("INVALID CONTINENT\n");
                console_error();
            }
            return argv[i + 1];
        }
    }
    // if there is no '-L'
    return NULL;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: get_S
 *
 * Arguments: int argc -- number of arguments
 *            char **argv -- arguments of command line
 *            int *year -- year to get
 *            int *week -- week to get
 *
 * Return: DEA -- if option is dea
 *         INF -- if option is inf
 *         ALFA -- if option is alfa or if there is no '-S' in argv
 *         POP -- if option is pop
 *
 * Description: This function gets the S option and checks if it is
 *              valid
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

order_data get_S(int argc, char **argv, int *year, int *week)
{
    // search '-S'
    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-' && argv[i][1] == 'S' && strlen(argv[i]) == 2){
            // check option of -S and get week if it is the case
            if(strcmp(argv[i + 1], "dea") == 0){
                sscanf(argv[i + 2], "%d-%d", year, week);
                return DEA;
            }
            else if(strcmp(argv[i + 1], "inf") == 0){
                sscanf(argv[i + 2], "%d-%d", year, week);
                return INF;
            }
            else if(strcmp(argv[i + 1], "alfa") == 0){
                return ALFA;
            }
            else if(strcmp(argv[i + 1], "pop") == 0){
                return POP;
            }
            // return error if no valid input
            else{
                printf("S argument invalid\n");
                console_error();
            }
        }
    }
    // default option if there is no -S
    return ALFA;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: get_D
 *
 * Arguments: int argc -- number of arguments
 *            char **argv -- arguments of command line
 *            int *year -- year to get
 *            int *week -- week to get
 *
 * Return: SELECT_DEA -- if option is selectdea
 *         SELECT_INF -- if option is selectinf
 *         RACIOINF -- if option is racioinf
 *         RACIODEA -- if option is raciodea
 *         NO_INPUT_1 -- if there is no D option
 *
 * Description: This function gets the D option and checks if it is
 *              valid
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

select_data get_D(int argc, char **argv)
{
    // search D option
    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-' && argv[i][1] == 'D' && strlen(argv[i]) == 2){
            // check option
            if(strcmp(argv[i + 1], "inf") == 0)
                return SELECT_INF;
            else if(strcmp(argv[i + 1], "dea") == 0)
                return SELECT_DEA;
            else if(strcmp(argv[i + 1], "racioinf") == 0)
                return RACIOINF;
            else if(strcmp(argv[i + 1], "raciodea") == 0)
                return RACIODEA;
            // end if no valid option 
            else{
                printf("D argument invalid\n");
                console_error();
            }
        }
    }
    // no D option in argv
    return NO_INPUT_1;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: get_P
 *
 * Arguments: int argc -- number of arguments
 *            char **argv -- arguments of command line
 *            int *n -- pointer to number of habitants to restrict
 *            int *year -- pointer to low limit date (year) to restrict
 *            int *week -- pointer to low limit date (week) to restrict
 *            int *max_year -- pointer to up limit date (year) to restrict
 *            int *max_week -- pointer to up limit date (week) to restrict
 *
 * Return: MIN -- if option is min
 *         MAX -- if option is max
 *         DATE -- if option is date
 *         DATES -- if option is dates
 *         NO_INPUT_2 -- if there is no P option
 *
 * Description: This function gets the P option and checks if it is
 *              valid
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

restrict_data get_P(int argc, char **argv, int *n, int *year, int *week, int *max_year, int *max_week)
{
    // search '-P'
    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-' && argv[i][1] == 'P' && strlen(argv[i]) == 2){
            // validate option and scan date or n if that is the case
            if(strcmp(argv[i + 1], "min") == 0){
                (*n) = atoi(argv[i + 2]);
                return MIN;
            }
            else if(strcmp(argv[i + 1], "max") == 0){
                (*n) = atoi(argv[i + 2]);
                return MAX;
            }
            else if(strcmp(argv[i + 1], "date") == 0){
                sscanf(argv[i + 2], "%d-%d", year, week);
                return DATE;
            }
            else if(strcmp(argv[i + 1], "dates") == 0){
                sscanf(argv[i + 2], "%d-%d", year, week);
                sscanf(argv[i + 3], "%d-%d", max_year, max_week);
                if(check_dates((*year), (*week), (*max_year), (*max_week)) == -1)
                    change_dates(year, week, max_year, max_week);
                return DATES;
            }
            // if invalid option
            else{
                printf("P argument invalid\n");
                console_error();
            }
        }
    }
    // if there is no input of 'P'
    return NO_INPUT_2;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: check_dates
 *
 * Arguments: int year1 -- year of date 1
 *            int week1 -- week of date 1
 *            int year2 -- year of date 2
 *            int week2 -- week of date 2
 *
 * Return: -1 -- if date 1 is later than date 2
 *          1 -- if date 1 is earlier than date 2
 * 
 * Description: This function checks if date 1 is earlier than date 2
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int check_dates(int year1, int week1, int year2, int week2)
{
    // check year
    if(year1 > year2)
        return -1;
    // if year is the same, check week
    else if(year1 == year2 && week1 > week2)
        return -1;
    else
        return 1;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: change_dates
 *
 * Arguments: int *year1 -- pointer to year of date 1
 *            int *week1 -- pointer to week of date 1
 *            int *year2 -- pointer to year of date 2
 *            int *week2 -- pointer to week of date 2
 *
 * Return: no return
 * 
 * Description: This function changes 2 dates
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void change_dates(int *year1, int *week1, int *year2, int *week2)
{
    // save year 1 in aux
    int aux;
    aux = (*year1);
    // put year 2 in year 1
    (*year1) = (*year2);
    // put year 1 in year 2
    (*year2) = aux;
    // save week 1 in aux
    aux = (*week1);
    // put week 2 in week 1
    (*week1) = (*week2);
    // put week 1 in week 2
    (*week2) = aux;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: change_dates
 *
 * Arguments: no arguments
 *
 * Return: no return
 * 
 * Description: This function prints help msg and exit program
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void console_error()
{
    printf("\
    SELECT READ FILES:\n\
        -i filename.csv -- read text file\n\
        -i filename.dat -- read binary input\n\
    SELECT OUTPUT FILES:\n\
        -o filename.csv -- output text file\n\
        -o filename.dat -- output binary file\n\
    READ SELECTOR:\n\
        -L all -- read all countries\n\
        -L continent -- just read countries of the \"continent\"\n\
    SELECT DATA:\n\
        -S alfa -- alphabethical order\n\
        -S pop -- highest to lowest population\n\
        -S inf yyyy-ww -- highest to lowest number of cases in week \"yyyy-ww\"\n\
        -S dea yyyy-ww -- highest to lowest number of deaths in week \"yyyy-ww\"\n\
    SELECT DATA:\n\
        -D inf -- select for each country the week with most cases\n\
        -D dea -- select for each country the week with most deaths\n\
        -D racioinf -- select for each country the week with most ratio of cases\n\
        -D raciodea -- select for each country the week with most ratio of deaths\n\
    RESTRICT DATA:\n\
        -P min n -- just countries with at least n*1000 of population\n\
        -P max n -- just countries with max of n*1000 of population\n\
        -P date yyyy-ww -- just the week \"yyyy-ww\"\n\
        -P dates yyyy-ww yyyy-ww -- just weeks between dates mentioned\n\
    ");
    exit(EXIT_FAILURE);
}
