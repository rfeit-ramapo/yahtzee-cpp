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

        void Strategize(const vector<int> &diceValues)
        {
            

        }

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