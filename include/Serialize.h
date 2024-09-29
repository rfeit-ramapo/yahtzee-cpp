#include <fstream>
#include <iostream>
#include "Scorecard.h"

// Class to handle serialization (game saving & loading).
class Serialize
{
public:

    // Default constructor
    Serialize() {};
    // Destructor
    ~Serialize()
    {
        // Close the file before destroying class
        m_file.close();
    }

    // Functions

    /* *********************************************************************
    Function Name: LoadGame
    Purpose: To load game info from a serialization file
    Parameters:
                a_currentRound, the integer that holds the round, passed by reference.
                    It will change to reflect the round as loaded from the file.
                a_scorecard, a Scorecard to alter, passed as a pointer.
                    It will update to reflect the rounds played in the serialization file.
                a_humanPlayer, a pointer to the Human player.
                    It will update this player's total points based on the file.
                a_pcPlayer, a pointer to the Computer player.
                    It will update this player's total points based on the file.
    Return Value: None
    Algorithm:
            1) Open the desired file
            2) Parse the Round number
            3) Parse Scorecard line (ensuring correct format)
            4) Loop through each line of the scorecard and update values
            Note that if loading fails at any point, the program will exit with an error.
    Reference: I received help with understanding istringstream functionality from ChatGPT.
    ********************************************************************* */
    void LoadGame(
        int& a_currentRound, 
        shared_ptr<Scorecard> a_scorecard, 
        shared_ptr<Player> a_humanPlayer, 
        shared_ptr<Player> a_pcPlayer
    );

    /* *********************************************************************
    Function Name: SaveGame
    Purpose: To save game info into a serialization file
    Parameters:
                a_currentRound, the current round number to record.
                a_scorecard, a Scorecard, passed const by a pointer, to pull info from.
    Return Value: None
    Algorithm:
            1) Open the desired file
            2) Write the header information (including Round #)
            3) Loop through each category and specify details of how it was filled
    Reference: none
    ********************************************************************* */
    void SaveGame(int a_currentRound, shared_ptr<const Scorecard> a_scorecard);

private:

    // Variables

    // Holds the file used for reading/writing
    fstream m_file;

    // Utility Functions

    /* *********************************************************************
    Function Name: OpenFile
    Purpose: Opens a user-specified file for read or write
    Parameters: 
                a_write, a bool deciding whether the file should open for writing
    Return Value: none
    Algorithm:
            1) Log an error to the console
            2) Exit the program
    Reference: none
    ********************************************************************* */
    void OpenFile(bool a_write);

    /* *********************************************************************
    Function Name: ExitError
    Purpose: Simple function to log an error with serialization and exit the program
    Parameters: none
    Return Value: none
    Algorithm:
            1) Log an error to the console
            2) Exit the program
    Reference: none
    ********************************************************************* */
    inline void ExitError()
    {
        cerr << "Error: Incorrect format for serialization file. Exiting program." << endl;
        exit(1);
    }
};