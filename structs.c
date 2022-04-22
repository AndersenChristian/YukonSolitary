//
// Created by Frederik on 4/22/2022.
//

#include "Header.h"

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
}

void printList(LinkedList* list){
    printf("List length: %d \t", list->length);

    Card* currentCard = list->head;

    while (currentCard->next != NULL){
        printf("%s\t", currentCard->name);
        currentCard = currentCard->next;
    }
    printf("%s\t", currentCard->name);
}