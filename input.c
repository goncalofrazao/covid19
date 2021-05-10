#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "order_data.h"
#include "new_struct.h"
#include "input.h"


fix_t *read_input(){

    FILE *fp;

    fix_t *head = NULL;
    fix_t *exist_country;
    var_t *exist_date;

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

    if((fp = fopen ("covid19_w_t01.csv", "r"))==NULL)
    {
        printf("Erro na abertura do ficheiro");
        return NULL;
    }
    fscanf(fp, "%*[^\n]\n");


    while(fscanf(fp,"%s,%s,%s,%ld,%s,%d,%d-%d,%f,%d", country, initials, continent, &pop, indicator, &weekly_count, &year, &week, &rate_14_day, &cumulative_count) != EOF){
            exist_country = find_country(head, country);

            if(exist_country == NULL){
                exist_country = create_new_fix(country, initials, continent, pop);
                head = insert_at_head_fix(head, exist_country);
                exist_date = create_new_var(weekly_count, year, indicator, weekly_count, rate_14_day, cumulative_count);
                exist_country->var = insert_at_head_var(exist_country->var, exist_date);
                if (head->next != NULL)
                    head->next->previous = head;
            }
            else{
                exist_date = find_date(exist_country->var, weekly_count, year);
                if(exist_date == NULL){
                    exist_date = create_new_var(weekly_count, year, indicator, weekly_count, rate_14_day, cumulative_count);
                    exist_country->var = insert_at_head_var(exist_country->var, exist_date);
                    if (head->next != NULL)
                        head->next->previous = head;
                }
                else{
                    if(strcmp(indicator, "deaths") == 0){
                        update_struct_deaths(exist_date, weekly_count, rate_14_day, cumulative_count);
                    }else{
                        update_struct_cases(exist_date, weekly_count, rate_14_day, cumulative_count);
                    }
                }

            }


    }

    fclose(fp);
    return head;
}
