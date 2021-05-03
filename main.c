#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"
#include "structures.h"

void printlist(fix_t *head)
{
    fix_t *tmp1 = head;
    //var_t *tmp2 = head->head;

    while (tmp1 != NULL){
        printf("%s - %ld - %d - %d\n", tmp1->country, tmp1->population, tmp1->var->cumulative_cases, tmp1->var->cumulative_deaths);
        /*
        while(tmp2 != NULL){
            printf("%s, %s, %s, %ld ", tmp1->country, tmp1->initials, tmp1->continent, tmp1->population);
            printf("%d-%d, %d, %d, %d, %d, %d, %d\n", tmp2->week, tmp2->year, tmp2->weekly_cases, tmp2->weekly_deads, tmp2->racio_cases, tmp2->racio_deads, tmp2->cumulative_cases, tmp2->cumulative_deads);
            tmp2 = tmp2->next;
        }
        */
        tmp1 = tmp1->next;
    }
    printf("\n");
}

fix_t *create_new_fix(char *country, char *initials, char *continent, long population){
    fix_t *result = (fix_t*) malloc(sizeof(fix_t));
    strcpy(result->country, country);
    strcpy(result->initials, initials);
    strcpy(result->continent, continent);
    result->population = population;
    result->next = NULL;
    return result;
}

var_t *create_new_var(int week, int year, char *indicator, int weekly_count, float rate_14_day, int cumulative_count){
    var_t *result = (var_t*) malloc(sizeof(var_t));
    result->week = week;
    result->year = year;
    if(strcmp(indicator, "deaths") == 0){
        result->weekly_deads = weekly_count;
        result->racio_deaths = rate_14_day;
        result->cumulative_deaths = cumulative_count;
    }else{
        result->weekly_cases = weekly_count;
        result->racio_cases = rate_14_day;
        result->cumulative_cases = cumulative_count;
    }
    result->next = NULL;
    return result;
}

fix_t *insert_at_head(fix_t *head, fix_t *fix_to_insert){
    fix_to_insert->next = head;
    return fix_to_insert;
}

var_t *insert_at_head_var(var_t *head, var_t *var_to_insert){
    var_to_insert->next = head;
    return var_to_insert;
}

int main(){
    fix_t *head = NULL;
    fix_t *tmp1;
    var_t *tmp2;
    
    char country[30];
    char initials[4];
    char continent[10];
    long pop;
    int week;
    int year;
    char indicator[7];
    int weekly_count;
    float rate_14_day;
    int cumulative_count;
    strcpy(country, "Ireland");
    strcpy(initials, "AND");
    strcpy(continent, "Europe");
    pop = 20;
    week = 12;
    year = 2020;
    strcpy(indicator, "cases");
    weekly_count = 108;
    rate_14_day = 148.3387374;
    cumulative_count = 50;
    tmp1 = create_new_fix(country, initials, continent, pop);
    head = insert_at_head(head, tmp1);
    tmp2 = create_new_var(week, year, indicator, weekly_count, rate_14_day, cumulative_count);
    tmp1->var = insert_at_head_var(tmp1->var, tmp2);
    if (head->next != NULL)
        head->next->previous = head;
    
    strcpy(country, "Pakistan");
    strcpy(initials, "AUS");
    strcpy(continent, "Oceania");
    pop = 20;
    week = 12;
    year = 2020;
    strcpy(indicator, "cases");
    weekly_count = 3;
    rate_14_day = 0.039215869;
    cumulative_count = 100;
    tmp1 = create_new_fix(country, initials, continent, pop);
    head = insert_at_head(head, tmp1);
    tmp2 = create_new_var(week, year, indicator, weekly_count, rate_14_day, cumulative_count);
    tmp1->var = insert_at_head_var(tmp1->var, tmp2);
    if (head->next != NULL)
        head->next->previous = head;

    strcpy(country, "Egypt");
    strcpy(initials, "EGY");
    strcpy(continent, "Africa");
    pop = 20;
    week = 12;
    year = 2020;
    strcpy(indicator, "cases");
    weekly_count = 1;
    rate_14_day = 0.000977188;
    cumulative_count = 10;
    tmp1 = create_new_fix(country, initials, continent, pop);
    head = insert_at_head(head, tmp1);
    tmp2 = create_new_var(week, year, indicator, weekly_count, rate_14_day, cumulative_count);
    tmp1->var = insert_at_head_var(tmp1->var, tmp2);
    if (head->next != NULL)
        head->next->previous = head;

    strcpy(country, "Portugal");
    strcpy(initials, "IRL");
    strcpy(continent, "Europe");
    pop = 20;
    week = 12;
    year = 2020;
    strcpy(indicator, "cases");
    weekly_count = 2;
    rate_14_day = 0.805730354;
    cumulative_count = 150;
    tmp1 = create_new_fix(country, initials, continent, pop);
    head = insert_at_head(head, tmp1);
    tmp2 = create_new_var(week, year, indicator, weekly_count, rate_14_day, cumulative_count);
    tmp1->var = insert_at_head_var(tmp1->var, tmp2);
    if (head->next != NULL)
        head->next->previous = head;

    strcpy(indicator, "cases");

    printlist(head);
    head = decreasin(head, 12, 2020, indicator);
    printlist(head);

    printf("\n");

    return 0;
}



/*
int main()
{
    node_t *head = NULL;
    node_t *tmp;
    
    for (int i = 1; i < 10; i++){
        tmp = create_new_node(i);
        head = insert_at_head(head, tmp);
    }
    
    printlist(head);

    return 0;
}
*/