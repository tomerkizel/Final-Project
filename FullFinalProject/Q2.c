

/*This program gets moves list, a 2D board and a start pos and prints the list's path according to the project definitions
,deletes the invalid moves in the list the returns the number of them*/


#define N 4 ///Rows

#define M 5 ///Columns


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Q2.h"



int display(movesList *moves_list, boardPos start, char **board)
{
	int count = 1;
	int removed = 0;
	int i, j;
	moveCell *temp;
	moveCell *tempPrevious;

	char **newBoard;//new board to print changes
	newBoard = (char*)malloc(N * sizeof *newBoard);
	checkAlloc(newBoard);
	for (i = 0; i < N; i++)
	{
		newBoard[i] = (char*)malloc(M * sizeof *newBoard[i]);
		checkAlloc(newBoard[i]);
	}


	for (j = 0; j < N; j++) //sets values to be the same as the given board
	{
		for (i = 0; i < M; i++)
		{
			newBoard[j][i] = board[j][i];
		}
	}

	newBoard[(int)(start[0] - 'A')][(int)(start[1] - '1')] = '#';

	temp = moves_list->head;

	while (temp != NULL)
	{
		if (inValidRows(temp->move, (int)(start[0] - 'A')) || inValidCols(temp->move, (int)(start[1] - '1')))
		{
			if (temp->prev == NULL)
			{
				temp = temp->next;
				free(temp->prev);
				temp->prev = NULL;
			}

			else if (temp->next == NULL)
			{
				temp = temp->prev;
				free(temp->next);
				temp->next = NULL;
				temp = temp->next;
			}

			else
			{
				temp = temp->next;
				removeCell(temp->prev);
			}

			removed++;
		}

		else if (newBoard[(int)(start[0] - 'A') + temp->move.rows][(int)(start[1] - '1') + temp->move.cols] == ' ')
		{
			newBoard[(int)(start[0] - 'A') + temp->move.rows][(int)(start[1] - '1') + temp->move.cols] = (char)(count + '0');
			count++;
			start[0] = (char)(start[0] + temp->move.rows);
			start[1] = (char)(start[1] + temp->move.cols);
			temp = temp->next;
		}

		else /// already has a number or *
		{
			if (temp->prev == NULL)
			{
				temp = temp->next;
				free(temp->prev);
				temp->prev = NULL;
			}

			else if (temp->next == NULL)
			{
				temp = temp->prev;
				free(temp->next);
				temp->next = NULL;
				temp = temp->next;
			}

			else
			{
				temp = temp->next;
				removeCell(temp->prev);
			}

			removed++;
		}
	}

	printBoard(newBoard);

	free(newBoard);

	return (removed);
}


void printBoard(char **board)
{
	char letter = 'A';;
	int i, j, num;

	printf(" ");

	for (num = 1; num <= M; num++)//printing the numbers row in the top of the board
		printf("   %d", num);

	printf("\n\n");


	for (j = 1; j <= N; j++)
	{
		for (i = 0; i <= M; i++)
		{
			if (i == 0)
				printf("%c", letter);
			else
				printf("   %c", board[j - 1][i - 1]);
		}
		letter++;
		printf("\n\n");
	}
}


void removeCell(moveCell *toDelete)
{
	moveCell *prev;

	prev = toDelete->prev;
	prev->next = toDelete->next;
	toDelete->next->prev = prev;
	free(toDelete);
}


