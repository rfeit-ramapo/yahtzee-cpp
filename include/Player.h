#pragma once

#include <string>
#include "StrategyEngine.h"
#include "Dice.h"
#include "Input.h"

using namespace std;

class Player
{
public:

    // Constructors

    // Default
    Player() {}; // Default

    // Including a log name and internal name
    Player(string a_logName, string a_internalName): 
        m_logName(a_logName), m_internalName(a_internalName), m_score(0) 
    {};

    // Selectors

    inline string const GetLogName() const { return m_logName; }
    inline string const GetInternalName() const { return m_internalName; }
    inline int const GetScore() const { return m_score; }

    // Mutators

    // Adds points to the current score
    inline void AddScore(int a_add) { m_score+= a_add; }

    // Functions

    /* *********************************************************************
    Function Name: RollAll
    Purpose: Rolls all unlocked dice for the player
    Parameters: 
                dice, a reference to the dice set to be rerolled
    Return Value: a vector of the newly generated dice face values
    Algorithm:
        1) Checks if the player wants to manually input the roll
            2) If so, gets new values for unlocked dice
        3) Otherwise, uses automatic reroll function
    Reference: none
    ********************************************************************* */
    vector<int> RollAll(Dice &dice);
    
    // Virtual Functions

    /* *********************************************************************
    Function Name: RollOne
    Purpose: To have this player roll one die
    Parameters: 
                dice, a reference to the dice set to roll
    Return Value: The resulting value from the roll
    Algorithm:
        This is a pure virtual function to be implemented by derived classes.
    Reference: I asked ChatGPT about defining pure virtual functions.
    ********************************************************************* */
    virtual int RollOne(Dice& dice) = 0;

    /* *********************************************************************
    Function Name: ListAvailableCategories
    Purpose: Makes player list available categories given the dice set
    Parameters: 
                a_strat, a constant reference to a StrategyEngine for generating possibilities
                a_dice, a pointer to constant Dice used to determine available categories
    Return Value: A vector of categories that are available by index [1,12]
    Algorithm:
        This is a pure virtual function to be implemented by derived classes.
    Reference: I asked ChatGPT about defining pure virtual functions.
    ********************************************************************* */
    virtual vector<int> ListAvailableCategories(
        const StrategyEngine& a_strat, 
        shared_ptr<const Dice> a_dice
    ) = 0;

    /* *********************************************************************
    Function Name: PursueCategories
    Purpose: Makes player choose which categories to pursue
    Parameters: 
                a_strat, a constant reference to a StrategyEngine for generating possibilities
                a_availableCategories, a constant reference to a vector containing available categories by index [1,12]
                a_dice, a pointer to constant Dice object used to determine possibilities
    Return Value: None
    Algorithm:
        This is a pure virtual function to be implemented by derived classes.
    Reference: I asked ChatGPT about defining pure virtual functions.
    ********************************************************************* */
    virtual void PursueCategories(
        const StrategyEngine& a_strat, 
        const vector<int>& a_availableCategories, 
        shared_ptr<const Dice> a_dice
    ) = 0;

    /* *********************************************************************
    Function Name: HandleRerolls
    Purpose: Makes player decide whether to stand or reroll, and which dice to reroll
    Parameters: 
                a_dice, a pointer to the Dice to be rerolled
    Return Value: a boolean indicating if the player wants to reroll
    Algorithm:
        This is a pure virtual function to be implemented by derived classes.
    Reference: I asked ChatGPT about defining pure virtual functions.
    ********************************************************************* */
    virtual bool HandleRerolls(shared_ptr<Dice> a_dice) = 0;

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
        This is a pure virtual function to be implemented by derived classes.
    Reference: I asked ChatGPT about defining pure virtual functions.
    ********************************************************************* */
    virtual void ChooseCategory(
        shared_ptr<Scorecard> a_scorecard, 
        int a_round, 
        const StrategyEngine& a_strat, 
        const vector<int>& a_availableCategories, 
        shared_ptr<const Dice> a_dice
    ) = 0; 

private:
    // Name to output to log for this player
    string m_logName;
    // Name to use internally and for scorecard for this player
    string m_internalName;
    // This player's current score
    int m_score;
};