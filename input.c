#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "input.h"
#include "structures.h"
#include "new_struct.h"

fix_t *read_input(char *what_to_read)
{

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
    unsigned long population;
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

        if (strcmp(column[2], what_to_read) == 0 || strcmp(what_to_read, "all") == 0){
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
                aux1->var = insert_var(aux2, aux1->var);
            }
            else{
                aux2 = find_date(aux1->var, year, week);
                if(aux2 == NULL){
                    aux2 = create_date(year, week, indicator, weekly_count, rate_14_day, cumulative_count);
                    aux1->var = insert_var(aux2, aux1->var);
                }
                else{
                    update_date(aux2, indicator, weekly_count, rate_14_day, cumulative_count);
                }
            }
        }
    }
    fclose(fp);
    return head;
}

void _op(fix_t *head)
{
    fix_t *aux1;
    var_t *aux2;
    FILE *fp = fopen("output.csv", "w");
    while(head != NULL){
        fprintf(fp, "%s, %lu\n", head->name, head->population);
        while(head->var != NULL){
            aux2 = head->var->next;
            free(head->var);
            head->var = aux2;
        }
        aux1 = head->next;
        free(head);
        head = aux1;
    }
    fclose(fp);
}

void output(fix_t *head)
{
    fix_t *aux1;
    var_t *aux2;
    FILE *fp = fopen("output.csv", "w");
    while(head != NULL){
        while(head->var != NULL){
            fprintf(fp, "%s, %d-%d, %d, %f, %d, %d, %f, %d\n", head->name, head->var->year, head->var->week, head->var->weekly_cases, head->var->rate_cases, head->var->cumulative_cases, head->var->weekly_deaths, head->var->rate_deaths, head->var->cumulative_deaths);
            aux2 = head->var->next;
            free(head->var);
            head->var = aux2;
        }
        aux1 = head->next;
        free(head);
        head = aux1;
    }
    fclose(fp);
}

void binary_output(fix_t *head)
{
    FILE *fp = fopen("output.dat", "wb");
    int i = 0;
    var_t *aux1;
    fix_t *aux2;
    while(head != NULL){
        fwrite(head->name, 30, 1, fp);
        fwrite(head->initials, 4, 1, fp);
        fwrite(head->continent, 10, 1, fp);
        fwrite(&head->population, 8, 1, fp);
        i = count_var(head->var);
        fwrite(&i, 4, 1, fp);
        for(int a = 0; a < i; a++){
            fwrite(&head->var->year, 4, 1, fp);
            fwrite(&head->var->week, 4, 1, fp);
            fwrite(&head->var->weekly_cases, 4, 1, fp);
            fwrite(&head->var->rate_cases, 8, 1, fp);
            fwrite(&head->var->cumulative_cases, 4, 1, fp);
            fwrite(&head->var->weekly_deaths, 4, 1, fp);
            fwrite(&head->var->rate_deaths, 8, 1, fp);
            fwrite(&head->var->cumulative_deaths, 4, 1, fp);
            
            aux1 = head->var->next;
            free(head->var);
            head->var = aux1;
        }
        aux2 = head->next;
        free(head);
        head = aux2;
    }
    fclose(fp);
}

fix_t *binary_input()
{
    FILE *fp = fopen("output.dat", "rb");
    int i = 0;
    char name[30];
    char initials[4];
    char continent[10];
    unsigned long population;
    int week;
    int year;
    int weekly_cases;
    int weekly_deaths;
    double rate_cases;
    double rate_deaths;
    int cumulative_cases;
    int cumulative_deaths;
    fix_t *head;
    var_t *aux1;
    fix_t *aux2;
    while(fread(name, 30, 1, fp) != NULL){
        fread(initials, 4, 1, fp);
        fread(continent, 10, 1, fp);
        fread(&population, 8, 1, fp);
        aux2 = create_country(name, initials, continent, population);
        head = insert_fix(aux2, head);
        fread(&i, 4, 1, fp);
        for(int a = 0; a < i; a++){
            fread(&year, 4, 1, fp);
            fread(&week, 4, 1, fp);
            fread(&weekly_cases, 4, 1, fp);
            fread(&rate_cases, 8, 1, fp);
            fread(&cumulative_cases, 4, 1, fp);
            fread(&weekly_deaths, 4, 1, fp);
            fread(&rate_deaths, 8, 1, fp);
            fread(&cumulative_deaths, 4, 1, fp);
            aux1 = create_date(year, week, "cases", weekly_cases, rate_cases, cumulative_cases);
            update_date(aux1, "deaths", weekly_deaths, rate_deaths, cumulative_deaths);
            aux2->var = insert_var(aux1, aux2->var);
        }
    }
    fclose(fp);
    return head;
}

int count_var(var_t *head)
{
    int i = 0;
    while(head != NULL){
        i++;
        head = head->next;
    }
    return i;
}