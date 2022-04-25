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

    if (validateDeck()) //check if the deck has all the cards necessary.
        setIsDeckLoaded(true);
}

bool validateDeck(){
    CARD_SUITS suit;
    CARD_VALUES cardValue;
    printf("%d",cardValue);
    Card* nextCard = getDeck()->head;
    bool flag;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 13; ++j) {
            flag = false;
            do {
                cardValue = A;
                cardValue = (int) 'A';
                char c = (char) 'A';
                cardValue = (int) nextCard->name[0];
                suit = nextCard->name[1];
                printf("%d%d", cardValue, suit);
                //if ((enum CARD_VALUES) nextCard->name[0] == j && (enum CARD_SUITS) nextCard->name[1] == i) {
                    if (flag) {
                        //set error message
                        return false; //break the code
                    }
                    flag = true;
                //}
                nextCard = nextCard->next;
            } while (nextCard->next != NULL);
        }
    }
}