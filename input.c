#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "input.h"
#include "structures.h"
#include "new_struct.h"

fix_t *read_input(char *what_to_read, char *filename)
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

    if((fp = fopen (filename, "r"))==NULL)
    {
        printf("Erro na abertura do ficheiro");
        return NULL;
    }
    fscanf(fp, "%*[^\n]\n");

    while(fgets(str, MAXLEN, fp) != NULL){
        check_line(str);
        stringlen = strlen(str);

        if(str[stringlen - 1] == '\n')
            str[stringlen - 2] = '\0';

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
        if(i < 8){
            read_error();
        }

        for(int j = 0; j < i; j++){
            switch (j)
            {
            case 0:
            case 1:
            case 2:
            case 4:
                check_string(column[j]);
                break;

            case 3:
            case 5:
            case 8:
                check_int(column[j]);
                break;

            case 6:
                check_date(column[j]);
                break;

            case 7:
                if(i == 8){
                    check_int(column[j]);
                }
                else{
                    check_float(column[j]);
                }
                break;

            default:
                break;
            }
        }


        if (strcmp(column[2], what_to_read) == 0 || strcmp(what_to_read, "all") == 0){
            strcpy(country, column[0]);
            strcpy(initials, column[1]);
            strcpy(continent, column[2]);
            population = (unsigned) atol(column[3]);
            strcpy(indicator, column[4]);
            weekly_count = atoi(column[5]);
            sscanf(column[6], "%d-%d", &year, &week);
            if(week > 53)
                read_error();

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

void _op(fix_t *head, char *filename)
{
    fix_t *aux1;
    var_t *aux2;
    FILE *fp = fopen(filename, "w");
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

void output(fix_t *head, char *filename)
{
    fix_t *aux1;
    var_t *aux2;
    FILE *fp = fopen(filename, "w");
    fprintf(fp, "country,country_code,continent,population,indicator,weekly_count,year_week,rate_14_day,cumulative_count\n");
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

void binary_output(fix_t *head, char *filename)
{
    FILE *fp = fopen(filename, "wb");
    int i = count_fix(head);
    var_t *aux1;
    fix_t *aux2;
    fwrite(&i, sizeof(int), 1, fp);
    while(head != NULL){
        fwrite(head, sizeof(fix_t), 1, fp);
        i = count_var(head->var);
        fwrite(&i, sizeof(int), 1, fp);
        for(int a = 0; a < i; a++){
            fwrite(head->var, sizeof(var_t), 1, fp);
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

fix_t *binary_input(char *filename)
{
    FILE *fp = fopen(filename, "rb");
    int i = 0;
    int j = 0;
    fix_t *head;
    var_t *aux1;
    fix_t *aux2;
    fread(&i, sizeof(int), 1, fp);
    for(int b = 0; b < i; b++){
        aux2 = (fix_t*) malloc(sizeof(fix_t));
        fread(aux2, sizeof(fix_t), 1, fp);
        aux2->next = NULL;
        aux2->var = NULL;
        head = insert_fix(aux2, head);
        fread(&j, sizeof(int), 1, fp);
        for(int a = 0; a < j; a++){
            aux1 = (var_t*) malloc(sizeof(var_t));
            fread(aux1, sizeof(var_t), 1, fp);
            aux1->next = NULL;
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

int count_fix(fix_t *head)
{
    int i = 0;
    while(head != NULL){
        i++;
        head = head->next;
    }
    return i;
}

void check_string(char *check)
{
    for(int i = 0; i < strlen(check); i++){
        if(!((check[i] >= 'a' && check[i] <= 'z') || (check[i] >= 'A' && check[i] <= 'Z') || (check[i] == ' ')))
            read_error();
    }
}

void check_int(char *check)
{
    for(int i = 0; i < strlen(check); i++){

        if(!(check[i] >= '0' && check[i] <= '9'))
            read_error();
    }
}

void check_float(char *check)
{
    int flag = 0;
    for(int i = 0; i < strlen(check); i++){
        if(!((check[i] >= '0' && check[i] <= '9') || (check[i] == '.')))
            read_error();
        if(check[i] == '.')
            flag++;
    }
    if(flag > 1)
        read_error();
}

void check_line(char *line)
{
    int comma_number = 0;
    while((*line) != '\0'){
        if((*line) == ',')
            comma_number++;
        line++;
    }
    if(comma_number < 8)
        read_error();
}

void check_date(char *date)
{
    int ifen_number = 0;
    for(int i = 0; i < strlen(date); i++){
        if(date[i] == '-')
            ifen_number++;
        if((date[i] < '0' || date[i] > '9') && !(date[i] == '-'))
            read_error();
    }
    if(ifen_number > 1)
        read_error();
}

void read_error()
{
    printf("-1 READ ERROR\n");
    exit(EXIT_FAILURE);
}
