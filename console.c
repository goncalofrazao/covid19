#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "console.h"
#include "structures.h"

char *get_input_file_name(int argc, char **argv)
{
    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-' && argv[i][1] == 'i' && strlen(argv[i]) == 2)
            return argv[i + 1];
    }
    return NULL;
}

char *get_ouput_file_name(int argc, char **argv)
{
    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-' && argv[i][1] == 'o' && strlen(argv[i]) == 2)
            return argv[i + 1];
    }
    return NULL;
}

char *get_L(int argc, char **argv)
{
    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-' && argv[i][1] == 'L' && strlen(argv[i]) == 2)
            return argv[i + 1];
    }
    return NULL;
}

order_data get_S(int argc, char **argv, int *year, int *week)
{
    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-' && argv[i][1] == 'S' && strlen(argv[i]) == 2){
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
            else{
                printf("S argument invalid\n");
                console_error();
            }
        }
    }
    return ALFA;
}

select_data get_D(int argc, char **argv)
{
    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-' && argv[i][1] == 'D' && strlen(argv[i]) == 2){
            if(strcmp(argv[i + 1], "inf") == 0)
                return SELECT_INF;
            else if(strcmp(argv[i + 1], "dea") == 0)
                return SELECT_DEA;
            else if(strcmp(argv[i + 1], "racioinf") == 0)
                return RACIOINF;
            else if(strcmp(argv[i + 1], "raciodea") != 0)
                return RACIODEA;
            else{
                printf("D argument invalid\n");
                console_error();
            }
        }
    }
    return NO_INPUT_1;
}

restrict_data get_P(int argc, char **argv, int *n, int *year, int *week, int *max_year, int *max_week)
{
    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-' && argv[i][1] == 'P' && strlen(argv[i]) == 2){
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
            else{
                printf("P argument invalid\n");
                console_error();
            }
        }
    }
    return NO_INPUT_2;
}

int check_dates(int year1, int week1, int year2, int week2)
{
    if(year1 > year2)
        return -1;
    else if(year1 == year2 && week1 > week2)
        return -1;
    else
        return 1;
}

void change_dates(int *year1, int *week1, int *year2, int *week2)
{
    int aux;
    aux = (*year1);
    (*year1) = (*year2);
    (*year2) = aux;
    aux = (*week1);
    (*week1) = (*week2);
    (*week2) = aux;
}

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