#pragma once

#include <string>
#include <vector>
#include <iomanip>
#include "Category.h"

class Player; // Forward declaration

using namespace std;

class Scorecard
{
    public:

        // for temporary testing purposes
        void FillCategory(int a_categoryIndex);

        void FillCategory(int a_categoryIndex, int a_points, int a_round, string a_winner);

        // print a basic scorecard, with just the number and category name
        void PrintBasic() const;

        void Print() const;

        // Constructors
        Scorecard() {}; // Default

        void FillMultiple
        (
            vector<int> a_categoryIndices,
            vector<int> a_scores,
            vector<string> a_winners,
            vector<int> a_rounds,
            shared_ptr<Player> a_humanPlayer,
            shared_ptr<Player> a_pcPlayer
        );

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