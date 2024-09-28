#include "Strategy.h"
#include "Scorecard.h"


void Strategy::Print(bool suggest) const
{
    cout << GetString(suggest);
};

string Strategy::GetString(bool suggest) const
{
    string stratString = "";
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
    else
    {
        // Calculate which dice should be set aside (in addition to what is already locked).
        vector<int> currentFreeDice = m_dice->GetFreeDice();
        vector<int> setAside(6, 0);
        bool lockNew = false;

        for (int i = 0; i < 6; ++i)
        {
            if (currentFreeDice[i] - m_rerollCounts[i] > 0) lockNew = true;
            setAside[i] = currentFreeDice[i] - m_rerollCounts[i];
        }

        if (suggest)
        {
            stratString = "I recommend that you try for the " + m_categoryName + " category with " + PrintDice(m_targetDice) + " because it gives the maximum possible points (" + to_string(m_maxScore) + ") among all the options.\n";
            if (lockNew)
            {
                stratString += "Therefore, " + PrintDice(setAside) + " should be set aside.\n";
            }
        }
        else
        {
            stratString = "The computer plans to reroll to try for the " + m_categoryName + " category with " + PrintDice(m_targetDice) + " because it gives the maximum possible points (" + to_string(m_maxScore) + ") among all the options.\n";
            if (lockNew)
            {
                stratString += "Therefore, " + PrintDice(setAside) + " will be set aside.\n";
            }
        }
    }
    return stratString;
}

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

string Strategy::PrintDice(vector<int> a_diceValues) const
{
    string fullString = "";

    int diceCounted = 0;
    int totalDice = accumulate(a_diceValues.begin(), a_diceValues.end(), 0);
    bool multipleFaces = false;

    for (int i = 0; i < 6; ++i)
    {
        int value = i + 1;
        int count = a_diceValues[i];
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