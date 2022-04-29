#include "Header.h"

#include <string.h>
#include <stdio.h>

/**
 * Author: Frederik G. Petersen (S215834)
 * @return
 */
void getPlayerInput(){
    printf("INPUT > ");
    fflush(stdin);
    fgets (dataPTR_lastCommand(), 255, stdin);
}

