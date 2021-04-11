#include "block.h"
#include "playerField.h"

Block::Block():
	y_(0),
	x_(4)
{
}

Block::~Block()
{

}

void Block::generate(int type)

{
	x_ = 4;
	y_ = 0;
	int temp[4][4] = { {0} };
	copyMatrix(temp, matrix, size);
	switch (type)
	{
	case BLOCK_Z:
		matrix[0][0] = type;
		matrix[0][1] = type;
		matrix[1][1] = type;
		matrix[1][2] = type;
		this->size = 3;
		break;
	case BLOCK_S:
		matrix[0][1] = type;
		matrix[0][2] = type;
		matrix[1][0] = type;
		matrix[1][1] = type;
		this->size = 3;
		break;
	case BLOCK_J:
		matrix[0][0] = type;
		matrix[1][1] = type;
		matrix[1][2] = type;
		matrix[1][0] = type;
		this->size = 3;
		break;
	case BLOCK_L:
		matrix[0][2] = type;
		matrix[1][1] = type;
		matrix[1][2] = type;
		matrix[1][0] = type;
		this->size = 3;
		break;
	case BLOCK_O:
		matrix[0][0] = type;
		matrix[0][1] = type;
		matrix[1][0] = type;
		matrix[1][1] = type;
		this->size = 2;
		break;
	case BLOCK_I:
		matrix[1][0] = type;
		matrix[1][1] = type;
		matrix[1][2] = type;
		matrix[1][3] = type;
		this->size = 4;
		x_--;
		break;
	case BLOCK_T:
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


bool Block::collide(int(*field)[10])
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] && (this->y_ + i == BOARD_HEIGHT || field[this->y_ + i][this->x_ + j] != 0)) return true;
		}
	}
	return false;
}

void Block::move(int x, int y)
{
	x_ += x;
	y_ += y;
}

void Block::rotate(int matrix[4][4], int(*field)[10])
{
	int temp[4][4] = { {0} };
	if (matrix == NULL) matrix = this->matrix;
	copyMatrix(matrix, temp, 4);
	horizontalReflectioin(matrix,this->size);
	transpose(matrix, this->size);

	int xMove = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			while (matrix[i][j] && ((this->x_ + j >= BOARD_WIDTH)))
			{
				move(-1, 0);
				xMove--;
			}
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			while (matrix[i][j] && ((this->x_ + j < 0)))
			{
				move(1, 0);
				xMove++;
			}
		}
	}

	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			if (matrix[i][j] && ((this->y_ + i >= BOARD_HEIGHT) || (field[this->y_ + i][this->x_ + j] != 0)))
			{
				copyMatrix(temp, matrix, 4);
				move(-xMove, 0);
				xMove = 0;
				return;
			}
		}
	}
}

void Block::hardDrop(int(*field)[10])
{
	while (!collide(field))
	{
		move(0, 1);
	}
}

void Block::moveRight(int(*field)[10])
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] && ((this->x_ + j + 1 == BOARD_WIDTH) || (field[this->y_ + i][this->x_ + j + 1] != 0)))
			{
				return;
			}
		}
	}
	move(1, 0);
}

void Block::moveLeft(int(*field)[10])
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] && ((this->x_ + j == 0) || (field[this->y_ + i][this->x_ + j - 1] != 0)))
			{
				return;
			}
		}
	}
	move(-1, 0);
}

/*void Block::control(SDL_Event &keypress)
{
	if (keypress.type == SDL_KEYDOWN && keypress.key.repeat == 0)
	{
		switch (keypress.key.keysym.sym)
		{
			case SDLK_UP:
				rotate(matrix);
				break;

			case SDLK_DOWN:
				move(0, 1);
				break;

			case SDLK_RIGHT:
				moveRight();
				break;

			case SDLK_LEFT:
				moveLeft();
				break;

			case SDLK_SPACE:
				hardDrop();
				break;

			default:
				break;
		}
	}

}*/

void Block::print()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (matrix[i][j] == 0) continue;
			int x_print = START_WIDTH + (x_ + j) * BLOCK_SIZE;
			int y_print = START_HEIGHT + (y_ + i - 2) * BLOCK_SIZE;
			if (y_print >= START_HEIGHT) BlockSheet.render(x_print, y_print, &BlockRect[matrix[i][j]]);
		}
	}
}

void Block::printShade()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (matrix[i][j] == 0) continue;
			int x_print = START_WIDTH + (x_ + j) * BLOCK_SIZE;
			int y_print = START_HEIGHT + (y_ + i - 2) * BLOCK_SIZE;
			if (y_print >= START_HEIGHT) ShadeSheet.render(x_print, y_print, &BlockRect[matrix[i][j]]);
		}
	}
}

