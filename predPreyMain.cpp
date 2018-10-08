/********************************************************************* 
** Author:      Group 11
** Date:        07/29/18
** Description: This program uses cellular automata to create a 2D 
*               predator–prey simulation in the program.  The preys 
*               are ants and the predators are doodlebugs.
*********************************************************************/
#include "game.hpp"
#include "gameMenu.hpp"
#include <iostream>
#include <cstdlib> 
#include <ctime>

void gameLoop();
void exitLoop();

int main()
{
    srand(time(NULL)); // Create seed for random function
    startMenu();
    return 0;
}