#include <iostream>
#include <cmath>
#include "Scorecard.h"
#include "PossibleRoll.h"

using namespace std;

int nCr(int n, int r) {
    if (r > n) return 0;
    if (r == 0 || r == n) return 1;
    int res = 1;
    for (int i = 0; i < r; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

class Strategy
{
    public:

        // Function to generate all combinations
        void GenerateCombinations(int faces, int dice, vector<int>& combination, int start) {
            if (dice == 0) {
                vector<int> result(faces, 0);
                for (int num : combination) {
                    result[num - 1]++; // Increment count for the face (num - 1)
                }
                vector<int> scoreValues;
                for ( Category c : m_scorecard->GetCategories())
                {
                    scoreValues.push_back(c.Score(result));
                }
                m_possibleRolls.push_back(PossibleRoll(result, scoreValues));
                return;
            }

            for (int i = start; i <= faces; ++i) {
                combination.push_back(i);
                GenerateCombinations(faces, dice - 1, combination, i);
                combination.pop_back();
            }
        }

        void InitializeStrategy()
        {
            int faces = 6;
            int dice = 5;

            vector<int> combination;

            GenerateCombinations(faces, dice, combination, 1);
        };

        void Strategize(const vector<int> &diceValues)
        {
            double maxWeightedScore = 0;
            vector<int> targetValues;

            int maxScore = 0;
            int categoryIndex;
            auto categories = m_scorecard->GetCategories();
            for ( int i = 0; i < categories.size(); ++i)
            {
                int categoryScore = categories[i].Score(diceValues);
                if (maxScore < categoryScore)
                {
                    maxScore = categoryScore;
                    categoryIndex = i;
                }
            }

            // Current best; this could also be empty if there are no qualifying categories
            Category category = m_scorecard->GetCategory(categoryIndex);
            cout << "The current category to go for is " << category.GetName() << endl;
            cout << "This category will give " << maxScore << " points" << endl;

            // mark values that are needed for this score
            vector<int> temp_mark = {0, 0, 5, 0, 0, 0};

            // go through possible rolls and eliminate those that do not have min values shown above
            // if no current score was found, these values will be zero
            for (PossibleRoll r : m_possibleRolls)
            { 
                int update = 1;
                for (int i = 0; i < temp_mark.size(); i++)
                {
                    if (temp_mark[i] > r.GetDiceValues()[i]) 
                    {
                        update = 0;
                        break;
                    };
                }

                if (update)
                {
                    int newMax = 0;
                    int newCategory;
                    for (int i = 0; i < r.GetScoreValues().size(); i++)
                    {
                        if (newMax < r.GetScoreValues()[i]) 
                        {
                            newMax = r.GetScoreValues()[i];
                            newCategory = i;
                        }
                    }
                    if (newMax > maxScore) 
                    {
                        maxScore = newMax;
                        categoryIndex = newCategory;
                    }
                }

            }

            // if they do have min values required, and the score is greater than current max, set it as the recommended play
            category = m_scorecard->GetCategory(categoryIndex);
            cout << "The new category to go for is " << category.GetName() << endl;
            cout << "This category will give " << maxScore << " points" << endl;

        }

        void PrintRolls()
        {
            for (PossibleRoll r : m_possibleRolls) r.print();
        }

        // Constructors
        Strategy() {}; // Default

        Strategy(shared_ptr<Scorecard> a_scorecard) : m_scorecard(a_scorecard) {};

    private:
        shared_ptr<Scorecard> m_scorecard;
        vector<PossibleRoll> m_possibleRolls;
};