#include <stdio.h>
#include <stdlib.h>

#ifndef _STRUCTURES_
#define _STRUCTURES_

typedef struct fix //linked list with country data
{
    char country[30];     //name of the country
    char initials[4];     //initials of the country
    char continent[10];   //continent of the country
    long population;      //population of the country
    struct var *var;      //pointer to the head of the list with weekly data
    struct fix *next;     //pointer to next element of the list
    struct fix *previous; //pointer to the previous element of the list
} fix_t;

typedef struct var //linked list with weekly data
{
    int week;              //week
    int year;              //year
    int weekly_cases;      //cases of the week
    int weekly_deaths;     //deaths of the week
    int racio_cases;       //ratio of cases per 100k habitants
    int racio_deaths;      //ratio of deaths per 1M habitants
    int cumulative_cases;  //cumulative cases of the country
    int cumulative_deaths; //cumulative deaths of the country
    struct var *next;      //pointer to next list element
    struct var *previous;  //pointer to previous list element
} var_t;

#endif