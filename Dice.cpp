#include <random>
#include <iostream>
#include "Dice.h"


vector<int> Dice::ListToCount(vector<int> a_diceList)
{
    vector<int> diceCount(6,0);
    for (int i = 0; i < a_diceList.size(); ++i)
    {
        ++diceCount[a_diceList[i] - 1];
    }
    return diceCount;
}

vector<int> Dice::CountToList(vector<int> a_diceCount)
{
    vector<int> diceList;
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < a_diceCount[i]; ++j)
        {
            diceList.push_back(i + 1);
        }
    }
    return diceList;
}

bool Dice::LockDice(vector<int> a_keptDice)
{
    vector<int> newLocked(6,0);
    for (int i = 0; i < 6; ++i)
    {
        int numToLock = m_diceCount[i] - a_keptDice[i];
        if (numToLock < m_locked[i])
        {
            cerr << "Error: Input must be dice that were rolled and that have not already been set aside. Please try again." << endl;
            return false;
        }
        newLocked[i] = numToLock;
    }
    m_locked = newLocked;
    return true;
}

vector<int> Dice::RollAll()
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

bool Dice::ManualRoll(vector<int> a_input)
{
    // Make the dice match
    m_diceCount = m_locked;
    m_diceList = CountToList(m_locked);
    m_diceList.insert(m_diceList.end(), a_input.begin(), a_input.end());
    
    for (int i = 0; i < a_input.size(); ++i)
    {
        ++m_diceCount[m_diceList[i] - 1];
    }

    return true;
}

vector<int> Dice::RerollToMatch(const vector<int>& target) const
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

vector<int> Dice::GetUnlockedUnscored(const vector<int>& required) const
{
    vector<int> unlockedUnscored = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 6; ++i)
    {
        unlockedUnscored[i] = max(m_diceCount[i] - max(required[i], m_locked[i]), 0);
    }
    return unlockedUnscored;
}

vector<int> Dice::GetFreeDice() const
{
    vector<int> freeDice;
    for (int i = 0; i < 6; ++i)
    {
        freeDice.push_back(m_diceCount[i] - m_locked[i]);
    }
    return freeDice;
}

void Dice::Print() const
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

int Dice::GenerateDieValue()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(1, 6);
    return distribution(gen);
};