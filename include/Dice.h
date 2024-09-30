#pragma once

#include <vector>

using namespace std;

class Dice
{
public:
    // Constants

    // Number of dice rolled for the game
    static constexpr int NUM_DICE = 5;
    // The number of dice faces
    static constexpr int NUM_DICE_FACES = 6;

    // Constructor
    Dice() {};

    // Selectors
    inline vector<int> GetLockedDice() const { return m_locked; }
    inline vector<int> GetDiceCount() const { return m_diceCount; }

    // Inline Functions

    /* *********************************************************************
    Function Name: RollOne
    Purpose: To roll one die and return the value
    Parameters: None
    Return Value: an integer [1,6] representing the face value rolled
    Algorithm:
        1) Return the result of GenerateDieValue
    Reference: none
    ********************************************************************* */
    inline int RollOne() { return GenerateDieValue(); }

    /* *********************************************************************
    Function Name: LockAllDice
    Purpose: Locks all dice to prevent rerolling them
    Parameters: None
    Return Value: None
    Algorithm:
        1) Set locked dice equal to the current dice face counts
    Reference: none
    ********************************************************************* */
    inline void LockAllDice() { m_locked = m_diceCount; }

    /* *********************************************************************
    Function Name: UnlockAllDice
    Purpose: Unlocks all dice to allow for rerolls
    Parameters: None
    Return Value: None
    Algorithm:
        1) Clears the locked dice vector to all 0s
    Reference: none
    ********************************************************************* */
    inline void UnlockAllDice() { m_locked = {0, 0, 0, 0, 0, 0}; }

    /* *********************************************************************
    Function Name: ListToCount
    Purpose: Turn a list of dice into a vector of dice face counts
    Parameters: 
                a_diceList, the list of dice by face.
    Return Value: a vector representing how many of each face the dice list contained.
    Algorithm:
        1) Loops through the dice list
            2) For each face value, increment corresponding index of the diceCount vector
        3) Return the diceCount vector
    Reference: none
    ********************************************************************* */
    static vector<int> ListToCount(vector<int> a_diceList);

    /* *********************************************************************
    Function Name: CountToList
    Purpose: Turn a vector of dice face counts into a list of dice faces
    Parameters: 
                a_diceCount, the vector of dice face counts.
    Return Value: a vector of integers [1-6] that represent dice faces
    Algorithm:
        1) Loops through the dice counts vector
            2) For each additional die, add the face value to the dice list
        3) Return the diceList vector
    Reference: none
    ********************************************************************* */
    static vector<int> CountToList(vector<int> a_diceCount);
    
    /* *********************************************************************
    Function Name: LockDice
    Purpose: Lock all dice that are not designated to keep free
    Parameters: 
                a_keptDice, the vector of dice face counts to keep free.
    Return Value: a boolean indicating if locking was successful
    Algorithm:
        1) Loops through the dice face
            2) Try to lock any dice that are not kept
            3) If trying to unlock dice, report error and return
        4) Set the locked dice and return successfully
    Reference: none
    ********************************************************************* */
    bool LockDice(vector<int> a_keptDice);

    /* *********************************************************************
    Function Name: RollAll
    Purpose: Rolls all dice that are not locked.
    Parameters: None
    Return Value: a vector indicating what the new faces are.
    Algorithm:
        1) Loops through the die
            2) Rerolls the die if it is not locked
            3) If it is locked, skips and reduces locked count for that face
        2) Returns the new dice list
    Reference: none
    ********************************************************************* */
    vector<int> RollAll();

    /* *********************************************************************
    Function Name: ManualRoll
    Purpose: Allows for manual input of reroll values for free dice
    Parameters: 
                a_input, a vector of integers representing the rerolled dice
    Return Value: None
    Algorithm:
        1) Uses locked dice as the base
        2) Adds inputted dice to dice list
        3) Increments face counts based on inputted dice
    Reference: none
    ********************************************************************* */
    void ManualRoll(vector<int> a_input);



    /* *********************************************************************
    Function Name: GetUnlockedUnscored
    Purpose: To get the counts of dice of each face that are not contributing to a score
    Parameters: 
                a_required, a constant reference that represents which dice faces contribute to a score.
    Return Value: a vector of integers that represent how many of each dice face do not contribute.
    Algorithm:
        1) Loops through each dice face and calculates free dice that are not required
        2) Returns the resulting vector
    Reference: none
    ********************************************************************* */
    vector<int> GetUnlockedUnscored(const vector<int>& required) const;

    /* *********************************************************************
    Function Name: GetFreeDice
    Purpose: To get counts of unlocked dice faces
    Parameters: None
    Return Value: a vector of integers that represent how many of each dice face are not locked.
    Algorithm:
        1) Loops through each dice face and calculates total count - locked count
        2) Returns the resulting vector
    Reference: none
    ********************************************************************* */
    vector<int> GetFreeDice() const;

    /* *********************************************************************
    Function Name: Print
    Purpose: Prints out the current list of dice, with locked dice in red.
    Parameters: None
    Return Value: None
    Algorithm:
        1) Loops through the dice list and prints out each face value
            2) If this face is locked, it prints in red
    Reference: none
    ********************************************************************* */
    void Print() const;

private:
    // A vector containing the face values of all dice
    vector<int> m_diceList = {1, 1, 1, 1, 1};
    // A vector containing the counts of each dice face [1-6]
    vector<int> m_diceCount = {0, 0, 0, 0, 0, 0};
    // A vector containing the counts of each locked dice face [1-6]
    vector<int> m_locked = {0, 0, 0, 0, 0, 0};

    /* *********************************************************************
    Function Name: GenerateDieValue
    Purpose: Randomly generates a number between 1 and 6
    Parameters: None
    Return Value: an integer between 1 and 6, representing a die face
    Algorithm:
        1) Create and seed a random generator
        2) Use uniform distribution to generate a value between 1 and 6
    Reference: Used ChatGPT to research random generators
    ********************************************************************* */
    int GenerateDieValue();
};