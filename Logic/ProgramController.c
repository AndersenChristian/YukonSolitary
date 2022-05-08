//Libraries
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
bool gameWon();

/**
 * Author: Christian J. L. Andersen (S133288)
 */
extern void playGame() {
    updateDisplay();    //just to create a display the first time
    do {
        processPlayerInput(dataPTR_lastCommand());
        updateDisplay();
    }while(!gameWon());
}

/**
 * Author: Frederik G. Petersen (S215834) 50% & Christian J. L. Andersen (S133288) 50%
 *
 * compares the users input, to figure out what part of the program the users want access to.
 *
 * Also contains
 *
 * @param string that contains the users last input
 */
void processPlayerInput(char* string) {

    if (StrStrIA(string, "QQ\n") != NULL)
        QQ();

    else if (StrStrIA(string, "LD\n") != NULL || StrStrIA(string,"LD ") != NULL) {
        if(!*dataPTR_DeckLoaded())
            loadDeckFromFile(dataPTR_lastCommand());
        else
            setErrorMessage("Input not accepted at this point in the program");
    }

    else if (StrStrIA(string, "SW\n") != NULL) {
        if (!*dataPTR_GameStarted() && *dataPTR_DeckLoaded() && strlen(string))
            //do nothing
            setErrorMessage("OK");
        else
            setErrorMessage("Input not accepted at this point in the program");
    }

    else if (StrStrIA(string, "SI\n") != NULL || StrStrIA(string, "SI ") != NULL) {
        if (*dataPTR_DeckLoaded() && !*dataPTR_GameStarted())
            SI();
        else
            setErrorMessage("Input not accepted at this point in the program");
    }

    else if (StrStrIA(string, "SR\n") != NULL) {
        if (*dataPTR_DeckLoaded() && !*dataPTR_GameStarted()) {
            SR();
            setErrorMessage("OK");
        }
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

    else if (*dataPTR_GameStarted()){
        gameMove(string);
    }

    else{
        setErrorMessage("The command is not recognised, try again");
    }
}

/**
 * Author: Christian J. L. Andersen (S133288)
 *
 * this is used for closing the program and ensuring that we free up any memory we might have reserved
 */
void QQ(){
    remove("..\\CurrentSeed.txt");
    if (*dataPTR_DeckLoaded())
        deAllocateMalloc();
    printf("\n---Exiting Game---\n");
    exit(0);
}

/**
 * Author: Christian J. L. Andersen (S133288)
 *
 * takes the program back from the play mode into pre game mode.
 *
 * this is done by de allocating the memory of the cards in play, and reloading the original setup of cards
 * that were saved when the game was initially started
 */
void Q(){
    setErrorMessage("OK");
    deAllocateMalloc();                                     //removes the current card, and free the memory.
    loadDeckFromFile("LD ../currentSeed.txt");              //Setup 1 LinkedList containing the cards from CurrentSeed.txt
    *dataPTR_GameStarted() = false;
}

/**
 * Author: Christian J. L. Andersen (S133288)
 *
 * checks if all foundation have a king on them since that will mean the game has been beaten
 *
 * @return whether the game have been won
 */
bool gameWon(){
    if (!*dataPTR_GameStarted())
        return false;
    LinkedList* board = dataPTR_ToBoard();
    if (board[8].tail != NULL && board[8].tail->name[0] == 'K' &&
        board[9].tail != NULL && board[9].tail->name[0] == 'K' &&
        board[10].tail != NULL && board[10].tail->name[0] == 'K' &&
        board[11].tail != NULL && board[11].tail->name[0] == 'K' )
        return true;
    return false;
}