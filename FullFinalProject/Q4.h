/*
	Tomer Kizel 315765891
	Roei Rabey 314983594
*/
/*
	This Programm returns a movesList that covers the entier board or NULL if there
	is none like that.
*/

#ifndef Q4_H
#define Q4_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "DefHeader.h"
#include "Q3.h"
#include "Q1.h"
#include "Q2.h"
//Functions :

/*
	This function gets a starting point, movesArray and a board as parameters.
	This function checks if there is a path from 'start' that covers the
	whole board, if so, it returns it as a list, if there is no path it returns
	NULL.
*/
movesList* findPathCoveringAllBoard(boardPos start, movesArray **moves, char **board);

/*
	This function gets a treeNodeListCell , desiredNum, posArray, count and flag as parameters.
	This function find a path from cell that is desiredNum long and change flag to true if it finds it.
	Otherwise it change flag to flase.
*/
void findListToAGivenLevel(treeNodeListCell*  cell, int desiredNum, boardPos* posArray, int* count, bool* flag);

/*
	This function gets boardPos, desiredNum, movesList and boardPosArray as parameters.
	This function creates and put in the movesList a movesList according to the value on posArray
	in start point.
	This function frees all the allocated memory that posArray takes.
*/
void convPosArrayToList(boardPos start, int desiredNum, movesList* list, boardPosArray posArray);

/*
	This function gets 2 boardPos's as parameters.
	This function creates adn returns a moveCell with the move between
	the 2 boardPos's as data.
*/
moveCell* creatListCellFromPos(boardPos prev, boardPos dest);

/*
	This function gets 2 boardPos's as parameters.
	This functiion calculate and returns the move that links
	between the 2 boardPos's.
*/
Move createMove(boardPos start, boardPos dest);

/*
	This function gets a board as parameter.
	This function returns the amount of '*' chars in board.
	*/
int findAllStars(char** board);

/*
	This function gets no parameters.
	This function returns a movesList with allocated memory and NULL tail & head.
*/
movesList *createNewList();



#endif