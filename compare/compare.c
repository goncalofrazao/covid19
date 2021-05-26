#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000


/*************************************************
 * To compare 2 files:
 *  1 - compile with make
 *  2 - put 2 files in the tester folder
 *  3 - call with ./compare filename1 filename2
 * 
 * The program will return to stdout:
 *  ESTAS NA MERDA - if files are different
 *  NICE  - if files are equal
 ************************************************/

int main(int argc, char **argv)
{
    char *file1 = argv[1];
    char *file2 = argv[2];

    FILE *fp1 = fopen(file1, "r");
    FILE *fp2 = fopen(file2, "r");

    char buffer1[MAX_LEN];
    char buffer2[MAX_LEN];

    while(fgets(buffer1, MAX_LEN, fp1) == NULL || fgets(buffer2, MAX_LEN, fp2) == NULL){
        if(strcmp(buffer1, buffer2) != 0){
            printf("ESTAS NA MERDA\n");
            exit(EXIT_FAILURE);
        }
    }
    printf("NICE\n");
    return 0;
}