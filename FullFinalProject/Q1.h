//Roei Rabey 314983594
//Tomer Kizel 315765891
//Final Project

/*This program gets a 2D array of moves and a 2D board. Then it checks all the moves in each cell to see if they are
valid or not according to the project definitions. This program returns a 2D array of valid boardPositions you can
reach to from each cell, and deletes the invalid moves from the 2D array of moves*/

#ifndef Q1_H
#define Q1_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "DefHeader.h"


typedef char boardPos[2];///represents a position

typedef struct _move
{
	char rows, cols;
} Move;///represents a move

typedef struct _boardPosArray
{
	unsigned int size;
	boardPos *positions;
} boardPosArray;///represents an array of positions

typedef struct _movesArray
{
	unsigned int size;
	Move *moves;
} movesArray;///represents an array of moves



boardPosArray ** validMoves(movesArray **moves, char **board);
/*This func gets a 2D array of moves and a 2D board. Then it checks all the moves in each cell to see if they are
valid or not according to the project definitions. This program returns a 2D array of valid boardPositions you can
reach to from each cell, and deletes the invalid moves from the 2D array of moves*/

Move *deleteMoves(Move *moves, int num, int size);///deletes all the invalid moves

bool inValidRows(Move move, int num);///checks if the move in row level is valid or not

bool inValidCols(Move move, int num);///checks if the move in col level is valid or not

void checkAlloc(void *memp);///check if the memory allocation succeed

#endif