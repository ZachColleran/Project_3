#include <iostream>
#include "Computer.h"
using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
    public:

        // constructors
        Player();
        Player(string n, int c, int f, Computer arr[]);

        // setters
        void setName(string n);
        void setMoney(int m);
        void setFrustration(int f);
        void setStartName();

        // getters
        string getName();
        int getMoney();
        int getFrustration();
        string getComputerPartName(int i);
        void getComputerPartNames();
        void getComputerPartQuantities();
        int getSize();

        //other
        void initializeNames();
        void viewPartsInventory();
        void viewWholeInventory();
        void updateInventoryStats(int arr[]);
        void findInventoryStats(int arr[]);
        int addRandomPart();
        int subtractRandomPart();

        int repairComputer(int m);
        int virus(int v);
        void stackOverflow();
        bool playPuzzle(int l);

        bool battle(int f, int b);

    private:

        // data members
        string name;
        int coins;
        int frustration;
        const static int size = 10;
        Computer parts[size];
};

#endif