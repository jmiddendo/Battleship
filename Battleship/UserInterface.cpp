#include "UserInterface.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

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
	string userChoice = "0";

	do
	{
		cout << "        Battleship" << endl
			 << "---------------------------" << endl
			 << "(1) Start Game" << endl
			 << "(2) Play Turn" << endl
			 << "(3) Display Game Board" << endl
			 << "(4) Display Help" << endl
			 << "(5) Exit Game" << endl
			 << "What would you like to do: ";
		cin >> userChoice; 

		if (userChoice < "1" || userChoice > "5")
		{
			cout << "Please enter a valid number!\n\n";
			runAgain = true;
		}
		else
			runAgain = false;

	} while (runAgain);

	return atoi(userChoice.c_str());
}

void UserInterface::insertBreak()
{
	cout << '\n';
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
	string retValue = "0";
	bool runAgain = true;

	do
	{
	cout << "Is there 1 playar or 2 players (1 or 2)? ";
	cin >> retValue;

	if (retValue < "1" || retValue > "2")
	{
		cout << "\nPease enter a 1 or 2\n\n";
		runAgain = true;
	}
	else
		runAgain = false;

	} while (runAgain);

	return atoi(retValue.c_str());
}

string UserInterface::queryRestart()
{
	string retValue = "";
	bool runAgain = true;

	do
	{
		cout << "There is already a game in progress.  Do you want to start a new game (y or n): ";
		cin >> retValue;

		if(retValue.size() != 1)
		{
			cout << "Please enter only y or n.\n";
			runAgain = true;
		}
		else if (tolower(retValue[0]) != 'y' && tolower(retValue[0]) != 'n')
		{
			cout << "Please enter a valid value (y or n).\n";
			runAgain = true;
		}
		else
			runAgain = false;

	} while (runAgain);

	return retValue;
}

void UserInterface::displayBoard(vector<string>& displayString)
{
	displayBoard("\nEnemy Board\n", displayString[0]);	 
	displayBoard("\nYour Board\n", displayString[1]);

	return;
}

void UserInterface::displayBoard(string title, string readString)
{
	cout << title;
	for (int i = 0; i < readString.size(); i++)
	{
		cout << readString[i] << ' ';
		if(i % 10 == 9)
			cout << '\n';
	}
}

vector<int> UserInterface::queryEntry(string readLine)
{
	vector<int> retValue = vector<int>();
	string x1 = "0", y1 = "0", x2 = "0", y2 = "0";
	bool runAgain = true;

	displayBoard("\nChose points\n", readLine);

	do
	{
		cout << "\nPlease enter an x coordinate (0 to 9): ";
		cin >> x1;

		if (x1 < "0" || x1 > "9")
		{
			cout << "Please enter a valid coordinate.  Try again!";
			runAgain = true;
		}
		else
			runAgain = false;
	} while(runAgain);

	retValue.push_back(atoi(x1.c_str()));

	do
	{
		cout << "Please enter a y coordinate (0 to 9): ";
		cin >> y1;

		if (y1 < "0" || y1 > "9")
		{
			cout << "Please enter a valid coordinate.  Try again!";
			runAgain = true;
		}
		else
			runAgain = false;

	} while (runAgain);

	retValue.push_back(atoi(y1.c_str()));

	return retValue;
}

int UserInterface::queryEntry(vector<int> possibleEndPoints)
{
	bool runAgain = true;
	string retValue = "0", passValue = "0";
	vector<string> secondLocation = vector<string>();

	for (int i = 0; i < possibleEndPoints.size(); i += 2)
	{
		passValue = (to_string((possibleEndPoints[i] * 10) + possibleEndPoints[i + 1]));
		if (passValue.length() == 1)
			passValue = "0" + passValue;
		secondLocation.push_back(passValue);
	}

	do
	{
		cout << "\nPlease chose a second coordinate ("; 
		for (int i = 0; i < secondLocation.size(); i++)
			if (i == secondLocation.size() - 1)
				cout << secondLocation[i];
			else
				cout << secondLocation[i] << " or "; 
		cout << "): ";
		cin >> retValue;

		for (int i = 0; i < retValue.size(); i++)
			if (retValue[i] < '0' || retValue[i] > '9')
			{
				cout << "Please enter a valid coordinate.  Try again!";
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
				cout << "Please enter a valid coordinate.  Try again!";
			}
			

	} while (runAgain);


	return atoi(retValue.c_str());	
}

