#include "Scorecard.h"
#include "Player.h"

using namespace std;

void Scorecard::FillCategory(int a_categoryIndex)
{
    shared_ptr<Category> category = m_categories[a_categoryIndex];
    category->SetFull();

    m_numFilled++;
};

void Scorecard::FillCategory(int a_categoryIndex, int a_points, int a_round, string a_winner)
{
    shared_ptr<Category> category = m_categories[a_categoryIndex];
    category->SetFull();
    category->SetPoints(a_points);
    category->SetRound(a_round);
    category->SetWinner(a_winner);

    m_numFilled++;
};

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

void Scorecard::PrintBasic() const
{
    cout << "Basic Scorecard:" << endl;
    for (int i = 0; i < m_categories.size(); ++i)
    {
        cout << setw(4) << left << (i + 1) << setw(16) << left << m_categories[i]->GetName() << endl;
    }
    cout << endl;
}

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
        
    for (int i = 0; i < m_categories.size(); ++i)
    {
        cout 
            << setw(7) << left << (i + 1)
            << setw(17) << left << m_categories[i]->GetName() 
            << setw(40) << left << m_categories[i]->GetDescription() 
            << setw(33) << left << m_categories[i]->GetScore();
            
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