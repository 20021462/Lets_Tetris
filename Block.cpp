#include "block.h"
#include "playerField.h"

short int nextBlock[5];
short int p1NextBlock[5];
short int p2NextBlock[5];
short int fullList[50];

Block block[5];
Block p1Block[5];
Block p2Block[5];

void generateBlockId(short matrix[], int n)
{
	matrix[0] = 0;
	for (int i = 1; i < n; i++)
	{
		matrix[i] = rand() % 7 + 1;
	}
}

void newBlockGenerate(short matrix[], int n)
{
	for (int i = 1; i < n - 1; i++)
	{
		matrix[i] = matrix[i + 1];
	}
	matrix[n - 1] = rand() % 7 + 1;
}

void getBlockId(short matrix[], short list[], int startPoint)
{
	for (int i = 1; i < 5; i++)
	{
		matrix[i] = list[startPoint + i - 1];
	}
}

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
	if (this->size == 3) x_ = 3;
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

void Block::hardDrop(int(*field)[10], int &point)
{
	int line = 0;
	while (!collide(field))
	{
		line++;
		move(0, 1);
	}
	point += (line - 1) * 2;
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

void Block::print(int x)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (matrix[i][j] == 0) continue;
			int x_print = x + (x_ + j) * BLOCK_SIZE;
			int y_print = START_HEIGHT + (y_ + i - 2) * BLOCK_SIZE;
			if (y_print >= START_HEIGHT) BlockSheet.render(x_print, y_print, &BlockRect[matrix[i][j]]);
		}
	}
}

void Block::printNext(int x, int y, int size)
{
	x_ = -1;
	if (this->size == 2) x_ = 0;
	y_ = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (matrix[i][j] == 0) continue;
			int x_print;
			int y_print;

			if (size == 0)
			{
				x_print = x + (x_ + j) * BLOCK_SIZE;
				y_print = y + (y_ + i) * BLOCK_SIZE;
			}
			else
			{
				x_print = x + (x_ + j) * size;
				y_print = y + (y_ + i) * size;
			}
			BlockSheet.render(x_print, y_print, &BlockRect[matrix[i][j]], size);
		}
	}
}

void Block::printShade(int x)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (matrix[i][j] == 0) continue;
			int x_print = x + (x_ + j) * BLOCK_SIZE;
			int y_print = START_HEIGHT + (y_ + i - 2) * BLOCK_SIZE;
			if (y_print >= START_HEIGHT) ShadeSheet.render(x_print, y_print, &BlockRect[matrix[i][j]]);
		}
	}
}

void hold(Block blocks[], short matrix[], int n)
{
	if (!matrix[0])
	{
		matrix[0] = matrix[1];
		newBlockGenerate(matrix, n);
	}
	else
	{
		int tmp = matrix[0];
		matrix[0] = matrix[1];
		matrix[1] = tmp;
	}
	blocks[0].generate(matrix[0]);
	blocks[1].generate(matrix[1]);
}