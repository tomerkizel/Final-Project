
/*
	This Programm returns a movesList that covers the entier board or NULL if there
	is none like that.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Q4.h"

movesList* findPathCoveringAllBoard(boardPos start, movesArray **moves, char **board) {
	pathTree tree = findAllPossiblePaths(start, moves, board);
	int count = 0, desiredNumber;
	boardPosArray posArray;
	bool flag = false;
	movesList*  list = createNewList();

	desiredNumber = M * N - findAllStars(board) - 1;
	posArray.size = desiredNumber;
	posArray.positions = (boardPos*)malloc(sizeof(boardPos)*desiredNumber);

	findListToAGivenLevel(tree.head->next_possible_positions, desiredNumber, posArray.positions, &count, &flag);

	if (flag) {
		convPosArrayToList(start, desiredNumber, list, posArray);
		return list;
	}
	else {
		return NULL;
	}
}

void findListToAGivenLevel(treeNodeListCell*  cell, int desiredNum, boardPos* posArray, int* count, bool* flag) {
	if (*count == desiredNum) {
		*flag = true;
	}

	posArray[*count][0] = cell->node->position[0];
	posArray[*count][1] = cell->node->position[1];
	*count = *count + 1;

	if (*count == desiredNum) {
		*flag = true;
	}

	treeNodeListCell* node = cell->node->next_possible_positions;

	while (!*flag && node != NULL) {
		findListToAGivenLevel(node, desiredNum, posArray, count, flag);
		node = cell->next;
	}

	if (!*flag && *count != desiredNum) {
		*count = *count - 1;
	}

}

void convPosArrayToList(boardPos start, int desiredNum, movesList* list, boardPosArray posArray) {

	moveCell* node;
	moveCell* prev;
	int i = 0;
	node = creatListCellFromPos(start, posArray.positions[i]);
	list->head = node;
	prev = node;
	for (i = 1; i <= desiredNum; i++) {
		node = creatListCellFromPos(posArray.positions[i - 1], posArray.positions[i]);
		prev->next = node;
		list->tail = node;
		node->prev = prev;
		prev = node;
	}
	free(posArray.positions);
}

moveCell* creatListCellFromPos(boardPos prev, boardPos dest) {
	moveCell* cell;

	cell = (moveCell*)malloc(sizeof(moveCell));

	cell->move = createMove(prev, dest);

	cell->next = NULL;
	cell->prev = NULL;

	return cell;
}

Move createMove(boardPos start, boardPos dest) {
	Move move;
	int x, y;
	x = (int)(dest[0] - 'A') - (int)(start[0] - 'A');
	y = (int)(dest[1] - '1') - (int)(start[1] - '1');
	move.rows = x;
	move.cols = y;
	return move;
}

int findAllStars(char** board) {
	int i, j, count = 0;
	for (i = 0; i < N; i++) {
		for (j = 0; i < M; j++) {
			if (board[i][j] == '*') {
				count++;
			}
		}
	}
	return count;
}

movesList *createNewList() {
	movesList *list = (movesList*)malloc(sizeof(movesList));
	list->head = NULL;
	list->tail = NULL;
	return list;
}
