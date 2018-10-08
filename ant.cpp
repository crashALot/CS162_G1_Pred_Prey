/********************************************************************* 
** Author:      Group 11
** Date:        07/29/18
** Description: The ant.cpp file contains functions and implementations
*               of the Ant class. Ant class is a derived class
*               of Critter class.
*********************************************************************/
#include "ant.hpp"
#include <iostream>

/********************************************************************* 
** Description: Ant::Ant()
*               Default Ant class constructor
*********************************************************************/
Ant::Ant()
{
    setRow(-1);
    setCol(-1);
    setStep(0);
}

/********************************************************************* 
** Description: Ant::Ant(int rowIn, int colIn)
*               Ant class constructor with user specified inputs.
*********************************************************************/
Ant::Ant(int rowIn, int colIn)
{
    setRow(rowIn);
    setCol(colIn);
    setStep(0);
}

/********************************************************************* 
** Description: void Ant::breed(int * critterPop, Critter*** critterBoard)
*               Creates an Ant class object after a determined 
*               number of steps.
*********************************************************************/
void Ant::breed(int * critterPop, Critter*** critterBoard, int rows, int cols)
{
        // If variable "step" is divisible by 3, a new ant is born
        if (!((this->getStep())%3))
        {
            Critter::breed(critterPop, critterBoard, rows, cols);
        }
}

/********************************************************************* 
** Description: void Ant::move(int* critterPop, Critter*** critterBoard)
*               Enables the Ant class object to move according to set
*               rules. Ants will move in the cardinal directions only
*               unless all positions surrounding the Ant are full
*********************************************************************/
void Ant::move(int* critterPop, Critter*** critterBoard, int rows, int cols)
{
    Critter::move(critterPop, critterBoard, rows, cols);
}

/********************************************************************* 
** Description: char Ant::name()
*               Returns the Ant class specifier when called
*********************************************************************/
char Ant::name()
{
    return 'O';
}

/********************************************************************* 
** Description: Ant::~Ant()
*               Ant class destructor
*********************************************************************/
Ant::~Ant()
{
      // std::cout << "Ant Destructor" << std::endl; 
}
