#include <random>
#include <iostream>
#include "../include/Dice.h"

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
vector<int> Dice::ListToCount(vector<int> a_diceList)
{
    vector<int> diceCount(NUM_DICE_FACES,0);
    for (int i = 0; i < a_diceList.size(); ++i)
    {
        ++diceCount[a_diceList[i] - 1];
    }
    return diceCount;
}

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
vector<int> Dice::CountToList(vector<int> a_diceCount)
{
    vector<int> diceList;
    for (int i = 0; i < NUM_DICE_FACES; ++i)
    {
        for (int j = 0; j < a_diceCount[i]; ++j)
        {
            diceList.push_back(i + 1);
        }
    }
    return diceList;
}

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
bool Dice::LockDice(vector<int> a_keptDice)
{
    // Loop through each dice face
    vector<int> newLocked(NUM_DICE_FACES,0);
    for (int i = 0; i < NUM_DICE_FACES; ++i)
    {
        // Lock any dice that are not specified as kept.
        int numToLock = m_diceCount[i] - a_keptDice[i];
        // If the new number to lock is less than before, report error.
        // You cannot unlock dice with this function.
        if (numToLock < m_locked[i])
        {
            cerr << "Error: Input must be dice that were rolled and that have not already been set aside. Please try again." << endl;
            return false;
        }
        newLocked[i] = numToLock;
    }

    // If there were no errors, set the locked dice and return true (indicating success)
    m_locked = newLocked;
    return true;
}

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
vector<int> Dice::RollAll()
{
    // Keep track of how many locked dice remain
    m_diceCount = m_locked;
    vector<int> lockedRemaining = m_locked;

    // Loop through each die
    for (int i = 0; i < NUM_DICE; ++i) 
    {
        // If this face value is locked, do not reroll it.
        if (lockedRemaining[(m_diceList[i] - 1)])
        {
            // Decrement locked so that any extra of this face can be rerolled.
            --lockedRemaining[(m_diceList[i] - 1)];
            continue;
        }

        // Replace this die with a newly generated value.
        m_diceList[i] = GenerateDieValue();
        // Update the dice face counts as well.
        m_diceCount[(m_diceList[i] - 1)] += 1;
    }
    return m_diceList;
}

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
void Dice::ManualRoll(vector<int> a_input)
{
    // Set locked dice as base
    m_diceCount = m_locked;
    m_diceList = CountToList(m_locked);

    // Append input list to locked values
    m_diceList.insert(m_diceList.end(), a_input.begin(), a_input.end());
    
    // Add to dice counts for every input face value
    for (int i = 0; i < a_input.size(); ++i)
    {
        ++m_diceCount[m_diceList[i] - 1];
    }
}


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
vector<int> Dice::GetUnlockedUnscored(const vector<int>& required) const
{
    vector<int> unlockedUnscored(NUM_DICE_FACES, 0);
    for (int i = 0; i < NUM_DICE_FACES; ++i)
    {
        // Get whichever is greater: required dice of this face, or locked dice of this face
        // Subtract the above from current dice to see if there are extraneous dice of this face
        // Take the max between this and zero to avoid negative numbers
        unlockedUnscored[i] = max(m_diceCount[i] - max(required[i], m_locked[i]), 0);
    }
    return unlockedUnscored;
}

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
vector<int> Dice::GetFreeDice() const
{
    vector<int> freeDice;
    for (int i = 0; i < NUM_DICE_FACES; ++i)
    {
        freeDice.push_back(m_diceCount[i] - m_locked[i]);
    }
    return freeDice;
}

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
void Dice::Print() const
{
    const string RESET_COLOR = "\033[0m";
    const string RED_COLOR = "\033[31m";

    // Keep track of how many locked dice remain
    vector<int> lockedRemaining = m_locked; 
    for (int i = 0; i < NUM_DICE; ++i) 
    {
        // Print in red if this die is locked
        if (lockedRemaining[(m_diceList[i] - 1)])
        {
            --lockedRemaining[(m_diceList[i] - 1)];
            cout << RED_COLOR << m_diceList[i] << RESET_COLOR << " ";
        }
        // Otherwise print normally
        else
        {
            cout << m_diceList[i] << " ";
        }
    }
    cout << endl;
}

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
int Dice::GenerateDieValue()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(1, 6);
    return distribution(gen);
};