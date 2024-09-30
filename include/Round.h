#include <string>
#include <memory>
#include <iostream>
#include "Dice.h"
#include "Player.h"

using namespace std;

// For handling a round of the game.
class Round
{
public:
    // Constructors

    // Default
    Round() {}; // Default

    // Including round number, players, dice, strategy engine, and scorecard.
    Round(
        int a_roundNum, 
        vector<shared_ptr<Player>> a_players, 
        shared_ptr<Dice> a_dice, 
        shared_ptr<const StrategyEngine> a_strat, 
        shared_ptr<Scorecard> a_scorecard
    ) : m_roundNum(a_roundNum), 
        m_players(a_players), 
        m_dice(a_dice), 
        m_strat(a_strat), 
        m_scorecard(a_scorecard) 
    {};

    /* *********************************************************************
    Function Name: Play
    Purpose: Plays this round out
    Parameters: None
    Return Value: None
    Algorithm:
        1) Prints the round info
        2) Determines and prints who will go first in this round
        3) Completes player 1's turn
            4) If player 1 finished the game, ends the round early
        5) Completes player 2's turn
        6) Prints scores for both players before ending round
    Reference: none
    ********************************************************************* */
    void Play();
    
private:
    // A vector holding pointers to the players
    vector<shared_ptr<Player>> m_players;
    // A pointer to the dice set for this game
    shared_ptr<Dice> m_dice;
    // A pointer to the strategy engine
    shared_ptr<const StrategyEngine> m_strat;
    // A pointer to this game's scorecard
    shared_ptr<Scorecard> m_scorecard;
    // The current round number
    int m_roundNum;

    /* *********************************************************************
    Function Name: DetermineFirstPlayer
    Purpose: Swaps the order of the player vector according to turn order
    Parameters: None
    Return Value: None
    Algorithm:
        1) Gets the scores for each player
        2) If they are equal, make players roll dice until one has higher roll
        3) If player 2 should go first, swap player positions in vector
    Reference: none
    ********************************************************************* */
    void DetermineFirstPlayer();
};