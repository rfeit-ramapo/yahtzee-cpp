#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Serialize.h"

void Serialize::LoadGame(int& a_currentRound, shared_ptr<Scorecard> a_scorecard, shared_ptr<Player> a_humanPlayer, shared_ptr<Player> a_pcPlayer)
{
    // Try to open file specified by user
    cout << "Please input the name of the file to load from." << endl;
    while (true)
    {
        string input;
        getline(cin, input);

        m_file.open(input, ios::in);

        if (!m_file)
        {
            cerr << "Error: Could not open desired file. Please try again." << endl;
            continue;
        }
        break;
    }

    // Parse each line to get desired info.
    int currentRound;
    vector<int> categories;
    vector<int> scores;
    vector<string> winners;
    vector<int> rounds;

    string line;
    string word;

    // Round line
    getline(m_file, line);
    istringstream iss(line);

    iss >> word;
    if (word != "Round:") ExitError();
    iss >> word;
    try
    {
        currentRound = stoi(word);
    }
    catch (const invalid_argument& e)
    {
        ExitError();
    }

    // Scorecard line
    getline(m_file, line);
    if (line != "") ExitError();
    getline(m_file, line);
    iss.clear();
    iss.str(line);
    iss >> word;
    if (word != "Scorecard:") ExitError();

    // Go through each category line and extract info
    int index = 0;
    while (getline(m_file, line))
    {
        if (line.empty()) continue;
        if (index > 11) ExitError();

        iss.clear();
        iss.str(line);
        int score, roundNumber;
        string winner;

        if (!(iss >> score)) ExitError();

        if (score == 0)
        {
            // There should be nothing else on this line
            if (!iss.eof()) ExitError();
            ++index;
            continue;
        }

        if (!(iss >> winner >> roundNumber)) ExitError();
        if (!iss.eof() || (winner != "Human") && (winner != "Computer")) ExitError();

        categories.push_back(index);
        scores.push_back(score);
        winners.push_back(winner);
        rounds.push_back(roundNumber);

        ++index;
    }

    // Adjust the given round variable and scorecard accordingly.
    a_currentRound = currentRound;
    a_scorecard->FillMultiple(categories, scores, winners, rounds, a_humanPlayer, a_pcPlayer);

    cout << "Serialization file successfully processed!" << endl << endl;
    a_scorecard->Print();
}

void Serialize::SaveGame(int a_currentRound, shared_ptr<Scorecard> a_scorecard)
{
    m_file.close();
    m_file.open("save_game.txt", ios::out);
    if (!m_file.is_open())
    {
        cerr << "Error: Could not save game file. Exiting program." << endl;
        exit(1);
    }

    // Output serialization header, including current round
    m_file << "Round: " << a_currentRound << endl << endl;
    m_file << "Scorecard:" << endl;
    
    // Loop through each category and save data
    vector<shared_ptr<Category>> categories = a_scorecard->GetCategories();
    for (int i = 0; i < 12; ++i)
    {
        if (!categories[i]->IsFull()) 
        {
            m_file << "0" << endl;
        }
        else
        {
            m_file << 
                categories[i]->GetPoints() << " " << 
                categories[i]->GetWinner() << " " << 
                categories[i]->GetRound() << endl;

        }
    }

    cout << "Game saved successfully! Exiting..." << endl;
    exit(0);
}

void Serialize::ExitError()
{
    cerr << "Error: Incorrect format for serialization file. Exiting program." << endl;
    exit(1);
}