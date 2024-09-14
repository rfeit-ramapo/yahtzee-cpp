#pragma once

#include <vector>
#include <random>

using namespace std;

class Dice
{
    public:

        int RollOne() { return GenerateDieValue(); }

        vector<int> RollSome(vector<int> a_indices)
        {
            for (int i : a_indices) 
            {
                m_diceCount[(m_diceList[i] - 1)] -= 1;
                m_diceList[i] = GenerateDieValue();
                m_diceCount[(m_diceList[i] - 1)] += 1;
            }
            return m_diceList;
        }

        vector<int> RollAll()
        {
            m_diceCount = {0, 0, 0, 0, 0};
            for (int i; i < m_diceList.size(); ++i) 
            {
                m_diceList[i] = GenerateDieValue();
                m_diceCount[(m_diceList[i] - 1)] += 1;
            }
            return m_diceList;
        }

        // Returns a vector indicating which dice values to reroll to match the parameter.
        vector<int> RerollToMatch(const vector<int>& target) const
        {
            vector<int> rerollValues(6);
            for (int i = 0; i < m_diceCount.size(); ++i)
            {
                // Return negative values if this is impossible to achieve
                if (m_locked[i] > target[i]) return {-1, -1, -1, -1, -1, -1};
                rerollValues[i] = max(m_diceCount[i] - target[i], 0);
            }
            return rerollValues;
        }

        // Find unlocked, non-scoring dice
        // required paramter represents dice that would contribute to the score
        vector<int> GetUnlockedUnscored(const vector<int>& required) const
        {
            vector<int> unlockedUnscored(6);
            for (int i = 0; i < m_diceCount.size(); ++i)
            {
                unlockedUnscored[i] = max(m_diceCount[i] - max(required[i], m_locked[i]), 0);
            }
            return unlockedUnscored;
        }

        const vector<int> GetLockedDice() const { return m_locked; }

        // Getters
        const vector<int>& GetDiceCount() const { return m_diceCount; }

        // Constructors
        Dice() {}; // Default

        Dice(vector<int> a_diceCount) : m_diceCount(a_diceCount) {};

        Dice(vector<int> a_diceCount, vector<int> a_locked) : m_diceCount(a_diceCount), m_locked(a_locked) {};

    private:
        int GenerateDieValue()
        {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distribution(1, 6);
            return distribution(gen);
        };

        vector<int> m_diceList = {1, 1, 1, 1, 1};
        vector<int> m_diceCount = {0, 0, 0, 0, 0};
        vector<int> m_locked = {0, 0, 0, 0, 0};

};