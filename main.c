#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "order_data.h"
#include "structures.h"
#include "new_struct.h"
#include "restrict_data.h"
#include "input.h"

void printlist(fix_t *head)
{
    fix_t *tmp1 = head;
    //var_t *tmp2 = head->head;

    while (tmp1 != NULL)
    {
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

int main()
{
    /*
    strcpy(country, "Ireland");
    strcpy(initials, "AND");
    strcpy(continent, "Europe");
    pop = 100;
    week = 12;
    year = 2020;
    strcpy(indicator, "cases");
    weekly_count = 108;
    rate_14_day = 148.3387374;
    cumulative_count = 50;
    */

    input(country, initials, continent, pop, indicator, week, year, rate_14_day, cumulative_count, tmp1, head, tmp2);

    /*
    tmp1 = create_new_fix(country, initials, continent, pop);
    head = insert_at_head_fix(head, tmp1);
    tmp2 = create_new_var(week, year, indicator, weekly_count, rate_14_day, cumulative_count);
    tmp1->var = insert_at_head_var(tmp1->var, tmp2);
    if (head->next != NULL)
        head->next->previous = head;

    strcpy(country, "Pakistan");
    strcpy(initials, "AUS");
    strcpy(continent, "Oceania");
    pop = 1400;
    week = 12;
    year = 2020;
    strcpy(indicator, "cases");
    weekly_count = 3;
    rate_14_day = 0.039215869;
    cumulative_count = 100;
    tmp1 = create_new_fix(country, initials, continent, pop);
    head = insert_at_head_fix(head, tmp1);
    tmp2 = create_new_var(week, year, indicator, weekly_count, rate_14_day, cumulative_count);
    tmp1->var = insert_at_head_var(tmp1->var, tmp2);
    if (head->next != NULL)
        head->next->previous = head;

    strcpy(country, "Egypt");
    strcpy(initials, "EGY");
    strcpy(continent, "Africa");
    pop = 900;
    week = 12;
    year = 2020;
    strcpy(indicator, "cases");
    weekly_count = 1;
    rate_14_day = 0.000977188;
    cumulative_count = 10;
    tmp1 = create_new_fix(country, initials, continent, pop);
    head = insert_at_head_fix(head, tmp1);
    tmp2 = create_new_var(week, year, indicator, weekly_count, rate_14_day, cumulative_count);
    tmp1->var = insert_at_head_var(tmp1->var, tmp2);
    if (head->next != NULL)
        head->next->previous = head;

    strcpy(country, "Portugal");
    strcpy(initials, "IRL");
    strcpy(continent, "Europe");
    pop = 1300;
    week = 12;
    year = 2020;
    strcpy(indicator, "cases");
    weekly_count = 2;
    rate_14_day = 0.805730354;
    cumulative_count = 150;
    tmp1 = create_new_fix(country, initials, continent, pop);
    head = insert_at_head_fix(head, tmp1);
    tmp2 = create_new_var(week, year, indicator, weekly_count, rate_14_day, cumulative_count);
    tmp1->var = insert_at_head_var(tmp1->var, tmp2);
    if (head->next != NULL)
        head->next->previous = head;
        */

    printlist(head);
    min_habitants(1, &head);
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
