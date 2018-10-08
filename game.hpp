/********************************************************************* 
** Author:      Group 11
** Date:        07/29/18
** Description: The game.hpp file contains the interface required
*               to use Game class objects. Linked with game.cpp
*********************************************************************/
#ifndef GAME_HPP
#define GAME_HPP
#include "critter.hpp"
#include "ant.hpp"
#include "doodleBug.hpp"

enum critterType {Ants, DoodleBugs};

class Game
{
private:

    Critter*** critterBoard;
    int critterPop[2];
    int numRows;
    int numCols;
    int numSteps;

public:
    Game(int, int, int, int);
    double randomGenerator();
    //void placeInitialCritter();
    void placeCrittersRandomly(char);
    void everythingMove();
    void reproductionFunction();
    void doodleDeath();
    Critter* getCritterBoard(int, int);
    void setNumSteps(int);
    int getNumSteps();
    void printBoard();
    ~Game();
};

#endif
