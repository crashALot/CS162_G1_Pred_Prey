/********************************************************************* 
** Author:      Group 11
** Date:        07/29/18
** Description: The gameMenu.cpp file contains the consol interface
*               between code and the user.
*********************************************************************/
#include "gameMenu.hpp"
#include <iostream>

/********************************************************************* 
** Description: void startMenu()
*               The first menu the user will see is this one
*********************************************************************/
void startMenu()
{
    int userSelection; 
    std::cout << "*********** Welcome to the game of Predator and Prey! ***********" << std::endl << std::endl;
    std::cout << "      Please select from one of the options below:" << std::endl;
    std::cout << "          1. Play a game of Predator and Prey" << std::endl;
    std::cout << "           2. Exit the program" << std::endl;
    userSelection=mainMenuValidate();
    switch (userSelection)
    {
        case 1:
        startTheGame();
        break;
        
        case 2:
        exitMenu();
        break;
    }
}

/********************************************************************* 
** Description: void startTheGame()
*               Prompts the suer to enter important game information
*               before the start of the game.
*********************************************************************/
void startTheGame()
{
    bool quit = false;
    int userSelection;
    int numSteps;
    int numRows, numCols; //for user entered data
    int numAnts, numDoods; //for user entered data
    char ant='a', doodle='d';
    std::cout << "****************** Welcome to the Game Menu! ******************" << std::endl << std::endl;
    std::cout << "    Would you like to use default settings, or enter your own data (EC)" << std::endl;

    std::cout << "    1. Use default settings " << std::endl;
    std::cout << "    2. Enter your own data" << std::endl;
    userSelection=mainMenuValidate();
    std::cout << "    How many steps would you like the Critters to take?" << std::endl;   
    numSteps=gameMenuValidate();
    //User will determine the size of the board and the number of each critter
    if(userSelection == 2){
       std::cout << "    How many rows should the grid have?" << std::endl;
       numRows = gameMenuValidate();

       std::cout << "    How many columns should the grid have?" << std::endl;
       numCols = gameMenuValidate();

       if(numCols == 1 && numRows == 1){ //quits program for a 1x1 board
           quit = true;
           std::cout << "Sorry but a 1x1 board doesn't make for a very interesting program. Try again with different data" << std::endl;
       }
 
       else{
          std::cout << "    How many Ants should be placed on the board?" << std::endl;
          numAnts = gameMenuValidate();
          //max number of ants is 1 less than the max amount of critters
          while(numAnts > numRows*numCols - 1){
             std::cout << "    You entered too many Ants to fit on the board! Please re-enter number of Ants" << std::endl;
             numAnts = gameMenuValidate();
       }
          std::cout << "    How many Doodlebugs should be placed on the board?" << std::endl; 
          numDoods = gameMenuValidate();
          //Number of doodlebugs + ants can't exceed positions on boa
          while(numDoods > numRows*numCols - numAnts){
             std::cout << "    You entered too many Doodlebugs to fit on the board! Please re-enter number of Doodlebugs" << std::endl;
             numDoods = gameMenuValidate();
          }
       }
    }
    else{ //default conditions
           numRows = numCols = 20;
           numDoods = 5;
           numAnts = 100;
    }
    if(!quit){
       Game newGame(numRows, numCols, numAnts, numDoods);
       newGame.setNumSteps(numSteps);
       //newGame.placeInitialCritter();
       newGame.placeCrittersRandomly(ant);
       newGame.placeCrittersRandomly(doodle);
       playTheGame(&newGame, numSteps); 
   }
}

/********************************************************************* 
** Description: void playTheGame(Game* newGame,int numSteps)
*               Iterates a specific number of user requested times
*               through the predator-prey process 
*********************************************************************/
void playTheGame(Game* newGame,int numSteps)
{
    newGame->setNumSteps(numSteps);
    newGame->printBoard();
    for (int i=0; i<numSteps-1; i++)
    {
    newGame->everythingMove();
    newGame->reproductionFunction();
    newGame->doodleDeath();
    newGame->printBoard();
    }
    endMenu(newGame);    
}

/********************************************************************* 
** Description: void endMenu(Game* newGame)
*               Prompts the user to continue the program or exit
*********************************************************************/
void endMenu(Game* newGame)
{
    int userSelection, numSteps;
    std::cout << std::endl << "******* Congratuations! You've reached the end of the game *******" << std::endl << std::endl;
    std::cout << "      Please select from one of the options below:" << std::endl;
    std::cout << "          1. Continue playing where you left off" << std::endl;
    std::cout << "           2. Exit the program" << std::endl;
    userSelection=mainMenuValidate();
    switch (userSelection)
    {
        case 1:
        std::cout << "****************** You've chosen to continue! ******************" << std::endl << std::endl;
        std::cout << "    How many more steps would you like the Critters to take?" << std::endl;
        numSteps=gameMenuValidate();
        playTheGame(newGame, numSteps);
        break;
        
        case 2:
        exitMenu();
        break;
    }
}

/********************************************************************* 
** Description: void exitMenu()
*               Exit display used when leaving the program
*********************************************************************/
void exitMenu()
{
    std::cout << std::endl << "************ Thank you for playing! See you again soon! ************" << std::endl << std::endl;
}
