//Libaries
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <shlwapi.h>

//Headers
#include "../Data/Data_Header.h"
#include "../Interface/Display_Header.h"
#include "../Interface/Reader_Header.h"
#include "PreGameOperation_Header.h"
#include "GameController_Header.h"

//own methods declaration
void processPlayerInput(char*);
void QQ();
void Q();
bool winCondition();

extern void playGame() {
    updateDisplay();    //just to create a display the first time
    do {
        processPlayerInput(dataPTR_lastCommand());
        updateDisplay();
    }while(!(*dataPTR_IsGameDone()));
}

/**
 * Author: Frederik G. Petersen (S215834)
 * @param string
 */
// TODO Make better initial comparison to check nothing follows the initials
void processPlayerInput(char* string) {

    if (StrStrIA(string, "QQ\n") != NULL)
        QQ();

    else if (StrStrIA(string, "LD\n") != NULL || StrStrIA(string,"LD ") != NULL) {
        if(!*dataPTR_DeckLoaded())
            setupCards(dataPTR_lastCommand());
        else
            setErrorMessage("Input not accepted at this point in the program");
    }

    else if (StrStrIA(string, "SW\n") != NULL) {
        if (!*dataPTR_GameStarted() && *dataPTR_DeckLoaded() && strlen(string))
            //do nothing
            setErrorMessage("OK");
        else
            setErrorMessage("Wrong Input");
    }

    else if (StrStrIA(string, "SI\n") != NULL || StrStrIA(string, "SI ") != NULL) {
        if (*dataPTR_DeckLoaded() && !*dataPTR_GameStarted())
            SI();
        else
            setErrorMessage("Input not accepted at this point in the program");
    }

    else if (StrStrIA(string, "SR\n") != NULL) {
        if (*dataPTR_DeckLoaded() && !*dataPTR_GameStarted())
            SR();
        else
            setErrorMessage("Input not accepted at this point in the program");
    }

    else if (StrStrIA(string, "SD ") != NULL) {
        if (*dataPTR_DeckLoaded() && !*dataPTR_GameStarted())
            SD(&string[3]);
        else
            setErrorMessage("Input not accepted at this point in the program");
    }

    else if (StrStrIA(string, "P\n") != NULL) {
        if (*dataPTR_DeckLoaded() && !*dataPTR_GameStarted()) {
            SD("currentSeed.txt");
            P();

        }else
            setErrorMessage("Input not accepted at this point in the program");
    }

    else if (StrStrIA(string, "Q\n") != NULL) {
        if (*dataPTR_GameStarted())
            Q();
        else
            setErrorMessage("Input not accepted at this point in the program");
    }

    else if (string[2] == ':' && string[5] == '-' && string[6] == '>') { // Game Move
        // Get everything from input
        char fromColumn[3];
        char card[3];
        char toColumn[3];

        memcpy(fromColumn, string, 2);
        memcpy(card, &string[3], 2);
        memcpy(toColumn, &string[7], 2);

        card[2] = '\0';
        toColumn[2] = '\0';

        // Process it
        bool moveMade = attemptCardMove(fromColumn, card, toColumn);
        //TODO make PlayGame handle error messages
    } else if (string[2] == '-' && string[3] == '>') { // From/To foundation
        char fromColumn[3];
        char toColumn[3];
        memcpy(fromColumn, string, 2);
        memcpy(toColumn, &string[4], 2);

        attemptFoundationMove(fromColumn, toColumn);
    }
}

void QQ(){
    remove("..\\CurrentSeed.txt");
    if (*dataPTR_DeckLoaded())
        deAllocateMalloc();
    printf("\n---Exiting Game---\n");
    exit(0);
}

void Q(){
    setErrorMessage("OK");
    deAllocateMalloc();                                 //removes the current card, and free the memory.
    setupCards("LD ../currentSeed.txt");                //Setup 1 LinkedList containing the cards from CurrentSeed.txt
    *dataPTR_GameStarted() = false;
}

/**
 *
 * @return
 */
bool winCondition(){
    //todo test for win condition
}