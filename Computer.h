#include <string>
#include <iostream>
#include "Player.h"

using namespace std;

class Computer : public Player
{
    public:

        int RollOne(Dice &dice) { return dice.RollOne(); }

        // Todo
        vector<int> RollSome(Dice &dice) {};

        vector<int> RollAll(Dice &dice) { return dice.RollAll(); };

        vector<int> ListAvailableCategories(const StrategyEngine& a_strat, shared_ptr<const Dice> a_dice)
        {
            // Get the conclusive list.
            vector<int> availableCategories = a_strat.GetPossibleCategories(a_dice);

            // Print a basic scorecard for reference.
            cout << endl;
            a_strat.GetScorecard()->Print();

            // Inform player of next step.
            cout << "Listing all available categories, given the dice set so far..." << endl;

            // Print the categories.
            for (int i = 0; i < availableCategories.size(); ++i)
            {
                cout << (availableCategories[i] + 1) << " ";
            }
            cout << endl;

            return availableCategories;
        }

        void PursueCategories(const StrategyEngine& a_strat, const vector<int>& a_availableCategories, shared_ptr<const Dice> a_dice) 
        {
            m_strat = a_strat.Strategize(a_dice);
            cout << endl;
            m_strat.Print(false);
        }

        bool HandleRerolls(shared_ptr<Dice> a_dice)
        {
            if (m_strat.PlanToStand()) return true;

            // Get the dice to reroll based on the decided strategy.
            vector<int> diceToReroll = m_strat.GetRerollDice();

            // Lock all other dice.
            a_dice->LockDice(diceToReroll);

            return false;
        }

        void ChooseCategory(shared_ptr<Scorecard> a_scorecard, int a_round, const StrategyEngine& a_strat, const vector<int>& a_availableCategories, shared_ptr<const Dice> a_dice) 
        {
            m_strat = a_strat.Strategize(a_dice);
            AddScore(m_strat.GetCurrentScore());
            m_strat.Enact(*a_scorecard, a_round);
        };

        // Constructors
        Computer() : Player("The computer", "Computer") {}; // Default
        Computer(int a_score) : Player("The computer", "Computer", a_score) {};

    private:
        Strategy m_strat;
};