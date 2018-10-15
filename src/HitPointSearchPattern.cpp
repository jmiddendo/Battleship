#include "HitPointSearchPattern.h"

HitPointSearchPattern::HitPointSearchPattern()
{
    //ctor
}

void HitPointSearchPattern::addHit(std::pair<int,int> newPair)
{
    dfs.push(newPair);
}

std::stack<std::pair<int,int>> HitPointSearchPattern::getDfs()
{
    return dfs;
}

std::pair<int,int> HitPointSearchPattern::getNextShot(Board tempBoard)
{
    std::pair<int,int> returnValue, currentValue, checkValueOne, checkValueTwo, checkValueThree, checkValueFour;
    int boardSize = tempBoard.getSize();

    currentValue = dfs.top();

    checkValueOne.first = currentValue.first - 1;
    checkValueOne.second = currentValue.second;

    checkValueTwo.first = currentValue.first + 1;
    checkValueTwo.second = currentValue.second;

    checkValueThree.first = currentValue.first;
    checkValueThree.second = currentValue.second - 1;

    checkValueFour.first = currentValue.first;
    checkValueFour.second = currentValue.second + 1;

    if (checkValueOne.first >= 0 && visited.count(checkValueOne) == 0)
    {
        return checkValueOne;
    }

    if (checkValueTwo.first < boardSize && visited.count(checkValueTwo) == 0)
        return checkValueOne;

    if (checkValueThree.second >= 0 && visited.count(checkValueThree) == 0)
        return checkValueThree;

    if (checkValueFour.second < boardSize && visited.count(checkValueFour) == 0)
        return checkValueOne;

    dfs.pop();

    return returnValue;
}

int HitPointSearchPattern::getSize()
{
    return dfs.size();
}

std::map<std::pair<int,int>,std::pair<int,int>> HitPointSearchPattern::getVisited()
{
    return visited;
}

void HitPointSearchPattern::setDfs(std::stack<std::pair<int,int>> newDfs)
{
    dfs = newDfs;
}

void HitPointSearchPattern::setVisited(std::map<std::pair<int,int>,std::pair<int,int>> newVisited)
{
    visited = newVisited;
}

void HitPointSearchPattern::updateVisited(std::pair<int,int> firedPair,std::pair<int,int> previousPair)
{
    visited.insert({firedPair,previousPair});
}
