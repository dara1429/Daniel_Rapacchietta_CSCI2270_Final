#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "maze.h"
class player
{
    public:
        player();
        virtual ~player();
        void game(std::vector<vertex> maze);
        int gameShowChoices(int choices);
        bool gameRisk(int risk);
        void setDifficulty();
        void gameHelp();
        int getLives();
        int getKeys();
        void setLives(int numLives);
        void setKeys(int numKeys);
    protected:
    private:
        int keys = 0;
        int lives = 3;
        std::vector<vertex> currentOptions;
        std::vector<int> currentRisks;
        vertex *currentRoom;
};

#endif // PLAYER_H