void UserInterface::displayStartError()
{
	cout << "\nPlease start a game to continue! Try again!\n";
	return;
}

void UserInterface::displayExit()
{
	cout << "\nThank you for playing.  Have a pleasant day!" << endl << endl;
	return;
}

void UserInterface::displayComputerAssignment()
{
	cout << "\nPlease wait! Assigning computer ships...\n";
	return;
}

void UserInterface::displayHelp()
{
	cout << "\nWelcome to the battleship game!\n\n";

	cout << "Select option 1 to register an start a game.  You have to chose this option before you can choose option 2 or 3."
		<< "This option will let you establish 1 or 2 players and set up your ships.  If you choose 1 player, the computer will "
		<< "assign play the second player for you.\n\n";

	cout << "Select option 2 to execute the turn of whichever player's turn it is.  A board will display where you will chose the row "
		<< "and column to fire at.  Then, pass the computer to the other player to take their turn.  No looking at the other player's board.\n\n";

	cout << "Select option 3 to display the game board of the current player's turn.\n\n";

	cout << "Select option 4 to display this help menu again.\n\n";

	cout << "Select option 5 to exit the game.\n\n";

}

vector<int> UserInterface::queryFirePoint()
{
	vector<int> retValue = vector<int>();
	bool runAgain = false;
	string userResponse = "";
	int returnResponse = 0;

	do
	{
		cout << "\nPlease enter a row value to attack: ";
		cin >> userResponse;

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
		cout << "Please enter a column value to attack: ";
		cin >> userResponse;

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
	cout << "The target you selected has already been fired at.  Please try again!";
	return;
}

void UserInterface::displayShotResults(char result)
{
	string shipResult = "";

	switch (result)
	{
		case 'a':
		{
			cout << "\nYou hit the oppenent's aircraft carrier!\n\n";
			break;
		}
		case 'b':
		{
			cout << "\nYou hit the oppenent's battleship!\n\n";
			break;
		}
		case 's':
		{
			cout << "\nYou hit the oppenent's submarine!\n\n";
			break;
		}
		case 'd':
		{
			cout << "\nYou hit the oppenent's destroyer!\n\n";
			break;
		}
		case 'p':
		{
			cout << "\nYou hit the oppenent's patrol boat!\n\n";
			break;
		}
		default:
		{
			cout << "\nThe shot was a miss!\n\n";
		}
	}

	return;
}

void UserInterface::displayShipStatus(char result)
{
	string shipResult = "";

	switch (result)
	{
		case 'a':
		{
				cout << "\nYou sank the oppenent's aircraft carrier!\n\n";
				break;
		}
		case 'b':
		{
				cout << "\nYou sank the oppenent's battleship!\n\n";
				break;
		}
		case 's':
		{
				cout << "\nYou sank the oppenent's submarine!\n\n";
				break;
		}
		case 'd':
		{
				cout << "\nYou sank the oppenent's destroyer!\n\n";
				break;
		}
		case 'p':
		{
				cout << "\nYou sank the oppenent's patrol boat!\n\n";
				break;
		}
	}

	return;
}

void UserInterface::displayGameResults(int player)
{
	cout << "\nPlayer " << player << " has won the game!!\n\n";
	return;
}

void UserInterface::displayPlayerTurn(int player)
{
	cout << "\n******************************" << endl;
	cout << "It is player " << player << "'s turn..." << endl;
	cout << "******************************\n\n";
}