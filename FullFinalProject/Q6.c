

/*This program reads bordpositions from a binary file, and then it checks if the path of them is valid,
if it is the program prints the path according to the project definitions, and also return a different int value for:
if the file exists, if the path is valid, if the path covers the whole board and if it is not*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "Q6.h"



int checkAndDisplayPathFromFile(char *file_name, movesArray **moves, char **board)
{
	BYTE * bytesArr;
	int posotionsSize;
	int bytesArrSize;
	int bitsArrSize;
	int * bitsArr;
	int i, k, j, cnt = 1, legalPos = 0, repeated = 0;
	boardPosArray pos_arr;
	unsigned short int short1;
	char **newBoard;


	if (!isExists(file_name))
		return(-1);


	bytesArr = readFromFile(file_name, &short1, &bytesArrSize);

	posotionsSize = (int)short1;

	bitsArr = createBitsArr(bytesArr, bytesArrSize);

	bitsArrSize = bytesArrSize * 8;

	pos_arr = createPosArr(bitsArr, bitsArrSize, posotionsSize);

	if (validation(pos_arr, moves, board))
	{
		return (1);
	}

	newBoard = (char*)malloc(N * sizeof newBoard);
	checkAlloc(newBoard);
	for (i = 0; i < N; i++)
	{
		newBoard[i] = (char*)malloc(M * sizeof newBoard[i]);
		checkAlloc(newBoard[i]);
	}

	for (j = 0; j < N; j++) //sets values to be the same as the given board
	{
		for (i = 0; i < M; i++)
		{
			newBoard[j][i] = board[j][i];
			if (newBoard[j][i] = ' ')
				legalPos++;
		}
	}


	for (k = 0; k < pos_arr.size; k++)
	{
		j = (int)(pos_arr.positions[k][0] - 'A');
		i = (int)(pos_arr.positions[k][1] - '1');

		if (newBoard[j][i] == ' ')
		{
			newBoard[j][i] = (char)(cnt + '0');
			cnt++;
		}
		else
			repeated++;
	}

	printBoard(newBoard);

	if ((pos_arr.size) - repeated == legalPos)
	{
		return (2);
	}

	else
	{
		return (3);
	}

}


bool validation(boardPosArray pos_arr, movesArray **moves, char **board)
{
	int i, k, j, c, rows, cols, check = 0;


	for (k = 0; k < pos_arr.size; k++)
	{
		j = (int)(pos_arr.positions[k][0] - 'A');
		i = (int)(pos_arr.positions[k][1] - '1');

		if (inValidRows2(j) || inValidCols2(i))
		{
			return (true);
		}

		if (board[j][i] == '*')
		{
			return (true);
		}

		if (k < pos_arr.size - 1)
		{
			rows = (int)(pos_arr.positions[k + 1][0] - 'A') - j;
			cols = (int)(pos_arr.positions[k + 1][1] - '1') - i;

			for (c = 0; c < moves[j][i].size; c++)
			{
				if (moves[j][i].moves[c].rows == rows && moves[j][i].moves[c].cols == cols)
					check = 1;
			}

			if (check == 0)
				return (true);
			check = 0;
		}
	}

	return (false);
}


bool isExists(char *file_name)
{
	FILE *f;
	f = fopen(file_name, "rb");

	if (f == NULL)
		return(false);
	else
	{
		return(true);
		fclose(f);
	}
}



BYTE * readFromFile(char*fname, unsigned short int *short1, unsigned int *bytesArrSize)
{
	BYTE * bytesArr;
	unsigned int i;
	int sizeBytesArr;
	unsigned short int short2;
	FILE *f;

	f = fopen(fname, "rb");

	if (f == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		return;
	}

	fread(&short2, sizeof(unsigned short int), 1, f);

	sizeBytesArr = (int)short2 * 3 * 2;


	if (sizeBytesArr % 8 == 0)
		sizeBytesArr = sizeBytesArr / 8;
	else
		sizeBytesArr = (sizeBytesArr / 8) + 1;

	bytesArr = (BYTE *)malloc(sizeof(BYTE) * sizeBytesArr);
	checkAlloc(bytesArr);
	for (i = 0; i < sizeBytesArr; i++)
	{
		fread(&bytesArr[sizeBytesArr - i - 1], sizeof(BYTE), 1, f);
	}

	*short1 = short2;
	*bytesArrSize = sizeBytesArr;

	fclose(f);

	return(bytesArr);
}


int * createBitsArr(BYTE *arr, unsigned int arrSize)
{
	int i, j, k = 7, cnt = 0;

	int* intArr = (int *)malloc(sizeof(int) * arrSize * 8);
	checkAlloc(intArr);

	for (j = 0; j < arrSize; j++)
	{
		for (i = 0; i < 8; i++)
		{
			intArr[arrSize * 8 - 1 - cnt] = (int)((arr[j] >> i) & 1);
			cnt++;
		}
		k += 8;
	}
	return(intArr);
}


boardPosArray createPosArr(int *bitsArr, unsigned int bitsArrSize, unsigned int posSize)
{
	int i, j = 0;

	int * tmp = (int*)malloc(sizeof(int) * 3);
	checkAlloc(tmp);

	boardPosArray *pos_arr = (boardPosArray*)malloc(sizeof(boardPosArray));
	checkAlloc(pos_arr);
	pos_arr->size = posSize;
	pos_arr->positions = (boardPos*)malloc(sizeof(boardPos)*pos_arr->size);
	checkAlloc(pos_arr->positions);


	for (i = 0; i < posSize; i++)
	{
		tmp[0] = bitsArr[j];
		tmp[1] = bitsArr[j + 1];
		tmp[2] = bitsArr[j + 2];
		pos_arr->positions[i][0] = (char)(binaryToDecimal(tmp) + 'A');
		j += 3;
		tmp[0] = bitsArr[j];
		tmp[1] = bitsArr[j + 1];
		tmp[2] = bitsArr[j + 2];
		pos_arr->positions[i][1] = (char)(binaryToDecimal(tmp) + '1');
		j += 3;
	}

	return (*pos_arr);
}


int binaryToDecimal(int *arr)
{
	int num;

	num = arr[0] * 2 * 2 + arr[1] * 2 + arr[2];

	return (num);
}


bool inValidRows2(int num)
{
	return((num < 0) || (num >= N));
}


bool inValidCols2(int num)
{
	return((num < 0) || (num >= M));
}
