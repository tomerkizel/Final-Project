
/*This program gets a 2D array of moves and a 2D board. Then it checks all the moves in each cell to see if they are
valid or not according to the project definitions. This program returns a 2D array of valid boardPositions you can
reach to from each cell, and deletes the invalid moves from the 2D array of moves*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Q1.h"



boardPosArray ** validMoves(movesArray **moves, char **board)
{
	int i, j, k;
	int cnt = 0;
	boardPos boardPos1;

	boardPosArray ** positionsArray;
	positionsArray = (boardPosArray*)malloc(M * sizeof *positionsArray);
	checkAlloc(positionsArray);
	for (i = 0; i < M; i++)
	{
		positionsArray[i] = (boardPosArray*)malloc(N * sizeof *positionsArray[i]);
		checkAlloc(positionsArray[i]);
	}


	for (j = 0; j < N; j++)
	{
		for (i = 0; i < M; i++)
		{
			positionsArray[j][i].positions = (boardPos*)malloc((moves[j][i].size) * sizeof(boardPos));
			checkAlloc(positionsArray[j][i].positions);

			for (k = 0; k < moves[j][i].size; k++)
			{
				if (inValidRows(moves[j][i].moves[k], j) || inValidCols(moves[j][i].moves[k], i))
				{
					moves[j][i].moves[k].rows = FLAG;///flag of invalid move (char)
				}

				else if (board[j + moves[j][i].moves[k].rows][i + moves[j][i].moves[k].cols] == '*')
				{
					moves[j][i].moves[k].rows = FLAG;///flag of invalid move (char)
				}

				else
				{
					boardPos1[0] = (char)(j + moves[j][i].moves[k].rows + 'A');
					boardPos1[1] = (char)(i + moves[j][i].moves[k].cols + '1');
					positionsArray[j][i].positions[cnt][0] = boardPos1[0];
					positionsArray[j][i].positions[cnt][1] = boardPos1[1];
					cnt++;
				}
			}
			positionsArray[j][i].size = cnt;
			positionsArray[j][i].positions = (boardPos*)realloc(positionsArray[j][i].positions, sizeof(boardPos)*(cnt));

			moves[j][i].moves = deleteMoves(moves[j][i].moves, cnt, moves[j][i].size);
			moves[j][i].size = cnt;
			cnt = 0;
		}
	}
	return (positionsArray);
}


bool inValidRows(Move move, int num)
{
	return((num + move.rows < 0) || (num + move.rows >= N));
}


bool inValidCols(Move move, int num)
{
	return((num + move.cols < 0) || (num + move.cols >= M));
}


Move *deleteMoves(Move *moves, int num, int size)
{
	int i, j;
	int cnt = 0;

	for (i = 0; i < size - 1; i++)
	{
		if (moves[i].rows == FLAG)
		{
			for (j = i; j < size - 1; j++)
			{
				moves[j].rows = moves[j + 1].rows;
				moves[j].cols = moves[j + 1].cols;
			}
			cnt++;
		}
		moves = (Move*)realloc(moves, sizeof(Move)*(size - cnt));
	}
	return (moves);
}


void checkAlloc(void *memp)
{
	if (memp == NULL)
	{
		printf("Malloc failed\n");
		exit(0);
	}
}
