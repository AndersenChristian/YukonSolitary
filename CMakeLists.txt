cmake_minimum_required(VERSION 3.21)
project(Yukon C)

set(CMAKE_C_STANDARD 99)

add_executable(Yukon main.c Data.c Logic.c Interface/Display.c Header.h Interface/Reader.c structs.c Logic_Header.h Interface/Interface_Header.h)
