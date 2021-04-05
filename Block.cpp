#include "Block.h"

Block::Block(Block_type type):
	y_(0),
	x_ ((BOARD_WIDTH - 4) / 2)
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

int Block::x()
{
	return x_;
}

int Block::y()
{
	return y_;
}


