//Libaries
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Headers
#include "../Data/Data_Header.h"
#include "../Interface/Display_Header.h"
#include "../Interface/Reader_Header.h"
#include "PreGameOperation_Header.h"
#include "GameController_Header.h"

//own methods declaration
void processPlayerInput(char*);
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

    if (strcasecmp(string, "QQ\n") == 0) {
        remove("..\\CurrentSeed.txt");
        if (dataPTR_DeckLoaded())
            deAllocateMalloc();
        printf("\n---Exiting Game---\n");
        exit(0);
    }

    if (!(*dataPTR_DeckLoaded())) {
        if (strstr(string, "LD") != NULL)
            setupCards(dataPTR_lastCommand());
        else
            setErrorMessage("Wrong game command at current stage of the game");
    } else if (!(*dataPTR_GameStarted())) {

        if (strcasecmp(string, "SW\n") == 0) {
            //All functionality of this one is programmed into the display.
            setErrorMessage("OK");
        } else if (strcasecmp(string, "SI\n") == 0) {
            //todo, do something
        } else if (strcasecmp(string, "SR\n") == 0) {
            if (dataPTR_DeckLoaded()) {
                SR();
                setErrorMessage("OK");
            } else {
                setErrorMessage("You must load a deck before shuffeling");
            }
        } else if (strstr(string, "SD") != NULL) {
            if (strlen(string) > 3) {
                SD(&string[3]);
            } else
                setErrorMessage("You must choose a file name");
        } else if (strcasecmp(string, "P\n") == 0) {
            SD("CurrentSeed.txt"); //saves the current card setup.
            P();
            *dataPTR_GameStarted() = true;
            setErrorMessage("OK");
        } else
            setErrorMessage("Wrong game command at current stage of the game");
    } else if (dataPTR_GameStarted()) {
        if (strcasecmp(string, "Q\n") == 0) {             //ensures that a game is in progress.
            setErrorMessage("OK");
            deAllocateMalloc();                                 //removes the current card, and free the memory.
            setupCards(
                    "LD ../currentSeed.txt");                                       //Setup 1 LinkedList containing the cards from CurrentSeed.txt
            *dataPTR_GameStarted() = false;
        }

        if (string[2] == ':' && string[5] == '-' && string[6] == '>') { // Game Move
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
            //bool moveMade = attemptCardMove(fromColumn, card, toColumn);
            //TODO make PlayGame handle error messages
        } else if (string[2] == '-' && string[3] == '>') { // From/To foundation
            char fromColumn[3];
            char toColumn[3];
            memcpy(fromColumn, string, 2);
            memcpy(toColumn, &string[4], 2);

            attemptFoundationMove(fromColumn, toColumn);

        } else {
            //shouldn't happend
            //could implement some reset code here to reset the entire game
        }
    }
}

/**
 *
 * @return
 */
bool winCondition(){
    //todo test for win condition
}