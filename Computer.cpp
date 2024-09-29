#include <iostream>
#include "Computer.h"

using namespace std;

int Computer::RollOne(Dice &dice) 
{ 
    // Manual input option
    cout << "Computer's roll..." << endl;
    cout << "Would you like to manually input this dice roll? (y/n)" << endl;
    
    if (Input::ValidateYesNo())
    {
        cout << "Input the result of your roll." << endl;
        return Input::ValidateInt({1,2,3,4,5,6}, "dice face");
    }

    return dice.RollOne(); 
}

vector<int> Computer::ListAvailableCategories
(
    const StrategyEngine& a_strat, 
    shared_ptr<const Dice> a_dice
)
{
    // Get the conclusive list.
    vector<int> availableCategories = a_strat.GetPossibleCategories(a_dice);

    // Print a basic scorecard for reference.
    cout << endl;
    //a_strat.GetScorecard()->Print();

    // Inform player of next step.
    cout << "Listing all available categories, given the dice set so far..." << endl;

    // Print the categories.
    for (int i = 0; i < availableCategories.size(); ++i)
    {
        ++availableCategories[i];
        cout << availableCategories[i] << " ";
    }
    cout << endl;

    return availableCategories;
}

void Computer::PursueCategories
(
    const StrategyEngine& a_strat, 
    const vector<int>& a_availableCategories, 
    shared_ptr<const Dice> a_dice
) 
{
    m_strat = a_strat.Strategize(a_dice);
    cout << endl;
    m_strat.Print(false);
}

bool Computer::HandleRerolls(shared_ptr<Dice> a_dice)
{
    if (m_strat.PlanToStand()) return true;

    // Get the dice to reroll based on the decided strategy.
    vector<int> diceToReroll = m_strat.GetRerollDice();

    // Lock all other dice.
    a_dice->LockDice(diceToReroll);

    return false;
}

void Computer::ChooseCategory
(
    shared_ptr<Scorecard> a_scorecard, 
    int a_round, 
    const StrategyEngine& a_strat, 
    const vector<int>& a_availableCategories, 
    shared_ptr<const Dice> a_dice
)
{
    m_strat = a_strat.Strategize(a_dice);
    AddScore(m_strat.GetCurrentScore());
    m_strat.Enact(*a_scorecard, a_round);
};