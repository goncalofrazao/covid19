#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "order_data.h"
#include "new_struct.h"
#include "input.h"


int input(char country, char initials, char continent, long pop, char indicator, int week, int year, float rate_14_day, int cumulative_count, fix_t *tmp1, fix_t *head, var_t *tmp2){

    FILE *fp;
    fix_t *i;
    var_t *j;

    if((fp = fopen ("covid19_w_t01.csv", "r"))==NULL)
    {
        printf("Erro na abertura do ficheiro");
        return -1;
    }
    //FALTA DAR SKIP NA PRIMEIRA LINHA
    while(fscanf(fp,"%s,%s,%s,%ld,%s,%d,%d,%f,%d",&country, &initials, &continent, &pop, &week, &year, &rate_14_day, &cumulative_count)!= EOF){
            i = find_country(head, country);

            if(i==NULL){
                tmp1 = create_new_fix(country, initials, continent, pop);
                head = insert_at_head_fix(head, tmp1);
                tmp2 = create_new_var(week, year, indicator, weekly_count, rate_14_day, cumulative_count);
                tmp1->var = insert_at_head_var(tmp1->var, tmp2);
                if (head->next != NULL)
                    head->next->previous = head;
            }
            else{
                j= find_date(head, week, year);
                if(j==NULL){
                        //nao ha data
                    }
                else{
                    //quando ha data
                }

            }


    }





    fclose(fp);
    return 0;
}
