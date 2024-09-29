#pragma once

#include <iostream>
#include <cmath>
#include "Scorecard.h"

using namespace std;

class StrategyEngine
{
    public:

        vector<int> GetPossibleCategories(shared_ptr<const Dice> a_dice) const;

        Strategy Strategize(shared_ptr<const Dice> a_dice) const;

        inline void FillCategory(int a_categoryIndex) 
        { 
            m_scorecard->FillCategory(a_categoryIndex); 
        }

        // Constructors
        StrategyEngine() {}; // Default

        StrategyEngine(shared_ptr<Scorecard> a_scorecard) : m_scorecard(a_scorecard) {};

        // Getters
        shared_ptr<const Scorecard> GetScorecard() const { return m_scorecard; }

    private:
        shared_ptr<Scorecard> m_scorecard;
};