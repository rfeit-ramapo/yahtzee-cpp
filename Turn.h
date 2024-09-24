#include <iostream>
#include <iterator>
#include "Player.h"

using namespace std;

class Turn
{
    public:

        void Play(int a_roundNum)
        {            
            cout << "=================================" << endl;
            cout << "Turn -- " << m_player->GetLogName() << endl;

            // Up to two rerolls allowed.
            bool stand = false;
            int rollNum = 1;
            vector<int> availableCategories;

            while (!stand)
            {
                // Roll and print the dice.
                cout << "=================================" << endl;
                cout << "Roll " << rollNum << endl;
                m_player->RollAll(*m_dice);
                m_dice->Print();

                if (rollNum < 3) 
                {
                    // List all scorecard categories available, given the dice set so far.
                    availableCategories = m_player->ListAvailableCategories(*m_strat, m_dice);

                    // List the category or categories that the player wants to pursue.
                    m_player->PursueCategories(*m_strat, availableCategories, m_dice);

                    // State whether the player wants to roll again or stand after rolls 1 and 2.
                    stand = m_player->HandleRerolls(m_dice);
                }
                else 
                {
                    // todo: decide whether to just replace with break
                    /*
                    m_dice->LockAllDice(); // On Roll 3, so no dice can be rerolled.

                    // List all scorecard categories available, given the dice set so far.
                    availableCategories = m_player->ListAvailableCategories(*m_strat, m_dice);
                    stand = true;
                    */
                   break;
                }

                ++rollNum;
            }

            // Announce the category filled, if any, and score earned.
            // Enter the player name, score, and round number into the scorecard.
            m_dice->LockAllDice();  // Player stood, so no dice can be rerolled.
            availableCategories = m_player->ListAvailableCategories(*m_strat, m_dice);
            // todo: decide whether to actually make the player list categories now
            m_player->ChooseCategory(m_scorecard, a_roundNum, *m_strat, availableCategories, m_dice);
            m_dice->UnlockAllDice();
        };
    
        // Constructors
        Turn() {}; // Default

        Turn(shared_ptr<Player> a_player, shared_ptr<Dice> a_dice, shared_ptr<const StrategyEngine> a_strat, shared_ptr<Scorecard> a_scorecard) : m_player(a_player), m_dice(a_dice), m_strat(a_strat), m_scorecard(a_scorecard) {};

    private:
        shared_ptr<Player> m_player;
        shared_ptr<Dice> m_dice;
        shared_ptr<const StrategyEngine> m_strat;
        shared_ptr<Scorecard> m_scorecard;
};