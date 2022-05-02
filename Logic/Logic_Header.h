//
// Created by Christian Andersen on 29-04-2022.
//
#include <stdbool.h>
#include "../Data/Data_Header.h"

#ifndef YUKON_LOGIC_HEADER_H
#define YUKON_LOGIC_HEADER_H

void playGame();
bool winCondition();
void shuffle();
void setupBoard();
void updateBoard();
void saveGame(char* filename);
bool attemptCardMove(char* columnFrom, char* card, char* columnDest);
void attemptMovingCardsToFoundation(LinkedList* list);
int getColumnIndex(char* columnStr);
bool cardCanBePlaced(Card* cardBehind, Card* cardOntop);
CARD_SUITS getCardSuit(Card* card);
int getCardValue(Card* card);
LinkedList* getFoundation(Card* card);
void flipTopCards();
void loadDeck();
void deAllocateMalloc();
void processPlayerInput(char*);

#endif //YUKON_LOGIC_HEADER_H
