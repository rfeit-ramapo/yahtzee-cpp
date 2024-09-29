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
        virtual int Score(const Dice &a_dice) const = 0;

        // Function to determine how to achieve this category, given current diceset
        virtual Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice) const = 0;

        // Constructors
        Category() {}; // Default

        Category(
            string a_name, 
            string a_description, 
            string a_score
            ): m_name(a_name), 
            m_description(a_description), 
            m_score(a_score)
        {};

        Category(
            string a_name, 
            string a_description, 
            string a_score, 
            string a_winner, 
            int a_points, 
            int a_round
        ) : m_name(a_name), 
            m_description(a_description), 
            m_score(a_score), 
            m_winner(a_winner), 
            m_points(a_points), 
            m_round(a_round) 
        {};

        // Getters
        inline string const GetName() const { return m_name; };
        inline string const GetDescription() const { return m_description; };
        inline string const GetWinner() const { return m_winner; };
        inline string const GetScore() const { return m_score; };
        inline int GetPoints() const { return m_points; };
        inline int GetRound() const { return m_round; };
        inline bool IsFull() const { return m_full; };

        // Setters
        inline void const SetWinner(string a_winner) { m_winner = a_winner; }
        inline void const SetPoints(int a_points) { m_points = a_points; }
        inline void const SetRound(int a_round) { m_round = a_round; }
        inline void const SetFull() { m_full = true; }

    protected:
        bool m_full = false;

    private:
        string m_name;
        string m_description;
        string m_score;
        string m_winner;
        int m_points = 0;
        int m_round = 0;
};

// Class for Aces, Twos, Threes, Fours, Fives, and Sixes
class MultiplesCategory : public Category
{
    public:

        // Function to calculate the score for this category
        int Score(const Dice& a_dice) const;

        // Function to determine how to achieve this category, given current diceset
        Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice) const;

        // Constructors
        MultiplesCategory() {}; // Default

        MultiplesCategory(
            string a_name, 
            string a_description, 
            string a_score, 
            int a_multipleNumber
        ) : Category(a_name, a_description, a_score), 
            m_multipleIndex(a_multipleNumber - 1) 
        {};

        MultiplesCategory(
            string a_name, 
            string a_description, 
            string a_score, 
            string a_winner, 
            int a_points, 
            int a_round, 
            int a_multipleNumber
        ) : Category(a_name, a_description, a_score, a_winner, a_points, a_round), 
            m_multipleIndex(a_multipleNumber - 1)
        {};

        private:
            int m_multipleIndex;  // The index of the face we want multiples of (face value - 1)
};

class KindCategory : public Category
{
    public:

        // Function to calculate the score for this category
        int Score(const Dice& a_dice) const;
        // Overload for Score function to use on incomplete dice
        int Score(const vector<int>& diceValues) const;

        // Function to determine how to achieve this category, given current diceset
        Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice) const;

        // Constructors
        KindCategory(
            string a_name, 
            string a_description, 
            string a_score, 
            int a_numKind
        ): Category(a_name, a_description, a_score), 
            m_numKind(a_numKind) 
        {};

        KindCategory(
            string a_name, 
            string a_description, 
            string a_score, 
            string a_winner, 
            int a_points, 
            int a_round, 
            int a_numKind
        ) : Category(a_name, a_description, a_score, a_winner, a_points, a_round), 
            m_numKind(a_numKind)
        {};
        
    private:
        int m_numKind;   // The number of duplicate dice needed (4 or 5)
};

class FullHouseCategory : public Category
{
    public:

        // Function to calculate the score for this category
        int Score(const Dice& a_dice) const;

        Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice) const;

        // Constructors
        FullHouseCategory(
            string a_name, 
            string a_description, 
            string a_score
        ): Category(a_name, a_description, a_score) 
        {};

        FullHouseCategory(
            string a_name, 
            string a_description, 
            string a_score, 
            string a_winner, 
            int a_points, 
            int a_round
        ) : Category(a_name, a_description, a_score, a_winner, a_points, a_round) 
        {};
        
    
    private:

        static const int m_maxScore = 25;   // The score you get from achieving this category
};

class StraightCategory : public Category
{
    public:

        // Function to calculate the score for this category
        int Score(const Dice& a_dice) const;

        // Function to determine how to achieve this category, given current diceset
        Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice) const;

        // Constructors
        StraightCategory(
            string a_name, 
            string a_description, 
            string a_score, 
            int a_streakNum, 
            int a_scoreValue
        ): Category(a_name, a_description, a_score), 
            m_streakNum(a_streakNum), 
            m_scoreValue(a_scoreValue) 
        {};

        StraightCategory(
            string a_name, 
            string a_description, 
            string a_score, 
            string a_winner, 
            int a_points, 
            int a_round, 
            int a_streakNum, 
            int a_scoreValue
        ) : Category(a_name, a_description, a_score, a_winner, a_points, a_round), 
            m_streakNum(a_streakNum), 
            m_scoreValue(a_scoreValue)
        {};
        
    private:
        int m_streakNum;    // The number of consecutive dice needed for this category (4 or 5)
        int m_scoreValue;   // The score value of filling this category (30 or 40)
};

class YahtzeeCategory : public Category
{
    public:

        // Function to calculate the score for this category
        int Score(const Dice& a_dice) const;

        Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice) const;

        // Constructors
        YahtzeeCategory(
            string a_name, 
            string a_description, 
            string a_score
        ): Category(a_name, a_description, a_score) 
        {};

        YahtzeeCategory(
            string a_name, 
            string a_description, 
            string a_score, 
            string a_winner, 
            int a_points, 
            int a_round
        ) : Category(a_name, a_description, a_score, a_winner, a_points, a_round) 
        {};
    
    private:

        static const int m_maxScore = 50;   // The score you get from achieving this category
};