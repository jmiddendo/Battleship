#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <vector>


class Board
{
public:
	Board();
	Board(int);
	Board(const Board&);
	bool addShip(int, int, int, int, char);
	bool checkShipOverlap(int, int, int, int);
	void clearBoard();
	void copyBoard(const Board&);
	void displayHit(char, int, int);
	int getSize();
	bool receiveIncoming(int, int);
	std::string toString(char);
	char getBoardSpot(int, int);

private:
	int boardSize;
	std::vector<std::vector<char>> topBoard;
	std::vector<std::vector<char>>  bottomBoard;
};
#endif
