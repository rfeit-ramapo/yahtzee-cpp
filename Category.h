#pragma once

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include "Strategy.h"

using namespace std;

class Category
: public enable_shared_from_this<Category>
{
    public:

        // Function to calculate the score for this category
        virtual int Score(const Dice &a_dice) const {};

        // Function to determine how to achieve this category, given current diceset
        virtual Strategy GetRerollStrategy(const Dice &a_dice, int a_numRerolls) const { return Strategy(); };

        // Constructors
        Category() {}; // Default

        Category(string a_name, string a_description, string a_score):
        m_name(a_name), m_description(a_description), m_score(a_score)
        {};

        Category(string a_name, string a_description, string a_score, string a_winner, int a_points, int a_round):
        m_name(a_name), m_description(a_description), m_score(a_score), m_winner(a_winner), m_points(a_points), m_round(a_round)
        {};

        // Getters
        inline string const GetName() { return m_name; };

        // Setters
        inline void const SetWinner(string a_winner) { m_winner = a_winner; }
        inline void const SetPoints(int a_points) { m_points = a_points; }
        inline void const SetRound(int a_round) { m_round = a_round; }

    protected:
        int m_full;

    private:
        string m_name;
        string m_description;
        string m_score;
        string m_winner;
        int m_points;
        int m_round;
};

// Class for Aces, Twos, Threes, Fours, Fives, and Sixes
class MultiplesCategory : public Category
{
    public:
        // Function to calculate the score for this category
        int Score(const Dice& a_dice) const { return a_dice.GetDiceCount()[m_multipleIndex]; }

        // Function to determine how to achieve this category, given current diceset
        Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice, int a_numRerolls) const
        {
            // Return a default, 0 score strategy if this category has already been filled.
            if (m_full) return Strategy();

            // If this is the max value for aces already, you should stand.
            int currentScore = Score(*a_dice);
            int maxScore = (m_multipleIndex + 1) * 5;
            if (currentScore == maxScore) return StandStrategy(currentScore, shared_from_this());
            
            // If this set of dice already scores, the best strategy is to reroll nonmatching dice.
            if (currentScore)
            {
                vector<int> rerollCounts(6, 0);
                rerollCounts[m_multipleIndex] = 5;
                rerollCounts = a_dice->RerollToMatch(rerollCounts);

                // Weigh scores based on how many dice are saved. More rerolls = lower weight.
                double keptDiceFraction = (double) accumulate(rerollCounts.begin(), rerollCounts.end(), 0) / 5;
                double weightedScore = (double) maxScore * keptDiceFraction;

                return RerollStrategy(currentScore, weightedScore, shared_from_this(), a_dice, rerollCounts);

            }
            else
            return RerollStrategy(0, shared_from_this(), a_dice);
        };

        // Constructors
        MultiplesCategory(string a_name, string a_description, string a_score, int a_multipleNumber): Category(a_name, a_description, a_score), m_multipleIndex(a_multipleNumber - 1) {};

        MultiplesCategory(string a_name, string a_description, string a_score, string a_winner, int a_points, int a_round, int a_multipleNumber) : Category(a_name, a_description, a_score, a_winner, a_points, a_round), m_multipleIndex(a_multipleNumber - 1)
        {};

        private:
            int m_multipleIndex;
};

class StraightCategory : public Category
{
    public:

        // Function to calculate the score for this category
        int Score(const Dice& a_dice) const 
        { 
            const vector<int> &diceValues = a_dice.GetDiceCount();
            int streak = 0;
            for (int i = 0; i < diceValues.size(); i++)
            {
                if (diceValues[i] >= 1) streak++;
                else streak = 0;
            }
            if (streak >= m_numRepeats) return m_scoreValue;
            else return 0;
        }

        // Function to determine how to achieve this category, given current diceset
        Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice, int a_numRerolls) const
        {

        }


        // Constructors
        StraightCategory(string a_name, string a_description, string a_score, int a_numRepeats, int a_scoreValue): Category(a_name, a_description, a_score), m_numRepeats(a_numRepeats), m_scoreValue(a_scoreValue) {};

        StraightCategory(string a_name, string a_description, string a_score, string a_winner, int a_points, int a_round, int a_numRepeats, int a_scoreValue) : Category(a_name, a_description, a_score, a_winner, a_points, a_round), m_numRepeats(a_numRepeats), m_scoreValue(a_scoreValue)
        {};
        
    private:
        int m_numRepeats;
        int m_scoreValue;
};