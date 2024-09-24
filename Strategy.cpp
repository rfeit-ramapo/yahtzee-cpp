#include "Strategy.h"
#include "Scorecard.h"

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