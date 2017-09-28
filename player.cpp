/*
 * Author: Alexia Soucy, 40014822
 * Course: COMP 345, section D
 * Assignment: 1
 */

#include <iostream>
#include "player.h"
using std::cin;
using std::cout;
using std::endl;

// Creates a new player with no allocated troops.
Player::Player()
{
    playerName = "";
    playerTroops = 0;
    hasConquered = false;
    setDice();
    setHand();
}

// Creates a new named player with no allocated troops.
Player::Player(string playerName)
{
    this->playerName = playerName;
    playerTroops = 0;
    hasConquered = false;
    setDice();
    setHand();
}

// Initializes the player's dice object.
void Player::setDice()
{
    Dice playerDice; // Create Dice object with default constructor on heap.
}

// Returns the player's dice object.
Dice Player::getDice()
{
    return playerDice;
}

// Initializes the player's hand object.
void Player::setHand()
{
    Hand playerHand;
}

// Returns the player's hand object.
Hand& Player::getHand()
{
    return playerHand;
}

// Returns the number of troops the player possesses.
int Player::getTroops()
{
    return playerTroops;
}

// Grants new troops to the player.
void Player::addTroops(int troops)
{
    playerTroops += troops;
}

// Takes away troops from the player.
void Player::subtractTroops(int troops)
{
    playerTroops -= troops;
}

// Returns the collection of countries the player owns.
vector<Country*> Player::getCountries()
{
    return countries;
}

// Adds a country to the player's country collection.
void Player::addCountry(Country* country)
{
    countries.push_back(country);
}

// Removes a country to the player's country collection.
void Player::removeCountry(Country* country)
{
    // Search the player's country collection to find where the target is, then erase it.
    for(int i = 0; i < countries.size(); i++)
    {
        if (countries.at(i) == country)
            countries.erase(countries.begin() + i);
    }
}

// Takes troops from a player and deploys them to an owned territory.
void Player::reinforce(int troops, Country* country)
{
    /*
     * Confirm that the player has enough troops, otherwise give an error
     * message and let the function terminate.
     */
    if (troops <= playerTroops && troops > 0)
    {
        // Marker to validate the presence of the country in the player's collection.
        bool countryValid = false;
        
        // Check the player's collection, validate if the country is found.
        for (int i = 0; i < countries.size(); i++)
        {
            if (countries.at(i)->getName() == country->getName())
            {
                countryValid = true;
                break;
            }
        }
        
        // If the country is found, add parametized troops to it and subtract them from the player's troops.
        if (countryValid)
        {
            country->setArmyNum(country->getArmyNum() + troops);
            playerTroops -= troops;
            cout << country->getName() << " reinforced with " << troops << " troops." << endl;
        }
        else
            cout << country->getName() << " is not owned by " << playerName << "; reinforcement aborted." << endl;
        
    }
    else if (troops > 0)
        cout << "Not enough troops; this action cannot be taken." << endl;
    else
        cout << "Cannot reinforce with 0 or fewer troops." << endl;
    
    cout << playerName << " has " << playerTroops << " deployable troops." << endl;
}

