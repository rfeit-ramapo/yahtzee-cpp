#include <iostream>
#include <cmath>
#include "Scorecard.h"
#include "PossibleRoll.h"

using namespace std;

class StrategyEngine
{
    public:

        void InitializeStrategy()
        {
            
        };

        void Strategize(shared_ptr<const Dice> a_dice)
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

            // Print the best strategy found
            strategy.Print();
        }

        void FillCategory(int a_categoryIndex) { m_scorecard->FillCategory(a_categoryIndex); }


        void PrintRolls()
        {
            for (PossibleRoll r : m_possibleRolls) r.print();
        }

        // Constructors
        StrategyEngine() {}; // Default

        StrategyEngine(shared_ptr<Scorecard> a_scorecard) : m_scorecard(a_scorecard) {};

    private:
        shared_ptr<Scorecard> m_scorecard;
        vector<PossibleRoll> m_possibleRolls;
};