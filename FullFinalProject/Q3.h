
/*
	This Programm creates a tree with pathTree as a struct.
	The tree root is a given start point in the board and the
	rest of the tree is cohirent to the values of a given movesArray
	(the tree does not include loops)
*/

#ifndef Q3_H
#define Q3_H

#define N 4 ///Rows A B C D...

#define M 5 ///Columns 1 2 3 4...

#define FLAG 200

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "DefHeader.h"
#include "Q1.h"
//Structs :

typedef struct _treeNode treeNode;
typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode {
	boardPos position;
	treeNodeListCell *next_possible_positions;
}treeNode;

typedef struct _treeNodeListCell {
	treeNode *node;
	struct _treeNodeListCell *next;
}treeNodeListCell;

typedef struct _pathTree {
	treeNode *head;
}pathTree;

//Functions :

/*
	This function gets a starting point, movesArray and board as parameters.
	This function remove any illigal moves from movesArray with board as a
	guideline.
	This function create a tree with the starting point as its root and
	all the possible paths from the root, without any loops and according to the
	movesArray and board as guidelines.
*/
pathTree findAllPossiblePaths(boardPos start, movesArray** moves, char** board);

/*
	This function gets movesArray and board as parameters.
	This function remove any illigal moves from movesArray with
	board as a guildeline.
*/
void fixMovesArray(movesArray** moves, char** board);

/*
	This function gets a parent, Move array, integet, movesArray and a board as parameters.
	This function create the pathTree from "findAllPossiblePaths" recursively.
	-parent: is the parent of the level this function creates
	-possibleMoves: is the possible moves from the parent according to movesArray
	-i : is the integer to check for the finish condition
	-moves: is the matrix contains all the moves needed to create possibleMoves
	- board: is the game board
*/
treeNodeListCell *createListCell(treeNode *parent, Move *possibleMoves, int i, movesArray **moves, char **board);

/*
	This function gets a Move and integet as a parameter.
	This function returns true if the move rows are lligal and false otherwise
*/
bool checkRows(Move move, int num);

/*
	This function gets a Move and integet as a parameter.
	This function returns true if the move collumns are lligal and false otherwise
*/
bool checkCols(Move move, int num);

/*
	This function checks memory allocation after
	dinamicly allocating memory
*/
void checkMemoryAllocation(void *ptr);

#endif
