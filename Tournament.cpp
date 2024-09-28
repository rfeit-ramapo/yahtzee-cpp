#include "Tournament.h"
#include <iostream>

void Tournament::Play()
{
    while (!m_scorecard->IsFull())
    {
        Round round = Round(m_roundNum, m_players, m_dice, m_strat, m_scorecard);
        round.Play();
        m_roundNum++;
    }

    // Print final scorecard and winner
    Player& player1 = *m_players[0];
    Player& player2 = *m_players[1];

    cout << endl << "=================================" << endl << "Game Complete!" << endl << endl;
    m_scorecard->Print();
    cout << "Score -- " << player1.GetLogName() << ": " << player1.GetScore() << endl;
    cout << "Score -- " << player2.GetLogName() << ": " << player2.GetScore() << endl;
    
    // Player 1 wins
    if (player1.GetScore() > player2.GetScore())
    {
        cout << player1.GetLogName() << " wins!" << endl;
    }
    // Player 2 wins
    else if (player1.GetScore() < player2.GetScore())
    {
        cout << player2.GetLogName() << " wins!" << endl;
    }
    // Draw
    else
    {
        cout << "It's a draw!" << endl;
    }
};