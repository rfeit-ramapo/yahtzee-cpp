#include <iostream>
#include <iterator>
#include "Player.h"

using namespace std;

class Turn
{
    public:

        void Play()
        {
            cout << "====================" << endl << "First Roll" << endl;
            vector<int> rollResult = m_dice->RollAll();
            cout << m_player->GetLogName() << " rolled    ";
            for (int i : rollResult) cout << " " << i;
            cout << endl;
        };
    
        // Constructors
        Turn() {}; // Default

    private:
        shared_ptr<Player> m_player;
        shared_ptr<Dice> m_dice;
};