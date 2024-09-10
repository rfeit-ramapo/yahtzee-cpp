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

        static int aces (const vector<int> &diceValues) { return diceValues[0]; };
        static int twos (const vector<int> &diceValues) { return diceValues[1] * 2; };
        static int threes (const vector<int> &diceValues) { return diceValues[2] * 3; };
        static int fours (const vector<int> &diceValues) { return diceValues[3] * 4; };
        static int fives (const vector<int> &diceValues) { return diceValues[4] * 5; };
        static int sixes (const vector<int> &diceValues) { return diceValues[5] * 6; };

        static int three_kind (const vector<int> &diceValues)
        {
            int condition_met = 0;
            int score = 0;
            for (int i = 0; i < diceValues.size(); ++i)
            {
                score += diceValues[i] * i;
                if (diceValues[i] >= 3) condition_met = 1;
            }
            return score * condition_met;
        }

        static int four_kind (const vector<int> &diceValues)
        {
            int condition_met = 0;
            int score = 0;
            for (int i = 0; i < diceValues.size(); ++i)
            {
                score += diceValues[i] * i;
                if (diceValues[i] >= 4) condition_met = 1;
            }
            return score * condition_met;
        }

        static int full_house (const vector<int> &diceValues)
        {
            int condition1_met = 0;
            int condition2_met = 0;
            for (int i = 0; i < diceValues.size(); ++i)
            {
                if (diceValues[i] == 3) condition1_met = 1;
                else if (diceValues[i] == 2) condition2_met = 1;
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
            Category("Aces", "Any combination", "Sum of dice with the number 1", aces),
            Category("Twos", "Any combination", "Sum of dice with the number 2", twos),
            Category("Threes", "Any combination", "Sum of dice with the number 3", threes),
            Category("Fours", "Any combination", "Sum of dice with the number 4", fours),
            Category("Fives", "Any combination", "Sum of dice with the number 5", fives),
            Category("Sixes", "Any combination", "Sum of dice with the number 6", sixes),
            Category("Three of a Kind", "At least three dice the same", "Sum of all the dice", three_kind),
            Category("Four of a Kind", "At least four dice the same", "Sum of all the dice", four_kind),
            Category("Full House", "Three of one number and two of another", "25", full_house),
            Category("Four Straight", "Four sequential dice", "30", four_straight),
            Category("Five Straight", "Five sequential dice", "40", five_straight),
            Category("Yahtzee", "All five dice the same", "50", yahtzee)
        };

};