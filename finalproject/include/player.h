#ifndef PLAYER_H
#define PLAYER_H


class player
{
    public:
        player();
        virtual ~player();
        void gameStart();
        void setDifficulty();
        int getLives();
        int getKeys();
        int getPosition();
        void setLives(int numLives);
        void setKeys(int numKeys);
        void setPosition(int ID);
    protected:
    private:
        int keys = 0;
        int lives = 3;
        int position = 0;
};

#endif // PLAYER_H
