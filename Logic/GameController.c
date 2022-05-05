//Libaries
#include <string.h>

//Header
#include "../Data/Data_Header.h"
#include "GameController_Header.h"

//Own methods declaration
bool cardCanBePlaced(Card*, Card*);
CARD_SUITS getCardSuit(Card*);
LinkedList* getFoundation(Card*);
int getColumnIndex(char*);
void flipTopCards(LinkedList*);
int getCardValue(Card*);

bool moveIsPossible(Card* card, LinkedList* columnTo);
void moveCardToColumn(LinkedList* columnFrom, Card* card, LinkedList* columnTo);
void moveCardFromFoundation(LinkedList* foundation, LinkedList* column);
void moveCardToFoundation(LinkedList* column);


void gameMove(char* input){
    // TODO make these not case sensitive
    if(input[2] == ':' && input[5] == '-' && input[6] == '>'){
        char columnFrom[3];
        char cardName[3];
        char columnTo[3];
        memcpy(columnFrom, input, 2);
        memcpy(cardName, &input[3], 2);
        memcpy(columnTo, &input[7], 2);
        cardName[2] = '\0';
        columnTo[2] = '\0';

        LinkedList* fromList = &dataPTR_ToBoard()[getColumnIndex(columnFrom)];
        LinkedList* toList = &dataPTR_ToBoard()[getColumnIndex(columnTo)];
        Card* card = getCardByName(fromList, cardName);

        if(moveIsPossible(card, toList)){
            moveCardToColumn(fromList, card, toList);
            flipTopCards(fromList);
            setErrorMessage("Move Successful");
        }else{
            setErrorMessage("Invalid Move");
        };

    }
    else if(input[2] == '-' && input[3] == '>'){
        char columnFrom[3];
        char columnTo[3];
        memcpy(columnFrom, input, 2);
        memcpy(columnTo, &input[4], 2);
        LinkedList* fromList = &dataPTR_ToBoard()[getColumnIndex(columnFrom)];
        LinkedList* toList = &dataPTR_ToBoard()[getColumnIndex(columnTo)];

        if(input[0] == 'C' && input[4] == 'F'){
            moveCardToFoundation(fromList);
            setErrorMessage("Move Successful");
        }
        if(input[0] == 'F' && input[4] == 'C'){
            moveCardFromFoundation(fromList, toList);
            setErrorMessage("Move Successful");
        }
    }
    else {
        setErrorMessage("Invalid Move");
        return;
    }
}

void moveCardToColumn(LinkedList* columnFrom, Card* card, LinkedList* columnTo){
    // Get info
    Card* lastCardFrom = getLastCard(columnFrom);
    Card* lastCardTo = getLastCard(columnTo);

    // Change FROM head and tails
    if(card == columnFrom->head){
        columnFrom->head = NULL;
        columnFrom->tail = NULL;
    } else {
        columnFrom->tail = card->prev;
    }

    // Change TO head and tails
    if(columnTo->head == NULL){
        columnTo->head = card;
    }
    columnTo->tail = lastCardFrom;

    // Detach
    if(card->prev != NULL){
        card->prev->next = NULL;
        card->prev = NULL;
    }

    // Connect
    if (lastCardTo != NULL){
        lastCardTo->next = card;
        card->prev = lastCardTo;
    }
    printf("Test");
}

void moveCardFromFoundation(LinkedList* foundation, LinkedList* column){
    Card* foundationCard = getLastCard(foundation);
    moveCardToColumn(foundation, foundationCard, column);
}

void moveCardToFoundation(LinkedList* column){
    Card* card = getLastCard(column);

    char suit = card->name[1];
    LinkedList* foundation = NULL;

    if (suit == 'C'){ foundation = &dataPTR_ToBoard()[7]; }
    else if (suit == 'S'){ foundation = &dataPTR_ToBoard()[8]; }
    else if (suit == 'D'){ foundation = &dataPTR_ToBoard()[9]; }
    else if (suit == 'H'){ foundation = &dataPTR_ToBoard()[10]; }
    else{
        setErrorMessage("Invalid Move");
        return;
    }

    // Validate move
    if (getCardValue(foundation->tail)+1 == getCardValue(card)){
        moveCardToColumn(column, card, foundation);
    }
}

bool moveIsPossible(Card* card, LinkedList* columnTo){
    Card* cardBehind = getLastCard(columnTo);
    Card* cardOnTop = card;

    // King exception
    if(cardBehind == NULL){
        if(card->name[0] == 'K'){
            return true;
        }
    } else

    // Suits
    if (getCardSuit(cardBehind) != getCardSuit(cardOnTop)){
        if (getCardValue(cardBehind) == getCardValue(cardOnTop) +1){
            return true;
        }
    }
    return false;
}












