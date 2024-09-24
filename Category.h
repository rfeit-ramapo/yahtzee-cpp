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
        virtual Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice) const { return Strategy(); };

        // Constructors
        Category() {}; // Default

        Category(string a_name, string a_description, string a_score):
        m_name(a_name), m_description(a_description), m_score(a_score)
        {};

        Category(string a_name, string a_description, string a_score, string a_winner, int a_points, int a_round):
        m_name(a_name), m_description(a_description), m_score(a_score), m_winner(a_winner), m_points(a_points), m_round(a_round)
        {};

        // Getters
        inline string const GetName() const { return m_name; };
        inline string const GetDescription() const { return m_description; };
        inline string const GetWinner() const { return m_winner; };
        inline string const GetScore() const { return m_score; };
        inline int GetPoints() const { return m_points; };
        inline int GetRound() const { return m_round; };

        // Setters
        inline void const SetWinner(string a_winner) { m_winner = a_winner; }
        inline void const SetPoints(int a_points) { m_points = a_points; }
        inline void const SetRound(int a_round) { m_round = a_round; }
        inline void const SetFull() { m_full = true; }

    protected:
        bool m_full;

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
        int Score(const Dice& a_dice) const { return (a_dice.GetDiceCount()[m_multipleIndex] * (m_multipleIndex + 1)); }

        // Function to determine how to achieve this category, given current diceset
        Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice) const
        {
            // Return a default, 0 score strategy if this category has already been filled.
            if (m_full) return Strategy();

            // Get the current score value of the dice set
            int currentScore = Score(*a_dice);
            vector<int> currentDiceCounts = a_dice->GetDiceCount();

            // Find all unlocked, non-scoring dice
            vector<int> perfectScore(6, 0);
            perfectScore[m_multipleIndex] = 5;
            vector<int> unlockedUnscored = a_dice->GetUnlockedUnscored(perfectScore);
            int rerolledDice = accumulate(unlockedUnscored.begin(), unlockedUnscored.end(), 0);

            perfectScore[m_multipleIndex] = currentDiceCounts[m_multipleIndex] + rerolledDice;

            // Stand if there are no possible dice to reroll
            int maxScore = currentScore + (m_multipleIndex + 1) * rerolledDice;
            if (!rerolledDice) return Strategy(currentScore, maxScore, GetName());
            else return Strategy(currentScore, maxScore, GetName(), a_dice, perfectScore, unlockedUnscored);
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
            for (int i = 0; i < 6; ++i)
            {
                score += diceValues[i] * (i + 1);
                if (diceValues[i] >= m_numKind) condition_met = true;
            }
            return score * condition_met;
        }
        int Score(const vector<int>& diceValues) const
        {
            bool condition_met = false;
            int score = 0;
            for (int i = 0; i < 6; ++i)
            {
                score += diceValues[i] * (i + 1);
                if (diceValues[i] >= m_numKind) condition_met = true;
            }
            return score * condition_met;
        }

        // Function to determine how to achieve this category, given current diceset
        Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice) const
        {
            if (m_full) return Strategy();

            // Get the current score value of the dice set
            int currentScore = Score(*a_dice);

            const vector<int> &diceValues = a_dice->GetDiceCount();
            vector<int> idealDice;

            vector<int> toReroll;
            vector<int> rerollable;
            for (int i = 5; i >= 0; --i)
            {
                vector<int> minimumScore(6, 0);
                minimumScore[i] = m_numKind;
                rerollable = a_dice->GetUnlockedUnscored(minimumScore);
                int rerollableNum = accumulate(rerollable.begin(), rerollable.end(), 0);

                idealDice = a_dice->GetLockedDice();
                idealDice[i] = diceValues[i];
                for (int j = 0; j < 6; ++j)
                {
                    rerollableNum = rerollable[j];
                    while (rerollableNum && (idealDice[i] < m_numKind) )
                    {
                        rerollableNum--;
                        idealDice[i]++;
                    }
                    while (rerollableNum)
                    {
                        rerollableNum--;
                        idealDice[5]++;
                    }
                }

                if (idealDice[i] >= m_numKind)
                {
                    rerollable = a_dice->GetUnlockedUnscored(idealDice);
                    int maxScore = Score(idealDice);
                    return Strategy(currentScore, maxScore, GetName(), a_dice, idealDice, rerollable);
                }
            }

            // If no face values returned, this means it is impossible to get this category
            return Strategy();

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
            for (int i = 0; i < 6; i++)
            {
                if (diceValues[i] >= 1) streak++;
                else streak = 0;
            }
            if (streak >= m_streakNum) return m_scoreValue;
            else return 0;
        }

        // Function to determine how to achieve this category, given current diceset
        Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice) const
        {
            if (m_full) return Strategy();

            // Get the current score value of the dice set
            int currentScore = Score(*a_dice);

            // If this scores, stand because you always get maximum points in this category
            if (currentScore) return Strategy(currentScore, currentScore, GetName());

            // If this doesn't score, decide which to reroll
            // There are only a set few minimum values for 4 and 5 straight
            // Add each to a vector to check if getting any is possible
            vector<vector<int>> dicesetsToCheck;

            if (m_streakNum == 4)
            {
                dicesetsToCheck.push_back({0, 1, 1, 1, 1, 0});
                dicesetsToCheck.push_back({1, 1, 1, 1, 0, 0});
                dicesetsToCheck.push_back({0, 0, 1, 1, 1, 1});
            }
            else if (m_streakNum == 5)
            {
                dicesetsToCheck.push_back({0, 1, 1, 1, 1, 1});
                dicesetsToCheck.push_back({1, 1, 1, 1, 1, 0});
            }

            // Check Straight restrictions

            int minRerollNum = 0; // Current minimum number of rerolls required
            const vector<int> &diceValues = a_dice->GetDiceCount();
            vector<int> toReroll; // The dice to reroll 
            vector<int> idealDice; // Target set of dice after reroll
            vector<int> lockedDice = a_dice->GetLockedDice(); // Dice that are locked in place

            // Go through each possible configuration to check which is best/possible
            for (int i = 0; i < dicesetsToCheck.size(); ++i)
            {
                // Start the attempt with required (locked) dice
                vector<int> straightAttempt = lockedDice; 

                // Find all non-contributing dice and add them up
                vector<int> checkRerolls = a_dice->GetUnlockedUnscored(dicesetsToCheck[i]);
                /* delete me
                cout << "diceValues: ";
                for (int i = 0; i < 6; ++i)
                {
                    cout << a_dice->GetDiceCount()[i] << " ";
                }
                cout << endl;
                cout << "unlocked unscored: ";
                for (int i = 0; i < 6; ++i)
                {
                    cout << checkRerolls[i] << " ";
                }
                cout << endl;
                */
                int rerollsAvailable = accumulate(checkRerolls.begin(), checkRerolls.end(), 0);

                // Go through each face
                int rerollsNeeded = 0;
                for (int j = 0; j < 6; ++j)
                {
                    // If locked dice does not already include this face, but the config does 
                    if (diceValues[j] < dicesetsToCheck[i][j])
                    {
                        // Use a reroll to try and fill this hole
                        rerollsNeeded++;
                        straightAttempt[j]++;
                        // If we ran out of rerolls, this is not viable
                        if (rerollsNeeded > rerollsAvailable) break;
                    }
                    // If there are enough dice of this face, keep the minimum required
                    else if (dicesetsToCheck[i][j]) 
                    {
                        straightAttempt[j] = max(1, straightAttempt[j]);
                    }
                }

                // Ran out of rerolls, so this configuration is impossible
                if (rerollsNeeded > rerollsAvailable) continue;

                // If an option has not been set, or this configuration requires fewer rerolls than before
                if (!minRerollNum || (minRerollNum > rerollsNeeded))
                {
                    // Set the new minimum rerolls, target dice config, and dice to reroll
                    minRerollNum = rerollsNeeded;
                    idealDice = straightAttempt;
                    toReroll = checkRerolls;
                }

            }

            // If there were no rerolls, this means that every config failed and this category is impossible given the current diceset.
            if (!minRerollNum) return Strategy();
            // Otherwise, return the best configuration found.
            return Strategy(currentScore, m_scoreValue, GetName(), a_dice, idealDice, toReroll);
        }


        // Constructors
        StraightCategory(string a_name, string a_description, string a_score, int a_streakNum, int a_scoreValue): Category(a_name, a_description, a_score), m_streakNum(a_streakNum), m_scoreValue(a_scoreValue) {};

        StraightCategory(string a_name, string a_description, string a_score, string a_winner, int a_points, int a_round, int a_streakNum, int a_scoreValue) : Category(a_name, a_description, a_score, a_winner, a_points, a_round), m_streakNum(a_streakNum), m_scoreValue(a_scoreValue)
        {};
        
    private:
        int m_streakNum;
        int m_scoreValue;
};

