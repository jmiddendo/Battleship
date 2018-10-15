#include "UserInterface.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

UserInterface::UserInterface()
{
	mainMenuSize = 5;
}

UserInterface::UserInterface(int newSize)
{
	mainMenuSize = newSize;
}

int UserInterface::displayMainMenu()
{
	bool runAgain = false;
	std::string userChoice = "0";

	do
	{
		std::cout << "        Battleship" << std::endl
			 << "---------------------------" << std::endl
			 << "(1) Start Game" << std::endl
			 << "(2) Play Turn" << std::endl
			 << "(3) Display Game Board" << std::endl
			 << "(4) Display Help" << std::endl
			 << "(5) Exit Game" << std::endl
			 << "What would you like to do: ";
		std::cin >> userChoice;

		if (userChoice < "1" || userChoice > "5")
		{
			std::cout << "Please enter a valid number!\n\n";
			runAgain = true;
		}
		else
			runAgain = false;

	} while (runAgain);

	return atoi(userChoice.c_str());
}

void UserInterface::insertBreak()
{
	std::cout << '\n';
	return;
}

int UserInterface::getMainMenuSize()
{
	return mainMenuSize;
}

void UserInterface::setMainMenuSize(int newSize)
{
	mainMenuSize = newSize;
	return;
}

int UserInterface::queryPlayerNumber()
{
	std::string retValue = "0";
	bool runAgain = true;

	do
	{
	std::cout << "Is there 1 player or 2 players (1 or 2)? ";
	std::cin >> retValue;

	if (retValue < "1" || retValue > "2")
	{
		std::cout << "\nPlease enter a 1 or 2\n\n";
		runAgain = true;
	}
	else
		runAgain = false;

	} while (runAgain);

	return atoi(retValue.c_str());
}

std::string UserInterface::queryRestart()
{
	std::string retValue = "";
	bool runAgain = true;

	do
	{
		std::cout << "There is already a game in progress.  Do you want to start a new game (y or n): ";
		std::cin >> retValue;

		if(retValue.size() != 1)
		{
			std::cout << "Please enter only y or n.\n";
			runAgain = true;
		}
		else if (tolower(retValue[0]) != 'y' && tolower(retValue[0]) != 'n')
		{
			std::cout << "Please enter a valid value (y or n).\n";
			runAgain = true;
		}
		else
			runAgain = false;

	} while (runAgain);

	return retValue;
}

void UserInterface::displayBoard(std::vector<std::string>& displayString)
{
	displayBoard("\nEnemy Board\n", displayString[0]);
	displayBoard("\nYour Board\n", displayString[1]);

	return;
}

void UserInterface::displayBoard(std::string title, std::string readString)
{
	std::cout << title;
	for (int i = 0; i < readString.size(); i++)
	{
		std::cout << readString[i] << ' ';
		if(i % 10 == 9)
			std::cout << '\n';
	}
}

std::vector<int> UserInterface::queryEntry(std::string readLine)
{
	std::vector<int> retValue = std::vector<int>();
	std::string x1 = "0", y1 = "0", x2 = "0", y2 = "0";
	bool runAgain = true;

	displayBoard("\nChose points\n", readLine);

	do
	{
		std::cout << "\nPlease enter an x coordinate (0 to 9): ";
		std::cin >> x1;

		if (x1 < "0" || x1 > "9")
		{
			std::cout << "Please enter a valid coordinate.  Try again!";
			runAgain = true;
		}
		else
			runAgain = false;
	} while(runAgain);

	retValue.push_back(atoi(x1.c_str()));

	do
	{
		std::cout << "Please enter a y coordinate (0 to 9): ";
		std::cin >> y1;

		if (y1 < "0" || y1 > "9")
		{
			std::cout << "Please enter a valid coordinate.  Try again!";
			runAgain = true;
		}
		else
			runAgain = false;

	} while (runAgain);

	retValue.push_back(atoi(y1.c_str()));

	return retValue;
}

int UserInterface::queryEntry(std::vector<int> possibleEndPoints)
{
	bool runAgain = true;
	std::string retValue = "0", passValue = "0";
	std::vector<std::string> secondLocation = std::vector<std::string>();

	for (int i = 0; i < possibleEndPoints.size(); i += 2)
	{
		passValue = (std::to_string((possibleEndPoints[i] * 10) + possibleEndPoints[i + 1]));
		if (passValue.length() == 1)
			passValue = "0" + passValue;
		secondLocation.push_back(passValue);
	}

	do
	{
		std::cout << "\nPlease chose a second coordinate (";
		for (int i = 0; i < secondLocation.size(); i++)
			if (i == secondLocation.size() - 1)
				std::cout << secondLocation[i];
			else
				std::cout << secondLocation[i] << " or ";
		std::cout << "): ";
		std::cin >> retValue;

		for (int i = 0; i < retValue.size(); i++)
			if (retValue[i] < '0' || retValue[i] > '9')
			{
				std::cout << "Please enter a valid coordinate.  Try again!";
				runAgain = true;
				continue;
			}

			for (int i = 0; i < secondLocation.size(); i++)
			{
				if (retValue.c_str() == secondLocation[i])
				{
					runAgain = false;
					continue;
				}
			}

			if (runAgain)
			{
				std::cout << "Please enter a valid coordinate.  Try again!";
			}


	} while (runAgain);


	return atoi(retValue.c_str());
}

