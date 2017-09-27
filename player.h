/*
 * Author: Alexia Soucy, 40014822
 * Course: COMP 345, section D
 * Assignment: 1
 */

// TO DO: Consolidate with other parts to add dice rolling facility and 
// countries collection.

#ifndef PLAYER_H
#define PLAYER_H

#include "Dice.h"
#include "cards.h"
#include "Map.h"

// A player with its own hand of cards and troops counter.
class Player
{
public:
    Player(); // Creates a new player with no allocated troops and no name.
    Player(string playerName); // Creates a new named player with no allocated troops.
    int getTroops(); // Returns the number of troops the player possesses.
    void addTroops(int troops); // Grants new troops to the player.
    void subtractTroops(int troops); // Takes away troops from the player.
    
    // Hand functionality
    void setHand(); // Initialize the player's hand.
    Hand& getHand(); // Returns the player's hand object.
    
    // Map functionality
    vector<Country*> getCountries(); // Returns the collection of countries the player owns.
    void addCountry(Country*); // Adds a country to the player's country collection.
    void removeCountry(Country*); // Removes a country to the player's country collection.
    void reinforce(int troops, Country* country);
    void attack();
    void fortify();
    
    // Dice functionality
    Dice getDice(); // Returns the player's dice object.
    void setDice(); // Initializes the player's dice object.
private:
    string playerName;
    int playerTroops;
    Dice playerDice;
    Hand playerHand;
    vector<Country*> countries;
};

#endif /* PLAYER_H */

