#include "../include/Strategy.h"
#include "../include/Scorecard.h"

/* *********************************************************************
Function Name: GetString
Purpose: Creates a user-friendly string describing this strategy
Parameters: 
            suggest, a boolean indicating whether this is a suggestion for the user
Return Value: a string describing the strategy
Algorithm:
    1) Creates a string to hold the strategy info
    2) If the max score is zero, this strategy is for a dead-end dice set
    3) If the current score is the max score, print a stand strategy
    4) Otherwise, create a string explaining how to reroll for maximum points
Reference: none
********************************************************************* */
string Strategy::GetString(bool suggest) const
{
    string stratString = "";

    // Stand strategy - no fillable categories
    if (m_maxScore == 0)
    {
        if (suggest) 
        {
            stratString = "I recommend that you stand because there are no fillable categories given your current dice set.\n";
        }
        else 
        {
            stratString = "The computer plans to stand because there are no fillable categories given its current dice set.\n";
        }
    }

    // Stand strategy - already reached maximum score
    else if (m_currentScore == m_maxScore)
    {
        if (suggest)
        {
            stratString = "I recommend that you try for the " + m_categoryName + " category with your current dice set because it gives the maximum possible points (" + to_string(m_maxScore) + ") among all the options.\n";
        }
        else
        {
            stratString = "The computer plans to stand and try for the " + m_categoryName + " category with its current dice set because it gives the maximum possible points (" + to_string(m_maxScore) + ") among all the options.\n";
        }
        
    }

    // Reroll strategy - current score is not at its maximum potential
    else
    {
        if (suggest)
        {
            stratString = "I recommend that you try for the " + m_categoryName + " category with " + PrintDice(m_targetDice) + " because it gives the maximum possible points (" + to_string(m_maxScore) + ") among all the options. Therefore, " + PrintDice(m_rerollCounts) + " should be rerolled.\n";
            if (m_currentScore == 0)
            {
                stratString += "However, depending on dice rolls you may not be able to score in this category, so be cautious!\n";
            }
            else
            {
                stratString += "At minimum, you will score " + to_string(m_currentScore) + " points in this category.\n";
            }
        }
        else
        {
            stratString = "The computer plans to reroll to try for the " + m_categoryName + " category with " + PrintDice(m_targetDice) + " because it gives the maximum possible points (" + to_string(m_maxScore) + ") among all the options. Therefore, " + PrintDice(m_rerollCounts) + " will be rerolled.\n";
            if (m_currentScore != 0)
            {
                stratString += "At minimum, the computer will score " + to_string(m_currentScore) + " points in this category.\n";
            }
        }
    }
    return stratString;
}

/* *********************************************************************
Function Name: Enact
Purpose: Enacts this strategy for a Computer player by filling the scorecard
Parameters: 
            a_scorecard, a reference to the scorecard to update
            a_round, the current round number
Return Value: none
Algorithm:
    1) If attempting to enact an empty strategy, skip
    2) Get the category info and fill it via the scorecard
    3) Print the scorecard
Reference: none
********************************************************************* */
void Strategy::Enact(Scorecard& a_scorecard, int a_round)
{
    // If this strategy is not scoring, do not fill any categories.
    if (!m_currentScore)
    {
        cout << "There is no way to score with the current dice set and open categories. Skipping turn." << endl << endl;
        return;
    }

    // Fill the category with info
    int categoryIndex = a_scorecard.GetCategoryIndex(m_categoryName);
    a_scorecard.FillCategory(categoryIndex, m_currentScore, a_round, "Computer");
    cout << "Filling the " << m_categoryName << " category with a score of " << m_currentScore << " points." << endl << endl;

    a_scorecard.Print();
}

/* *********************************************************************
Function Name: PrintDice
Purpose: Gets a string listing dice counts in a user-friendly format
        (e.g. 1 Ace, 3 Twos, and 2 Sixes)
Parameters: 
            a_diceValues, a vector holding dice face counts
Return Value: a string listing the dice counts in a user-friendly format
Algorithm:
    1) Loops through each dice face and checks how many dice there are
    2) For each die, add on to the string (accounting for plurals)
    3) When all dice have been processed, ensure string ends properly (with or without "and")
    4) Return the built string
Reference: none
********************************************************************* */
string Strategy::PrintDice(vector<int> a_diceValues) const
{
    string fullString = "";

    int diceCounted = 0;
    int totalDice = accumulate(a_diceValues.begin(), a_diceValues.end(), 0);
    // Record if multiple faces were listed in order to determine if "and" is required
    bool multipleFaces = false;

    for (int i = 0; i < Dice::NUM_DICE_FACES; ++i)
    {
        int value = i + 1;
        int count = a_diceValues[i];
        diceCounted += count;

        // Switch string based on what face value this is
        string valueString;
        if (count)
        {
            switch (value)
            {
                case 1:
                    valueString = "Ace";
                    break;
                case 2:
                    valueString = "Two";
                    break;
                case 3:
                    valueString = "Three";
                    break;
                case 4:
                    valueString = "Four";
                    break;
                case 5:
                    valueString = "Five";
                    break;
                case 6:
                    valueString = "Six";
                    break;
            }

            // Account for plurals
            if (count > 1)
            {
                if (value == 6) valueString = "Sixes";
                else valueString += "s";
            }

            // If it's the last die in the list
            if (diceCounted == totalDice)
            {
                // Don't print 'and' if there was only one type of die
                if (multipleFaces) fullString += "and ";
                fullString += to_string(count) + " " + valueString;
                return fullString;
            }
            
            multipleFaces = true;
            fullString += to_string(count) + " " + valueString + ", ";
        }
    }
    return fullString;
};