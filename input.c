#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "input.h"
#include "structures.h"
#include "new_struct.h"

fix_t *read_input(){

    FILE *fp;

    char *token;
    char *column[9] = {0};
    int stringlen;
    int i = 0;

    fix_t *head = NULL;
    fix_t *aux1;
    var_t *aux2;

    char str[MAXLEN];
    char country[30];
    char initials[4];
    char continent[10];
    uint32_t population;
    int week;
    int year;
    char indicator[7];
    int weekly_count;
    double rate_14_day;
    int cumulative_count;

    if((fp = fopen ("covid19_w_t01.csv", "r"))==NULL)
    {
        printf("Erro na abertura do ficheiro");
        return NULL;
    }
    fscanf(fp, "%*[^\n]\n");


    while(fgets(str, MAXLEN, fp) != NULL){
        //sscanf(str, "%s,%s,%s,%ld,%s,%d,%d-%d,%f,%d", country, initials, continent, &pop, indicator, &weekly_count, &year, &week, &rate_14_day, &cumulative_count);
        stringlen = strlen(str);
        
        if(str[stringlen - 1] == '\n')
            str[stringlen - 1] = '\0';

        if ((str[stringlen - 2] == '\n' && str[stringlen - 1] == '\r')){
            str[stringlen - 2] = '\0';
            str[stringlen - 1] = '\0';
        }
        
        token = strtok(str, ",");
        column[0] = token;
        i = 1;
        while((token = strtok(NULL,",")) != NULL && i < 9){
            column[i++] = token;
        }

        strcpy(country, column[0]);
        strcpy(initials, column[1]);
        strcpy(continent, column[2]);
        population = (unsigned) atol(column[3]);
        strcpy(indicator, column[4]);
        weekly_count = atoi(column[5]);
        sscanf(column[6], "%d-%d", &year, &week);
        if(i == 8){
            cumulative_count = atoi(column[7]);
            rate_14_day = 0;
        }
        else{
            rate_14_day = atof(column[7]);
            cumulative_count = atoi(column[8]);
        }

        aux1 = find_country(head, country);
        if(aux1 == NULL){
            aux1 = create_country(country, initials, continent, population);
            head = insert_fix(aux1, head);
            aux2 = create_date(year, week, indicator, weekly_count, rate_14_day, cumulative_count);
            head->var = insert_var(aux2, head->var);
        }
        else{
            aux2 = find_date(aux1->var, weekly_count, year);
            if(aux2 == NULL){
                aux2 = create_date(year, week, indicator, weekly_count, rate_14_day, cumulative_count);
                aux1->var = insert_var(aux2, aux1->var);
            }
            else{
                update_date(aux2, indicator, weekly_count, rate_14_day, cumulative_count);
            }
        }
        printf("%s -- next: %s\n", aux1->name, aux1->next->name);
    }
    fclose(fp);
    return head;
}