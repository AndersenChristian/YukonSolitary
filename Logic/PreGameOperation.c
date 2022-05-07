//Libaries
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

//Headers
#include "../Data/Data_Header.h"

/**
 * Author: Christian J. L. Andersen (S133288)
 * TODO write docs
 */
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
 * todo write docs
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
    
    //reset the deck head and tail for safety
    dataPTR_ToDeck()->head = NULL;
    dataPTR_ToDeck()->tail = NULL;
    
    //reset the head and tail of all ingame linkedList
    for (int i = 0; i < 11; ++i) {
        dataPTR_ToBoard()[i].head = NULL;
        dataPTR_ToBoard()[i].tail = NULL;
    }
}

/**
 * Author: Emil Falck Hansen (S215823)
 *
 * This method is used to split the deck of cards into two piles. With a split parameter, you can define the size of
 * pile one. After this it merges the two piles into a third pile. The third pile becomes the deck of the game.
 */
void SI(){
    LinkedList* deck = dataPTR_ToDeck(); //Getting the deck as a linked List pointer.
    LinkedList firstPile;
    LinkedList secondPile;
    LinkedList thirdPile;

    int splitNumber;
    int i = 0;
    bool calculateNewSplit = false;
    int lengthOfNumber = strlen(dataPTR_lastCommand());

    //Taking split input
    if (lengthOfNumber == 5) {
        splitNumber = atoi(&dataPTR_lastCommand()[3]);
    }
    else if (lengthOfNumber == 6) {
        splitNumber = atoi(&dataPTR_lastCommand()[3]);
    }
    else {
        for (int j = 0; j < 500; j++) {
            splitNumber = rand() % 52;
        }
    }

    Card* temp = deck->head;
    //Finding where the first piles tail should be.
    for (int j = 0; j < splitNumber-1; j++) {
        temp = temp->next;
    }

    //If splitNumber is bigger than 26, a new split number needs to be calculated.
    if (splitNumber > 26){
        splitNumber = 52 - splitNumber;
        calculateNewSplit = true;
    }

    //Defining the first pile.
    firstPile.head = deck->head;
    firstPile.tail = temp;

    //Defining the second pile.
    secondPile.head = temp->next;
    secondPile.tail = deck->tail;

    //Card pointers to merge first pile and second pile.
    Card* currentFirst = firstPile.head;
    Card* currentSecond = secondPile.head;
    Card* currentThird = NULL;

    //Logic to merge first pile and second pile.
    for (int j = 0; j < splitNumber; j++) {
        Card* firstNextCard = currentFirst->next;
        Card* secondNextCard = currentSecond->next;

        //Putting the first cards from each pile.
        if (j == 0){
            thirdPile.head = currentFirst;
            currentFirst->prev = NULL;

            currentFirst->next = currentSecond;
            currentSecond->prev = currentFirst;

            currentThird = currentSecond;
         //Adding the rest of the cards in each pile, until split number is reached.
        }else{
            currentThird->next = currentFirst;
            currentFirst->prev = currentThird;
            currentThird = currentFirst;

            currentThird->next = currentSecond;
            currentSecond->prev = currentThird;
            currentThird = currentSecond;
        }
        //Updating the next card in the linked list for each interation.
        currentFirst = firstNextCard;
        currentSecond = secondNextCard;
    }
    // If the splitNumber was bigger than 26.
    if (calculateNewSplit == true) {
        currentThird->next = currentFirst;
        currentFirst->prev = currentThird;

        thirdPile.tail = firstPile.tail;
    }
    else{
        currentThird->next = currentSecond;
        currentSecond->prev = currentThird;

        thirdPile.tail = secondPile.tail;
    }
    //Defining the deck in the game based on the shuffled pile.
    deck->head = thirdPile.head;
    deck->tail = thirdPile.tail;
}