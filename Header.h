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

//enum INPUT{LD,SW,SI,SR,SD,QQ,P,Q}; //TODO might need to be deleted
enum SUITS{C = 0, D = 13, H = 26, S = 39};
enum CARD_VALUES{A = 1,T = 10, J = 11, Q = 12, K = 13};

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
Card* getCard(LinkedList* list, int index);
void printList(LinkedList* list);
void moveCardToStack(Card* cardToMove, Card* destination)


//global variables
#define DECK_SIZE 52+11 //the 11 are dummies for linked lists


//Methods
//Data
void initDeck();
bool isDeckLoaded();
void pushCardToDeck(char name[3]);
LinkedList* getDeck();
LinkedList* getBoard();
void printDeck();
bool isGameWon();
void setLastCommand(char* command);
char* getLastCommand();


//Logic
void setupGame();
void playGame();
bool winCondition();
void shuffle();
void swap(Card*, Card*);
void setupBoard();
void updateBoard();
void saveGame(char* filename);
void exitGame();
void attemptCardMove(char* columnFrom, Card* card, char* columnDest);
int getColumnIndex(char* columnStr);
bool cardCanBePlaced(Card* cardBehind, Card* cardOntop);
enum SUITS getCardSuit(Card* card);
int getCardValue(Card* card);
void flipTopCards();


//Interface
void updateDisplay();
void displayEmpty();
void displayInfolines();

//Reader
void setupCards();

//PlayerInput
char* getPlayerInput();
void processPlayerInput(char string[]);
void showMessage(char* msg);

#endif //YUKON_HEADER_H
