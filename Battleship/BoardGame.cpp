#include "BoardGame.h"
#include "Board.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
using namespace std;

BoardGame::BoardGame()
{
	for (int x = 0; x < SIZE; x++)
		listOfBoards[x] = Board();
}

void BoardGame::assignPlayerShips(int player, vector<int>& shipPoints, char sym)
{
	listOfBoards[player - 1].addShip(shipPoints[0],shipPoints[1],shipPoints[2],shipPoints[3],sym);
	return;
}

void BoardGame::emptyBoard()
{
	for (int x = 0; x < SIZE; x++)
		listOfBoards[x] = Board();
}

void BoardGame::assignComputerShips()
{
	const int SHIP_SIZE = 5;
	int x = 0, y = 0, length = 0, xy = 0, choice = 0;
	bool runAgain = true;
	char orientation[2] = { 'v', 'h' }, ships[SHIP_SIZE] = { 'a', 'b', 's', 'd', 'p' };
	vector<int> points = vector<int>(), endPoints = vector<int>();
	vector<string> secondLocation = vector<string>();
	string passValue = "";

	for (int z = 0; z < SHIP_SIZE; z++)
	{
		do
		{
			srand(time(NULL));

			points.clear();
			endPoints.clear();

			x = rand() % 10;
			y = rand() % 10;

			points.push_back(x);
			points.push_back(y);

			if (getBoardSpot(2, points[0], points[1]) != '-')
			{
				runAgain = true;
				continue;
			}

			switch (ships[z])
			{
				case 'a':
				{
						length = 4;
						break;
				}
				case 'b':
				{
						length = 3;
						break;
				}
				case 's':
				{
						length = 2;
						break;
				}
				case 'd':
				{
						length = 2;
						break;
				}
				case 'p':
				{
						length = 1;
						break;
				}
			}

			if (points[0] + length <= 9)
			if (validPlacement(2, points[0], points[1], points[0] + length, points[1]))
			{
				x = points[0] + length;
				y = points[1];
				endPoints.push_back(x);
				endPoints.push_back(y);
			}

			if (points[0] - length >= 0)
			if (validPlacement(2, points[0], points[1], points[0] - length, points[1]))
			{
				x = points[0] - length;
				y = points[1];
				endPoints.push_back(x);
				endPoints.push_back(y);
			}

			if (points[1] + length <= 9)
			if (validPlacement(2, points[0], points[1], points[0], points[1] + length))
			{
				x = points[0];
				y = points[1] + length;
				endPoints.push_back(x);
				endPoints.push_back(y);
			}

			if (points[1] - length >= 0)
			if (validPlacement(2, points[0], points[1], points[0], points[1] - length))
			{
				x = points[0];
				y = points[1] - length;
				endPoints.push_back(x);
				endPoints.push_back(y);
			}

			if (endPoints.size() == 0)
			{
				runAgain = true;
				continue;
			}

			secondLocation.clear();

			for (int i = 0; i < endPoints.size(); i += 2)
			{
				passValue = (to_string((endPoints[i] * 10) + endPoints[i + 1]));
				if (passValue.length() == 1)
					passValue = "0" + passValue;
				secondLocation.push_back(passValue);
			}

			choice = secondLocation.size() - 1;
			if (choice == 0)
				passValue = secondLocation[0];
			else
				passValue = secondLocation[rand() % choice];

			xy = atoi(passValue.c_str());
			x = xy / 10;
			y = xy % 10;

			points.push_back(x);
			points.push_back(y);

			if (points[0] != points[2] && points[1] != points[3])
			{
				runAgain = true;
				continue;
			}
			else
				runAgain = false;

		} while (runAgain);

		assignPlayerShips(2, points, ships[z]);


	}

	return;
}

bool BoardGame::validPlacement(int player, int x1, int y1, int x2, int y2)
{
	return listOfBoards[player - 1].checkShipOverlap(x1,y1,x2,y2);
}

bool BoardGame::fireShot(int player, int x, int y)
{
	bool retValue = true;
	if (player == 1)
	{
		retValue = listOfBoards[1].receiveIncoming(x,y);
		if(retValue)
			listOfBoards[0].displayHit('*',x,y);
		else
			listOfBoards[0].displayHit('m',x,y);
	}
	else if (player == 2)
	{
		retValue = listOfBoards[0].receiveIncoming(x,y);
		if(retValue)
			listOfBoards[1].displayHit('*',x,y);
		else
			listOfBoards[1].displayHit('m',x,y);

	}
	return retValue;
}

char BoardGame::getBoardSpot(int player, int x, int y)
{
	return listOfBoards[player - 1].getBoardSpot(x, y);
}

bool BoardGame::checkShipStatus(char checkValue, int player)
{
	int playerNumber = 0;

	if (player == 1)
		playerNumber = 1;
	else
		playerNumber = 0;

	string checkLine = listOfBoards[playerNumber].toString('b');

	for (int i = 0; i < checkLine.size(); i++)
		if (checkLine[i] == checkValue)
			return false;

	return true;
}

vector<int> BoardGame::autoFire()
{
	vector<int> retValue = vector<int>();
	int x = 0, y = 0;

	x = rand() % 10;
	y = rand() % 10;

	retValue.push_back(x);
	retValue.push_back(y);

	return retValue;
}

vector<string> BoardGame::getBoardSetup(int player)
{
	vector<string> tempSetup = vector<string>();
	tempSetup.push_back(listOfBoards[player - 1].toString('t'));
	tempSetup.push_back(listOfBoards[player - 1].toString('b'));

	return tempSetup;
}

bool BoardGame::checkWinStatus(int player)
{
	int playerNumber = 0;

	if (player == 1)
		playerNumber = 1;
	else
		playerNumber = 0;

	string checkLine = listOfBoards[playerNumber].toString('b');

	for (int i = 0; i < checkLine.size(); i++)
	{
		switch (checkLine[i])
		{
			case 'a':
			case 'b':
			case 's':
			case 'd':
			case 'p':
				return false;
		}
	}

	return true;
}
