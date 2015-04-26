# Daniel_Rapacchietta_CSCI2270_Final

----Summary----

This program will offer users to edit and play a labyrinth game. The program will utalize a text file input and the graph data structure to store the maze. Users can add rooms and connections, edit distances (which in this program will represent a percentage chance of falling into a trap), Find the shortest and safest path through their maze, as well as play through their maze.

---How to Run---

A "maze.txt" file is required to run the program (as argument 1). The structure is similar to the graph assignment.
1. The first line of the maze.txt file must have "rooms" followed by comma separated room names.
ex: rooms,entrance,hallway,balcony...etc
2. All lines after the first should contain the names of the rooms in the first line (in the same order),
followed by comma separated integer values between 0 and 50 for connected rooms.
ex: entrance,-2,40,30,20...etc
3. Any two rooms that are not connected must be represented by a -1 in the maze.txt file.
4. There must be a -2 value when putting in the risk value for the same two rooms.

Restrictions:
- In the maze game the risk values represent the percentage chance of falling into a trap. This chance can only be 
between 0% (safe) and 50% (very dangerous).

An example maze.txt file is provided in the repo. Here is the graph of that file.
/////


---Dependencies---

This program does not require any additional dependencies.

---System Requirements---

This program should run on all platforms that have a C++ 11 compiler.

---Group Members/Contributors---

N/A

--Known bugs---

None.