class FullHouseCategory : public Category
{
    public:

        // Function to calculate the score for this category
        int Score(const Dice& a_dice) const 
        { 
            const vector<int> &diceValues = a_dice.GetDiceCount();
            int condition1_met = false;
            int condition2_met = false;
            for (int i = 0; i < diceValues.size(); ++i)
            {
                if (diceValues[i] == 3) condition1_met = true;
                else if (diceValues[i] == 2) condition2_met = true;
            }
            return 25 * condition1_met * condition2_met;
        }

        Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice) const
        {
            if (m_full) return Strategy();

            // Get the current score value of the dice set
            int currentScore = Score(*a_dice);

            // If this scores, stand because you always get maximum points in this category
            if (currentScore) return Strategy(currentScore, currentScore, GetName());

            // Check locked dice to see if this strategy is possible
            vector<int> lockedDice = a_dice->GetLockedDice();
            int lockedFaces = 0; // Count the number of faces with locked dice
            int lockedMode1 = -1;
            int lockedMode2 = -1;
            int lockedMaxCount = 0;
            for (int i = 0; i < 6; ++i)
            {
                if (lockedDice[i])
                {
                    if (lockedFaces && (lockedDice[i] > lockedMaxCount))
                    {
                        lockedMaxCount = lockedDice[i];
                        lockedMode2 = lockedMode1;
                        lockedMode1 = i;
                    }
                    else lockedMode2 = i;
                    lockedFaces++;
                }
                // Impossible if a face has more than 3 locked dice
                if (lockedDice[i] > 3) return Strategy();
            }
            // Impossible if more than two face values have locked dice
            if (lockedFaces > 2) return Strategy();

            // 
            vector<int> idealDice(6, 0);

            // If there are locked dice, use those. Otherwise, find mode of other dice.
            int mode1;
            int mode2;
            int maxCount1 = 0;
            int maxCount2 = 0;

            const vector<int> &diceValues = a_dice->GetDiceCount();
            for (int i = 0; i < 6; ++i)
            {
                if (diceValues[i] > maxCount1)
                {
                    mode1 = i;
                    maxCount1 = diceValues[i];
                }
                else if (diceValues[i] > maxCount2)
                {
                    mode2 = i;
                    maxCount2 = diceValues[i];
                }
            }

            if ((lockedMode1 >= 0) && (diceValues[lockedMode1] == 3)) mode1 = lockedMode1;
            if (diceValues[lockedMode2])

            if (lockedMode1 >= 0)
            {
                if (lockedMode2 >= 0)
                {
                    mode1 = lockedMode1;
                    mode2 = lockedMode2;
                }
                else if (mode1 != lockedMode1)
                {
                    if (maxCount1 > lockedMaxCount) mode2 = lockedMode1;
                    else
                    {
                        mode2 = mode1;
                        mode1 = lockedMode1;
                    }
                }
            }

            idealDice[mode1] = 3;
            idealDice[mode2] = 2;

            vector<int> toReroll = a_dice->GetUnlockedUnscored(idealDice);

            return Strategy(currentScore, m_maxScore, GetName(), a_dice, idealDice, toReroll);
        }

        // Constructors
        FullHouseCategory(string a_name, string a_description, string a_score): Category(a_name, a_description, a_score) {};

        FullHouseCategory(string a_name, string a_description, string a_score, string a_winner, int a_points, int a_round) : Category(a_name, a_description, a_score, a_winner, a_points, a_round) {};
        
    
    private:

        static const int m_maxScore = 25;
};

