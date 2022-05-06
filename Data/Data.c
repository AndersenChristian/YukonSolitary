//Libaries
#include "Data_Header.h"
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

LinkedList deck;
LinkedList boardSlots[11]; //0-6 Cards, 7-11 Foundations

char lastCommand[255] = "\n";
char errorMessage[255]; //set by the various methods of the program to proper display if anything goes wrong.

//the following boolean values are used to keep a track of the current game-state
bool deckLoaded = false;
bool gameStarted = false;

LinkedList* dataPTR_ToDeck(){
    return &deck;
}

LinkedList* dataPTR_ToBoard(){
    return boardSlots;
}

char* dataPTR_lastCommand(){
    return lastCommand;
}

char* dataPTR_ErrorMessage(){
    return errorMessage;
}

bool* dataPTR_DeckLoaded(){
    return &deckLoaded;
}

bool* dataPTR_GameStarted(){
    return &gameStarted;
}

void setErrorMessage(char* message){
    strcpy(errorMessage, message);
}


/**
 * Author: Frederik G. Petersen (S215834)
 * @param list
 * @param pCard
 */
void addCard(const char* cardInfo){
    LinkedList* list = dataPTR_ToDeck();
    Card* newCard = malloc(sizeof (Card));
    newCard->name[0] = cardInfo[0];
    newCard->name[1] = cardInfo[1];
    newCard->name[2] = '\0';
    newCard->next = NULL;
    newCard->prev = list->tail;
    newCard->faceUp = false;

    if (list->head == NULL){ // First entry
        list->head = newCard;
        list->tail = newCard;

    } else { // Every other entry
        Card* oldTail = list->tail;

        oldTail->next = newCard;

        newCard->prev = oldTail;
        newCard->next = NULL;

        list->tail = newCard;
    }
}

/**
 * Author: Frederik G. Petersen (S215834)
 *
 * @param card gets the numerical value of a Card.
 * @return numerical value of the card. Returns 0 when passed NULL
 */
int getCardValue(Card* card){
    if (card == NULL) return 0;
    switch (card->name[0]) {
        case 'A': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'T': return 10;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
        default: return 0;
    }
}

/**
 * Author: Frederik G. Petersen (S215834)
 *
 * Extracts the card's suit from the name of a card
 * @param card
 * @return ENUM of Card_Suits
 */
CARD_SUITS getCardSuit(Card* card){
    switch (card->name[1]) {
        case 'S': return S;
        case 'D': return D;
        case 'H': return H;
        case 'C': return C;
        default: return 0;
    }
}