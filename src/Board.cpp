#include "Board.h"

Board::Board()
{
    boardSize = 10;
	for (int x = 0; x < boardSize; x++)
    {
        topBoard.push_back(std::vector<char>(10));
        bottomBoard.push_back(std::vector<char>(10));
		for (int y = 0; y < boardSize; y++)
		{
			bottomBoard[x][y] = '-';
			topBoard[x][y] = '-';
		}
    }

}

Board::Board(int NewSize)
{
    boardSize = NewSize;
	for (int x = 0; x < boardSize; x++)
    {
        topBoard.push_back(std::vector<char>(10));
        bottomBoard.push_back(std::vector<char>(10));
		for (int y = 0; y < boardSize; y++)
		{
			bottomBoard[x][y] = '-';
			topBoard[x][y] = '-';
		}
    }
}

Board::Board(const Board& obj)
{
    boardSize = obj.boardSize;
    bottomBoard = obj.bottomBoard;
    topBoard = obj.topBoard;

}

void Board::copyBoard(const Board& copyBoard)
{
	boardSize = copyBoard.boardSize;
	topBoard = copyBoard.topBoard;
	bottomBoard = copyBoard.bottomBoard;
}

bool Board::addShip(int x1, int y1, int x2, int y2, char sym)
{
	if (x1 == x2 && y1 != y2)
	{
		if (y1 < y2)
		{
			for (int i = y1; i <= y2; i++)
			{
				bottomBoard[x1][i] = sym;
			}
		}
		else
		{
			for (int i = y1; i >= y2; i--)
			{
				bottomBoard[x1][i] = sym;
			}
		}
	}
	else if (x1 != x2 && y1 == y2)
	{
		if (x1 < x2)
		{
			for (int i = x1; i <= x2; i++)
			{
				bottomBoard[i][y1] = sym;
			}
		}
		else
		{
			for (int i = x1; i >= x2; i--)
			{
				bottomBoard[i][y1] = sym;
			}
		}
	}
	else
		return false;

	return true;
}

bool Board::checkShipOverlap(int x1, int y1, int x2, int y2)
{
	if (x1 == x2 && y1 != y2)
	{
		if (y1 < y2)
		{
			for (int i = y1; i <= y2; i++)
			{
				if (bottomBoard[x1][i] != '-')
				{
					return false;
				}
			}
		}
		else
		{
			for (int i = y1; i >= y2; i--)
			{
				if (bottomBoard[x1][i] != '-')
				{
					return false;
				}
			}
		}
	}
	else if (x1 != x2 && y1 == y2)
	{
		if (x1 < x2)
		{
			for (int i = x1; i <= x2; i++)
			{
				if (bottomBoard[i][y1] != '-')
				{
					return false;
				}
			}
		}
		else
		{
			for (int i = x1; i >= x2; i--)
			{
				if (bottomBoard[i][y1] != '-')
				{
					return false;
				}
			}
		}
	}

	return true;
}

void Board::displayHit(char sym, int x, int y)
{
	topBoard[x][y] = sym;
	return;
}

int Board::getSize()
{
	return boardSize;
}

bool Board::receiveIncoming(int x, int y)
{
	if (bottomBoard[x][y] != '-')
	{
		bottomBoard[x][y] = '*';
		return true;
	}
	else
	{
		bottomBoard[x][y] = 'm';
		return false;
	}
}

std::string Board::toString(char board)
{
	std::string retVal = "";
	if(board == 't')
		for (int x = 0; x < boardSize; x++)
			for (int y = 0; y < boardSize; y++)
				retVal += topBoard[x][y];
	else if (board == 'b')
		for (int x = 0; x < boardSize; x++)
			for (int y = 0; y < boardSize; y++)
				retVal += bottomBoard[x][y];

	return retVal;
}

char Board::getBoardSpot(int x, int y)
{
	return bottomBoard[x][y];
}
