/********************************************************************* 
** Author:      Group 11
** Date:        07/29/18
** Description: The menuValidation.cpp file contains the functions 
*               necessary to limit user input so as to not crash the
*               program.
*********************************************************************/
#include "menuValidation.hpp"
#include <iostream>
#include <string>
#include <cmath>

/********************************************************************* 
** Description: int mainMenuValidate()
*               Acts as a barrier to incorrect user inputs. Prompts
*               the user for new input if values entered are not
*               integers 1 or 2
*********************************************************************/
int mainMenuValidate()
{
    int go=1;
    std::string userIn;
    do
    {
        // http://www.cplusplus.com/forum/beginner/2624/
        // How to identify the Enter key when pressed alone 
        std::getline(std::cin, userIn);
        int length=userIn.length();
        if (userIn[0]==' ' || length>1 || (userIn[0]-'0')>2 || (userIn[0]-'0')<1)
        {
            std::cout << "Please re-enter your choice as an integer 1,2 or 3:" << std::endl;
        }
        else
        {
            // Work cited: https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
            go=0; // Signal variable exits while loop
            return((int)userIn[0]-'0'); // Converts char to int via ASCII code math
        }
    }
    while (go);
    return 0;
}

/********************************************************************* 
** Description: int gameMenuValidate()
*               Acts as a barrier to incorrect user inputs. Prompts
*               the user for new input if values entered are not a
*               positive integer
*********************************************************************/
int gameMenuValidate()
{
    int runTotal=0, go=1;
    do
    {
        std::string userIn;
        std::getline(std::cin, userIn);
        int length=userIn.length();
        for (int i=0; i<length; i++)
        {
            if (isdigit(userIn[i]) && !(ispunct(userIn[i])) && !(isspace(userIn[i])))
            {
                // Work cited: https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-cs
                runTotal+=pow(10,length-1-i)*(userIn[i]-'0'); // Converts char back to int
                if ((i+1)==length)
                    go=0;
                if (!runTotal)
                {
                    std::cout << "Please enter a positive integer value (without spaces, commas, or periods) greater than 0: " << std::endl;
                    runTotal=0;
                    go=1;
                }
            }
            else
            {
                std::cout << "Please enter a positive integer value (without spaces, commas, or periods) greater than 0: " << std::endl;
                runTotal=0;
                break;
            }   
        }
    } while (go);
    return runTotal;
}
