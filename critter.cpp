/********************************************************************* 
** Author:      Group 11
** Date:        07/29/18
** Description: The critter.cpp file contains functions and implementations
*               of the Critter class. Critter class is a base class
*               for Ant and Doodlebug classes
*********************************************************************/
#include "critter.hpp"
#include "doodleBug.hpp"
#include "ant.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

/********************************************************************* 
** Description: Critter::Critter()
*               Default Critter class constructor
*********************************************************************/
Critter::Critter()
{
    row=-100;
    col=-100;
    step=0;
}

/********************************************************************* 
** Description: Critter::Critter(int rowIn, int colIn)
*               Critter constructor with user input. Used mid-game
*               when a critter instance is generated (e.g. critter
*               being born)
*********************************************************************/
Critter::Critter(int rowIn, int colIn)
{
    row=rowIn;
    col=colIn;
    step=0;
}

/********************************************************************* 
** Description: void Critter::starve(int* critterPop, Critter*** critterBoard)
*               Virtual function. Determines if affected critter will
*               be eliminated from the board of critters. Specfically
*               for doodle bug objects.
*********************************************************************/
void Critter::starve(int* critterPop, Critter*** critterBoard)
{
    
}

/********************************************************************* 
** Description: void Critter::breed(int *critterPop, Critter*** critterBoard)
*               Virtual function. Default breed algorithm. Determines
*               open position for critter to be born and places 
*               new critter object in position
*               Rows and Cols correspond to the dimensions of the board
*********************************************************************/
void Critter::breed(int *critterPop, Critter*** critterBoard, int rows, int cols)
{
    int counts=0; 
    Critter** openSpacesForaBaby=new Critter*[4];   // Holds Critter addresses found in North, East, South, and West positions around
                                                    // current critter
    
    // The next 4 if-statements determine if the cardinal directions around our current critter are open.
    // If they are, the address of the critter is saved to an array for possibly be chosen later
    if (this->getRow()-1>=0 && critterBoard[this->getRow()-1][this->getCol()]->name()==' ') // Check North
    { 
        openSpacesForaBaby[counts]=critterBoard[this->getRow()-1][this->getCol()];
        openSpacesForaBaby[counts]->setRow(this->getRow()-1);
        openSpacesForaBaby[counts]->setCol(this->getCol());
        counts++; // Variable "counts" is used as an array position tracker for "openSpacesForaBaby"
    }
    if (this->getCol()+1<cols && critterBoard[this->getRow()][this->getCol()+1]->name()==' ') // Check East
    {
        openSpacesForaBaby[counts]=critterBoard[this->getRow()][this->getCol()+1];
        openSpacesForaBaby[counts]->setRow(this->getRow());
        openSpacesForaBaby[counts]->setCol(this->getCol()+1);
        counts++;
    }
    if (this->getRow()+1<rows && critterBoard[this->getRow()+1][this->getCol()]->name()==' ') // Check South
    {
        openSpacesForaBaby[counts]=critterBoard[this->getRow()+1][this->getCol()];
        openSpacesForaBaby[counts]->setRow(this->getRow()+1);
        openSpacesForaBaby[counts]->setCol(this->getCol());
        counts++;
    }
    if (this->getCol()-1>=0 && critterBoard[this->getRow()][this->getCol()-1]->name()==' ') // Check West
    {
        openSpacesForaBaby[counts]=critterBoard[this->getRow()][this->getCol()-1];
        openSpacesForaBaby[counts]->setRow(this->getRow());
        openSpacesForaBaby[counts]->setCol(this->getCol()-1);
        counts++;
    }
    
    // If our array length tracker counted any open positions at all (counts>0) then the code below will execute
    // Make note that even if the array "openSpacesForaBaby" was not filled entirely, the random selection of an
    // open position in the array is limited by the "counts" variable
    if (counts)
    {
        // Randomly select an in the "openSpacesForaBaby" array
        int goingTo=(randomGenerator()*(counts-1));
        // The value in the array will be a pointer to a Critter, so we need to initialize a new variable to store said value
        Critter* bornTo = openSpacesForaBaby[goingTo];
        int newRow=bornTo->getRow();
        int newCol=bornTo->getCol();
        bornTo=NULL;
        // Delete the original critter from the position where our new Critter will be 
        delete critterBoard[newRow][newCol];
        // Identify which critter is producing and place the new critter in our predetermined position 
        if (this->name()=='X')
        {
            critterBoard[newRow][newCol]=new Doodlebug(newRow,newCol);
            //increment the respective critter population
            critterPop[DoodleBugs]++;

        }
        if (this->name()=='O')
        {
            critterBoard[newRow][newCol]=new Ant(newRow,newCol);
            //increment the respective critter population
            critterPop[Ants]++;
        }
    }
    // Delete the "openSpacesForaBaby" array
    delete [] openSpacesForaBaby;
}

