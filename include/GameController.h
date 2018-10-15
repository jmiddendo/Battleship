#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <iostream>
#include <vector>
#include "BoardGame.h"
#include "UserInterface.h"

class GameController
{
    public:
        GameController();
        void assignShips(int);
        void displayGameBoard(int, bool, bool);
        void exitGame();
        void displayHelp();
        void init();
        void playGame(int&, bool&, bool&);
        void registerGame(bool&, bool&, int&);

    private:
        UserInterface display;
        BoardGame fleets;
};

#endif // GAMECONTROLLER_H
