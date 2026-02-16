#ifndef ENTITY_H
#define ENTITY_H
#include <iostream>
#include <vector>

using namespace std;

struct Potion{
    string name;
    string description;
    char type;
    double effect_value;
    double price;
};

struct Equipment{
    string name;
    string description;
    char type;
    double effect_value;
    char element;
    double price;
};

class Entity{
    private:
        string _name;
        double _hp;
        double _stamina;
        double _defense;
        char _condition;
        bool _advantage;
        double _gold;
        char _weakness;
        vector <Potion> _potions; //max size 3
        vector <Equipment> _inventory; // max size unlimited
        vector <Equipment> _equipped; // max size 2
        vector <Equipment> _items;
        float _calamity; 
        bool _can_move;

    public:
        //default constructor
        Entity(); 

        // initializes all variables
        Entity(string, double, double, char, bool, double, double, bool, char, float); 

        //sets if the player can execute their turn
        bool getCanMove();

        //gets if the player can move on their turn
        void setCanMove(bool can_move);

        //returns name of entity
        string getName(); 

        //returns HP of entity
        double getHP();

        //returns condition of entity
        char getCondition();  

        //returns gold possessed by entity
        double getGold(); 

        //returns stamina of entity
        double getStamina();  
        
        //returns defense of entity
        double getDefense(); 

        //returns if entity has advantage
        bool getAdvantage();

         //returns chance of calamity of entity
        float getCalamity();

        //returns weakness of entity
        char getWeakness(); 

        //returns all potions possessed by Entity
        vector <Potion> getAllPotions(); 

        //returns full unequipped inventory possessed by Entity
        vector <Equipment> getFullInventory(); 

        //returns equipped inventory possessed by Entity
        vector <Equipment> getFullEquipped(); 

        //returns the size of an Entity's equipped inventory
        int getEquippedSize();

        //returns the size of an Entity's inventory
        int getInventorySize();
        
        //returns the size of an Entity's potions vector
        int getPotionsSize();

        //returns an element of an Entity's equipped inventory based on index provided
        Equipment getEquippedElement(int index);

        //returns an element of an Entity's inventory based on index provided
        Equipment getInventoryElement(int index);

        //returns an element of an Entity's potions vector based on index provided
        Potion getPotionsElement(int index);


        // sets name of entity
        void setName(string name); 

        // sets HP of entity
        void setHP(double HP); 

        // sets condition of entity
        void setCondition(char condition); 

        // sets gold of entity
        void setGold(double gold); 

        // sets stamina of entity
        void setStamina(double stamina);

        // sets defense of entity
        void setDefense(double defense); 

        // sets advantage of entity
        void setAdvantage(bool advantage); 

        // sets calamity of entity
        void setCalamity(float calamity); 

        // sets weakness of entity
        void setWeakness(char weakness); 

        // adds a new potion to Entity's potions vector(max 3)
        void appendPotion(Potion newPotion); 

        // adds a new equipment to Entity's Inventory/Equipped vector
        void appendInventory(Equipment newItem); 

        // increases effect value of weapon slot 1 by "damage"
        void buffMainWeapon(double damage);


        //prints stats for Entity
        void printStats();

        //moves selected inventory item into equipped slot 1
        //shifts equipped slot 1 to equipped slot 2
        //moves equipped slot 2 to the end of inventory vector
        //REMEMBER TO PASS IN USERCHOICE - 1 BECAUSE THIS FUNCTION DEALS WITH INDEXING
        void swap(int inventorySwap, int equippedSwap);

        //updates certain stats of Entity based on which potion they choose to use
        //REMEMBER TO PASS IN USERCHOICE - 1 BECAUSE THIS FUNCTION DEALS WITH INDEXING
        void usePotion(int userChoice); 

};



#endif