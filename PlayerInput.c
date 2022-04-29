#include "Header.h"

#include <string.h>
#include <stdio.h>


char input[255];

/**
 * Author: Frederik G. Petersen (S215834)
 * @return
 */
char* getPlayerInput(){
    printf("INPUT > ");
    fflush(stdin);
    strcpy(dataPTR_lastCommand(), fgets (input, 255, stdin));
    return input;
}

