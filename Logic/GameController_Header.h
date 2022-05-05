#ifndef YUKON_GAMECONTROLLER_HEADER_H
#define YUKON_GAMECONTROLLER_HEADER_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../Data/Data_Header.h"

void gameMove(char* input);
void addCard(const char*);
Card* getCardByName(LinkedList* list, char* name);
Card* getLastCard(LinkedList* list);
void printList(LinkedList* list);

#endif //YUKON_GAMECONTROLLER_HEADER_H