/*
bool attemptCardMove(char* columnFrom, char* cardName, char* columnDest){
    // Find card in from-column
    LinkedList* fromList = &dataPTR_ToBoard()[getColumnIndex(columnFrom)];
    LinkedList* toList = &dataPTR_ToBoard()[getColumnIndex(columnDest)];
    Card* fromCard = getCardByName(fromList, cardName);
    Card* toCard = getLastCard(toList);

    // King to Empty Column
    if (toList->head == NULL){
        if (fromCard->name[0] == 'K'){
            moveCardToColumn(toList, fromCard);
        } else {
            setErrorMessage("Invalid move");
            return false;
        }
    }

        // Normal move
    else if (columnFrom[0] == 'C' && columnDest[0] == 'C'){
        if (fromCard == NULL || toCard == NULL){
            setErrorMessage("Move is Invalid!");
            return false;
        }
        if (cardCanBePlaced(toCard, fromCard)){
            moveCardToCard(fromCard, toCard);
            flipTopCards(fromList);
            setErrorMessage("Card Moved");
            return true;
        }
    }
}

void attemptFoundationMove(char* columnFrom, char* columnDest){
    LinkedList* fromList = &dataPTR_ToBoard()[getColumnIndex(columnFrom)];
    LinkedList* toList = &dataPTR_ToBoard()[getColumnIndex(columnDest)];

    if (columnFrom[0] == 'C' && columnDest[0] == 'F'){ // To Foundation

        Card* card = getLastCard(fromList);

        // Get correct Foundation.
        char suit = card->name[1];
        LinkedList* foundation = NULL;

        if (suit == 'C'){ foundation = &dataPTR_ToBoard()[7]; }
        if (suit == 'S'){ foundation = &dataPTR_ToBoard()[8]; }
        if (suit == 'D'){ foundation = &dataPTR_ToBoard()[9]; }
        if (suit == 'H'){ foundation = &dataPTR_ToBoard()[10]; }

        if (foundation == NULL){
            setErrorMessage("Move Is Invalid");
            return;
        }

        // See if it's a valid move
        if (getCardValue(foundation->tail)+1 == getCardValue(card)){
            // Disconnect Card
            if (card->prev == NULL){ // Last card in stack
                fromList->head = NULL;
                fromList->tail = NULL;

            } else { // not last
                fromList->tail = fromList->tail->prev;
                card->prev->next = NULL;
                card->prev = NULL;
            }

            moveCardToFoundation(foundation, card);
        } else {
            setErrorMessage("Move is Invalid");
        }
    }

    if (columnFrom[0] == 'F' && columnDest[0] == 'C') { // Back from foundation
        Card* foundationCard = getLastCard(fromList);
        Card* columnCard = getLastCard(toList);

        // Disconnect it from foundation
        if (foundationCard->prev == NULL){
            fromList->head = NULL;
            fromList->tail = NULL;
        } else {
            foundationCard->prev->next = NULL;
            foundationCard->prev = NULL;
        }

        //
        if (cardCanBePlaced(columnCard, foundationCard)){
            moveCardToCard(foundationCard, columnCard);
        }
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
*/


void flipTopCards(LinkedList* list) {
    Card *currentCard = getLastCard(list);
    if (currentCard->faceUp == false) {
        currentCard->faceUp = true;
    }
}

/**
 * Author: Frederik G. Petersen (S215834)
 * @param card
 * @return
 */
int getCardValue(Card* card){
    if (card==NULL) return 0;
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


/**
 * Author: Frederik G. Petersen (S215834)
 * @param list
 * @param pCard
 */
// TODO might not be used, since length never gets updated
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
 * @param list
 * @param index
 * @return
 */
Card* getCardByIndex(LinkedList* list, int index){
    // TODO rewrite since length cannot be used:
    /*
    Card* currentCard = list->head;
    for (int i = 0; i < list->length; ++i) {
        if (i == index){
            return currentCard;
        } else {
            currentCard = currentCard->next;
        }
    }
    return currentCard;
     */
}

Card* getCardByName(LinkedList* list, char* name){
    Card* currentCard = list->head;

    while (currentCard != NULL) {
        if (strcasecmp(currentCard->name, name) == 0){
            return currentCard;
        }
        currentCard = currentCard->next;
    }

    return NULL;
}

/**
 * Author: Frederik G. Petersen (S215834)
 * @param list
 * @return
 */
Card* getLastCard(LinkedList* list){
    Card* currentCard = list->head;
    while (currentCard != NULL){
        if (currentCard->next == NULL) break;
        currentCard = currentCard->next;
    }
    return currentCard;
}

/**
 * Author: Frederik G. Petersen (S215834)
 * @param list
 */
void printList(LinkedList* list){

    Card* currentCard = list->head;

    while (currentCard->next != NULL){
        currentCard = currentCard->next;
    }
}