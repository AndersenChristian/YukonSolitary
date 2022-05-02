cmake_minimum_required(VERSION 3.21)
project(Yukon C)

set(CMAKE_C_STANDARD 99)

add_executable(Yukon main.c Data/Data.c Logic/Logic.c Interface/Display.c Logic/Header.h Interface/Reader.c Logic/linkedListFunctionality.c Logic/Logic_Header.h Interface/Display_Header.h Data/Data_Header.h Interface/Reader_Header.h Logic/PlayGame.c Logic/PlayGame_Header.h)
