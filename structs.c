#include "Header.h"

/**
 * Author: Frederik G. Petersen (S215834)
 * @param list
 * @param pCard
 */
void addCard(LinkedList* list, Card* pCard){
    Card* newCard = malloc(sizeof (Card));
    newCard->name[0] = pCard->name[0];
    newCard->name[1] = pCard->name[1];
    newCard->name[2] = pCard->name[2];
    newCard->next = pCard->next;
    newCard->prev = pCard->prev;
    newCard->faceUp = pCard->faceUp;

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
Card* getCard(LinkedList* list, int index){
    if (list->length <= 0) printf("List has length 0");

    Card* currentCard = list->head;
    for (int i = 0; i < list->length; ++i) {
        if (i == index){
            return currentCard;
        } else {
            currentCard = currentCard->next;
        }
    }
    return currentCard;
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
void moveCardToStack(Card* cardToMove, Card* destination){
    cardToMove->prev->next = cardToMove->next;
    cardToMove->next->prev = cardToMove->prev;

    destination->next = cardToMove;
    cardToMove->prev = destination;
    cardToMove->next = NULL;

}
/**
 * Author: Frederik G. Petersen (S215834)
 * @param list
 */
void printList(LinkedList* list){
    printf("List length: %d \t", list->length);

    Card* currentCard = list->head;

    while (currentCard->next != NULL){
        printf("%s\t", currentCard->name);
        currentCard = currentCard->next;
    }
    printf("%s\n", currentCard->name);
}