void Player::attack(Map map, Country* attackingCountry, Country* defendingCountry)
{
    /* 
     * The following conditions must be met for a valid attack:
     * - The attacking country belongs to the attacker.
     * - The defending country does not belong to the attacker.
     * - The two countries are adjacent.
     * - The attacking country has more than 1 army in it.
     */
    
    // Markers to ensure the attacking country is owned by the correct player 
    // and that the attack as a whole is valid.
    bool attackingCountryValid = false;
    bool attackValid = false;
        
    // Check the player's collection, validate if the country is found.
    for (int i = 0; i < countries.size(); i++)
    {
        if (countries.at(i)->getName() == attackingCountry->getName())
        {
            attackingCountryValid = true;
            break;
        }
    }
    
    // Continue if the attacking country is owned by the attacking player.
    if (attackingCountryValid)
    {
        // Check if the defending country belongs to an opponent.
        if (defendingCountry->getPlayerName() != playerName)
        {
            // Check if the two countries are adjacent.
            if (map.areAdjacent(*attackingCountry, *defendingCountry))
            {
                if (attackingCountry->getArmyNum() > 1)
                {
                    attackValid = true;
                }
                else
                    cout << attackingCountry->getName() << " doesn't have enough troops to attack." << endl;
            }
            else
                cout << attackingCountry->getName() << " and " << defendingCountry->getName() << " are not adjacent." << endl;
        }
        else
            cout << defendingCountry->getName() << " is already owned by " << playerName << "." << endl;
    }
    else
        cout << attackingCountry->getName() << "is not owned by " << playerName << "." << endl;
    
    // If the attack conditions are met
    if (attackValid)
    {
        // Number of dice used by each player.
        int attackDiceCount = 0;
        int defenseDiceCount = 0;
        
        /*
         * Loop dice count requests until a valid number is selected.
         * There must be 1, 2, or 3 attacking dice, and less than the number 
         * of armies in the attacking country.
         */
        while(attackDiceCount > 0 && attackDiceCount <= 3 && attackDiceCount < attackingCountry->getArmyNum())
        {
            cout << "Enter the number of dice used to attack: ";
            cin >> attackDiceCount;
            cout << endl;
            
            if (attackDiceCount <= 0)
                cout << "A positive number of dice must be used to attack." << endl;
            else if (attackDiceCount >= attackingCountry->getArmyNum())
                cout << "Fewer than " << attackingCountry->getArmyNum() << " dice must be used to attack." << endl;
            else if (attackDiceCount > 3)
                cout << "3 dice or less must be used to attack." << endl;
        }
        
        /*
         * Loop dice count requests until a valid number is selected.
         * There must be 1, 2, or 3 attacking dice, and less or as many  
         * as the number of armies in the attacking country.
         */
        while(defenseDiceCount > 0 && defenseDiceCount <= 2 && defenseDiceCount <= defendingCountry->getArmyNum())
        {
            cout << "Enter the number of dice used to defend: ";
            cin >> defenseDiceCount;
            cout << endl;
            
            if (defenseDiceCount <= 0)
                cout << "A positive number of dice must be used to defend." << endl;
            else if (defenseDiceCount > defendingCountry->getArmyNum())
                cout << defendingCountry->getArmyNum() << " dice or less must be used to defend." << endl;
            else if (defenseDiceCount > 2)
                cout << "2 dice or less must be used to defend." << endl;
        }
        
        // Variables used to keep track of attack and defense rolls.
        int bestAttack = 0;
        int secondBestAttack = 0;
        
        int bestDefense = 0;
        int secondBestDefense = 0;
        
        int tempRoll;
        
        // Roll the attack die as many times as necessary, sort the results.
        for (int i = 0; i < attackDiceCount; i++)
        {
            tempRoll = playerDice.randomiser();
            
            cout << playerName << " rolled a " << tempRoll << "." << endl;
            
            if (tempRoll >= bestAttack) {
                secondBestAttack = bestAttack;
                bestAttack = tempRoll;
            }
            else if (tempRoll >= secondBestAttack)
                secondBestAttack = tempRoll;
        }
        
        // Roll the defense die as many times as necessary, sort the results.
        for (int i = 0; i < defenseDiceCount; i++)
        {
            tempRoll = playerDice.randomiser();
            
            cout << defendingCountry->getPlayerName() << " rolled a " << tempRoll << "." << endl;
            
            if (tempRoll >= bestDefense) {
                secondBestDefense = bestDefense;
                bestDefense = tempRoll;
            }
            else if (tempRoll >= secondBestDefense)
                secondBestDefense = tempRoll;
        }
        
        // Count the number of wins for the attack and defense.
        int attackWins = 0;
        int defenseWins = 0;
        
        if (bestAttack > bestDefense)
            attackWins++;
        else
            defenseWins++;
        
        // check second-best dice if both players used two dice or more.
        if (defenseDiceCount == 2 && attackDiceCount >= 2)
            if (secondBestAttack > secondBestDefense)
                attackWins++;
            else
                defenseWins++;
        
        // Report the losses on each side.
        if (defenseWins == 1)
            cout << playerName << " lost 1 army!" << endl;
        else
            cout << playerName << " lost " << defenseWins << " armies!" << endl;
        
        if (attackWins == 1)
            cout << defendingCountry->getPlayerName() << " lost 1 army!" << endl;
        else
            cout << defendingCountry->getPlayerName() << " lost " << defenseWins << " armies!" << endl;
        
        // Adjust the armies in each country as a result of the attack.
        attackingCountry->setArmyNum(attackingCountry->getArmyNum() - defenseWins);
        defendingCountry->setArmyNum(defendingCountry->getArmyNum() - attackWins);
        
        // Report on the current state of the attacking country.
        cout << playerName << " now has " << attackingCountry->getArmyNum() << " armies in " << attackingCountry->getName() << "." << endl;
        if (attackingCountry->getArmyNum() == 1)
            cout << attackingCountry->getName() << " can no longer attack." << endl;
        
        // Report on the current state of the defending country.
        // If conquered, move troops and transfer ownership.
        cout << defendingCountry->getPlayerName() << " now has " << defendingCountry->getArmyNum() << " armies in " << defendingCountry->getName() << "." << endl;
        if (defendingCountry->getArmyNum() == 0)
        {
            // Keep track of the armies selected to move.
            int movedArmies = 0;
            
            // Inform on the status of the country.
            cout << attackingCountry->getName() << " has been conquered." << endl;
            cout << playerName << " must move at least " << attackDiceCount << " armies to " << defendingCountry->getName() << "." << endl;
            
            // Loop until a valid number of armies is selected.
            while (movedArmies >= attackDiceCount)
            {
                cout << "Enter the number of armies to move: ";
                cin >> movedArmies;
                cout << endl;
                
                if (movedArmies < attackDiceCount)
                    cout << "Too few armies selected. Try again." << endl;
            }
            
            cout << "Transferring " << movedArmies << " armies from " << attackingCountry->getName() << " to " defendingCountry->getName() << "." << endl;
            cout << "Transferring ownership of " << defendingCountry->getName() << " from " << defendingCountry->getPlayerName() << " to " playerName << "." << endl;
            
            // Transfer ownership and troops.
            defendingCountry->setPlayerName(playerName);
            countries.push_back(defendingCountry);
            // REMOVE DEFENDInG COUNTRY FROM DEFENDING PLAYER'S COLLECTION
            defendingCountry->setArmyNum(movedArmies);
            attackingCountry->setArmyNum(attackingCountry->getArmyNum() - movedArmies);
            
            // Mark the player as having earned a card.
            hasConquered = true;
        }
    }
}

// Allows the player to move armies from a country to another one, as long as they are connected.
void Player::fortify(Country* origin, Country* target)
{
    
}

// Resets hasConquered back to false.
void Player::resetTurn()
{
    hasConquered = false;
}