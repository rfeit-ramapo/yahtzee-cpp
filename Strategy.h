#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <numeric>
#include "Dice.h"

using namespace std;

// Forward declaration required to avoid circular dependencies.
class Scorecard;

class Strategy
{
    public:

        inline bool PlanToStand() const { return (m_maxScore == m_currentScore); }

        void Print(bool suggest) const;
        string GetString(bool suggest) const;

        void Enact(Scorecard& a_scorecard, int a_round);

        // Constructors
        Strategy() : m_currentScore(0), m_maxScore(0) {}; // Default

        // Build a strategy, with a type, current score, weighted score, and category.
        Strategy(
            int a_currentScore, 
            int a_maxScore, 
            const string a_categoryName
        ) : m_currentScore(a_currentScore), 
            m_maxScore(a_maxScore), 
            m_categoryName(a_categoryName) 
        {};

        Strategy(
            int a_currentScore, 
            int a_maxScore, 
            const string a_categoryName, 
            shared_ptr<const Dice> a_dice, 
            vector<int> a_targetDice, 
            vector<int> a_rerollCounts
        ) : m_currentScore(a_currentScore), 
            m_maxScore(a_maxScore), 
            m_categoryName(a_categoryName), 
            m_dice(a_dice), 
            m_targetDice(a_targetDice), 
            m_rerollCounts(a_rerollCounts) 
        {};

        // Getters
        inline int GetMaxScore() const { return m_maxScore; }
        inline int GetCurrentScore() const { return m_currentScore; }
        inline vector<int> GetRerollDice() const { return m_rerollCounts; }

        bool operator <(const Strategy& s) const { return (m_maxScore < s.m_maxScore); }
        bool operator ==(const Strategy& s) const { return (m_maxScore == s.m_maxScore); }
        bool operator >(const Strategy& s) const { return (m_maxScore > s.m_maxScore); }
        bool operator <=(const Strategy& s) const { return (*this <= s); }
        bool operator >=(const Strategy& s) const { return (*this >= s); }
        bool operator !=(const Strategy& s) const { return !(*this == s); }
    
    private:

        string PrintDice(vector<int> a_diceValues) const;

        int m_currentScore; // if this category is selected, the value it would give
        int m_maxScore; // maximum score possible for this category, given the diceset
        string m_categoryName; // the category this strategy is based on

        shared_ptr< const Dice> m_dice; // the set of dice this strategy is for
        vector<int> m_targetDice; // the desired dice face counts after enacting this strategy
        vector<int> m_rerollCounts; // how many dice of each face value to reroll
};