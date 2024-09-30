#pragma once

#include <vector>
#include <string>

using namespace std;

// Class to handle validating user input of various kinds.
class Input
{
public:

    /* *********************************************************************
    Function Name: ValidateYesNo
    Purpose: Asks the user for (y/n) input and returns the result
    Parameters: None
    Return Value: a boolean indicating yes (true) or no (false)
    Algorithm:
        1) Enter loop
            2) Get user input
            3) Validate that it is one character long
            4) Return true for 'y' and false for 'n'
            5) If neither was received, restart loop
    Reference: none
    ********************************************************************* */
    static bool ValidateYesNo();

    /* *********************************************************************
    Function Name: ValidateExactIntList
    Purpose: Validates that a user input the same integers as a given list
    Parameters:
                a_valid, a vector of integers to check against
                a_type, a string describing what the vector is for (for logging)
                a_helpString, a string to print if the user requests help
    Return Value: a boolean indicating yes (true) or no (false)
    Algorithm:
        1) Enter loop
            2) Get user input
            3) Provide help string if requested (and restart loop)
            4) Add player input to a vector
            5) Sort and compare vector to valid vector 
                6) If different, log error and restart loop
                7) If equivalent, exit the function
    Reference: none
    ********************************************************************* */
    static void ValidateExactIntList(vector<int> a_valid, string a_type = "values", string a_helpString = "");

    /* *********************************************************************
    Function Name: ValidateIntList
    Purpose: Validates that a user input a subset of a given integer list
    Parameters:
                a_valid, a vector of integers to check against
                a_type, a string describing what the vector is for (for logging)
                a_countRequired, a number specifying how many inputs are required
                a_helpString, a string to print if the user requests help
    Return Value: the vector of integers that the player input
    Algorithm:
        1) Enter loop
            2) Get user input
            3) Provide help string if requested (and restart loop)
            4) Add player input to a vector
            5) Check if vector size and input is valid
                6) If not, log error and restart loop
                7) If it is, return the player's input vector
    Reference: none
    ********************************************************************* */
    static vector<int> ValidateIntList(vector<int> a_valid, string a_type = "values", int a_countRequired = 0, string a_helpString = "");

    /* *********************************************************************
    Function Name: ValidateInt
    Purpose: Validates that a user input an int within a valid list
    Parameters:
                a_valid, a vector of integers to check against
                a_type, a string describing what the vector is for (for logging)
                a_helpString, a string to print if the user requests help
    Return Value: the integer that the player input
    Algorithm:
        1) Enter loop
            2) Get user input
            3) Provide help string if requested (and restart loop)
            4) Check if player entered an integer, and if it was valid
                5) If valid, return the integer
                6) Otherwise, restart the loop
    Reference: none
    ********************************************************************* */
    static int ValidateInt(vector<int> a_valid, string a_type = "value", string a_helpString = "");

    /* *********************************************************************
    Function Name: ValidateStandReroll
    Purpose: Validates user choice to either stand or reroll
    Parameters:
                a_helpString, a string to print if the user requests help
    Return Value: boolean indicating if the player will stand (true) or reroll (false)
    Algorithm:
        1) Enter loop
            2) Get user input
            3) Provide help string if requested (and restart loop)
            4) Check if player entered an integer, and if it was valid
                5) If valid, return the integer
                6) Otherwise, restart the loop
    Reference: Received help from ChatGPT to find out how to convert to lowercase
    ********************************************************************* */
    static bool ValidateStandReroll(string a_helpString = "");
};
