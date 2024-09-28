#include "Input.h"
#include <iostream>
#include <algorithm>
#include <sstream>

bool Input::ValidateYesNo()
{
    while (true)
    {
        string input;
        getline(cin, input);

        // Check syntax: must be y or n
        if (input.length() != 1)
        {
            cerr << "Error: Input must be 'y' or 'n'. Please try again." << endl;
            continue;
        }

        // Return result, or continue loop
        if (tolower(input[0]) == 'y') return true;
        // Random dice roll
        else if (tolower(input[0] == 'n')) return false;
        else cerr << "Error: Input must be 'y' or 'n'. Please try again." << endl;
    }
}

        // Validates that user input exactly the desired list
void Input::ValidateExactIntList(vector<int> a_valid, string a_type)
{
    while (true)
    {
        // Ask for player input.
        vector<int> playerList;
        string input;
        getline(cin, input);

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

        // Validates that user input a subset of a valid list of integers
vector<int> Input::ValidateIntList(vector<int> a_valid, string a_type, int a_countRequired)
{
    while (true)
    {
        // Ask for player input.
        vector<int> playerList;
        string input;
        getline(cin, input);

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

        // Validates that user input a subset of a valid list of integers
int Input::ValidateInt(vector<int> a_valid, string a_type)
{
    while (true)
    {
        int playerInt;
        string input;
        getline(cin, input);
        istringstream stream(input);

        // Try to convert the string to an integer
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

bool Input::ValidateStandReroll()
{
    while(true)
    {
        string input;
        getline(cin, input);

        transform(input.begin(), input.end(), input.begin(), 
            [](unsigned char c){ return tolower(c); });

        if (input == "stand") return true;
        else if (input == "reroll") return false;
    }
}