void UserInterface::displayStartError()
{
	std::cout << "\nPlease start a game to continue! Try again!\n";
	return;
}

void UserInterface::displayExit()
{
	std::cout << "\nThank you for playing.  Have a pleasant day!" << std::endl << std::endl;
	return;
}

void UserInterface::displayComputerAssignment()
{
	std::cout << "\nPlease wait! Assigning computer ships...\n";
	return;
}

void UserInterface::displayHelp()
{
	std::cout << "\nWelcome to the battleship game!\n\n";

	std::cout << "Select option 1 to register an start a game.  You have to chose this option before you can choose option 2 or 3."
		<< "This option will let you establish 1 or 2 players and set up your ships.  If you choose 1 player, the computer will "
		<< "assign play the second player for you.\n\n";

	std::cout << "Select option 2 to execute the turn of whichever player's turn it is.  A board will display where you will chose the row "
		<< "and column to fire at.  Then, pass the computer to the other player to take their turn.  No looking at the other player's board.\n\n";

	std::cout << "Select option 3 to display the game board of the current player's turn.\n\n";

	std::cout << "Select option 4 to display this help menu again.\n\n";

	std::cout << "Select option 5 to exit the game.\n\n";

}

std::vector<int> UserInterface::queryFirePoint()
{
	std::vector<int> retValue = std::vector<int>();
	bool runAgain = false;
	std::string userResponse = "";
	int returnResponse = 0;

	do
	{
		std::cout << "\nPlease enter a row value to attack: ";
		std::cin >> userResponse;

		if (userResponse < "0" || userResponse > "9")
		{
			runAgain = true;
			continue;
		}
		else
			runAgain = false;

	} while (runAgain);

	retValue.push_back(atoi(userResponse.c_str()));

	do
	{
		std::cout << "Please enter a column value to attack: ";
		std::cin >> userResponse;

		if (userResponse < "0" || userResponse > "9")
		{
			runAgain = true;
			continue;
		}
		else
			runAgain = false;

	} while (runAgain);

	retValue.push_back(atoi(userResponse.c_str()));

	return retValue;
}

void UserInterface::displayDuplicateShot()
{
	std::cout << "The target you selected has already been fired at.  Please try again!";
	return;
}

void UserInterface::displayShotResults(char result)
{
	std::string shipResult = "";

	switch (result)
	{
		case 'a':
		{
			std::cout << "\nYou hit the opponent's aircraft carrier!\n\n";
			break;
		}
		case 'b':
		{
			std::cout << "\nYou hit the opponent's battleship!\n\n";
			break;
		}
		case 's':
		{
			std::cout << "\nYou hit the opponent's submarine!\n\n";
			break;
		}
		case 'd':
		{
			std::cout << "\nYou hit the opponent's destroyer!\n\n";
			break;
		}
		case 'p':
		{
			std::cout << "\nYou hit the opponent's patrol boat!\n\n";
			break;
		}
		default:
		{
			std::cout << "\nThe shot was a miss!\n\n";
		}
	}

	return;
}

void UserInterface::displayShipStatus(char result)
{
	std::string shipResult = "";

	switch (result)
	{
		case 'a':
		{
				std::cout << "\nYou sank the opponent's aircraft carrier!\n\n";
				break;
		}
		case 'b':
		{
				std::cout << "\nYou sank the opponent's battleship!\n\n";
				break;
		}
		case 's':
		{
				std::cout << "\nYou sank the opponent's submarine!\n\n";
				break;
		}
		case 'd':
		{
				std::cout << "\nYou sank the opponent's destroyer!\n\n";
				break;
		}
		case 'p':
		{
				std::cout << "\nYou sank the opponent's patrol boat!\n\n";
				break;
		}
	}

	return;
}

void UserInterface::displayGameResults(int player)
{
	std::cout << "\nPlayer " << player << " has won the game!!\n\n";
	return;
}

void UserInterface::displayPlayerTurn(int player)
{
	std::cout << "\n******************************" << std::endl;
	std::cout << "It is player " << player << "'s turn..." << std::endl;
	std::cout << "******************************\n\n";
}

void UserInterface::invalidSpot()
{
    std::cout << "\nPlease enter a valid spot!\n";
}

void UserInterface::filledSpot()
{
    std::cout << "\nPlease select an empty spot!";
}
