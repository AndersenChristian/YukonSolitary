#ifndef YUKON_GAMECONTROLLER_HEADER_H
#define YUKON_GAMECONTROLLER_HEADER_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../Data/Data_Header.h"

void gameMove(char* input);
bool attemptCardMove(char*, char*, char*);
void addCard(const char*);
Card* getCardByIndex(LinkedList* list, int index);
Card* getCardByName(LinkedList* list, char* name);
Card* getLastCard(LinkedList* list);
void printList(LinkedList* list);
void attemptFoundationMove(char*, char*);


#endif //YUKON_GAMECONTROLLER_HEADER_H
