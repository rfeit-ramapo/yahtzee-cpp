#include "Player.h"

using namespace std;

// Class to handle functionality for a human player.
class Human : public Player
{
public:

    // Constructor
    Human() : Player("You", "Human") {};

    // Functions

    /* *********************************************************************
    Function Name: RollOne
    Purpose: To have this player roll one die
    Parameters: 
                dice, a reference to the dice set to roll
    Return Value: The resulting value from the roll
    Algorithm:
            1) Asks if the player wants to manually roll the die
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
            2) Create a help string in case the user wants to be told directly
            3) Acquire and validate user input
            4) Return the list of available categories
    Reference: None
    ********************************************************************* */
    vector<int> ListAvailableCategories
    (
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
            2) Validate player input of categories to pursue
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
            1) Ask if player wants to reroll
                2) Return true if standing
            3) Loop until player inputs valid dice to reroll
            4) Return false to indicate that the player rerolled
    Reference: None
    ********************************************************************* */
    bool HandleRerolls(shared_ptr<Dice> a_dice);

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
            1) Return early if scoring is impossible
            2) Calculate best strategy and ask player to choose a category
            3) Validate player's input of how many points they earned
            4) Fill the category
    Reference: None
    ********************************************************************* */
    void ChooseCategory
    (
        shared_ptr<Scorecard> a_scorecard, 
        int a_round, 
        const StrategyEngine& a_strat, 
        const vector<int>& a_availableCategories, 
        shared_ptr<const Dice> a_dice
    );

private:
    // Strategy filled as turn progresses with help-suggested advice
    Strategy m_helpStrat;
};