#include <iostream>
#include "Human.h"
#include "Computer.h"
#include "Round.h"
#include "Scorecard.h"

class Tournament
{
    public:

        // Functions
        void Play()
        {
            Round round = Round(m_roundNum, m_players, m_dice);
            round.Play();
        };

        // Constructors
        Tournament() // Default
        {
            m_players = {make_shared<Human>(), make_shared<Computer>()};
            m_dice = make_shared<Dice>();
            m_scorecard = Scorecard();
        };

    private:
        vector<shared_ptr<Player>> m_players;
        shared_ptr<Dice> m_dice;
        Scorecard m_scorecard;

        int m_roundNum = 1;
};