#pragma once

#include <string>
#include <vector>
#include "Category.h"

using namespace std;

class Scorecard
{
    public:
        // Constructors
        Scorecard() {}; // Default

        // Getters
        const vector<Category> GetCategories()
        {
            return m_categories;
        }

        const Category GetCategory(int a_index)
        {
            return m_categories[a_index];
        }

    private:

        static int full_house (const vector<int> &diceValues)
        {
            int condition1_met = false;
            int condition2_met = false;
            for (int i = 0; i < diceValues.size(); ++i)
            {
                if (diceValues[i] == 3) condition1_met = true;
                else if (diceValues[i] == 2) condition2_met = true;
            }
            return 25 * condition1_met * condition2_met;
        }

        static int four_straight (const vector<int> &diceValues)
        {
            int streak = 0;
            for (int i = 0; i < diceValues.size(); i++)
            {
                if (diceValues[i] >= 1) streak++;
                else streak = 0;
            }
            if (streak >= 4) return 30;
            else return 0;
        }

        static int five_straight (const vector<int> &diceValues)
        {
            int streak = 0;
            for (int i = 0; i < diceValues.size(); i++)
            {
                if (diceValues[i] >= 1) streak++;
                else streak = 0;
            }
            if (streak == 5) return 40;
            else return 0;
        }

        static int yahtzee(const vector<int> &diceValues)
        {
            for (int i = 0; i < diceValues.size(); i++) 
                if (diceValues[i] == 5) return 50;
            
            return 0;
        }

        vector<Category> m_categories = 
        {
            MultiplesCategory("Aces", "Any combination", "Sum of dice with the number 1", 1),
            MultiplesCategory("Twos", "Any combination", "Sum of dice with the number 2", 2),
            MultiplesCategory("Threes", "Any combination", "Sum of dice with the number 3", 3),
            MultiplesCategory("Fours", "Any combination", "Sum of dice with the number 4", 4),
            MultiplesCategory("Fives", "Any combination", "Sum of dice with the number 5", 5),
            MultiplesCategory("Sixes", "Any combination", "Sum of dice with the number 6", 6),
            KindCategory("Three of a Kind", "At least three dice the same", "Sum of all the dice", 3),
            KindCategory("Four of a Kind", "At least four dice the same", "Sum of all the dice", 4),
            Category("Full House", "Three of one number and two of another", "25"),
            Category("Four Straight", "Four sequential dice", "30"),
            Category("Five Straight", "Five sequential dice", "40"),
            Category("Yahtzee", "All five dice the same", "50")
        };

};