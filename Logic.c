//
// Created by Christian Andersen on 01-04-2022.
//
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Header.h"

// TODO LIST
// - Test if move is valid when moving. It is causing errors.
// - Be sure to update tail pointer when adding cards to end of stack.

/**
 *
 */
extern void playGame() {
    updateDisplay();

    do {
        processPlayerInput(getPlayerInput());
        updateBoard(); // Nothing in function
        updateDisplay();

    }while(!isGameWon());
}

/**
 *
 * @return
 */
bool winCondition(){
    //todo test for win condition
}
void split(){
    LinkedList* deck = getDeck();
    LinkedList secondPile;
    LinkedList thirdPile;

    int cardsInList = 1;
    int count = atoi( &getLastCommand()[3]);
    int i = 0;

    int randomNumber = rand()%(cardsInList+1);
    Card* temp = deck->head;
    if (getLastCommand() > 0 && getLastCommand() < 52){
        secondPile.head = deck->head;
        do {
            temp = temp->next;
            i++;

        }while(i < count);
        secondPile.tail = temp;

        thirdPile.head = secondPile.tail->next;
        thirdPile.tail = deck->tail;

        secondPile.tail->next = NULL;
        thirdPile.head->prev = NULL;
    }
    else{
        secondPile.head = deck->head;
        do {
            temp = temp->next;
            i++;

        }while(i < randomNumber);
        secondPile.tail = temp;

        thirdPile.head = secondPile.tail->next;
        thirdPile.tail = deck->tail;

        secondPile.tail->next = NULL;
        thirdPile.head->prev = NULL;
    }
    deck->head = secondPile.head;
    deck->tail = secondPile.head;

    do{
        deck->tail->next = secondPile.head->next;
        deck->tail = secondPile.head->next;
        deck->tail->next = thirdPile.head->next;
        deck->tail = thirdPile.head->next;

    }while (secondPile.tail->next != NULL || thirdPile.tail->next != NULL);
}

/**
 * Author: Christian J. L. Andersen (S133288)
 *
 * Shuffle the cards.
 */

void shuffle() {
    LinkedList* deck = getDeck();       //gets a pointer to the current LinkedList
    Card* nextCard = deck->head->next;  //keeps a track of the remaining card we need to shuffle into the LinkedList
    int cardInList = 1;                 //keep a track of how many cards is currently in the new LinkedList

    //removes all the card except the first from the LinkedList, and ensure all pointers are correct.
    deck->tail = deck->head;
    deck->head->next = NULL;
    deck->head->prev = NULL;

    //Create a random generator to decide where to put the card
    srand(time(NULL));
    int randomNumber;
    Card* cardForNextItteration;

    do{
        randomNumber = rand()%(cardInList + 1); //generates a random number between 0 and the number of cards in list
        if(nextCard->next != NULL) {
            cardForNextItteration = nextCard->next; //pointer to the next card to ensure we don't lose it.
        }
        if (randomNumber == 0) {                //If the random number is 0, we have to set a new head of the LinkedList
            deck->head->prev = nextCard;
            nextCard->next = deck->head;
            nextCard->prev = NULL;
            deck->head = nextCard;
        } else{
            Card* tempCard = deck->head;
            while (randomNumber != 1){
                tempCard = tempCard ->next;         //Finds the card that should be after the one we are trying to place
                randomNumber--;
            }
            if(tempCard->next == NULL){         //If this is true, the new card must be the new tail of the LinkedList
                deck->tail = nextCard;
                nextCard->next = NULL;
                tempCard->next = nextCard;
                nextCard->prev = tempCard;
            }else{
                nextCard->next = tempCard->next;
                nextCard->next->prev = nextCard;
                tempCard->next = nextCard;
                nextCard->prev = tempCard;
            }
        }
        nextCard = cardForNextItteration; //Updates the card we are trying to place
        cardInList++;
    }while(cardInList != 52);      //ensures that we put all cards into the new LinkedList

}
/**
 * Author: Christian J. L. Andersen (S133288)
 */
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

