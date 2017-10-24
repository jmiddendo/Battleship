#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <string>
#include <vector>


class UserInterface
{
public:
	UserInterface();
	UserInterface(int);
	int displayMainMenu();
	void displayStartError();
	void displayExit();
	void displayComputerAssignment();
	void displayHelp();
	void insertBreak();
	int getMainMenuSize();
	void setMainMenuSize(int);
	int queryPlayerNumber();
	std::string queryRestart();
	void displayBoard(std::vector<std::string>&);
	void displayBoard(std::string, std::string);
	std::vector<int> queryEntry(std::string);
	int queryEntry(std::vector<int> possibleEndPoints);
	std::vector<int> queryFirePoint();
	void displayDuplicateShot();
	void displayShotResults(char);
	void displayShipStatus(char);
	void displayGameResults(int);
	void displayPlayerTurn(int);

private:
	int mainMenuSize;
};

#endif