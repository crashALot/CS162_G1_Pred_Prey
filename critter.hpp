/********************************************************************* 
** Author:      Group 11
** Date:        07/29/18
** Description: The critter.hpp file contains the interface required
*               to use Critter class objects. Linked with critter.cpp
*********************************************************************/
#ifndef CRITTER_HPP
#define CRITTER_HPP

class Critter
{
private:

    int row, col, step;

public:

    Critter();
    Critter(int, int);
    virtual void starve(int*, Critter***);
    virtual void breed(int*, Critter***, int, int);
    virtual void move(int*, Critter***, int, int);
    double randomGenerator();
    void setLocation(int, int);
    virtual char name();
    int getStep();
    void setStep();
    void setStep(int);
    int getRow();
    int getCol();
    void setRow(int);
    void setCol(int);
    virtual ~Critter();

};

#endif
