#include "../include/StrategyEngine.h"

vector<int> StrategyEngine::GetPossibleCategories(shared_ptr<const Dice> a_dice) const
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

Strategy StrategyEngine::Strategize(shared_ptr<const Dice> a_dice) const
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