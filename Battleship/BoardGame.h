#ifndef BOARDGAME_H
#define BOARDGAME_H
#include "Board.h"
#include <vector>


class BoardGame
{
public:
	BoardGame();
	int determineEndPoint(int, int);
	void assignPlayerShips(int, std::vector<int>&, char);
	void assignComputerShips();
	void emptyBoard();
	bool validPlacement(int, int, int, int, int);
	bool fireShot(int, int, int);
	char getBoardSpot(int, int, int);
	bool checkShipStatus(char, int);
	std::vector<int> autoFire();
	vector<string> getBoardSetup(int);
	bool checkWinStatus(int);
	

private:
	static const int SIZE = 2;
	Board listOfBoards[SIZE];
};

#endif