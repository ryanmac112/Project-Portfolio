#ifndef MAP_H
#define MAP_H

#define RED "\033[41m"     /* Red */
#define GREEN "\033[42m"   /* Green */
#define BLUE "\033[44m"    /* Blue */
#define MAGENTA "\033[45m" /* Magenta */
#define CYAN "\033[46m"    /* Cyan */
#define RESET "\033[0m"

#include <iostream>
#include <stdio.h>     
#include <stdlib.h>     
#include <time.h>

using namespace std;

class Map{
    public:

    // Constructor
    Map();
    
    // Parametrized Constructor
    Map(int players_num, int size);

    //Setter-Getter pair for position on map
    void setMapPos(string value, int playerID, int index);
    string getMapPos(int playerID, int index);

    // STUDENTS: Make changes to this function to produce correct ratios of tiles
    // THE CURRENT IMPLEMENTATION DOES NOT GIVE YOU THE CORRECT RATIOS
    // The last tile for each player should be a different color to represent Ithaca 
    // See the defines above for color options
    void initializeMap();

    //returns an element of hidden_treasures array based on player number
    int getHiddenTreasures(int player, int numElement);

    //fills hidden_treasures with tiles for both players that will result in an opportunity to solve a riddle for a treasure
    void setHiddenTreasures(int player, int indexOnMap);

    void setGreenTiles(int);


    private:
    // 2 is there as there are 2 players
    // 50 is there as there are 50 tiles for a player's lane = 100 total tiles
    // Note: This array holds STRINGS that have been defined above
    string m_mapArr[2][50] = {};
    
    //array of indexes of red tiles that will be hidden treasure tiles
    int hidden_treasures[2][3];
    int numOfTreasures[2];
    

};

#endif