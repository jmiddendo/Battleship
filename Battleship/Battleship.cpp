#include <iostream>
#include <vector>
#include "BoardGame.h"
#include "UserInterface.h"
using namespace std;

UserInterface display = UserInterface();
BoardGame fleets = BoardGame();

void registerGame(bool&, bool&, int&);
void playGame(int&, bool&, bool&);
void displayHelp();
void exitGame();
void assignShips(int);
void displayGameBoard(int, bool, bool);

int main()
{
	int userChoice = 4, playerTurn = 1;
	bool computerTurn = false, gameActive = false;

	do
	{
		if (gameActive)
			display.displayPlayerTurn(playerTurn);

		userChoice = display.displayMainMenu();

		switch (userChoice)
		{
			case 1:
			{
				registerGame(computerTurn, gameActive, playerTurn);
				break;
			}
			case 2:
			{
				playGame(playerTurn, gameActive, computerTurn);
				break;
			}
			case 3:
			{
					  displayGameBoard(playerTurn, gameActive, computerTurn);
				break;
			}
			case 4:
			{
				displayHelp();
				break;
			}
			case 5:
			{
				exitGame();
				break;
			}
		}
		display.insertBreak();
		display.insertBreak();
	
	} while (userChoice != display.getMainMenuSize());

	system("pause");

	return 0;
}

void registerGame(bool& turns, bool& active, int& player)
{
	int playerNumber = 0;

	if (active)
	{
		if (display.queryRestart() == "y")
		{
			turns = false;
			active = false;
			player = 1;
			fleets.emptyBoard();
		}
		else
			return;
	}
	
	playerNumber = display.queryPlayerNumber();

	if (playerNumber == 1)
		turns = true;
	else if (playerNumber == 2)
		turns = false;

	assignShips(1);

	system("cls");
	
	if (turns)
	{
		display.displayComputerAssignment();
		fleets.assignComputerShips();
	}
	else
		assignShips(2);

	system("cls");

	active = true;

	return;
}

void playGame(int &player, bool &start, bool &computer)
{
	bool runAgain = false;
	vector<int> shotPoint = vector<int>();
	char previousSpot = '0';

	if (!start)
	{
		display.displayStartError();
		return;
	}

	display.displayPlayerTurn(player);
	
	if (computer && player == 2)
	{
		do
		{
			shotPoint.clear();
			shotPoint = fleets.autoFire();

			previousSpot = fleets.getBoardSpot(1, shotPoint[0], shotPoint[1]);

			if (previousSpot == '*' || previousSpot == 'm')
			{
				runAgain = true;
				continue;
			}
			else
				runAgain = false;

		} while (runAgain);

		if (fleets.fireShot(player, shotPoint[0], shotPoint[1]))
		{
			display.displayShotResults(previousSpot);
			if (fleets.checkShipStatus(previousSpot, player))
				display.displayShipStatus(previousSpot);
		}
		else
			display.displayShotResults('m');

		if (fleets.checkWinStatus(player))
		{
			display.displayGameResults(player);
			start = false;
			player = 1;
			computer = false;
			fleets.emptyBoard();
		}
		else
		{
			if (player == 1)
				player = 2;
			else
				player = 1;
		}

	}
	else
	{
		displayGameBoard(player, start, computer);

		do
		{
			shotPoint.clear();
			shotPoint = display.queryFirePoint();

			if (player == 1)
				previousSpot = fleets.getBoardSpot(2, shotPoint[0], shotPoint[1]);
			else
				previousSpot = fleets.getBoardSpot(1, shotPoint[0], shotPoint[1]);

			if (previousSpot == '*' || previousSpot == 'm')
			{
				display.displayDuplicateShot();
				runAgain = true;
				continue;
			}
			else
				runAgain = false;

		} while (runAgain);

		if (fleets.fireShot(player, shotPoint[0], shotPoint[1]))
		{
			display.displayShotResults(previousSpot);
			if (fleets.checkShipStatus(previousSpot, player))
				display.displayShipStatus(previousSpot);
		}
		else
			display.displayShotResults('m');
	
		if (fleets.checkWinStatus(player))
		{
			display.displayGameResults(player);
			start = false;
			player = 1;
			computer = false;
			fleets.emptyBoard();
		}
		else
		{
			if (player == 1)
				player = 2;
			else
				player = 1;
		}
	}

	system("pause");

	system("cls");

	return;
}

void displayGameBoard(int player, bool start, bool computer)
{

	if (!start)
	{
		display.displayStartError();
		return;
	}

	if (computer && player == 2)
	{
		display.displayPlayerTurn(player);
	}
	else 
	{
		vector<string> boardVector = vector<string>();
		boardVector = fleets.getBoardSetup(player);
		display.displayBoard(boardVector);
		return;
	}


}

void displayHelp()
{
	display.displayHelp();
}

void exitGame()
{
	display.displayExit();
}

void assignShips(int player)
{
	const int SIZE = 5;
	char ships[] = {'a','b','s','d','p'};
	vector<string> strVec = fleets.getBoardSetup(player);
	vector<int> points = vector<int>(), endPoints = vector<int>();
	int x = 0, y = 0, length = 0, xy = 0;
	bool runAgain = true;


	for (int z = 0; z < SIZE; z++)
	{

		do 
		{
			points.clear();
			endPoints.clear();
			strVec = fleets.getBoardSetup(player);

			points = display.queryEntry(strVec[1]);

			if (fleets.getBoardSpot(player,points[0],points[1]) != '-')
			{
				display.displayDuplicateShot();
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
				if (fleets.validPlacement(player,points[0],points[1],points[0] + length, points[1]))
				{
					endPoints.push_back(points[0] + length);
					endPoints.push_back(points[1]);
				}

			if (points[0] - length >= 0)
				if (fleets.validPlacement(player, points[0], points[1], points[0] - length, points[1]))
				{
					endPoints.push_back(points[0] - length);
					endPoints.push_back(points[1]);
				}

			if (points[1] + length <= 9)
				if (fleets.validPlacement(player,points[0],points[1],points[0], points[1] + length))
				{
					endPoints.push_back(points[0]);
					endPoints.push_back(points[1] + length);
				}

			if (points[1] - length >= 0)
				if (fleets.validPlacement(player,points[0],points[1],points[0], points[1] - length))
				{
					endPoints.push_back(points[0]);
					endPoints.push_back(points[1] - length);
				}

			if (endPoints.size() == 0)
			{
				cout << "\nPlease enter a valid spot!\n";
				runAgain = true;
				continue;
			}

			xy = display.queryEntry(endPoints);
			x = xy / 10;
			y = xy % 10;

			points.push_back(x);
			points.push_back(y);
			runAgain = false;

		} while (runAgain);

		fleets.assignPlayerShips(player, points, ships[z]);
	} 

	return;
}