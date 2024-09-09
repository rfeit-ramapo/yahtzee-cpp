#include <string>
#include <iostream>
#include "Player.h"

using namespace std;

class Computer : public Player
{
    public:

        int RollOne(Dice &dice) { return dice.RollOne(); }

        // Todo
        vector<int> RollSome(Dice &dice) {};

        vector<int> RollAll(Dice &dice) { return dice.RollAll(); };

        // Constructors
        Computer() : Player("The computer", "Computer") {}; // Default
        Computer(int a_score) : Player("The computer", "Computer", a_score) {};
};