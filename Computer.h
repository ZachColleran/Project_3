#include <iostream>
using namespace std;

#ifndef COMPUTER_H
#define COMPUTER_H

class Computer
{
    public:

        // constructors
        Computer();
        Computer(string n, int q);

        // setters
        void setPartName(string n);
        void setPartQuantity(int q);

        // getters
        string getPartName(); 
        int getPartQuantity();

    private:

        // data members
        string partName;
        int partQuantity;
};

#endif