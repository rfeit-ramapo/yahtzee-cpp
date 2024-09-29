#pragma once

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include "Strategy.h"

using namespace std;

// Class to handle different scorecard categories.
class Category
: public enable_shared_from_this<Category>
{
public:

    // Constructors

    // Default
    Category() {};
    // Including a name, description, and score.
    Category(
        string a_name, 
        string a_description, 
        string a_score
        ): m_name(a_name), 
        m_description(a_description), 
        m_score(a_score)
    {};

    // Selectors

    inline string const GetName() const { return m_name; };
    inline string const GetDescription() const { return m_description; };
    inline string const GetWinner() const { return m_winner; };
    inline string const GetScore() const { return m_score; };
    inline int GetPoints() const { return m_points; };
    inline int GetRound() const { return m_round; };
    inline bool IsFull() const { return m_full; };

    // Mutators

    inline void const SetWinner(string a_winner) { m_winner = a_winner; }
    inline void const SetPoints(int a_points) { m_points = a_points; }
    inline void const SetRound(int a_round) { m_round = a_round; }
    inline void const SetFull() { m_full = true; }

    // Functions

    /* *********************************************************************
    Function Name: Score
    Purpose: To calculate the score for a particular dice set.
    Parameters: 
                a_dice, a constant reference to the dice set to check the score for.
    Return Value: The score for this category with the given dice set
    Algorithm:
        This is a pure virtual function to be implemented by derived classes.
    Reference: I asked ChatGPT about defining pure virtual functions.
    ********************************************************************* */
    virtual int Score(const Dice& a_dice) const = 0;

    /* *********************************************************************
    Function Name: GetRerollStrategy
    Purpose: To determine a strategy that will achieve this category, if possible.
    Parameters: 
                a_dice, a pointer to const Dice to determine the strategy for.
    Return Value: The strategy to achieve this category.
    Algorithm:
        This is a pure virtual function to be implemented by derived classes.
    Reference: I asked ChatGPT about defining pure virtual functions.
    ********************************************************************* */    
   virtual Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice) const = 0;

protected:
    // Whether this category has been filled
    bool m_full = false;

private:
    // The name of the category (e.g. "Aces")
    string m_name;
    // The description of the category (what is valid)
    string m_description;
    // The way to calculate the score
    string m_score;

    // The winner of the category
    string m_winner;
    // The points earned by the winner
    int m_points = 0;
    // The round that this was filled in
    int m_round = 0;
};

// Class for scoring Aces, Twos, Threes, Fours, Fives, and Sixes.
class MultiplesCategory : public Category
{
public:
    // Constructors
    
    // Default
    MultiplesCategory() {};

    // Takes a name, description, how to score, and the face that requires multiple values.
    MultiplesCategory(
        string a_name, 
        string a_description, 
        string a_score, 
        int a_multipleNumber
    ) : Category(a_name, a_description, a_score), 
        m_multipleIndex(a_multipleNumber - 1) 
    {};

    // Functions

    /* *********************************************************************
    Function Name: Score
    Purpose: To calculate the score for a particular dice set.
    Parameters: 
                a_dice, a constant reference to the dice set to check the score for.
    Return Value: The score for this category with the given dice set
    Algorithm:
            1) Calculate and return the score based on the face count and value
    Reference: none
    ********************************************************************* */
    int Score(const Dice& a_dice) const;

    /* *********************************************************************
    Function Name: GetRerollStrategy
    Purpose: To determine a strategy that will achieve this category, if possible.
    Parameters: 
                a_dice, a pointer to const Dice to determine the strategy for.
    Return Value: The strategy to achieve this category.
    Algorithm:
            1) Return an empty strategy if the category is full
            2) Get the current score and dice values
            3) Determine what the ideal dice set would be for maximum points
            4) Return a strategy using the ideal dice set
    Reference: none
    ********************************************************************* */  
    Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice) const;

private:
    // The index of the face we want multiples of (face value - 1)
    int m_multipleIndex;
};

// Category class for 3 and 4 of a Kind.
class KindCategory : public Category
{
public:

    // Constructors

    // Default
    KindCategory() {};

    // Include name, description, score string, and how many of a kind are needed.
    KindCategory(
        string a_name, 
        string a_description, 
        string a_score, 
        int a_numKind
    ): Category(a_name, a_description, a_score), 
        m_numKind(a_numKind) 
    {};

    // Functions

    /* *********************************************************************
    Function Name: Score
    Purpose: To calculate the score for a particular dice set.
    Parameters: 
                a_dice, a constant reference to the dice set to check the score for.
    Return Value: The score for this category with the given dice set
    Algorithm:
            1) Loop through each face value and check how many dice match it
                2) Add the face value to the running score
                3) If there are enough of a kind, the condition to score is met
            4) Return either 0 (not enough of same dice) or the sum of dice faces
    Reference: none
    ********************************************************************* */
    int Score(const Dice& a_dice) const;        

    /* *********************************************************************
    Function Name: GetRerollStrategy
    Purpose: To determine a strategy that will achieve this category, if possible.
    Parameters: 
                a_dice, a pointer to const Dice to determine the strategy for.
    Return Value: The strategy to achieve this category.
    Algorithm:
            1) Return an empty strategy if the category is full
            2) Get the current score and dice values
            3) Loop backwards through dice faces
                4) Determine best dice set (highest sum) possible given locked dice and scoring face
                5) Return the first strategy that can score
            4) If no faces returned, this category is unachievable (return empty Strategy)
    Reference: none
    ********************************************************************* */  
    Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice) const;
    
