#include <string>
#include <vector>
#include <functional>
#include <memory>
#include "../include/Category.h"

using namespace std;

/*
    MULTIPLES CATEGORY
*/

/* *********************************************************************
Function Name: Score
Purpose: To calculate the score for a particular dice set.
Parameters: 
            a_dice, a constant reference to the dice set to check the score for.
Return Value: The score for this category with the given dice set
Algorithm:
        1) Calculate and return the score based on the face count and value
Reference: none
********************************************************************* */
int MultiplesCategory::Score(const Dice& a_dice) const 
{ 
    // The score = how many times this face appears * the value of the face
    return (a_dice.GetDiceCount()[m_multipleIndex] * (m_multipleIndex + 1)); 
}

/* *********************************************************************
Function Name: GetRerollStrategy
Purpose: To determine a strategy that will achieve this category, if possible.
Parameters: 
            a_dice, a pointer to const Dice to determine the strategy for.
Return Value: The strategy to achieve this category.
Algorithm:
        1) Return an empty strategy if the category is full
        2) Get the current score and dice values
        3) Determine what the ideal dice set would be for maximum points
        4) Return a strategy using the ideal dice set
Reference: none
********************************************************************* */    
Strategy MultiplesCategory::GetRerollStrategy(shared_ptr<const Dice> a_dice) const
{
    // Return a default, 0 score strategy if this category has already been filled.
    if (m_full) return Strategy();

    // Get the current score of the dice set, and dice face counts.
    int currentScore = Score(*a_dice);
    vector<int> currentDiceCounts = a_dice->GetDiceCount();

    // Try to determine what the best possible roll would look like.

    vector<int> perfectScore(Dice::NUM_DICE_FACES, 0);
    // Find all dice that are not locked and are not contributing to the current score.
    vector<int> unlockedUnscored = a_dice->GetUnlockedUnscored(perfectScore);
    // Determine how many dice can be rerolled.
    int rerolledDice = accumulate(unlockedUnscored.begin(), unlockedUnscored.end(), 0);
    // Add all possible rerolls to the scoring face.
    perfectScore[m_multipleIndex] = currentDiceCounts[m_multipleIndex] + rerolledDice;

    // Calculate maximum score from maximum possible dice of desired face
    int maxScore = (m_multipleIndex + 1) * perfectScore[m_multipleIndex];

    // Stand if there are no possible dice to reroll, or create a reroll strategy.
    if (!rerolledDice) return Strategy(currentScore, maxScore, GetName());
    else return Strategy(currentScore, maxScore, GetName(), a_dice, perfectScore, unlockedUnscored);
};



/*
    KIND CATEGORY
*/

/* *********************************************************************
Function Name: Score
Purpose: To calculate the score for a particular dice set.
Parameters: 
            a_dice, a constant reference to the dice set to check the score for.
Return Value: The score for this category with the given dice set
Algorithm:
        1) Loop through each face value and check how many dice match it
            2) Add the face value to the running score
            3) If there are enough of a kind, the condition to score is met
        4) Return either 0 (not enough of same dice) or the sum of dice faces
Reference: none
********************************************************************* */
int KindCategory::Score(const Dice& a_dice) const 
{
    bool condition_met = false;
    int score = 0;

    // Loop through counts for each face
    const vector<int>& diceValues = a_dice.GetDiceCount();
    for (int i = 0; i < Dice::NUM_DICE_FACES; ++i)
    {
        // Calculate score by adding face value * count
        score += diceValues[i] * (i + 1);
        // If there are enough of the same kind, the condition is met
        if (diceValues[i] >= m_numKind) condition_met = true;
    }
    // Either 0, or the sum of all dice faces
    return score * condition_met;
}
/* *********************************************************************
Function Name: Score
Purpose: To calculate the score for a particular dice set.
        This is an overloaded function to use for strategy evaluation.
Parameters: 
            a_dice, a constant reference to dice count values to check.
Return Value: The score for this category with the given dice set
Algorithm:
        1) Loop through each face value and check how many dice match it
            2) Add the face value to the running score
            3) If there are enough of a kind, the condition to score is met
        4) Return either 0 (not enough of same dice) or the sum of dice faces
Reference: none
********************************************************************* */
int KindCategory::Score(const vector<int>& a_diceValues) const
{
    bool condition_met = false;
    int score = 0;

    // Loop through counts for each face
    for (int i = 0; i < Dice::NUM_DICE_FACES; ++i)
    {
        // Calculate score by adding face value * count
        score += a_diceValues[i] * (i + 1);
        // If there are enough of the same kind, the condition is met
        if (a_diceValues[i] >= m_numKind) condition_met = true;
    }
    // Either 0, or the sum of all dice faces
    return score * condition_met;
}

