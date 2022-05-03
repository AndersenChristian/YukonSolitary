#ifndef YUKON_GAMECONTROLLER_HEADER_H
#define YUKON_GAMECONTROLLER_HEADER_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../Data/Data_Header.h"

void addCard(const char*);
Card* getCardByIndex(LinkedList* list, int index);
Card* getCardByName(LinkedList* list, char* name);
Card* getLastCard(LinkedList* list);
void printList(LinkedList* list);
void moveCardToStack(Card* cardToMove, Card* destination);
void moveCardToFoundation(LinkedList* foundation, Card* card);
void attemptMovingCardsToFoundation(LinkedList*);
void attemptFoundationMove(char*, char*);

#endif //YUKON_GAMECONTROLLER_HEADER_H
