#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "Player.h"

using namespace std;

class Human : public Player
{
    public:

        int RollOne(Dice &dice) 
        {
            cout << "Press Enter to roll your die." << endl;
            cin.get();
            return dice.RollOne();
        };

        vector<int> RollAll(Dice &dice) 
        {
            cout << "Press Enter to roll the dice." << endl;
            cin.get();
            return dice.RollAll();
        };

        vector<int> ListAvailableCategories(const StrategyEngine& a_strat, shared_ptr<const Dice> a_dice)
        {
            // Get the conclusive list.
            vector<int> availableCategories = a_strat.GetPossibleCategories(a_dice);

            // Print a basic scorecard for reference.
            cout << endl;
            a_strat.GetScorecard()->Print();

            // Get player list.
            cout << "Please list all scorecard categories available, given the dice set so far." << endl;
            // Loop to handle processing user input.
            while (true)
            {
                // Ask for player input.
                vector<int> playerCategoryList;
                string input;
                getline(cin, input);

                // Check syntax: must be a list of numbers within [1,12], separated by spaces.
                istringstream stream(input);
                int categoryNum;
                bool validInput = true;

                while (stream >> categoryNum)
                {
                    if (categoryNum < 1 || categoryNum > 12) 
                    {
                        validInput = false;
                        break;
                    }
                    else
                    {
                        playerCategoryList.push_back(categoryNum - 1);
                    }
                }

                if (!validInput || !stream.eof())
                {
                    cerr << "Error: Input must be a list of categories by index [1,12] delineated by spaces (e.g. '1 2 3 4'). Please try again." << endl;
                    continue;
                }

                // Check for accuracy (missing or extra categories).
                sort(playerCategoryList.begin(), playerCategoryList.end());
                if (!(playerCategoryList == availableCategories))
                {
                    cerr << "Error: Missing or extra categories listed. Please list all categories that are available, given the current dice set." << endl;
                    cerr << "cheat info: available categories = ";
                    for (int cat : availableCategories) cerr << (cat + 1) << " ";
                    cerr << endl;
                    continue;
                }

                break;
            }

            return availableCategories;
        }

        void PursueCategories(const StrategyEngine& a_strat, const vector<int>& a_availableCategories, shared_ptr<const Dice> a_dice) 
        {
            cout << "Please input one or two categories to pursue." << endl;
            // Loop to handle processing user input.
            while (true)
            {
                // Ask for player input.
                vector<int> playerPursuitList;
                string input;
                getline(cin, input);

                // Check syntax: must be a list of numbers within [1,12], separated by spaces.
                istringstream stream(input);
                int categoryNum;
                bool validInput = true;

                while (stream >> categoryNum)
                {
                    categoryNum--;
                    // The pursued categories must be available.
                    if (find(a_availableCategories.begin(), a_availableCategories.end(), categoryNum) == a_availableCategories.end())
                    {
                        validInput = false;
                        break;
                    }
                    else
                    {
                        playerPursuitList.push_back(categoryNum - 1);
                    }
                }

                // Check if error was encountered, and disallow more than 2 pursued categories.
                if (!validInput || !stream.eof() || (playerPursuitList.size() > 2))
                {
                    cerr << "Error: Input must be one or two available categories delineated by spaces (e.g. '2 5'). Please try again." << endl;
                    cerr << "validInput: " << validInput << "; ppsize: " << playerPursuitList.size() << endl;
                    continue;
                }

                break;
            }
        };

        bool HandleRerolls(shared_ptr<Dice> a_dice)
        {
            // If roll again, list the dice the player wants to re-roll. Identify dice by their current face (e.g., "I will re-roll 3, 1 and 6").

            cout << "Please choose whether to stand or reroll." << endl;

            // Handle player input.
            while(true)
            {
                string input;
                getline(cin, input);

                transform(input.begin(), input.end(), input.begin(), 
                    [](unsigned char c){ return tolower(c); });

                if (input == "stand")
                {
                    return true;
                }
                else if (input == "reroll")
                {
                    // Get the list of free dice (which ones are rerollable).
                    vector<int> freeDice = a_dice->GetFreeDice();
                    vector<int> playerRerollList;

                    cout << "Which dice would you like to reroll? Input the face values." << endl;

                    // Ask the player for which dice to reroll.
                    while (true)
                    {
                        // Ask for player input.
                        playerRerollList = {0, 0, 0, 0, 0, 0};
                        string input;
                        getline(cin, input);

                        // Check syntax: must be a list of numbers within [1,12], separated by spaces.
                        istringstream stream(input);
                        int diceValue;
                        bool validInput = true;

                        while (stream >> diceValue)
                        {
                            if (diceValue > 6 || diceValue < 1)
                            {
                                validInput = false;
                                break;
                            }

                            playerRerollList[diceValue - 1]++;
                        }

                        for (int i = 0; i < 6; ++i)
                        {
                            if (freeDice[i] < playerRerollList[i]) validInput = false;
                        }

                        // Check if error was encountered, and disallow more than 2 pursued categories.
                        if (!validInput || !stream.eof())
                        {
                            cerr << "Error: Input must be dice face values that are not locked, with space in between each entry. Please try again." << endl;
                            cout << "cheat entry - free dice: ";
                            for (int i = 0; i < 6; ++i)
                            {
                                cout << freeDice[i] << " ";
                            }
                            cout << endl;
                            continue;
                        }
                        break;
                    }

                    // Lock all other dice.
                    a_dice->LockDice(playerRerollList);

                    return false;
                }
                else
                {
                    cerr << "Error: Input must be either 'stand' or 'reroll'. Please try again." << endl;
                }
            }
            
        }

        void ChooseCategory(shared_ptr<Scorecard> a_scorecard, int a_round, const StrategyEngine& a_strat, const vector<int>& a_availableCategories, shared_ptr<const Dice> a_dice) 
        {
            int chosenCategory;
            int claimedScore;

            if (a_availableCategories.size() == 0)
            {
                cout << "There is no way to score with the current dice set and open categories. Skipping turn." << endl << endl;
                return;
            }

            // Take player input
            cout << "Please identify the category you would like to claim, followed by the score." << endl;

            // Loop to handle processing user input.
            while (true)
            {
                // Ask for player input.
                string input;
                getline(cin, input);

                // Check syntax: must be an available category, followed by an accurate score.
                istringstream stream(input);

                if (stream >> chosenCategory >> claimedScore)
                {
                    --chosenCategory;
                    if (find(a_availableCategories.begin(), a_availableCategories.end(), chosenCategory) == a_availableCategories.end())
                    {
                        cerr << "Error: Invalid category chosen. Please try again." << endl;
                        continue;
                    }

                    int actualScore = a_scorecard->GetCategory(chosenCategory)->Score(*a_dice);
                    if (actualScore != claimedScore)
                    {
                        cerr << "Error: Inaccurate scoring. Please try again." << endl;
                        continue;
                    }
                }
                else
                {
                    cerr << "Error: Input must be a category index, followed by a score (e.g. '6 18'). Please try again." << endl;
                    continue;
                }

                break;
            }

            cout << "Please press enter to fill the scorecard." << endl;
            cin.get();
            AddScore(claimedScore);
            a_scorecard->FillCategory(chosenCategory, claimedScore, a_round, "Human");
            a_scorecard->Print();
        }

        // Constructors
        Human() : Player("You", "Human") {}; // Default
        Human(int a_score) : Player("You", "Human", a_score) {};
};