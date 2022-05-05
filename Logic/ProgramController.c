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
bool gameWon();

extern void playGame() {
    updateDisplay();    //just to create a display the first time
    do {
        processPlayerInput(dataPTR_lastCommand());
        updateDisplay();
    }while(!gameWon());
}

/**
 * Author: Frederik G. Petersen (S215834)
 * @param string
 */
// TODO Make better initial comparison to check nothing follows the initials
// TODO ensure all errormessage is getting set correct
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

    else if (*dataPTR_GameStarted()){
        gameMove(string);
    }

    else{
        setErrorMessage("The command is not recognised, try again");
    }
}

/**
 * Author: Christian J. L. Andersen (S133288)
 * todo write docs
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
 * todo write docs
 */
void Q(){
    setErrorMessage("OK");
    deAllocateMalloc();                                 //removes the current card, and free the memory.
    setupCards("LD ../currentSeed.txt");                //Setup 1 LinkedList containing the cards from CurrentSeed.txt
    *dataPTR_GameStarted() = false;
}

/**
 * Author: Christian J. L. Andersen (S133288)
 * todo write docs
 * @return
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