/**
 * Author: Christian J. L. Andersen (S133288)
 *
 * Gets a String containing the name of the .txt file
 *
 * @param filename gets the name of the file, including the type. limited to only accept .txt files
 */
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

}
/**
 * Author: Frederik G. Petersen (S215834)
 * @param string
 */
 // TODO Make better initial comparision to check nothing follows the initals
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
        attemptCardMove(fromColumn, card, toColumn);



    } else if (string[2] == '-' && string[3] == '>'){ // From/To foundation
        char fromColumn[3];
        char toColumn[3];
        memcpy(fromColumn, string, 2);
        memcpy(toColumn, &string[4], 2);

        attemptFoundationMove(fromColumn, toColumn);

    } else {
        char initials[3];
        memcpy(initials, string, 2);
        initials[2] = '\0';

        // Things to process
        if (strcasecmp(initials, "LD") == 0){
            if (!isDeckLoaded())
                setupCards();
            else
                setErrorMessage("Deck already loaded");
        } else if (strcasecmp(initials, "SW") == 0){
            //All functionality of this one is programmed into the display.
            setErrorMessage("OK");
        } else if (strcasecmp(initials, "SI") == 0){
            split();
        } else if (strcasecmp(initials, "SR") == 0){
            if (isDeckLoaded()) {
                shuffle();
                setErrorMessage("OK");
            } else {
                setErrorMessage("You must load a deck before shuffeling");
            }

        } else if (strcasecmp(initials, "SD") == 0){
            if (isDeckLoaded()) {
                if(strlen(string) > 3) {
                    char *filename = &string[3];
                    saveGame(filename);
                } else
                    setErrorMessage("You must choose a file name");
            }else
                setErrorMessage("You must first load i file to save it");
        } else if (strcasecmp(initials, "QQ") == 0){
            remove("..\\CurrentSeed.txt");
            if(isDeckLoaded())
                deAllocateMalloc();
            printf("\n---Exiting Game---\n");
            exit(0);

        // if a deck is loaded and the game is not already in progress, this will build our 11 LinkedList
        // for the board, and update the game state.
        }else if (strcasecmp(initials, "P\n") == 0){
            if(hasGameStarted())
                setErrorMessage("Game already in progress");
            else if(isDeckLoaded()) {
                saveGame("CurrentSeed.txt"); //saves the current card setup.
                setupBoard();

                setGameStarted(true);
                setErrorMessage("OK");
            }else{
                setErrorMessage("Must load a deck, before you can start the game");
            }

        // If the game is running, this will reverse the gamestate, and load the card into a single LinkedList
        // with the same setup as before the game started.
        } else if (strcasecmp(initials, "Q\n") == 0){
            if (hasGameStarted()) {                                 //ensures that a game is in progress.
                setErrorMessage("OK");
                deAllocateMalloc();                                 //removes the current card, and free the memory.
                setLastCommand("LD ../CurrentSeed.txt");   //The last command is where the setupCards get the filePath.
                setupCards();                                       //Setup 1 LinkedList containing the cards from CurrentSeed.txt
                setLastCommand("Q\n");                     //reverse the LastCommand for proper showing
                setGameStarted(false);
            }
            else
                setErrorMessage("Game not started");

        //the default if everything else fails.
        } else {
            setErrorMessage("Invalid command, try again");
        }
    }
}

void flipTopCards(LinkedList* list){
    Card* currentCard = getLastCard(list);
    if (currentCard->faceUp == false){
        currentCard->faceUp = true;
    }

}
/**
 * Author: Frederik G. Petersen (S215834)
 * @param columnFrom
 * @param cardName
 * @param columnDest
 */
bool attemptCardMove(char* columnFrom, char* cardName, char* columnDest){
    // Find card in from-column
    LinkedList* fromList = &getBoard()[getColumnIndex(columnFrom)];
    LinkedList* toList = &getBoard()[getColumnIndex(columnDest)];
    Card* fromCard = getCardByName(fromList, cardName);
    Card* toCard = getLastCard(toList);

    // King to Empty Column
    if (toList->head == NULL){
        if (fromCard->name[0] == 'K'){
            moveCardToColumn(toList, fromCard);
        } else {
            setErrorMessage("Invalid move");
            return false;
        }
    }

    // Normal move
    else if (columnFrom[0] == 'C' && columnDest[0] == 'C'){
        if (fromCard == NULL || toCard == NULL){
            setErrorMessage("Move is Invalid!");
            return false;
        }
        if (cardCanBePlaced(toCard, fromCard)){
            moveCardToCard(fromCard, toCard);
            flipTopCards(fromList);
            setErrorMessage("Card Moved");
            return true;
        }
    }
}

