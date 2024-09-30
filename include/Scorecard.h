#pragma once

#include <string>
#include <vector>
#include <iomanip>
#include "Category.h"

class Player; // Forward declaration

using namespace std;

// For handling information about the game's scorecard.
class Scorecard
{
public:
    // Constants

    // Number of categories in the Scorecard
    static constexpr int NUM_CATEGORIES = 12;

    // Constructors

    // Default
    Scorecard() {};

    // Selectors

    inline const vector<shared_ptr<Category>>& GetCategories() const { return m_categories; };
    inline shared_ptr<const Category> GetCategory(int a_index) const {return m_categories[a_index];};
    inline bool IsFull() const { return (m_numFilled == m_categories.size()); };
    // Gets the index for a specific category name
    inline int GetCategoryIndex(string a_categoryName) const
    {
        for (int i = 0; i < m_categories.size(); ++i)
        {
            if (a_categoryName == m_categories[i]->GetName())
            {
                return i;
            }
        }
        return -1;
    }

    // Functions

    /* *********************************************************************
    Function Name: FillCategory
    Purpose: Fills and enters info for a particular category
    Parameters: 
                a_categoryIndex, the index of the category to fill
                a_points, the number of points scored
                a_round, the round this category was filled in
                a_winner, the name of the winner of this category
    Return Value: none
    Algorithm:
        1) Locates the desired category, then fills in info as required
        2) Increases numFilled variable for Scorecard
    Reference: none
    ********************************************************************* */
    void FillCategory(int a_categoryIndex, int a_points, int a_round, string a_winner);

    /* *********************************************************************
    Function Name: FillMultiple
    Purpose: Fills multiple categories at once
    Parameters: 
                a_categoryIndices, a vector of indices of categories to fill
                a_scores, a vector of the number of points scored
                a_winner, the name of the winner of this category
                a_rounds, a vector of which rounds the categories were filled in
                a_humanPlayer, a pointer to the human player (so their score can be adjusted)
                a_pcPlayer, a pointer to the computer palyer (so their score can be adjusted)
    Return Value: none
    Algorithm:
        1) Loops through each category index provided
            2) Adds score to the human or computer player as needed
        3) Fills the category with corresponding info from each vector
    Reference: none
    ********************************************************************* */
    void FillMultiple
    (
        vector<int> a_categoryIndices,
        vector<int> a_scores,
        vector<string> a_winners,
        vector<int> a_rounds,
        shared_ptr<Player> a_humanPlayer,
        shared_ptr<Player> a_pcPlayer
    );        

    /* *********************************************************************
    Function Name: Print
    Purpose: Prints the scorecard out
    Parameters: None
    Return Value: none
    Algorithm:
        1) Prints the header
        2) Loop through each category
            3) Print basic info of each category
            4) Print info about who won the category, if applicable
    Reference: none
    ********************************************************************* */
    void Print() const;

private:

    // The number of categories currently filled
    int m_numFilled = 0;
    // A vector containing pointers to every category in the scorecard
    vector<shared_ptr<Category>> m_categories = 
    {
        make_shared<MultiplesCategory>("Aces", "Any combination", "Sum of dice with the number 1", 1),
        make_shared<MultiplesCategory>("Twos", "Any combination", "Sum of dice with the number 2", 2),
        make_shared<MultiplesCategory>("Threes", "Any combination", "Sum of dice with the number 3", 3),
        make_shared<MultiplesCategory>("Fours", "Any combination", "Sum of dice with the number 4", 4),
        make_shared<MultiplesCategory>("Fives", "Any combination", "Sum of dice with the number 5", 5),
        make_shared<MultiplesCategory>("Sixes", "Any combination", "Sum of dice with the number 6", 6),
        make_shared<KindCategory>("Three of a Kind", "At least three dice the same", "Sum of all the dice", 3),
        make_shared<KindCategory>("Four of a Kind", "At least four dice the same", "Sum of all the dice", 4),
        make_shared<FullHouseCategory>("Full House", "Three of one number and two of another", "25"),
        make_shared<StraightCategory>("Four Straight", "Four sequential dice", "30", 4, 30),
        make_shared<StraightCategory>("Five Straight", "Five sequential dice", "40", 5, 40),
        make_shared<YahtzeeCategory>("Yahtzee", "All five dice the same", "50")
    };


};