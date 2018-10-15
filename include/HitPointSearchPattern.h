#ifndef HITPOINTSEARCHPATTERN_H
#define HITPOINTSEARCHPATTERN_H
#include <stack>
#include <map>
#include <utility>
#include "Board.h"

class HitPointSearchPattern
{
    public:
        HitPointSearchPattern();
        void addHit(std::pair<int,int>);
        std::stack<std::pair<int,int>>getDfs();
        std::pair<int,int> getNextShot(Board);
        int getSize();
        std::map<std::pair<int,int>,std::pair<int,int>> getVisited();
        void setDfs(std::stack<std::pair<int,int>>);
        void setVisited(std::map<std::pair<int,int>,std::pair<int,int>>);
        void updateVisited(std::pair<int,int>,std::pair<int,int>);

    private:
        std::stack<std::pair<int,int>> dfs;
        std::map<std::pair<int,int>,std::pair<int,int>> visited;
};

#endif // HITPOINTSEARCHPATTERN_H
