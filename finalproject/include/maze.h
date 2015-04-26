#ifndef MAZE_H
#define MAZE_H
#include<vector>
#include<iostream>

struct vertex;

struct adjVertex{
    vertex *v;
    //Chance of falling into a trap when traveling room to room.
    int risk;
};


struct vertex{
    std::string name;
    std::vector<adjVertex> adj;
    bool visited = false;
    //This int will check the graph after its created to check for unconnected rooms.
    int mazeCheck = -1;
    //ID number for each room.
    int ID = -1;
    //Used for calculating safest path.
    int risk = 0;
    //Used for calculating shortest path.
    int distance = 0;
    //Locked door. Needs a key to open if true.
    bool door = false;
    //Key located in this room
    bool key = false;
};

class maze
{
    public:
        maze();
        ~maze();
        bool createMaze(std::vector<std::string> rooms, std::vector< std::vector<int> > connections);
        void addEdge(std::string room1, std::string room2, int risk, int option);
        void addVertex(std::string name);
        void displayEdges();
        void mazeErrorCheck();
        void mazeErrorCheckBFT(std::string startingRoom, int id);
        void findSafestPath();
        void findShortestPath();
        void addDoorAndKey();
        void addRoom();
        void printRooms();
        std::vector<vertex> getVertices();
    protected:
    private:
        //Flag to determine if the maze was created successfully.
        bool mazeSet = false;
        //Holds entire maze data.
        std::vector<vertex> vertices;

};

#endif // MAZE_H
