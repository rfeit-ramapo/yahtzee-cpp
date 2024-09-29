#pragma once

#include <vector>
#include <string>

using namespace std;

class Input
{
    public:

        // Validate y/n input and return 'y' or 'n'
        static bool ValidateYesNo();

        // Validates that user input exactly the desired list
        static void ValidateExactIntList(vector<int> a_valid, string a_type = "values", string a_helpString = "");

        // Validates that user input a subset of a valid list of integers
        static vector<int> ValidateIntList(vector<int> a_valid, string a_type = "values", int a_countRequired = 0, string a_helpString = "");

        // Validates that user input a subset of a valid list of integers
        static int ValidateInt(vector<int> a_valid, string a_type = "value", string a_helpString = "");

        static bool ValidateStandReroll(string a_helpString = "");
};
