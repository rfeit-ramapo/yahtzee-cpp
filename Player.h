#pragma once

#include <string>
#include "Dice.h"

using namespace std;

class Player
{
    public:

        // Functions
        virtual int RollOne(Dice &dice) {};
        virtual vector<int> RollSome(Dice &dice) {};
        virtual vector<int> RollAll(Dice &dice) {};

        // Constructors
        Player() {}; // Default
        Player(string a_logName, string a_internalName): m_logName(a_logName), m_internalName(a_internalName), m_score(0) {};
        Player(string a_logName, string a_internalName, int a_score): m_logName(a_logName), m_internalName(a_internalName), m_score(a_score) {};

        // Getters
        inline string const GetLogName() { return m_logName; }
        inline string const GetInternalName() { return m_internalName; }
        inline int const GetScore() { return m_score; }

    private:
        string m_logName;
        string m_internalName;
        int m_score;
};