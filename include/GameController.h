#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <vector>
#include <map>
#include <stack>
#include <utility>
#include "BoardGame.h"
#include "UserInterface.h"

class GameController
{
    public:
        GameController();
        void assignShips(int);
        void computerTurn();
        void displayGameBoard(int, bool, bool);
        void exitGame();
        void displayHelp();
        void init();
        void playGame(int&, bool&, bool&);
        void registerGame(bool&, bool&, int&);

    private:
        UserInterface display;
        BoardGame fleets;
        std::stack<std::pair<int,int>> dfs;
        std::map<std::pair<int,int>,std::pair<int,int>> visited;
};

#endif // GAMECONTROLLER_H
