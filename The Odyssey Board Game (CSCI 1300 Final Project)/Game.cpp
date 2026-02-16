#include <iostream>
#include <iomanip>
#include "Game.h"
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib> 
#include <ctime>

using namespace std;

int split(string input_string, char separator, string arr[], const int ARR_SIZE){
    if (input_string.empty()) {
        return 0;
    }
    size_t pos = input_string.find(separator);
    if (pos == string::npos) {
        arr[0] = input_string;
        return 1;
    }
    int num_elements = 1;
    for(size_t  j = 0; j < input_string.length(); j++ ){
        if (input_string[j] == separator){
            num_elements++;
        }
    }
    
    int pieces = 0;
    int prev = 0;

    while((pos != string::npos) && (pieces < ARR_SIZE)){
        arr[pieces++] = input_string.substr(prev, pos - prev);
        prev = pos + 1;

        pos = input_string.find(separator, prev);
    }
    
    if (pieces < ARR_SIZE){
        arr[pieces++] = input_string.substr(prev);
    }
    
    if (num_elements > ARR_SIZE) {
        return -1;
    } else {
        return num_elements;
    }

}

Game::Game(){
    loadAllPotions("allPotions.txt");
    loadAllEquipment("allEquipment.txt");
    loadPlayableCharacters("playableChar.txt");
    loadIslandEnemies("islandEnemies.txt");
    loadEpicEquipment("epicEquipment.txt");
    loadEpicEnemies("epicEnemies.txt");
    loadRiddles("riddles.txt");
    generateMap();
    srand(time(NULL));
    playerPosition[0] = 0;
    playerPosition[1] = 0;
}


void Game::loadPlayableCharacters(string filename){
    ifstream inStream;
    inStream.open(filename);
    
    
    string line;
    const int num_elements = 9;
    string thisLine[num_elements];
    const int CHARACTERS_SIZE = 4;
    int firstLine = 0;
    while(getline(inStream, line) && firstLine <= CHARACTERS_SIZE){
        if (firstLine != 0){
            Entity thisPlayer;
            split(line, '|', thisLine, num_elements);
            for(int j = 0; j < num_elements; j++){
                if (j == 0){
                    thisPlayer.setName(thisLine[j]);
                } else if (j == 1){
                   thisPlayer.setHP(stod(thisLine[j]));
                }  else if (j == 2){
                    thisPlayer.setStamina(stod(thisLine[j]));
                } else if (j == 3){
                    thisPlayer.setDefense(stod(thisLine[j]));
                } else if (j == 4){
                    thisPlayer.setCondition(thisLine[j][0]);
                } else if (j == 5){
                    if(thisLine[j] == "True"){
                        thisPlayer.setAdvantage(true);
                    } else{
                        thisPlayer.setAdvantage(false);
                    }
                } else if (j == 6){
                    thisPlayer.setWeakness(thisLine[j][0]);
                } else if (j == 7){
                    thisPlayer.setGold(stod(thisLine[j]));
                } else if (j == 8){
                    string theseItems[2];
                    string currentLine = thisLine[j];
                    split(currentLine, ',', theseItems, 2);
                    for(int w = 0; w < 2; w++){
                        if (w == 0){
                            for(int r = 0; r<_allPotions.size(); r++){
                                if (_allPotions[r].name == theseItems[w]){
                                    thisPlayer.appendPotion(_allPotions[r]);
                                }
                            }
                        } else if (w == 1){
                            for(int r = 0; r<_allEquip.size(); r++){
                                if (_allEquip[r].name == theseItems[w]){
                                    thisPlayer.appendInventory(_allEquip[r]);
                                }
                            }
                        }
                    }
                    
                }
        
            }
            _players.push_back(thisPlayer);
            cout<< thisPlayer.getName() << " loaded!" <<endl;
        } 
        firstLine++;   
    }
    inStream.close();
} 

void Game::loadEpicEnemies(string filename){
    ifstream inStream;
    inStream.open(filename);
    
    
    string line;
    const int num_elements = 9;
    string thisLine[num_elements];
    const int CHARACTERS_SIZE = 3;
    int firstLine = 0;
    while(getline(inStream, line) && firstLine <= CHARACTERS_SIZE){
        if (firstLine != 0){
            Entity thisEnemy;
            split(line, '|', thisLine, num_elements);
            for(int j = 0; j < num_elements; j++){
                if (j == 0){
                    thisEnemy.setName(thisLine[j]);
                } else if (j == 1){
                    thisEnemy.setHP(stod(thisLine[j]));
                }  else if (j == 2){
                    thisEnemy.setStamina(stod(thisLine[j]));
                } else if (j == 3){
                    thisEnemy.setDefense(stod(thisLine[j]));
                } else if (j == 4){
                    thisEnemy.setCondition(thisLine[j][0]);
                } else if (j == 5){
                    if(thisLine[j] == "True"){
                        thisEnemy.setAdvantage(true);
                    } else{
                        thisEnemy.setAdvantage(false);
                    }
                } else if (j == 6){
                    thisEnemy.setWeakness(thisLine[j][0]);
                } else if (j == 7){
                    thisEnemy.setGold(stod(thisLine[j]));
                } else if (j == 8){
                    string theseItems[2];
                    string currentLine = thisLine[j];
                    split(currentLine, ',', theseItems, 2);
                    for(int w = 0; w < 2; w++){
                        if (w == 0){
                            for(int r = 0; r<_allPotions.size(); r++){
                                if (_allPotions[r].name == theseItems[w]){
                                    thisEnemy.appendPotion(_allPotions[r]);
                                }
                            }
                        } else if (w == 1){
                            for(int r = 0; r < _epicEquip.size(); r++){
                                if (_epicEquip[r].name == theseItems[w]){
                                    thisEnemy.appendInventory(_epicEquip[r]);
                                }
                            }
                        }
                    }
                }
        
            }
            _epicEnemies.push_back(thisEnemy);
        } 
        firstLine++;   
    }
    inStream.close();
}

void Game::loadIslandEnemies(string filename){
    ifstream inStream;
    inStream.open(filename);
    
    
    string line;
    const int num_elements = 9;
    string thisLine[num_elements];
    const int CHARACTERS_SIZE = 7;
    int firstLine = 0;
    while(getline(inStream, line) && firstLine <= CHARACTERS_SIZE){
        if (firstLine != 0){
            Entity thisEnemy;
            split(line, '|', thisLine, num_elements);
            for(int j = 0; j < num_elements; j++){
                if (j == 0){
                    thisEnemy.setName(thisLine[j]);
                } else if (j == 1){
                    thisEnemy.setHP(stod(thisLine[j]));
                }  else if (j == 2){
                    thisEnemy.setStamina(stod(thisLine[j]));
                } else if (j == 3){
                    thisEnemy.setDefense(stod(thisLine[j]));
                } else if (j == 4){
                    thisEnemy.setCondition(thisLine[j][0]);
                } else if (j == 5){
                    if(thisLine[j] == "True"){
                        thisEnemy.setAdvantage(true);
                    } else{
                        thisEnemy.setAdvantage(false);
                    }
                } else if (j == 6){
                    thisEnemy.setWeakness(thisLine[j][0]);
                } else if (j == 7){
                    thisEnemy.setGold(stod(thisLine[j]));
                } else if (j == 8){
                    string theseItems[2];
                    string currentLine = thisLine[j];
                    split(currentLine, ',', theseItems, 2);
                    for(int w = 0; w < 2; w++){
                        if (w == 0){
                            for(int r = 0; r<_allPotions.size(); r++){
                                if (_allPotions[r].name == theseItems[w]){
                                    thisEnemy.appendPotion(_allPotions[r]);
                                }
                            }
                        } else if (w == 1){
                            for(int r = 0; r<_allEquip.size(); r++){
                                if (_allEquip[r].name == theseItems[w]){
                                    thisEnemy.appendInventory(_allEquip[r]);
                                }
                            }
                        }
                    }
                }
        
            }
            _islandEnemies.push_back(thisEnemy);
        } 
        firstLine++;   
    }
    inStream.close();
}

void Game::loadAllPotions(string filename){
    ifstream inStream;
    inStream.open(filename);
    
    
    string line;
    const int num_elements = 5;
    string thisLine[num_elements];
    const int CHARACTERS_SIZE = 9;
    int firstLine = 0;
    while(getline(inStream, line) && firstLine <= CHARACTERS_SIZE){
        if (firstLine != 0){
            Potion thisPotion;
            split(line, '|', thisLine, num_elements);
            for( int j = 0; j < num_elements; j++){
                if (j == 0){
                    thisPotion.name = thisLine[j];
                } else if (j == 1){
                    thisPotion.description = thisLine[j];
                }  else if (j == 2){
                    thisPotion.type = thisLine[j][0];
                } else if (j == 3){
                    thisPotion.effect_value = stod(thisLine[j]);
                } else if (j == 4) {
                    thisPotion.price = stod(thisLine[j]);
                }

            }
            _allPotions.push_back(thisPotion);
        } 
        firstLine++;   
    }
    inStream.close();
}

void Game::loadEpicEquipment(string filename){
    ifstream inStream;
    inStream.open(filename);
    
    
    string line;
    const int num_elements = 6;
    string thisLine[num_elements];
    const int CHARACTERS_SIZE = 3;
    int firstLine = 0;
    while(getline(inStream, line) && firstLine <= CHARACTERS_SIZE){
        if (firstLine != 0){
            Equipment thisEquip;
            split(line, '|', thisLine, num_elements);
            for( int j = 0; j < num_elements; j++){
                if (j == 0){
                    thisEquip.name = thisLine[j];
                } else if (j == 1){
                    thisEquip.description = thisLine[j];
                }  else if (j == 2){
                    thisEquip.type = thisLine[j][0];
                } else if (j == 3){
                    thisEquip.effect_value = stod(thisLine[j]);
                } else if (j == 4){
                    thisEquip.element = thisLine[j][0];
                }else if (j == 5) {
                    thisEquip.price = stod(thisLine[j]);
                }
        
            }
            _epicEquip.push_back(thisEquip);
        } 
        firstLine++;   
    }
    inStream.close();
}

