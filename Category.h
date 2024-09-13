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
        virtual int Score(const Dice &a_dice) const { return 0; };

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

            // Get the current score value of the dice set
            int currentScore = Score(*a_dice);

            // Find all unlocked, non-scoring dice
            vector<int> perfectScore(6, 0);
            perfectScore[m_multipleIndex] = 5;
            vector<int> unlockedUnscored = a_dice->GetUnlockedUnscored(perfectScore);
            int rerolledDice = accumulate(unlockedUnscored.begin(), unlockedUnscored.end(), 0);

            // Stand if there are no possible dice to reroll
            if (!rerolledDice && currentScore)
            {
                return StandStrategy(currentScore, "you have achieved the maximum points possible in this category, given your dice set.", shared_from_this());
            }
            else
            {
                double keptDiceFraction = (double) (5 - rerolledDice) / 5;
                int maxScoreDiff = (m_multipleIndex + 1) * rerolledDice;
                double weightedScore = currentScore + ((double) maxScoreDiff * keptDiceFraction);

                string reasoning = "you can potentially achieve " + to_string(maxScoreDiff + currentScore) + " points in this category by rerolling these dice.";
                return RerollStrategy(currentScore, weightedScore, reasoning, shared_from_this(), a_dice, unlockedUnscored);
            }
        };

        // Constructors
        MultiplesCategory(string a_name, string a_description, string a_score, int a_multipleNumber): Category(a_name, a_description, a_score), m_multipleIndex(a_multipleNumber - 1) {};

        MultiplesCategory(string a_name, string a_description, string a_score, string a_winner, int a_points, int a_round, int a_multipleNumber) : Category(a_name, a_description, a_score, a_winner, a_points, a_round), m_multipleIndex(a_multipleNumber - 1)
        {};

        private:
            int m_multipleIndex;
};

class KindCategory : public Category
{
    public:

        // Function to calculate the score for this category
        int Score(const Dice& a_dice) const 
        {
            const vector<int> &diceValues = a_dice.GetDiceCount();
            bool condition_met = false;
            int score = 0;
            for (int i = 0; i < diceValues.size(); ++i)
            {
                score += diceValues[i] * i;
                if (diceValues[i] >= m_numKind) condition_met = true;
            }
            return score * condition_met;
        }

        // Function to determine how to achieve this category, given current diceset
        Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice, int a_numRerolls) const
        {
            // Get the current score value of the dice set
            int currentScore = Score(*a_dice);

            const vector<int> &diceValues = a_dice->GetDiceCount();

            int maxFace = 0;
            int maxDice = 0;
            vector<int> toReroll;
            int rerolledDice;
            // for (int i = 5; i >= 0; --i)
            for (int i = 0; i < diceValues.size(); ++i)
            {
                int myFace = i + 1;
                int myDice = diceValues[i];

                if (myDice >= maxDice) 
                {
                    vector<int> minimumScore(6, 0);
                    minimumScore[i] = m_numKind;
                    vector<int> rerollable = a_dice->GetUnlockedUnscored(minimumScore);
                    int rerollableTotal = accumulate(rerollable.begin(), rerollable.end(), 0);

                    if ((myDice + rerollableTotal) < m_numKind) continue;

                    myFace = maxFace;
                    maxDice = myDice;
                    toReroll = rerollable;
                    rerolledDice = rerollableTotal;
                }
            }

            // If maxFace is 0, this means it is impossible to get this category
            if (!maxFace) return Strategy();

            double keptDiceFraction = (double) (5 - rerolledDice) / 5;
            int maxScore = (maxFace * m_numKind) + (6 * (5 - m_numKind));
            int maxScoreDiff = maxScore - currentScore;
            double weightedScore = currentScore + ((double) maxScoreDiff * keptDiceFraction);

            string reasoning = "you can potentially achieve " + to_string(maxScore) + " points in this category by rerolling these dice.";
            return RerollStrategy(currentScore, weightedScore, reasoning, shared_from_this(), a_dice, toReroll);
        }


        // Constructors
        KindCategory(string a_name, string a_description, string a_score, int a_numKind): Category(a_name, a_description, a_score), m_numKind(a_numKind) {};

        KindCategory(string a_name, string a_description, string a_score, string a_winner, int a_points, int a_round, int a_numKind) : Category(a_name, a_description, a_score, a_winner, a_points, a_round), m_numKind(a_numKind)
        {};
        
    private:
        int m_numKind;
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
            if (streak >= m_streakNum) return m_scoreValue;
            else return 0;
        }

        // Function to determine how to achieve this category, given current diceset
        Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice, int a_numRerolls) const
        {
            return Strategy();
        }


        // Constructors
        StraightCategory(string a_name, string a_description, string a_score, int a_streakNum, int a_scoreValue): Category(a_name, a_description, a_score), m_streakNum(a_streakNum), m_scoreValue(a_scoreValue) {};

        StraightCategory(string a_name, string a_description, string a_score, string a_winner, int a_points, int a_round, int a_streakNum, int a_scoreValue) : Category(a_name, a_description, a_score, a_winner, a_points, a_round), m_streakNum(a_streakNum), m_scoreValue(a_scoreValue)
        {};
        
    private:
        int m_streakNum;
        int m_scoreValue;
};