/* *********************************************************************
Function Name: GetRerollStrategy
Purpose: To determine a strategy that will achieve this category, if possible.
Parameters: 
            a_dice, a pointer to const Dice to determine the strategy for.
Return Value: The strategy to achieve this category.
Algorithm:
        1) Return an empty strategy if the category is full
        2) Get the current score and dice values
        3) Loop backwards through dice faces
            4) Determine best dice set (highest sum) possible given locked dice and scoring face
            5) Return the first strategy that can score
        4) If no faces returned, this category is unachievable (return empty Strategy)
Reference: none
********************************************************************* */  
Strategy KindCategory::GetRerollStrategy(shared_ptr<const Dice> a_dice) const
{
    // Return a default, 0 score strategy if this category has already been filled.
    if (m_full) return Strategy();

    // Get the current score of the dice set, and dice face counts.
    int currentScore = Score(*a_dice);
    const vector<int>& diceValues = a_dice->GetDiceCount();

    // Try to determine what the best possible roll would look like.

    vector<int> idealDice;
    // Vector to hold dice that can be rerolled for a better score.
    vector<int> rerollable;
    // Loop through each dice face counting down. (The best score comes from higher faces.)
    for (int i = Dice::NUM_DICE_FACES - 1; i >= 0; --i)
    {
        // Keep track of minimum dice needed to score with this face.
        vector<int> minimumScore(Dice::NUM_DICE_FACES, 0);
        minimumScore[i] = m_numKind;

        // Set rerollable as any non-essential dice for scoring.
        rerollable = a_dice->GetUnlockedUnscored(minimumScore);

        // Ideal dice set must at minimum include locked dice.
        idealDice = a_dice->GetLockedDice();

        // Loop through each dice face value to convert rerollable dice 
        for (int j = 0; j < Dice::NUM_DICE_FACES; ++j)
        {
            // The number of rerollable dice of this face.
            int rerollableNum = rerollable[j];
            
            // Loop while there are rerollable dice and scoring face does not have enough.
            while (rerollableNum && (idealDice[i] < m_numKind) )
            {
                // Ideally, this rerolls into the scoring face.
                rerollableNum--;
                idealDice[i]++;
            }
            // Loop while there are rerollable dice (and scoring face has enough).
            while (rerollableNum)
            {
                // Ideally, this rerolls into the maximum face value (because it results in a larger sum).
                rerollableNum--;
                idealDice[Dice::NUM_DICE_FACES - 1]++;
            }
        }

        // If the requisite number of scoring faces were reached...
        if (idealDice[i] >= m_numKind)
        {
            // Recalculate rerollable to account for ideal dice values for maximum score
            rerollable = a_dice->GetUnlockedUnscored(idealDice);
            int maxScore = Score(idealDice);
            // Return a reroll strategy.
            return Strategy(currentScore, maxScore, GetName(), a_dice, idealDice, rerollable);
        }
    }

    // If no face values returned, this means it is impossible to get this category.
    return Strategy();
}



/*
    FULL HOUSE CATEGORY
*/

/* *********************************************************************
Function Name: Score
Purpose: To calculate the score for a particular dice set.
Parameters: 
            a_dice, a constant reference to the dice set to check the score for.
Return Value: The score for this category with the given dice set
Algorithm:
        1) Loop through each face value and check how many dice match it
            2) If there are 3 of a kind, the first condition is met
            3) If there are 2 of a kind, the second condition is met
        4) Return either 0 (conditions unmet) or the set score
Reference: none
********************************************************************* */
int FullHouseCategory::Score(const Dice& a_dice) const 
{ 
    // Condition of 3 of a kind
    int condition1_met = false;
    // Conditino of 2 of a kind
    int condition2_met = false;

    // Loop through counts for each face
    const vector<int>& diceValues = a_dice.GetDiceCount();
    for (int i = 0; i < diceValues.size(); ++i)
    {
        // 3 faces are the same
        if (diceValues[i] == 3) condition1_met = true;
        // 2 faces are the same
        else if (diceValues[i] == 2) condition2_met = true;
    }

    // Return the score only if both conditions were met, otherwise 0
    return FULL_HOUSE_SCORE * condition1_met * condition2_met;
}

