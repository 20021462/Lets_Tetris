#include "block.h"

Block::Block():
	y_(0),
	x_(4)
{
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
	int temp[4][4] = { {0} };
	if (matrix == NULL) matrix = this->matrix;
	copyMatrix(matrix, temp, 4);
	horizontalReflectioin(matrix,this->size);
	transpose(matrix, this->size);
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			if (matrix[i][j] && (player1Field[this->y_ + i][this->x_ + j] != 0))
			{
				copyMatrix(temp, matrix, 4);
				break;
			}
		}
	}
}


bool Block::collide()
{	
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] && (this->y_+i+1 == BOARD_HEIGHT|| player1Field[this->y_ + i + 1][this->x_+j]!=0)) return true;
		}
	}
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

void Block::generate(int type)

{
	x_ = 4;
	y_ = 0;
	int temp[4][4] = { {0} };
	copyMatrix(temp, matrix, size);
	switch (type)
	{
	case Z:
		matrix[0][0] = type;
		matrix[0][1] = type;
		matrix[1][1] = type;
		matrix[1][2] = type;
		this->size = 3;
		break;
	case S:
		matrix[0][1] = type;
		matrix[0][2] = type;
		matrix[1][0] = type;
		matrix[1][1] = type;
		this->size = 3;
		break;
	case J:
		matrix[0][0] = type;
		matrix[1][1] = type;
		matrix[1][2] = type;
		matrix[1][0] = type;
		this->size = 3;
		break;
	case L:
		matrix[0][2] = type;
		matrix[1][1] = type;
		matrix[1][2] = type;
		matrix[1][0] = type;
		this->size = 3;
		break;
	case O:
		matrix[0][0] = type;
		matrix[0][1] = type;
		matrix[1][0] = type;
		matrix[1][1] = type;
		this->size = 2;
		break;
	case I:
		matrix[1][0] = type;
		matrix[1][1] = type;
		matrix[1][2] = type;
		matrix[1][3] = type;
		this->size = 4;
		x_--;
		break;
	case T:
		matrix[1][0] = type;
		matrix[1][1] = type;
		matrix[1][2] = type;
		matrix[0][1] = type;
		this->size = 3;
		break;
	default:
		break;
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

void unite(Block& block)
{
	if (block.collide())
	{
		for (int i = 0; i < block.size; i++)
		{
			for (int j = 0; j < block.size; j++)
			{
				if (block.matrix[i][j])
				{
					player1Field[block.y_ + i][block.x_ + j] = block.matrix[i][j];
				}
			}
		}
	}
}
