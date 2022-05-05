#ifndef YUKON_DATA_HEADER_H
#define YUKON_DATA_HEADER_H

#include <stdbool.h>

//Enums
typedef enum {C = 0, D, H, S} CARD_SUITS;

// --- Structs ---
typedef struct Card Card;
typedef struct LinkedList LinkedList;

struct Card {
    char name[3];
    bool faceUp;
    Card* prev;
    Card* next;
};

struct LinkedList {
    Card* head;
    Card* tail;
};

//Global variables
#define DECK_SIZE (52)

//Data access methods
LinkedList* dataPTR_ToDeck();
LinkedList* dataPTR_ToBoard();
char* dataPTR_lastCommand();
char* dataPTR_ErrorMessage();
bool* dataPTR_DeckLoaded();
bool* dataPTR_GameStarted();
void setErrorMessage(char*);

//Enum translation methods
CARD_SUITS getCardSuit(Card*);
int getCardValue(Card*);

//Add a new card to Deck
void addCard(const char*);

#endif //YUKON_DATA_HEADER_H
