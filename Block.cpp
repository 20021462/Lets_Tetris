#include "block.h"

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
		
		break;
	case S:
		matrix[0][1] = L;
		matrix[0][2] = L;
		matrix[1][0] = L;
		matrix[1][1] = L;
		break;
	case J:
		matrix[0][0] = J;
		matrix[1][1] = J;
		matrix[1][2] = J;
		matrix[1][0] = J;
		break;
	case L:
		matrix[0][2] = L;
		matrix[1][1] = L;
		matrix[1][2] = L;
		matrix[1][0] = L;
		break;
	case O:
		matrix[0][0] = O;
		matrix[0][1] = O;
		matrix[1][0] = O;
		matrix[1][1] = O;
		break;
	case I:
		matrix[0][0] = I;
		matrix[0][1] = I;
		matrix[0][2] = I;
		matrix[0][3] = I;
		break;
	case T:
		matrix[0][0] = T;
		matrix[0][1] = T;
		matrix[0][2] = T;
		matrix[1][1] = T;
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

}

int Block::x()
{
	return x_;
}

int Block::y()
{
	return y_;
}


