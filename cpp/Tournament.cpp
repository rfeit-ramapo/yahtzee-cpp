#include "../include/Tournament.h"
#include "../include/Input.h"
#include "../include/Serialize.h"
#include "../include/Round.h"
#include <iostream>

/* *********************************************************************
Function Name: Play
Purpose: To run the game of Yahtzee 
Parameters: None
Return Value: None
Algorithm:
    1) Print the instructions
    2) Ask the player whether to load from a file
    3) Generate rounds of play until the scorecard is full
    4) Print the winner of the tournament
Reference: none
********************************************************************* */
void Tournament::Play()
{
    // Print the instructions for the game.
    PrintInstructions();

    // Serialize the game from a file if desired.
    Serialize serializer;
    cout << "Would you like to load the game from a file? (y/n)" << endl;
    if (Input::ValidateYesNo()) 
    {
        serializer.LoadGame(m_roundNum, m_scorecard, m_players[0], m_players[1]);
    }

    // Run the game until the scorecard has been filled.
    while (!m_scorecard->IsFull())
    {
        // Successfully create and play rounds, increasing the round number each time.
        Round round = Round(m_roundNum, m_players, m_dice, m_strat, m_scorecard);
        round.Play();
        m_roundNum++;

        // If the scorecard is NOT full, ask if the player would like to save the game.
        // If it is full, the game is over already (and will be completed upon hitting the loop).
        if (!m_scorecard->IsFull())
        {
            cout << "Would you like to save and exit? (y/n)" << endl;
            if (Input::ValidateYesNo()) serializer.SaveGame(m_roundNum, m_scorecard);
        }
    }

    // Print final scorecard and winner of the tournament.
    PrintWinner();
};

/* *********************************************************************
Function Name: PrintInstructions
Purpose: To print the instructions and scorecard for the game 
Parameters: None
Return Value: None
Algorithm:
    1) Print a basic overview of the game functionality
    2) Print the scorecard
    3) Confirm that the player has read the instructions and wishes to continue
Reference: none
********************************************************************* */
void Tournament::PrintInstructions()
{
    cout << endl << "Welcome to Yahtzee! Below you will find the scorecard categories. When asked to input dice, please use face values. When asked for multiple values (dice or categories), please separate each by a space. All categories should be specified by index. To help visualize the dice, all 'locked' dice (those that have been set aside and cannot be rerolled) are displayed in red. If you need help, enter 'h' to get a recommendation." << endl << endl;

    m_scorecard->Print();

    cout << "To begin the game, please press enter." << endl;
    cin.get();
};

/* *********************************************************************
Function Name: PrintWinner
Purpose: To print the determined winner of the Tournament 
Parameters: None
Return Value: None
Algorithm:
    1) Print game completion confirmation
    2) Print both players' scores
    3) Determine winner based on player scores and print result
Reference: none
********************************************************************* */
void Tournament::PrintWinner()
{
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