#include "const.h"
#include "Block.h"

unsigned long long int totalTime = 0;
unsigned long long int p1TotalTime = 0;
unsigned long long int p2TotalTime = 0;
int tmpLine1 = 0;
int tmpLine2 = 0;
short int p1Place;
short int p2Place;
bool p1CanHold = true;
bool p2CanHold = true;

void copyMatrix(int matrix[4][4], int temp[4][4], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            temp[i][j] = matrix[i][j];
        }
    }
}

void horizontalReflectioin(int matrix[4][4], int size)
{
    int temp[4][4];
    copyMatrix(matrix, temp, size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = temp[size - 1 - i][j];
        }
    }
}

void transpose(int matrix[4][4], int size)
{
    int temp[4][4];
    copyMatrix(matrix, temp, size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = temp[j][i];
        }
    }
}
