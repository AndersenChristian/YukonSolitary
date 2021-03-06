//Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <shlwapi.h>

//Header
#include "../Data/Data_Header.h"

//local methods declaration
void printGame();
void printEmptyDisplay();
void printCards();
void printCommandLines();

/**
 * Author: Christian J. L. Andersen (S133288)
 *
 * this determinate what state the program is in, and print the display that is proper.
 */
void updateDisplay(){
    system("@cls||clear");
    printf("\nC1\tC2\tC3\tC4\tC5\tC6\tC7\n\n"); //always the first line we need printed
    if (!(*dataPTR_DeckLoaded()))
        printEmptyDisplay();
    else if(!(*dataPTR_GameStarted()))
        printCards();
    else
        printGame();

    printCommandLines();
}

/**
 * Author: Christian J. L. Andersen (S133288)
 *
 * This methods is used to print an empty display if a deck has not yet been loaded.
 */
void printEmptyDisplay(){
    int count = 1;
    for (int i = 0; i < 7; ++i) {
        if (i%2 == 0) {
            for (int j = 0; j <8; ++j) {
                printf("\t");
            }
            printf("[]\tF%d\n",count);
            count++;
        }else {
            printf("\n");
        }
    }
}

/**
 * Author: Christian J. L. Andersen (S133288)
 *
 * prints all the cards from the deck before the game starts.
 */
void printCards(){
    int cardPrinted = 0;
    int foundationsPrinted = 0;
    int lineOn = 1;
    Card* currentCard = dataPTR_ToDeck()->head;
    do{
        if (currentCard->faceUp || StrStrIA(dataPTR_lastCommand(), "SW\n") != NULL )
            printf("%s\t",currentCard->name);
        else
            printf("[]\t");
        if ((cardPrinted +1) % 7 == 0){
            if (foundationsPrinted != 4 && lineOn%2 == 1) {
                printf("\t[]\tF%d", foundationsPrinted + 1);
                foundationsPrinted++;
            }
            printf("\n");
            lineOn++;
        }
        cardPrinted++;
        if (currentCard->next != NULL)
            currentCard = currentCard->next;
    }while (cardPrinted != 52 || foundationsPrinted != 4);
    printf("\n");
}

/**
 * Author: Christian J. L. Andersen (S133288)
 *
 * prints the display when the program is in play mode
 */
void printGame(){
    Card* currentCard;
    int cardsPrinted = 0;
    int currentLine = 0;
    int line = 0;
    int finishesPrinted = 0;
    int finishedLines[7]; //0 = not finished, 1 = is finished.

    for (int i = 0; i < 7; i++) {
        if(dataPTR_ToBoard()[i].head != NULL)
            finishedLines[i]=0;
        else
            finishedLines[i]=1;
    }

    do {
        if (finishedLines[currentLine] == 0) {
            currentCard = dataPTR_ToBoard()[currentLine].head;
            for (int i = 0; i < line; i++){
                currentCard = currentCard->next;
            }
            if (currentCard->faceUp)
                printf("%s\t",currentCard->name);
            else
                printf("[]\t");
            if (currentCard->next == NULL)
                finishedLines[currentLine] = 1;
            cardsPrinted++;
        } else
            printf("\t");
        if (currentLine == 6) {
            if (line == 0 || line == 2 || line == 4 || line == 6) {
                char* foundation = "[]\0";
                LinkedList F = dataPTR_ToBoard()[finishesPrinted + 7];
                Card* fCard = F.tail;

                if (fCard != NULL){
                    foundation = fCard->name;
                    foundation[2] = '\0';
                    cardsPrinted++;
                }

                printf("\t%s\tF%d", foundation, finishesPrinted + 1);
                finishesPrinted++;
            }
            currentLine = 0;
            line++;
            if (cardsPrinted != 52)
                printf("\n");
        }
        else
            currentLine++;
    }while (cardsPrinted!=52 || finishesPrinted != 4);
    printf("\n");
}

/**
 * Author: Christian J. L. Andersen (S133288)
 *
 * prints the bottom information to the display
 */
void printCommandLines() {
    printf("\nLAST Command: %s", dataPTR_lastCommand());
    if (strcmp(dataPTR_ErrorMessage(), "") == 0) //if errormessage points to null or is empty.
        printf("Message: OK\n");
    else
        printf("Message: %s\n",dataPTR_ErrorMessage());
    printf("INPUT > ");
    fflush(stdin);
    fgets (dataPTR_lastCommand(), 255, stdin);
}