/* *********************************************************************
Function Name: GetRerollStrategy
Purpose: To determine a strategy that will achieve this category, if possible.
Parameters: 
            a_dice, a pointer to const Dice to determine the strategy for.
Return Value: The strategy to achieve this category.
Algorithm:
        1) Return an empty strategy if the category is full
        2) Return a stand strategy if this dice set scores already
        3) Determine the mode and secondary mode from locked dice
            4) If more than 3 faces are locked, or more than 3 dice of any face are locked, return empty strategy (impossible to score)
        5) Determine the mode and secondary mode from all dice
        6) Determine which face to aim for 3 and which to aim for 2
        7) Create a strategy based on these modes
Reference: none
********************************************************************* */  
Strategy FullHouseCategory::GetRerollStrategy(shared_ptr<const Dice> a_dice) const
{
    // Return a default, 0 score strategy if this category has already been filled.
    if (m_full) return Strategy();

    // If this scores, stand because you always get maximum points in this category.
    int currentScore = Score(*a_dice);
    if (currentScore) return Strategy(currentScore, currentScore, GetName());

    // Check locked dice to see if this strategy is possible.

    vector<int> lockedDice = a_dice->GetLockedDice();
    // The number of locked faces
    int lockedFaces = 0;
    // The mode (face value with most dice) among locked faces
    int lockedMode1 = -1;
    // The second-highest mode among locked faces
    int lockedMode2 = -1;
    // The current maximum of number of locked faces
    int lockedMaxCount = 0;

    // Loop through each dice face and check for locked dice.
    for (int i = 0; i < Dice::NUM_DICE_FACES; ++i)
    {
        if (lockedDice[i])
        {
            // Check if this is the new mode amongst locked dice.
            if (lockedFaces && (lockedDice[i] > lockedMaxCount))
            {
                // Set the mode and the number of dice that are locked.
                lockedMaxCount = lockedDice[i];
                // Shift the previus mode.
                lockedMode2 = lockedMode1;
                lockedMode1 = i;
            }
            // If not, it should be the second mode (there can be a maximum of two locked faces).
            else lockedMode2 = i;
            lockedFaces++;
        }
        // Impossible to score if a face has more than 3 locked dice, so return.
        if (lockedDice[i] > 3) return Strategy();
    }
    // Impossible to score if more than two face values have locked dice, so return.
    if (lockedFaces > 2) return Strategy();    

    // Check the mode amongst all dice

    int mode1 = -1;
    int mode2 = -1;
    int maxCount1 = 0;
    int maxCount2 = 0;

    const vector<int>& diceValues = a_dice->GetDiceCount();
    for (int i = 0; i < Dice::NUM_DICE_FACES; ++i)
    {
        // Set the maximum mode to this face if it exceeds the current mode.
        if (diceValues[i] > maxCount1)
        {
            // Shift current mode to secondary.
            mode2 = mode1;
            maxCount2 = maxCount1;
            // Set to this face.
            mode1 = i;
            maxCount1 = diceValues[i];
        }
        // If it is not greater than the maximum, but is greater than the secondary...
        else if (diceValues[i] > maxCount2)
        {
            // Simply drop the secondary mode and replace.
            mode2 = i;
            maxCount2 = diceValues[i];
        }
    }

    // Check which mode values to use.

    // If the mode does not have at least 2 values, remove it
    if (maxCount1 == 1) mode1 = -1;
    if (maxCount2 == 1) mode2 = -1;

    if (lockedMode1 >= 0)
    {
        // If there are two locked faces, you must use those.
        if (lockedMode2 >= 0)
        {
            mode1 = lockedMode1;
            mode2 = lockedMode2;
        }
        // If the locked mode and actual mode are different
        else if (mode1 != lockedMode1)
        {
            // If the locked mode is less than the actual mode, set it as secondary.
            if (maxCount1 > lockedMaxCount) mode2 = lockedMode1;
            // Otherwise, shift the actual mode to be secondary and locked mode comes first.
            else
            {
                mode2 = mode1;
                mode1 = lockedMode1;
            }
        }
    }

    // Ideal dice will always be 3 of mode1 and 2 of mode2.
    vector<int> idealDice(6, 0);
    if (mode1 >= 0) idealDice[mode1] = 3;
    if (mode2 >= 0) idealDice[mode2] = 2;

    // Return a strategy that rerolls all nonscoring dice.
    vector<int> toReroll = a_dice->GetUnlockedUnscored(idealDice);
    return Strategy(currentScore, FULL_HOUSE_SCORE, GetName(), a_dice, idealDice, toReroll);
}



