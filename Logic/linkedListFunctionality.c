//Libaries
#include <string.h>
#include <malloc.h>

//Headers
#include "../Data/Data_Header.h"

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
        list->length += 1;

    } else { // Every other entry
        Card* oldTail = list->tail;

        oldTail->next = newCard;

        newCard->prev = oldTail;
        newCard->next = NULL;

        list->tail = newCard;

        list->length++;
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

    while (currentCard->next != NULL) {
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
 * @param cardToMove
 * @param destination
 */

// These might need to be moved to logic. --------------------------------------
void moveCardToCard(Card* cardToMove, Card* destination){
    if (cardToMove->prev != NULL){
        cardToMove->prev->next = NULL;
    }
    destination->next = cardToMove;
    cardToMove->prev = destination;
}

void moveCardToColumn(LinkedList* column, Card* card){
    card->prev->next = card->next;

    if(card->next != NULL){
        card->next->prev = card->prev;
    }
    card->prev = NULL;

    column->head = card;
    column->tail = card;
}

void moveCardToFoundation(LinkedList* foundation, Card* cardToMove){
    if (foundation->head == NULL){
        foundation->head = cardToMove;
        foundation->tail = cardToMove;
    } else {
        foundation->tail->next = cardToMove;
        cardToMove->prev = foundation->tail;
        foundation->tail = cardToMove;
    }
}

void moveCardFromFoundation(LinkedList* foundation, LinkedList* columnDest){

}

/**
 * Author: Frederik G. Petersen (S215834)
 * @param list
 */
void printList(LinkedList* list){

    Card* currentCard = list->head;

    while (currentCard->next != NULL){
        printf("%s\t", currentCard->name);
        currentCard = currentCard->next;
    }
    printf("%s\n", currentCard->name);
}