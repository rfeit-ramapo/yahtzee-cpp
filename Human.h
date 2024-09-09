#include <string>
#include <iostream>
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

        // Todo
        vector<int> RollSome(Dice &dice) {};

        vector<int> RollAll(Dice &dice) 
        {
            cout << "Press Enter to roll all dice." << endl;
            cin.get();
            return dice.RollAll();
        };

        // Constructors
        Human() : Player("You", "Human") {}; // Default
        Human(int a_score) : Player("You", "Human", a_score) {};
};