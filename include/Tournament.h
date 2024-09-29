#include <iostream>
#include "Human.h"
#include "Computer.h"
#include "Scorecard.h"
#include "StrategyEngine.h"

// Class to hold information about the entire tournament and kick off play.
class Tournament
{
public:
    
    // Constructors

    // Default constructor
    Tournament():
        m_players{make_shared<Human>(), make_shared<Computer>()},
        m_dice(make_shared<Dice>()),
        m_scorecard(make_shared<Scorecard>()),
        m_strat(make_shared<StrategyEngine>(m_scorecard))
    {};

    // Functions

    /* *********************************************************************
    Function Name: Play
    Purpose: To run the game of Yahtzee 
    Parameters: None
    Return Value: None
    Algorithm:
        1) Print the instructions
        2) Ask the player whether to load from a file
        3) Generate rounds of play until the scorecard is full
        4) Print the winner of the tournament
    Reference: none
    ********************************************************************* */
    void Play();

private:
    // Variables

    // The players participating in this tournament.
    vector<shared_ptr<Player>> m_players;
    // The dice set used in the tournament.
    shared_ptr<Dice> m_dice;
    // The scorecard used in the tournament.
    shared_ptr<Scorecard> m_scorecard;
    // A strategy generator to be used within the tournament.
    shared_ptr<const StrategyEngine> m_strat;
    // The current round.
    int m_roundNum = 1;

    // Internal Utility Functions

    /* *********************************************************************
    Function Name: PrintInstructions
    Purpose: To print the instructions and scorecard for the game 
    Parameters: None
    Return Value: None
    Algorithm:
        1) Print a basic overview of the game functionality
        2) Print the scorecard
        3) Confirm that the player has read the instructions and wishes to continue
    Reference: none
    ********************************************************************* */
    void PrintInstructions();

    /* *********************************************************************
    Function Name: PrintWinner
    Purpose: To print the determined winner of the Tournament 
    Parameters: None
    Return Value: None
    Algorithm:
        1) Print game completion confirmation
        2) Print both players' scores
        3) Determine winner based on player scores and print result
    Reference: none
    ********************************************************************* */
    void PrintWinner();
};