class YahtzeeCategory : public Category
{
    public:

        // Function to calculate the score for this category
        int Score(const Dice& a_dice) const 
        { 
            const vector<int> &diceValues = a_dice.GetDiceCount();
            for (int i = 0; i < diceValues.size(); i++) 
                if (diceValues[i] == 5) return 50;
            
            return 0;
        }

        Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice) const
        {
            if (m_full) return Strategy();

            // Get the current score value of the dice set
            int currentScore = Score(*a_dice);

            // If this scores, stand because you always get maximum points in this category
            if (currentScore) return Strategy(currentScore, currentScore, GetName());

            // Check locked dice to see if this strategy is possible
            vector<int> lockedDice = a_dice->GetLockedDice();
            int lockedFaces = 0; // Count the number of faces with locked dice
            int lockedIndex = -1; // Set the index for the locked face
            for (int i = 0; i < 6; ++i)
            {
                if (lockedDice[i])
                {
                    lockedFaces++;
                    lockedIndex = i;
                }
            }
            // Impossible if more than one face value has locked dice
            if (lockedFaces > 1) return Strategy();

            // 
            vector<int> idealDice(6, 0);

            // If there are locked dice, use those. Otherwise, find mode of other dice.
            if (lockedIndex >= 0) idealDice[lockedIndex] = 5;
            else
            {
                int mode;
                int maxCount = 0;
                const vector<int> &diceValues = a_dice->GetDiceCount();
                for (int i = 0; i < 6; ++i)
                {
                    if (diceValues[i] > maxCount)
                    {
                        mode = i;
                        maxCount = diceValues[i];
                    }
                }
                idealDice[mode] = 5;
            }
            
            vector<int> toReroll = a_dice->GetUnlockedUnscored(idealDice);

            return Strategy(currentScore, m_maxScore, GetName(), a_dice, idealDice, toReroll);
        }

        // Constructors
        YahtzeeCategory(string a_name, string a_description, string a_score): Category(a_name, a_description, a_score) {};

        YahtzeeCategory(string a_name, string a_description, string a_score, string a_winner, int a_points, int a_round) : Category(a_name, a_description, a_score, a_winner, a_points, a_round) {};
    
    private:

        static const int m_maxScore = 50;
};