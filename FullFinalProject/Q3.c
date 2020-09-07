/*
	Tomer Kizel 315765891
	Roei Rabey 314983594
*/
/*
	This Programm creates a tree with pathTree as a struct.
	The tree root is a given start point in the board and the
	rest of the tree is cohirent to the values of a given movesArray
	(the tree does not include loops)
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Q3.h"

pathTree findAllPossiblePaths(boardPos start, movesArray **moves, char **board) {
	fixMovesArray(moves, board); //remove all incorrect moves
	pathTree tree;
	treeNode *node = (treeNode*)malloc(sizeof(treeNode));
	checkMemoryAllocation(node);
	//create a board copy:
	char** newBoard;
	newBoard = (char*)malloc(N * sizeof *newBoard);
	for (int i = 0; i < N; i++) {
		newBoard[i] = (char*)malloc(M * sizeof *newBoard[i]);
	}
	for (int j = 0; j < N; j++) { //sets values to the board's cells
		for (int i = 0; i < M; i++)
		{
			newBoard[j][i] = board[j][i];
		}
	}
	//sets the root of the tree:
	node->position[0] = start[0];
	node->position[1] = start[1];
	if (moves[start[0] - 'A'][start[1] - '1'].size == 0) { //if there is no vlues to create the tree from
		node->next_possible_positions = NULL;
		tree.head = node;
		return tree;
	}
	node->next_possible_positions = createListCell(node, moves[start[0] - 'A'][start[1] - '1'].moves, 0, moves, newBoard);
	tree.head = node;
	return tree;
}

treeNodeListCell *createListCell(treeNode *parent, Move *possibleMoves, int i, movesArray **moves, char **board) {
	int x, y, orgX, orgY;
	orgX = parent->position[0] - 'A'; //parent x position
	orgY = parent->position[1] - '1'; //parent y position
	treeNode *newNode = (treeNode*)malloc(sizeof(treeNode));
	checkMemoryAllocation(newNode);
	treeNodeListCell *cell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	checkMemoryAllocation(cell);
	x = orgX + (int)(possibleMoves[i].rows); //child x position
	y = orgY + (int)(possibleMoves[i].cols); //child y position
	if (board[x][y] == '*') { //if the child position in unavailable
		i++;
		return createListCell(parent, possibleMoves, i, moves, board); //continue to the next value
	}
	else {
		//create the child node:
		newNode->position[0] = (char)(x + 'A');
		newNode->position[1] = (char)(y + '1');
		if (moves[x][y].moves == NULL || moves[x][y].size == 0) { //if there are not further advancments in the child level
			newNode->next_possible_positions = NULL;
			cell->node = newNode;
			board[x][y] = '*'; // to prevent loops
			i++;
			if (i == moves[orgX][orgY].size) { //if the recurstion is done with the child's level
				cell->next = NULL;
			}
			else { //there is further information in the parent child level
				cell->next = createListCell(parent, possibleMoves, i, moves, board); //continue the level
			}
		}
		else {
			newNode->next_possible_positions = createListCell(newNode, moves[x][y].moves, 0, moves, board); //create the next level with the newNode as the parent
			board[x][y] = '*'; //to prevent loops
			cell->node = newNode;
			i++;
			if (i == moves[orgX][orgY].size) { //if the recurstion is done with the child's level
				cell->next = NULL;
			}
			else {
				cell->next = createListCell(parent, possibleMoves, i, moves, board);
			}
		}
	}
	return cell;
}

void fixMovesArray(movesArray** moves, char **board) {
	int i, j, k, cnt = 0;
	// triple loops to run on the movesArray:
	for (j = 0; j < N; j++)
	{
		for (i = 0; i < M; i++)
		{
			for (k = 0; k < moves[j][i].size; k++)
			{
				if (checkRows(moves[j][i].moves[k], j) || checkCols(moves[j][i].moves[k], i))// if the value of the move in the k-th position is illigal

				{
					moves[j][i].moves[k].rows = FLAG; //setting value to an illigal char FLAG (200)
				}
				else if (board[j + moves[j][i].moves[k].rows][i + moves[j][i].moves[k].cols] == '*') //if the board has '*' in the position
				{
					moves[j][i].moves[k].rows = FLAG; //setting value to an illigal char FLAG (200)
				}
				else {
					cnt++;
				}
			}
			moves[j][i].moves = deleteMoves(moves[j][i].moves, cnt, moves[j][i].size); //remove any move with FLAG
			moves[j][i].size = cnt; //set new size
			cnt = 0;
		}
	}
}


bool checkRows(Move move, int num) {
	return((num + move.rows < 0) || (num + move.rows >= N));
}

bool checkCols(Move move, int num) {
	return((num + move.cols < 0) || (num + move.rows >= M));
}

void checkMemoryAllocation(void *ptr) {
	if (ptr == NULL)
	{
		printf("Malloc failed\n");
		exit(0);
	}
}