#include <string>
#include <memory>
#include <random>
#include <iostream>
#include "Dice.h"
#include "Player.h"

using namespace std;

class Round
{
    public:
        
        void DetermineFirstPlayer()
        {
            int p1_score = m_players[0]->GetScore();
            int p2_score = m_players[1]->GetScore();

            if (p1_score == p2_score)
            {
                cout << "Determining who will go first..." << endl;

                int p1_roll;
                int p2_roll;
                do
                {
                    p1_roll = m_players[0]->RollOne(*m_dice);
                    p2_roll = m_players[1]->RollOne(*m_dice);
                    cout << m_players[0]->GetLogName() << " rolled a " << p1_roll << endl;
                    cout << m_players[1]->GetLogName() << " rolled a " << p2_roll << endl << endl;
                } while (p1_roll == p2_roll);

                if (p2_roll > p1_roll) swap(m_players[0], m_players[1]);
            }
            else if (p1_score > p2_score) swap(m_players[0], m_players[1]);
        }

        void Play()
        {
            cout << "Round " << m_roundNum << ":" << endl << endl;
            DetermineFirstPlayer();
            cout << m_players[0]->GetLogName() << " will go first." << endl;
        }

        // Constructors
        Round() {}; // Default

        Round(int a_roundNum, vector<shared_ptr<Player>> a_players, shared_ptr<Dice> a_dice) : m_roundNum(a_roundNum), m_players(a_players), m_dice(a_dice) {}
        
    private:
        vector<shared_ptr<Player>> m_players;
        shared_ptr<Dice> m_dice;

        int m_roundNum;
};