#include <vector>
#include <string>

using namespace std;

class Input
{
    public:

        // Validate y/n input and return 'y' or 'n'
        static bool ValidateYesNo();

        // Validates that user input exactly the desired list
        static void ValidateExactIntList(vector<int> a_valid, string a_type = "values");

        // Validates that user input a subset of a valid list of integers
        static vector<int> ValidateIntList(vector<int> a_valid, string a_type = "values", int a_countRequired = 0);

        // Validates that user input a subset of a valid list of integers
        static int ValidateInt(vector<int> a_valid, string a_type = "value");

        static bool ValidateStandReroll();
};
