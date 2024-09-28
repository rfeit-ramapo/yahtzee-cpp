#include "Round.h"
#include "Turn.h"

using namespace std;

void Round::DetermineFirstPlayer()
{
    int p1_score = m_players[0]->GetScore();
    int p2_score = m_players[1]->GetScore();

    if (p1_score == p2_score)
    {
        cout << "Determining who will go first..." << endl;

        int p1_roll;
        int p2_roll;
        do
        {
            p1_roll = m_players[0]->RollOne(*m_dice);
            p2_roll = m_players[1]->RollOne(*m_dice);
            cout << m_players[0]->GetLogName() << " rolled a " << p1_roll << endl;
            cout << m_players[1]->GetLogName() << " rolled a " << p2_roll << endl << endl;
        } while (p1_roll == p2_roll);

        if (p2_roll > p1_roll) swap(m_players[0], m_players[1]);
    }
    else if (p1_score > p2_score) swap(m_players[0], m_players[1]);
}

void Round::Play()
{
    cout << "=================================" << endl << endl;
    cout << "Round " << m_roundNum << ":" << endl << endl;
    cout << "=================================" << endl;
    DetermineFirstPlayer();
    cout << m_players[0]->GetLogName() << " will go first." << endl;

    // Turn for Player 1
    Turn&& turn = Turn(m_players[0], m_dice, m_strat, m_scorecard);
    turn.Play(m_roundNum);

    // Turn for Player 2
    turn = Turn(m_players[1], m_dice, m_strat, m_scorecard);
    turn.Play(m_roundNum);

    // Print current score for each player
    cout << "Score - " << m_players[0]->GetLogName() << ": " << m_players[0]->GetScore() << endl;
    cout << "Score - " << m_players[1]->GetLogName() << ": " << m_players[1]->GetScore() << endl;
}