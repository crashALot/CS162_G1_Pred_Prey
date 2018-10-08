/********************************************************************* 
** Author:      Group 11
** Date:        07/29/18
** Description: The doodleBug.cpp file contains functions and implementations
*               of the doodleBug class. Doodlebug class is a derived class
*               of Critter class.
*********************************************************************/
#include "doodleBug.hpp"
#include "game.hpp"
#include <iostream>
#include <cmath>

/********************************************************************* 
** Description: Doodlebug::Doodlebug()
*               Default Doodlebug class constructor
*********************************************************************/
Doodlebug::Doodlebug()
{
    setRow(-1);
    setCol(-1);
    setStep(0);
    daysSinceLastMeal=0;
}

/********************************************************************* 
** Description: Doodlebug::Doodlebug(int rowIn, int colIn)
*               Doodlebug class constructor with user input.
*********************************************************************/
Doodlebug::Doodlebug(int rowIn, int colIn)
{
    setRow(rowIn);
    setCol(colIn);
    setStep(0);
    daysSinceLastMeal=0;
}

/********************************************************************* 
** Description: void Doodlebug::starve(int* critterPop, Critter*** critterBoard)
*               Deletes doodleBug Class object after a determined
*               number of steps.
*********************************************************************/
void Doodlebug::starve(int* critterPop, Critter*** critterBoard)
{
    // If variable "daysSinceLstMeal" is divisible by 3, a the doodleBug is deleted
    if (this->daysSinceLastMeal>=3)
    {
        // We'll be deleting the object but need it's location reference
        int rows=this->getRow();
        int columns=this->getCol();
        // Delete doodleBug object
        delete critterBoard[this->getRow()][this->getCol()];
        // Decrement doodleBug population
        critterPop[DoodleBugs]--;
        // Instantiate new critter in its place (using previously stored location reference)
        critterBoard[rows][columns]=new Critter(rows, columns);
    }
}

/********************************************************************* 
** Description: void Doodlebug::breed(int* critterPop, Critter*** critterBoard)
*               Creates a doodleBug class object after a determined 
*               number of steps.
*********************************************************************/
void Doodlebug::breed(int* critterPop, Critter*** critterBoard, int rows, int cols)
{
    // If variable "step" is divisible by 8, a new doodleBug is born
    if (!((this->getStep())%8))
    {
        Critter::breed(critterPop, critterBoard, rows, cols);
    }
}

/********************************************************************* 
** Description: void Doodlebug::move(int* critterPop, Critter*** critterBoard)
*               Defines how and when the Doodlebug class object moves
*               and eats. Determines if any ants are near the doodleBug
*               and moves to randomly eat one. Otherwise moves according
*               in accordance with default rules.
*********************************************************************/
void Doodlebug::move(int* critterPop, Critter*** critterBoard, int rows, int cols)
{
    int column, row;
    Critter** critterPtr = new Critter*[9]; // the "critterPtr" array stores the addresses of any ants immediately around
                                            // the doodleBug
    int arrayCount=0; // Variable "arrayCount" is used as an array length tracker
    
    // First we need to figure out if there are any ants surrounding the doodle bug
    // We'll start by storing the current critter's location for reference
    column=this->getCol();
    row=this->getRow();
    
    // Next we'll go through each square sourrounding the doodleBug and identify any ants 
    // We'll save any ants we find to an array of ant addresses 
    for (int i=-1; i<2; i++)
    {
        for (int j=-1; j<2; j++)
        {
            // Using an if statement in the for-loop we'll omit searching for ants outside the edges of the board
            if (row+i<rows && row+i>=0 && column+j<cols && column+j>=0)
            {
                // Using another if statement we identify and add any ants to the "critterPtr" array 
                if (critterBoard[row+i][column+j]->name()=='O' && abs((i+j) % 2) == 1)
                {
                    critterPtr[arrayCount]=critterBoard[row+i][column+j];
                    arrayCount++;
                }
            }
        }
    }
    
    // Next we'll select an ant address from "critterPtr" array, as long as it contains any ants at all!
    if (arrayCount>0)
    {
        // Choose the random ant from the array of ants
        int antSelection=(randomGenerator()*arrayCount);
        // The ant we select will in fact be a pointer to said ant, so we need to store the value in a new pointer
        Critter* finalAntSelection;
        // Select a position in the "critterPtr" array to find an ant we'll have the doodleBug "eat"
        finalAntSelection=critterPtr[antSelection];
        // Delete the "critterPtr" array
        delete [] critterPtr;
        // Knowing which ant will be eaten means we can delete it from the critterBoard
        int victimAntCol=finalAntSelection->getCol();
        int victimAntRow=finalAntSelection->getRow();
        // The Ant gets eaten!
        delete critterBoard[victimAntRow][victimAntCol];
        // With the ant deleted we can move the current doodlebug pointer to the now deleted ant location
        critterBoard[victimAntRow][victimAntCol]=critterBoard[row][column];
        // Update the doodleBug's new location as well (it's row and column variables need manual updating)
        this->setRow(victimAntRow);
        this->setCol(victimAntCol);
        // And finally instantiate a new base critter at the old doodlebug location
        critterBoard[row][column]=new Critter(row, column);
        // Since we ate an ant, we need to decrement the ant population
        critterPop[Ants]--;
        // Increment the number of steps this doodleBug has taken
        this->setStep();
        // Reset the timer since the doodle bug ate an ant
        daysSinceLastMeal=0;
    }
    else 
    {
        // This code runs when no suitable ant is found around the doodlebug
        delete [] critterPtr;
        // The doodle bug has starved another turn, we increment the days since last meal
        daysSinceLastMeal++;
        // Now we move the doodlebug according to the default rules
        Critter::move(critterPop, critterBoard, rows, cols);
    }
        
}

/********************************************************************* 
** Description: char Doodlebug::name()
*               Returns the Doodlebug class specifier when called
*********************************************************************/
char Doodlebug::name()
{
    return 'X';
}

/********************************************************************* 
** Description: Doodlebug::~Doodlebug()
*               Doodlebug class destructor
*********************************************************************/
Doodlebug::~Doodlebug()
{
   //std::cout << "Doodlebug Destructor" << std::endl; 
}
