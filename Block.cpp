#include "block.h"

Block::Block(int type):
	y_(0),
	x_(4)
{
	switch (type)
	{
	case Z:
		matrix[0][0] = Z;
		matrix[0][1] = Z;
		matrix[1][1] = Z;
		matrix[1][2] = Z;
		this->size = 3;
		break;
	case S:
		matrix[0][1] = L;
		matrix[0][2] = L;
		matrix[1][0] = L;
		matrix[1][1] = L;
		this->size = 3;
		break;
	case J:
		matrix[0][0] = J;
		matrix[1][1] = J;
		matrix[1][2] = J;
		matrix[1][0] = J;
		this->size = 3;
		break;
	case L:
		matrix[0][2] = L;
		matrix[1][1] = L;
		matrix[1][2] = L;
		matrix[1][0] = L;
		this->size = 3;
		break;
	case O:
		matrix[0][0] = O;
		matrix[0][1] = O;
		matrix[1][0] = O;
		matrix[1][1] = O;
		this->size = 2;
		break;
	case I:
		matrix[1][0] = I;
		matrix[1][1] = I;
		matrix[1][2] = I;
		matrix[1][3] = I;
		this->size = 4;
		x_--;
		break;
	case T:
		matrix[1][0] = T;
		matrix[1][1] = T;
		matrix[1][2] = T;
		matrix[0][1] = T;
		this->size = 3;
		break;
	default:
		break;
	}
}

Block::~Block()
{

}

void Block::move(int x, int y)
{
	x_ += x;
	y_ += y;
}

void Block::rotate(int matrix[4][4])
{
	int temp[4][4];
	if (matrix == NULL) matrix = this->matrix;
	copyMatrix(matrix, temp, this->size);
	horizontalReflectioin(matrix,this->size);
	transpose(matrix, this->size);
}

void Block::collide()
{
	return false;
}

void Block::gravity()
{
	while (!collide())
	{
		move(0, 1);
	}
}

void Block::print()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (matrix[i][j] == 0) continue;
			int x_print = START_WIDTH + (x_ + j) * BLOCK_SIZE;
			int y_print = START_HEIGHT + (y_ + i - 4) * BLOCK_SIZE;
			if (y_print >= START_HEIGHT) BlockSheet.render(x_print, y_print, &BlockRect[matrix[i][j]]);
		}
	}
}

int Block::x()
{
	return x_;
}

int Block::y()
{
	return y_;
}


