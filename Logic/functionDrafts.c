//
// Created by Frederik on 5/4/2022.
//
#include <stdlib.h>

//Header
#include "../Data/Data_Header.h"
#include "GameController_Header.h"

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
        lastCardTo->prev->next = card;
        card->prev = lastCardTo;
    }
}

