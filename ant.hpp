/********************************************************************* 
** Author:      Group 11
** Date:        07/29/18
** Description: The ant.hpp file contains the interface required
*               to use Ant class objects. Linked with ant.cpp
*********************************************************************/
#ifndef ANT_HPP
#define ANT_HPP
#include "critter.hpp"

class Ant : public Critter
{
private:

public:

    Ant();
    Ant(int, int);
    void breed(int*, Critter***, int, int);
    void move(int*, Critter***, int, int);
    char name();
    ~Ant();

};

#endif
