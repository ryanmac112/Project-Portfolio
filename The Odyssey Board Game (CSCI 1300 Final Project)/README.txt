------------------------
HOW TO COMPILE AND RUN
------------------------
Compile: g++ -g -Wall -Werror -Wpedantic -std=c++17 Entity.cpp Game.cpp Map.cpp project2.cpp
Run: ./a.out
------------------------
DEPENDENCIES
------------------------
Entity.h, Map.h, Game.h, playableChar.txt, epicEquipment.txt, allEquipment.txt, epicEnemies.txt, 
islandEnemies.txt, allPotions.txt, and riddles.txt must be in the same
directory as the cpp files in order to compile.
------------------------
SUBMISSION INFORMATION
------------------------
CSCI1300 Spring 2024 Project 2
Author: Ryan McElvain
Recitation: 103 - Chethan Kavaraganahalli Prasanna
Date: Apr 25, 2024
------------------------
ABOUT THIS PROJECT
------------------------
This project implements an interactive board game themed after the Greek story The Odyssey. The
game is a pvp race to the island Ithaca, with many outcomes on every tile such as fighting enemies,
random calamities, and even buried treasure. There is also a feature where both participating players 
work together to defeat an enemy together, and this is called Epic Combat. Among these facets, there 
are also item shops to be visited on board, and each player moves along the board by rolling a 6 sided die.
If a player dies, the other player is declared the winner, otherwise the winner is the player who reaches 
Ithaca first.