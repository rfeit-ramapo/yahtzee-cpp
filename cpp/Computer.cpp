#include <iostream>
#include "../include/Computer.h"

using namespace std;

/* *********************************************************************
Function Name: RollOne
Purpose: To have this player roll one die
Parameters: 
            dice, a reference to the dice set to roll
Return Value: The resulting value from the roll
Algorithm:
        1) Asks if the user wants to manually roll the die
            2) If yes, validate input
        3) Otherwise, randomly generate die roll
Reference: I asked ChatGPT about defining pure virtual functions.
********************************************************************* */
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

/* *********************************************************************
Function Name: ListAvailableCategories
Purpose: Makes player list available categories given the dice set
Parameters: 
            a_strat, a constant reference to a StrategyEngine for generating possibilities
            a_dice, a pointer to constant Dice used to determine available categories
Return Value: A vector of categories that are available by index [1,12]
Algorithm:
        1) Get the list of possible categories based on the dice
        2) Print those categories
        3) Return the list of available categories
Reference: None
********************************************************************* */
vector<int> Computer::ListAvailableCategories
(
    const StrategyEngine& a_strat, 
    shared_ptr<const Dice> a_dice
)
{
    // Inform player of next step.
    cout << endl << "Listing all available categories, given the dice set so far..." << endl;

    // Get and print the conclusive list of available categories.
    vector<int> availableCategories = a_strat.GetPossibleCategories(a_dice);
    for (int i = 0; i < availableCategories.size(); ++i)
    {
        ++availableCategories[i];
        cout << availableCategories[i] << " ";
    }
    cout << endl;

    return availableCategories;
}

/* *********************************************************************
Function Name: PursueCategories
Purpose: Makes player choose which categories to pursue
Parameters: 
            a_strat, a constant reference to a StrategyEngine for generating possibilities
            a_availableCategories, a constant reference to a vector containing available categories by index [1,12]
            a_dice, a pointer to constant Dice object used to determine possibilities
Return Value: None
Algorithm:
        1) Set the help strategy based on current dice set
        2) Print the current strategy
Reference: None
********************************************************************* */
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

/* *********************************************************************
Function Name: HandleRerolls
Purpose: Makes player decide whether to stand or reroll, and which dice to reroll
Parameters: 
            a_dice, a pointer to the Dice to be rerolled
Return Value: a boolean indicating if the player wants to reroll
Algorithm:
        1) Check if strategy warrants standing
            2) Return true if so
        3) Get dice to reroll from the strategy
        4) Lock all other dice
        5) Return false to indicate rerolling
Reference: None
********************************************************************* */
bool Computer::HandleRerolls(shared_ptr<Dice> a_dice)
{
    // Return early if the strategy indicates standing.
    if (m_strat.PlanToStand()) return true;

    // Get the dice to reroll based on the decided strategy.
    vector<int> diceToReroll = m_strat.GetRerollDice();
    // Lock all other dice.
    a_dice->LockDice(diceToReroll);

    return false;
}

/* *********************************************************************
Function Name: ChooseCategory
Purpose: Makes player decide which category to fill
Parameters: 
            a_scorecard, a pointer to the scorecard to update
            a_round, the current round number
            a_strat, a StrategyEngine for determining strategy
            a_availableCategories, a list of category indices that are available
            a_dice, a pointer to const Dice used to determine what categories can be scored
Return Value: None
Algorithm:
        1) Calculate strategy that gives maximum points
        2) Update the computer's score and enact the strategy
Reference: None
********************************************************************* */
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