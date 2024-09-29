#include "Tournament.h"
#include "Input.h"
#include "Serialize.h"
#include <iostream>

void Tournament::PrintInstructions()
{
    cout << endl << "Welcome to Yahtzee! Below you will find the scorecard categories. When asked to input dice, please use face values. When asked for multiple values (dice or categories), please separate each by a space. All categories should be specified by index. To help visualize the dice, all 'locked' dice (those that have been set aside and cannot be rerolled) are displayed in red. If you need help, enter 'h' to get a recommendation." << endl << endl;

    m_scorecard->Print();

    cout << "To begin the game, please press enter." << endl;
    cin.get();
}

void Tournament::Play()
{
    PrintInstructions();

    Serialize serializer;
    cout << "Would you like to load the game from a file? (y/n)" << endl;
    if (Input::ValidateYesNo()) serializer.LoadGame(m_roundNum, m_scorecard, m_players[0], m_players[1]);

    while (!m_scorecard->IsFull())
    {
        Round round = Round(m_roundNum, m_players, m_dice, m_strat, m_scorecard);
        round.Play();
        m_roundNum++;
        if (!m_scorecard->IsFull())
        {
            cout << "Would you like to save and exit? (y/n)" << endl;
            if (Input::ValidateYesNo()) serializer.SaveGame(m_roundNum, m_scorecard);
        }
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
        cout << "Winner: " << player1.GetLogName() << endl;
    }
    // Player 2 wins
    else if (player1.GetScore() < player2.GetScore())
    {
        cout << "Winner: " << player2.GetLogName() << endl;
    }
    // Draw
    else
    {
        cout << "It's a draw!" << endl;
    }
};