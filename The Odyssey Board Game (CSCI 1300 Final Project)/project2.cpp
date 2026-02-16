#include <iostream>
#include <iomanip>
#include "Game.h"
#include "Entity.h"
#include "Map.h"
#include <fstream>
#include <string>
#include <cctype>
#include "Map.h"
#include <ctype.h>
#include <iostream>



using namespace std;



int main(){
    cout<<"Welcome to the Odyssey!" <<endl;
    Game thisGame;

     //this chunk is for setting player1/player2
    cout<< "Player 1 please select a player: " <<endl;   
    vector <Entity> playerList = thisGame.getCharacters();
    for (int i = 0; i < playerList.size(); i++){
        cout<< "(" <<i+1<< ") " <<playerList[i].getName() << " ";
    }
    cout<<endl;
    string charSelect;
    getline(cin, charSelect);
    thisGame.setPlayers(stoi(charSelect) - 1, 0);
    cout << thisGame.getPlayers(0).getName() << " chosen successfully!"<<endl;
    cout<<endl;
    playerList = thisGame.getCharacters();
    cout<< "Player 2 please select a player: " <<endl;
    for (int i = 0; i < playerList.size(); i++){
        cout<< "(" <<i+1<< ") " <<playerList[i].getName() << " ";
    }
    cout<<endl;
    getline(cin, charSelect);
    thisGame.setPlayers(stoi(charSelect) - 1, 1);
    cout << thisGame.getPlayers(1).getName() << " chosen successfully!"<<endl;
    cout<<endl;
    
    //this chunk is for both players to visit the item shop before departure
    cout<<"Before our departure, both players will have an opportunity to purchase an item from the Item Shop" <<endl;
    
    cout<< thisGame.getPlayers(0).getName() <<" will visit the Item Shop first." <<endl;
    cout<<endl;
    thisGame.itemShop(0);
    
    cout<< thisGame.getPlayers(1).getName() <<" will visit the Item Shop next." <<endl;
    cout<<endl;
    thisGame.itemShop(1);
    cout<<"Now that both players have had the opportunity to visit the item shop:" <<endl;
    cout<<endl;
    cout<<"LET THE GAMES BEGIN!!" <<endl;
    cout<<endl;
    
    bool _break = false;
    do{
        for (int i = 0; i < 2; i++){
            if(thisGame.getLosersSize() == 0){
                thisGame.playGame(i);
            } else{
                _break = true;
                break;
            }
        }
    } while (_break == false);
    ofstream out_file("results.txt");
    Entity winner;
    Entity loser;
    Entity players[2] = {thisGame.getActivePlayersElement(0), thisGame.getActivePlayersElement(1)};
    if(thisGame.getLosersSize() == 2){
        cout<<"Both players have died, therefore there is no winner." <<endl;
            for (int i = 0; i < 2; i++){
                out_file << "Player: " << players[i].getName() <<endl;
                out_file << "W/L: Loser" <<endl;
                out_file << "Gold held: " << players[i].getGold() <<endl;
                out_file << "HP: " << players[i].getHP() <<endl;
                out_file << "Stamina: " << players[i].getStamina() <<endl;
                out_file << "Equipped Inventory: " <<endl;
                for (int j = 0; j < players[i].getEquippedSize(); j++){
                    out_file<<players[i].getEquippedElement(j).name <<endl;
                }
                out_file << "Unequipped Inventory: " <<endl;
                for (int j = 0; j < players[i].getInventorySize(); j++){
                    out_file<<players[i].getInventoryElement(j).name <<endl;
                }
                out_file << endl;
            }  
    } else{
        for (int i = 0; i < 2; i++){
            if(thisGame.getLoser(0).getName() != players[i].getName()){
                winner = players[i];
            }
            if(thisGame.getLoser(0).getName() == players[i].getName()){
                loser = players[i];
            }
        }
        cout<< winner.getName() << " has won the Odyssey!" <<endl;
        out_file << "Player: " << winner.getName() <<endl;
        out_file << "W/L: Winner" <<endl;
        out_file << "Gold held: " << winner.getGold() <<endl;
        out_file << "HP: " << winner.getHP() <<endl;
        out_file << "Stamina: " << winner.getStamina() <<endl;
        out_file << "Equipped Inventory: " <<endl;
        for (int j = 0; j < winner.getEquippedSize(); j++){
            out_file<<winner.getEquippedElement(j).name <<endl;
        }
        out_file << "Unequipped Inventory: " <<endl;
        for (int j = 0; j < winner.getInventorySize(); j++){
            out_file<<winner.getInventoryElement(j).name <<endl;
        }
        out_file << endl;
        out_file << "Player: " << loser.getName() <<endl;
        out_file << "W/L: Loser" <<endl;
        out_file << "Gold held: " << loser.getGold() <<endl;
        out_file << "HP: " << loser.getHP() <<endl;
        out_file << "Stamina: " << loser.getStamina() <<endl;
        out_file << "Equipped Inventory: " <<endl;
        for (int j = 0; j < loser.getEquippedSize(); j++){
            out_file<<loser.getEquippedElement(j).name <<endl;
        }
        out_file << "Unequipped Inventory: " <<endl;
        for (int j = 0; j < loser.getInventorySize(); j++){
            out_file<<loser.getInventoryElement(j).name <<endl;
        }
}
      
    out_file.close();
    return 0;
}

