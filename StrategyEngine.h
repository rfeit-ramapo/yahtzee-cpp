#pragma once

#include <iostream>
#include <cmath>
#include "Scorecard.h"

using namespace std;

class StrategyEngine
{
    public:

        vector<int> GetPossibleCategories(shared_ptr<const Dice> a_dice) const
        {
            // Set up the boolean vector to hold whether each category is available.
            vector<int> possibleCategories;

            // Retrieve the categories from the scorecard
            const vector<shared_ptr<Category>>& categories = m_scorecard->GetCategories();

            // Check if max possible score > 0 (if the category is possible given current diceset)
            for (int i = 0; i < categories.size(); ++i)
            {
                if (categories[i]->GetRerollStrategy(a_dice).GetMaxScore())
                {
                    // Save the index of all possible categories.
                    possibleCategories.push_back(i);
                }
            }
            
            return possibleCategories;
        }

        Strategy Strategize(shared_ptr<const Dice> a_dice) const
        {
            // Retrieve the categories from the scorecard
            const vector<shared_ptr<Category>>& categories = m_scorecard->GetCategories();

            Strategy strategy; // Use default constructor to initialize

            // Iterate over each category
            for (const auto& category : categories)
            {
                // Call GetRerollStrategy() on the shared_ptr<Category> object
                const Strategy& testStrategy = category->GetRerollStrategy(a_dice);

                // Update the best strategy based on the score
                if (strategy < testStrategy) 
                {
                    strategy = testStrategy;
                }
            }

            return strategy;
        }

        void FillCategory(int a_categoryIndex) { m_scorecard->FillCategory(a_categoryIndex); }

        // Constructors
        StrategyEngine() {}; // Default

        StrategyEngine(shared_ptr<Scorecard> a_scorecard) : m_scorecard(a_scorecard) {};

        // Getters
        shared_ptr<const Scorecard> GetScorecard() const { return m_scorecard; }

    private:
        shared_ptr<Scorecard> m_scorecard;
};