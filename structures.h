#ifndef _STRUCTURES_
#define _STRUCTURES_

typedef struct fix{
    char country[30];
    char initials[4];
    char continent[10];
    long population;
    struct var* var;
    struct fix* next;
    struct fix* previous;
}fix_t;
//typedef struct fix fix_t;

typedef struct var{
    int week;
    int year;
    int weekly_cases;
    int weekly_deaths;
    int racio_cases;
    int racio_deaths;
    int cumulative_cases;
    int cumulative_deaths;
    struct var* next;
}var_t;
//typedef struct var var_t;

#endif