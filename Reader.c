//
// Created by Rawfodog on 02-04-2022.
//
#include <stdio.h>
#include "Header.h"
#include <string.h>

char buffer[5];
FILE *cardFile;
char* token; //token is used to do some string manipulation, and remove unwanted chars in the beginning.

/**
 * Author: Christian J. L. Andersen (S133288)
 *
 * This method loads in a deck of playing cards from a file.
 *
 * If the player doesn't give a filename, the default file Cards.txt will be used.
 *
 * else, it will try and read the file with the name and path given.
 *
 * This method will fail if only a name is given. If the file is saved within the root
 * of this program, the format must be ../<filename>
 * If in doubt use absolute path
 *
 * (note) some OS accept '\\' but this can cause issues.
 */
void setupCards(char* command){
    if (command[2] != 32) //checks if the 3 char in the string is an empty space.
        cardFile = fopen("..\\Cards.txt","r");
    else {
        token = command + 3; //gets the string that start after the empty space.
        if(!(strcspn(token,"\n") == strlen(token))) //checks if there is a /n in the end of the string and removes it.
            token[strcspn(token, "\n")] = 0;
        cardFile = fopen((token), "r");
    }
    if (cardFile == NULL) { //If the file we are trying to read doesn't exist, fopen will return NULL
        setErrorMessage("the file does not exist");
        return;
    }
    for (int i = 0; i < DECK_SIZE; ++i) {
        if (fgets(buffer, 10, cardFile)){
            pushCardToDeck((char *) buffer); //setup the card one by one.
        }
    }
    fclose(cardFile);

    if (validateDeck()) { //check if the deck has all the cards necessary.
        *dataPTR_DeckLoaded() = true;
        setErrorMessage("Deck loaded correct");
    } else {
        deAllocateMalloc(); //if the validation fails, we remove our mem allocation.
    }
}

/**
 * Author: Christian J. L. Andersen (S133288)
 *
 * We goes through each suit, and in each suit we iterate through each cardValue from ace to king.
 * If it doesn't find the card, or finds the cards twice, it will stop and return an error code.
 *
 * @return whether or not the file contains exactly 1 of each playing card.
 */
bool validateDeck() {
    Card *nextCard;
    bool flag = true;
    int cardsChecked;

    for (int i = 0; i < 4; ++i) {       //goes through all suits
        for (int j = 0; j < 13; ++j) {  //goes through all card values
            if (!flag) { //If we get here and flag is false, we have iterated through all cards without finding the one we are looking for.
                setErrorMessage("Card is missing");
                return false;
            }
            cardsChecked = 0;
            nextCard = dataPTR_ToDeck()->head; //gets the first card in the deck.
            flag = false;
            do {
                if (getCardSuit(nextCard) == i && getCardValue(nextCard) == j+1) { //check if the suit and value equils the card we are looking for.
                    if (flag) { //if we have a match, and flag is already true, we have found the same card twice.
                        setErrorMessage("Same card exist twice");
                        return false; //break the code
                    }
                    flag = true;
                    }
                cardsChecked++;
                if(nextCard->next == NULL){ //this goes through when we have iterated through all the cards in the list.
                    if(cardsChecked != 52) { //if the amount of cards found at this point is not 52 exactly, we either have to many or to few cards in the deck.
                        setErrorMessage("Wrong amount of cards in deck");
                        return false;
                    }
                    break;
                }
                nextCard = nextCard->next; //gets the next card in the series ready for next loop
            }while (1); //don't need a condition, since we build in break methods to reduce runtime.
        }
    }
    return true; //if we gets here, we have found exactly 1 of each playing card, and therefor it must be a valid deck.
}