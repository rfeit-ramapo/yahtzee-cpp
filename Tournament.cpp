#include "Tournament.h"

void Tournament::Play()
{
    while (!m_scorecard->IsFull())
    {
        Round round = Round(m_roundNum, m_players, m_dice, m_strat, m_scorecard);
        round.Play();
        m_roundNum++;
    }
};