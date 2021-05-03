#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct fix{
    char country[30];
    char initials[4];
    char continent[10];
    long population;
    struct var* head;
    struct fix* next;
    struct fix* previous;
};
typedef struct fix fix_t;

struct var{
    int week;
    int year;
    int weekly_cases;
    int weekly_deads;
    int racio_cases;
    int racio_deads;
    int cumulative_cases;
    int cumulative_deads;
    struct var* next;
};
typedef struct var var_t;

void printlist(fix_t *head)
{
    fix_t *tmp1 = head;
    //var_t *tmp2 = head->head;

    while (tmp1 != NULL){
        printf("%s - %ld - %s - %s\n", tmp1->country, tmp1->population, tmp1->next->country, tmp1->previous->country);
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
        result->racio_deads = rate_14_day;
        result->cumulative_deads = cumulative_count;
    }else{
        result->weekly_cases = weekly_count;
        result->racio_cases = rate_14_day;
        result->cumulative_cases = cumulative_count;
    }
    result->next = NULL;
    return result;
}

int high_or_low(char *word1, char *word2){
    if(*(word1) < *(word2))
        return 1;
    else if(*(word1) > *(word2))
        return 0;
    else
        return high_or_low(word1++, word2++);
}

fix_t *alphabetical(fix_t *head){
    fix_t *aux1 = head;
    fix_t *aux2 = aux1->next;
    do{
        if(high_or_low(aux1->country, aux2->country) == 1){
            aux1 = aux2;
            aux2 = aux2->next;
        }else{
            aux1->next = aux2->next;
            if (aux2->next != 0)
                aux2->next->previous = aux1;
            aux2->next = aux1;
            if (aux1 != head){
                aux1->previous->next = aux2;
                aux2->previous = aux1->previous;
            }else{
                head = aux2;
                aux2->previous = NULL;
            }
            aux1->previous = aux2;
            aux1 = head;
            aux2 = aux1->next;
        }
    }while(aux2 != NULL);
    return head;
}

fix_t *decreasin_population(fix_t *head){
    fix_t *aux1 = head;
    fix_t *aux2 = aux1->next;
    do{
        if(aux1->population > aux2->population){
            aux1 = aux2;
            aux2 = aux2->next;
        }else{
            if(aux1->population == aux2->population && high_or_low(aux1->country, aux2->country) == 1){
                aux1 = aux2;
                aux2 = aux2->next;
            }else{
                aux1->next = aux2->next;
                if (aux2->next != 0)
                    aux2->next->previous = aux1;
                aux2->next = aux1;
                if (aux1 != head){
                    aux1->previous->next = aux2;
                    aux2->previous = aux1->previous;
                }else{
                    head = aux2;
                    aux2->previous = NULL;
                }
                aux1->previous = aux2;
                aux1 = head;
                aux2 = aux1->next;
            }
        }
    }while(aux2 != NULL);
    return head;
}

fix_t *insert_at_head(fix_t *head, fix_t *fix_to_insert){
    fix_to_insert->next = head;
    return fix_to_insert;
}

int main(){
    fix_t *head = NULL;
    fix_t *tmp;
    
    char country[30] = "Alamm";
    char initials[4] = "ESP";
    char continent[10] = "Europe";
    long population = 20;
    tmp = create_new_fix(country, initials, continent, population);
    head = insert_at_head(head, tmp);
    if (head->next != NULL)
        head->next->previous = head;
    
    strcpy(country, "Borrado");
    strcpy(initials, "POR");
    strcpy(continent, "Europe");
    population = 10;
    tmp = create_new_fix(country, initials, continent, population);
    head = insert_at_head(head, tmp);
    if (head->next != NULL)
        head->next->previous = head;


    strcpy(country, "Corno");
    strcpy(initials, "POR");
    strcpy(continent, "Europe");
    population = 6;
    tmp = create_new_fix(country, initials, continent, population);
    head = insert_at_head(head, tmp);
    if (head->next != NULL)
        head->next->previous = head;


    strcpy(country, "Dador");
    strcpy(initials, "POR");
    strcpy(continent, "Europe");
    population = 7;
    tmp = create_new_fix(country, initials, continent, population);
    head = insert_at_head(head, tmp);
    if (head->next != NULL)
        head->next->previous = head;


    strcpy(country, "Elipse");
    strcpy(initials, "POR");
    strcpy(continent, "Europe");
    population = 20;
    tmp = create_new_fix(country, initials, continent, population);
    head = insert_at_head(head, tmp);
    if (head->next != NULL)
        head->next->previous = head;



    printlist(head);
    head = decreasin_population(head);

    printlist(head);
    
    free(head->next);
    free(head);

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