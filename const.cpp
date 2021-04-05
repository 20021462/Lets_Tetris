#include "const.h"

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
