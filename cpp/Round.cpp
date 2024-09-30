#include "../include/Round.h"
#include "../include/Turn.h"

using namespace std;

/* *********************************************************************
Function Name: Play
Purpose: Plays this round out
Parameters: None
Return Value: None
Algorithm:
    1) Prints the round info
    2) Determines and prints who will go first in this round
    3) Completes player 1's turn
        4) If player 1 finished the game, ends the round early
    5) Completes player 2's turn
    6) Prints scores for both players before ending round
Reference: none
********************************************************************* */
void Round::Play()
{
    // Round header
    cout << "=================================" << endl << endl;
    cout << "Round " << m_roundNum << ":" << endl << endl;
    cout << "=================================" << endl;
    DetermineFirstPlayer();
    cout << m_players[0]->GetLogName() << " will go first." << endl;

    // Turn for Player 1
    Turn&& turn = Turn(m_players[0], m_dice, m_strat, m_scorecard);
    turn.Play(m_roundNum);

    // Turn for Player 2
    if (m_scorecard->IsFull()) return;
    turn = Turn(m_players[1], m_dice, m_strat, m_scorecard);
    turn.Play(m_roundNum);

    // Print current score for each player
    cout << "Score - " << m_players[0]->GetLogName() << ": " << m_players[0]->GetScore() << endl;
    cout << "Score - " << m_players[1]->GetLogName() << ": " << m_players[1]->GetScore() << endl;
}

/* *********************************************************************
Function Name: DetermineFirstPlayer
Purpose: Swaps the order of the player vector according to turn order
Parameters: None
Return Value: None
Algorithm:
    1) Gets the scores for each player
    2) If they are equal, make players roll dice until one has higher roll
    3) If player 2 should go first, swap player positions in vector
Reference: none
********************************************************************* */
void Round::DetermineFirstPlayer()
{
    int p1_score = m_players[0]->GetScore();
    int p2_score = m_players[1]->GetScore();

    // First turn or equal scores
    if (p1_score == p2_score)
    {
        cout << "Determining who will go first..." << endl;

        // Roll dice until winner is found.
        int p1_roll;
        int p2_roll;
        do
        {
            p1_roll = m_players[0]->RollOne(*m_dice);
            p2_roll = m_players[1]->RollOne(*m_dice);
            cout << m_players[0]->GetLogName() << " rolled a " << p1_roll << endl;
            cout << m_players[1]->GetLogName() << " rolled a " << p2_roll << endl << endl;
        } while (p1_roll == p2_roll);

        // Swap player order if required
        if (p2_roll > p1_roll) swap(m_players[0], m_players[1]);
    }
    // Swap player order if required
    else if (p1_score > p2_score) swap(m_players[0], m_players[1]);
}