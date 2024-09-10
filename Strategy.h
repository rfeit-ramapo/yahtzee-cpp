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

        // Constructors
        Strategy() : m_currentScore(0), m_weightedScore(0) {}; // Default

        // Build a strategy, with a type, current score, weighted score, and category.
        Strategy(string a_type, int a_currentScore, double a_weightedScore, shared_ptr< const Category> a_categoryToPursue) : m_type(a_type), m_currentScore(a_currentScore), m_weightedScore(a_weightedScore),m_categoryToPursue(a_categoryToPursue) {};

        bool operator <(const Strategy& s) { return (m_weightedScore < s.m_weightedScore); }
        bool operator ==(const Strategy& s) { return (m_weightedScore == s.m_weightedScore); }
        bool operator >(const Strategy& s) { return (m_weightedScore > s.m_weightedScore); }
        bool operator <=(const Strategy& s) { return (m_weightedScore <= s.m_weightedScore); }
        bool operator >=(const Strategy& s) { return (m_weightedScore >= s.m_weightedScore); }
        bool operator !=(const Strategy& s) { return (m_weightedScore != s.m_weightedScore); }
    
    private:

        string m_type; // stand or reroll dice
        int m_currentScore; // if this category is selected, the value it would give
        double m_weightedScore; // score given weight based on chances of achieving
        shared_ptr< const Category> m_categoryToPursue; // the category this strategy is based on
};

class StandStrategy : public Strategy
{

    public:
        // Default
        StandStrategy() {};

        // 
        StandStrategy(int a_currentScore, shared_ptr< const Category> a_categoryToPursue)
            : Strategy("stand", a_currentScore, (double) a_currentScore, a_categoryToPursue) {};
};

class RerollStrategy : public Strategy
{

    public:
        // Default
        RerollStrategy() {};

        // Reroll all if no counts are specified. Also assumes currentScore is 0.
        RerollStrategy(double a_weightedScore, shared_ptr< const Category> a_categoryToPursue, shared_ptr< const Dice > a_dice)
            : Strategy("reroll", 0, a_weightedScore, a_categoryToPursue), m_dice(a_dice), m_rerollCounts(a_dice->GetDiceCount()) {};

        // Constructor that omits current score, as it's assumed to be 0.
        RerollStrategy(double a_weightedScore, shared_ptr< const Category> a_categoryToPursue, shared_ptr<const Dice> a_dice, vector<int> a_rerollCounts)
            : Strategy("reroll", 0, a_weightedScore, a_categoryToPursue), m_dice(a_dice), m_rerollCounts(a_rerollCounts) {};

        // Full constructor options
        RerollStrategy(int a_currentScore, double a_weightedScore, shared_ptr< const Category> a_categoryToPursue, shared_ptr<const Dice> a_dice, vector<int> a_rerollCounts)
            : Strategy("reroll", a_currentScore, a_weightedScore, a_categoryToPursue), m_dice(a_dice), m_rerollCounts(a_rerollCounts) {};

    private:
        shared_ptr< const Dice> m_dice; // the set of dice this strategy is for
        vector<int> m_rerollCounts; // how many dice of each face value to reroll
};