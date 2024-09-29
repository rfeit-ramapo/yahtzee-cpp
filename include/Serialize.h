#include <fstream>
#include "Scorecard.h"

using namespace std;

class Serialize
{
    public:
        // Function to load a game from a file.
        void LoadGame(int& a_currentRound, shared_ptr<Scorecard> a_scorecard, shared_ptr<Player> a_humanPlayer, shared_ptr<Player> a_pcPlayer);

        // Function to save current game to a file.
        void SaveGame(int a_currentRound, shared_ptr<Scorecard> a_scorecard);

        void ExitError();

        // Constructor
        Serialize() {};
        // Destructor
        ~Serialize()
        {
            m_file.close();
        }

    private:
        fstream m_file;
};