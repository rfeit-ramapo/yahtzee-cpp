#include "../include/Player.h"

/* *********************************************************************
Function Name: RollAll
Purpose: Rolls all unlocked dice for the player
Parameters:
            dice, a reference to the dice set to be rerolled
Return Value: a vector of the newly generated dice face values
Algorithm:
    1) Checks if the player wants to manually input the roll
        2) If so, gets new values for unlocked dice
    3) Otherwise, uses automatic reroll function
Reference: none
********************************************************************* */
vector<int> Player::RollAll(Dice& dice)
{
    // Manual input option
    cout << "Would you like to manually input this dice roll? (y/n)" << endl;
    if (Input::ValidateYesNo())
    {
        // Only reroll unlocked dice
        vector<int> lockedDice = dice.GetLockedDice();
        int numToRoll = Dice::NUM_DICE - accumulate(lockedDice.begin(), lockedDice.end(), 0);

        // Validate user input use it to manually reroll
        cout << "Input the result of your roll." << endl;
        vector<int> inputDice;
        if (numToRoll > 1)
        {
            inputDice = Input::ValidateIntList({1, 2, 3, 4, 5, 6}, "dice faces", numToRoll);
        }
        else
        {
            inputDice.push_back(Input::ValidateInt({1, 2, 3, 4, 5, 6}, "dice face"));
        }
        dice.ManualRoll(inputDice);
        return inputDice;
    }

    // Automatically reroll dice that are unlocked
    return dice.RollAll();
};