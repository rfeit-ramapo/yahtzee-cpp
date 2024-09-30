#include "../include/Turn.h"

/* *********************************************************************
Function Name: Play
Purpose: Plays out a turn of the game
Parameters: 
            a_roundNum, the round this turn takes place during
Return Value: None
Algorithm:
    1) Print the turn header
    2) Roll the dice up to three times, or until the player stands
        3) After each roll, list possible categories, what to pursue, and whether to stand
    4) Player must choose what category to fill from the available options
    5) Prepare dice for next player's turn
Reference: none
********************************************************************* */
void Turn::Play(int a_roundNum)
{            
    cout << "=================================" << endl;
    cout << "Turn -- " << m_player->GetLogName() << endl;

    // Up to two rerolls allowed.
    bool stand = false;
    int rollNum = 1;
    vector<int> availableCategories;

    // Keep rolling until the player has chosen to stand
    while (!stand)
    {
        // Roll and print the dice.
        cout << "=================================" << endl;
        cout << "Roll " << rollNum << endl;
        m_player->RollAll(*m_dice);
        cout << "Roll result: ";
        m_dice->Print();

        // Allow player choice until third roll
        if (rollNum < 3) 
        {
            // List all scorecard categories available, given the dice set so far.
            availableCategories = m_player->ListAvailableCategories(*m_strat, m_dice);

            // List the category or categories that the player wants to pursue.
            m_player->PursueCategories(*m_strat, availableCategories, m_dice);

            // State whether the player wants to roll again or stand after rolls 1 and 2.
            stand = m_player->HandleRerolls(m_dice);
        }
        else break;

        ++rollNum;
    }

    // Player stood (or reached 3rd roll), so no dice can be rerolled.
    m_dice->LockAllDice();  

    // Make player list scoring categories and choose from them.
    availableCategories = m_player->ListAvailableCategories(*m_strat, m_dice);
    m_player->ChooseCategory(m_scorecard, a_roundNum, *m_strat, availableCategories, m_dice);

    // Unlock dice in preparation for next turn.
    m_dice->UnlockAllDice();
};