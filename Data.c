//
// Created by Rawfodog on 01-04-2022.
//
#include "Header.h"

#include <stdio.h>

LinkedList deck;
struct Card* boardSlots[11];

Card * getCard(int position){

}

void pushCardToDeck(char name[3]){
    addCard(&deck, name);
}

Card * getDeck (){
    return (Card *) &deck;
}

Card ** getBoard(){
    return (Card**) &boardSlots;
}
