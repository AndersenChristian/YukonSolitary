//
// Created by Rawfodog on 02-04-2022.
//
#include <stdio.h>
#include "Header.h"
#include <string.h>

char buffer[5];
FILE *cardFile;
char* token;

void setupCards(){
    if (getLastCommand()[2] != 32)
        cardFile = fopen("..\\Cards.txt","r");
    else
        cardFile = fopen((getLastCommand()+3),"r");
    if (cardFile == NULL) {
        setErrorMessage("the file does not exist");
        return;
    }
    initDeck();
    for (int i = 0; i < 52; ++i) {
        if (fgets(buffer, 10, cardFile)){
            pushCardToDeck((char *) buffer);
        }
    }
    fclose(cardFile);

    if (validateDeck()) { //check if the deck has all the cards necessary.
        setIsDeckLoaded(true);
        setErrorMessage("Deck loaded correct");
    }
}

bool validateDeck() {
    Card *nextCard;
    bool flag = true;

    for (int i = 0; i < 4; ++i) { //goes through all suits
        for (int j = 0; j < 13; ++j) { //goes through all card values
            if (!flag) {
                setErrorMessage("Card is missing");
                return false;
            }
            nextCard = getDeck()->head;
            flag = false;
            do {
                if (getCardSuit(nextCard) == i && getCardValue(nextCard) == j+1) {
                    if (flag) {
                        setErrorMessage("Same card exist twice");
                        return false; //break the code
                    }
                    flag = true;
                    }
                if(nextCard->next == NULL)
                    break;
                nextCard = nextCard->next;
            }while (1);
        }
    }
    return true;
}