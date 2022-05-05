/*
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

void moveCardFromFoundation(LinkedList* foundation, LinkedList* column){
    Card* foundationCard = getLastCard(foundation);
    moveCardToColumn(foundation, foundationCard, column);
}


void moveCardToFoundation(LinkedList* column){
    Card* card = getLastCard(column);

    char suit = card->name[1];
    LinkedList* foundation = NULL;

    if (suit == 'C'){ foundation = &dataPTR_ToBoard()[7]; }
    if (suit == 'S'){ foundation = &dataPTR_ToBoard()[8]; }
    if (suit == 'D'){ foundation = &dataPTR_ToBoard()[9]; }
    if (suit == 'H'){ foundation = &dataPTR_ToBoard()[10]; }

    // Validate move
    if (getCardValue(foundation->tail)+1 == getCardValue(card)){
        moveCardToColumn(column, card, foundation);
    }
}


bool moveIsPossible(LinkedList* columnFrom, Card* card, LinkedList* columnTo){
    Card* cardBehind = card;
    Card* cardOnTop = getLastCard(columnTo);

    // King exception
    if(cardOnTop == NULL){
        if(card->name[0] == 'K'){
            return true;
        }
    }


    // Suits
    if (getCardSuit(cardBehind) != getCardSuit(cardOntop)){
        if (getCardValue(cardBehind) == getCardValue(cardOntop) +1){
            return true;
        }
    }
    return false;

}
*/