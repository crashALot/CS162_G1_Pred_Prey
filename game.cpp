/********************************************************************* 
** Author:      Group 11
** Date:        07/29/18
** Description: The game.cpp file contains functions and implementations
*               of the Game class. The Game class is the main driving
                code behind much of the game's operation.
*********************************************************************/
#include "game.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>

/********************************************************************* 
** Description: Game::Game(int stepsIn)
*               Game class constructor with user inputs
*               The parameters correspond to user inputs unless user
*               has chosen default values
*********************************************************************/
Game::Game(int numRows, int numCols, int numAnts, int numDoods)
{

    critterBoard = new Critter**[numRows];
    for (int i=0; i<numRows; i++)
        critterBoard[i]= new Critter*[numCols];
    
    for (int i=0; i<numRows; i++)
    {
        for (int j=0; j<numCols; j++)
        {
            critterBoard[i][j]=new Critter();
        }
    }
    
    this -> numRows = numRows;
    this -> numCols = numCols;
    critterPop[Ants]=numAnts;
    critterPop[DoodleBugs]=numDoods;
    numSteps=0;
}
/********************************************************************* 
** Description: double Game::randomGenerator()
*               Generates a random value between 0 and 1 
*********************************************************************/
double Game::randomGenerator()
{
    return (((double)rand())/((double)RAND_MAX));
}


/********************************************************************* 
** Description: void Game::placeCrittersRandomly(char critterIn)
*               Initializes the game board by placing ants and 
*               doodleBugs at random locations
*********************************************************************/
void Game::placeCrittersRandomly(char critterIn)
{
    int critterNumber;
    
    if (critterIn=='a') // If ants this "critterNumber" will be used
        critterNumber=critterPop[Ants];
    if (critterIn=='d') // If doodleBugs this "critterNumber" will be used
        critterNumber=critterPop[DoodleBugs];
    
    int randomColumn;
    int columnsLeft=numCols;
    // Iterate through the rest of the critters left that need a spot
    for (int i=0; i<critterNumber; i++)
    {
        //Pick a random row to start
        int randomRow=randomGenerator()*numRows;
        // Count variable needed to reset to 0 for every critter
        int counts=0;

        //* We'll need to check how many of our column positions in the random row are open:
        //*   We'll go through the row and find each open column space, we'll save the open column
        //*   positions to a dynamic array for choosing later            
        int* openColPositsLarge = new int[columnsLeft];
        for (int j=0; j<columnsLeft; j++)
        {
            if (critterBoard[randomRow][j]->name()==' ')
            {
                openColPositsLarge[counts]=j;
                counts++;
            }
        }
        //Checks if there are available spots in the column
        if(counts > 0){       
        // Now we need to resize the array so we can randomly select a column
            int* openColPositsSmall = new int[counts];
        // We'll copy over the old larger array into the new smaller one
            for (int k=0; k<(counts); k++)
            {
                openColPositsSmall[k]=openColPositsLarge[k];
            }
        // Delete the old array
            delete [] openColPositsLarge;
        // Finally, we'll select the random column the ant will be placed
            randomColumn=openColPositsSmall[static_cast<int>(randomGenerator()*(counts))];
        // Delete the new array
            delete [] openColPositsSmall;
        // Now we can instantiate a new ant or doodleBug at a random row and column
            if (critterIn=='a')        
            {
                Critter* antPtr=new Ant(randomRow, randomColumn);
                delete critterBoard[randomRow][randomColumn];
                critterBoard[randomRow][randomColumn]=antPtr;
            }
            if (critterIn=='d')     
            {   
                Critter* doodlePtr=new Doodlebug(randomRow, randomColumn);
                delete critterBoard[randomRow][randomColumn];
                critterBoard[randomRow][randomColumn]=doodlePtr;
            }
        }
        else{
            delete [] openColPositsLarge;
            i--;
        }
    }
}

/********************************************************************* 
** Description: void Game::everythingMove()
*               Driver function responsible for moving Critters
*               according to their set rules
*********************************************************************/
void Game::everythingMove()
{
    Critter** doodleLocations=new Critter*[critterPop[DoodleBugs]]; // Stores the addresses of doodleBugs on critter Board
    int doodleCounts=0, antCounts=0; // Array length tracker for "doodleLocations" and "antLocations"
    
    // The below for-loop iterates through the game board and identifies where doodleBugs are located
    // It then stores those addresses in the "doodleLocations" array.
    for (int i=0; i<numRows; i++)
    {
        for (int j=0; j<numCols; j++)
        {
            if (critterBoard[i][j]->name()=='X')
            {
                doodleLocations[doodleCounts]=critterBoard[i][j];
                doodleCounts++;
            }
        }
    }
    
    // Go to each doodleBug object and call it's move function
    for (int i=0; i<critterPop[DoodleBugs]; i++)
    {
        doodleLocations[i]->move(critterPop, critterBoard, numRows, numCols);
    }

    // Delete the dynamic array
    delete [] doodleLocations;
  
    
    Critter** antLocations=new Critter*[critterPop[Ants]]; // Stores the addresses of ants on critter Board

    // The below for-loop iterates through the game board and identifies where ants are located
    // It then stores those addresses in the "antLocations" array.
    for (int i=0; i<numRows; i++)
    {
        for (int j=0; j<numCols; j++)
        {
            if (critterBoard[i][j]->name()=='O')
            {
                antLocations[antCounts]=critterBoard[i][j];
                antCounts++;
            }
        }
    }
    
    // Go to each ant object and call it's move function
    for (int i=0; i<critterPop[Ants]; i++)
    {
        antLocations[i]->move(critterPop, critterBoard, numRows, numCols);
    }
    
    // Delete the dynamic array
    delete [] antLocations;
        
}

