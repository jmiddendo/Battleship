#include "GameController.h"

GameController::GameController()
{
    display = UserInterface();
    fleets = BoardGame();
}

void GameController::assignShips(int player)
{
    const int SIZE = 5;
	char ships[] = {'a','b','s','d','p'};
	std::vector<std::string> strVec = fleets.getBoardSetup(player);
	std::vector<int> points = std::vector<int>(), endPoints = std::vector<int>();
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
				display.filledSpot();
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
                display.invalidSpot();
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
}

void GameController::displayGameBoard(int player, bool start, bool computer)
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
		std::vector<std::string> boardVector = std::vector<std::string>();
		boardVector = fleets.getBoardSetup(player);
		display.displayBoard(boardVector);
		return;
	}
}

void GameController::exitGame()
{
    display.displayExit();
}

void GameController::displayHelp()
{

    display.displayHelp();

}

void GameController::init()
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

}

void GameController::playGame(int &player, bool &start, bool &computer)
{
    bool runAgain = false;
	std::vector<int> shotPoint = std::vector<int>();
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

	if (system("cls"))
        system("clear");

	return;
}

void GameController::registerGame(bool& turns, bool& active, int& player)
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

	if (system("cls"))
        system("clear");

	if (turns)
	{
		display.displayComputerAssignment();
		fleets.assignComputerShips();
	}
	else
		assignShips(2);

	if (system("cls"))
        system("clear");

	active = true;

	return;
}
