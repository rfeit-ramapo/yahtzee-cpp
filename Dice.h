#pragma once

#include <vector>

using namespace std;

class Dice
{
    public:

        inline int RollOne() { return GenerateDieValue(); }
        inline void LockAllDice() { m_locked = m_diceCount; }
        inline void UnlockAllDice() { m_locked = {0, 0, 0, 0, 0, 0}; }

        static vector<int> ListToCount(vector<int> a_diceList);
        static vector<int> CountToList(vector<int> a_diceCount);
        
        // Lock all dice except those specified to reroll.
        bool LockDice(vector<int> a_keptDice);

        vector<int> RollAll();
        bool ManualRoll(vector<int> a_input);

        // Returns a vector indicating which dice values to reroll to match the parameter.
        vector<int> RerollToMatch(const vector<int>& target) const;

        // Find unlocked, non-scoring dice
        // required paramter represents dice that would contribute to the score
        vector<int> GetUnlockedUnscored(const vector<int>& required) const;

        // Returns the number of dice of each face value that are NOT locked
        vector<int> GetFreeDice() const;

        void Print() const;

        // Getters
        inline vector<int> GetLockedDice() const { return m_locked; }
        inline vector<int> GetDiceCount() const { return m_diceCount; }

        // Constructors
        Dice() {}; // Default

        Dice(vector<int> a_diceCount) : m_diceCount(a_diceCount) {};

        Dice(
            vector<int> a_diceCount, 
            vector<int> a_locked
        ) : m_diceCount(a_diceCount), m_locked(a_locked) 
        {};

    private:
        int GenerateDieValue();

        vector<int> m_diceList = {1, 1, 1, 1, 1};
        vector<int> m_diceCount = {0, 0, 0, 0, 0, 0};
        vector<int> m_locked = {0, 0, 0, 0, 0, 0};

};