void attemptFoundationMove(char* columnFrom, char* columnDest){
    LinkedList* fromList = &getBoard()[getColumnIndex(columnFrom)];
    LinkedList* toList = &getBoard()[getColumnIndex(columnDest)];

    if (columnFrom[0] == 'C' && columnDest[0] == 'F'){ // To Foundation

        Card* card = getLastCard(fromList);

        // Get correct Foundation.
        char suit = card->name[1];
        LinkedList* foundation = NULL;

        if (suit == 'C'){ foundation = &getBoard()[7]; }
        if (suit == 'S'){ foundation = &getBoard()[8]; }
        if (suit == 'D'){ foundation = &getBoard()[9]; }
        if (suit == 'H'){ foundation = &getBoard()[10]; }

        if (foundation == NULL){
            setErrorMessage("Move Is Invalid");
            return;
        }

        // See if it's a valid move
        if (getCardValue(foundation->tail)+1 == getCardValue(card)){
            // Disconnect Card
            if (card->prev == NULL){ // Last card in stack
                fromList->head = NULL;
                fromList->tail = NULL;

            } else { // not last
                fromList->tail = fromList->tail->prev;
                card->prev->next = NULL;
                card->prev = NULL;
            }

            moveCardToFoundation(foundation, card);
        } else {
            setErrorMessage("Move is Invalid");
        }
    }

    if (columnFrom[0] == 'F' && columnDest[0] == 'C') { // Back from foundation
        Card* foundationCard = getLastCard(fromList);
        Card* columnCard = getLastCard(toList);

        // Disconnect it from foundation
        if (foundationCard->prev == NULL){
            fromList->head = NULL;
            fromList->tail = NULL;
        } else {
            foundationCard->prev->next = NULL;
            foundationCard->prev = NULL;
        }

        //
        if (cardCanBePlaced(columnCard, foundationCard)){
            moveCardToCard(foundationCard, columnCard);
        }
    }
}

int getColumnIndex(char* columnStr){
    if (strcasecmp(columnStr, "C1") == 0) {return 0;}
    if (strcasecmp(columnStr, "C2") == 0) {return 1;}
    if (strcasecmp(columnStr, "C3") == 0) {return 2;}
    if (strcasecmp(columnStr, "C4") == 0) {return 3;}
    if (strcasecmp(columnStr, "C5") == 0) {return 4;}
    if (strcasecmp(columnStr, "C6") == 0) {return 5;}
    if (strcasecmp(columnStr, "C7") == 0) {return 6;}
    if (strcasecmp(columnStr, "F1") == 0) {return 7;}
    if (strcasecmp(columnStr, "F2") == 0) {return 8;}
    if (strcasecmp(columnStr, "F3") == 0) {return 9;}
    if (strcasecmp(columnStr, "F4") == 0) {return 10;}
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

/**
 * Author: Frederik G. Petersen (S215834)
 * @param card
 * @return
 */
int getCardValue(Card* card){
    if (card == NULL) return 0;
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

/**
 * Author: Frederik G. Petersen (S215834)
 * @param card
 * @return
 */
CARD_SUITS getCardSuit(Card* card){
    switch (card->name[1]) {
        case 'S': return S;
        case 'D': return D;
        case 'H': return H;
        case 'C': return C;
    }
}

LinkedList* getFoundation(Card* card){
    LinkedList* list = getBoard();
    if (card->name[1] == 'C') return &list[7];
    if (card->name[1] == 'S') return &list[8];
    if (card->name[1] == 'D') return &list[9];
    if (card->name[1] == 'H') return &list[10];
}

/**
 * Author: Christian J. L. Andersen (S133288)
 *
 * This method is used to free the memory used by malloc.
 * It's seperated into 2 section.
 *
 * First section is if the game has started. In that case, the references to the cards can be found in the
 * LinkedList array called boardSlots, and we will iterate through each of those list to free all Cards.
 *
 * Second is if cards have been loaded, but haven't been split into the smaller LinkedList.
 * In that case, all the references can be found in the LinkedList deck, and we iterate through that one, until all have been removed.
*/
void deAllocateMalloc(){
    Card* card;
    if(hasGameStarted()){                   //If the game has started the cards pointers are in the 11 LinkedList,
        for (int i = 0; i < 11; ++i) {
            if (getBoard()[i].head == NULL) //ensures that there are any cards in the LinkedList
                break;
            card = getBoard()[i].head;      //gets the first Card of the LinkedList
            do{
                if(card->next == NULL){
                    free(card);
                    break;
                }
                card = card->next;
                free(card->prev);
            }while(1);
        }
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
