//Libraries
#include <string.h>
#include <stdbool.h>

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
Card* getCardByName(LinkedList* list, char* name);
Card* getLastCard(LinkedList* list);

/**
 * Author: Frederik G. Petersen (S215834)
 *
 * The functions processes the player's input to determine the correct way to act based on how the input is constructed.
 * @param input the input String given by the player.
 */
void gameMove(char* input){
    if(input[2] == ':' && input[5] == '-' && input[6] == '>'){
        // Segments the string to substrings
        char columnFrom[3];
        char cardName[3];
        char columnTo[3];
        memcpy(columnFrom, input, 2);
        memcpy(cardName, &input[3], 2);
        memcpy(columnTo, &input[7], 2);
        cardName[2] = '\0';
        columnTo[2] = '\0';

        // Get relevant objects
        LinkedList* fromList = &dataPTR_ToBoard()[getColumnIndex(columnFrom)];
        LinkedList* toList = &dataPTR_ToBoard()[getColumnIndex(columnTo)];
        if (fromList == toList){
            setErrorMessage("Invalid Move");
            return;
        }

        Card* card = getCardByName(fromList, cardName);

        // Ensure no NULL pointers
        if(card == NULL || fromList == NULL || toList == NULL){
            setErrorMessage("Invalid Move");
            return;
        }

        if(moveIsPossible(card, toList)){
            moveCardToColumn(fromList, card, toList);
            flipTopCards(fromList);
            setErrorMessage("Move Successful");
        }else{
            setErrorMessage("Invalid Move");
        };

    }
    else if(input[2] == '-' && input[3] == '>'){
        // Segments string to substrings
        char columnFrom[3];
        char columnTo[3];
        memcpy(columnFrom, input, 2);
        memcpy(columnTo, &input[4], 2);

        // Get relevant objects
        LinkedList* fromList = &dataPTR_ToBoard()[getColumnIndex(columnFrom)];
        LinkedList* toList = &dataPTR_ToBoard()[getColumnIndex(columnTo)];
        
        if((input[0] == 'C' || input[0] == 'c') && (input[4] == 'F' || input[4] == 'f')){
            moveCardToFoundation(fromList);
        }
        else if((input[0] == 'F' || input[0] == 'f') && (input[4] == 'C' || input[4] == 'c')){
            moveCardFromFoundation(fromList, toList);
        } else {
            setErrorMessage("Invalid Move");
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

    setErrorMessage("Move Successful");
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
    if(moveIsPossible(foundationCard, column)){
        moveCardToColumn(foundation, foundationCard, column);
    } else {
        setErrorMessage("Invalid move");
    }
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
    if(card == NULL){
        setErrorMessage("Invalid move");
        return;
    }

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
    if (card->faceUp == false){
        return false;
    }

    Card* cardBehind = getLastCard(columnTo);
    Card* cardOnTop = card;

    // King exception
    if(cardBehind == NULL){
        if(card->name[0] == 'K'){
            return true;
        }
    } else

    // Suits
    if (getCardSuit(cardBehind) != getCardSuit(cardOnTop)
        && getCardValue(cardBehind) == getCardValue(cardOnTop) +1)
        return true;

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
    return -1;
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