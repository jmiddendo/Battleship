#ifndef BOARD_H
#define BOARD_H
#include <string>
using namespace std;


class Board
{
public:
	Board();
	Board(Board&);
	bool addShip(int, int, int, int, char);
	bool checkShipOverlap(int, int, int, int);
	void copyBoard(Board&);
	void displayHit(char, int, int);
	int getSize();
	bool receiveIncoming(int, int);
	string toString(char);
	char getBoardSpot(int, int);

private:
	static const int SIZE = 10;
	char topBoard[SIZE][SIZE];
	char bottomBoard[SIZE][SIZE];
};
#endif