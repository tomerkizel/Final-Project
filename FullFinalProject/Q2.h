//Roei Rabey 314983594
//Tomer Kizel 315765891
//Final Project

/*This program gets moves list, a 2D board and a start pos and prints the list's path according to the project definitions
,deletes the invalid moves in the list the returns the number of them*/

#ifndef Q2_H
#define Q2_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Q1.h"
#include "DefHeader.h"

typedef struct _moveCell
{
	Move move;
	struct _moveCell *next, *prev;
} moveCell;

typedef struct _movesList
{
	moveCell *head;
	moveCell *tail;
} movesList;



int display(movesList *moves_list, boardPos start, char **board);
/*This func gets moves list, a 2D board and a start pos and prints the list's path according to the project definitions
,deletes the invalid moves in the list the returns the number of them*/

void printBoard(char **board);///prints a 2D board

void removeCell(moveCell *toDelete);///remove a cell from moves list


#endif