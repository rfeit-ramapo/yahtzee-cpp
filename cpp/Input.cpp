#include "../include/Input.h"
#include <iostream>
#include <algorithm>
#include <sstream>

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
bool Input::ValidateYesNo()
{
    while (true)
    {
        string input;
        getline(cin, input);

        // Check syntax: must be only one character.
        if (input.length() != 1)
        {
            cerr << "Error: Input must be 'y' or 'n'. Please try again." << endl;
            continue;
        }

        // Return result or redo loop.
        if (tolower(input[0]) == 'y') return true;
        else if (tolower(input[0] == 'n')) return false;
        else cerr << "Error: Input must be 'y' or 'n'. Please try again." << endl;
    }
}

/* *********************************************************************
Function Name: ValidateExactIntList
Purpose: Validates that a user input the same integers as a given list
Parameters:
            a_valid, a vector of integers to check against
            a_type, a string describing what the vector is for (for logging)
            a_helpString, a string to print if the user requests help
Return Value: None
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
void Input::ValidateExactIntList(vector<int> a_valid, string a_type, string a_helpString)
{
    while (true)
    {
        // Ask for player input.
        vector<int> playerList;
        string input;
        getline(cin, input);

        // Provide help if it was requested and is available.
        if (!a_helpString.empty() && (input == "h" || input == "H"))
        {
            cout << a_helpString << endl;
            continue;
        }

        // Check syntax: must be a list of integers, separated by spaces.
        istringstream stream(input);
        int inputNum;
        while (stream >> inputNum) 
        {
            playerList.push_back(inputNum);
        };

        if (!stream.eof())
        {
            cerr << "Error: Input must be a list of integers delineated by spaces (e.g. '1 2 3 4'). Please try again." << endl;
            continue;
        }

        // Check for accuracy (missing or extra categories).
        sort(playerList.begin(), playerList.end());
        if (!(playerList == a_valid))
        {
            cerr << "Error: Missing or extra " << a_type << " listed. Please try again." << endl;
            continue;
        }
        break;
    }
}

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
vector<int> Input::ValidateIntList(vector<int> a_valid, string a_type, int a_countRequired, string a_helpString)
{
    while (true)
    {
        // Ask for player input.
        vector<int> playerList;
        string input;
        getline(cin, input);

        // Provide help if it was requested and is available.
        if (!a_helpString.empty() && (input == "h" || input == "H"))
        {
            cout << a_helpString << endl;
            continue;
        }

        // Check syntax: must be a list of integers, separated by spaces.
        istringstream stream(input);
        int inputNum;

        while (stream >> inputNum) 
        {
            playerList.push_back(inputNum);
        };

        if (!stream.eof())
        {
            cerr << "Error: Input must be a list of integers delineated by spaces (e.g. '1 2 3 4'). Please try again." << endl;
            continue;
        }

        // If a specific number of inputs was required, validate that.
        if (a_countRequired && (playerList.size() != a_countRequired))
        {
            cerr << "Error: Must enter " << a_countRequired << " " << a_type << ". Please try again." << endl;
            continue;
        }

        // Check for accuracy (no numbers outside valid list).
        bool validInput = true;
        for (int i = 0; i < playerList.size(); ++i)
        {
            // If input was not found in the valid list
            if (find(a_valid.begin(), a_valid.end(), playerList[i]) == a_valid.end())
            {
                cout << "a_valid: ";
                for (int j = 0; j < a_valid.size(); ++j)
                {
                    cout << a_valid[j] << " ";
                }
                cout << endl;
                cerr << "Error: Invalid " << a_type << ". Please try again." << endl;
                validInput = false;
                break;
            }
        }
        
        if (validInput) return playerList;
    }

}

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
int Input::ValidateInt(vector<int> a_valid, string a_type, string a_helpString)
{
    while (true)
    {
        int playerInt;
        string input;
        getline(cin, input);

        // Provide help if it was requested and is available.
        if (!a_helpString.empty() && (input == "h" || input == "H"))
        {
            cout << a_helpString << endl;
            continue;
        }

        // Try to convert the string to an integer
        istringstream stream(input);
        stream >> playerInt;
        if (!stream.eof())
        {
            cerr << "Error: The input was not a valid integer. Please try again." << endl;
            continue;
        }

        // Check if it's in the valid list.
        if (find(a_valid.begin(), a_valid.end(), playerInt) == a_valid.end())
        {
            cerr << "Error: Invalid " << a_type << ". Please try again." << endl;
            continue;
        }
        return playerInt;
    }
}

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
bool Input::ValidateStandReroll(string a_helpString)
{
    while(true)
    {
        string input;
        getline(cin, input);

        // Provide help if it was requested and is available.
        if (!a_helpString.empty() && (input == "h" || input == "H"))
        {
            cout << a_helpString << endl;
            continue;
        }

        // Convert input to lowercase
        transform(input.begin(), input.end(), input.begin(), 
            [](unsigned char c){ return tolower(c); });

        if (input == "stand") return true;
        else if (input == "reroll") return false;
        else cerr << "Error: Input must be 'stand' or 'reroll'. Please try again." << endl;
    }
}
