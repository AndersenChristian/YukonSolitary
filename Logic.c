//
// Created by Christian Andersen on 01-04-2022.
//
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Header.h"

extern void playGame() {
    updateDisplay();
    do {
        processPlayerInput(getPlayerInput());
        updateBoard();
        updateDisplay();
    }while(!isGameWon());
}

bool winCondition(){
    //todo test for win condition
}

void shuffle() { //TODO redo with task described setup.
    LinkedList deck = *getDeck();
    Card *cardH = deck.head;
    Card *cardN = cardH->next;
    Card *card1 = cardH;
    Card *cardP = cardH;
    int j = 0;
    srand(time(NULL));
    while (j < 10000){
        int randomNumber = (rand()%52)+1;
        for (int i = 0; i <= randomNumber; ++i) {
            card1 = card1->next;
        }
        cardP->prev = cardH;
        cardH->prev = card1;
        cardH->next->prev = NULL;

        deck.head = cardN;
        cardH->next = cardP;
        card1->next = cardH;
        cardP = card1->next;
        j++;
    }
}

void setupBoard(){
    Card * ptrToCard = getDeck()->head;
    LinkedList* boardSlots = getBoard();

    for (int i = 0; i<7; i++){ //create the first point in the linked list
        boardSlots[i].head = ptrToCard;
        boardSlots[i].tail = ptrToCard;
        if (i == 0)
            ptrToCard->faceUp = true;
        ptrToCard = ptrToCard->next;
        boardSlots[i].head->next = NULL;
        boardSlots[i].head->prev = NULL;
    }

    int cardsPerPile[] = {0,5,6,7,8,9,10};
    int currentList = 0;
    int amountOfCardsUsed = 7;
    do {
        if (cardsPerPile[currentList] != 0) {
            Card *currentSlotsLastCard = boardSlots[currentList].tail;
            currentSlotsLastCard->next = ptrToCard;
            ptrToCard->prev = currentSlotsLastCard;
            boardSlots[currentList].tail = ptrToCard;
            if (cardsPerPile[currentList] < 6)
                ptrToCard->faceUp = true;
            ptrToCard = ptrToCard->next;
            boardSlots[currentList].tail->next=NULL;
            cardsPerPile[currentList]--;
            amountOfCardsUsed++;
        }
        //ensure we get around
        if (currentList == 6)
            currentList = 0;
        else
            currentList++;
    } while (amountOfCardsUsed != 52);
}

void saveGame(char* filename){
    FILE *fp;
    if(strcspn(filename,".txt") == strlen(filename)){
        setErrorMessage("Wrong file type");
        return;
    }
    char filePath[100] = "../";
    strcat(filePath,filename);
    filePath[strcspn(filePath,"\n")]=0;
    fp = fopen (filePath, "w");
    if (getDeck()->head != NULL){
        Card* card = getDeck()->head;
        fputs(card->name, fp);
        fputs("\n",fp);
        while(card->next != NULL){
            card = card->next;
            fputs(card->name, fp);
            fputs("\n",fp);
        }
    }
    fclose(fp);
}

void updateBoard(){
    //flipTopCards();
    //TODO Make this function
    //MoveCardsToFoundations();
}

