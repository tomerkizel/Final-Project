//Roei Rabey 314983594
//Tomer Kizel 315765891
//Final Project Q5

/*This program gets an array of boardpos and saves them in a binary file according to the project definitions
as bits including an unsigned short int which represents the size of the array*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "Q5.h"



void saveListToBinFile(char *file_name, boardPosArray *pos_arr)
{
	BYTE * bytesArr;
	int size1;
	int size2;
	int * bitsArr;
	int * bitsPosition;
	unsigned short int short1 = pos_arr->size;

	bitsArr = createBitsArray(pos_arr->positions, pos_arr->size, &size1);

	bitsPosition = bitsPos(bitsArr, size1, &size2);

	bytesArr = createBytesArray(bitsPosition, size2, &size1);

	saveInFile(bytesArr, file_name, size1, short1);

	free(bitsArr);
	free(bytesArr);
	free(bitsPosition);

}


int * createBitsArray(boardPos *positions, int size, int *bitsSize)
{
	int i, j = 0, k = 0;
	int * binary;
	int * num;

	*bitsSize = size * 3 * 2;
	k = 8 - (*bitsSize % 8);
	*bitsSize += k;

	binary = (int*)malloc(sizeof(int) * (*bitsSize));
	checkAlloc(binary);

	for (i = 0; i < size; i++)
	{
		num = decimalToBinary((int)(positions[i][0] - 'A'));
		binary[j] = num[0];
		binary[j + 1] = num[1];
		binary[j + 2] = num[2];
		j += 3;
		num = decimalToBinary((int)(positions[i][1] - '1'));
		binary[j] = num[0];
		binary[j + 1] = num[1];
		binary[j + 2] = num[2];
		j += 3;
	}

	for (i = 0; i < k; i++)
		binary[*bitsSize - k + i] = 0;

	return (binary);
}


int* bitsPos(int *arr, int bitsSize, int *size2)
{
	int i, j = 0;
	int * arr2;

	arr2 = (int*)malloc(sizeof(int)*bitsSize);
	checkAlloc(arr2);

	for (i = bitsSize - 1; i >= 0; i--)
	{
		if (arr[i] == 1)
		{
			arr2[j] = bitsSize - 1 - i;

			j++;
		}
	}

	*size2 = j;
	arr2 = realloc(arr2, sizeof(int)*j);

	return (arr2);
}


int* decimalToBinary(int num)
{
	int *binary;
	int i = 0;

	binary = (int*)malloc(sizeof(int) * 3);
	checkAlloc(binary);

	while (num > 0)
	{
		binary[2 - i] = num % 2;
		num = num / 2;
		i++;
	}

	while (i < 3)
	{
		binary[2 - i] = 0;
		i++;
	}

	return (binary);
}


BYTE * createBytesArray(int *arr, int size, int * bitsSize)
{
	int i;
	BYTE * bytesArr;
	int max = maxValue(arr, size);
	int newSize = max / 8 + 1;

	bytesArr = (BYTE *)malloc(sizeof(BYTE) * newSize);
	checkAlloc(bytesArr);

	for (i = 0; i < newSize; i++)
		bytesArr[i] = 0;

	for (i = 0; i < size; i++)
		bytesArr[arr[i] / 8] = setBit(bytesArr[arr[i] / 8], arr[i] % 8);

	*bitsSize = newSize;

	return (bytesArr);
}


int maxValue(int *arr, int size)
{
	int i;
	int max = arr[0];

	for (i = 1; i < size; i++)
	{
		if (arr[i] > max)
			max = arr[i];
	}

	return (max);
}


BYTE setBit(BYTE ch, int i)
{
	BYTE mask = 1 << i;
	return (ch | mask);
}


void saveInFile(BYTE * bitsArr, char*fname, unsigned int arrSize, unsigned short int short1)
{
	unsigned int i;
	FILE *f;


	f = fopen(fname, "wb");
	if (f == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		return;
	}

	fwrite(&short1, sizeof(unsigned short int), 1, f);

	for (i = 0; i < arrSize; i++)
	{
		fwrite(&bitsArr[arrSize - i - 1], sizeof(BYTE), 1, f);
	}

	fclose(f);
}
