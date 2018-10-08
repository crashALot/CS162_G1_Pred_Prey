/********************************************************************* 
** Author:      Group 11
** Date:        07/29/18
** Description: The gameMenu.hpp file contains the interface required
*               to use gameMenu functions. Linked with gameMenu.cpp
*********************************************************************/
#ifndef GAMEMENU_HPP
#define GAMEMENU_HPP
#include "menuValidation.hpp"
#include "game.hpp"

void startMenu();
void startTheGame();
void playTheGame(Game*, int);
void endMenu(Game*);
void exitMenu();

#endif