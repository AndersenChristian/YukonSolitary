//Libaries
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

//Headers
#include "../Data/Data_Header.h"

//own methods declaration


void SR() {
    LinkedList* deck = dataPTR_ToDeck();    //gets a pointer to the current LinkedList
    Card* nextCard = deck->head->next;      //keeps a track of the remaining card we need to SR into the LinkedList
    int cardInList = 1;                     //keep a track of how many cards is currently in the new LinkedList

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
void P(){
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
    *dataPTR_GameStarted() = true;
}

/**
 * Author: Christian J. L. Andersen (S133288)
 *
 * Gets a String containing the name of the .txt file
 *
 * @param filename gets the name of the file, including the type. limited to only accept .txt files
 */
void SD(char* filename){
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
 * Author: Christian J. L. Andersen (S133288)
 *
 * This method is used to free the memory used by malloc.
 * It's seperated into 2 section.
 *
 * First section is if the game has started. In that case, the references to the cards can be found in the
 * LinkedList array called boardSlots, and we will iterate through each of those list to free all Cards.
 *
 * Second is if cards have been loaded, but haven't been SI into the smaller LinkedList.
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
    dataPTR_ToDeck()->head = NULL;
    dataPTR_ToDeck()->tail = NULL;
}

void SI(){
    LinkedList* deck = dataPTR_ToDeck();
    LinkedList secondPile;
    LinkedList thirdPile;

    int splitNumber;
    int cardsInList = 1;
    //int getLastCommandNum = dataPTR_lastCommand()[3] - 0;
    int i = 0;

    int lengthOfNumber = strlen(dataPTR_lastCommand());

    if (lengthOfNumber == 1)
        splitNumber = dataPTR_lastCommand()[3] - 0;
    else if (lengthOfNumber == 2)
        splitNumber = (dataPTR_lastCommand()[3] - 0) * 10 + (dataPTR_lastCommand()[4] - 0);
    else
        splitNumber = rand()%52;

    Card* temp = deck->head;
    if (splitNumber > 0 && splitNumber < 52){
        secondPile.head = deck->head;
        do {
            temp = temp->next;
            i++;
        }while(i < splitNumber);

        secondPile.tail = temp;

        thirdPile.head = secondPile.tail->next;
        thirdPile.tail = deck->tail;

        secondPile.tail->next = NULL;
        thirdPile.head->prev = NULL;
    }
    deck->head = secondPile.head;
    deck->tail = secondPile.head;
    if(secondPile.head->next != NULL){
        secondPile.head = secondPile.head->next;
        secondPile.head->prev = NULL;
    }else{
        secondPile.head = NULL;
    }
    deck->head->next = NULL;

    do{
        if(thirdPile.head != NULL) {
            thirdPile.head->prev = deck->tail;
            deck->tail = thirdPile.head;
            thirdPile.head = thirdPile.head->next;
            thirdPile.head->next = NULL;
            deck->tail->prev->next = deck->tail;
            thirdPile.head->prev = NULL;
        }
        if(secondPile.head != NULL) {
            secondPile.head->prev = deck->tail;
            deck->tail = secondPile.head;
            secondPile.head = secondPile.head->next;
            secondPile.head->next = NULL;
            deck->tail->prev->next = deck->tail;
            secondPile.head->prev = NULL;
        }
    }while (secondPile.tail->next != NULL || thirdPile.tail->next != NULL);
}