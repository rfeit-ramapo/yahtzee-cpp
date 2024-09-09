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