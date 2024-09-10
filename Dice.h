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
                rerollValues[i] = max(m_diceCount[i] - target[i], 0);
            }
            return rerollValues;
        }

        // Getters
        const vector<int>& GetDiceCount() const { return m_diceCount; }

        // Constructors
        Dice() {}; // Default

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