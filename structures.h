#include <stdio.h>
#include <stdlib.h>

#ifndef _STRUCTURES_
#define _STRUCTURES_

//typedef unsigned long uint32_t;

typedef struct fix //linked list with country data
{
    char name[30];     //name of the country
    char initials[4];     //initials of the country
    char continent[10];   //continent of the country
    unsigned long population;      //population of the country
    struct var *var;      //pointer to the head of the list with weekly data
    struct fix *next;     //pointer to next element of the list
} fix_t;

typedef struct var //linked list with weekly data
{
    int week;              //week
    int year;              //year
    int cases;
    int deaths;
    int weekly_cases;      //cases of the week
    int weekly_deaths;     //deaths of the week
    double rate_cases;       //ratio of cases per 100k habitants
    double rate_deaths;      //ratio of deaths per 1M habitants
    int cumulative_cases;  //cumulative cases of the country
    int cumulative_deaths; //cumulative deaths of the country
    struct var *next;      //pointer to next list element
} var_t;

typedef enum _order_data { // order data options
    ALFA,
    POP,
    INF,
    DEA
} order_data;

typedef enum _select_data { // select data options
    SELECT_INF,
    SELECT_DEA,
    RACIOINF,
    RACIODEA,
    NO_INPUT_1
} select_data;

typedef enum _restrict_data { // restrict data options
    MIN,
    MAX,
    DATE,
    DATES,
    NO_INPUT_2
} restrict_data;

#endif