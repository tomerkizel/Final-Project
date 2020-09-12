
/*This program gets an array of boardpos and saves them in a binary file according to the project definitions
as bits including an unsigned short int which represents the size of the array*/

#ifndef Q5_H
#define Q5_H


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "DefHeader.h"
#include "Q1.h"


typedef unsigned char BYTE;

void saveListToBinFile(char *file_name, boardPosArray *pos_arr);
/*This func gets an array of boardpos and saves them in a binary file according to the project definitions
as bits including an unsigned short int which represents the size of the array*/

void saveInFile(BYTE * bitsArr, char*fname, unsigned int arrSize, unsigned short int short1);///saves bytes array in a binary file

BYTE * createBytesArray(int *arr, int size, int * bitsSize);///creates an array of bytes

BYTE setBit(BYTE ch, int i);///sets a bit in the i location

int *createBitsArray(boardPos *positions, int size, int *bitsSize);///creates an array of bits

int *bitsPos(int *arr, int bitsSize, int *size2);///creates an array of bits locations

int *decimalToBinary(int num);///converts number from decimal to binary

int maxValue(int *arr, int size);///finds the max value


#endif
