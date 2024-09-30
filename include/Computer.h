#include <string>
#include "Player.h"

using namespace std;

class Computer : public Player
{
public:

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
    Reference: None
    ********************************************************************* */
    int RollOne(Dice &dice);

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
    vector<int> ListAvailableCategories(
        const StrategyEngine& a_strat, 
        shared_ptr<const Dice> a_dice
    );

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
    void PursueCategories
    (
        const StrategyEngine& a_strat, 
        const vector<int>& a_availableCategories, 
        shared_ptr<const Dice> a_dice
    );

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
    bool HandleRerolls(shared_ptr<Dice> a_dice);

    void ChooseCategory
    (
        shared_ptr<Scorecard> a_scorecard, 
        int a_round, 
        const StrategyEngine& a_strat, 
        const vector<int>& a_availableCategories, 
        shared_ptr<const Dice> a_dice
    );

    // Constructors
    Computer() : Player("The computer", "Computer") {}; // Default

private:
    Strategy m_strat;
};