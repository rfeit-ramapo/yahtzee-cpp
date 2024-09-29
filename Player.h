#pragma once

#include <string>
#include "StrategyEngine.h"
#include "Dice.h"
#include "Input.h"

using namespace std;

class Player
{
    public:

        // Functions
        virtual int RollOne(Dice &dice) = 0;

        vector<int> RollAll(Dice &dice);

        virtual vector<int> ListAvailableCategories(
            const StrategyEngine& a_strat, 
            shared_ptr<const Dice> a_dice
        ) = 0;

        virtual void PursueCategories(
            const StrategyEngine& a_strat, 
            const vector<int>& a_availableCategories, 
            shared_ptr<const Dice> a_dice
        ) = 0;

        virtual bool HandleRerolls(shared_ptr<Dice> a_dice) = 0;

        virtual void ChooseCategory(
            shared_ptr<Scorecard> a_scorecard, 
            int a_round, 
            const StrategyEngine& a_strat, 
            const vector<int>& a_availableCategories, 
            shared_ptr<const Dice> a_dice
        ) = 0; 

        // Constructors
        Player() {}; // Default

        Player(string a_logName, string a_internalName): 
            m_logName(a_logName), m_internalName(a_internalName), m_score(0) 
        {};

        Player(string a_logName, string a_internalName, int a_score): 
            m_logName(a_logName), m_internalName(a_internalName), m_score(a_score) 
        {};

        // Getters
        inline string const GetLogName() const { return m_logName; }

        inline string const GetInternalName() const { return m_internalName; }

        inline int const GetScore() const { return m_score; }
        
        inline void AddScore(int a_add) { m_score+= a_add; }

    private:
        string m_logName;
        string m_internalName;
        int m_score;
};