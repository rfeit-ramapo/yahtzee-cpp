#include <iostream>
#include <vector>

using namespace std;

class PossibleRoll
{
    public:


        void print() const {
            cout << "Dice Values: ";
            for (int value : m_diceValues) {
                cout << value << " ";
            }
            cout << "\nScore Values: ";
            for (int score : m_scoreValues) {
                cout << score << " ";
            }
            cout << endl;
        }

        // Getters
        const vector<int> GetDiceValues()
        {
            return m_diceValues;
        }

        const vector<int> GetScoreValues()
        {
            return m_scoreValues;
        }

        // Constructors
        PossibleRoll() {}; // Default

        PossibleRoll(vector<int> a_diceValues, vector<int> a_scoreValues) : m_diceValues(a_diceValues), m_scoreValues(a_scoreValues) {};

    private:
        // How many dice of each value are in this roll
        vector<int> m_diceValues;
        // The score for each category given this roll
        vector<int> m_scoreValues;

};