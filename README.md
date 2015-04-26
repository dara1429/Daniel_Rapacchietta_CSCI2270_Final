# Daniel_Rapacchietta_CSCI2270_Final

----Summary----

This program will offer users to edit and play a labyrinth game. The program will utalize a text file input and the graph data structure to store the maze. Users can add rooms and connections, edit distances (which in this program will represent a percentage chance of falling into a trap), Find the shortest and safest path through their maze, as well as play through their maze.

---How to Run---

A "maze.txt" file is required to run the program (as argument 1). The structure is similar to the graph assignment.

1. The first line of the maze.txt file must have "rooms" followed by comma separated room names.

2. All lines after the first should contain the names of the rooms in the first line (in the same order),
followed by comma separated integer values between 0 and 50 for connected rooms.


3. Any two rooms that are not connected must be represented by a -1 in the maze.txt file.


4. There must be a -2 value when putting in the risk value for the same two rooms.

5. There must be a room called "Entrance" and "Exit" (can be lowercase). These are used for the starting room for the player and the destination room to win the game. You should entrance as the first room and exit as the last when making the text file but it is not necessary.

Here is a small example:

rooms,entrance,room1,room2,exit

entrance,-2,10,-1,-1

room1,10,-2,20,-1

room2,-1,20,-2,50

exit,-1,-1,50,-2

Restrictions:
- In the maze game the risk values represent the percentage chance of falling into a trap. This chance can only be 
between 0% (safe) and 50% (very dangerous).

An example maze.txt file is provided in the repo. Here is the graph of that file.
![alt tag](https://raw.github.com/dara1429/Rapacchietta_CSCI2270_FinalProject/master/finalproject/maze.jpg)

---Dependencies---

This program does not require any additional dependencies.

---System Requirements---

This program should run on all platforms that have a C++ 11 compiler.

---Group Members/Contributors---

N/A

--Known bugs---

1. When a user enters a string after being asked for a numerical input, the program gets stuck in a loop.
