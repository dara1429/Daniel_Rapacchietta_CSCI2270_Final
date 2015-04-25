#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "maze.h"
class player
{
    public:
        player();
        virtual ~player();
        void gameStart(std::vector<vertex> maze);
        void gameShowChoices();
        void setDifficulty();
        int getLives();
        int getKeys();
        void setLives(int numLives);
        void setKeys(int numKeys);
    protected:
    private:
        int keys = 0;
        int lives = 3;
        vertex *currentRoom;
};

#endif // PLAYER_H
