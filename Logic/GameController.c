//Libaries
#include <string.h>

//Header
#include "../Data/Data_Header.h"
#include "GameController_Header.h"

//Own methods declaration
bool moveIsPossible(Card* card, LinkedList* columnTo);
void moveCardToColumn(LinkedList* columnFrom, Card* card, LinkedList* columnTo);
void moveCardFromFoundation(LinkedList* foundation, LinkedList* column);
void moveCardToFoundation(LinkedList* column);
LinkedList* getFoundation(Card*);
int getColumnIndex(char*);
void flipTopCards(LinkedList*);

/**
 * Author: Frederik G. Petersen (S215834)
 *
 * The functions processes the player's input to determine the correct way to act based on how the input is constructed.
 * @param input the input String given by the player.
 */
void gameMove(char* input){
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

        if((input[0] == 'C' && input[4] == 'F') || (input[0] == 'c' && input[4] == 'f')){
            moveCardToFoundation(fromList);
            setErrorMessage("Move Successful");
        }
        if((input[0] == 'F' && input[4] == 'C') || (input[0] == 'f' && input[4] == 'c')){
            moveCardFromFoundation(fromList, toList);
            setErrorMessage("Move Successful");
        }
    }
    else {
        setErrorMessage("Invalid Move");
        return;
    }
}

/**
 * Author: Frederik G. Petersen (S215834)
 *
 * The standard game move, moves a card from a column to the top of another column.
 * @param columnFrom The LinkedList which the card to move resides in
 * @param card The card to move
 * @param columnTo The LinkedList to move the card over to
 */
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
}

/**
 * Author: Frederik G. Petersen (S215834)
 *
 * Moves a card from a foundation to a column.
 * @param foundation From which the foundation the top card is to be moved back into the game
 * @param column The column that the foundation card should be placed on.
 */
void moveCardFromFoundation(LinkedList* foundation, LinkedList* column){
    Card* foundationCard = getLastCard(foundation);
    moveCardToColumn(foundation, foundationCard, column);
}

/**
 * Author: Frederik G. Petersen (S215834)
 *
 * This function is to move a card from a standard column to a foundation.
 * The function determines the corresponding foundation itself.
 * @param column the LinkedList which the last card should attempt to be moved to a foundation.
 */
void moveCardToFoundation(LinkedList* column){
    Card* card = getLastCard(column);
    LinkedList* foundation = getFoundation(card);
    if(foundation == NULL){
        setErrorMessage("Invalid Move");
        return;
    }

    // Validate move
    if (getCardValue(foundation->tail)+1 == getCardValue(card)){
        moveCardToColumn(column, card, foundation);
    } else {
        setErrorMessage("Invalid Move");
        return;
    }
}

/**
 * Author: Frederik G. Petersen (S215834)
 *
 * Checks if the normal game move (Column to Column) is valid.
 * @param card the card which you wish to move
 * @param columnTo the column the card is going to.
 * @return
 */
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

/**
 * Author: Frederik G. Petersen (S215834)
 *
 * This should be called when removing a card from at stack to ensure that thetop card gets flipped.
 * @param list The list to flip the top card on
 */
void flipTopCards(LinkedList* list) {
    Card *currentCard = getLastCard(list);
    if (currentCard->faceUp == false) {
        currentCard->faceUp = true;
    }
}

/**
 * Author: Frederik G. Petersen (S215834)
 *
 * @param card gets the numerical value of a Card.
 * @return numerical value of the card. Returns 0 when passed NULL
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
    }
}

/**
 * Author: Frederik G. Petersen (S215834)
 *
 * Gets the corresponding foundation based on the suit of the card.
 * @param card The card which should be placed in a foundation.
 * @return Return the foundation LinkedList corresponding to the card suit.
 */
LinkedList* getFoundation(Card* card){
    LinkedList* list = dataPTR_ToBoard();
    if (card->name[1] == 'C') return &list[7];
    if (card->name[1] == 'S') return &list[8];
    if (card->name[1] == 'D') return &list[9];
    if (card->name[1] == 'H') return &list[10];
    else return NULL;
}

/**
 * Author: Frederik G. Petersen (S215834)
 *
 * Gets the index of a column/foundation from the column/foundations name
 * @param columnStr the name of the column
 * @return the index of the column.
 */
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
 * Gets the card in a linkedList base on the card name
 * @param list The linkedlist the card should be found int
 * @param name The name of the card
 * @return Returns Card pointer, or NULL if the card does not exists in the linkedlist
 */
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
 *
 * Get's the last card of a LinkedList
 * @param list the LinkedList which the last card should be found in.
 * @return Returns Card pointer, or NULL if there is no card in the linkedlist.
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
 *
 * For debugging linked lists
 * @param list LinkedList to print
 */
void printList(LinkedList* list){

    Card* currentCard = list->head;

    while (currentCard->next != NULL){
        currentCard = currentCard->next;
    }
}