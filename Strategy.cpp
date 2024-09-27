#include "Strategy.h"
#include "Scorecard.h"


void Strategy::Print(bool suggest) const
{
    if (m_maxScore == 0)
    {
        if (suggest) 
        {
            cout << "I recommend that you stand because there are no fillable categories given your current dice set." << endl;
        }
        else 
        {
            cout << "The computer plans to stand because there are no fillable categories given its current dice set." << endl;
        }
    }
    else if (m_currentScore == m_maxScore)
    {
        if (suggest)
        {
            cout << "I recommend that you try for the " << m_categoryName << " category with your current dice set because it gives the maximum possible points (" << m_maxScore << ") among all the options." << endl;
        }
        else
        {
            cout << "The computer plans to stand and try for the " << m_categoryName << " category with its current dice set because it gives the maximum possible points (" << m_maxScore << ") among all the options." << endl;
        }
        
    }
    else
    {
        if (suggest)
        {
            cout << "I recommend that you try for the " << m_categoryName << " category with " << PrintTargetDice() << " because it gives the maximum possible points (" << m_maxScore << ") among all the options." << endl;
        }
        else
        {
            cout << "The computer plans to reroll to try for the " << m_categoryName << " category with " << PrintTargetDice() << " because it gives the maximum possible points (" << m_maxScore << ") among all the options." << endl;
        }
        
    }
};

void Strategy::Enact(Scorecard& a_scorecard, int a_round)
{
    // If this strategy is not scoring, do not fill any categories.
    if (!m_currentScore)
    {
        cout << "There is no way to score with the current dice set and open categories. Skipping turn." << endl << endl;
        return;
    }

    int categoryIndex = a_scorecard.GetCategoryIndex(m_categoryName);

    a_scorecard.FillCategory(categoryIndex, m_currentScore, a_round, "Computer");

    cout << "Filling the " << m_categoryName << " category with a score of " << m_currentScore << " points." << endl << endl;

    a_scorecard.Print();
}

string Strategy::PrintTargetDice() const
{
    string fullString = "";

    int diceCounted = 0;
    int totalDice = accumulate(m_targetDice.begin(), m_targetDice.end(), 0);

    for (int i = 0; i < 6; ++i)
    {
        int value = i + 1;
        int count = m_targetDice[i];
        diceCounted += count;

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
                if (count != 5) fullString += "and ";
                fullString += to_string(count) + " " + valueString;
                return fullString;
            }
            fullString += to_string(count) + " " + valueString + ", ";
        }
    }

    return fullString;
};