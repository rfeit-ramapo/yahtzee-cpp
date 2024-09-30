#pragma once

#include <iostream>
#include <cmath>
#include "Scorecard.h"

using namespace std;

// Class to generate strategies.
class StrategyEngine
{
public:
    // Constructors

    // Default
    StrategyEngine() {};
    // Including scorecard pointer
    StrategyEngine(shared_ptr<Scorecard> a_scorecard) : m_scorecard(a_scorecard) {};

    // Selectors
    shared_ptr<const Scorecard> GetScorecard() const { return m_scorecard; }

    // Functions

    /* *********************************************************************
    Function Name: GetPossibleCategories
    Purpose: Checks all categories that can be achieved, given locked dice
    Parameters: 
                a_dice, a pointer to const Dice object to compare against
    Return Value: a vector of category indices that are possible for this dice set
    Algorithm:
        1) Gets a reference to every category
        2) For each category, gets a reroll strategy
            3) If the strategy is worth 0 max points, it is impossible to achieve
            4) If possible, add the category index to a vector
        5) Return the vector of possible category indices
    Reference: none
    ********************************************************************* */
    vector<int> GetPossibleCategories(shared_ptr<const Dice> a_dice) const;

    /* *********************************************************************
    Function Name: Strategize
    Purpose: Determines the best strategy to follow based on the given dice set
    Parameters: 
                a_dice, a pointer to const Dice object to analyze
    Return Value: the best Strategy found
    Algorithm:
        1) Get a reference to every category
        2) For each category, check the reroll strategy for this dice set
            3) If the strategy is greater than the previous best strategy, replace it
        4) Return the final best strategy found
    Reference: none
    ********************************************************************* */
    Strategy Strategize(shared_ptr<const Dice> a_dice) const;

private:
    // Pointer to the scorecard for this game
    shared_ptr<Scorecard> m_scorecard;
};