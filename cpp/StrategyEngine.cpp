#include "../include/StrategyEngine.h"

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
vector<int> StrategyEngine::GetPossibleCategories(shared_ptr<const Dice> a_dice) const
{
    // Set up the vector to hold category indices.
    vector<int> possibleCategories;

    // Retrieve the categories from the scorecard
    const vector<shared_ptr<Category>>& categories = m_scorecard->GetCategories();

    // Check if max possible score > 0 (if the category is possible given current diceset)
    for (int i = 0; i < Scorecard::NUM_CATEGORIES; ++i)
    {
        if (categories[i]->GetRerollStrategy(a_dice).GetMaxScore())
        {
            // Save the index of all possible categories.
            possibleCategories.push_back(i);
        }
    }
    
    return possibleCategories;
}

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
Strategy StrategyEngine::Strategize(shared_ptr<const Dice> a_dice) const
{
    // Retrieve the categories from the scorecard
    const vector<shared_ptr<Category>>& categories = m_scorecard->GetCategories();

    // Use default constructor to initialize
    Strategy strategy; 

    // Iterate over each category
    for (const auto& category : categories)
    {
        // Call GetRerollStrategy() on the shared_ptr<Category> object
        const Strategy& testStrategy = category->GetRerollStrategy(a_dice);

        // Update the best strategy based on the score
        if (strategy <= testStrategy) 
        {
            strategy = testStrategy;
        }
    }

    return strategy;
}