void Game::loadAllEquipment(string filename){
    ifstream inStream;
    inStream.open(filename);
    
    
    string line;
    const int num_elements = 6;
    string thisLine[num_elements];
    const int CHARACTERS_SIZE = 14;
    int firstLine = 0;
    while(getline(inStream, line) && firstLine <= CHARACTERS_SIZE){
        if (firstLine != 0){
            Equipment thisEquip;
            split(line, '|', thisLine, num_elements);
            for( int j = 0; j < num_elements; j++){
                if (j == 0){
                    thisEquip.name = thisLine[j];
                } else if (j == 1){
                    thisEquip.description = thisLine[j];
                }  else if (j == 2){
                    thisEquip.type = thisLine[j][0];
                } else if (j == 3){
                    thisEquip.effect_value = stod(thisLine[j]);
                } else if (j == 4){
                    thisEquip.element = thisLine[j][0];
                }else if (j == 5) {
                    thisEquip.price = stod(thisLine[j]);
                }
        
            }
            _allEquip.push_back(thisEquip);
        } 
        firstLine++;   
    }
    inStream.close();
}

vector <Entity> Game::getCharacters(){
    return _players;
}

void Game::setPlayers(int user_input, int index){
    activePlayers[index] = _players[user_input];
    _players.erase(_players.begin() + user_input);
}

Entity Game::getPlayers(int index){
    return activePlayers[index];
}

void Game::itemShop(int index){
    int rand_num;
    vector <Potion> itemShopPotions;
    vector <Equipment> itemShopEquipment;
    string select_item;
    string itemShopChoice;
    bool selected_weapon = false;
    bool selected_potion = false;
    
    while((!selected_weapon || !selected_potion)){
        cout<< activePlayers[index].getName() <<"'s current gold: " <<activePlayers[index].getGold() <<endl;
        
        cout<< "   ITEM SHOP" <<endl;
        cout<< "---------------" <<endl;
        cout<< "1. Buy Weapon" <<endl;
        cout<< "2. Buy Potion" <<endl;
        cout<< "3. Leave Shop" <<endl;
        getline(cin, itemShopChoice);
        
        if (stoi(itemShopChoice) == 1){
            cout<< "Which weapon would you like to purchase?" <<endl;
            for(int i = 0; i < 3; i++){
                rand_num = rand() % _allEquip.size();
                cout<< "(" <<i+1<< ") " << _allEquip[rand_num].name << " || Price: " <<_allEquip[rand_num].price <<endl;
                itemShopEquipment.push_back(_allEquip[rand_num]);
            }
            getline(cin, select_item);
            if(stoi(select_item) == 1){
                if (activePlayers[index].getGold() >= itemShopEquipment[0].price){
                    activePlayers[index].appendInventory(itemShopEquipment[0]);
                    activePlayers[index].setGold(activePlayers[index].getGold() - itemShopEquipment[0].price); 
                    cout<< "Successfully purchased " << itemShopEquipment[0].name <<endl;
                    cout<< endl;
                    selected_weapon = true;
                } else{
                    cout<< "You're too broke for this one, buddy" <<endl;
                    cout<< endl;
                    selected_weapon = false;
                }
            } else if(stoi(select_item) == 2){
                if (activePlayers[index].getGold() >= itemShopEquipment[1].price){
                    activePlayers[index].appendInventory(itemShopEquipment[1]);
                    activePlayers[index].setGold(activePlayers[index].getGold() - itemShopEquipment[1].price); 
                    cout<< "Successfully purchased " << itemShopEquipment[1].name <<endl;
                    cout<< endl;
                     selected_weapon = true;
                } else{
                    cout<< "You're too broke for this one, buddy" <<endl;
                    cout<< endl;
                     selected_weapon = false;
                }
            } else if(stoi(select_item) == 3){
                if (activePlayers[index].getGold() >= itemShopEquipment[2].price){
                    activePlayers[index].appendInventory(itemShopEquipment[2]);
                    activePlayers[index].setGold(activePlayers[index].getGold() - itemShopEquipment[2].price); 
                    cout<< "Successfully purchased " << itemShopEquipment[2].name <<endl;
                    cout<< endl;
                     selected_weapon = true;
                } else{
                    cout<< "You're too broke for this one, buddy" <<endl;
                    cout<< endl;
                    selected_weapon = false;
                }
            }
        } else if (stoi(itemShopChoice) == 2){
            cout<< "Which potion would you like to purchase?" <<endl;
            for(int i = 0; i < 3; i++){
                rand_num = rand() % _allPotions.size();
                cout<< "(" <<i+1<< ") " << _allPotions[rand_num].name << " || Price: " <<_allPotions[rand_num].price <<endl;
                itemShopPotions.push_back(_allPotions[rand_num]);
            }
            getline(cin, select_item);
            if(stoi(select_item) == 1){
                if (activePlayers[index].getGold() >= itemShopPotions[0].price){
                    activePlayers[index].appendPotion(itemShopPotions[0]);
                    activePlayers[index].setGold(activePlayers[index].getGold() - itemShopPotions[0].price); 
                    cout<< "Successfully purchased " << itemShopPotions[0].name <<endl;
                    cout<< endl;
                    selected_potion = true;
                } else{
                    cout<< "You're too broke for this one, buddy" <<endl;
                    cout<< endl;
                    selected_potion = false;
                }
            } else if(stoi(select_item) == 2){
                if (activePlayers[index].getGold() >= itemShopPotions[1].price){
                    activePlayers[index].appendPotion(itemShopPotions[1]);
                    activePlayers[index].setGold(activePlayers[index].getGold() - itemShopPotions[1].price); 
                    cout<< "Successfully purchased " << itemShopPotions[1].name <<endl;
                    cout<< endl;
                    selected_potion = true;
                } else{
                    cout<< "You're too broke for this one, buddy" <<endl;
                    cout<< endl;
                    selected_potion = false;
                }
            } else if(stoi(select_item) == 3){
                if (activePlayers[index].getGold() >= itemShopPotions[2].price){
                    activePlayers[index].appendPotion(itemShopPotions[2]);
                    activePlayers[index].setGold(activePlayers[index].getGold() - itemShopPotions[2].price); 
                    cout<< "Successfully purchased " << itemShopPotions[2].name <<endl;
                    cout<< endl;
                    selected_potion = true;
                    
                } else{
                    cout<< "You're too broke for this one, buddy" <<endl;
                    cout<< endl;
                    selected_potion = false;
                }
            }
        } else if (stoi(itemShopChoice) == 3){
            cout<< "Bye!!" <<endl;
            cout<< endl;
            selected_weapon = true;
            selected_potion = true;
        }
    }
}

void Game::generateMap(){
    map.initializeMap();
}

void Game::printMap(){
    for(int i = 0; i < 50; i++){
        if (i != playerPosition[0]){
            cout << map.getMapPos(0,i) << "  " << RESET; 
        }else{
            cout << map.getMapPos(0,i) << "1" << " " << RESET; 
        }
    }

    cout << endl;

    for(int i = 0; i < 50; i++){
        if (i != playerPosition[1]){
            cout << map.getMapPos(1,i) << "  " << RESET; 
        }else{
            cout << map.getMapPos(1,i) << "2" << " " << RESET; 
        } 
    }

    // // Use RESET to revert back to the default terminal text color when done
    cout << RESET << endl;
    cout<<endl;
}

void Game::setPlayerPosition(int position, int index){
    playerPosition[index] = position;
}

       
int Game::getPlayerPosition(int index){
    return playerPosition[index];
}

