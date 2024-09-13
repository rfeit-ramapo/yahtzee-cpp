#include <iostream>
#include "Tournament.h"
#include "Strategy.h"

using namespace std;

int main()
{
    Tournament test = Tournament();

    test.Play();

    //Strategy strat = Strategy(make_shared<Scorecard>());
    //strat.InitializeStrategy();
    //strat.PrintRolls();

    //strat.Strategize({2,1,2,0,0,0});


}