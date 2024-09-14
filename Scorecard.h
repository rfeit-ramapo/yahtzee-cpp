#pragma once

#include <string>
#include <vector>
#include "Category.h"

using namespace std;

class Scorecard
{
    public:

        void FillCategory(int a_categoryIndex)
        {
            shared_ptr<Category> category = m_categories[a_categoryIndex];
            category->SetFull();
        };

        void FillCategory(int a_categoryIndex, int a_points, int a_round, string a_winner)
        {
            shared_ptr<Category> category = m_categories[a_categoryIndex];
            category->SetFull();
            category->SetPoints(a_points);
            category->SetRound(a_round);
            category->SetWinner(a_winner);
        };

        // Constructors
        Scorecard() {}; // Default

        // Getters
        const vector<shared_ptr<Category>>& GetCategories() const
        {
            return m_categories;
        }

        shared_ptr<const Category> GetCategory(int a_index) const
        {
            return m_categories[a_index];
        }

    private:

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