void Game::playGame(int index){
    printMap();
    cout<< activePlayers[index].getName()<< "'s turn!" <<endl;
    cout<<endl;
    if (activePlayers[index].getStamina() == 0){
            cout<< activePlayers[index].getName() << " is out of stamina, so they lose their turn." <<endl;
            activePlayers[index].setStamina(10);
            return;
        } 
    if (activePlayers[index].getCanMove() == false){
            cout<< activePlayers[index].getName() << " cannot move this turn." <<endl;
            activePlayers[index].setCanMove(true);
            return;
        }
    if(activePlayers[index].getCondition() == 'P'){
        activePlayers[index].setHP(activePlayers[index].getHP() - 5);
    } else if(activePlayers[index].getCondition() == 'D'){
        activePlayers[index].setStamina(activePlayers[index].getStamina() - 5);
    }
    string menuSelect;
    bool printstat = false;
    do{
        cout<< "    Menu" <<endl;
        cout<< "------------" <<endl;
        cout<< "1. Move" <<endl;
        cout<< "2. Swap Weapon" <<endl;
        cout<< "3. Use Potion" <<endl;
        cout<< "4. Print Player Stats" <<endl;
        cout<< "5. Quit" <<endl;
        printstat = false;
        getline(cin, menuSelect);
        
        if (stoi(menuSelect) == 4){
            activePlayers[index].printStats();
            printstat = true;
        }
    } while(printstat == true);

    if (stoi(menuSelect) == 1){
        activePlayers[index].setStamina(activePlayers[index].getStamina() - 3);
        int rand_dice_roll = (rand() % 6) + 1;
        cout<< activePlayers[index].getName() << " rolled a " <<rand_dice_roll<<endl;
        for (int i = 0; i < rand_dice_roll; i++){
            setPlayerPosition(getPlayerPosition(index) + 1, index);
            if(getTileColor(index) == GREEN){
                break;
            }
        }
        //this is to indicate if a player has reached Ithaca
        if(getPlayerPosition(index) >= 49){
            cout<< activePlayers[index].getName() << " has reached Ithaca!" <<endl;
            for(int i = 0; i < 2; i++){
                if (activePlayers[i].getName() != activePlayers[index].getName()){
                    setLosers(activePlayers[i]);
                }
            }
        }
        //this is to initiate Epic combat
        if(getPlayerPosition(0) == getPlayerPosition(1)){
            int rand_epic_enemy = rand() % _epicEnemies.size();
            Entity currentEpicEnemy = _epicEnemies[rand_epic_enemy];
            cout<<"Oh no! Both players have landed on the same tile and must engage in Epic Combat!" <<endl;
            cout<< "Now " <<activePlayers[0].getName() << " and " <<activePlayers[1].getName() << " must work together to defeat " << currentEpicEnemy.getName() <<endl;
            epicCombat(activePlayers[0], activePlayers[1], currentEpicEnemy);
            return;
        }
        
        if (getTileColor(index) == RED){
            for (int i = 0; i < 3; i++){
                if (getPlayerPosition(index) == map.getHiddenTreasures(index, i)){
                    Riddle tempRiddle = getRandomRiddle();
                    cout<< tempRiddle.question <<endl;
                    string answer;
                    getline(cin, answer);
                    if (tempRiddle.answer == answer){
                        int rand_treasure = (rand() % 10) +1;
                        cout<<"Correct!!" <<endl;
                        if(rand_treasure <= 3){
                            double rand_stamina = (rand() % 21) + 10;
                            activePlayers[index].setStamina(activePlayers[index].getStamina() + rand_stamina);
                            cout<< activePlayers[index].getName() << "'s stamina has been increased by " << rand_stamina<<endl;
                            return;
                        } else if(rand_treasure <= 6){
                            double rand_gold = (rand() % 21) + 20;
                            activePlayers[index].setGold(activePlayers[index].getGold() + rand_gold);
                            cout<< activePlayers[index].getName() << " has inherited " << rand_gold << " gold" <<endl;
                            return;
                        } else{
                            double rand_buff = (rand() % 6) + 5;
                            activePlayers[index].buffMainWeapon(rand_buff);
                            cout<< activePlayers[index].getName() <<"'s main weapon (" << activePlayers[index].getEquippedElement(0).name << ") has been buffed by " <<rand_buff << " damage" <<endl;
                            return;
                        }
                    }else{
                        cout<<"Incorrect."<<endl;
                        return;
                    }
                    
                }
            }
            int rand_special_tile = rand() % 4;
            if (rand_special_tile == 0){
                cout<< activePlayers[index].getName() << " landed on a Shortcut Tile!" <<endl;
                cout << "Your spirits soar as you're propelled four tiles ahead. Ithaca isn't far." <<endl;
                setPlayerPosition(getPlayerPosition(index) + 4, index);
            } else if (rand_special_tile == 1){
                cout<< activePlayers[index].getName() << " landed on a Siren's Song Tile!" <<endl;
                cout<< "As the Siren's Song echoes through the air, you sense its magical pull, an otherworldly force that toys with the hearts of those who dare to listen. You stop in your tracks. You cannot move on your next turn only." <<endl;
                activePlayers[index].setCanMove(false);
            } else if (rand_special_tile == 2){
                cout<< activePlayers[index].getName() << " landed on a Helios' Beacon Tile!" <<endl;
                cout << "As you stand in the brilliance of Helios' Beacon, you feel the warmth of the sun god's favor shining upon you. You feel luckier. Reduce calamity chances by 5%, permanently" <<endl;
                activePlayers[index].setCalamity((activePlayers[index].getCalamity() / 20) * 19);
            } else{
                cout<< activePlayers[index].getName() << " landed on a Nymph's Spring Tile!" <<endl;
                cout << "In the embrace of the Nymph's Spring, you feel the embrace of nature itself. Your stamina is replenished." <<endl;
                activePlayers[index].setStamina(100);
            }
                
        } else if (getTileColor(index) == GREEN){
            int rand_enemy = rand() % _islandEnemies.size();
            Entity current_enemy = _islandEnemies[rand_enemy];
            cout<<"Oh no! You have landed on an island and stumbled across an Island Enemy!" <<endl;
            cout<< "Now " <<activePlayers[index].getName() << " must engage in combat with " << current_enemy.getName() <<endl;
            combat(activePlayers[index], current_enemy, index);

        } else if (getTileColor(index) == BLUE){
            int rand_calamity = (rand() % 100) + 1;
            if (rand_calamity <= activePlayers[index].getCalamity()){
                int rand_which_calamity = (rand() % 100) + 1;
                if (rand_which_calamity <= 45){
                    int randMoveBack = (rand() % 3) + 1;
                    setPlayerPosition(getPlayerPosition(index) - randMoveBack, index);
                    cout<< "With each passing moment, the storm grows fiercer, testing your courage and resolve as you struggle to keep your ship afloat amidst the wrath of Poseidon." <<endl;
                    cout<< activePlayers[index].getName() << " moves back " <<randMoveBack<< " spaces." <<endl;
                    printMap();
                } else if (rand_which_calamity <= 80){
                    cout<< "The spread of the plague seems unstoppable, defying your best efforts to contain it and leaving you to confront the harsh reality of your own mortality." <<endl;
                    cout<< activePlayers[index].getName() << " is now diseased." <<endl;
                    activePlayers[index].setCondition('D');
                } else {
                    cout<< "Much to your dismay, it seems you are not the only one on your ship." <<endl;
                    cout<< activePlayers[index].getName() << " is now poisoned." <<endl;
                    activePlayers[index].setCondition('P');
                }
            }

        }
    } else if (stoi(menuSelect) == 2){
        if(activePlayers[index].getInventorySize() == 0){
            cout<<"You have nothing in your inventory to swap!" <<endl;
            return;
        }
        
        cout<<"Current inventory:" <<endl;
        for (int i = 0; i <activePlayers[index].getInventorySize(); i++ ){
            cout<< "(" <<i+1<< ") "<<activePlayers[index].getInventoryElement(i).name <<endl;
        }
        cout<<endl;
        cout<<"Please select the item that you wish to swap into your equipped inventory" <<endl;
        string inventorySwap;
        getline(cin, inventorySwap);
        cout<<endl;
        
        cout<<"Current equipped inventory:" <<endl;
        for (int i = 0; i <activePlayers[index].getEquippedSize(); i++ ){
            cout<< "(" <<i+1<< ") "<<activePlayers[index].getEquippedElement(i).name;
        }
        cout<<endl;
        cout<<"Please select the item that you wish to swap into your inventory" <<endl;
        string equippedSwap;
        getline(cin, equippedSwap);

        activePlayers[index].swap(stoi(inventorySwap) - 1, stoi(equippedSwap) - 1);
                
    } else if(stoi(menuSelect) == 3){
        if(activePlayers[index].getPotionsSize() == 0){
            cout<<"You have no potions to consume!" <<endl;
            return;
        }
        cout<<"Current potions:" <<endl;
        for (int i = 0; i <activePlayers[index].getPotionsSize(); i++ ){
            cout<< "(" <<i+1<< ") "  << activePlayers[index].getPotionsElement(i).name <<endl;
        }
        cout<<endl;
        cout<<"Please select the potion that you wish to use" <<endl;
        string usePotion;
        getline(cin, usePotion);
        cout<< "Successfully consumed a " <<activePlayers[index].getPotionsElement(stoi(usePotion) - 1).name <<endl;
        if(activePlayers[index].getPotionsElement(stoi(usePotion) - 1).name == "Lesser Health Potion" || activePlayers[index].getPotionsElement(stoi(usePotion) - 1).name == "Greater Health Potion"){
            cout<< "HP before: " << activePlayers[index].getHP() <<endl;
            activePlayers[index].usePotion(stoi(usePotion) - 1);
            cout<< "HP after: " << activePlayers[index].getHP() <<endl;
        }else if (activePlayers[index].getPotionsElement(stoi(usePotion) - 1).name == "Lesser Stamina Potion" || activePlayers[index].getPotionsElement(stoi(usePotion) - 1).name == "Greater Stamina Potion"){
            cout<< "Stamina before: " << activePlayers[index].getStamina() <<endl;
            activePlayers[index].usePotion(stoi(usePotion) - 1);
            cout<< "Stamina after: " << activePlayers[index].getStamina() <<endl;
        }else if (activePlayers[index].getPotionsElement(stoi(usePotion) - 1).name == "Cleansing Potion"){
            cout<< "Condition before: " << activePlayers[index].getCondition() <<endl;
            activePlayers[index].usePotion(stoi(usePotion) - 1);
            cout<< "Condition after: " << activePlayers[index].getCondition() <<endl;
        } else if (activePlayers[index].getPotionsElement(stoi(usePotion) - 1).name == "Greater Rejuvenation Potion" || activePlayers[index].getPotionsElement(stoi(usePotion) - 1).name == "Lesser Rejuvenation Potion"){
            cout<< "HP before: " << activePlayers[index].getHP() <<endl;
            cout<< "Stamina before: " << activePlayers[index].getStamina() <<endl;
            activePlayers[index].usePotion(stoi(usePotion) - 1);
            cout<< "HP after: " << activePlayers[index].getHP() <<endl;
            cout<< "Stamina after: " << activePlayers[index].getStamina() <<endl;
        }else if (activePlayers[index].getPotionsElement(stoi(usePotion) - 1).name == "Minor Strength Potion" || activePlayers[index].getPotionsElement(stoi(usePotion) - 1).name == "Major Strength Potion"){
            for (int i = 0; i < activePlayers[index].getEquippedSize(); i++){
                cout<< "Weapon "<<i+1<< " damage before: "  << activePlayers[index].getEquippedElement(i).effect_value <<endl;
            }
            activePlayers[index].usePotion(stoi(usePotion) - 1);
            for (int i = 0; i < activePlayers[index].getEquippedSize(); i++){
                cout<< "Weapon "<<i+1<< " damage after: "  << activePlayers[index].getEquippedElement(i).effect_value <<endl;;
            }
        }
    } else if (stoi(menuSelect) == 5){
        setLosers(activePlayers[index]);
    } 
}    

void Game::setLosers(Entity loser){
    losers.push_back(loser);
}

Entity Game::getLoser(int index){
    return losers[index];
}

int Game::getLosersSize(){
    return losers.size();
}

string Game::getTileColor(int index){
    return map.getMapPos(index, getPlayerPosition(index));
}

