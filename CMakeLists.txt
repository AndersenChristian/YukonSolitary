cmake_minimum_required(VERSION 3.21)
project(Yukon C)

set(CMAKE_C_STANDARD 99)

add_executable(Yukon main.c Data/Data.c Logic/ProgramController.c Interface/Display.c Logic/GameController_Header.h Interface/Reader.c Logic/ProgramController_Header.h Interface/Display_Header.h Data/Data_Header.h Interface/Reader_Header.h Logic/GameController.c Logic/PreGameOperation.c Logic/PreGameOperation_Header.h Logic/functionDrafts.c)
