#include "Entity.h"
#include <iostream>
#include <iomanip>

using namespace std;

Entity::Entity(){ 
    _gold = 0;
    _hp = 0;
    _name = "";
    _condition= 'H';
    _stamina = 0;
    _defense = 0;
    _advantage = false;
    _weakness = ' ';
    _calamity = 30;

}

Entity::Entity(string name, double hp, double gold, char condition, bool enemy, double stamina, double defense, bool advantage, char weakness, float calamity){ 
    _name = name;
    if(hp < 0 || hp > 100){
        if(hp < 0){
            _hp = 0;
        } else if(hp > 100 ){
            _hp = 100;
        }
    } else{
        _hp = hp;
    }

    if(stamina < 0 || stamina > 100){
        if(stamina < 0){
            _stamina = 0;
        } else if(stamina > 100 ){
            _stamina = 100;
        }
    } else{
        _stamina = stamina;
    }
    

    if(gold < 0){
        _gold = 0;
    } else{
        _gold = gold;
    }
    if(condition != 'H' && condition != 'P' && condition != 'D'){
        _condition = 'H';
    } else{
        _condition = condition;
    }
    
    _defense = defense;
    _advantage = advantage;
    _weakness = weakness;
    _calamity = calamity;

}

string Entity::getName(){
    return _name;
}

double Entity::getHP(){
    return _hp;
}

char Entity::getCondition(){
    return _condition;
}

double Entity::getGold(){
    return _gold;
}

double Entity::getStamina(){
    return _stamina;
}

double Entity::getDefense(){
    return _defense;
}

bool Entity::getAdvantage(){
    return _advantage;
}

float Entity::getCalamity(){ 
    return _calamity;
} 

char Entity::getWeakness(){
    return _weakness;
}

vector <Potion> Entity::getAllPotions(){
    return _potions;
}

vector <Equipment> Entity::getFullInventory(){
    return _inventory;
}

vector <Equipment> Entity::getFullEquipped(){
    return _equipped;
}

int Entity::getEquippedSize(){
    return _equipped.size();
}

int Entity::getInventorySize(){
    return _inventory.size();
}

int Entity::getPotionsSize(){
    return _potions.size();
}

Equipment Entity::getEquippedElement(int index){
    return _equipped[index];
}

Equipment Entity::getInventoryElement(int index){
    return _inventory[index];
}

Potion Entity::getPotionsElement(int index){
    return _potions[index];
}



void Entity::setName(string name){
    _name = name;
}

void Entity::setHP(double hp){
    if(hp < 0 || hp > 100){
        if(hp < 0){
            _hp = 0;
        } else if(hp > 100 ){
            _hp = 100;
        }
    } else{
        _hp = hp;
    }
}

void Entity::setCondition(char condition){
    if (condition == 'P' ||condition == 'H' ||condition == 'D'){
        _condition = condition;
    } 
}

void Entity::setGold(double gold){
    if(gold < 0 || gold > 500){
        if (gold < 0){
             _gold = 0;
        } else if (gold > 500){
             _gold = 500;
        }
    } else{
        _gold = gold;
    }
}

void Entity::setStamina(double stamina){
    if(stamina < 0 || stamina > 100){
        if(stamina < 0){
            _stamina = 0;
        } else if(stamina > 100 ){
            _stamina = 100;
        }
    } else{
        _stamina = stamina;
    }
}

void Entity::setDefense(double defense){
    _defense = defense;
}

void Entity::setAdvantage(bool advantage){
    _advantage  = advantage;
}

void Entity::setCalamity(float calamity){ 
    _calamity = calamity;
}

void Entity::setWeakness(char weakness){
    _weakness = weakness;
}

void Entity::appendPotion(Potion newPotion){
    if (_potions.size() < 3){
        _potions.push_back(newPotion);
    }    
}

void Entity::appendInventory(Equipment newItem){
    if(_equipped.size() < 2){
        _equipped.push_back(newItem);
    } else{
        _inventory.push_back(newItem);
    }
}




void Entity::printStats(){
    cout<< getName() << "'s stats:" << endl;
    cout<< "HP: " <<fixed << setprecision(2) << getHP() << endl;
    cout<< "Stamina: " << getStamina() << endl;
    cout<< "Defense: " << getDefense() << endl;
    cout<< "Condition: " << getCondition() << endl;
    cout<< "Gold held: " << getGold() << endl;
    
}

void Entity::swap(int inventorySwap, int equippedSwap){
    Equipment thisEquipment = _equipped[equippedSwap];
    _equipped[equippedSwap] = _inventory[inventorySwap];
    _inventory[inventorySwap] = thisEquipment;
}

void Entity::usePotion(int userChoice){
    
    if(_potions[userChoice].name == "Lesser Health Potion" || _potions[userChoice].name == "Greater Health Potion"){
        setHP(getHP() + _potions[userChoice].effect_value);
        _potions.erase(_potions.begin() + userChoice);
    }else if (_potions[userChoice].name == "Lesser Stamina Potion" || _potions[userChoice].name == "Greater Stamina Potion"){
        setStamina(getStamina() + _potions[userChoice].effect_value);
        _potions.erase(_potions.begin() + userChoice);
    }else if (_potions[userChoice].name == "Cleansing Potion"){
        setCondition('H');
        _potions.erase(_potions.begin() + userChoice);
    } else if (_potions[userChoice].name == "Greater Rejuvenation Potion" || _potions[userChoice].name == "Lesser Rejuvenation Potion"){
        setHP(getHP() + _potions[userChoice].effect_value);
        setStamina(getStamina() + _potions[userChoice].effect_value);
        _potions.erase(_potions.begin() + userChoice);
    }else if (_potions[userChoice].name == "Minor Strength Potion" || _potions[userChoice].name == "Major Strength Potion"){
        _equipped[0].effect_value += _potions[userChoice].effect_value;
        _equipped[1].effect_value += _potions[userChoice].effect_value;
        _potions.erase(_potions.begin() + userChoice);
    }
}

void Entity::buffMainWeapon(double damage){
    Equipment temp = getEquippedElement(0);
    temp.effect_value += damage;
    _equipped[0] = temp;
}

bool Entity::getCanMove(){
    return _can_move;
}

void Entity::setCanMove(bool can_move){
    _can_move = can_move;
}