void Game::loadRiddles(string filename){
    ifstream inStream;
    inStream.open(filename);
    
    
    string line;
    const int num_elements = 2;
    string thisLine[num_elements];
    const int CHARACTERS_SIZE = 15;
    int firstLine = 0;
    while(getline(inStream, line) && firstLine <= CHARACTERS_SIZE){
        Riddle thisRiddle;
        split(line, '|', thisLine, num_elements);
        for( int j = 0; j < num_elements; j++){
            if (j == 0){
                thisRiddle.question = thisLine[j];
            } else if (j == 1){
                thisRiddle.answer = thisLine[j];
            }
        }
        riddles.push_back(thisRiddle);
        firstLine++;   
    }
    inStream.close();
}

Riddle Game::getRandomRiddle(){
    int rand_riddle = rand() % riddles.size();
    Riddle thisRiddle = riddles[rand_riddle];
    riddles.erase(riddles.begin() + rand_riddle);
    return thisRiddle;
}

void Game::combat(Entity &player, Entity enemy, int index){
    player.printStats();
    int rand_player_advantage = 0;
    int rand_enemy_advantage = 0;
    if (enemy.getAdvantage() == false && player.getAdvantage() == false){
        do{
            rand_player_advantage = rand() % 6;
            rand_enemy_advantage = rand() % 6;
        } while (rand_player_advantage == rand_enemy_advantage);
    }    
    int rand_enemy_hit = 0;
    double rand_enemy_damage = 0;
    double enemy_damage_dealt = 0;

    string playerChoice;
    int rand_player_hit = 0;
    double rand_player_damage = 0;
    double player_damage_dealt = 0;
    Equipment playerMainWeapon;

    string inventorySwap;
    string equippedSwap;

    string usePotion;

    int rand_run;
    int can_visit_shop = true;

    bool has_weapon = true;
    
    if (rand_player_advantage > rand_enemy_advantage){
        do{    
            cout<< "Player wins initiative roll."<< endl;
            cout<< "Commencing battle."<<endl;
            cout << "Current Player Stats" <<endl;
            player.printStats();
            cout << "Current Enemy Stats" <<endl;
            enemy.printStats();
            cout<< "Which action would you like to take?" <<endl;
            cout<< "1. Attack" <<endl;
            cout<< "2. Use Potion" <<endl;
            cout<< "3. Swap Weapon" <<endl;
            cout<< "4. Attempt to Run" <<endl;
            getline(cin, playerChoice);
            if(stoi(playerChoice) == 1){
                rand_player_hit = rand() % 5;
                if(rand_player_hit == 0){
                cout<<"Miss!"<<endl;
                }else{
                    for (int i = 0; i < player.getEquippedSize(); i++){
                        if(player.getEquippedElement(i).type == 'D'){
                            playerMainWeapon = player.getEquippedElement(i);
                        break;
                        } else{
                            has_weapon = false;
                        }
                    }
                    if(has_weapon == false){
                        cout<< player.getName() <<" does not have a weapon and therefore they die to " <<enemy.getName() <<endl;
                        setLosers(player);
                        return;
                    }
                    rand_player_damage = ((rand() % (int) playerMainWeapon.effect_value) + 1);
                    if((enemy.getWeakness() == 'F' && playerMainWeapon.element == 'W') || (enemy.getWeakness() == 'A' && playerMainWeapon.element == 'F') || (enemy.getWeakness() == 'E' && playerMainWeapon.element == 'A') || (enemy.getWeakness() == 'W' && playerMainWeapon.element == 'E')){
                        rand_player_damage *=2;
                    } else if ((enemy.getWeakness() == 'E' && playerMainWeapon.element == 'W') || (enemy.getWeakness() == 'A' && playerMainWeapon.element == 'E') || (enemy.getWeakness() == 'F' && playerMainWeapon.element == 'A') || (enemy.getWeakness() == 'W' && playerMainWeapon.element == 'F')){
                        rand_player_damage /=2;
                    }
                    player_damage_dealt = rand_player_damage - enemy.getDefense();
                    if(player_damage_dealt < 3.5){
                        player_damage_dealt = 3.5;
                    } else{
                        player_damage_dealt *= 3.5;
                    }
                    cout<< "Hit successful! Deals " << player_damage_dealt<< " damage!" <<endl;
                    cout<< "Enemy HP before: " << enemy.getHP() <<endl;
                    enemy.setHP(enemy.getHP() - player_damage_dealt);
                    cout<< "Enemy HP after: " << enemy.getHP() <<endl;
                    
                    if (enemy.getHP() == 0){
                        cout<< "Battle ended." <<endl;
                        cout<< enemy.getName() << " has been defeated!" <<endl;
                        cout<< player.getName() << " inherits " << enemy.getName() << "'s gold(" <<enemy.getGold() << ") and weapon(" << enemy.getEquippedElement(0).name << ")" <<endl;
                        player.setGold(player.getGold() + enemy.getGold());
                        player.appendInventory(enemy.getEquippedElement(0));
                        for (int i = 0; i < _islandEnemies.size(); i++){
                                if(enemy.getName() == _islandEnemies[i].getName()){
                                    _islandEnemies.erase(_islandEnemies.begin() + i);
                                    break;
                                }
                            }
                        break;
                    }
                    
                }
                cout << "Swapping turns!" <<endl;
            } else if(stoi(playerChoice) == 2){
                if(player.getPotionsSize() == 0){
                    cout<<"You have no potions to consume!" <<endl;
                    
                } else {
                    cout<<"Current potions:" <<endl;
                    for (int i = 0; i <player.getPotionsSize(); i++ ){
                        cout<< "(" <<i+1<< ") "  << player.getPotionsElement(i).name <<endl;
                    }
                    cout<<endl;
                    cout<<"Please select the potion that you wish to use" <<endl;
                    getline(cin, usePotion);
                    cout<< "Successfully consumed a " <<player.getPotionsElement(stoi(usePotion) - 1).name <<endl;
                    if(player.getPotionsElement(stoi(usePotion) - 1).name == "Lesser Health Potion" || player.getPotionsElement(stoi(usePotion) - 1).name == "Greater Health Potion"){
                        cout<< "HP before: " << player.getHP() <<endl;
                        player.usePotion(stoi(usePotion) - 1);
                        cout<< "HP after: " << player.getHP() <<endl;
                    }else if (player.getPotionsElement(stoi(usePotion) - 1).name == "Lesser Stamina Potion" || player.getPotionsElement(stoi(usePotion) - 1).name == "Greater Stamina Potion"){
                        cout<< "Stamina before: " << player.getStamina() <<endl;
                        player.usePotion(stoi(usePotion) - 1);
                        cout<< "Stamina after: " << player.getStamina() <<endl;
                    }else if (player.getPotionsElement(stoi(usePotion) - 1).name == "Cleansing Potion"){
                        cout<< "Condition before: " << player.getCondition() <<endl;
                        player.usePotion(stoi(usePotion) - 1);
                        cout<< "Condition after: " << player.getCondition() <<endl;
                    } else if (player.getPotionsElement(stoi(usePotion) - 1).name == "Greater Rejuvenation Potion" || player.getPotionsElement(stoi(usePotion) - 1).name == "Lesser Rejuvenation Potion"){
                        cout<< "HP before: " << player.getHP() <<endl;
                        cout<< "Stamina before: " << player.getStamina() <<endl;
                        player.usePotion(stoi(usePotion) - 1);
                        cout<< "HP after: " << player.getHP() <<endl;
                        cout<< "Stamina after: " << player.getStamina() <<endl;
                    }else if (player.getPotionsElement(stoi(usePotion) - 1).name == "Minor Strength Potion" || player.getPotionsElement(stoi(usePotion) - 1).name == "Major Strength Potion"){
                        for (int i = 0; i < player.getEquippedSize(); i++){
                            cout<< "Weapon "<<i+1<< " damage before: "  << player.getEquippedElement(i).effect_value<<endl;
                        }
                        player.usePotion(stoi(usePotion) - 1);
                        for (int i = 0; i < player.getEquippedSize(); i++){
                            cout<< "Weapon "<<i+1<< " damage after: "  << player.getEquippedElement(i).effect_value<<endl;
                        }
                    }
                }
                    cout << "Swapping turns!" <<endl;
            } else if(stoi(playerChoice) == 3){
                if(player.getInventorySize() == 0){
                    cout<<"You have nothing in your inventory to swap!" <<endl;
                } else{
                
                    cout<<"Current inventory:" <<endl;
                    for (int i = 0; i <player.getInventorySize(); i++ ){
                        cout<< "(" <<i+1<< ") "<<player.getInventoryElement(i).name <<endl;
                    }
                    cout<<endl;
                    cout<<"Please select the item that you wish to swap into your equipped inventory" <<endl;
                    getline(cin, inventorySwap);
                    cout<<endl;
                    
                    cout<<"Current equipped inventory:" <<endl;
                    for (int i = 0; i <player.getEquippedSize(); i++ ){
                        cout<< "(" <<i+1<< ") "<<player.getEquippedElement(i).name;
                    }
                    cout<<endl;
                    cout<<"Please select the item that you wish to swap into your inventory" <<endl;
                    getline(cin, equippedSwap);
                    cout<< "Player Weapon Before: " << player.getEquippedElement(stoi(equippedSwap) - 1).name <<endl;
                    player.swap(stoi(inventorySwap) - 1, stoi(equippedSwap) - 1);
                    cout<< "Player Weapon After: " << player.getEquippedElement(stoi(equippedSwap) - 1).name <<endl;
                }
                cout << "Swapping turns!" <<endl;
            } else if(stoi(playerChoice) == 4){
                rand_run = rand() % 10;
                if(rand_run == 0){
                    cout<< "Your attempt to run was unsuccessful and " <<enemy.getName() << " has killed you." <<endl;
                    setLosers(player);
                    return;
                }else{
                    //where do you think you're going(extra credit)
                    cout<< "Your attempt to run was successful" <<endl;
                    
                    rand_enemy_damage = ((rand() % (int) enemy.getEquippedElement(0).effect_value) + 1);
                    if((player.getWeakness() == 'F' && enemy.getEquippedElement(0).element == 'W') || (player.getWeakness() == 'A' && enemy.getEquippedElement(0).element == 'F') || (player.getWeakness() == 'E' && enemy.getEquippedElement(0).element == 'A') || (player.getWeakness() == 'W' &&enemy.getEquippedElement(0).element == 'E')){
                        rand_enemy_damage *=2;
                    } else if ((player.getWeakness() == 'E' && enemy.getEquippedElement(0).element == 'W') || (player.getWeakness() == 'A' && enemy.getEquippedElement(0).element == 'E') || (player.getWeakness() == 'F' && enemy.getEquippedElement(0).element == 'A') || (player.getWeakness() == 'W' && enemy.getEquippedElement(0).element == 'F')){
                        rand_enemy_damage /=2;
                    }
                    enemy_damage_dealt = rand_enemy_damage - player.getDefense();
                    if(enemy_damage_dealt < 2.5){
                        enemy_damage_dealt = 2.5;
                    } else{
                        enemy_damage_dealt *= 2.5;
                    }   
                            
                    cout<< enemy.getName() << " hits you for " <<enemy_damage_dealt<< " damage as you leave." <<endl;
                    cout<< "Player HP before: " << player.getHP() <<endl;
                    player.setHP(player.getHP() - enemy_damage_dealt);
                    cout<< "Player HP after: " << player.getHP() <<endl;
                    if (player.getHP() == 0){
                        cout<< "Battle ended." <<endl;
                        setLosers(player);
                        return;
                    }

                    player.setStamina(player.getStamina() - 35);
                    can_visit_shop = false;
                    return;
                }
            }

            cout<< "Remember: On their turn, Enemies only attack." <<endl;
            rand_enemy_hit = rand() % 5;
            if(rand_enemy_hit == 0){
                cout<<"Miss!"<<endl;
            }else{
                rand_enemy_damage = ((rand() % (int) enemy.getEquippedElement(0).effect_value) + 1);
                if((player.getWeakness() == 'F' && enemy.getEquippedElement(0).element == 'W') || (player.getWeakness() == 'A' && enemy.getEquippedElement(0).element == 'F') || (player.getWeakness() == 'E' && enemy.getEquippedElement(0).element == 'A') || (player.getWeakness() == 'W' &&enemy.getEquippedElement(0).element == 'E')){
                    rand_enemy_damage *=2;
                } else if ((player.getWeakness() == 'E' && enemy.getEquippedElement(0).element == 'W') || (player.getWeakness() == 'A' && enemy.getEquippedElement(0).element == 'E') || (player.getWeakness() == 'F' && enemy.getEquippedElement(0).element == 'A') || (player.getWeakness() == 'W' && enemy.getEquippedElement(0).element == 'F')){
                    rand_enemy_damage /=2;
                }
                enemy_damage_dealt = rand_enemy_damage - player.getDefense();
                if(enemy_damage_dealt < 2.5){
                    enemy_damage_dealt = 2.5;
                } else{
                    enemy_damage_dealt *= 2.5;
                }   
                cout<< "Hit successful! Deals " << enemy_damage_dealt<< " damage!" <<endl;
                cout<< "Player HP before: " << player.getHP() <<endl;
                player.setHP(player.getHP() - enemy_damage_dealt);
                cout<< "Player HP after: " << player.getHP() <<endl;
                if (player.getHP() == 0){
                    cout<< "Battle ended." <<endl;
                    setLosers(player);
                    return;
                }
            }    
                cout << "Swapping turns!" <<endl;
        }while (true);

    } else if ((rand_player_advantage < rand_enemy_advantage) || (enemy.getAdvantage() == true && player.getAdvantage() == false)){
        cout<< "Enemy wins initiative roll."<< endl;
        cout<< "Commencing battle."<<endl;

        do{
            cout<< "Remember: On their turn, Enemies only attack." <<endl;
            rand_enemy_hit = rand() % 5;
            if(rand_enemy_hit == 0){
                cout<<"Miss!"<<endl;
            }else{
                rand_enemy_damage = ((rand() % (int) enemy.getEquippedElement(0).effect_value) + 1);
                if((player.getWeakness() == 'F' && enemy.getEquippedElement(0).element == 'W') || (player.getWeakness() == 'A' && enemy.getEquippedElement(0).element == 'F') || (player.getWeakness() == 'E' && enemy.getEquippedElement(0).element == 'A') || (player.getWeakness() == 'W' &&enemy.getEquippedElement(0).element == 'E')){
                    rand_enemy_damage *=2;
                } else if ((player.getWeakness() == 'E' && enemy.getEquippedElement(0).element == 'W') || (player.getWeakness() == 'A' && enemy.getEquippedElement(0).element == 'E') || (player.getWeakness() == 'F' && enemy.getEquippedElement(0).element == 'A') || (player.getWeakness() == 'W' && enemy.getEquippedElement(0).element == 'F')){
                    rand_enemy_damage /=2;
                }
                enemy_damage_dealt = rand_enemy_damage - player.getDefense();
                if(enemy_damage_dealt < 2.5){
                    enemy_damage_dealt = 2.5;
                } else{
                    enemy_damage_dealt *= 2.5;
                }    
                cout<< "Hit successful! Deals " << enemy_damage_dealt<< " damage!" <<endl;
                cout<< "Player HP before: " << player.getHP() <<endl;
                player.setHP(player.getHP() - enemy_damage_dealt);
                cout<< "Player HP after: " << player.getHP() <<endl;
                if (player.getHP() == 0){
                    cout<< "Battle ended." <<endl;
                    setLosers(player);
                    return;
                }
            }    
                cout << "Swapping turns!" <<endl;

                cout << "Current Player Stats" <<endl;
                player.printStats();
                cout << "Current Enemy Stats" <<endl;
                enemy.printStats();
                cout<< "Which action would you like to take?" <<endl;
                cout<< "1. Attack" <<endl;
                cout<< "2. Use Potion" <<endl;
                cout<< "3. Swap Weapon" <<endl;
                cout<< "4. Attempt to Run" <<endl;
                getline(cin, playerChoice);
                if(stoi(playerChoice) == 1){
                    rand_player_hit = rand() % 5;
                    if(rand_player_hit == 0){
                    cout<<"Miss!"<<endl;
                    }else{
                        for (int i = 0; i < player.getEquippedSize(); i++){
                            if(player.getEquippedElement(i).type == 'D'){
                                playerMainWeapon = player.getEquippedElement(i);
                                break;
                            } else {
                                has_weapon = false;
                            }
                        }
                        if(has_weapon == false){
                            cout<< player.getName() <<" does not have a weapon and therefore they die to " <<enemy.getName() <<endl;
                            setLosers(player);
                            return;
                        }
                        rand_player_damage = ((rand() % (int) playerMainWeapon.effect_value) + 1);
                        if((enemy.getWeakness() == 'F' && playerMainWeapon.element == 'W') || (enemy.getWeakness() == 'A' && playerMainWeapon.element == 'F') || (enemy.getWeakness() == 'E' && playerMainWeapon.element == 'A') || (enemy.getWeakness() == 'W' && playerMainWeapon.element == 'E')){
                            rand_player_damage *=2;
                        } else if ((enemy.getWeakness() == 'E' && playerMainWeapon.element == 'W') || (enemy.getWeakness() == 'A' && playerMainWeapon.element == 'E') || (enemy.getWeakness() == 'F' && playerMainWeapon.element == 'A') || (enemy.getWeakness() == 'W' && playerMainWeapon.element == 'F')){
                            rand_player_damage /=2;
                        }
                        player_damage_dealt = rand_player_damage - enemy.getDefense();
                        if(player_damage_dealt < 3.5){
                            player_damage_dealt = 3.5;
                        } else{
                            player_damage_dealt *= 3.5;
                        }
                        cout<< "Hit successful! Deals " << player_damage_dealt<< " damage!" <<endl;
                        cout<< "Enemy HP before: " << enemy.getHP() <<endl;
                        enemy.setHP(enemy.getHP() - player_damage_dealt);
                        cout<< "Enemy HP after: " << enemy.getHP() <<endl;
                        
                        if (enemy.getHP() == 0){
                            cout<< "Battle ended." <<endl;
                            cout<< enemy.getName() << " has been defeated!" <<endl;
                            cout<< player.getName() << " inherits " << enemy.getName() << "'s gold(" <<enemy.getGold() << ") and weapon(" << enemy.getEquippedElement(0).name << ")" <<endl;
                            player.setGold(player.getGold() + enemy.getGold());
                            player.appendInventory(enemy.getEquippedElement(0));
                            for (int i = 0; i < _islandEnemies.size(); i++){
                                if(enemy.getName() == _islandEnemies[i].getName()){
                                    _islandEnemies.erase(_islandEnemies.begin() + i);
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    cout << "Swapping turns!" <<endl;
                } else if(stoi(playerChoice) == 2){
                    if(player.getPotionsSize() == 0){
                        cout<<"You have no potions to consume!" <<endl;
                        
                    } else {
                        cout<<"Current potions:" <<endl;
                        for (int i = 0; i <player.getPotionsSize(); i++ ){
                            cout<< "(" <<i+1<< ") "  << player.getPotionsElement(i).name <<endl;
                        }
                        cout<<endl;
                        cout<<"Please select the potion that you wish to use" <<endl;
                        getline(cin, usePotion);
                        cout<< "Successfully consumed a " <<player.getPotionsElement(stoi(usePotion) - 1).name <<endl;
                        if(player.getPotionsElement(stoi(usePotion) - 1).name == "Lesser Health Potion" || player.getPotionsElement(stoi(usePotion) - 1).name == "Greater Health Potion"){
                            cout<< "HP before: " << player.getHP() <<endl;
                            player.usePotion(stoi(usePotion) - 1);
                            cout<< "HP after: " << player.getHP() <<endl;
                        }else if (player.getPotionsElement(stoi(usePotion) - 1).name == "Lesser Stamina Potion" || player.getPotionsElement(stoi(usePotion) - 1).name == "Greater Stamina Potion"){
                            cout<< "Stamina before: " << player.getStamina() <<endl;
                            player.usePotion(stoi(usePotion) - 1);
                            cout<< "Stamina after: " << player.getStamina() <<endl;
                        }else if (player.getPotionsElement(stoi(usePotion) - 1).name == "Cleansing Potion"){
                            cout<< "Condition before: " << player.getCondition() <<endl;
                            player.usePotion(stoi(usePotion) - 1);
                            cout<< "Condition after: " << player.getCondition() <<endl;
                        } else if (player.getPotionsElement(stoi(usePotion) - 1).name == "Greater Rejuvenation Potion" || player.getPotionsElement(stoi(usePotion) - 1).name == "Lesser Rejuvenation Potion"){
                            cout<< "HP before: " << player.getHP() <<endl;
                            cout<< "Stamina before: " << player.getStamina() <<endl;
                            player.usePotion(stoi(usePotion) - 1);
                            cout<< "HP after: " << player.getHP() <<endl;
                            cout<< "Stamina after: " << player.getStamina() <<endl;
                        }else if (player.getPotionsElement(stoi(usePotion) - 1).name == "Minor Strength Potion" || player.getPotionsElement(stoi(usePotion) - 1).name == "Major Strength Potion"){
                            for (int i = 0; i < player.getEquippedSize(); i++){
                                cout<< "Weapon "<<i+1<< " damage before: "  << player.getEquippedElement(i).effect_value<<endl;
                            }
                            player.usePotion(stoi(usePotion) - 1);
                            for (int i = 0; i < player.getEquippedSize(); i++){
                                cout<< "Weapon "<<i+1<< " damage after: "  << player.getEquippedElement(i).effect_value<<endl;
                            }
                        }
                    }
                        cout << "Swapping turns!" <<endl;
                } else if(stoi(playerChoice) == 3){
                    if(player.getInventorySize() == 0){
                        cout<<"You have nothing in your inventory to swap!" <<endl;
                    } else{
                    
                        cout<<"Current inventory:" <<endl;
                        for (int i = 0; i <player.getInventorySize(); i++ ){
                            cout<< "(" <<i+1<< ") "<<player.getInventoryElement(i).name <<endl;
                        }
                        cout<<endl;
                        cout<<"Please select the item that you wish to swap into your equipped inventory" <<endl;
                        getline(cin, inventorySwap);
                        cout<<endl;
                        
                        cout<<"Current equipped inventory:" <<endl;
                        for (int i = 0; i <player.getEquippedSize(); i++ ){
                            cout<< "(" <<i+1<< ") "<<player.getEquippedElement(i).name;
                        }
                        cout<<endl;
                        cout<<"Please select the item that you wish to swap into your inventory" <<endl;
                        getline(cin, equippedSwap);
                        cout<< "Player Weapon Before: " << player.getEquippedElement(stoi(equippedSwap) - 1).name <<endl;
                        player.swap(stoi(inventorySwap) - 1, stoi(equippedSwap) - 1);
                        cout<< "Player Weapon After: " << player.getEquippedElement(stoi(equippedSwap) - 1).name <<endl;
                    }
                    cout << "Swapping turns!" <<endl;
                } else if(stoi(playerChoice) == 4){
                    rand_run = rand() % 10;
                    if(rand_run == 0){
                        cout<< "Your attempt to run was unsuccessful and " <<enemy.getName() << " has killed you." <<endl;
                        setLosers(player);
                        return;
                    }else{
                        //where do you think you're going(extra credit)
                        cout<< "Your attempt to run was successful" <<endl;
                        
                        rand_enemy_damage = ((rand() % (int) enemy.getEquippedElement(0).effect_value) + 1);
                        if((player.getWeakness() == 'F' && enemy.getEquippedElement(0).element == 'W') || (player.getWeakness() == 'A' && enemy.getEquippedElement(0).element == 'F') || (player.getWeakness() == 'E' && enemy.getEquippedElement(0).element == 'A') || (player.getWeakness() == 'W' &&enemy.getEquippedElement(0).element == 'E')){
                            rand_enemy_damage *=2;
                        } else if ((player.getWeakness() == 'E' && enemy.getEquippedElement(0).element == 'W') || (player.getWeakness() == 'A' && enemy.getEquippedElement(0).element == 'E') || (player.getWeakness() == 'F' && enemy.getEquippedElement(0).element == 'A') || (player.getWeakness() == 'W' && enemy.getEquippedElement(0).element == 'F')){
                            rand_enemy_damage /=2;
                        }
                        enemy_damage_dealt = rand_enemy_damage - player.getDefense();
                        if(enemy_damage_dealt < 2.5){
                            enemy_damage_dealt = 2.5;
                        } else{
                            enemy_damage_dealt *= 2.5;
                        }   
                                
                        cout<< enemy.getName() << " hits you for " <<enemy_damage_dealt<< " damage as you leave." <<endl;
                        cout<< "Player HP before: " << player.getHP() <<endl;
                        player.setHP(player.getHP() - enemy_damage_dealt);
                        cout<< "Player HP after: " << player.getHP() <<endl;
                        if (player.getHP() == 0){
                            cout<< "Battle ended." <<endl;
                            setLosers(player);
                            return;
                        }

                        player.setStamina(player.getStamina() - 35);
                        can_visit_shop = false;
                        return;
                    }
                }
        } while (true);
    }
    if(can_visit_shop == true){
        cout<< "After defeating an enemy, a player has the opportunity to visit the item shop" <<endl;
        itemShop(index);
    }
    
    
}

Entity Game::getActivePlayersElement(int index){
    return activePlayers[index];
}


void Game::epicCombat(Entity &player1, Entity &player2, Entity enemy){
    string playerChoice;
    Equipment playerMainWeapon;
    int rand_player_hit = 0;
    double rand_player_damage = 0;
    double player_damage_dealt = 0;
    string usePotion;
    string inventorySwap;
    string equippedSwap;
    int rand_run = 0;
    bool has_weapon = true;
    
    
    bool isInFight1 = true;
    bool isInFight2 = true;

    int rand_enemy_hit = 0;
    double rand_enemy_damage1 = 0;
    double enemy_damage_dealt1 = 0;
    double rand_enemy_damage2 = 0;
    double enemy_damage_dealt2 = 0;

    
    cout << "Commencing battle." <<endl;

    do{
        for (int i = 0; i < getLosersSize(); i++){
            if (player1.getName() == losers[i].getName()){
                isInFight1 = false;
            }
        }
        for (int i = 0; i < runners.size(); i++){
            if (player1.getName() == runners[i].getName()){
                isInFight1 = false;
            }
        }

        if(isInFight1){
            player1.printStats();
            enemy.printStats();
            cout<< player1.getName() << ", which action would you like to take?" <<endl;
            cout<< "1. Attack" <<endl;
            cout<< "2. Use Potion" <<endl;
            cout<< "3. Swap Weapon" <<endl;
            cout<< "4. Attempt to Run" <<endl;
            getline(cin, playerChoice);
            if(stoi(playerChoice) == 1){
                rand_player_hit = rand() % 5;
                if(rand_player_hit == 0){
                    cout<<"Miss!"<<endl;
                }else{
                    for (int i = 0; i < player1.getEquippedSize(); i++){
                        if(player1.getEquippedElement(i).type == 'D'){
                            playerMainWeapon = player1.getEquippedElement(i);
                        break;
                        } else{
                            has_weapon = false;
                        }
                    }
                    if(has_weapon == false){
                        cout<< player1.getName() <<" does not have a weapon and therefore they die to " <<enemy.getName() <<endl;
                        setLosers(player1);
                    }
                    rand_player_damage = ((rand() % (int) playerMainWeapon.effect_value) + 1);
                    if((enemy.getWeakness() == 'F' && playerMainWeapon.element == 'W') || (enemy.getWeakness() == 'A' && playerMainWeapon.element == 'F') || (enemy.getWeakness() == 'E' && playerMainWeapon.element == 'A') || (enemy.getWeakness() == 'W' && playerMainWeapon.element == 'E')){
                        rand_player_damage *=2;
                    } else if ((enemy.getWeakness() == 'E' && playerMainWeapon.element == 'W') || (enemy.getWeakness() == 'A' && playerMainWeapon.element == 'E') || (enemy.getWeakness() == 'F' && playerMainWeapon.element == 'A') || (enemy.getWeakness() == 'W' && playerMainWeapon.element == 'F')){
                        rand_player_damage /=2;
                    }
                    player_damage_dealt = rand_player_damage - enemy.getDefense();
                    if(player_damage_dealt < 3.5){
                        player_damage_dealt = 3.5;
                    } else{
                        player_damage_dealt *= 3.5;
                    }
                    cout<< "Hit successful! Deals " << player_damage_dealt<< " damage!" <<endl;
                    cout<< "Enemy HP before: " << enemy.getHP() <<endl;
                    enemy.setHP(enemy.getHP() - player_damage_dealt);
                    cout<< "Enemy HP after: " << enemy.getHP() <<endl;
                    
                    if (enemy.getHP() == 0){
                        cout<< "Battle ended." <<endl;
                        cout<< enemy.getName() << " has been defeated!" <<endl;
                        cout<< player1.getName() << " and " << player2.getName() << " both inherits " << enemy.getName() << "'s gold(" <<enemy.getGold() << ") and weapon(" << enemy.getEquippedElement(0).name << ")" <<endl;
                        player1.setGold(player1.getGold() + enemy.getGold());
                        player1.appendInventory(enemy.getEquippedElement(0));
                        player2.setGold(player2.getGold() + enemy.getGold());
                        player2.appendInventory(enemy.getEquippedElement(0));
                        for (int i = 0; i < _islandEnemies.size(); i++){
                                if(enemy.getName() == _islandEnemies[i].getName()){
                                    _islandEnemies.erase(_islandEnemies.begin() + i);
                                    break;
                                }
                            }
                        return;
                    }
                    
                    
                
                }
                cout << "Swapping turns!" <<endl;
            } else if(stoi(playerChoice) == 2){
                if(player1.getPotionsSize() == 0){
                    cout<<"You have no potions to consume!" <<endl;
                    
                } else {
                    cout<<"Current potions:" <<endl;
                    for (int i = 0; i <player1.getPotionsSize(); i++ ){
                        cout<< "(" <<i+1<< ") "  << player1.getPotionsElement(i).name <<endl;
                    }
                    cout<<endl;
                    cout<<"Please select the potion that you wish to use" <<endl;
                    getline(cin, usePotion);
                    cout<< "Successfully consumed a " <<player1.getPotionsElement(stoi(usePotion) - 1).name <<endl;
                    if(player1.getPotionsElement(stoi(usePotion) - 1).name == "Lesser Health Potion" || player1.getPotionsElement(stoi(usePotion) - 1).name == "Greater Health Potion"){
                        cout<< "HP before: " << player1.getHP() <<endl;
                        player1.usePotion(stoi(usePotion) - 1);
                        cout<< "HP after: " << player1.getHP() <<endl;
                    }else if (player1.getPotionsElement(stoi(usePotion) - 1).name == "Lesser Stamina Potion" || player1.getPotionsElement(stoi(usePotion) - 1).name == "Greater Stamina Potion"){
                        cout<< "Stamina before: " << player1.getStamina() <<endl;
                        player1.usePotion(stoi(usePotion) - 1);
                        cout<< "Stamina after: " << player1.getStamina() <<endl;
                    }else if (player1.getPotionsElement(stoi(usePotion) - 1).name == "Cleansing Potion"){
                        cout<< "Condition before: " << player1.getCondition() <<endl;
                        player1.usePotion(stoi(usePotion) - 1);
                        cout<< "Condition after: " << player1.getCondition() <<endl;
                    } else if (player1.getPotionsElement(stoi(usePotion) - 1).name == "Greater Rejuvenation Potion" || player1.getPotionsElement(stoi(usePotion) - 1).name == "Lesser Rejuvenation Potion"){
                        cout<< "HP before: " << player1.getHP() <<endl;
                        cout<< "Stamina before: " << player1.getStamina() <<endl;
                        player1.usePotion(stoi(usePotion) - 1);
                        cout<< "HP after: " << player1.getHP() <<endl;
                        cout<< "Stamina after: " << player1.getStamina() <<endl;
                    }else if (player1.getPotionsElement(stoi(usePotion) - 1).name == "Minor Strength Potion" || player1.getPotionsElement(stoi(usePotion) - 1).name == "Major Strength Potion"){
                        for (int i = 0; i < player1.getEquippedSize(); i++){
                            cout<< "Weapon "<<i+1<< " damage before: "  << player1.getEquippedElement(i).effect_value<<endl;
                        }
                        player1.usePotion(stoi(usePotion) - 1);
                        for (int i = 0; i < player1.getEquippedSize(); i++){
                            cout<< "Weapon "<<i+1<< " damage after: "  << player1.getEquippedElement(i).effect_value<<endl;
                        }
                    }
                }
                cout << "Swapping turns!" <<endl;
            } else if(stoi(playerChoice) == 3){
                if(player1.getInventorySize() == 0){
                    cout<<"You have nothing in your inventory to swap!" <<endl;
                } else{
                
                    cout<<"Current inventory:" <<endl;
                    for (int i = 0; i <player1.getInventorySize(); i++ ){
                        cout<< "(" <<i+1<< ") "<<player1.getInventoryElement(i).name <<endl;
                    }
                    cout<<endl;
                    cout<<"Please select the item that you wish to swap into your equipped inventory" <<endl;
                    getline(cin, inventorySwap);
                    cout<<endl;
                    
                    cout<<"Current equipped inventory:" <<endl;
                    for (int i = 0; i <player1.getEquippedSize(); i++ ){
                        cout<< "(" <<i+1<< ") "<<player1.getEquippedElement(i).name;
                    }
                    cout<<endl;
                    cout<<"Please select the item that you wish to swap into your inventory" <<endl;
                    getline(cin, equippedSwap);
                    cout<< "Player Weapon Before: " << player1.getEquippedElement(stoi(equippedSwap) - 1).name <<endl;
                    player1.swap(stoi(inventorySwap) - 1, stoi(equippedSwap) - 1);
                    cout<< "Player Weapon After: " << player1.getEquippedElement(stoi(equippedSwap) - 1).name <<endl;
                }
                cout << "Swapping turns!" <<endl;
            } else if(stoi(playerChoice) == 4){
                rand_run = rand() % 10;
                if(rand_run == 0){
                    cout<< "Your attempt to run was unsuccessful and " <<enemy.getName() << " has killed you." <<endl;
                    setLosers(player1);
                }else{
                    cout<< "Your attempt to run was successful" <<endl;
                    rand_enemy_damage1 = ((rand() % (int) enemy.getEquippedElement(0).effect_value) + 1);
                    rand_enemy_damage1 *= 2.5;
                    enemy_damage_dealt1 = rand_enemy_damage1 - player1.getDefense();
                    
                    if(enemy_damage_dealt1 < 0){
                        enemy_damage_dealt1 = 2.5;
                    }
                    
                    cout<< enemy.getName() << " hits you for " <<enemy_damage_dealt1<< " damage as you leave." <<endl;
                    cout<< "Player HP before: " << player1.getHP() <<endl;
                    player1.setHP(player1.getHP() - enemy_damage_dealt1);
                    cout<< "Player HP after: " << player1.getHP() <<endl;
                    if(losers.size() > 0){
                        if (player1.getHP() == 0 && (player1.getName() != losers[0].getName())){
                            cout<< player1.getName() << " has been killed." <<endl;
                            setLosers(player1);
                        }
                    } else{
                        if (player1.getHP() == 0){
                            cout<< player1.getName() << " has been killed." <<endl;
                            setLosers(player1);
                        }
                    }
                    setRunner(player1);
                    player1.setStamina(player1.getStamina() - 35);
                }
            }
        }
        rand_run = 0;
        rand_player_hit = 0;
        rand_player_damage = 0;
        player_damage_dealt = 0;
        has_weapon = true;

        if(isInFight2){
            player2.printStats();
            enemy.printStats();
            cout<< player2.getName() << ", which action would you like to take?" <<endl;
            cout<< "1. Attack" <<endl;
            cout<< "2. Use Potion" <<endl;
            cout<< "3. Swap Weapon" <<endl;
            cout<< "4. Attempt to Run" <<endl;
            getline(cin, playerChoice);
            if(stoi(playerChoice) == 1){
                rand_player_hit = rand() % 5;
                if(rand_player_hit == 0){
                    cout<<"Miss!"<<endl;
                }else{
                    for (int i = 0; i < player2.getEquippedSize(); i++){
                        if(player2.getEquippedElement(i).type == 'D'){
                            playerMainWeapon = player2.getEquippedElement(i);
                        break;
                        } else{
                            has_weapon = false;
                        }
                    }
                    if(has_weapon == false){
                        cout<< player2.getName() <<" does not have a weapon and therefore they die to " <<enemy.getName() <<endl;
                        setLosers(player2);
                    }
                    rand_player_damage = ((rand() % (int) playerMainWeapon.effect_value) + 1);
                    if((enemy.getWeakness() == 'F' && playerMainWeapon.element == 'W') || (enemy.getWeakness() == 'A' && playerMainWeapon.element == 'F') || (enemy.getWeakness() == 'E' && playerMainWeapon.element == 'A') || (enemy.getWeakness() == 'W' && playerMainWeapon.element == 'E')){
                        rand_player_damage *=2;
                    } else if ((enemy.getWeakness() == 'E' && playerMainWeapon.element == 'W') || (enemy.getWeakness() == 'A' && playerMainWeapon.element == 'E') || (enemy.getWeakness() == 'F' && playerMainWeapon.element == 'A') || (enemy.getWeakness() == 'W' && playerMainWeapon.element == 'F')){
                        rand_player_damage /=2;
                    }
                    player_damage_dealt = rand_player_damage - enemy.getDefense();
                    if(player_damage_dealt < 3.5){
                        player_damage_dealt = 3.5;
                    } else{
                        player_damage_dealt *= 3.5;
                    }
                    cout<< "Hit successful! Deals " << player_damage_dealt<< " damage!" <<endl;
                    cout<< "Enemy HP before: " << enemy.getHP() <<endl;
                    enemy.setHP(enemy.getHP() - player_damage_dealt);
                    cout<< "Enemy HP after: " << enemy.getHP() <<endl;
                    
                    if (enemy.getHP() == 0){
                        cout<< "Battle ended." <<endl;
                        cout<< enemy.getName() << " has been defeated!" <<endl;
                        cout<< player1.getName() << " and " << player2.getName() << " both inherits " << enemy.getName() << "'s gold(" <<enemy.getGold() << ") and weapon(" << enemy.getEquippedElement(0).name << ")" <<endl;
                        player1.setGold(player1.getGold() + enemy.getGold());
                        player1.appendInventory(enemy.getEquippedElement(0));
                        player2.setGold(player2.getGold() + enemy.getGold());
                        player2.appendInventory(enemy.getEquippedElement(0));
                        for (int i = 0; i < _islandEnemies.size(); i++){
                                if(enemy.getName() == _islandEnemies[i].getName()){
                                    _islandEnemies.erase(_islandEnemies.begin() + i);
                                    break;
                                }
                            }
                        return;
                    }
                    
                    
                
                }
                cout << "Swapping turns!" <<endl;
            } else if(stoi(playerChoice) == 2){
                if(player2.getPotionsSize() == 0){
                    cout<<"You have no potions to consume!" <<endl;
                    
                } else {
                    cout<<"Current potions:" <<endl;
                    for (int i = 0; i <player2.getPotionsSize(); i++ ){
                        cout<< "(" <<i+1<< ") "  << player2.getPotionsElement(i).name <<endl;
                    }
                    cout<<endl;
                    cout<<"Please select the potion that you wish to use" <<endl;
                    getline(cin, usePotion);
                    cout<< "Successfully consumed a " <<player2.getPotionsElement(stoi(usePotion) - 1).name <<endl;
                    if(player2.getPotionsElement(stoi(usePotion) - 1).name == "Lesser Health Potion" || player2.getPotionsElement(stoi(usePotion) - 1).name == "Greater Health Potion"){
                        cout<< "HP before: " << player2.getHP() <<endl;
                        player2.usePotion(stoi(usePotion) - 1);
                        cout<< "HP after: " << player2.getHP() <<endl;
                    }else if (player2.getPotionsElement(stoi(usePotion) - 1).name == "Lesser Stamina Potion" || player2.getPotionsElement(stoi(usePotion) - 1).name == "Greater Stamina Potion"){
                        cout<< "Stamina before: " << player2.getStamina() <<endl;
                        player2.usePotion(stoi(usePotion) - 1);
                        cout<< "Stamina after: " << player2.getStamina() <<endl;
                    }else if (player2.getPotionsElement(stoi(usePotion) - 1).name == "Cleansing Potion"){
                        cout<< "Condition before: " << player2.getCondition() <<endl;
                        player2.usePotion(stoi(usePotion) - 1);
                        cout<< "Condition after: " << player2.getCondition() <<endl;
                    } else if (player2.getPotionsElement(stoi(usePotion) - 1).name == "Greater Rejuvenation Potion" || player2.getPotionsElement(stoi(usePotion) - 1).name == "Lesser Rejuvenation Potion"){
                        cout<< "HP before: " << player2.getHP() <<endl;
                        cout<< "Stamina before: " << player2.getStamina() <<endl;
                        player2.usePotion(stoi(usePotion) - 1);
                        cout<< "HP after: " << player2.getHP() <<endl;
                        cout<< "Stamina after: " << player2.getStamina() <<endl;
                    }else if (player2.getPotionsElement(stoi(usePotion) - 1).name == "Minor Strength Potion" || player2.getPotionsElement(stoi(usePotion) - 1).name == "Major Strength Potion"){
                        for (int i = 0; i < player2.getEquippedSize(); i++){
                            cout<< "Weapon "<<i+1<< " damage before: "  << player2.getEquippedElement(i).effect_value<<endl;
                        }
                        player2.usePotion(stoi(usePotion) - 1);
                        for (int i = 0; i < player2.getEquippedSize(); i++){
                            cout<< "Weapon "<<i+1<< " damage after: "  << player2.getEquippedElement(i).effect_value<<endl;
                        }
                    }
                }
                cout << "Swapping turns!" <<endl;
            } else if(stoi(playerChoice) == 3){
                if(player2.getInventorySize() == 0){
                    cout<<"You have nothing in your inventory to swap!" <<endl;
                } else{
                
                    cout<<"Current inventory:" <<endl;
                    for (int i = 0; i <player2.getInventorySize(); i++ ){
                        cout<< "(" <<i+1<< ") "<<player2.getInventoryElement(i).name <<endl;
                    }
                    cout<<endl;
                    cout<<"Please select the item that you wish to swap into your equipped inventory" <<endl;
                    getline(cin, inventorySwap);
                    cout<<endl;
                    
                    cout<<"Current equipped inventory:" <<endl;
                    for (int i = 0; i <player2.getEquippedSize(); i++ ){
                        cout<< "(" <<i+1<< ") "<<player2.getEquippedElement(i).name;
                    }
                    cout<<endl;
                    cout<<"Please select the item that you wish to swap into your inventory" <<endl;
                    getline(cin, equippedSwap);
                    cout<< "Player Weapon Before: " << player2.getEquippedElement(stoi(equippedSwap) - 1).name <<endl;
                    player2.swap(stoi(inventorySwap) - 1, stoi(equippedSwap) - 1);
                    cout<< "Player Weapon After: " << player2.getEquippedElement(stoi(equippedSwap) - 1).name <<endl;
                }
                cout << "Swapping turns!" <<endl;
            } else if(stoi(playerChoice) == 4){
                rand_run = rand() % 10;
                if(rand_run == 0){
                    cout<< "Your attempt to run was unsuccessful and " <<enemy.getName() << " has killed you." <<endl;
                    setLosers(player2);
                }else{
                    cout<< "Your attempt to run was successful" <<endl;
                    rand_enemy_damage2 = ((rand() % (int) enemy.getEquippedElement(0).effect_value) + 1);
                    rand_enemy_damage2 *= 2.5;
                    enemy_damage_dealt2 = rand_enemy_damage2 - player2.getDefense();
                    
                    if(enemy_damage_dealt2 < 0){
                        enemy_damage_dealt2 = 2.5;
                    }
                    
                    cout<< enemy.getName() << " hits you for " <<enemy_damage_dealt2<< " damage as you leave." <<endl;
                    cout<< "Player HP before: " << player2.getHP() <<endl;
                    player2.setHP(player2.getHP() - enemy_damage_dealt2);
                    cout<< "Player HP after: " << player2.getHP() <<endl;
                    if (player2.getHP() == 0 && (player2.getName() != losers[0].getName())){
                        cout<< player2.getName() << " has been killed." <<endl;
                        setLosers(player2);
                    }
                    setRunner(player2);
                    player2.setStamina(player2.getStamina() - 35);
                }
            }
            rand_enemy_hit = 0;
            rand_enemy_damage1 = 0;
            enemy_damage_dealt1 = 0;
            rand_enemy_damage2 = 0;
            enemy_damage_dealt2 = 0;


            cout<< "Remember: On their turn, Enemies only attack." <<endl;
            rand_enemy_hit = rand() % 5;
            if(rand_enemy_hit == 0){
                cout<<"Miss!"<<endl;
            }else{
                rand_enemy_damage1 = ((rand() % (int) enemy.getEquippedElement(0).effect_value) + 1);
                if((player1.getWeakness() == 'F' && enemy.getEquippedElement(0).element == 'W') || (player1.getWeakness() == 'A' && enemy.getEquippedElement(0).element == 'F') || (player1.getWeakness() == 'E' && enemy.getEquippedElement(0).element == 'A') || (player1.getWeakness() == 'W' && enemy.getEquippedElement(0).element == 'E')){
                    rand_enemy_damage1 *=2;
                } else if ((player1.getWeakness() == 'E' && enemy.getEquippedElement(0).element == 'W') || (player1.getWeakness() == 'A' && enemy.getEquippedElement(0).element == 'E') || (player1.getWeakness() == 'F' && enemy.getEquippedElement(0).element == 'A') || (player1.getWeakness() == 'W' && enemy.getEquippedElement(0).element == 'F')){
                    rand_enemy_damage1 /=2;
                }
                enemy_damage_dealt1 = rand_enemy_damage1 - player1.getDefense();
                if(enemy_damage_dealt1 < 2.5){
                    enemy_damage_dealt1 = 2.5;
                } else{
                    enemy_damage_dealt1 *= 2.5;
                }    
                rand_enemy_damage2 = ((rand() % (int) enemy.getEquippedElement(0).effect_value) + 1);
                if((player2.getWeakness() == 'F' && enemy.getEquippedElement(0).element == 'W') || (player2.getWeakness() == 'A' && enemy.getEquippedElement(0).element == 'F') || (player2.getWeakness() == 'E' && enemy.getEquippedElement(0).element == 'A') || (player2.getWeakness() == 'W' &&enemy.getEquippedElement(0).element == 'E')){
                    rand_enemy_damage2 *=2;
                } else if ((player2.getWeakness() == 'E' && enemy.getEquippedElement(0).element == 'W') || (player2.getWeakness() == 'A' && enemy.getEquippedElement(0).element == 'E') || (player2.getWeakness() == 'F' && enemy.getEquippedElement(0).element == 'A') || (player2.getWeakness() == 'W' && enemy.getEquippedElement(0).element == 'F')){
                    rand_enemy_damage2 /=2;
                }
                enemy_damage_dealt2 = rand_enemy_damage2 - player2.getDefense();
                if(enemy_damage_dealt2 < 2.5){
                    enemy_damage_dealt2 = 2.5;
                } else{
                    enemy_damage_dealt2 *= 2.5;
                }    

                cout<< "Hit successful! Deals " << enemy_damage_dealt1 << " damage to "  <<player1.getName() << " and " <<enemy_damage_dealt2 << " damage to "  <<player2.getName() <<endl;
                cout<< "Player 1 HP before: " << player1.getHP() <<endl;
                cout<< "Player 2 HP before: " << player2.getHP() <<endl;
                player1.setHP(player1.getHP() - enemy_damage_dealt1);
                player2.setHP(player2.getHP() - enemy_damage_dealt2);
                cout<< "Player 1 HP after: " << player1.getHP() <<endl;
                cout<< "Player 2 HP after: " << player2.getHP() <<endl;
                if(losers.size() > 0){
                        if (player1.getHP() == 0 && (player1.getName() != losers[0].getName())){
                            cout<< player1.getName() << " has been killed." <<endl;
                            setLosers(player1);
                            return;
                        }
                        if (player2.getHP() == 0 && (player2.getName() != losers[0].getName())){
                            cout<< player2.getName() << " has been killed." <<endl;
                            setLosers(player2);
                            return;
                        }
                    } else{
                        if (player1.getHP() == 0){
                            cout<< player1.getName() << " has been killed." <<endl;
                            setLosers(player1);
                        }
                        if (player2.getHP() == 0){
                            cout<< player2.getName() << " has been killed." <<endl;
                            setLosers(player2);
                        }
                    }
            }    
                cout << "Swapping turns!" <<endl;
        }
    } while (runners.size() < 2 && losers.size() < 2);



}



void Game::setRunner(Entity runner){
    runners.push_back(runner);
}

Entity Game::getRunnerElement(int index){
    return runners[index];
}  
            