/********************************************************************* 
** Description: void Critter::move(int* critterPop, Critter*** critterBoard)
*               Virtual function. Determines default Critter movement.
*               Increments critter steps when completed.
*               Rows and Cols correspond to the dimensions of the board
*********************************************************************/
void Critter::move(int* critterPop, Critter*** critterBoard, int rows, int cols)
{     

    int go=0; // Sentinel value used in switch statement
    int victimOpenCol; // Column the critter will be moving to
    int victimOpenRow; // Row the critter will be moving to
    
    // First we need to figure out which direction the critter will move
    int whereTo=(randomGenerator()*4);

    // Now we'll check the random cardinal direction and identify if an edge or any other critters exists
    // If an edge or critter exists the current critter will not move
    switch (whereTo)
    {
        case 0: // North
            if (this->getRow()-1>=0 && critterBoard[this->getRow()-1][this->getCol()]->name()==' ')  
            {
                go=1; // Using "go" as a sentinel variable, if the cardinal direction is open and not beyond the edge
                victimOpenCol=this->getCol();
                victimOpenRow=this->getRow()-1;
            }

        break;

        case 1: // East
            if (this->getCol()+1<cols && critterBoard[this->getRow()][this->getCol()+1]->name()==' ') 
            {
                go=1;
                victimOpenCol=this->getCol()+1;
                victimOpenRow=this->getRow();
            }

        break;
        
        case 2: // South
            if (this->getRow()+1<rows && critterBoard[this->getRow()+1][this->getCol()]->name()==' ')
            {
                go=1;
                victimOpenCol=this->getCol();
                victimOpenRow=this->getRow()+1;
            }
            
        break;
        
        case 3: // West
            if (col-1>=0 && critterBoard[this->getRow()][this->getCol()-1]->name()==' ')
            {
                go=1;
                victimOpenCol=this->getCol()-1;
                victimOpenRow=this->getRow();
            }
        break;
    }
    
    // If the randomly selected direction chosen has a critter in it or is beyond the edge this code will NOT run
    if (go) 
    {
        // We now know which opening the critter will move to, the critter at the new position must be deleted from the critterBoard

        delete critterBoard[victimOpenRow][victimOpenCol];
        // With the critter in our open spot deleted we can move the current critter pointer to the now deleted critter location
        critterBoard[victimOpenRow][victimOpenCol]=critterBoard[row][col];
        // And finally instantiate a new base critter at the old critter location
        critterBoard[this->getRow()][this->getCol()]=new Critter(row, col);
        // Lastly, we store the column and row position for the new critter
        this->setRow(victimOpenRow);
        this->setCol(victimOpenCol);
    }
    // The move function completed, we increment the steps taken by the critter
    step++;
    
}

/********************************************************************* 
** Description: double Critter::randomGenerator()
*               Generates a random value between 0 and 1 
*********************************************************************/
double Critter::randomGenerator()
{
    return (static_cast<double>(rand())/static_cast<double>(RAND_MAX));
}

/********************************************************************* 
** Description: char Critter::name()
*               Virtual function. Returns character value representing
*               critter object type (critter, ant, doodlebug)
*********************************************************************/
char Critter::name()
{
    return ' ';
}

/********************************************************************* 
** Description: Get and Set functions
*               Included below are the mutator and accessor functions
*               for the Critter class. Allows user to interact with
*               Critter class objects
*********************************************************************/
void Critter::setLocation(int rowIn, int colIn)
{
    row=rowIn;
    col=colIn;
}

int Critter::getRow()
{
    return row;
}

int Critter::getCol()
{
    return col;
}

void Critter::setRow(int rowIn)
{
    row=rowIn;
}

void Critter::setCol(int colIn)
{
    col=colIn;
}

int Critter::getStep()
{
    return step;
}

void Critter::setStep()
{
    step++;
}

void Critter::setStep(int stepIn)
{
    step=stepIn;
}

/********************************************************************* 
** Description: Critter::~Critter()
*               Critter class destroyer
*********************************************************************/
Critter::~Critter()
{
       //std::cout << "Critter Destructor" << std::endl; 
}
