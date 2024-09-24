#pragma once

#include <string>
#include <vector>
#include <iomanip>
#include "Category.h"

using namespace std;

class Scorecard
{
    public:

        // for temporary testing purposes
        void FillCategory(int a_categoryIndex)
        {
            shared_ptr<Category> category = m_categories[a_categoryIndex];
            category->SetFull();

            m_numFilled++;
        };

        void FillCategory(int a_categoryIndex, int a_points, int a_round, string a_winner)
        {
            shared_ptr<Category> category = m_categories[a_categoryIndex];
            category->SetFull();
            category->SetPoints(a_points);
            category->SetRound(a_round);
            category->SetWinner(a_winner);

            m_numFilled++;
        };

        // print a basic scorecard, with just the number and category name
        void PrintBasic() const
        {
            cout << "Basic Scorecard:" << endl;
            for (int i = 0; i < m_categories.size(); ++i)
            {
                cout << setw(4) << left << (i + 1) << setw(16) << left << m_categories[i]->GetName() << endl;
            }
            cout << endl;
        }

        void Print() const
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

        // Constructors
        Scorecard() {}; // Default

        // Getters
        inline const vector<shared_ptr<Category>>& GetCategories() const
        {
            return m_categories;
        }

        inline shared_ptr<const Category> GetCategory(int a_index) const
        {
            return m_categories[a_index];
        }
        
        inline int GetCategoryIndex(string a_categoryName) const
        {
            for (int i = 0; i < m_categories.size(); ++i)
            {
                if (a_categoryName == m_categories[i]->GetName())
                {
                    return i;
                }
            }

            return -1;
        }

        inline bool IsFull() const
        {
            return (m_numFilled == m_categories.size());
        }

    private:

        int m_numFilled = 0;

        vector<shared_ptr<Category>> m_categories = 
        {
            make_shared<MultiplesCategory>("Aces", "Any combination", "Sum of dice with the number 1", 1),
            make_shared<MultiplesCategory>("Twos", "Any combination", "Sum of dice with the number 2", 2),
            make_shared<MultiplesCategory>("Threes", "Any combination", "Sum of dice with the number 3", 3),
            make_shared<MultiplesCategory>("Fours", "Any combination", "Sum of dice with the number 4", 4),
            make_shared<MultiplesCategory>("Fives", "Any combination", "Sum of dice with the number 5", 5),
            make_shared<MultiplesCategory>("Sixes", "Any combination", "Sum of dice with the number 6", 6),
            make_shared<KindCategory>("Three of a Kind", "At least three dice the same", "Sum of all the dice", 3),
            make_shared<KindCategory>("Four of a Kind", "At least four dice the same", "Sum of all the dice", 4),
            make_shared<FullHouseCategory>("Full House", "Three of one number and two of another", "25"),
            make_shared<StraightCategory>("Four Straight", "Four sequential dice", "30", 4, 30),
            make_shared<StraightCategory>("Five Straight", "Five sequential dice", "40", 5, 40),
            make_shared<YahtzeeCategory>("Yahtzee", "All five dice the same", "50")
        };


};