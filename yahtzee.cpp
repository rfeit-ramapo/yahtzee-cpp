/*     
************************************************************
* Name:  Rebecca Feit                                      *
* Project:  Yahtzee in C++                                 *
* Class:  OPL (CMPS 366 01)                                *
* Date:  09/29/2024                                        *
************************************************************
*/

#include <iostream>
#include "include/Tournament.h"

using namespace std;

int main()
{
    // Create the tournament and start play.
    Tournament myGame = Tournament();
    myGame.Play();

    exit(0);
}