#include <iostream>
#include "Tournament.h"
#include "StrategyEngine.h"

using namespace std;

int main()
{
    //Tournament test = Tournament();

    //test.Play();

    
    StrategyEngine stratTester = StrategyEngine(make_shared<Scorecard>());

    /*
    stratTester.FillCategory(5);
    stratTester.FillCategory(6);
    stratTester.FillCategory(7);
    stratTester.FillCategory(8);
    stratTester.FillCategory(11);
    */

    // stratTester.FillCategory(10);
    shared_ptr<Dice> dice = make_shared<Dice>(Dice({1, 1, 1, 1, 0, 1}, {1, 1, 0, 0, 0, 0}));
    Strategy mystrat = stratTester.Strategize(dice);

    mystrat.Print(false);
}