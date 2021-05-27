#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "input.h"
#include "structures.h"
#include "new_struct.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: read_input
 *
 * Arguments: char *what_to_read -- what we want to read from the
 *                                  input file
 *            char *filename -- name of the file
 *
 * Return: fix_t *head -- pointer to the head of list of countries
 *
 * Description: This function reads the input file name
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

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
        exit(EXIT_FAILURE);
    }
    //scan first line to discard it (we dont need it since it's always the same)
    fscanf(fp, "%*[^\n]\n");

    while(fgets(str, MAXLEN, fp) != NULL){
        check_line(str);
        stringlen = strlen(str);
        
		//new line = end of string
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
        //less than 8 columns is an error
        if(i < 8){
            read_error();
        }

        //check errors
        for(int j = 0; j < i; j++){
            switch (j)
            {
			//for columns 0,1,2,4 we need to check the string
            case 0:
            case 1:
            case 2:
            case 4:
                check_string(column[j]);
                break;
			//for columns 0,1,2,4 we need to check the int
            case 3:
            case 5:
            case 8:
                check_int(column[j]);
                break;
			//for columns 6 we need to check if the date is in the right format
            case 6:
                check_date(column[j]);
                break;
            case 7:
				//if it only has 8 columns, check int (cumulative count)
                if(i == 8){
                    check_int(column[j]);
                }
                //if it has 9 columns, check float (rate_14_day)
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
            //there are no years with 54 weeks!
            if(week > 53)
                read_error();
			//sometimes there is no data for rate_14_day, in those cases strtok only creates 8 tokens!
            if(i == 8){
                cumulative_count = atoi(column[7]);
                rate_14_day = 0;
            }
            else{
                rate_14_day = atof(column[7]);
                cumulative_count = atoi(column[8]);
            }
            check_indicator(indicator);
            aux1 = find_country(head, country);
            //if a structure for the country doesnt exist yet, we create one
            if(aux1 == NULL){
                aux1 = create_country(country, initials, continent, population);
                head = insert_fix(aux1, head);
                aux2 = create_date(year, week, indicator, weekly_count, rate_14_day, cumulative_count);
                aux1->var = insert_var(aux2, aux1->var);
            }
            //if there is already a structure for the country, we update that structure
            else{
				//check if date already exists
                aux2 = find_date(aux1->var, year, week);
                //if it doesnt, create a new date
                if(aux2 == NULL){
                    aux2 = create_date(year, week, indicator, weekly_count, rate_14_day, cumulative_count);
                    aux1->var = insert_var(aux2, aux1->var);
                }
                //if it does, update the data for the date
                else{
                    update_date(aux2, indicator, weekly_count, rate_14_day, cumulative_count);
                }
            }
        }
    }
    fclose(fp);
    return head;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: output
 *
 * Arguments: fix_t *head -- pointer to the head of list of countries
 *            char *filename -- name of the file to write
 *
 * Return: no return
 *
 * Description: This function creates a .csv file with the data
 *              from the structures
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void output(fix_t *head, char *filename)
{
    fix_t *aux1;
    var_t *aux2;
    FILE *fp = fopen(filename, "w");
    //write the first line that indicates the columns
    fprintf(fp, "country,country_code,continent,population,indicator,weekly_count,year_week,rate_14_day,cumulative_count\n");
    //go through the list of structures
    while(head != NULL){
        while(head->var != NULL){
            if(head->var->cases == 1)
                fprintf(fp, "%s, %s, %s, %lu, cases, %d, %4d-%2d, %f, %d\n", head->name, head->initials, head->continent, head->population, head->var->weekly_cases, head->var->year, head->var->week, head->var->rate_cases, head->var->cumulative_cases);
            if(head->var->deaths == 1)
                fprintf(fp, "%s, %s, %s, %lu, deaths, %d, %4d-%2d, %f, %d\n", head->name, head->initials, head->continent, head->population, head->var->weekly_deaths, head->var->year, head->var->week, head->var->rate_deaths, head->var->cumulative_deaths);
            //save the next struct on aux2
            aux2 = head->var->next;
            free(head->var);
            //head->var becomes the next struct
            head->var = aux2;
        }
        aux1 = head->next;
        free(head);
        head = aux1;
    }
    fclose(fp);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: binary_output
 *
 * Arguments: fix_t *head -- pointer to the head of list of countries
 *            char *filename -- name of the file to write
 *
 * Return: no return
 *
 * Description: This function creates a .dat binary file with the data
 *              from the structures
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void binary_output(fix_t *head, char *filename)
{
    FILE *fp = fopen(filename, "wb");
    //count number of fix structures
    int i = count_fix(head);
    var_t *aux1;
    fix_t *aux2;
    fwrite(&i, sizeof(int), 1, fp);
    while(head != NULL){
		//write the fix structure
        fwrite(head, sizeof(fix_t), 1, fp);
        //count number of var structures
        i = count_var(head->var);
        fwrite(&i, sizeof(int), 1, fp);
        for(int a = 0; a < i; a++){
			//write the var structure
            fwrite(head->var, sizeof(var_t), 1, fp);
            //save next on aux1
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

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: binary_input
 *
 * Arguments: char *filename -- name of the file
 *
 * Return: fix_t *head -- pointer to the head of list of countries
 *
 * Description: This function reads the .dat input file
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

fix_t *binary_input(char *filename)
{
    // open file
    FILE *fp = fopen(filename, "rb");
    int i = 0;
    int j = 0;
    fix_t *head;
    var_t *aux1;
    fix_t *aux2;
    head = NULL;
    //read number of fix structures
    fread(&i, sizeof(int), 1, fp);
    //go through all of the fix structures written on the .dat file
    for(int b = 0; b < i; b++){
        aux2 = (fix_t*) malloc(sizeof(fix_t));
        fread(aux2, sizeof(fix_t), 1, fp);
        aux2->next = NULL;
        aux2->var = NULL;
        //insert structure on the list
        head = insert_fix(aux2, head);
        //read number of var structures
        fread(&j, sizeof(int), 1, fp);
        //go through all of the var structures
        for(int a = 0; a < j; a++){
            aux1 = (var_t*) malloc(sizeof(var_t));
            fread(aux1, sizeof(var_t), 1, fp);
            aux1->next = NULL;
            //insert var structure
            aux2->var = insert_var(aux1, aux2->var);
        }
    }
    // close file
    fclose(fp);
    return head;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: count_var
 *
 * Arguments: var_t *head -- pointer to the head of list of countries
 *
 * Return: int i -- number of var_t type structures
 *
 * Description: This function counts the number of var_t type structures
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int count_var(var_t *head)
{
    int i = 0;
    //go thought the list counting the number of var structures, until the end is reached
    while(head != NULL){
        i++;
        //go to the next structure
        head = head->next;
    }
    return i;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: count_fix
 *
 * Arguments: fix_t *head -- pointer to the head of list of countries
 *
 * Return: int i -- number of fix_t type structures
 *
 * Description: This function counts the number of fix_t type structures
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int count_fix(fix_t *head)
{
    int i = 0;
    //go thought the list counting the number of fix structures, until the end is reached
    while(head != NULL){
        i++;
        //go to the next structure
        head = head->next;
    }
    return i;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: check_string
 *
 * Arguments: char *check -- string to check
 *
 * Return: no return
 *
 * Description: Checks if string only has characters from a to z, A to Z
 *              or space. If it doesn't, it ends the program
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void check_string(char *check)
{
    for(int i = 0; i < strlen(check); i++){
        if(!((check[i] >= 'a' && check[i] <= 'z') || (check[i] >= 'A' && check[i] <= 'Z') || (check[i] == ' ')))
            read_error();
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: check_int
 *
 * Arguments: char *check -- string to check
 *
 * Return: no return
 *
 * Description: Checks if string only has numbers
 *              If it doesn't, it ends the program
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void check_int(char *check)
{
    for(int i = 0; i < strlen(check); i++){

        if(!(check[i] >= '0' && check[i] <= '9'))
            read_error();
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: check_float
 *
 * Arguments: char *check -- string to check
 *
 * Return: no return
 *
 * Description: Checks if string only has numbers and one '.'
 *              If it doesn't, it ends the program
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void check_float(char *check)
{
    int flag = 0;
    for(int i = 0; i < strlen(check); i++){
        if(!((check[i] >= '0' && check[i] <= '9') || (check[i] == '.')))
            read_error();
        if(check[i] == '.')
            flag++;
    }
    //floats only have one '.', more than that is an error
    if(flag > 1)
        read_error();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: check_line
 *
 * Arguments: char *check -- string to check
 *
 * Return: no return
 *
 * Description: Counts the number of commas in the string
 *              If the number is different than 8, it ends the program
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void check_line(char *line)
{
    int comma_number = 0;
    while((*line) != '\0'){
        if((*line) == ',')
            comma_number++;
        line++;
    }
    //every line on the .csv file has 8 commas
    if(comma_number != 8)
        read_error();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: check_date
 *
 * Arguments: char *date -- string to check
 *
 * Return: no return
 *
 * Description: Check if string only has number and one '-'
 *              If it doesn't, it ends the program
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void check_date(char *date)
{
    int ifen_number = 0;
    for(int i = 0; i < strlen(date); i++){
        if(date[i] == '-')
            ifen_number++;
        if((date[i] < '0' || date[i] > '9') && !(date[i] == '-'))
            read_error();
    }
    //dates are on the format year-week, so they only have one ifen
    if(ifen_number != 1)
        read_error();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: check_indicator
 *
 * Arguments: char *indicator -- string to check
 *
 * Return: no return
 *
 * Description: Check if string is different than "cases" and "deaths"
 *              it ends the program
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
void check_indicator(char *indicator)
{
	if(strcmp(indicator,"cases") != 0 && strcmp(indicator,"deaths") != 0)
		read_error();
	}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function name: read_error
 *
 * Arguments: no arguments
 *
 * Return: no return
 *
 * Description: Prints error message and ends program
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void read_error()
{
    printf("-1 READ ERROR\n");
    exit(EXIT_FAILURE);
}
