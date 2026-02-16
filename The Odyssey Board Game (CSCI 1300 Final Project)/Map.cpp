#include "Map.h"


Map::Map(){}

Map::Map(int players_num, int size){
    m_mapArr[players_num][size] = {};
    numOfTreasures[0] = 0;
    numOfTreasures[1] = 0;
}

// setter for position on map given the value and which player and then the index for their lane
void Map::setMapPos(string value, int playerID, int index){
    m_mapArr[playerID][index] = value;
}

// getter for position on map given which player and then the index for their lane
string Map::getMapPos(int playerID, int index){
    return m_mapArr[playerID][index];
}

int Map::getHiddenTreasures(int player, int numElement){
    return hidden_treasures[player][numElement];
}

void Map::setHiddenTreasures(int player, int indexOnMap){
    hidden_treasures[player][numOfTreasures[player]++] = indexOnMap;
}



void Map::initializeMap(){
    srand (time(NULL));
    // variables to hold random numbers
    int rand_num1, rand_num2;
   

    bool lastRed[2] = {false, false};
    bool lastGreen[2] = {false, false};

    int red = 0;
    int green = 0;
    int red1 = 0;
    int green1 = 0;
    while (((red < 4 || green < 3) || (red1 < 4 || green1 < 3)) || (numOfTreasures[0] != 3 || numOfTreasures[1] != 3)){
        red = 0;
        green = 0;
        red1 = 0;
        green1 = 0;
        numOfTreasures[0] = 0;
        numOfTreasures[1] = 0;
        for (int i = 0; i < 50; i++) {
            if(i == 49){
                m_mapArr[0][i] = GREEN;
                m_mapArr[1][i] = GREEN;
                break;
            }
            
            do {
           
                rand_num1 = rand() % 3;

                if((lastRed[0] && rand_num1 == 0) || (lastGreen[0] && rand_num1 == 1)){
                continue;
                }

                break;
            } while (true);

       
            lastRed[0] = lastGreen[0] = false;

            if (rand_num1 == 0) {
                m_mapArr[0][i] = RED;
                red++;
                lastRed[0] = true;
                
                if(numOfTreasures[0] < 3){
                    int rand_is_treasure = rand() % 5;
                    if (rand_is_treasure == 0){
                        setHiddenTreasures(0, i);
                    }
                }        

            
            } else if (rand_num1 == 1) {
                m_mapArr[0][i] = GREEN;
                green++;
                lastGreen[0] = true;
                
            } else {
                m_mapArr[0][i] = BLUE;
            }

            do {
                rand_num2 = rand() % 3;

                if((lastRed[1] && rand_num2 == 0) || (lastGreen[1] && rand_num2 == 1)){
                    continue;
                }
                break;
            } while (true);

            
            lastRed[1] = lastGreen[1] = false;

            if (rand_num2 == 0) {
                m_mapArr[1][i] = RED;
                red1++;
                lastRed[1] = true;
                
                if(numOfTreasures[1] < 3){
                    int rand_is_treasure2 = rand() % 5;
                    if (rand_is_treasure2 == 0){
                        setHiddenTreasures(1, i);
                    }
                } 


            } else if (rand_num2 == 1) {
                m_mapArr[1][i] = GREEN;
                green1++;
                lastGreen[1] = true;
            } else {
                m_mapArr[1][i] = BLUE;
            }
            if(i == 47){
            lastGreen[0] = true;
            lastGreen[1] = true;
        }
        } 
    
    }
}    