void processPlayerInput(char* string){
    //printf("Inputted String: %s\n", string); //todo: delete after testing

    setLastCommand(string);

    if (string[2] == ':' && string[5] == '-' && string[6] == '>'){ // Game Move
        // Get everything from input
        char fromColumn[3];
        char card[3];
        char toColumn[3];

        memcpy(fromColumn, string, 2);
        memcpy(card, &string[3], 2);
        memcpy(toColumn, &string[7], 2);

        card[2] = '\0';
        toColumn[2] = '\0';

        // Process it
        //attemptCardMove(fromColumn, card, toColumn);

    } else {
        char initials[3];
        memcpy(initials, string, 2);
        //printf("Initials: %s\n", initials); //TODO: delete after testing

        // Things to process
        if (strcmp(initials, "LD") == 0){
            if (!isDeckLoaded())
                setupCards();
            else
                setErrorMessage("Deck already loaded");
        } else if (strcmp(initials, "SW") == 0){

        } else if (strcmp(initials, "SI") == 0){

        } else if (strcmp(initials, "SR") == 0){

        } else if (strcmp(initials, "SD") == 0){
            if (isDeckLoaded()) {
                if(strlen(string) > 3) {
                    char *filename = &string[3];
                    saveGame(filename);
                } else
                    setErrorMessage("You must choose a file name");
            }else
                setErrorMessage("You must first load i file to save it");
        } else if (strcmp(initials, "QQ") == 0){
            remove("..\\CurrentSeed.txt");
            if(isDeckLoaded())
                deAllocateMalloc();
            printf("\n---Exiting Game---\n");
            exit(0);
        } else if (strcmp(initials, "P\n") == 0){
            if(getGameStarted())
                setErrorMessage("Game already in progress");
            else if(isDeckLoaded()) {
                saveGame("CurrentSeed.txt"); //saves the current card setup.
                setupBoard();
            }else{
                setErrorMessage("Must load a deck, before you can start the game");
            }
        } else if (strcmp(initials, "Q\n") == 0){
            if (hasGameStarted()) {
                setGameStarted(false);
                setErrorMessage("OK");
            }
            else
                setErrorMessage("Game not started");
        } else {
            setErrorMessage("Invalid command, try again");
        }
    }
}
/*
void flipTopCards(){
    LinkedList* slots = getBoard();
    for (int i = 0; i < 7; ++i) {
        LinkedList currentList = slots[i];
        Card* currentCard = getLastCard(&currentList);
        if (currentCard->faceUp == false){
            currentCard->faceUp = true;
        }
    }
}

void attemptCardMove(char* columnFrom, Card* card, char* columnDest){
    // Find card in from-column
    LinkedList fromList = getBoard()[getColumnIndex(columnFrom)];
    Card* fromCard = fromList.head;
    while (fromCard != NULL){
        if (card == fromCard){
            // The card does exists in column
            LinkedList toList = getBoard()[getColumnIndex(columnDest)];
            Card* toCard = toList.head;
            while (toCard != NULL){
                if (toCard->next == NULL){
                    if (cardCanBePlaced(toCard, card)){
                        moveCardToStack(card, toCard);
                    }
                    break;
                }
                toCard = toCard->next;
            }
            return;
        }
        // Next
        fromCard = fromCard->next;
    }
}

int getColumnIndex(char* columnStr){
    if (strcmp(columnStr, "C1") == 0) {return 0;}
    if (strcmp(columnStr, "C2") == 0) {return 1;}
    if (strcmp(columnStr, "C3") == 0) {return 2;}
    if (strcmp(columnStr, "C4") == 0) {return 3;}
    if (strcmp(columnStr, "C5") == 0) {return 4;}
    if (strcmp(columnStr, "C6") == 0) {return 5;}
    if (strcmp(columnStr, "C7") == 0) {return 6;}
    if (strcmp(columnStr, "F1") == 0) {return 7;}
    if (strcmp(columnStr, "F2") == 0) {return 8;}
    if (strcmp(columnStr, "F3") == 0) {return 9;}
    if (strcmp(columnStr, "F4") == 0) {return 10;}
}

bool cardCanBePlaced(Card* cardBehind, Card* cardOntop){
    // Suits
    if (getCardSuit(cardBehind) != getCardSuit(cardOntop)){
        if (getCardValue(cardBehind) == getCardValue(cardOntop) +1){
            return true;
        }
    }
    return false;
}
 */

int getCardValue(Card* card){
    switch (card->name[0]) {
        case 'A': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'T': return 10;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
    }
}

CARD_SUITS getCardSuit(Card* card){
    switch (card->name[1]) {
        case 'S': return S;
        case 'D': return D;
        case 'H': return H;
        case 'C': return C;

    }
}

void deAllocateMalloc(){
    Card* card;
    if(getGameStarted()){
        printf("need to be implemented");
    }else{
        card = getDeck()->head->next;
        while (true){
            free(card->prev);
            if(card->next == NULL){
                free(card);
                break;
            }
            card = card->next;
        }
    }
}
