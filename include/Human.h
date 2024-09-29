#include "Player.h"

using namespace std;

class Human : public Player
{
    public:

        int RollOne(Dice &dice);

        vector<int> RollAll(Dice &dice);

        vector<int> ListAvailableCategories
        (
            const StrategyEngine& a_strat, 
            shared_ptr<const Dice> a_dice
        );

        void PursueCategories
        (
            const StrategyEngine& a_strat, 
            const vector<int>& a_availableCategories, 
            shared_ptr<const Dice> a_dice
        );

        bool HandleRerolls(shared_ptr<Dice> a_dice);

        void ChooseCategory
        (
            shared_ptr<Scorecard> a_scorecard, 
            int a_round, 
            const StrategyEngine& a_strat, 
            const vector<int>& a_availableCategories, 
            shared_ptr<const Dice> a_dice
        );

        // Constructors
        Human() : Player("You", "Human") {}; // Default
        Human(int a_score) : Player("You", "Human", a_score) {};

    private:
        Strategy m_helpStrat;
};