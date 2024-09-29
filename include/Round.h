#include <string>
#include <memory>
#include <iostream>
#include "Dice.h"
#include "Player.h"

using namespace std;

class Round
{
    public:
        
        void DetermineFirstPlayer();

        void Play();

        // Constructors
        Round() {}; // Default

        Round(
            int a_roundNum, 
            vector<shared_ptr<Player>> a_players, 
            shared_ptr<Dice> a_dice, 
            shared_ptr<const StrategyEngine> a_strat, 
            shared_ptr<Scorecard> a_scorecard
        ) : m_roundNum(a_roundNum), 
            m_players(a_players), 
            m_dice(a_dice), 
            m_strat(a_strat), 
            m_scorecard(a_scorecard) 
        {};
        
    private:
        vector<shared_ptr<Player>> m_players;
        shared_ptr<Dice> m_dice;
        shared_ptr<const StrategyEngine> m_strat;
        shared_ptr<Scorecard> m_scorecard;

        int m_roundNum;
};