private:
    // The number of duplicate dice needed (3 or 4)
    int m_numKind;

    /* *********************************************************************
    Function Name: Score
    Purpose: To calculate the score for a particular dice set.
            This is an overloaded function to use for strategy evaluation.
    Parameters: 
                a_dice, a constant reference to dice count values to check.
    Return Value: The score for this category with the given dice set
    Algorithm:
            1) Loop through each face value and check how many dice match it
                2) Add the face value to the running score
                3) If there are enough of a kind, the condition to score is met
            4) Return either 0 (not enough of same dice) or the sum of dice faces
    Reference: none
    ********************************************************************* */
    int Score(const vector<int>& a_diceValues) const;
};

// Category class for the Full House category.
class FullHouseCategory : public Category
{
public:
    // Constructors
    FullHouseCategory() {};

    // Default

    // Including name, description, and score.
    FullHouseCategory(
        string a_name, 
        string a_description, 
        string a_score
    ): Category(a_name, a_description, a_score) 
    {};

    /* *********************************************************************
    Function Name: Score
    Purpose: To calculate the score for a particular dice set.
    Parameters: 
                a_dice, a constant reference to the dice set to check the score for.
    Return Value: The score for this category with the given dice set
    Algorithm:
            1) Loop through each face value and check how many dice match it
                2) If there are 3 of a kind, the first condition is met
                3) If there are 2 of a kind, the second condition is met
            4) Return either 0 (conditions unmet) or the set score
    Reference: none
    ********************************************************************* */
    int Score(const Dice& a_dice) const;

    /* *********************************************************************
    Function Name: GetRerollStrategy
    Purpose: To determine a strategy that will achieve this category, if possible.
    Parameters: 
                a_dice, a pointer to const Dice to determine the strategy for.
    Return Value: The strategy to achieve this category.
    Algorithm:
            1) Return an empty strategy if the category is full
            2) Return a stand strategy if this dice set scores already
            3) Determine the mode and secondary mode from locked dice
                4) If more than 3 faces are locked, or more than 3 dice of any face are locked, return empty strategy (impossible to score)
            5) Determine the mode and secondary mode from all dice
            6) Determine which face to aim for 3 and which to aim for 2
            7) Create a strategy based on these modes
    Reference: none
    ********************************************************************* */  
    Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice) const;
    
private:
    // Constant indicating how many points this category is worth.
    static constexpr int FULL_HOUSE_SCORE = 25;
};

// Category class for 4 and 5 Straight.
class StraightCategory : public Category
{
public:
    // Constructors

    // Default
    StraightCategory() {};

    // Including name, description, score, required streak number, and score value.
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

    // Functions

    /* *********************************************************************
    Function Name: Score
    Purpose: To calculate the score for a particular dice set.
    Parameters: 
                a_dice, a constant reference to the dice set to check the score for.
    Return Value: The score for this category with the given dice set
    Algorithm:
            1) Loop through each face value and check the dice count
                2) Add to a streak if there is at least one
                3) Otherwise, reset the streak
                4) Once the required streak number is met, return set score
            5) If loop completes without returning, do not score
    Reference: none
    ********************************************************************* */
    int Score(const Dice& a_dice) const;

    /* *********************************************************************
    Function Name: GetRerollStrategy
    Purpose: To determine a strategy that will achieve this category, if possible.
    Parameters: 
                a_dice, a pointer to const Dice to determine the strategy for.
    Return Value: The strategy to achieve this category.
    Algorithm:
            1) Return an empty strategy if the category is full
            2) Return a stand strategy if this dice set scores already
            3) Create a vector of all possible dice configurations for this category
            4) Loop through the vector
                5) Check which dice need to be rerolled to achieve each configuration
                    6) If more rerolls are required than are available, it is impossible
                    7) If it is possible and requires less rerolls than any previous config, use this
            8) If no configurations were possible, return an empty Strategy
            9) Otherwise, return the best strategy found (fewest rerolls needed)
    Reference: none
    ********************************************************************* */  
    // Function to determine how to achieve this category, given current diceset
    Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice) const;
    
private:
    // The number of consecutive dice needed for this category (4 or 5)
    int m_streakNum;
    // The score value of filling this category (30 or 40)
    int m_scoreValue;
};

// Category class for the Yahtzee category.
class YahtzeeCategory : public Category
{
public:
    // Constructors

    // Default
    YahtzeeCategory() {};

    // Including name, description, and score.
    YahtzeeCategory(
        string a_name, 
        string a_description, 
        string a_score
    ): Category(a_name, a_description, a_score) 
    {};

    /* *********************************************************************
    Function Name: Score
    Purpose: To calculate the score for a particular dice set.
    Parameters: 
                a_dice, a constant reference to the dice set to check the score for.
    Return Value: The score for this category with the given dice set
    Algorithm:
            1) Loop through each face value and check the dice count
                2) If any values have all dice, return the set score
            3) If loop completes without returning, do not score
    Reference: none
    ********************************************************************* */
    int Score(const Dice& a_dice) const;

    /* *********************************************************************
    Function Name: GetRerollStrategy
    Purpose: To determine a strategy that will achieve this category, if possible.
    Parameters: 
                a_dice, a pointer to const Dice to determine the strategy for.
    Return Value: The strategy to achieve this category.
    Algorithm:
            1) Return an empty strategy if the category is full
            2) Return a stand strategy if this dice set scores already
            3) Check for locked dice faces to see if this category is possible
                4) If there is more than one locked face, return an empty Strategy (impossible)
            4) Use either the locked dice face or mode of all dice to pursue
            5) Return a reroll strategy based on selected face
    Reference: none
    ********************************************************************* */ 
    Strategy GetRerollStrategy(shared_ptr<const Dice> a_dice) const;

private:
    // Constant indicating how many points this category is worth
    static constexpr int YAHTZEE_SCORE = 50;
};