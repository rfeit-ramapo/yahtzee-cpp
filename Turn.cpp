#include "Turn.h"

void Turn::Play(int a_roundNum)
{            
    cout << "=================================" << endl;
    cout << "Turn -- " << m_player->GetLogName() << endl;

    // Up to two rerolls allowed.
    bool stand = false;
    int rollNum = 1;
    vector<int> availableCategories;

    while (!stand)
    {
        // Roll and print the dice.
        cout << "=================================" << endl;
        cout << "Roll " << rollNum << endl;
        m_player->RollAll(*m_dice);
        cout << "Roll result: ";
        m_dice->Print();

        if (rollNum < 3) 
        {
            // List all scorecard categories available, given the dice set so far.
            availableCategories = m_player->ListAvailableCategories(*m_strat, m_dice);

            // List the category or categories that the player wants to pursue.
            m_player->PursueCategories(*m_strat, availableCategories, m_dice);

            // State whether the player wants to roll again or stand after rolls 1 and 2.
            stand = m_player->HandleRerolls(m_dice);
        }
        else 
        {
            break;
        }

        ++rollNum;
    }

    // Announce the category filled, if any, and score earned.
    // Enter the player name, score, and round number into the scorecard.
    m_dice->LockAllDice();  // Player stood, so no dice can be rerolled.
    availableCategories = m_player->ListAvailableCategories(*m_strat, m_dice);
    // todo: decide whether to actually make the player list categories now
    m_player->ChooseCategory(m_scorecard, a_roundNum, *m_strat, availableCategories, m_dice);
    m_dice->UnlockAllDice();
};