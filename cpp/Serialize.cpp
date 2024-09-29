#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "../include/Serialize.h"

using namespace std;

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
void Serialize::LoadGame(
    int& a_currentRound, 
    shared_ptr<Scorecard> a_scorecard, 
    shared_ptr<Player> a_humanPlayer, 
    shared_ptr<Player> a_pcPlayer
)
{
    // Try to open file specified by user
    cout << "Please input the name of the file to load from." << endl;
    OpenFile(false);

    // Parse each line to get desired info.

    // Variables to be updated in Scorecard & Tournament
    int currentRound;
    vector<int> categories;
    vector<int> scores;
    vector<string> winners;
    vector<int> rounds;

    // Variables for parsing the file
    string line;
    string word;

    // Parse the "Round:" part of the file
    getline(m_file, line);
    istringstream iss(line);
    iss >> word;
    if (word != "Round:") ExitError();

    // Parse the actual round number
    iss >> word;
    try
    {
        currentRound = stoi(word);
    }
    catch (const invalid_argument& e)
    {
        ExitError();
    }

    // Parse the blank line
    getline(m_file, line);
    // Ensure the line is either empty or has only spaces
    if (!all_of(line.begin(), line.end(), [](unsigned char c) { return isspace(c); })) 
    {
        ExitError();
    }

    // Parse the "Scorecard:" line
    getline(m_file, line);
    iss.clear();
    iss.str(line);
    iss >> word;
    if (word != "Scorecard:") ExitError();

    // Loop through every line until all categories are processed
    int categoryIndex = 0;
    while (getline(m_file, line))
    {
        // Skip blank lines
        if (line.empty()) continue;
        // Once all categories have been processed, there should be no extra non-blank lines.
        if (categoryIndex == Scorecard::NUM_CATEGORIES) ExitError();

        // Variables to hold extracted info from each line
        int score, roundNumber;
        string winner;
        string remaining;

        // Extract the score
        iss.clear();
        iss.str(line);
        if (!(iss >> score)) ExitError();

        // If the score is 0, there is no need to update this category
        if (score == 0)
        {
            // There should be no other characters remaining
            getline(iss, remaining);
            if (!all_of(
                remaining.begin(), 
                remaining.end(), 
                [](unsigned char c) { return isspace(c); })
            ) 
            {
                ExitError();
            }
            // Update the index and go onto the next line
            ++categoryIndex;
            continue;
        }

        // Attempt to extract the winner and the round this was scored.
        if (!(iss >> winner >> roundNumber)) ExitError();
        // There should be no other characters on this line
        getline(iss, remaining);
        if (!all_of(
            remaining.begin(), 
            remaining.end(), 
            [](unsigned char c) { return isspace(c); })
            // The winner must be either the "Human" or "Computer"
            || ((winner != "Human") && (winner != "Computer"))
        ) 
        {
            ExitError();
        }

        // If all checks were passed, add the updated info to each vector.
        categories.push_back(categoryIndex);
        scores.push_back(score);
        winners.push_back(winner);
        rounds.push_back(roundNumber);

        ++categoryIndex;
    }

    // Adjust the given round variable and scorecard accordingly.
    a_currentRound = currentRound;
    a_scorecard->FillMultiple(categories, scores, winners, rounds, a_humanPlayer, a_pcPlayer);

    // Print success and the updated scorecard.
    cout << "Serialization file successfully processed!" << endl << endl;
    a_scorecard->Print();
}

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
void Serialize::SaveGame(int a_currentRound, shared_ptr<const Scorecard> a_scorecard)
{
    // Close the file in case it was opened for reading earlier.
    m_file.close();
    // Open file for writing.
    cout << "Please input the name of the file to save to." << endl;
    OpenFile(true);

    // Output serialization header, including current round
    m_file << "Round: " << a_currentRound << endl << endl;
    m_file << "Scorecard:" << endl;
    
    // Loop through each category and save data.
    const vector<shared_ptr<Category>> categories = a_scorecard->GetCategories();
    for (int i = 0; i < Scorecard::NUM_CATEGORIES; ++i)
    {
        // If this category was not filled, just write a 0.
        if (!categories[i]->IsFull()) 
        {
            m_file << "0" << endl;
        }
        // Otherwise, output all info to the file.
        else
        {
            m_file << 
                categories[i]->GetPoints() << " " << 
                categories[i]->GetWinner() << " " << 
                categories[i]->GetRound() << endl;
        }
    }

    // Confirm success and exit the game.
    cout << "Game saved successfully! Exiting..." << endl;
    exit(0);
}

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
void Serialize::OpenFile(bool a_write)
{
    // Loop until the user inputs something valid.
    while (true)
    {
        // Get user input.
        string input;
        getline(cin, input);

        // Open either for writing or reading.
        if (a_write) m_file.open(input, ios::out);
        else m_file.open(input, ios::in);

        // Log any errors and prompt user again.
        if (!m_file)
        {
            cerr << "Error: Could not open desired file. Please try again." << endl;
            continue;
        }
        break;
    }
}