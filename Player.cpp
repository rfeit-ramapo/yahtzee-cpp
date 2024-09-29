#include "Player.h"

vector<int> Player::RollAll(Dice &dice) 
{ 
    // Manual input option
    cout << "Would you like to manually input this dice roll? (y/n)" << endl;
    if (Input::ValidateYesNo())
    {
        vector<int> lockedDice = dice.GetLockedDice();
        int numToRoll = 5 - accumulate(lockedDice.begin(), lockedDice.end(), 0);
        cout << "Input the result of your roll." << endl;
        vector<int> inputDice = Input::ValidateIntList({1,2,3,4,5,6}, "dice faces", numToRoll);
        dice.ManualRoll(inputDice);
        return inputDice;
    }

    return dice.RollAll(); 
};