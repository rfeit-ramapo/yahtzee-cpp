#include "../include/Scorecard.h"
#include "../include/Player.h"

using namespace std;

/* *********************************************************************
Function Name: FillCategory
Purpose: Fills and enters info for a particular category
Parameters: 
            a_categoryIndex, the index of the category to fill
            a_points, the number of points scored
            a_round, the round this category was filled in
            a_winner, the name of the winner of this category
Return Value: none
Algorithm:
    1) Locates the desired category, then fills in info as required
    2) Increases numFilled variable for Scorecard
Reference: none
********************************************************************* */
void Scorecard::FillCategory(int a_categoryIndex, int a_points, int a_round, string a_winner)
{
    shared_ptr<Category> category = m_categories[a_categoryIndex];
    category->SetFull();
    category->SetPoints(a_points);
    category->SetRound(a_round);
    category->SetWinner(a_winner);

    m_numFilled++;
};

/* *********************************************************************
Function Name: FillMultiple
Purpose: Fills multiple categories at once
Parameters: 
            a_categoryIndices, a vector of indices of categories to fill
            a_scores, a vector of the number of points scored
            a_winner, the name of the winner of this category
            a_rounds, a vector of which rounds the categories were filled in
            a_humanPlayer, a pointer to the human player (so their score can be adjusted)
            a_pcPlayer, a pointer to the computer palyer (so their score can be adjusted)
Return Value: none
Algorithm:
    1) Loops through each category index provided
        2) Adds score to the human or computer player as needed
    3) Fills the category with corresponding info from each vector
Reference: none
********************************************************************* */
void Scorecard::FillMultiple
(
    vector<int> a_categoryIndices,
    vector<int> a_scores,
    vector<string> a_winners,
    vector<int> a_rounds,
    shared_ptr<Player> a_humanPlayer,
    shared_ptr<Player> a_pcPlayer
)
{
    for (int i = 0; i < a_categoryIndices.size(); ++i)
    {
        if (a_winners[i] == "Human") a_humanPlayer->AddScore(a_scores[i]);
        else a_pcPlayer->AddScore(a_scores[i]);
        FillCategory(a_categoryIndices[i], a_scores[i], a_rounds[i], a_winners[i]);
    }
}

/* *********************************************************************
Function Name: Print
Purpose: Prints the scorecard out
Parameters: None
Return Value: none
Algorithm:
    1) Prints the header
    2) Loop through each category
        3) Print basic info of each category
        4) Print info about who won the category, if applicable
Reference: none
********************************************************************* */
void Scorecard::Print() const
{
    cout << "Current Scorecard:" << endl;

    // Print the header
    cout 
        << setw(7) << left << "Index"
        << setw(17) << left << "Category" 
        << setw(40) << left << "Description"
        << setw(33) << left << "Score"
        << setw(10) << left << "Winner"
        << setw(8) << left << "Points"
        << setw(5) << left << "Round";

    cout << endl << "========================================================================================================================" << endl;
        
    // Loop through each category
    for (int i = 0; i < NUM_CATEGORIES; ++i)
    {
        cout 
            << setw(7) << left << (i + 1)
            << setw(17) << left << m_categories[i]->GetName() 
            << setw(40) << left << m_categories[i]->GetDescription() 
            << setw(33) << left << m_categories[i]->GetScore();
            
        // Only print out winning info if it has been filled

        if (!m_categories[i]->GetWinner().empty())
        {
            cout << setw(10) << left << m_categories[i]->GetWinner();
        }
        if (!(m_categories[i]->GetPoints() == 0))
        {
            cout << setw(8) << left << m_categories[i]->GetPoints();
        }
        if (!(m_categories[i]->GetRound() == 0))
        {
            cout << setw(5) << left << m_categories[i]->GetRound();
        }

        cout << endl;
    }
    cout << endl;
}