/********************************************************************* 
** Description: void Game::reproductionFunction()
*               Driver function resposnible for adding new Critters
*               during the game
*********************************************************************/
void Game::reproductionFunction()
{
    Critter** doodleLocations=new Critter*[critterPop[DoodleBugs]];  // Stores the addresses of doodleBugs on critter Board
    int doodleCounts=0, antCounts=0; // Array length tracker for "doodleLocations" and "antLocations"
    
    // The below for-loop iterates through the game board and identifies where doodleBugs are located
    // It then stores those addresses in the "doodleLocations" array.
    for (int i=0; i<numRows; i++)
    {
        for (int j=0; j<numCols; j++)
        {
            if (critterBoard[i][j]->name()=='X')
            {
                doodleLocations[doodleCounts]=critterBoard[i][j];
                doodleCounts++;
            }
        }
    }
    
    // Since this function actively adds doodleBug objects, we must store the initial population size in 
    // a separate variable
    int initialDoodlePopulation=critterPop[DoodleBugs];
    
    // Go to each doodleBug object and call it's breed function to determine if it will add a new doodleBug
    for (int i=0; i<initialDoodlePopulation; i++)
    {
        doodleLocations[i]->breed(critterPop, critterBoard, numRows, numCols);
    }
  
    // Delete the dynamic array
    delete [] doodleLocations;
    
    Critter** antLocations=new Critter*[critterPop[Ants]]; // Stores the addresses of ants on critter Board
   
    // The below for-loop iterates through the game board and identifies where ants are located
    // It then stores those addresses in the "antLocations" array.
    for (int i=0; i<numRows; i++)
    {
        for (int j=0; j<numCols; j++)
        {
            if (critterBoard[i][j]->name()=='O')
            {
                antLocations[antCounts]=critterBoard[i][j];
                antCounts++;
            }
        }
    }

    // Since this function actively adds ant objects, we must store the initial population size in 
    // a separate variable
    int initialAntPopulation=critterPop[Ants];

    // Go to each ant object and call it's breed function to determine if it will add a new ant
    for (int i=0; i<initialAntPopulation; i++)
    {
        antLocations[i]->breed(critterPop, critterBoard, numRows, numCols);
    }
    
    // Delete the dynamic array   
    delete [] antLocations;    
}

/********************************************************************* 
** Description: void Game::doodleDeath()
*               Driver function responsible for deleting doodleBug class
*               objects during game
*********************************************************************/
void Game::doodleDeath()
{
    Critter** doodleLocations=new Critter*[critterPop[DoodleBugs]]; // Stores the addresses of doodleBugs on critter Board
    int doodleCounts=0; // Array length tracker for "doodleLocations"
    
    // The below for-loop iterates through the game board and identifies where doodleBugs are located
    // It then stores those addresses in the "doodleLocations" array.
    for (int i=0; i<numRows; i++)
    {
        for (int j=0; j<numCols; j++)
        {
            if (critterBoard[i][j]->name()=='X')
            {
                doodleLocations[doodleCounts]=critterBoard[i][j];
                doodleCounts++;
            }
        }
    }
    
    // Since this function actively removes doodleBug objects, we must store  the initial population size in 
    // a separate variable
    int initialDoodlePopulation=critterPop[DoodleBugs];
    
    // Go to each doodleBug object and call it's starve function to determine if it will be deleted
    for (int i=0; i<initialDoodlePopulation; i++)
    {
        doodleLocations[i]->starve(critterPop, critterBoard);
    }
  
    // Delete the dynamic array
    delete [] doodleLocations;
}

/********************************************************************* 
** Description: void Game::printBoard()
*               Ouputs game board to consol with associated Critters
*********************************************************************/
void Game::printBoard()
{
    
    std::cout << std::endl << "******* You have "<< numSteps << " steps remaining. *******" << std::endl <<std::endl;
    numSteps--;
    std::cout << "  ";
    for (int i=0; i<numCols; i++)
        std::cout << std::setw(2) << i+1  ;
    std::cout << std::endl;
    
    for (int i=0; i<numRows; i++)
    {
        std::cout << std::setw(2) << i+1 << " "  ;
        for (int j=0; j<numCols; j++)
        {
                std::cout<< critterBoard[i][j]->name();
                std::cout << " ";
        }
    std::cout << std::endl;
    }   
    std::cout << std::string(42, '-') << std::endl;        
}

/********************************************************************* 
** Description: Get and Set functions
*               Included below are the mutator and accessor functions
*               for the Game class. Allows user to interact with
*               Game class objects
*********************************************************************/
Critter* Game::getCritterBoard(int rowIn, int colIn)
{
    return critterBoard[rowIn][colIn];
}

void Game::setNumSteps(int stepsIn)
{
    numSteps=stepsIn;
}

int Game::getNumSteps()
{
    return numSteps;
}

/********************************************************************* 
** Description: Game::~Game()
*               Game class destructor
*********************************************************************/
Game::~Game()
{
    for (int i=0; i<numRows; i++)
    {
        for (int j=0; j<numCols; j++)
        {
         
            delete critterBoard[i][j];
        }
    }
    
    for (int i=0; i<numRows; i++)
    {
        delete [] critterBoard[i];
    }

    delete [] critterBoard;
}