/*
    STRAIGHT CATEGORY
*/

/* *********************************************************************
Function Name: Score
Purpose: To calculate the score for a particular dice set.
Parameters: 
            a_dice, a constant reference to the dice set to check the score for.
Return Value: The score for this category with the given dice set
Algorithm:
        1) Loop through each face value and check the dice count
            2) Add to a streak if there is at least one
            3) Otherwise, reset the streak
            4) Once the required streak number is met, return set score
        5) If loop completes without returning, do not score
Reference: none
********************************************************************* */
int StraightCategory::Score(const Dice& a_dice) const 
{ 
    int streak = 0;

    // Loop through dice face counts
    const vector<int>& diceValues = a_dice.GetDiceCount();
    for (int i = 0; i < 6; i++)
    {
        // Add to the streak for every successive face that exists
        if (diceValues[i] >= 1) streak++;
        // Otherwise, reset the streak
        else streak = 0;

        // Once the streak hits the required value, return immediately
        if (streak == m_streakNum) return m_scoreValue;
    }

    // If the streak requirement was not met, do not score.
    return 0;
}

/* *********************************************************************
Function Name: GetRerollStrategy
Purpose: To determine a strategy that will achieve this category, if possible.
Parameters: 
            a_dice, a pointer to const Dice to determine the strategy for.
Return Value: The strategy to achieve this category.
Algorithm:
        1) Return an empty strategy if the category is full
        2) Return a stand strategy if this dice set scores already
        3) Create a vector of all possible dice configurations for this category
        4) Loop through the vector
            5) Check which dice need to be rerolled to achieve each configuration
                6) If more rerolls are required than are available, it is impossible
                7) If it is possible and requires less rerolls than any previous config, use this
        8) If no configurations were possible, return an empty Strategy
        9) Otherwise, return the best strategy found (fewest rerolls needed)
Reference: none
********************************************************************* */  
Strategy StraightCategory::GetRerollStrategy(shared_ptr<const Dice> a_dice) const
{
    // Return a default, 0 score strategy if this category has already been filled.
    if (m_full) return Strategy();

    // If this scores, stand because you always get maximum points in this category.
    int currentScore = Score(*a_dice);
    if (currentScore) return Strategy(currentScore, currentScore, GetName());

    // If this doesn't score, decide which dice to reroll.

    // There are only a set few minimum values for 4 and 5 straight.
    // Add each to a vector for review.
    vector<vector<int>> dicesetsToCheck;
    if (m_streakNum == 4)
    {
        dicesetsToCheck.push_back({0, 1, 1, 1, 1, 0});
        dicesetsToCheck.push_back({1, 1, 1, 1, 0, 0});
        dicesetsToCheck.push_back({0, 0, 1, 1, 1, 1});
    }
    else if (m_streakNum == 5)
    {
        dicesetsToCheck.push_back({0, 1, 1, 1, 1, 1});
        dicesetsToCheck.push_back({1, 1, 1, 1, 1, 0});
    }

    // Check Straight restrictions

    // Current minimum number of rerolls required to achieve this category.
    int minRerollNum = 0;
    // Track which dice should be rerolled.
    vector<int> toReroll;
    vector<int> idealDice;

    const vector<int>& diceValues = a_dice->GetDiceCount();
    vector<int> lockedDice = a_dice->GetLockedDice();
    
    // Go through each possible configuration to check which is possible and/or the best.
    for (int i = 0; i < dicesetsToCheck.size(); ++i)
    {
        // Start the attempt with required (locked) dice.
        vector<int> straightAttempt = lockedDice; 

        // Find all nonscoring dice and add them up.
        vector<int> checkRerolls = a_dice->GetUnlockedUnscored(dicesetsToCheck[i]);
        int rerollsAvailable = accumulate(checkRerolls.begin(), checkRerolls.end(), 0);

        // Loop through each face to find how many need to be rerolled.
        int rerollsNeeded = 0;
        for (int j = 0; j < Dice::NUM_DICE_FACES; ++j)
        {
            // If locked dice does not already include this face, but this config does
            if (diceValues[j] < dicesetsToCheck[i][j])
            {
                // Use a reroll to try and fill this hole.
                rerollsNeeded++;
                straightAttempt[j]++;
                // If we ran out of rerolls, this is not viable.
                if (rerollsNeeded > rerollsAvailable) break;
            }
            // There is at least one die of this face (and it is required)
            else if (dicesetsToCheck[i][j]) 
            {
                // Keep either 1, or however many are locked.
                straightAttempt[j] = max(1, straightAttempt[j]);
            }
        }

        // Ran out of rerolls, so this configuration is impossible.
        if (rerollsNeeded > rerollsAvailable) continue;

        // If an option has not been set, or this configuration requires fewer rerolls than before
        if (!minRerollNum || (minRerollNum > rerollsNeeded))
        {
            // Set the new minimum rerolls, target dice config, and dice to reroll
            minRerollNum = rerollsNeeded;
            idealDice = straightAttempt;
            toReroll = checkRerolls;
        }
    }

    // If there were no rerolls, this means that every config failed and this category is impossible given the current diceset.
    if (!minRerollNum) return Strategy();
    // Otherwise, return the best configuration found.
    return Strategy(currentScore, m_scoreValue, GetName(), a_dice, idealDice, toReroll);
}



