#include <iostream>
#include <iterator>
#include "Player.h"

using namespace std;

// Class to handle a turn of the game.
class Turn
{
public:
    // Constructors

    // Default
    Turn() {};

    // Including player, dice, strategy engine, and scorecard.
    Turn(
        shared_ptr<Player> a_player, 
        shared_ptr<Dice> a_dice, 
        shared_ptr<const StrategyEngine> a_strat, 
        shared_ptr<Scorecard> a_scorecard
    ) : m_player(a_player), 
        m_dice(a_dice), 
        m_strat(a_strat), 
        m_scorecard(a_scorecard) 
    {};

    /* *********************************************************************
    Function Name: Play
    Purpose: Plays out a turn of the game
    Parameters: 
                a_roundNum, the round this turn takes place during
    Return Value: None
    Algorithm:
        1) Print the turn header
        2) Roll the dice up to three times, or until the player stands
            3) After each roll, list possible categories, what to pursue, and whether to stand
        4) Player must choose what category to fill from the available options
        5) Prepare dice for next player's turn
    Reference: none
    ********************************************************************* */
    void Play(int a_roundNum);

private:
    // A pointer to the player whose turn it is
    shared_ptr<Player> m_player;
    // A pointer to the dice used to roll during this turn
    shared_ptr<Dice> m_dice;
    // A pointer to a const strategy engine, for generating strategies
    shared_ptr<const StrategyEngine> m_strat;
    // A pointer to the scorecard for strategizing and filling at the end of the turn
    shared_ptr<Scorecard> m_scorecard;
};