#include <iostream>
#include "Computer.h"
using namespace std;

#ifndef BESTBUY_H
#define BESTBUY_H

class BestBuy
{
    public:

        // constructors
        BestBuy();
        BestBuy(Computer arr[], int p[], int f);

        // getters
        int getFloor();

        // other
        void initializeNames();
        void initializePrices();
        void displayStockInfo();
        void startBestBuy();
        int buy(int coins, int arr[], int f);
        int buyPart(int i, int coins, int arr[]);

    private:
        // data members
        int floor;
        const static int size = 10;
        Computer stock[size];
        int price[size];
};

#endif