/*
    YAHTZEE CATEGORY
*/

/* *********************************************************************
Function Name: Score
Purpose: To calculate the score for a particular dice set.
Parameters: 
            a_dice, a constant reference to the dice set to check the score for.
Return Value: The score for this category with the given dice set
Algorithm:
        1) Loop through each face value and check the dice count
            2) If any values have all dice, return the set score
        3) If loop completes without returning, do not score
Reference: none
********************************************************************* */
int YahtzeeCategory::Score(const Dice& a_dice) const 
{ 
    const vector<int>& diceValues = a_dice.GetDiceCount();
    for (int i = 0; i < diceValues.size(); i++) 
    {
        if (diceValues[i] == Dice::NUM_DICE) return YAHTZEE_SCORE;
    }
    
    return 0;
}

/* *********************************************************************
Function Name: GetRerollStrategy
Purpose: To determine a strategy that will achieve this category, if possible.
Parameters: 
            a_dice, a pointer to const Dice to determine the strategy for.
Return Value: The strategy to achieve this category.
Algorithm:
        1) Return an empty strategy if the category is full
        2) Return a stand strategy if this dice set scores already
        3) Check for locked dice faces to see if this category is possible
            4) If there is more than one locked face, return an empty Strategy (impossible)
        4) Use either the locked dice face or mode of all dice to pursue
        5) Return a reroll strategy based on selected face
Reference: none
********************************************************************* */ 
Strategy YahtzeeCategory::GetRerollStrategy(shared_ptr<const Dice> a_dice) const
{
    // Return a default, 0 score strategy if this category has already been filled.
    if (m_full) return Strategy();

    // If this scores, stand because you always get maximum points in this category
    int currentScore = Score(*a_dice);
    if (currentScore) return Strategy(currentScore, currentScore, GetName());
    
    // Check locked dice to see if this strategy is possible.

    vector<int> lockedDice = a_dice->GetLockedDice();
    // The number of faces with locked dice
    int lockedFaces = 0;
    // The index of the locked dice face, if one exists
    int lockedIndex = -1;

    for (int i = 0; i < Dice::NUM_DICE_FACES; ++i)
    {
        // If this dice face is locked, update index and face count.
        if (lockedDice[i])
        {
            lockedFaces++;
            lockedIndex = i;
        }
    }
    // Impossible if more than one face value has locked dice; return empty Strategy.
    if (lockedFaces > 1) return Strategy();

    // If there are locked dice, use those to score.
    vector<int> idealDice(6, 0);
    if (lockedIndex >= 0) idealDice[lockedIndex] = Dice::NUM_DICE;
    // Otherwise, use the mode of all other dice.
    else
    {
        int mode;
        int maxCount = 0;
        const vector<int>& diceValues = a_dice->GetDiceCount();
        for (int i = 0; i < Dice::NUM_DICE_FACES; ++i)
        {
            if (diceValues[i] >= maxCount)
            {
                mode = i;
                maxCount = diceValues[i];
            }
        }
        idealDice[mode] = Dice::NUM_DICE;
    }
    
    // Return reroll strategy based on determined dice.
    vector<int> toReroll = a_dice->GetUnlockedUnscored(idealDice);
    return Strategy(currentScore, YAHTZEE_SCORE, GetName(), a_dice, idealDice, toReroll);
}