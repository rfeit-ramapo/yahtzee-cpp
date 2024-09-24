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

        // Lock all dice except those specified to reroll.
        void LockDice(vector<int> a_keptDice)
        {
            // delete comments
            //cout << "locking dice... ";
            for (int i = 0; i < 6; ++i)
            {
                m_locked[i] = m_diceCount[i] - a_keptDice[i];
                //cout << m_locked[i] << " ";
            }
        }

        inline void LockAllDice() { m_locked = m_diceCount; }
        inline void UnlockAllDice() { m_locked = {0, 0, 0, 0, 0, 0}; }

        vector<int> RollAll()
        {
            m_diceCount = m_locked;
            vector<int> lockedRemaining = m_locked; // keep track of how many locked dice remain
            for (int i = 0; i < 5; ++i) 
            {
                if (lockedRemaining[(m_diceList[i] - 1)])
                {
                    --lockedRemaining[(m_diceList[i] - 1)];
                    continue;
                }
                m_diceList[i] = GenerateDieValue();
                m_diceCount[(m_diceList[i] - 1)] += 1;
            }
            return m_diceList;
        }

        // Returns a vector indicating which dice values to reroll to match the parameter.
        vector<int> RerollToMatch(const vector<int>& target) const
        {
            vector<int> rerollValues = {0, 0, 0, 0, 0, 0};
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
            vector<int> unlockedUnscored = {0, 0, 0, 0, 0, 0};
            for (int i = 0; i < 6; ++i)
            {
                unlockedUnscored[i] = max(m_diceCount[i] - max(required[i], m_locked[i]), 0);
            }
            return unlockedUnscored;
        }

        const vector<int> GetLockedDice() const { return m_locked; }

        // Returns the number of dice of each face value that are NOT locked
        vector<int> GetFreeDice() const
        {
            vector<int> freeDice;
            for (int i = 0; i < 6; ++i)
            {
                freeDice.push_back(m_diceCount[i] - m_locked[i]);
            }
            return freeDice;
        }

        void Print() const
        {
            #define RESET   "\033[0m"
            #define RED     "\033[31m"

            vector<int> lockedRemaining = m_locked; // keep track of how many locked dice remain
            for (int i = 0; i < 5; ++i) 
            {
                if (lockedRemaining[(m_diceList[i] - 1)])
                {
                    --lockedRemaining[(m_diceList[i] - 1)];
                    cout << RED << m_diceList[i] << RESET << " ";
                }
                else
                {
                    cout << m_diceList[i] << " ";
                }
            }
            cout << endl;
        }

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
        vector<int> m_diceCount = {0, 0, 0, 0, 0, 0};
        vector<int> m_locked = {0, 0, 0, 0, 0, 0};

};