#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <numeric>
#include "Dice.h"

using namespace std;

// Forward declaration required to avoid circular dependencies.
class Scorecard;

// Holds info for a particular strategy.
class Strategy
{
public:

    // Constructors

    // Default
    Strategy() : m_currentScore(0), m_maxScore(0) {};

    // Build a strategy, with a current score, max score, and category.
    Strategy(
        int a_currentScore, 
        int a_maxScore, 
        const string a_categoryName
    ) : m_currentScore(a_currentScore), 
        m_maxScore(a_maxScore), 
        m_categoryName(a_categoryName) 
    {};
    // Build a strategy, with a current score, max score, category, dice set, target dice values, and reroll counts.
    Strategy(
        int a_currentScore, 
        int a_maxScore, 
        const string a_categoryName, 
        shared_ptr<const Dice> a_dice, 
        vector<int> a_targetDice, 
        vector<int> a_rerollCounts
    ) : m_currentScore(a_currentScore), 
        m_maxScore(a_maxScore), 
        m_categoryName(a_categoryName), 
        m_dice(a_dice), 
        m_targetDice(a_targetDice), 
        m_rerollCounts(a_rerollCounts) 
    {};

    // Selectors

    // Return whether this strategy requires the player to stand
    inline bool PlanToStand() const { return (m_maxScore == m_currentScore); }
    inline int GetMaxScore() const { return m_maxScore; }
    inline int GetCurrentScore() const { return m_currentScore; }
    inline vector<int> GetRerollDice() const { return m_rerollCounts; }

    // Operator overloads
    // Used to determine which strategy is ideal based on the maximum score potential
    bool operator <(const Strategy& s) const { return (m_maxScore < s.m_maxScore); }
    bool operator ==(const Strategy& s) const { return (m_maxScore == s.m_maxScore); }
    bool operator >(const Strategy& s) const { return (m_maxScore > s.m_maxScore); }
    bool operator <=(const Strategy& s) const { return (m_maxScore <= s.m_maxScore); }
    bool operator >=(const Strategy& s) const { return (m_maxScore >= s.m_maxScore); }
    bool operator !=(const Strategy& s) const { return !(m_maxScore != s.m_maxScore); }

    // Functions

    /* *********************************************************************
    Function Name: Print
    Purpose: Prints the strategy in user-friendly format
    Parameters: 
                suggest, a boolean indicating whether this is a suggestion for the user
    Return Value: None
    Algorithm:
        1) Prints out the string generated by this strategy
    Reference: none
    ********************************************************************* */
    inline void Print(bool suggest) const { cout << GetString(suggest); };

    /* *********************************************************************
    Function Name: GetString
    Purpose: Creates a user-friendly string describing this strategy
    Parameters: 
                suggest, a boolean indicating whether this is a suggestion for the user
    Return Value: a string describing the strategy
    Algorithm:
        1) Creates a string to hold the strategy info
        2) If the max score is zero, this strategy is for a dead-end dice set
        3) If the current score is the max score, print a stand strategy
        4) Otherwise, create a string explaining how to reroll for maximum points
    Reference: none
    ********************************************************************* */
    string GetString(bool suggest) const;

    /* *********************************************************************
    Function Name: Enact
    Purpose: Enacts this strategy for a Computer player by filling the scorecard
    Parameters: 
                a_scorecard, a reference to the scorecard to update
                a_round, the current round number
    Return Value: none
    Algorithm:
        1) If attempting to enact an empty strategy, skip
        2) Get the category info and fill it via the scorecard
        3) Print the scorecard
    Reference: none
    ********************************************************************* */
    void Enact(Scorecard& a_scorecard, int a_round);
    
private:
    // The category this strategy is based on
    string m_categoryName; 
    // If this category is selected, the value it would give
    int m_currentScore; 
    // Maximum score possible for this category, given the dice set
    int m_maxScore;
    // The set of dice this strategy is for
    shared_ptr< const Dice> m_dice; 
    // The desired dice face counts after enacting this strategy
    vector<int> m_targetDice; 
    // How many dice of each face value to reroll
    vector<int> m_rerollCounts;

    /* *********************************************************************
    Function Name: PrintDice
    Purpose: Gets a string listing dice counts in a user-friendly format
            (e.g. 1 Ace, 3 Twos, and 2 Sixes)
    Parameters: 
                a_diceValues, a vector holding dice face counts
    Return Value: a string listing the dice counts in a user-friendly format
    Algorithm:
        1) Loops through each dice face and checks how many dice there are
        2) For each die, add on to the string (accounting for plurals)
        3) When all dice have been processed, ensure string ends properly (with or without "and")
        4) Return the built string
    Reference: none
    ********************************************************************* */
    string PrintDice(vector<int> a_diceValues) const;
};