//Roei Rabey 314983594
//Tomer Kizel 315765891
//Final Project Q6

/*This program reads bordpositions from a binary file, and then it checks if the path of them is valid,
if it is the program prints the path according to the project definitions, and also return a different int value for:
if the file exists, if the path is valid, if the path covers the whole board and if it is not*/

#ifndef Q6_H
#define Q6_H


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "DefHeader.h"
#include "Q5.h"
#include "Q2.h"
#include "Q1.h"



int checkAndDisplayPathFromFile(char *file_name, movesArray **moves, char **board);
/*This func reads bordpositions from a binary file, and then it checks if the path of them is valid,
if it is the program prints the path according to the project definitions, and also return a different int value for:
if the file exists, if the path is valid, if the path covers the whole board and if it is not*/

int binaryToDecimal(int *arr);///converts a binary num to a decimal

int * createBitsArr(BYTE *arr, unsigned int arrSize);///creates a bits array

BYTE * readFromFile(char*fname, unsigned short int *short1, unsigned int *bytesArrSize);///reads bytes array from binary file

boardPosArray createPosArr(int *bitsArr, unsigned int bitsArrSize, unsigned int posSize);///creates array of positions

bool isExists(char *file_name);///checks if the file exists

bool validation(boardPosArray pos_arr, movesArray **moves, char **board);///checks the validation of the path

bool inValidRows2(int num);///checks if the move in row level is valid or not

bool inValidCols2(int num);///checks if the move in col level is valid or not

#endif