#include <sstream>
#include <algorithm>
#include "Human.h"

using namespace std;

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

vector<int> Human::ListAvailableCategories
(
    const StrategyEngine& a_strat, 
    shared_ptr<const Dice> a_dice
)
{
    // Get the conclusive list.
    vector<int> availableCategories = a_strat.GetPossibleCategories(a_dice);

    // Print a basic scorecard for reference.
    cout << endl;

    // Get player list.
    cout << "Please list all scorecard categories available, given the dice set so far." << endl;

    string helpString = "The available categories are:";
    // Validate user input.
    for (int i = 0; i < availableCategories.size(); ++i) 
    {
        ++availableCategories[i];
        helpString += " " + to_string(availableCategories[i]);
    }
    Input::ValidateExactIntList(availableCategories, "categories", helpString);

    return availableCategories;
}

void Human::PursueCategories
(
    const StrategyEngine& a_strat, 
    const vector<int>& a_availableCategories, 
    shared_ptr<const Dice> a_dice
) 
{
    cout << "Please input one or two categories to pursue." << endl;
    m_helpStrat = a_strat.Strategize(a_dice);
    // Loop to handle processing user input.
    Input::ValidateIntList(a_availableCategories, "categories", 0, m_helpStrat.GetString(true));
};

bool Human::HandleRerolls(shared_ptr<Dice> a_dice)
{
    // If roll again, list the dice the player wants to re-roll. Identify dice by their current face (e.g., "I will re-roll 3, 1 and 6").
    cout << "Please choose whether to stand or reroll." << endl;
    
    // Handle player input.
    if (Input::ValidateStandReroll(m_helpStrat.GetString(true))) return true;

    cout << "Which dice would you like to reroll? Input the face values." << endl;

    vector<int> freeDice = a_dice->GetFreeDice();
    vector<int> playerRerollCount;
    do
    {
        vector<int> playerDiceList = Input::ValidateIntList({1,2,3,4,5,6}, "dice faces");
        playerRerollCount = Dice::ListToCount(playerDiceList);
    }
    while (!a_dice->LockDice(playerRerollCount));
    return false;
}

void Human::ChooseCategory
(
    shared_ptr<Scorecard> a_scorecard, 
    int a_round, 
    const StrategyEngine& a_strat, 
    const vector<int>& a_availableCategories, 
    shared_ptr<const Dice> a_dice
) 
{
    if (a_availableCategories.size() == 0)
    {
        cout << "There is no way to score with the current dice set and open categories. Skipping turn." << endl << endl;
        return;
    }

    m_helpStrat = a_strat.Strategize(a_dice);

    // Take player input
    cout << "Please identify the category you would like to claim." << endl;

    // Loop to handle processing user input.
    int chosenCategory = Input::ValidateInt(a_availableCategories, "categories", m_helpStrat.GetString(true)) - 1;

    cout << "Please enter the score earned for this category." << endl;
    int claimedScore = Input::ValidateInt(
        {a_scorecard->GetCategory(chosenCategory)->Score(*a_dice)},
         "score"
    );

    cout << "Please press enter to fill the scorecard." << endl;
    cin.get();
    AddScore(claimedScore);
    a_scorecard->FillCategory(chosenCategory, claimedScore, a_round, "Human");
    a_scorecard->Print();
}