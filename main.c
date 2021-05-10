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
    fix_t *head;
    head = read_input();

    alphabetical(&head);   
    printlist(head);

    printf("\n");

    return 0;
}
