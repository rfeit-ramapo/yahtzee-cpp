#pragma once

#include <iostream>
#include <string>
#include "Dice.h"

using namespace std;

// Forward declaration required for Category to avoid circular dependencies.
class Category;

class Strategy
{
    public:



        // print function goes here
        void Print()
        {
            if (m_maxScore == 0)
            {
                cout << "I recommend that you stand because there are no fillable categories given your current dice set." << endl;
            }
            else if (m_currentScore == m_maxScore)
            {
                cout << "I recommend that you try for the " << m_categoryName << " category with your current dice set because it gives the maximum possible points (" << m_maxScore << ") among all the options." << endl;
            }
            else
            {
                cout << "I recommend that you try for the " << m_categoryName << " category with " << PrintTargetDice() << " because it gives the maximum possible points (" << m_maxScore << ") among all the options." << endl;
            }
        };

        // Constructors
        Strategy() : m_currentScore(0), m_maxScore(0) {}; // Default

        // Build a strategy, with a type, current score, weighted score, and category.
        Strategy(int a_currentScore, int a_maxScore, const string a_categoryName) : m_currentScore(a_currentScore), m_maxScore(a_maxScore), m_categoryName(a_categoryName) {};

        Strategy(int a_currentScore, int a_maxScore, const string a_categoryName, shared_ptr<const Dice> a_dice, vector<int> a_targetDice, vector<int> a_rerollCounts) : m_currentScore(a_currentScore), m_maxScore(a_maxScore), m_categoryName(a_categoryName), m_dice(a_dice), m_targetDice(a_targetDice), m_rerollCounts(a_rerollCounts) {};

        bool operator <(const Strategy& s) const { return (m_maxScore < s.m_maxScore); }
        bool operator ==(const Strategy& s) const { return (m_maxScore == s.m_maxScore); }
        bool operator >(const Strategy& s) const { return (m_maxScore > s.m_maxScore); }
        bool operator <=(const Strategy& s) const { return (*this <= s); }
        bool operator >=(const Strategy& s) const { return (*this >= s); }
        bool operator !=(const Strategy& s) const { return !(*this == s); }
    
    private:

        string PrintTargetDice()
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

        int m_currentScore; // if this category is selected, the value it would give
        double m_maxScore; // maximum score possible for this category, given the diceset
        string m_categoryName; // the category this strategy is based on

        shared_ptr< const Dice> m_dice; // the set of dice this strategy is for
        vector<int> m_targetDice; // the desired dice face counts after enacting this strategy
        vector<int> m_rerollCounts; // how many dice of each face value to reroll
};