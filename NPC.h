#include <iostream>
using namespace std;

#ifndef NPC_H
#define NPC_H

class NPC
{
    public:

        // constructors
        NPC();
        NPC(int f, int p);

        // setters
        void setFriendliness(int f);
        void setPuzzle(int p);

        // getters
        int getFriendliness();
        int getPuzzle();

        // other
        void puzzleGame();
        void friendlinessGame();
        bool playPuzzle(int l);
        int startNPC();

    private:

        // data members
        int friendliness;
        int puzzle;
};

#endif