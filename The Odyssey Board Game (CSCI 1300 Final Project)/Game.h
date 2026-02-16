#ifndef GAME_H
#define GAME_H
#include "Entity.h"
#include "Map.h"
#include <vector>

struct Riddle{
    string question;
    string answer;
};

class Game {
    private:
        vector<Entity> _players;
        vector<Entity> _islandEnemies;
        vector<Entity> _epicEnemies;
        vector<Potion> _allPotions;
        vector<Equipment> _allEquip;
        vector<Equipment> _epicEquip;
        Entity activePlayers[2];
        int playerPosition[2];
        vector <Entity> losers;
        Map map;
        vector <Riddle> riddles;
        vector<Entity> runners;
        
    public:
        // loads all characters, enemies, potions, and equipment into their respective vectors
        Game();

        void setRunner(Entity runner);

        Entity getRunnerElement(int index);
        

        //returns an Entity from active players based on index(either 1 or 0)
        Entity getActivePlayersElement(int index);

        //combat function 2 players vs Epic Enemy
        void epicCombat(Entity &player1, Entity &player2, Entity enemy);
        
        //combat function Player vs. Enemy
        void combat(Entity &player, Entity enemy, int index); 

        //pretty much the entire game
        void playGame(int index); 

        //adds another Entity to the back of the losers vector
        void setLosers(Entity loser);

        //returns an element of the losers vector based on index
        Entity getLoser(int index);

        //returns the size of the losers vector
        int getLosersSize();

        //fills vector with all playable characters
        void loadPlayableCharacters(string filename); 

        //fills vector with island enemies
        void loadIslandEnemies(string filename); 

        //fills vector with Epic enemies
        void loadEpicEnemies(string filename);

        //fills vector with all potions
        void loadAllPotions(string filename);

        //fills vector with all equipment
        void loadAllEquipment(string filename); 

        //fills vector with epic equipment
        void loadEpicEquipment(string filename); 

        //returns entire vector of playable characters
        vector <Entity> getCharacters(); 

        //sets player 1/2 based on user choice
        void setPlayers(int user_input, int index); 

        //returns player entity (index = player number [0,1])
        Entity getPlayers(int index); 

        //prints a random item shop of either potions or equipment (index = player number [0,1])
        void itemShop(int index); 

        //generates the map that will be used all game
        void generateMap();

        //sets the position of a player on the game board (index = player number [0,1])
        void setPlayerPosition(int position, int index);

        //returns the position of a player on the game board (index = player number [0,1])
        int getPlayerPosition(int index);

        //prints the current map, and where the players are indicated by "1" or "2"
        void printMap();
        
        //returns tile color that player is on (index = player number [0,1])
        string getTileColor(int index);

        //loads riddles into vector of Riddles
        void loadRiddles(string filename);

        //returns a random riddle, removes riddle from riddles vector
        Riddle getRandomRiddle();

        
        
       


        
};

#endif 