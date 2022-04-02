//
// Created by Rawfodog on 02-04-2022.
//

#ifndef YUKON_HEADER_H
#define YUKON_HEADER_H

 struct Card{
    char name[2];
    unsigned int faceUp;
};

//global variables
#define DECK_SIZE 52


//Methods
//Data
void createDeck();
struct Card getCard(int position);

//Logic
void setupGame();
void playGame();

//Interface
void updateDisplay();

#endif //YUKON_HEADER_H
