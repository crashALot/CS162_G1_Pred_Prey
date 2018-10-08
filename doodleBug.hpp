/********************************************************************* 
** Author:      Group 11
** Date:        07/29/18
** Description: The doodleBug.hpp file contains the interface required
*               to use Doodlebug class objects. Linked with doodleBug.cpp
*********************************************************************/
#ifndef DOODLEBUG_HPP
#define DOODLEBUG_HPP
#include "critter.hpp"
#include "game.hpp"

class Doodlebug : public Critter
{
private:

    int daysSinceLastMeal;

public:

    Doodlebug();
    Doodlebug(int, int);
    void starve(int*, Critter***);
    void breed(int*, Critter***, int, int);
    void move(int*, Critter***, int, int);
    char name();
   ~Doodlebug();

};

#endif
