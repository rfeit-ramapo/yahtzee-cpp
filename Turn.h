#include <iostream>
#include <iterator>
#include "Player.h"

using namespace std;

class Turn
{
    public:

        void Play(int a_roundNum);
    
        // Constructors
        Turn() {}; // Default

        Turn(
            shared_ptr<Player> a_player, 
            shared_ptr<Dice> a_dice, 
            shared_ptr<const StrategyEngine> a_strat, 
            shared_ptr<Scorecard> a_scorecard
        ) : m_player(a_player), 
            m_dice(a_dice), 
            m_strat(a_strat), 
            m_scorecard(a_scorecard) 
        {};

    private:
        shared_ptr<Player> m_player;
        shared_ptr<Dice> m_dice;
        shared_ptr<const StrategyEngine> m_strat;
        shared_ptr<Scorecard> m_scorecard;
};