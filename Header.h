//
// Created by Christian Andersen on 02-04-2022.
//
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef YUKON_HEADER_H
#define YUKON_HEADER_H

typedef struct Card Card;
typedef struct LinkedList LinkedList;

typedef enum {C = 0, D, H, S} CARD_SUITS;

// --- Structs ---
struct Card {
    char name[3];
    bool faceUp;
    Card* prev;
    Card* next;
};

struct LinkedList {
    int length;
    Card* head;
    Card* tail;
};

void addCard(LinkedList* list, Card* pCard);
Card* getCardByIndex(LinkedList* list, int index);
Card* getCardByName(LinkedList* list, char* name);
Card* getLastCard(LinkedList* list);
void printList(LinkedList* list);
void moveCardToStack(Card* cardToMove, Card* destination);
void moveCardToFoundation(LinkedList* foundation, Card* card);


//global variables
#define DECK_SIZE (52)


//Methods
//Data
void pushCardToDeck(char name[3]);
LinkedList* dataPTR_ToDeck();
LinkedList* dataPTR_ToBoard();
char* dataPTR_lastCommand();
char* dataPTR_ErrorMessage();
bool* dataPTR_DeckLoaded();
bool* dataPTR_IsGameDone();
bool* dataPTR_GameStarted();
void setErrorMessage(char*);



//Logic
void setupGame();
void playGame();
bool winCondition();
void shuffle();
void setupBoard();
void updateBoard();
void saveGame(char* filename);
void exitGame();
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


//Interface
void updateDisplay();
void gameDisplay();
void displayEmpty();
void displayInfolines();
void defaultDisplay();

//Reader
void setupCards(char*);
bool validateDeck();

//PlayerInput
void getPlayerInput();
void processPlayerInput(char string[]);

#endif //YUKON_HEADER_H
