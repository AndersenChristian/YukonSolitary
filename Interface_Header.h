//
// Created by Christian Andersen on 29-04-2022.
//
#include "Header.h"

#ifndef YUKON_INTERFACE_HEADER_H
#define YUKON_INTERFACE_HEADER_H
//Interface
void updateDisplay();
void gameDisplay();
void displayEmpty();
void defaultDisplay();
void displayInfolines();

//Reader
void setupCards(char*);

//PlayerInput
void getPlayerInput();
#endif //YUKON_INTERFACE_HEADER_H
