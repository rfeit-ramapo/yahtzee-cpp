#include <sstream>
#include <algorithm>
#include "../include/Human.h"

using namespace std;

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
int Human::RollOne(Dice& dice)
{
    // Manual input option
    cout << "Would you like to manually input this dice roll? (y/n)" << endl;
    
    if (Input::ValidateYesNo())
    {
        cout << "Input the result of your roll." << endl;
        return Input::ValidateInt({1,2,3,4,5,6}, "dice face");
    }

    return dice.RollOne();
};

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
vector<int> Human::ListAvailableCategories
(
    const StrategyEngine& a_strat, 
    shared_ptr<const Dice> a_dice
)
{
    // Get the conclusive list.
    vector<int> availableCategories = a_strat.GetPossibleCategories(a_dice);
    // Create string in case player needs help.
    string helpString = "The available categories are:";
    for (int i = 0; i < availableCategories.size(); ++i) 
    {
        ++availableCategories[i];
        helpString += " " + to_string(availableCategories[i]);
    }

    // Get player list and validate input.
    cout << endl << "Please list all scorecard categories available, given the dice set so far." << endl;
    Input::ValidateExactIntList(availableCategories, "categories", helpString);

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
        2) Validate player input of categories to pursue
Reference: None
********************************************************************* */
void Human::PursueCategories
(
    const StrategyEngine& a_strat, 
    const vector<int>& a_availableCategories, 
    shared_ptr<const Dice> a_dice
) 
{
    cout << "Please input one or two categories to pursue." << endl;
    m_helpStrat = a_strat.Strategize(a_dice);
    Input::ValidateIntList(a_availableCategories, "categories", 0, m_helpStrat.GetString(true));
};

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
bool Human::HandleRerolls(shared_ptr<Dice> a_dice)
{
    // If roll again, list the dice the player wants to re-roll. Identify dice by their current face (e.g., "I will re-roll 3, 1 and 6").
    cout << "Please choose whether to stand or reroll." << endl;
    // Return true if standing.
    if (Input::ValidateStandReroll(m_helpStrat.GetString(true))) return true;

    // If rerolling, loop until the player inputs valid faces (not locked)
    cout << "Which dice would you like to reroll? Input the face values." << endl;
    vector<int> playerRerollCount;
    do
    {
        vector<int> playerDiceList = Input::ValidateIntList({1,2,3,4,5,6}, "dice faces");
        playerRerollCount = Dice::ListToCount(playerDiceList);
    }
    while (!a_dice->LockDice(playerRerollCount));
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
        1) Return early if scoring is impossible
        2) Calculate best strategy and ask player to choose a category
        3) Validate player's input of how many points they earned
        4) Fill the category
Reference: None
********************************************************************* */
void Human::ChooseCategory
(
    shared_ptr<Scorecard> a_scorecard, 
    int a_round, 
    const StrategyEngine& a_strat, 
    const vector<int>& a_availableCategories, 
    shared_ptr<const Dice> a_dice
) 
{
    // Skip category choice if current dice set prevents scoring.
    if (a_availableCategories.size() == 0)
    {
        cout << "There is no way to score with the current dice set and open categories. Skipping turn." << endl << endl;
        return;
    }

    // Calculate the best strategy in case the player wants help
    m_helpStrat = a_strat.Strategize(a_dice);

    // Take player input
    cout << "Please identify the category you would like to claim." << endl;

    // Loop to handle processing user input.
    int chosenCategory = Input::ValidateInt(a_availableCategories, "categories", m_helpStrat.GetString(true)) - 1;

    // Validate score
    cout << "Please enter the score earned for this category." << endl;
    int claimedScore = Input::ValidateInt(
        {a_scorecard->GetCategory(chosenCategory)->Score(*a_dice)},
         "score"
    );

    // Validate round
    cout << "Please input the current round." << endl;
    Input::ValidateInt({a_round}, "round");

    // Fill the scorecard with player, round, and points info
    cout << "Please press enter to fill the scorecard." << endl;
    cin.get();
    AddScore(claimedScore);
    a_scorecard->FillCategory(chosenCategory, claimedScore, a_round, "Human");
    a_scorecard->Print();
}