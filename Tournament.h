#include <iostream>
#include "Human.h"
#include "Computer.h"
#include "Round.h"
#include "Scorecard.h"
#include "StrategyEngine.h"

class Tournament
{
    public:

        // Functions
        void Play();

        // Constructors
        Tournament() // Default
        {
            m_players = {make_shared<Human>(), make_shared<Computer>()};
            m_dice = make_shared<Dice>();
            m_scorecard = make_shared<Scorecard>();
            m_strat = make_shared<StrategyEngine>(m_scorecard);
        };

    private:
        vector<shared_ptr<Player>> m_players;
        shared_ptr<Dice> m_dice;
        shared_ptr<Scorecard> m_scorecard;
        shared_ptr<const StrategyEngine> m_strat;

        int m_roundNum = 1;
};