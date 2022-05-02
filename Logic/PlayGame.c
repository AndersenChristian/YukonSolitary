//Libaries
#include <string.h>

//Header
#include "../Data/Data_Header.h"
#include "Header.h"

//Own methods declaration
bool cardCanBePlaced(Card*, Card*);
CARD_SUITS getCardSuit(Card*);
LinkedList* getFoundation(Card*);
int getColumnIndex(char*);
void flipTopCards(LinkedList*);
void attemptMovingCardsToFoundation(LinkedList*);
int getCardValue(Card*);

/**
 * Author: Frederik G. Petersen (S215834)
 * @param columnFrom
 * @param cardName
 * @param columnDest
 */
bool attemptCardMove(char* columnFrom, char* cardName, char* columnDest){
    // Find card in from-column
    LinkedList fromList = dataPTR_ToBoard()[getColumnIndex(columnFrom)];
    LinkedList toList = dataPTR_ToBoard()[getColumnIndex(columnDest)];
    Card* fromCard = getCardByName(&fromList, cardName);
    Card* toCard = getLastCard(&toList);

    if (fromCard == NULL || toCard == NULL){
        setErrorMessage("Move is Invalid!");
        return false;
    }

    if (cardCanBePlaced(toCard, fromCard)){
        moveCardToStack(fromCard, toCard);
        flipTopCards(&fromList);
        setErrorMessage("Card Moved");
        // TODO Check if it works when having implemented showing foundations
        attemptMovingCardsToFoundation(&fromList);
        return true;
    }
}

void attemptMovingCardsToFoundation(LinkedList* list){
    Card* card = getLastCard(list);
    LinkedList foundation = *getFoundation(card);
    Card* foundationCard = foundation.tail;

    if (foundationCard == NULL){ // Only for Aces
        if (getCardValue(card) == 1){
            moveCardToFoundation(&foundation, card);
            //attemptMovingCardsToFoundation(list); // Get back when no infinite loop
        }

    } else if (getCardValue(foundationCard)+1 == getCardValue(card)){
        // For rest
        moveCardToFoundation(&foundation, card);
        //attemptMovingCardsToFoundation(list); // Get back when no infinite loop
    }
}

bool cardCanBePlaced(Card* cardBehind, Card* cardOntop){
    // Suits
    if (getCardSuit(cardBehind) != getCardSuit(cardOntop)){
        if (getCardValue(cardBehind) == getCardValue(cardOntop) +1){
            return true;
        }
    }
    return false;
}

void flipTopCards(LinkedList* list){
    Card* currentCard = getLastCard(list);
    if (currentCard->faceUp == false){
        currentCard->faceUp = true;
    }

}

/**
 * Author: Frederik G. Petersen (S215834)
 * @param card
 * @return
 */
int getCardValue(Card* card){
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
    }
}

/**
 * Author: Frederik G. Petersen (S215834)
 * @param card
 * @return
 */
CARD_SUITS getCardSuit(Card* card){
    switch (card->name[1]) {
        case 'S': return S;
        case 'D': return D;
        case 'H': return H;
        case 'C': return C;
    }
}

LinkedList* getFoundation(Card* card){
    LinkedList* list = dataPTR_ToBoard();
    if (card->name[1] == 'C') return &list[7];
    if (card->name[1] == 'S') return &list[8];
    if (card->name[1] == 'D') return &list[9];
    if (card->name[1] == 'H') return &list[10];
}

int getColumnIndex(char* columnStr){
    if (strcasecmp(columnStr, "C1") == 0) {return 0;}
    if (strcasecmp(columnStr, "C2") == 0) {return 1;}
    if (strcasecmp(columnStr, "C3") == 0) {return 2;}
    if (strcasecmp(columnStr, "C4") == 0) {return 3;}
    if (strcasecmp(columnStr, "C5") == 0) {return 4;}
    if (strcasecmp(columnStr, "C6") == 0) {return 5;}
    if (strcasecmp(columnStr, "C7") == 0) {return 6;}
    if (strcasecmp(columnStr, "F1") == 0) {return 7;}
    if (strcasecmp(columnStr, "F2") == 0) {return 8;}
    if (strcasecmp(columnStr, "F3") == 0) {return 9;}
    if (strcasecmp(columnStr, "F4") == 0) {return 10;}
}