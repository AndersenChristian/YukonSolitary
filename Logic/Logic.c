//Libaries
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

//Headers
#include "../Data/Data_Header.h"
#include "../Interface/Display_Header.h"
#include "../Interface/Reader_Header.h"
#include "Header.h"

//own methods declaration
void deAllocateMalloc();
void processPlayerInput(char*);

/**
 *
 */
extern void playGame() {
    updateDisplay();

    do {
        processPlayerInput(dataPTR_lastCommand());
        updateDisplay();

    }while(!(*dataPTR_IsGameDone()));
}

/**
 *
 * @return
 */
bool winCondition(){
    //todo test for win condition
}

/**
 * Author: Christian J. L. Andersen (S133288)
 *
 * Shuffle the deck
 */
void shuffle() {
    LinkedList* deck = dataPTR_ToDeck();       //gets a pointer to the current LinkedList
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
    Card * ptrToCard = dataPTR_ToDeck()->head;
    LinkedList* boardSlots = dataPTR_ToBoard();

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
    if (dataPTR_ToDeck()->head != NULL){
        Card* card = dataPTR_ToDeck()->head;
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

/**
 * Author: Frederik G. Petersen (S215834)
 * @param string
 */
 // TODO Make better initial comparison to check nothing follows the initials
void processPlayerInput(char* string){

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
        //bool moveMade = attemptCardMove(fromColumn, card, toColumn);
        //TODO make PlayGame handle error messages

    } else {
        char initials[3];
        memcpy(initials, string, 2);

        // Things to process
        if (strcasecmp(initials, "LD") == 0){
            if (!(*dataPTR_DeckLoaded()))
                setupCards(dataPTR_lastCommand());
            else
                setErrorMessage("Deck already loaded");
        } else if (strcasecmp(initials, "SW") == 0){
            //All functionality of this one is programmed into the display.
            setErrorMessage("OK");
        } else if (strcasecmp(initials, "SI") == 0){

        } else if (strcasecmp(initials, "SR") == 0){
            if (dataPTR_DeckLoaded()) {
                shuffle();
                setErrorMessage("OK");
            } else {
                setErrorMessage("You must load a deck before shuffeling");
            }

        } else if (strcasecmp(initials, "SD") == 0){
            if (dataPTR_DeckLoaded()) {
                if(strlen(string) > 3) {
                    char *filename = &string[3];
                    saveGame(filename);
                } else
                    setErrorMessage("You must choose a file name");
            }else
                setErrorMessage("You must first load i file to save it");
        } else if (strcasecmp(initials, "QQ") == 0){
            remove("..\\CurrentSeed.txt");
            if(dataPTR_DeckLoaded())
                deAllocateMalloc();
            printf("\n---Exiting Game---\n");
            exit(0);

        // if a deck is loaded and the game is not already in progress, this will build our 11 LinkedList
        // for the board, and update the game state.
        }else if (strcasecmp(initials, "P\n") == 0){
            if(*dataPTR_GameStarted())
                setErrorMessage("Game already in progress");
            else if(dataPTR_DeckLoaded()) {
                saveGame("CurrentSeed.txt"); //saves the current card setup.
                setupBoard();

                /*
                // TODO !!!!!!!!!!!!!!!!!!!!!!!!!!!!1
                // Find better place for this:
                attemptMovingCardsToFoundation(&dataPTR_ToBoard()[0]);
                attemptMovingCardsToFoundation(&dataPTR_ToBoard()[1]);
                attemptMovingCardsToFoundation(&dataPTR_ToBoard()[2]);
                attemptMovingCardsToFoundation(&dataPTR_ToBoard()[3]);
                attemptMovingCardsToFoundation(&dataPTR_ToBoard()[4]);
                attemptMovingCardsToFoundation(&dataPTR_ToBoard()[5]);
                attemptMovingCardsToFoundation(&dataPTR_ToBoard()[6]);
                 */

                *dataPTR_GameStarted() = true;
                setErrorMessage("OK");
            }else{
                setErrorMessage("Must load a deck, before you can start the game");
            }

        // If the game is running, this will reverse the gamestate, and load the card into a single LinkedList
        // with the same setup as before the game started.
        } else if (strcasecmp(initials, "Q\n") == 0){
            if (*dataPTR_GameStarted()) {                                 //ensures that a game is in progress.
                setErrorMessage("OK");
                deAllocateMalloc();                                 //removes the current card, and free the memory.
                setupCards("LD ../currentSeed.txt");                                       //Setup 1 LinkedList containing the cards from CurrentSeed.txt
                *dataPTR_GameStarted() = false;
            }
            else
                setErrorMessage("Game not started");

        //the default if everything else fails.
        } else {
            setErrorMessage("Invalid command, try again");
        }
    }
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
    if(*dataPTR_GameStarted()){                   //If the game has started the cards pointers are in the 11 LinkedList,
        for (int i = 0; i < 11; ++i) {
            if (dataPTR_ToBoard()[i].head == NULL) //ensures that there are any cards in the LinkedList
                break;
            card = dataPTR_ToBoard()[i].head;      //gets the first Card of the LinkedList
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
        card = dataPTR_ToDeck()->head->next;
        while (true){
            free(card->prev);
            if(card->next == NULL){
                free(card);
                break;
            }
            card = card->next;
        }
    }
    dataPTR_ToDeck()->length = 0;
    dataPTR_ToDeck()->head = NULL;
    dataPTR_ToDeck()->tail = NULL;
}
